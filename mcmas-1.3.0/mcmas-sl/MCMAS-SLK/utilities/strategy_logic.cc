#include "utilities.hh"
#include "strategy_logic.hh"
#include "benchmark.hh"
#include <pthread.h>
#include "../cudd-2.5.0-exp/cudd/cuddInt.h"


strategy
build_strategy(string variable_name, modal_formula *subformula,
               bdd_parameters *para)
{
  BENCHMARK_START("build-strategy");

  if (options["verbosity"] > 4) {
    cout << "Building strategy '" << variable_name << "'" << endl;
  }
  vector<BDD> bdd_variables;

  // Generate shared local states and the associated available actions.
  list<pair<BDD, set<string> > > shared_local_states;
  set<basic_agent *> sharing_agents = subformula->get_sharing_agents(
      variable_name);
  for (set<basic_agent *>::iterator i = sharing_agents.begin();
       i != sharing_agents.end(); i++) {
    if (options["verbosity"] > 4) {
      cout << "Generating local states for agent '" << ((*i)->get_name())
           << "'" << endl;
    }
    list<pair<BDD, set<string> > > local_states = generate_local_states(*i,
        para);
    if (options["verbosity"] > 4) {
      cout << "Merging states (" << local_states.size() << ")" << endl;
    }
    BENCHMARK_START("merge-states");
    merge_local_states(&shared_local_states, &local_states, para);
    BENCHMARK_END();
    if (options["verbosity"] > 4) {
      cout << "Merged" << endl;
    }
  }

  if (options["verbosity"] > 4) {
    cout << "Generating entries" << endl;
  }

  BENCHMARK_START("assign-bdds");
  vector<strategy_entry> entries = generate_action_mapping(&shared_local_states,
      &bdd_variables, para);
  BENCHMARK_END();

  if (options["verbosity"] > 4) {
    cout << "Generated entries" << endl;
  }

  BENCHMARK_START("valid-restrictions");
  BDD valid_restrictions = calculate_valid_restrictions(&entries, para);
  BENCHMARK_END();

  strategy s(entries, bdd_variables, sharing_agents, valid_restrictions);

  BENCHMARK_END();

  return s;
}

BDD
calculate_valid_restrictions(vector<strategy_entry> *entries,
                             bdd_parameters *para)
{
  BDD valid_restrictions = para->bddmgr->bddOne();

  for (vector<strategy_entry>::iterator i = entries->begin();
       i != entries->end(); i++) {
    if (i->get_actions()->size() > 0) {
      BDD mapping_restriction = para->bddmgr->bddZero();
      for (map<string, BDD>::iterator j = i->get_actions()->begin();
           j != i->get_actions()->end(); j++) {
        mapping_restriction = mapping_restriction + j->second;
      }
      valid_restrictions = valid_restrictions * mapping_restriction;
    }
  }

  return valid_restrictions;
}

set<string>
get_state_actions(basic_agent *agent, BDD state, bdd_parameters *para)
{
  vector<protocol_line *> *protocol = agent->get_protocol();
  if (protocol->empty()) {
    return *(agent->get_actions());
  }

  set<string> actions;
  BDD null_action = para->bddmgr->bddOne();

  for (vector<protocol_line *>::iterator i = protocol->begin();
       i != protocol->end(); i++) {
    bool_expression *condition = (*i)->get_condition();
    BDD condition_bdd;
    if (condition->is_other_branch()) {
      condition_bdd = null_action;
    } else {
      condition_bdd = condition->encode_bdd_flat(para,
        para->bddmgr->bddOne());
      null_action = null_action * !condition_bdd;
    }

    if (condition_bdd * state == state) {
      set<string> *protocol_actions = (*i)->get_actions();
      actions.insert(protocol_actions->begin(), protocol_actions->end());
    }
  }

  return actions;
}

