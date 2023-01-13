/* ************************************************************************
 *            MCMAS-SL -- Model Checker for Multi-Agent Systems
 *
 *     Copyright (C) 2007, 2008, 2009, 2010, 2011
 *     Hongyang Qu and Franco Raimondi and Alessio Lomuscio
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 * 
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 *   For AAAI2015 submission purposes the authors of the package are here
 *   taken from the original MCMAS package. Copyright of MCMAS-SL rests with
 *   the anonymous authors. The package is provided as open-source under the
 *   same terms of MCMAS.
 *
 **************************************************************************/

#define URL "http://vas.doc.ic.ac.uk/tools/mcmas/"

#include <unistd.h>
//#include <sys/syscall.h>
#include <sys/types.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>
#include <signal.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <cctype>
#include <ctime>
#include "types.hh"
#include "utilities.hh"
#include "mcmas-driver.hh"
#include "cuddObj.hh"
#include <sys/timeb.h>
#include "benchmark.hh"
#include "sl_perfect_recall.hh"

using namespace std;

vector< string * >*string_table;
vector< bool_expression * >*logic_expression_table;
vector< bool_expression * >*logic_expression_table1;
vector< variable * >*variable_table;
map< string, basic_agent * >*is_agents;
vector< basic_agent * >*agents;
map< string, bool_expression * >*is_evaluation;
bool_expression *is_istates = NULL;
map< string, set< string > >*is_groups;
vector< modal_formula > *is_formulae;
vector< modal_formula > *is_perfect_recall_formulae;
vector< fairness_expression * >*is_fairness;
int obsvars_bdd_length;
int envars_bdd_length;
// A map to store global options, e.g. verbosity, etc.
map< string, int >options;
string cex_prefix;    // Destination directory for counterexamples
int scount;     // a global counter for counterexamples.
int states_count = 0;
int actions_count = 0;
unsigned int next_bdd_variable = 0;
Cudd_ReorderingType REORDERING = CUDD_REORDER_GROUP_SIFT_CONV;
bdd_parameters * parameters; /* copy of the single parameters for the signal handler */

bool global_consistency_check();
void exec_simulation(void *ptr);
void *compute_partial_state_space( void *ptr );
void allocate_bdd_variables(vector<BDD> *v, vector<ADD> *addv, 
                            vector<BDD> *pv, vector<ADD> *addpv,
                            vector<BDD> *a, Cudd *bddmgr);
BDD compute_reach(BDD in_st, vector<BDD> *v, vector<BDD> *pv, 
                  vector<BDD> *a, vector<BDD> *vRT, Cudd *bddmgr,
                  unsigned int *acounter1, int id, unsigned long *threadmem);
bool read_options(int argc, char *argv[]);
void print_help(void);

void
mcmas_signal_handler(int signal)
{
  /* using cerr here seems to disagree with Linux */
	
  fprintf(stderr, "\nCaught signal ");
  switch (signal)	{
	case SIGINT:
    fprintf(stderr, "SIGINT\n");
    break;
  case SIGPIPE:
    fprintf(stderr, "SIGPIPE\n");
    break;
  case SIGABRT:
    fprintf(stderr, "SIGABRT\n");
    break;
  case SIGTERM:
    fprintf(stderr, "SIGTERM\n");
    break;
  default:
    fprintf(stderr, "SIG OTHER\n");
    break;
  }

  /* check if we have bdd_stats */
  if (options["bdd_stats"] == 1) {
    /* check if we have a single BDD parameter and a bddmgr */
    if (parameters && (parameters->bddmgr))	{
      parameters->bddmgr->info(); /* print the current bdd stats */
    }
  }
  exit(signal);
}

void
print_banner(void)
{
  cout <<
    "************************************************************************"
       << endl;
  cout << "                       MCMAS-SL v1.1.0 " << endl << endl;
  cout << " This software comes with ABSOLUTELY NO WARRANTY, to the extent"
       << endl;
  cout << " permitted by applicable law. " << endl << endl;
  cout << " Please check "  << URL;
  cout << " for the latest release.\n Please send any feedback to <mcmas@imperial.ac.uk>"
       << endl;
  cout <<
    "************************************************************************"
       << endl << endl;
}

void
print_state(BDD state, vector<BDD> v)
{
  for (unsigned int i = 0; i < agents->size(); i++) {
    cout << "Agent " << (*agents)[i]->get_name() << endl;
    (*agents)[i]->print_state("  ", state, v);
  }
}

string
state_to_str(BDD state, vector<BDD> v)
{
  ostringstream s;

  for (unsigned int i = 0; i < agents->size(); i++) {
    s << "  Agent " << (*agents)[i]->get_name() << "\n";
    s << (*agents)[i]->state_to_str(state, v);

  }
  return s.str();
}

bool
find_same_state(map< string, int >*statehash, string state)
{
  if (statehash != NULL) {
    map< string, int >::iterator iter = statehash->find(state);
    if (iter != statehash->end()) {
      return true;
    }
  }
  return false;
}

