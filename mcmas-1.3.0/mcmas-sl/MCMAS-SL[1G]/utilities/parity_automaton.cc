#include "sl_perfect_recall.hh"


parity_automaton::parity_automaton(
    const BDD & initial_state, const BDD & transition_relation,
    const vector<BDD> & state_variables,
    const vector<BDD> & state_next_variables,
    const vector<BDD> & action_variables, const vector<BDD> &colouring,
    bdd_parameters *para):
    automaton(initial_state, transition_relation, state_variables,
        state_next_variables, action_variables, para),
    colouring(colouring)
{
  assert(colouring.size() > 0);

  // Optimize performance.
  for (unsigned int i = 0; i < this->colouring.size(); i++) {
    this->colouring[i] *= get_reachable_states();
  }
}

const vector<BDD> &
parity_automaton::get_colouring() const
{
  return colouring;
}

void
parity_automaton::print_colouring() const
{
  for (unsigned int i = 0; i < get_colouring().size(); i++) {
    cout << "      Colour " << i << ":" << endl;
    print_state(get_colouring()[i], &get_state_variables(), get_parameters());
  }
}

void
parity_automaton::print() const
{
  automaton::print();
  print_colouring();
}
