#include "sl_perfect_recall.hh"


generalized_automaton::generalized_automaton(
    const BDD & initial_state, const BDD & transition_relation,
    const vector<BDD> & state_variables,
    const vector<BDD> & state_next_variables,
    const vector<BDD> & action_variables,
    const vector<BDD> & fairness_constraints, bdd_parameters *para):
    automaton(initial_state, transition_relation, state_variables,
        state_next_variables, action_variables, para),
    fairness_constraints(fairness_constraints)
{
}

const vector<BDD> &
generalized_automaton::get_fairness_constraints() const
{
  return fairness_constraints;
}