void
merge_local_states(list<pair<BDD, set<string> > > *shared_local_states, 
                   list<pair<BDD, set<string> > > *local_states,
                   bdd_parameters *para)
{
  // This avoids initial merging.
  if (local_states->size() > shared_local_states->size()) {
    list<pair<BDD, set<string> > > tmp = *shared_local_states;
    *shared_local_states = *local_states;
    *local_states = tmp;
  }

  for (list<pair<BDD, set<string> > >::iterator i = local_states->begin();
       i != local_states->end(); i++) {
    BDD local_bdd = i->first;
    set<string> local_actions = i->second;

    for (list<pair<BDD, set<string> > >::iterator j =
         shared_local_states->begin(); j != shared_local_states->end();) {
      BDD shared_bdd = j->first;
      set<string> shared_actions = j->second;

      if (local_bdd * shared_bdd != para->bddmgr->bddZero()) {
        local_bdd = local_bdd + shared_bdd;
        set<string> intersection;

        set_intersection(local_actions.begin(), local_actions.end(),
                         shared_actions.begin(), shared_actions.end(),
                         std::inserter(intersection, intersection.begin()));
        local_actions = intersection;
        j = shared_local_states->erase(j);
      } else {
        j++;
      }
    }

    shared_local_states->push_back(make_pair(local_bdd, local_actions));
  }
}

vector<strategy_entry>
generate_action_mapping(list<pair<BDD, set<string> > > *shared_local_states,
                        vector<BDD> *bdd_variables, bdd_parameters *para)
{
  vector<strategy_entry> action_mapping;
  action_mapping.reserve(shared_local_states->size());

  for (list<pair<BDD, set<string> > >::iterator i =
       shared_local_states->begin(); i != shared_local_states->end(); i++) {
    pair<BDD, map<string, BDD> > entry = convert_actions_to_bdds(&i->second,
        bdd_variables, para);
    action_mapping.push_back(strategy_entry(i->first, entry.first,
        entry.second));
  }

  return action_mapping;
}

pair<BDD, map<string, BDD> >
convert_actions_to_bdds(set<string> *actions, vector<BDD> *bdd_variables,
                        bdd_parameters *para)
{
  int action_count = actions->size();
  int variable_count =
      action_count <= 1 ? 0 : log_2((unsigned int) action_count);
  if (action_count == 0) {
    cout << "Warning: shared local state with no possible action." << endl;
  }

  map<string, BDD> bdds;
  BDD variables = para->bddmgr->bddOne();

  int binary_representation = 0;
  for (set<string>::iterator i = actions->begin(); i != actions->end(); i++) {
    BDD bdd = para->bddmgr->bddOne();
    for (int j = 0; j < variable_count; j++) {
      BDD variable = para->bddmgr->bddVar(next_bdd_variable + j);
      bdd_variables->push_back(variable);
      variables = variables * variable;
      if ((binary_representation >> j) & 1) {
        bdd = bdd * variable;
      } else {
        bdd = bdd * !variable;
      }
    }

    bdds.insert(make_pair(*i, bdd));
    binary_representation++;
  }
  next_bdd_variable += variable_count;

  return make_pair(variables, bdds);
}

void *
generate_local_states_thread(void *arg)
{
  generating_thread_data_t *data = (generating_thread_data_t *) arg;
  generate_local_states_recursive(
      data->bddmgr, data->current_state, data->current_variable,
      data->end_variable, data->local_states, data->thread_levels);
  return NULL;
}

