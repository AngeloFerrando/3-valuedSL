#include "sl_perfect_recall.hh"


nondeterministic_automaton::nondeterministic_automaton(
    const BDD & initial_state, const BDD & transition_relation,
    const vector<BDD> & state_variables,
    const vector<BDD> & state_next_variables,
    const vector<BDD> & action_variables, const BDD & fairness_constraint,
    bdd_parameters *para):
    automaton(initial_state, transition_relation, state_variables,
        state_next_variables, action_variables, para),
    fairness_constraint(fairness_constraint)
{
}

const BDD &
nondeterministic_automaton::get_fairness_constraint() const
{
  return fairness_constraint;
}
