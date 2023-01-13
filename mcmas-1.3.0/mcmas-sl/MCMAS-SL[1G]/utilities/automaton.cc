#include "sl_perfect_recall.hh"


automaton::automaton(const BDD & initial_state, const BDD & transition_relation,
                     const vector<BDD> & state_variables,
                     const vector<BDD> & state_next_variables,
                     const vector<BDD> & action_variables,
                     bdd_parameters *para):
    initial_state(initial_state), transition_relation(transition_relation),
    state_variables(state_variables),
    state_next_variables(state_next_variables),
    action_variables(action_variables), para(para)
{
  assert(state_variables.size() == state_next_variables.size());

  BDD existential_transition_relation = Exists(para->bddmgr, &action_variables,
      transition_relation);
  reachable_states = initial_state;
  BDD tmp = para->bddmgr->bddOne();
  while (tmp != reachable_states) {
    tmp = reachable_states;
    reachable_states += Exists(para->bddmgr, &state_variables,
        existential_transition_relation * reachable_states)
            .SwapVariables(state_variables, state_next_variables);
  }

  // Optimize performance.
  this->transition_relation *= reachable_states;
}

const BDD &
automaton::get_initial_state() const
{
  return initial_state;
}

const BDD &
automaton::get_transition_relation() const
{
  return transition_relation;
}

const vector<BDD> &
automaton::get_state_variables() const
{
  return state_variables;
}

const vector<BDD> &
automaton::get_state_next_variables() const
{
  return state_next_variables;
}

const vector<BDD> &
automaton::get_action_variables() const
{
  return action_variables;
}

const BDD &
automaton::get_reachable_states() const
{
  return reachable_states;
}

bdd_parameters *
automaton::get_parameters() const
{
  return para;
}

BDD
automaton::swap_variables(const BDD & state) const
{
  return state.SwapVariables(get_state_variables(), get_state_next_variables());
}

void
automaton::print() const
{
  cout << "      Initial states:" << endl;
  print_state(get_initial_state(), &get_state_variables(), get_parameters());

  cout << "      Transition relation:" << endl;
  print_transition(get_transition_relation(), &get_state_variables(),
      &get_state_next_variables(), &get_action_variables(), get_parameters());

  cout << "      Reachable states:" << endl;
  print_state(get_reachable_states(), &get_state_variables(), get_parameters());
}

void
automaton::print_state(const BDD & result, const vector<BDD> *state_variables,
                       unsigned int state_index, bdd_parameters *para)
{
  if (result != para->bddmgr->bddZero()) {
    if (state_index == state_variables->size()) {
      cout << "        ";
      for (unsigned int j = 0; j < state_variables->size(); j++) {
        cout << ((result * (*state_variables)[j] == para->bddmgr->bddZero()) ?
            '0' : '1');
      }
      cout << endl;
    } else {
      print_state(result * !(*state_variables)[state_index], state_variables,
          state_index + 1, para);
      print_state(result * (*state_variables)[state_index], state_variables,
          state_index + 1, para);
    }
  }
}

void
automaton::print_transition(const BDD & result,
                            const vector<BDD> *state_variables,
                            const vector<BDD> *state_next_variables,
                            const vector<BDD> *action_variables,
                            unsigned int state_index,
                            unsigned int state_next_index,
                            unsigned int action_index, bdd_parameters *para)
{
  if (result != para->bddmgr->bddZero()) {
    if (state_index < state_variables->size()) {
      print_transition(result * !(*state_variables)[state_index],
          state_variables, state_next_variables, action_variables,
          state_index + 1, state_next_index, action_index, para);
      print_transition(result * (*state_variables)[state_index],
          state_variables, state_next_variables, action_variables,
          state_index + 1, state_next_index, action_index, para);
    } else {
      if (action_index < action_variables->size()) {
        print_transition(result * !(*action_variables)[action_index],
            state_variables, state_next_variables, action_variables,
            state_index, state_next_index, action_index + 1, para);
        print_transition(result * (*action_variables)[action_index],
            state_variables, state_next_variables, action_variables,
            state_index, state_next_index, action_index + 1, para);
      } else {
        if (state_next_index < state_next_variables->size()) {
          print_transition(result * !(*state_next_variables)[state_next_index],
              state_variables, state_next_variables, action_variables,
              state_index, state_next_index + 1, action_index, para);
          print_transition(result * (*state_next_variables)[state_next_index],
              state_variables, state_next_variables, action_variables,
              state_index, state_next_index + 1, action_index,  para);
        } else {
          cout << "        ";
          for (unsigned int i = 0; i < state_variables->size(); i++) {
            cout << ((result * (*state_variables)[i] ==
                para->bddmgr->bddZero()) ? '0' : '1');
          }
          cout << "--";
          for (unsigned int i = 0; i < action_variables->size(); i++) {
            cout << ((result * (*action_variables)[i] ==
                para->bddmgr->bddZero()) ? '0' : '1');
          }
          cout << "->";
          for (unsigned int i = 0; i < state_next_variables->size(); i++) {
            cout << ((result * (*state_next_variables)[i] ==
                para->bddmgr->bddZero()) ? '0' : '1');
          }
          cout << endl;
        }
      }
    }
  }
}

void
automaton::print_state(const BDD & result, const vector<BDD> *state_variables,
                       bdd_parameters *para)
{
  print_state(result, state_variables, 0, para);
}

void
automaton::print_transition(const BDD & result,
                            const vector<BDD> *state_variables,
                            const vector<BDD> *state_next_variables,
                            const vector<BDD> *action_variables,
                            bdd_parameters *para)
{
  print_transition(result, state_variables, state_next_variables,
      action_variables, 0, 0, 0, para);
}