void
generate_local_states_recursive(Cudd *bddmgr, BDD current_state,
                                vector<BDD>::iterator current_variable,
                                vector<BDD>::iterator end_variable,
                                list<BDD> *local_states,
                                unsigned int thread_levels)
{
  if (current_state != bddmgr->bddZero()) {
    if (current_variable == end_variable) {
      local_states->push_back(current_state);
    } else {
      BDD s1 = !(*current_variable) * current_state;
      BDD s2 = (*current_variable) * current_state;

      if (thread_levels > 0) {
        BENCHMARK_START("thread-setup");
        Cudd new_bddmgr = options["cachesize"] > CUDD_CACHE_SLOTS ?
            Cudd(states_count * 2 + actions_count, 0, CUDD_UNIQUE_SLOTS,
                 options["cachesize"], options["maxmem"], 0) :
            Cudd(states_count * 2 + actions_count, 0, CUDD_UNIQUE_SLOTS,
                 CUDD_CACHE_SLOTS, options["maxmem"], 0);
        Cudd_AutodynDisable(new_bddmgr.getManager());
        Cudd_ShuffleHeap(
            new_bddmgr.getManager(), bddmgr->getManager()->invperm);

        BDD new_s2 = s2.Transfer(new_bddmgr);
        list<BDD> new_local_states;
        vector<BDD> new_variables;
        new_variables.reserve(end_variable - current_variable - 1);
        for (vector<BDD>::iterator i = current_variable + 1; i != end_variable;
             i++) {
          new_variables.push_back(i->Transfer(new_bddmgr));
        }

        generating_thread_data_t data;
        data.bddmgr = &new_bddmgr;
        data.current_state = new_s2;
        data.current_variable = new_variables.begin();
        data.end_variable = new_variables.end();
        data.local_states = &new_local_states;
        data.thread_levels = thread_levels - 1;
        BENCHMARK_END();

        pthread_t thread;
        pthread_create(
            &thread, NULL, generate_local_states_thread, (void *) &data);
        generate_local_states_recursive(
            bddmgr, s1, current_variable + 1, end_variable, local_states,
            thread_levels - 1);
        pthread_join(thread, NULL);

        BENCHMARK_START("thread-merge");
        for (list<BDD>::iterator i = new_local_states.begin();
             i != new_local_states.end(); i++) {
          local_states->push_back(i->Transfer(*bddmgr));
        }
        BENCHMARK_END();
      } else {
        generate_local_states_recursive(
            bddmgr, s1, current_variable + 1, end_variable, local_states, 0);
        generate_local_states_recursive(
            bddmgr, s2, current_variable + 1, end_variable, local_states, 0);
      }
    }
  }
}

list<pair<BDD, set<string> > >
generate_local_states(basic_agent *agent, bdd_parameters *para)
{
  vector<BDD> visible_variables = agent->get_visible_variables(para->v);
  if (options["verbosity"] > 4) {
    cout << "Visible variables: " << visible_variables.size() << endl;
  }

  // Cudd_AutodynDisable(para->bddmgr->getManager());

  BENCHMARK_START("generate-states");
  list<BDD> raw_states;
  generate_local_states_recursive(
      para->bddmgr, *para->reach, visible_variables.begin(),
      visible_variables.end(), &raw_states, options["threadbranching"]);
  BENCHMARK_END();

  // Cudd_AutodynEnable(para->bddmgr->getManager(), CUDD_REORDER_SAME);

  if (options["verbosity"] > 4) {
    cout << "Local states: " << raw_states.size() << endl;
  }

  BENCHMARK_START("generate-actions");
  list<pair<BDD, set<string> > > local_states;
  for (list<BDD>::iterator i = raw_states.begin(); i != raw_states.end(); i++) {
    local_states.push_back(make_pair(*i, get_state_actions(agent, *i, para)));
  }
  BENCHMARK_END();

  return local_states;
}

BDD
check_SL_EXISTS(BDD p, strategy *s, bdd_parameters *para)
{
  vector<strategy_entry> *action_mapping = s->get_action_mapping();
  for (vector<strategy_entry>::iterator i = action_mapping->begin();
       i != action_mapping->end(); i++) {
    BDD restriction_bdd = para->bddmgr->bddZero();
    for (map<string, BDD>::iterator j = i->get_actions()->begin();
         j != i->get_actions()->end(); j++) {
      restriction_bdd = restriction_bdd + j->second;
    }
    p = (p * restriction_bdd).ExistAbstract(*i->get_variables());
  }

  return p;
}

