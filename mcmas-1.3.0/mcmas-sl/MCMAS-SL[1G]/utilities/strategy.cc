#include "types.hh"
#include "utilities.hh"
#include <stack>

strategy_entry::strategy_entry(BDD state, BDD variables,
    map<string, BDD> actions): state(state), variables(variables),
    actions(actions)
{
}

strategy_entry::~strategy_entry()
{
}

BDD *
strategy_entry::get_state()
{
  return &state;
}

BDD *
strategy_entry::get_variables()
{
  return &variables;
}

map<string, BDD> *
strategy_entry::get_actions()
{
  return &actions;
}

strategy::strategy(vector<strategy_entry> action_mapping,
                   vector<BDD> bdd_variables,
                   set<basic_agent *> sharing_agents,
                   BDD valid_restrictions) {
  this->action_mapping = action_mapping;
  this->bdd_variables = bdd_variables;
  this->sharing_agents = sharing_agents;
  this->valid_restrictions = valid_restrictions;
}

strategy::~strategy()
{
}

vector<strategy_entry> *
strategy::get_action_mapping()
{
  return &action_mapping;
}

vector<BDD> *
strategy::get_bdd_variables()
{
  return &bdd_variables;
}

set<basic_agent *> *
strategy::get_sharing_agents()
{
  return &sharing_agents;
}

BDD *
strategy::get_valid_restrictions()
{
  return &valid_restrictions;
}

void
strategy::print_strategy(bdd_parameters * para, BDD *restricted_state)
{
  // Agent protocols.
  for (set<basic_agent *>::iterator i = sharing_agents.begin();
       i != sharing_agents.end(); i++) {
    basic_agent *agent = *i;
    cout << "Agent " << agent->get_name() << endl;

    // Collect all variables observable by the agent.
    vector<pair<string, basictype *> > variables;
    map<string, variable *> *lobsvars = agent->get_lobsvars();
    map<string, basictype *> *obsvars = (*agents)[0]->get_obsvars();
    map<string, basictype *> *vars = agent->get_vars();
    if (lobsvars != NULL) {
      for (map<string, variable *>::iterator i = lobsvars->begin();
           i != lobsvars->end(); i++) {
        variables.push_back(make_pair("Environment." + i->first,
                                      i->second->get_var_type()));
      }
    }
    if (obsvars != NULL) {
      for (map<string, basictype *>::iterator i = obsvars->begin();
           i != obsvars->end(); i++) {
        variables.push_back(make_pair("Environment." + i->first, i->second));
      }
    }
    if (vars != NULL) {
      copy(vars->begin(), vars->end(), back_inserter(variables));
    }

    /*for (vector<pair<string, basictype *> >::iterator i = variables.begin();
         i != variables.end(); i++) {
      cout << "  " << i->first << ": ";
      for (int j = 0; j < i->second->get_value_count(); j++) {
        if (j != 0) {
          cout << ", ";
        }
        cout << i->second->get_value(para->bddmgr, para->v, j).first;
      }
      cout << endl;
    }*/

    // Construct all possible observable states.
    stack<pair<BDD, int> > state_stack;
    vector<int> value_stack;
    state_stack.push(make_pair(para->bddmgr->bddOne(), 0));
    vector<pair<string, basictype *> >::iterator it = variables.begin();
    vector<pair<BDD, vector<int> > > local_states;

    while (true) {
      while (it != variables.end()) {
        BDD state = state_stack.top().first * it->second->get_value(
            para->bddmgr, para->v, 0).second * (*para->reach);
        state_stack.push(make_pair(state, it->second->get_value_count() - 1));
        value_stack.push_back(0);
        it++;
        if (state == para->bddmgr->bddZero()) {
          break;
        }
      }

      BDD current_state = state_stack.top().first;
      if (current_state != para->bddmgr->bddZero()) {
        local_states.push_back(make_pair(current_state, value_stack));
      }

      while (!state_stack.empty() && state_stack.top().second == 0) {
        state_stack.pop();
        value_stack.pop_back();
        it--;
      }

      if (!state_stack.empty()) {
        int remaining_indices = state_stack.top().second ;
        state_stack.pop();
        value_stack.pop_back();
        it--;

        basictype *type = it->second;
        int value_index = type->get_value_count() - remaining_indices;
        BDD state = state_stack.top().first * type->get_value(
            para->bddmgr, para->v, value_index).second * (*para->reach);
        state_stack.push(make_pair(state, remaining_indices - 1));
        value_stack.push_back(value_index);

        it++;
      } else {
        break;
      }
    }

    // Print observable states with associated actions
    for (vector<pair<BDD, vector<int> > >::iterator i = local_states.begin();
         i != local_states.end(); i++) {
      vector<int> *value_indices = &(i->second);
      BDD state = para->bddmgr->bddOne();

      cout << "  ";
      for (size_t j = 0; j < value_indices->size(); j++) {
        if (j != 0) {
          cout << ", ";
        }
        pair<string, basictype *> *variable = &variables[j];
        pair<string, BDD> value = variable->second->get_value(
            para->bddmgr, para->v, value_indices->at(j));
        cout << variable->first << "=" << value.first;
        state = state * value.second;
      }

      size_t j = 0;
      for (; j < action_mapping.size(); j++) {
        if (*action_mapping[j].get_state() * state != para->bddmgr->bddZero()) {
          break;
        }
      }
      if (j == action_mapping.size()) {
        cout << "No matching action mapping for the state" << endl;
        exit(1);
      }

      cout << " (" << j << "): ";

      map<string, BDD> *actions = action_mapping[j].get_actions();
      map<string, BDD>::iterator k = actions->begin();
      for (k = actions->begin(); k != actions->end(); k++) {
        if (k->second * (*restricted_state) != para->bddmgr->bddZero()) {
          break;
        }
      }
      if (k == actions->end()) {
        cout << "No matching action for the state" << endl;
        //exit(1);
      } else

      cout << k->first << endl;
    }
  }
}