bool
is_valid_state(BDD state, vector<BDD> v)
{
  for (unsigned int i = 0; i < agents->size(); i++) {
    if (!(*agents)[i]->is_valid_state(state, v))
      return false;
  }
  return true;
}

void
print_action(BDD state, vector<BDD> a)
{
  for (unsigned int i = 0; i < agents->size(); i++) {
    cout << (*agents)[i]->get_name() << " : ";
    (*agents)[i]->print_action(state, a);
    if (i < agents->size() - 1)
      cout << "; ";
    else
      cout << endl;
  }
}

void
print_action_1(BDD state, vector<BDD> a)
{
  for (unsigned int i = 0; i < agents->size(); i++) {
    cout << (*agents)[i]->get_name() << " : ";
    (*agents)[i]->print_action(state, a);
    cout << "; ";
  }
  cout << endl;
}

bool
is_valid_action(BDD state, vector<BDD> a)
{
  for (unsigned int i = 0; i < agents->size(); i++) {
    if (!(*agents)[i]->is_valid_action(state, a))
      return false;
  }
  return true;
}

BDD
append_variable_BDDs(Cudd * bddmgr, vector<BDD> * v, BDD a)
{
  for (unsigned int j = 0; j < agents->size(); j++) {
    map< string, basictype * >*obsvars = (*agents)[j]->get_obsvars();
    if (obsvars != NULL && obsvars->size() > 0)
      for (map< string, basictype * >::iterator i =
             obsvars->begin(); i != obsvars->end(); i++)
        a *= i->second->build_all_BDDs(bddmgr, v);
    map< string, basictype * >*vars = (*agents)[j]->get_vars();
    if (vars != NULL && vars->size() > 0)
      for (map< string, basictype * >::iterator i = vars->begin();
           i != vars->end(); i++)
        a *= i->second->build_all_BDDs(bddmgr, v);
  }
  return a;
}

BDD
append_variable_BDD(Cudd * bddmgr, vector<BDD> * v, BDD a, int j)
{
  map< string, basictype * >*obsvars = (*agents)[j]->get_obsvars();
  if (obsvars != NULL && obsvars->size() > 0)
    for (map< string, basictype * >::iterator i = obsvars->begin();
         i != obsvars->end(); i++)
      a *= i->second->build_all_BDDs(bddmgr, v);
  map< string, basictype * >*vars = (*agents)[j]->get_vars();
  if (vars != NULL && vars->size() > 0)
    for (map< string, basictype * >::iterator i = vars->begin();
         i != vars->end(); i++)
      a *= i->second->build_all_BDDs(bddmgr, v);
  return a;
}

void 
produce_witness(bdd_parameters *para, BDD state, string name) {
  vector< BDD * > S;
  int n = 0;
  BDD q = state;
  BDD p;
  BDD sum = q;
  do {
    q = check_EX(q, para) - sum;
    S.push_back(new BDD(q));
    sum += q;
    p = q * *(para->in_st);
    n++;
  } while (p == para->bddmgr->bddZero());
  
  p = p.PickOneMinterm(*para->v);
  vector< BDD *> tmpresult;
  vector< BDD * > tmptrans;
  tmpresult.push_back(new BDD(p));
  for(int k=(int)S.size()-2; k>=0; k--) {
    for (unsigned int i = 0; i < agents->size(); i++)
      p = p * (*para->vRT)[i];
    p = p.SwapVariables(*para->v, *para->pv);
    p = Exists(para->bddmgr, para->a, p);
    p = Exists(para->bddmgr, para->pv, p);
    p = p * (*(S[k]));
    p = p.PickOneMinterm(*para->v);
    tmpresult.push_back(new BDD(p));
  }
  tmpresult.push_back(new BDD(state));
  
  for (unsigned int i = 0; i < tmpresult.size() - 1; i++) {
    BDD to = (tmpresult[i + 1])->SwapVariables(*para->v, *para->pv);
    BDD actions = timesTrans(tmpresult[i], &to, para->vRT);
    actions = Exists(para->bddmgr, para->v, actions);
    actions = Exists(para->bddmgr, para->pv, actions);
    BDD action = actions.PickOneMinterm(*para->a);
    tmptrans.push_back(new BDD(action));
  }
  
  if (options["cex"] == 1 || options["cex"] == 3) {
    cout << "Below is a witness execution leading to the state: " << endl;
    for (unsigned int k = 0; k<tmpresult.size(); k++) {
      cout << "------------- State: " << k+1 << " -----------------" << endl;
      print_state(*tmpresult[k], *para->v);
      cout << "----------------------------------------" << endl;
    } 
  } 
  if (options["cex"] == 2 || options["cex"] == 3) {
    string filename = cex_prefix + name + ".dot";
    string filename2 = cex_prefix + name + ".info";
    ofstream myfile(filename.c_str());
    ofstream myfile2(filename2.c_str());
    
    if (myfile.is_open() && myfile2.is_open()) {
      myfile << "digraph " << name << " {\n";
      
      // print states and their description
      for (unsigned int k = 0; k<tmpresult.size(); k++) {
        myfile << " " << k << " [label=\"" << k << "\",shape=ellipse]" << endl;
        myfile2 << "-- State " << k << " --" << endl;
        myfile2 << state_to_str(*tmpresult[k], *para->v) << endl;
      }
      for (unsigned int k = 0; k<tmptrans.size(); k++) {
        myfile << "    " << k << " -> " << k+1 << "[label=\"<";
        for (unsigned int i = 0; i < agents->size(); i++) {
          string act_str = (*agents)[i]->action_to_str(*tmptrans[k], *para->a);
          if (act_str != "") {
            myfile << act_str;
            if (!(i == agents->size() - 1)) {
              myfile << ";";
            }
          }
        }
  
        myfile << ">\"]" << endl;
      }
      myfile << "}\n";
      
      myfile.close();
      myfile2.close();
    } else {
      if(options["quiet"] == 0) 
        cout << "Unable to open file " << filename;
    }
  }

  for(unsigned int i=0; i<S.size(); i++) 
    delete S[i];
  for(unsigned int i=0; i<tmpresult.size(); i++) 
    delete tmpresult[i];
  for(unsigned int i=0; i<tmptrans.size(); i++) 
    delete tmptrans[i];
}

