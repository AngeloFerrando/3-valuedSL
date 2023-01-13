#include "sl_perfect_recall.hh"


intermediate_automaton::intermediate_automaton(
    const BDD & initial_state, const BDD & transition_relation,
    const vector<BDD> & state_variables,
    const vector<BDD> & state_next_variables,
    const vector<BDD> & action_variables,
    const vector<BDD> & fairness_constraints, const BDD & formula,
    bool auxiliary, bdd_parameters *para):
    generalized_automaton(initial_state, transition_relation, state_variables,
        state_next_variables, action_variables, fairness_constraints, para),
    formula(formula), auxiliary(auxiliary)
{
}

const BDD &
intermediate_automaton::get_formula() const
{
  return formula;
}

bool
intermediate_automaton::is_auxiliary() const
{
  return auxiliary;
}

intermediate_automaton
intermediate_automaton::product(const intermediate_automaton & a1,
                                const intermediate_automaton & a2,
                                const BDD & formula, bool auxiliary)
{
  vector<BDD> state = a1.get_state_variables();
  state.insert(state.end(), a2.get_state_variables().begin(),
      a2.get_state_variables().end());

  vector<BDD> state_next = a1.get_state_next_variables();
  state_next.insert(state_next.end(), a2.get_state_next_variables().begin(),
      a2.get_state_next_variables().end());

  vector<BDD> fairness_constraints = a1.get_fairness_constraints();
  fairness_constraints.insert(fairness_constraints.end(),
      a2.get_fairness_constraints().begin(),
      a2.get_fairness_constraints().end());

  assert(a1.get_action_variables() == a2.get_action_variables());
  assert(a1.get_parameters() == a2.get_parameters());

  return intermediate_automaton(a1.get_initial_state() * a2.get_initial_state(),
      a1.get_transition_relation() * a2.get_transition_relation(),
      state, state_next, a1.get_action_variables(), fairness_constraints,
      formula, auxiliary, a1.get_parameters());
}
