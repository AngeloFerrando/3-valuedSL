#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>
#include <math.h>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include "types.hh"
using namespace std;
extern map< string, basic_agent * >*is_agents;
extern vector< basic_agent * >*agents;
extern map< string, bool_expression * >*is_evaluation;
extern bool_expression *is_istates;
extern map< string, set< string > >*is_groups;
extern vector< modal_formula > *is_formulae;
extern vector< fairness_expression * >*is_fairness;
extern map< string, int >options;
bool
global_consistency_check()
{
  basic_agent *is_environment = (*agents)[0];
  bool is_consistent = true;
  int count = 0;

  // create global variable table
  map< string, map< string, basictype * > >global_vars;
  map< string, basictype * >en_vars;
  map< string, basictype * >*enobsvars = is_environment->get_obsvars();
  map< string, basictype * >*envars = is_environment->get_vars();
  map< string, basictype * >::iterator m;
  en_vars.insert(enobsvars->begin(), enobsvars->end());
  en_vars.insert(envars->begin(), envars->end());
  pair < string, map< string, basictype * > >*a =
    new pair < string, map< string,
    basictype * > >(is_environment->get_name(), en_vars);
  global_vars.insert(*a);
  for (unsigned int i = 1; i < agents->size(); i++) {
    a =
      new pair < string, map< string,
      basictype * > >((*agents)[i]->get_name(), *((*agents)[i]->get_vars()));
    global_vars.insert(*a);
  }
  /*
   * collect enumerate values in observable variables
   */
  set< string > *obsenum = (*agents)[0]->get_obs_enum_values();

  /* 
   * Check consistency in Environment and other agents
   */
  for (unsigned int t = 0; t < agents->size(); t++) {
    basic_agent *agent = (*agents)[t];
    string agent_name = agent->get_name();
    if (options["verbosity"] > 9)
      cout << "Check agent " << agent_name << " ...... " << endl;
    if (t == 0) {

      // check if there is any variable defined in both vars and obsvars
      if (options["verbosity"] > 9)
        cout << "  checking redefined variables ... " << endl;
      for (map< string, basictype * >::iterator i = envars->begin();
           i != envars->end(); i++) {
        m = enobsvars->find(i->first);
        if (m != enobsvars->end()) {  // a variable is redefined.
          cout << "    error: variable " << m->first <<
            " has already been defined." << endl;
          is_consistent = false;
        }
      }
    }
    // check if a variable has been used as a enumerate value
    if (!agent->check_var_against_enum_values(obsenum))
      is_consistent = false;

    // check local observable variables
    if (options["verbosity"] > 4)
      cout << "  checking local observable variables ... " << endl;
    if (!agent->check_lobsvars(envars))
      is_consistent = false;

    // compute all observable variables for the agent
    map< string, basictype * >*obsvars = NULL;
    if (t > 0) {
      obsvars = new map< string, basictype * >;
      obsvars->insert(enobsvars->begin(), enobsvars->end());
      map< string, variable * >*lobsvars = agent->get_lobsvars();
      if (lobsvars != NULL && lobsvars->size() > 0) {
        map< string, basictype * >::iterator j;
        for (map< string, variable * >::iterator i = lobsvars->begin();
             i != lobsvars->end(); i++) {
          if (envars != NULL && (j = envars->find(i->first)) != envars->end())
            (*obsvars)[i->first] = j->second;
        }
      }
    }
    // check red states
    if (options["verbosity"] > 4)
      cout << "  checking red states ... " << endl;
    bool_expression *ag_red = agent->get_redstates();
    if (ag_red != NULL && !ag_red->check_var_and_value_flat(obsvars,
                                                            &(global_vars
                                                              [agent_name]),
                                                            agent_name,
                                                            is_agents))
      is_consistent = false;

    // check protocol
    if (options["verbosity"] > 4)
      cout << "  checking protocol ... " << endl;
    count = 0;
    vector< protocol_line * >*ag_prot = agent->get_protocol();
    set< string > *ag_act = agent->get_actions();
    for (vector< protocol_line * >::iterator i = ag_prot->begin();
         i != ag_prot->end(); i++) {
      if (options["verbosity"] > 4)
        cout << "    NO. " << ++count << " ... " << endl;
      set< string > *tmp_act = (*i)->get_actions();
      for (set< string >::iterator j = tmp_act->begin();
           j != tmp_act->end(); j++) {
        set< string >::iterator k = ag_act->find(*j);
        if (k == ag_act->end()) { // an action is undefined;
          cout << "      error: action " << *j << " is not defined." << endl;
          is_consistent = false;
        }
      }
      if (!((*i)->get_condition()->check_var_and_value_flat(obsvars,
                                                            &(global_vars
                                                              [agent_name]),
                                                            agent_name,
                                                            is_agents)))
        is_consistent = false;
    }

    // check evolution function
    if (options["verbosity"] > 4)
      cout << "  checking evolution function ..." << endl;
    count = 0;
    vector< evolution_line * >*ag_evol = agent->get_evolution();
    for (vector< evolution_line * >::iterator i = ag_evol->begin();
         i != ag_evol->end(); i++) {
      if (options["verbosity"] > 4)
        cout << "    NO. " << ++count << ":" << endl;
      if ((*i)->check_double_assignment())
        is_consistent = false;

      // check assignments (new states) 
      vector< assignment * >*va = (*i)->get_assignments();

      // check if there is only one assignment for smv style
      if (options["smv"] == 1 && va->size() > 1) {
        cout << "      only one assignment is allowed in smv style" << endl;
        is_consistent = false;
      }
      for (vector< assignment * >::iterator j = va->begin();
           j != va->end(); j++) {
        if (!
            ((*j)->check_var_and_value
             (enobsvars, &(global_vars[agent_name]))))
          is_consistent = false;
      }

      // check condition
      if (!((*i)->get_condition()->check_evolution_flat(obsvars,
                                                        &(global_vars
                                                          [agent_name]),
                                                        agent_name,
                                                        is_agents)))
        is_consistent = false;
    }
  }

  /* 
   * Check group definition
   */
  if (options["verbosity"] > 4)
    cout << endl << "Checking group definition ..." << endl;
  for (map< string, set< string > >::iterator i = is_groups->begin();
       i != is_groups->end(); i++) {
    if (options["verbosity"] > 4)
      cout << "  group " << (*i).first << " ..." << endl;
    for (set< string >::iterator j = (*i).second.begin();
         j != (*i).second.end(); j++) {
     if (is_agents->find(*j) == is_agents->end()) {
        is_consistent = false;
        cout << "    error: agent " << *j << " is not defined." << endl;
      }
    }
  }

  /* 
   * Check evaluation function
   */
  if (options["verbosity"] > 4)
    cout << endl << "Checking evaluation function ..." << endl;
  for (map< string, bool_expression * >::iterator i =
         is_evaluation->begin(); i != is_evaluation->end(); i++) {
    if (options["verbosity"] > 4)
      cout << "  atomic proposition " << (*i).first << " ..." << endl;
    if (!i->second->check_global_consistency_flat(&global_vars))
      is_consistent = false;
  }

  /*
   * add build-in atomic propositions: redstates and greenstates
   */
  for (unsigned int t = 0; t < agents->size(); t++) {
    basic_agent *agent = (*agents)[t];
    string agent_name = agent->get_name();
    bool_expression *ag_red = agent->get_redstates();
    bool_expression *ag_green;
    string redstates(agent_name + ".RedStates");
    string greenstates(agent_name + ".GreenStates");
    if (ag_red != NULL) {
      ag_green = new bool_expression(3, ag_red);
      pair < string, bool_expression * >a1(redstates, ag_red);
      pair < string, bool_expression * >a2(greenstates, ag_green);
      is_evaluation->insert(a1);
      is_evaluation->insert(a2);
    } else {
      ag_red = new bool_expression(6, NULL);
      ag_green = new bool_expression(5, NULL);
      pair < string, bool_expression * >a1(redstates, ag_red);
      pair < string, bool_expression * >a2(greenstates, ag_green);
      is_evaluation->insert(a1);
      is_evaluation->insert(a2);
    }
  }

  /* 
   * Check initstates
   */
  if (options["verbosity"] > 4)
    cout << endl << "Checking initial states ..." << endl;
  if (!is_istates->check_global_consistency_flat(&global_vars))
    is_consistent = false;

  cout << is_consistent << endl;

  /* 
   * Check fairness expression
   */
  if (options["verbosity"] > 4)
    cout << endl << "Checking fairness definition ..." << endl;
  count = 0;
  for (vector< fairness_expression * >::iterator i = is_fairness->begin();
       i != is_fairness->end(); i++) {
    if (options["verbosity"] > 4)
      cout << " fairness expression  " << ++count << " ... " << endl;
    if (!(*i)->check_atomic_proposition(0))
      is_consistent = false;
  }
  cout << is_consistent << endl;

  /* 
   * Check formulae
   */
  if (options["verbosity"] > 4)
    cout << endl << "Checking formula definition ..." << endl;
  count = 0;
  for (vector< modal_formula >::iterator i = is_formulae->begin();
       i != is_formulae->end(); i++) {
    if (options["verbosity"] > 4)
      cout << "  formula " << ++count << " ... " << endl;
    if (!(*i).check_atomic_proposition(0))
      is_consistent = false;
  }
  cout << is_consistent << endl;

  return is_consistent;
}