BDD
check_SL_FORALL(BDD p, strategy *s, bdd_parameters *para)
{
  return !check_SL_EXISTS(!p, s, para);
}

BDD
check_SL_X(BDD p, map<string, strategy *> *agents, bdd_parameters *para)
{
  // Swap the current and next state variables.
  BDD result = p.SwapVariables(*para->v, *para->pv);

  // Compute the preimage.
  if (options["nobddcache"] == 0) {
    if (para->calReachRT) {
      para->reachRT = new BDD(calculateTransition(para));
      para->calReachRT = false;
    }
    result = result * (*para->reachRT);
  } else {
    result = result * calculateTransition(para);
  }

  // Abstract away the next state.
  result = Exists(para->bddmgr, para->pv, result);

  // Apply the SL restrictions.
  if (options["nobddcache"] == 0) {
    if (para->calRestrictSL) {
      para->restrictSL = new BDD(calculateRestrictions(agents, para));
      para->calRestrictSL = false;
    }
    result = result * (*para->restrictSL);
  } else {
    result = result * calculateRestrictions(agents, para);
  }

  // Abstract away the joint action.
  result = Exists(para->bddmgr, para->a, result);

  return result * (*para->reach);
}

BDD
check_SL_F(BDD p, map<string, strategy *> *agents, bdd_parameters *para)
{
  return check_SL_U(para->bddmgr->bddOne(), p, agents, para);
}

BDD
check_SL_G(BDD p, map<string, strategy *> *agents, bdd_parameters *para)
{
  return !check_SL_F(!p, agents, para);
}

BDD
check_SL_U(BDD p, BDD q, map<string, strategy *> *agents, bdd_parameters *para)
{
  BDD result = q;
  BDD tmp = para->bddmgr->bddZero();

  while (result != tmp) {
    tmp = result;
    result = result + p * check_SL_X(result, agents, para);
  }

  return result;
}

BDD
SL_transition(map<string, strategy *> *agents, bdd_parameters *para)
{
  BDD result = para->bddmgr->bddOne();

  // Compute the preimage.
  if (options["nobddcache"] == 0) {
    if (para->calReachRT) {
      para->reachRT = new BDD(calculateTransition(para));
      para->calReachRT = false;
    }
    result = result * (*para->reachRT);
  } else {
    result = result * calculateTransition(para);
  }

  // Apply the SL restrictions.
  if (options["nobddcache"] == 0) {
    if (para->calRestrictSL) {
      para->restrictSL = new BDD(calculateRestrictions(agents, para));
      para->calRestrictSL = false;
    }
    result = result * (*para->restrictSL);
  } else {
    result = result * calculateRestrictions(agents, para);
  }

  return result;
}

BDD
calculateTransition(bdd_parameters *para)
{
  BDD transition = *para->reach;

  for (unsigned int i = 0; i < agents->size(); i++) {
    transition *= (*para->vRT)[i];
  }

  return transition;
}

BDD
calculateRestrictions(map<string, strategy *> *agents, bdd_parameters *para)
{
  BDD restriction = para->bddmgr->bddOne();

  for (map<string, strategy *>::iterator i = agents->begin();
       i != agents->end(); i++) {
    basic_agent *agent = is_agents->find(i->first)->second;
    vector<strategy_entry> *action_mapping = i->second->get_action_mapping();

    BDD agent_restriction = para->bddmgr->bddZero();

    for (vector<strategy_entry>::iterator j = action_mapping->begin();
         j != action_mapping->end(); j++) {
      for (map<string, BDD>::iterator k = j->get_actions()->begin();
           k != j->get_actions()->end(); k++) {
        BDD agent_action = agent->encode_action(para, k->first);
        agent_restriction =
            agent_restriction + (*j->get_state()) * agent_action * k->second;
      }
    }

    restriction *= agent_restriction;
  }

  return restriction;
}
