#ifndef SL_IMPERFECT_RECALL_HH
#define SL_IMPERFECT_RECALL_HH
#include <algorithm>
#include <list>
#include <map>
#include <stack>
#include <vector>
#include "types.hh"
#include "cuddObj.hh"

using namespace std;

struct generating_thread_data_t
{
  Cudd *bddmgr;
  BDD current_state;
  vector<BDD>::iterator current_variable;
  vector<BDD>::iterator end_variable;
  list<BDD> *local_states;
  unsigned int thread_levels;
};

strategy build_strategy(string variable_name, modal_formula *subformula,
    bdd_parameters * para);
BDD calculate_valid_restrictions(vector<strategy_entry> *entries,
    bdd_parameters *para);
set<string> get_state_actions(basic_agent *agent, BDD state,
    bdd_parameters *para);
void merge_local_states(list<pair<BDD, set<string> > > *shared_local_states, 
    list<pair<BDD, set<string> > > *local_states, bdd_parameters *para);
vector<strategy_entry> generate_action_mapping(
    list<pair<BDD, set<string> > > *shared_local_states,
    vector<BDD> *bdd_variables, bdd_parameters *para);
pair<BDD, map<string, BDD> > convert_actions_to_bdds(set<string> *actions,
    vector<BDD> *bdd_variables, bdd_parameters *para);

void *generate_local_states_thread(void *arg);
void generate_local_states_recursive(Cudd *bddmgr, BDD current_state,
    vector<BDD>::iterator current_variable, vector<BDD>::iterator end_variable,
    list<BDD> *local_states, unsigned int thread_levels);
list<pair<BDD, set<string> > > generate_local_states(basic_agent *agent,
    bdd_parameters *para);

BDD check_SL_EXISTS(BDD p, strategy *s, bdd_parameters * para);
BDD check_SL_FORALL(BDD p, strategy *s, bdd_parameters * para);
BDD check_SL_X(BDD p, map<string, strategy *> *agents, bdd_parameters * para);
BDD check_SL_F(BDD p, map<string, strategy *> *agents, bdd_parameters * para);
BDD check_SL_G(BDD p, map<string, strategy *> *agents, bdd_parameters * para);
BDD check_SL_U(BDD p, BDD q, map<string, strategy *> *agents,
    bdd_parameters * para);

BDD SL_transition(map<string, strategy *> *agents, bdd_parameters *para);
BDD calculateTransition(bdd_parameters *para);
BDD calculateRestrictions(map<string, strategy *> *agents,
    bdd_parameters *para);

#endif // ! SL_IMPERFECT_RECALL_HH
