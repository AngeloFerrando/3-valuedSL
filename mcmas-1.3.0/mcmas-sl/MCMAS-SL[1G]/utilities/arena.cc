#include "sl_perfect_recall.hh"


arena::arena(const BDD & initial_state, const BDD & transition_relation,
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
             const BDD & existential_player, bdd_parameters *para):
    automaton(initial_state, transition_relation, state_variables,
        state_next_variables, action_variables, para),
    inflated_variables(inflated_variables),
    inflated_next_variables(inflated_next_variables),
    inflated_counter(inflated_counter),
    inflated_counter_next(inflated_counter_next),
    action_names(action_names), actions(actions), actions_next(actions_next),
    transition_actions(transition_actions),
    existential_player(existential_player)
{
  assert(inflated_counter.size() == inflated_counter_next.size());
  assert(inflated_variables.size() == inflated_next_variables.size());
  assert(inflated_counter.size() == inflated_counter_next.size());
  assert(action_names.size() == actions.size());
  assert(actions.size() == actions_next.size());
  for (unsigned int i = 0; i < actions.size(); i++) {
    assert(action_names[i].size() == actions[i].size());
    assert(actions[i].size() == actions_next[i].size());
  }
}

const vector<BDD> &
arena::get_inflated_variables() const
{
  return inflated_variables;
}

const vector<BDD> &
arena::get_inflated_next_variables() const
{
  return inflated_next_variables;
}

const vector<BDD> &
arena::get_inflated_counter() const
{
  return inflated_counter;
}

const vector<BDD> &
arena::get_inflated_counter_next() const
{
  return inflated_counter_next;
}

const vector<vector<string> > &
arena::get_action_names() const
{
  return action_names;
}

const vector<vector<BDD> > &
arena::get_actions() const
{
  return actions;
}

const vector<vector<BDD> > &
arena::get_actions_next() const
{
  return actions_next;
}

const vector<BDD> &
arena::get_transition_actions() const
{
  return transition_actions;
}

const BDD &
arena::get_existential_player() const
{
  return existential_player;
}

void
arena::print_existential_player() const
{
  cout << "      Existential player:" << endl;
  print_state(get_reachable_states() * get_existential_player(),
      &get_state_variables(), get_parameters());

  cout << "      Universal player:" << endl;
  print_state(get_reachable_states() * !get_existential_player(),
      &get_state_variables(), get_parameters());
}

void
arena::print() const
{
  automaton::print();
  print_existential_player();
}