void free_mcmas_memory(bdd_parameters *para) {
  for(unsigned int i=0; i<agents->size(); i++)
    delete (*agents)[i];
  delete agents;
  delete is_agents;
  for(map<string, bool_expression *>::iterator it = is_evaluation->begin(); it != is_evaluation->end(); it++) {
    if((it->first).compare("_init") != 0 || it->second->get_op() != 0)
      delete it->second;
  }
  delete is_evaluation;
  delete is_groups;
  delete is_perfect_recall_formulae;
  for(unsigned int i=0; i<is_fairness->size(); i++) {
    (*is_fairness)[i]->delete_bdd_representation(para);
    delete (*is_fairness)[i];
  }
  delete is_fairness;
  for(unsigned int i=0; i<logic_expression_table->size(); i++) {
    logic_expression *tmp = (logic_expression *)((*logic_expression_table)[i]->get_operand(0));
    delete (*logic_expression_table)[i];
    delete tmp;
  }
  delete logic_expression_table;
  for(unsigned int i=0; i<logic_expression_table1->size(); i++) {
    logic_expression *tmp = (logic_expression *)((*logic_expression_table1)[i]->get_operand(0));
    delete (*logic_expression_table1)[i];  
    delete tmp;
  }
  delete logic_expression_table1;
  for(unsigned int i=0; i<string_table->size(); i++) {
    delete (*string_table)[i];
  }
  delete string_table;
  for(unsigned int i=0; i<variable_table->size(); i++)
    delete (*variable_table)[i];
  delete variable_table;
}

void free_cudd_memory(bdd_parameters *para) {
  delete(para->v);
  delete(para->pv);
  delete(para->a);
  delete(para->addv);
  delete(para->addpv);
  delete(para->vevol);
  delete(para->vprot);
  delete(para->vRT);
  delete(para->in_st);
  delete(para->reach);
  for(map<string, BDD>::iterator it = para->BDD_cache->begin(); it != para->BDD_cache->end(); it++)
    it->second = para->bddmgr->bddZero(); 
  delete para->BDD_cache;
  for(map<string, ADD>::iterator it = para->ADD_cache->begin(); it != para->ADD_cache->end(); it++)
    it->second = para->bddmgr->addZero(); 
  delete para->ADD_cache;
  if(para->reachRT) 
    delete para->reachRT;
  delete para->bddmgr;
  delete para;
}

void clear_cex(vector< vector< int >*>* countex, map< int, BDD * >* idbdd, 
               vector< vector< transition * >*>* cextr) {
  for(unsigned int i=0; i<countex->size(); i++)
    delete (*countex)[i];
  countex->clear();
  for(unsigned int i=0; i<cextr->size(); i++) {
    for(unsigned int j=0; j<(*cextr)[i]->size(); j++)
      delete (*(*cextr)[i])[j];
    delete (*cextr)[i];
  }
  cextr->clear();
  for(map<int, BDD *>::iterator it = idbdd->begin(); it != idbdd->end(); it++) {
    delete it->second;  
  }
  idbdd->clear();
}

void delete_cex(vector< vector< int >*>* countex, map< int, BDD * >* idbdd, 
                vector< vector< transition * >*>* cextr) {
  //clear_cex(countex, idbdd, cextr);
  delete countex;
  delete idbdd;
  delete cextr;
}

