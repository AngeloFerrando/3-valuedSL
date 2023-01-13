#include "sl_perfect_recall.hh"


game::game(const BDD & initial_state, const BDD & transition_relation,
           const vector<BDD> & state_variables,
           const vector<BDD> & state_next_variables,
           const vector<BDD> & action_variables,
           const vector<BDD> & inflated_counter,
           const vector<BDD> & inflated_counter_next,
           const vector<vector<string> > action_names,
           const vector<vector<BDD> > actions,
           const vector<vector<BDD> > actions_next,
           const vector<BDD> transition_actions,
           const vector<BDD> & inflated_variables,
           const vector<BDD> & inflated_next_variables,
           const BDD & existential_player,
           const vector<vector<BDD> > & colourings,
           const vector<BDD> & sub_strategy_counter,
           const vector<BDD> & sub_strategy_counter_next,
           const vector<BDD> & extra_variables,
           const vector<BDD> & extra_next_variables,
           bdd_parameters *para):
    arena(initial_state, transition_relation, state_variables,
        state_next_variables, action_variables, inflated_variables,
        inflated_next_variables, inflated_counter, inflated_counter_next,
        action_names, actions, actions_next, transition_actions,
        existential_player, para),
    colourings(colourings), sub_strategy_counter(sub_strategy_counter),
    sub_strategy_counter_next(sub_strategy_counter_next),
    extra_variables(extra_variables), extra_next_variables(extra_next_variables)
{
  assert(extra_variables.size() == extra_next_variables.size());
  assert(colourings.size() > 0);
  for (unsigned int i = 0; i < colourings.size(); i++) {
    assert(colourings[i].size() > 0);
  }

  // Optimize performance.
  for (unsigned int i = 0; i < this->colourings.size(); i++) {
    for (unsigned int j = 0; j < this->colourings[i].size(); j++) {
      this->colourings[i][j] *= get_reachable_states();
    }
  }
}

const vector<vector<BDD> > &
game::get_colourings() const
{
  return colourings;
}

const vector<BDD> &
game::get_sub_strategy_counter() const
{
  return sub_strategy_counter;
}

const vector<BDD> &
game::get_sub_strategy_counter_next() const
{
  return sub_strategy_counter_next;
}

const vector<BDD> &
game::get_extra_variables() const
{
  return extra_variables;
}

const vector<BDD> &
game::get_extra_next_variables() const
{
  return extra_next_variables;
}

void
game::print_colourings() const
{
  for (unsigned int i = 0; i < get_colourings().size(); i++) {
    cout << "      Colouring " << (i + 1) << "/" << get_colourings().size()
        << endl;
    for (unsigned int j = 0; j < get_colourings()[i].size(); j++) {
      cout << "      Colour " << j << ":" << endl;
      print_state(get_colourings()[i][j], &get_state_variables(),
          get_parameters());
    }
  }
}

void
game::print() const
{
  arena::print();
  print_colourings();
}
