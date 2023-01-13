#ifndef SL_PERFECT_RECALL_HH
#define SL_PERFECT_RECALL_HH
#include <cassert>
#include <list>
#include <vector>
#include "utilities.hh"
#include "types.hh"
#include "cuddObj.hh"
#include "benchmark.hh"

using namespace std;


// Strategy Logic quantifier.
class quantifier {
  private:
    string variable_name;
    bool existential;
    bool auxiliary;
    vector<basic_agent *> agents;
  public:
    quantifier(const string & ariable_name, bool existential, bool auxiliary,
        const vector<basic_agent *> & agents);
    quantifier(const string & variable_name, bool existential, bool auxiliary);
    const string & get_variable_name() const;
    bool is_existential() const;
    bool is_auxiliary() const;
    const vector<basic_agent *> & get_agents() const;
    string get_quantifier() const;
    string get_bindings() const;
};

// General automaton (without an acceptance condition).
class automaton {
  private:
    BDD initial_state;
    BDD transition_relation;
    vector<BDD> state_variables;
    vector<BDD> state_next_variables;
    vector<BDD> action_variables;
    BDD reachable_states;
    bdd_parameters *para;
    static void print_state(const BDD & result,
        const vector<BDD> *state_variables, unsigned int state_index,
        bdd_parameters *para);
    static void print_transition(const BDD & result,
        const vector<BDD> *state_variables,
        const vector<BDD> *state_next_variables,
        const vector<BDD> *action_variables, unsigned int state_index,
        unsigned int state_next_index, unsigned int action_index,
        bdd_parameters *para);
  public:
    automaton(const BDD & initial_state, const BDD & transition_relation,
        const vector<BDD> & state_variables,
        const vector<BDD> & state_next_variables,
        const vector<BDD> & action_variables, bdd_parameters *para);
    const BDD & get_initial_state() const;
    const BDD & get_transition_relation() const;
    const vector<BDD> & get_state_variables() const;
    const vector<BDD> & get_state_next_variables() const;
    const vector<BDD> & get_action_variables() const;
    const BDD & get_reachable_states() const;
    bdd_parameters *get_parameters() const;
    BDD swap_variables(const BDD & state) const;
    virtual void print() const;
    static void print_state(const BDD & result,
        const vector<BDD> *state_variables, bdd_parameters *para);
    static void print_transition(const BDD & result,
        const vector<BDD> *state_variables,
        const vector<BDD> *state_next_variables,
        const vector<BDD> *action_variables, bdd_parameters *para);
};

// Generalized non-deterministic Büchi automaton.
class generalized_automaton: public automaton {
  private:
    vector<BDD> fairness_constraints;
  public:
    generalized_automaton(const BDD & initial_state,
        const BDD & transition_relation, const vector<BDD> & state_variables,
        const vector<BDD> & state_next_variables,
        const vector<BDD> & action_variables,
        const vector<BDD> & fairness_constraints, bdd_parameters *para);
    const vector<BDD> & get_fairness_constraints() const;
    const BDD & get_formula() const;
};

// Intermediate non-deterministic Büchi automaton.
class intermediate_automaton: public generalized_automaton {
  private:
    BDD formula;
    bool auxiliary;
  public:
    intermediate_automaton(const BDD & initial_state,
        const BDD & transition_relation, const vector<BDD> & state_variables,
        const vector<BDD> & state_next_variables,
        const vector<BDD> & action_variables,
        const vector<BDD> & fairness_constraints, const BDD & formula,
        bool auxiliary, bdd_parameters *para);
    const BDD & get_formula() const;
    bool is_auxiliary() const;
    static intermediate_automaton product(const intermediate_automaton & a1,
        const intermediate_automaton & a2, const BDD & formula, bool auxiliary);
};

// Non-deterministic Büchi automaton (with a single acceptance condition).
class nondeterministic_automaton: public automaton {
  private:
    BDD fairness_constraint;
  public:
    nondeterministic_automaton(const BDD & initial_state,
        const BDD & transition_relation, const vector<BDD> & state_variables,
        const vector<BDD> & state_next_variables,
        const vector<BDD> & action_variables, const BDD & fairness_constraint,
        bdd_parameters *para);
    const BDD & get_fairness_constraint() const;
};

// Deterministic parity automaton.
class parity_automaton: public automaton {
  private:
    vector<BDD> colouring;
  protected:
    void print_colouring() const;
  public:
    parity_automaton(const BDD & initial_state, const BDD & transition_relation,
        const vector<BDD> & state_variables,
        const vector<BDD> & state_next_variables,
        const vector<BDD> & action_variables, const vector<BDD> & colouring,
        bdd_parameters *para);
    const vector<BDD> & get_colouring() const;
    virtual void print() const;
};