void print_strategy(string variable_name, strategy *s, BDD *restricted_state,
                    bdd_parameters *para)
{
  // Strategy label.
  stringstream label_stream;
  set<basic_agent *> *sharing_agents = s->get_sharing_agents();
  label_stream << "--- Strategy " << variable_name << " [";
  for (set<basic_agent *>::iterator i = sharing_agents->begin();
       i != sharing_agents->end(); i++) {
    if (i != sharing_agents->begin()) {
      label_stream << ", ";
    }
    label_stream << (*i)->get_name();
  }
  label_stream << "] ---";
  string label = label_stream.str();
  int extra_length = max(0, 40 - (int) label.size());
  cout << string(extra_length / 2, '-') << label;
  cout << string(extra_length - extra_length / 2, '-') << endl;

  // Strategy.
  s->print_strategy(para, restricted_state);

  // Separator.
  cout << string(40, '-') << endl;
}

void
print_reachable_states(const vector<BDD> & reachable_states,
                       bdd_parameters *para)
{
  for (unsigned int i = 0; i < reachable_states.size(); i++) {
    cout << "    g" << i << ":";
    bool is_first = true;

    for (unsigned int a = 0; a < agents->size(); a++) {
      const string &agent_name = (*agents)[a]->get_name();

      const map<string, basictype *> *obsvars = (*agents)[a]->get_obsvars();
      if (obsvars != NULL) {
        for (map<string, basictype *>::const_iterator it = obsvars->begin();
             it != obsvars->end(); it++) {
          if (is_first) {
            is_first = false;
          } else {
            cout << ",";
          }
          cout << " " << agent_name << "." <<
              it->second->state_to_str(reachable_states[i], *para->v);
        }
      }

      const map<string, basictype *> *vars = (*agents)[a]->get_vars();
      if (vars != NULL) {
        for (map<string, basictype *>::const_iterator it = vars->begin();
             it != vars->end(); it++) {
          if (is_first) {
            is_first = false;
          } else {
            cout << ",";
          }
          cout << " " << agent_name << "." <<
              it->second->state_to_str(reachable_states[i], *para->v);
        }
      }
    }

    if (reachable_states[i] * *para->in_st != para->bddmgr->bddZero()) {
      cout << " (initial)";
    }

    cout << endl;
  }
}

int
main(int argc, char *argv[])
{
  BENCHMARK_INIT();

  struct timeb tmb;
  ftime(&tmb);

  struct sigaction sigact;
  sigact.sa_handler = mcmas_signal_handler;
  sigemptyset(&sigact.sa_mask);
  sigact.sa_flags = 0;

  /* signals we want to catch */
  sigaction(SIGINT, &sigact, 0); /* interrupt */
  sigaction(SIGPIPE, &sigact, 0); /* broken pipe, used for timeouts */
  sigaction(SIGABRT, &sigact, 0); /* abort */
  sigaction(SIGTERM, &sigact, 0); /* term, debatable if we can actually catch this */

  unsigned long threadmem = 0;
  std::string filename;
  string s;
  mcmas_driver driver;

  if (argc < 2) {
    print_banner();
    print_help();
    exit(1);
  }

  cex_prefix = "";

  if (read_options(argc, argv))
    exit(1);

  if (options["quiet"] == 0) {
    print_banner();
    cout << "Command line:";
    for(int i = 0; i < argc; i++) {
      cout << " " << argv[i];
    }
    cout << endl << endl;
  }

  is_agents = new map< string, basic_agent * >;
  agents = new vector< basic_agent * >;
  is_evaluation = new map< string, bool_expression * >;
  is_groups = new map< string, set< string > >;
  is_formulae = new vector< modal_formula >;
  is_perfect_recall_formulae = new vector< modal_formula >;
  is_fairness = new vector< fairness_expression * >;

  string_table = new vector< string * >;
  string_table->push_back(new string("Environment"));
  logic_expression_table = new vector< bool_expression * >;
  logic_expression_table1 = new vector< bool_expression * >;
  variable_table = new vector< variable * >;
  
  filename = argv[argc - 1];
  driver.parse(filename);
  if (!driver.syntax_error) {
    if (options["quiet"] == 0 || options["simulation"] == 0)
      cout << filename << " has been parsed successfully." << endl;
    if (options["quiet"] == 0 || options["simulation"] == 0)
      cout << "Global syntax checking..." << endl;
    if (!global_consistency_check()) {
      cout << filename << " has error(s)." << endl;
      free_mcmas_memory(NULL);
      exit(-1);
    }
    if (options["quiet"] == 0)
      cout << "Done" << endl;
  } else {
    cout << filename << " has syntax error(s)." << endl;
    free_mcmas_memory(NULL);
    exit(-1);
  }

  if (options["verbosity"] > 2) {
    cout << "Done" << endl;
  }

  if (options["simulation"] == 0 || options["quiet"] == 0)
    cout << "Encoding BDD parameters..." << endl;

  // Calculate the number of BDD variables for states and actions
  for (unsigned int i = 0; i < agents->size(); i++) {
    states_count += (*agents)[i]->state_BDD_length();
    actions_count += (*agents)[i]->actions_BDD_length();
  }

  // Calculate the position of every variable and every set of actions
  int k1 = 0;
  int k2 = 0;
  for (unsigned int i = 0; i < agents->size(); i++) {
    k1 = (*agents)[i]->allocate_BDD_2_variables(k1);
    k2 = (*agents)[i]->allocate_BDD_2_actions(k2);
  }

  if (options["verbosity"] > 0) {
    cout << endl << "  Building BDDs variables...";
  }

  Cudd *bddmgr = options["cachesize"] > CUDD_CACHE_SLOTS ?
    new Cudd(states_count * 2 + actions_count, 0, CUDD_UNIQUE_SLOTS, options["cachesize"], options["maxmem"], 0) :  // The manager
    new Cudd(states_count * 2 + actions_count, 0, CUDD_UNIQUE_SLOTS, CUDD_CACHE_SLOTS, options["maxmem"], 0);  // The manager
  next_bdd_variable = states_count * 2 + actions_count;
  vector<BDD> *v;
  vector<ADD> *addv;
  vector<BDD> *pv;
  vector<ADD> *addpv;
  vector<BDD> *a;
  vector<BDD> *vevol, *vprot, *vRT;

  v = new vector<BDD>;  // Local states
  addv = new vector<ADD>;
  pv = new vector<BDD>; // "Next" local states
  addpv = new vector<ADD>;
  a = new vector<BDD>; // Actions

  // Allocate BDD variables to states and actions
  allocate_bdd_variables(v, addv, pv, addpv, a, bddmgr);

  if (options["verbosity"] > 0) {
    cout << "Done: " << v->size() << " for local states, " << a->
      size() << " for actions." << endl;
  }

  obsvars_bdd_length = (*agents)[0]->obsvars_BDD_length();
  envars_bdd_length = (*agents)[0]->get_var_index_end() + 1;

  vprot = new vector<BDD>;
  vevol = new vector<BDD>;
  vRT = new vector<BDD>;

  bdd_parameters *para = new bdd_parameters;
  parameters = para; /* for the signal handler */
  para->bddmgr = bddmgr;
  para->istates = is_istates;
  para->vRT = vRT;
  para->vevol = vevol;
  para->vprot = vprot;
  para->num_of_agents = agents->size();
  para->id = 0;
  para->v = v;
  para->pv = pv;
  para->addv = addv;
  para->addpv = addpv;
  para->a = a;
  para->reachRT = NULL;
  para->calReachRT = true;
  para->restrictSL = NULL;
  para->calRestrictSL = true;
  para->BDD_cache = new map< string, BDD > ();
  para->ADD_cache = new map< string, ADD > ();
  if(options["nomerge"] == 1) {
    para->merge = 0;
    para->vec_in_st = new vector<BDD*>;
    para->vec_reach = new vector<BDD*>;
    para->vec_formula = new vector<BDD*>;
    para->vec_reachRT = new vector<BDD*>;
    para->vec_istates = new vector<bool_expression*>;
  } else
    para->merge = 1;

  if (options["simulation"] == 1)
    exec_simulation(para);
  else {
    BDD in_st = bddmgr->bddOne();
    BDD reach, fair_reach;

    // REORDERING OF VARIABLES:
    //Cudd_ReorderingType REORDERING = CUDD_REORDER_GROUP_SIFT_CONV;
    if (options["dao"] == 0 || options["dao"] >= 2) // 1: all disable
      Cudd_AutodynEnable(bddmgr->getManager(), REORDERING);
    
    if (options["quiet"] == 0 || options["simulation"] == 0) {
      cout << "Building partial transition relation..." << endl;
    }
    for (unsigned int i = 0; i < agents->size(); i++) {
      if (options["verbosity"] > 0) {
        if (i == 0)
          cout << endl;
        cout << "      Processing " << (*agents)[i]->get_name() <<
          ": protocol... ";
        cout.flush();
      }
			struct timeb tmptmb0;
			ftime(&tmptmb0);
      para->vprot->push_back((*agents)[i]->encode_protocol(para));
      if (options["verbosity"] > 0) {
        cout << "done, evolution...";
        cout.flush();
      }
      if (options["smv"] == 0)
        para->vevol->push_back((*agents)[i]->encode_evolution(para));
      else
        para->vevol->push_back((*agents)[i]->encode_evolution_smv(para));
      if (options["verbosity"] > 0) {
        cout << "done, local transition relation...";
        cout.flush();
      }
			para->vRT->push_back((*para->vprot)[i] * (*para->vevol)[i]);
			struct timeb tmptmb1;
			ftime(&tmptmb1);
      if (options["verbosity"] > 0) {
        cout << "done. " << ((tmptmb1.time-tmptmb0.time) + (tmptmb1.millitm-tmptmb0.millitm)/1000.0) << " seconds" << endl;
      }
    }
    if (options["verbosity"] > 2)
      cout << "Done" << endl;
    if (options["quiet"] == 0 || options["simulation"] == 0) {
      cout << "Building BDD for initial states..." << endl;
    }
    in_st = is_istates->encode_bdd_flat(para, bddmgr->bddOne());
    in_st = append_variable_BDDs(bddmgr, v, in_st);
    if (options["verbosity"] > 2)
      cout << "Done." << endl;
    
    para->in_st = new BDD(in_st);
    
    REORDERING = CUDD_REORDER_GROUP_SIFT;
    if (options["dao"] == 0 || options["dao"] == 3) // 1: all disable, 2: after transition relation, 3: after reachable states
      Cudd_AutodynEnable(bddmgr->getManager(), REORDERING);
    else
      Cudd_AutodynDisable(bddmgr->getManager());
    
    if (options["quiet"] == 0 || options["simulation"] == 0) {
      cout << "Building reachable state space..." << endl;
    }
    unsigned int acounter1 = 1;

    BENCHMARK_START("reachability");
    reach = compute_reach(
        in_st, v, pv, a, vRT, bddmgr, &acounter1, 1, &threadmem);
    BENCHMARK_END();
    
    //time_t t2 = time(0);  
    para->reach = new BDD(reach);

    if (options["dao"] > 0) // 1: all disable, 2: after transition relation, 3: after reachable states
      Cudd_AutodynDisable(bddmgr->getManager());

    if (options["verbosity"] > 2)
      cout << "Done." << endl;

    // Check deadlock of the model
    if(options["deadlock"] == 1) {
      BDD ex = check_EX(para->bddmgr->bddOne(), para);
      bool satisfaction = ex == reach;

      if(satisfaction) {
        if(options["quiet"] == 0) 
          cout << "There is no deadlock state in the model!" << endl;
      } else {  
        BDD diff = reach - ex;
        BDD state = diff.PickOneMinterm(*para->v);
      
        if(options["quiet"] == 0) {
          cout << "Attention: there are deadlock states in the model!" << endl;
          cout << "The following state does not have any successors." << endl;
          print_state(state, *para->v);
          cout << "----------------------------------------" << endl;
        }
  
        if(options["cex"] > 0) 
          produce_witness(para, state, "deadlock");   
      }
    }
  
    // Check arithmetic overflow in the model
    if (options["overflow"] == 1) {
      BDD state;
      bool flag = false;
      BDD rc = reach;
      unsigned int i, j=0;
      for(i=0; i<agents->size(); i++)
        rc *= (*para->vprot)[i];
      for(i=0; i<agents->size(); i++) {
        vector< evolution_line * >* evolution = (*agents)[i]->get_evolution();
        for(j=0; j<evolution->size(); j++) {
          BDD bddevline = (*evolution)[j]->encode_bdd_overflow(para);
          bddevline *= rc;
          if(bddevline != para->bddmgr->bddZero()) {
            state = bddevline.PickOneMinterm(*para->v);
            flag = true;
            break;
          }
        }
        if(flag)
          break;
      }
      if(flag) {
        if(options["quiet"] == 0) {
          cout << "Evolution item " << j+1 << " in Agent " << (*agents)[i]->get_name()
               << " can cause overflow in the following state: " << endl;
          print_state(state, *para->v);
          cout << "----------------------------------------" << endl;
        }
        if(options["cex"] > 0) 
          produce_witness(para, state, "overflow");
      }
    }


    if (options["quiet"] == 0)
      cout << "Checking formulae..." << endl;

    string str = "_init";
    (*is_evaluation)[str] = is_istates;
    modal_formula *init = new modal_formula(new atomic_proposition(&str));

    if (!is_fairness->empty()) {
      if (options["quiet"] == 0 || options["simulation"] == 0)
        cout << "Building set of fair states..." << endl;
      for (vector< fairness_expression * >::iterator i =
             is_fairness->begin(); i != is_fairness->end(); i++) {
        BDD fairset = (*i)->check_formula(para);
        (*i)->set_bdd_representation(fairset);
      }
      // This is a set of "fair" states (the beginning of a fair computation)
      fair_reach = check_EG_fair(para->bddmgr->bddOne(), para);
      delete para->reach;
      para->reach = new BDD(fair_reach);
      in_st *= fair_reach;
    }       // end if
    (*para->BDD_cache)["_init"] = in_st;
    
    vector< vector< int >*> *countex = new vector< vector< int >*>;
    map< int, BDD * > *idbdd = new map< int, BDD * >;
    vector< vector< transition * >*> *cextr = new vector< vector< transition * >*>;

    if (options["quiet"] == 0 || options["simulation"] == 0)
      cout << "Verifying imperfect recall properties..." << endl;
    
    // Check if fair_reach is empty bdd
    if (!is_fairness->empty() && fair_reach == bddmgr->bddZero()) {
      if (options["quiet"] == 0)
        cout << "  Warning: ";
      cout << "The fairness constraint does not hold in any paths." << endl;
    }

    char buff[20];
    for (unsigned int i = 0; i < is_formulae->size(); i++) {
      set< string > trans_set;
      scount = 0;
      bool satisfaction = false;
      modal_formula f(4, init, &((*is_formulae)[i]));
      BDD result;

      BENCHMARK_START(concat("ir_check", i + 1));
      result = f.check_formula(para);
      BENCHMARK_END();

      satisfaction = result == *para->reach;
      if (options["quiet"] == 0)
        cout << "  Formula number " << i+1 << ": " <<
          (*is_formulae)[i].to_string() << ", is " << (satisfaction ?
                                                       "TRUE" : "FALSE")
             << " in the model" << endl;
      else
        cout << (satisfaction ? "TRUE" : "FALSE") << endl;
    
      if ((options["cex"] >= 1)) {
        // Computing counterexample / witness
        BDD *is = new BDD(in_st);
      
        scount = 0;
      
        modal_formula *g = (*is_formulae)[i].push_negations(0);
        
        string str_head;
        bool done = false;
        bool hascex = false;
        map<string, pair<strategy, BDD> > strategies;

        if ((satisfaction) && !(g->is_NoCTL()) && (g->is_ECTLK_new())) {
          // True and ECTLK: can print witness
          hascex = true;
          str_head = "witness";
  
          if (options["quiet"] == 0)
            cout << "  The following is a witness for the formula: " << endl;
  
          while ((*is) != bddmgr->bddZero()) {
            BDD curinitstate = is->PickOneMinterm(*v);
    
            if (is_valid_state(curinitstate, *v)) {
              bool cexresult = g->build_cex(
                  &curinitstate, 0, para, countex, idbdd, cextr, &strategies);
              if (cexresult) {
                done = true;
                break;
              } else {
                *is = *is - curinitstate;
                scount = 0;
                clear_cex(countex, idbdd, cextr);
              }
            }
          }
        } else if (!satisfaction) {
          // False and ACTLK: can print counterexample
          if (options["quiet"] == 0)
            cout <<
              "  The following is a counterexample for the formula: " << endl;
          hascex = true;
          str_head = "counterexample";
  
          *is = *is - result;
          if(g->is_ACTLK_new()) {
            // Negation of the formula:
            modal_formula fcex1(3, g);
            modal_formula *fcex = fcex1.push_negations(0);
            //cout << "fcex = " << fcex->to_string() << endl;
            while (*is != bddmgr->bddZero()) {
              BDD curinitstate = is->PickOneMinterm(*v);
              //print_state(curinitstate, *v);

              if (is_valid_state(curinitstate, *v)) {
                bool cexresult = fcex->build_cex(
                    &curinitstate, 0, para, countex, idbdd, cextr, &strategies);
                if (cexresult) {
                  done = true;
                  break;
                } else {
                  *is = *is - curinitstate;
                  scount = 0;
                  clear_cex(countex, idbdd, cextr);
                }
              }
            }
 						if(fcex != &fcex1)
							delete fcex;
          } else {
            done = true;
            BDD init_state = is->PickOneMinterm(*v);
            idbdd->insert(pair < int, BDD * >(0, new BDD(init_state)));
            vector< int >desc;    
            desc.push_back(0);
            countex->push_back(new vector< int >(desc));  
          }
        } else if (satisfaction) {
          if (options["quiet"] == 0)
            cout <<
              "    -- Sorry it is not possible to compute witnesses for non-ECTLK formulae"
                 << endl;
        } 
  
        if(hascex) {
          if (!done) {
            if (options["quiet"] == 0) {
              cout <<
                "A " << str_head << " exists but could not be generated." << endl;
            }
          } else {
            if (options["cex"] == 1 || options["cex"] == 3) {
              for (int ac = 0; ac < (int) countex->size(); ac++) {
                cout << "   < ";
                for (int j = 0; j < (int) countex->at(ac)->size(); j++) {
                  cout << countex->at(ac)->at(j) << " ";
                }
                cout << "> " << endl;
              }
      
              cout << "  States description: " << endl;
              for (map< int, BDD * >::iterator iter =
                     idbdd->begin(); iter != idbdd->end(); iter++) {
        
                cout << "------------- State: " << iter->first << " -----------------" << endl;
                print_state(*iter->second, *v);
                cout << "----------------------------------------" << endl;
              }

              if (strategies.size() > 0) {
                cout << "  Strategies: " << endl;
                for (map<string, pair<strategy, BDD> >::iterator iter =
                      strategies.begin(); iter != strategies.end(); iter++) {
                  print_strategy(iter->first, &(iter->second.first),
                                 &(iter->second.second), para);
                }
              }
            }
            if (options["cex"] == 2 || options["cex"] == 3) {
              // Writing full witness/counterexample to text file
              sprintf(buff, "formula%1d.dot", i + 1);
              string filename = cex_prefix + buff;
              sprintf(buff, "formula%1d.info", i + 1);
              string filename2 = cex_prefix + buff;
              ofstream myfile(filename.c_str());
              ofstream myfile2(filename2.c_str());
      
              if (myfile.is_open() && myfile2.is_open()) {
                myfile << "digraph " << str_head << i << " {\n";
        
                // print states and their description
                for (map< int, BDD * >::iterator iter =
                       idbdd->begin(); iter != idbdd->end(); iter++) {
                  myfile << " " << iter->first << " [label=\"" <<
                    iter->first << "\",shape=ellipse]" << endl;
                  myfile2 << "-- State " << iter->first << " --" << endl;
                  myfile2 << state_to_str(*iter->second, *v) << endl;
                }
        
                // printing transitions
                for (int ac = 0; ac < (int) cextr->size(); ac++) {
                  for (int j = 0; j < (int) cextr->at(ac)->size(); j++) {
                    string strTran = cextr->at(ac)->at(j)->index_to_string(a);
                    if (trans_set.find(strTran) == trans_set.end()) {
                      cextr->at(ac)->at(j)->to_str(&myfile, a);
                      trans_set.insert(strTran);
                    }
                  }
                }
        
                myfile << "}\n";
        
                myfile.close();
                myfile2.close();
              } else
                cout << "Unable to open file";
            }
            clear_cex(countex, idbdd, cextr);
          }
        } 
        delete is;
        delete g;
      }
    }
    if (options["quiet"] == 0) {
      cout << "done, " << is_formulae->size() <<
        " imperfect recall formulae successfully read and checked" << endl;
    }

    if (is_perfect_recall_formulae->size() > 0) {
      if (options["quiet"] == 0) {
        cout << "Verifying perfect recall properties..." << endl;
      }

      vector<BDD> reachable_states;
      if (options["cex"] > 0 || options["solutions"] > 0) {
        cout << "  Global reachable states:" << endl;
        reachable_states = enumerate_states(*para->reach, *para->v, para);
        print_reachable_states(reachable_states, para);
      }

      for (unsigned int i = 0; i < is_perfect_recall_formulae->size(); i++) {
        modal_formula &f = (*is_perfect_recall_formulae)[i];

        BENCHMARK_START(concat("pr_check", i + 1));
        pair<BDD, list<sl_solution> > result = check_perfect_recall_formula(&f,
            para);
        BENCHMARK_END();

        bool satisfied = result.first * (*para->in_st) == *para->in_st;
        cout << "  Formula number " << (i + 1) << ": " << f.to_string()
            << ", is " << (satisfied ? "TRUE" : "FALSE") << " in the model"
            << endl;

        if (options["cex"] > 0 || options["solutions"] > 0) {
          vector<sl_solution> solutions(result.second.begin(),
              result.second.end());

          // Witness/counterexample strategies.
          if (options["cex"] > 0) {
            for (unsigned int i = 0; i < solutions.size(); i++) {
              cout << "  " << (solutions[i].get_prefix()[1].is_existential() ?
                      "Witness" : "Counterexample")
                  << " " << (i + 1) << "/" << solutions.size()
                  << " (" << solutions[i].get_formula().to_string() << "):"
                  << endl;
              solutions[i].print_witness(reachable_states, para);
            }
          }

          // Full solutions.
          if (options["solutions"] > 0) {
            for (unsigned int i = 0; i < solutions.size(); i++) {
              cout << "  Solution " << (i + 1) << "/" << solutions.size()
                  << " (" << solutions[i].get_formula().to_string() << "):"
                  << endl;
              solutions[i].print(reachable_states, para);
            }
          }
        }
      }

      if (options["quiet"] == 0) {
        cout << "done, " << is_perfect_recall_formulae->size() <<
          " perfect recall formulae successfully read and checked" << endl;
      }
    }

    struct timeb tmb1;
    ftime(&tmb1);
    cout << "execution time = " << ((tmb1.time-tmb.time) + (tmb1.millitm-tmb.millitm)/1000.0) << endl;
    double reachablestates = reach.CountMinterm(v->size());
    cout << "number of reachable states = " << reachablestates << endl;
    unsigned long memoryinuse = bddmgr->ReadMemoryInUse();
    memoryinuse = (memoryinuse < threadmem) ? threadmem : memoryinuse;
    cout << "BDD memory in use = " << memoryinuse << endl;
    if (options["bdd_stats"] == 1) {
      bddmgr->info();
    }
    delete init;
    //delete_cex(countex, idbdd, cextr);
    in_st = reach = para->bddmgr->bddZero();
    if(!is_fairness->empty())
      fair_reach = para->bddmgr->bddZero();
  }
 clearmemory:
  free_mcmas_memory(para);
  free_cudd_memory(para);
}