// Two-player arena.
class arena: public automaton {
  private:
    vector<BDD> inflated_variables;
    vector<BDD> inflated_next_variables;
    vector<BDD> inflated_counter;
    vector<BDD> inflated_counter_next;
    vector<vector<string> > action_names;
    vector<vector<BDD> > actions;
    vector<vector<BDD> > actions_next;
    vector<BDD> transition_actions;
    BDD existential_player;
  protected:
    void print_existential_player() const;
  public:
    arena(const BDD & initial_state, const BDD & transition_relation,
        const vector<BDD> & state_variables,
        const vector<BDD> & state_next_variables,
        const vector<BDD> & action_variables,
        const vector<BDD> & inflated_variables,
        const vector<BDD> & inflated_next_variables,
        const vector<BDD> & inflated_counter,
        const vector<BDD> & inflated_counter_next,
        const vector<vector<string> > action_names,
        const vector<vector<BDD> > actions,
        const vector<vector<BDD> > actions_next,
        const vector<BDD> transition_actions,
        const BDD & existential_player,
        bdd_parameters *para);
    const vector<BDD> & get_inflated_variables() const;
    const vector<BDD> & get_inflated_next_variables() const;
    const vector<BDD> & get_inflated_counter() const;
    const vector<BDD> & get_inflated_counter_next() const;
    const vector<vector<string> > & get_action_names() const;
    const vector<vector<BDD> > & get_actions() const;
    const vector<vector<BDD> > & get_actions_next() const;
    const vector<BDD> & get_transition_actions() const;
    const BDD & get_existential_player() const;
    virtual void print() const;
};

// Two-player parity game.
class game: public arena {
  private:
    vector<vector<BDD> > colourings;
    vector<BDD> sub_strategy_counter;
    vector<BDD> sub_strategy_counter_next;
    vector<BDD> extra_variables;
    vector<BDD> extra_next_variables;
  protected:
    void print_colourings() const;
  public:
    game(const BDD & initial_state, const BDD & transition_relation,
        const vector<BDD> & state, const vector<BDD> & state_next,
        const vector<BDD> & action_variables,
        const vector<BDD> & inflated_counter,
        const vector<BDD> & inflated_counter_next,
        const vector<vector<string> > action_names,
        const vector<vector<BDD> > actions,
        const vector<vector<BDD> > actions_next,
        const vector<BDD> transition_actions,
        const vector<BDD> & inflated_variables,
        const vector<BDD> & inflated_next_variables,
        const BDD & existential_player, const vector<vector<BDD> > & colourings,
        const vector<BDD> & sub_strategy_counter,
        const vector<BDD> & sub_strategy_counter_next,
        const vector<BDD> & extra_variables,
        const vector<BDD> & extra_next_variables,
        bdd_parameters *para);
    const vector<vector<BDD> > & get_colourings() const;
    const vector<BDD> & get_sub_strategy_counter() const;
    const vector<BDD> & get_sub_strategy_counter_next() const;
    const vector<BDD> & get_extra_variables() const;
    const vector<BDD> & get_extra_next_variables() const;
    virtual void print() const;
};

// Solution of a subformula.
class sl_solution {
  private:
    modal_formula formula;
    vector<quantifier> prefix;
    game parity_game;
    pair<BDD, BDD> winning_regions;
    void print_strategy(const vector<BDD> reachable_states, const BDD & state,
        unsigned int index, bdd_parameters *para) const;
    static unsigned int determine_state_index(const BDD & state,
        vector<BDD> & automaton_states, bdd_parameters *para);
  public:
    sl_solution(const modal_formula & formula,
        const vector<quantifier> & prefix, const game & parity_game,
        const pair<BDD, BDD> & winning_regions);
    const modal_formula & get_formula() const;
    const vector<quantifier> & get_prefix() const;
    const game & get_parity_game() const;
    const pair<BDD, BDD> & get_winning_regions() const;
    void print(const vector<BDD> reachable_states, bdd_parameters *para) const;
    void print_witness(const vector<BDD> reachable_states,
        bdd_parameters *para) const;
};

pair<BDD, list<sl_solution> > check_perfect_recall_formula(
    modal_formula *formula, bdd_parameters *para);
pair<modal_formula *, vector<quantifier> > process_prefix(
    modal_formula *formula);
pair<vector<parity_automaton>, list<sl_solution> > determinize_formula(
    modal_formula *formula, bdd_parameters *para);
list<modal_formula *> get_conjuncts(modal_formula *formula);
pair<generalized_automaton, list<sl_solution> > construct_generalized_automaton(
    modal_formula *formula, bdd_parameters *para);
pair<intermediate_automaton, list<sl_solution> >
    construct_intermediate_automaton(modal_formula *formula,
        bdd_parameters *para);
intermediate_automaton finalize_automaton(intermediate_automaton *automaton,
    bdd_parameters *para);
nondeterministic_automaton convert_automaton(generalized_automaton *automaton,
    bdd_parameters *para);
vector<BDD> calculate_reachable_states(nondeterministic_automaton *automaton,
    bdd_parameters *para);
vector<BDD> enumerate_states(const BDD & states, const vector<BDD> & variables,
    bdd_parameters *para);
parity_automaton determinize_automaton(nondeterministic_automaton *automaton,
    bdd_parameters *para);
arena construct_arena(vector<quantifier> *prefix, bdd_parameters *para);
game combine_game(vector<parity_automaton> *automata, arena *arena,
    vector<quantifier> *prefix, bdd_parameters *para);
pair<BDD, BDD> solve_game(game *game, bdd_parameters *para);
pair<BDD, BDD> deadend_regions(game *game, BDD world, bdd_parameters *para);
pair<BDD, BDD> winning_regions_simple(game *game, BDD world,
    bdd_parameters *para);
pair<BDD, BDD> winning_regions_separate(game *game, BDD world,
    bdd_parameters *para);
BDD calculate_attractor(game *game, BDD states, BDD world,
    bool existential_player, bdd_parameters *para);

BDD equivalent(const BDD & a, const BDD & b);
BDD equivalent_vectors(const vector<BDD> & a, const vector<BDD> & b,
    bdd_parameters *para);

#endif // ! SL_PERFECT_RECALL_HH
