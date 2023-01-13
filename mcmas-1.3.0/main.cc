/* ************************************************************************
 *            MCMAS -- Model Checker for Multi-Agent Systems
 *
 *     Copyright (C) 2007-2017
 *     Hongyang Qu and Franco Raimondi and Alessio Lomuscio and Jeremy Kong
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
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <cctype>
#include <ctime>
#include "types.hh"
#include "utilities.hh"
#include "atlk.hh"
#include "mcmas-driver.hh"
#include "cuddObj.hh"
#include <sys/timeb.h>

using namespace std;

vector< string * >*string_table;
vector< bool_expression * >*logic_expression_table;
vector< bool_expression * >*logic_expression_table1;
vector< variable * >*variable_table;
map< string, basic_agent * >*is_agents;
map< string, int >*is_agents_index;
vector< basic_agent * >*agents;
map< string, bool_expression * >*is_evaluation;
bool_expression *is_istates = NULL;
map< string, set< string > >*is_groups;
vector< modal_formula > *is_formulae;
vector< fairness_expression * >*is_fairness;
int obsvars_bdd_length;
int envars_bdd_length;
// A map to store global options, e.g. verbosity, etc.
map< string, int >options;
string cex_prefix;    // Destination directory for counterexamples
int scount;     // a global counter for counterexamples.
int states_count = 0;
int actions_count = 0;
Cudd_ReorderingType REORDERING = CUDD_REORDER_GROUP_SIFT; //CUDD_REORDER_GROUP_SIFT_CONV;
bdd_parameters * parameters; /* copy of the single parameters for the signal handler */

bool force_atlk = false;
vector< vector< BDD* >* >* uniform_prots = NULL;
bool *satisfied = NULL;
unsigned int num_of_satisfied = 0;
double reachablestates = 0;
unsigned int num_of_strategies = 0;
string ufgroup_name = "";

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
void mcmas_signal_handler(int signal);
void print_state(BDD state, vector<BDD> v);
void print_states(BDD states, vector<BDD> v, Cudd* bddmgr);
string state_to_str(BDD state, vector<BDD> v);
bool find_same_state(map< string, int >*statehash, string state);
bool is_valid_state(BDD state, vector<BDD> v);
void print_action(BDD state, vector<BDD> a);
void print_action_1(BDD state, vector<BDD> a);
bool is_valid_action(BDD state, vector<BDD> a);
BDD append_variable_BDDs(Cudd * bddmgr, vector<BDD> * v, BDD a);
BDD append_variable_BDD(Cudd * bddmgr, vector<BDD> * v, BDD a, int j);
void produce_witness(bdd_parameters *para, BDD state, string name);
void free_mcmas_memory(bdd_parameters *para);
void free_cudd_memory(bdd_parameters *para);
void clear_cex(vector< vector< int >*>* countex, map< int, BDD * >* idbdd, vector< vector< transition * >*>* cextr);
void delete_cex(vector< vector< int >*>* countex, map< int, BDD * >* idbdd, vector< vector< transition * >*>* cextr);
void do_model_checking(bdd_parameters * para);

void
print_banner(void)
{
  cout <<
    "************************************************************************"
       << endl;
  cout << "                       MCMAS v1.3.0 " << endl << endl;
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

int
main(int argc, char *argv[])
{
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
  is_agents_index = new map< string, int >;
  agents = new vector< basic_agent * >;
  is_evaluation = new map< string, bool_expression * >;
  is_groups = new map< string, set< string > >;
  is_formulae = new vector< modal_formula >;
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

  // change atlk=0 to atlk=1 if there are fairness constraints
  if(options["ATLsemantics"] == 0 && !force_atlk && !is_fairness->empty())
    options["ATLsemantics"] = 1;
  // disable atl counterexample if there are fairness constraints or atlk > 0
  if(options["ATLsemantics"] > 0 || !is_fairness->empty())
    options["atlcex"] = 0;
  // override ATLsemantics when uniform is set
  if(options["uniform"] == 1) {
    options["atlcex"] = 0;
    // temporally disable cex generation until it is fixed
    //options["cex"] = 0; 
    if(options["ATLsemantics"] == 0 && !force_atlk && !is_fairness->empty())
      options["ATLsemantics"] = 1;
    options["nobddcache"] = 1;
    // check if the name of the group used to split protocols is set properly
    if(!ufgroup_name.empty()) {
      //check if the name is defined
      if(is_groups == NULL || is_groups->find(ufgroup_name) == is_groups->end()) {
        cout << "Group name " << ufgroup_name << " is not defined." << endl;
        free_mcmas_memory(NULL);
        exit(-1);
      }
    }
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
    cout.flush();
  }

  Cudd *bddmgr = options["cachesize"] > CUDD_CACHE_SLOTS ?
    new Cudd(states_count * 2 + actions_count, 0, CUDD_UNIQUE_SLOTS, options["cachesize"], options["maxmem"], 0) :  // The manager
    new Cudd(states_count * 2 + actions_count, 0, CUDD_UNIQUE_SLOTS, CUDD_CACHE_SLOTS, options["maxmem"], 0);  // The manager
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
  para->reach = NULL;
  para->reachRT = NULL;
  para->fair_gamma_FO = NULL;
  para->nfair_gamma_FO = NULL;
  para->calReachRT = true;  
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
    BDD reach;

    // REORDERING OF VARIABLES:
    //Cudd_ReorderingType REORDERING = CUDD_REORDER_GROUP_SIFT_CONV;
    if (options["dao"] == 0 || options["dao"] >= 2) // 1: all disable
      Cudd_AutodynEnable(bddmgr->getManager(), REORDERING);
    
    if (options["quiet"] == 0 || options["simulation"] == 0) {
      cout << "Building partial transition relation..." << endl;
    }
    struct timeb t0, t1;
    if (options["quiet"] == 0 && options["verbosity"] > 1)
      ftime(&t0);

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
      (*is_agents_index)[(*agents)[i]->get_name()] = i;
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
    if (options["quiet"] == 0 && options["verbosity"] > 1) {
      ftime(&t1);
      cout << "It took " << ((t1.time-t0.time) + (t1.millitm-t0.millitm)/1000.0) << " seconds to encode transition relation." << endl;
    }
    
    // build uniform protocol
    if(options["uniform"] == 1) {
      if (options["quiet"] == 0 && options["verbosity"] > 0)
        cout << "Building uniform protocols..." << endl;
      // compute individual BDD for each integer
      build_integer_BDDs(para);
      build_enumerate_BDDs(para);
      uniform_prots = new vector< vector< BDD* >* >;
      set< string > ufg;
      if(!ufgroup_name.empty())
        ufg = is_groups->find(ufgroup_name)->second;
      for(unsigned int x=0; x<agents->size(); x++) {
        if (options["quiet"] == 0 /*&& options["verbosity"] > 0*/) {
          cout << "  processing protocol in agent " << (*agents)[x]->get_name() << "...";
          cout.flush();
        }
        basic_agent* agent = (*agents)[x];
        vector< BDD* >* uni_prot;
        if(!ufgroup_name.empty() && ufg.find(agent->get_name()) == ufg.end()) {
          uni_prot = new vector< BDD* >();
          uni_prot->push_back(new BDD((*para->vprot)[x]));
        } else
          uni_prot= agent->split_protocol((*para->vprot)[x], para);
        uniform_prots->push_back(uni_prot);
        if (options["quiet"] == 0 /*&& options["verbosity"] > 0*/)
          cout << " done: " << uni_prot->size() << " uniform protocols" << endl;
      }
    }
    
    if (options["quiet"] == 0 || options["simulation"] == 0) {
      cout << "Building BDD for initial states..." << endl;
    }
    if (options["quiet"] == 0 && options["verbosity"] > 1)
      ftime(&t0);
    in_st = is_istates->encode_bdd_flat(para, bddmgr->bddOne());
    in_st = append_variable_BDDs(bddmgr, v, in_st);
    if (options["verbosity"] > 2)
      cout << "Done." << endl;
    if (options["quiet"] == 0 && options["verbosity"] > 1) {
      ftime(&t1);
      cout << "It took " << ((t1.time-t0.time) + (t1.millitm-t0.millitm)/1000.0) << " seconds to encode initial states." << endl;
    }
    
    para->in_st = new BDD(in_st);
    
    REORDERING = CUDD_REORDER_GROUP_SIFT;
    if (options["dao"] == 0 || options["dao"] == 3) // 1: all disable, 2: after transition relation, 3: after reachable states
      Cudd_AutodynEnable(bddmgr->getManager(), REORDERING);
    else
      Cudd_AutodynDisable(bddmgr->getManager());

    satisfied = new bool[is_formulae->size()];
    for(unsigned int x=0; x<is_formulae->size(); x++)
      satisfied[x] = false;

    if(options["uniform"] == 1) { // model checking uniform strategies
      traverse_uniform_strategies(uniform_prots, para);
      para->vprot = vprot;
      para->vRT = vRT;
      //delete para->reach;
      // delete individual BDD for integers
      clear_integer_BDDs(para);
      clear_enumerate_BDDs(para);
      for(unsigned int x=0; x<uniform_prots->size(); x++) {
        vector < BDD* > *uni_prot = (*uniform_prots)[x];
        for(unsigned int y=0; y<uni_prot->size(); y++)
          delete (*uni_prot)[y];
        delete (*uniform_prots)[x];
      }
      delete uniform_prots;
    } else {
      if (options["quiet"] == 0 || options["simulation"] == 0) {
        cout << "Building reachable state space..." << endl;
      }
      
      if (options["quiet"] == 0 && options["verbosity"] > 1)
        ftime(&t0);
      
      unsigned int acounter1 = 1;
      reach = compute_reach(in_st, v, pv, a, vRT, bddmgr, &acounter1, 1, &threadmem);
      
      //time_t t2 = time(0);  
      para->reach = new BDD(reach);
      
      if (options["dao"] > 0) // 1: all disable, 2: after transition relation, 3: after reachable states
        Cudd_AutodynDisable(bddmgr->getManager());
      
      if (options["verbosity"] > 2)
        cout << "Done." << endl;
      
      if (options["quiet"] == 0 && options["verbosity"] > 1) {
        ftime(&t1);
        cout << "It took " << ((t1.time-t0.time) + (t1.millitm-t0.millitm)/1000.0) << " seconds to generate state space." << endl;
      }
      
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

			if(options["exportmodel"] == 1) {
        vector< vector< int >*> *countex = new vector< vector< int >*>;
        map< int, BDD * > *idbdd = new map< int, BDD * >;
        vector< vector< transition * >*> *cextr = new vector< vector< transition * >*>;

        BDD *is_temp = new BDD(*(para->in_st));
        export_model(para, is_temp, countex, idbdd, cextr);
        //string tempstr;
        //transform(filename.begin(), filename.end(), back_inserter(tempstr), ::tolower);
        string fname = cex_prefix + /*filename.substr(0, tempstr.rfind(".ispl"))*/ + "model";
        print_cex(para, fname, "statespace", idbdd, cextr);
        clear_cex(countex, idbdd, cextr);
        delete_cex(countex, idbdd, cextr);
        delete is_temp;
      }

			// Model checking procedure
      do_model_checking(para); 
    }

    struct timeb tmb1;
    ftime(&tmb1);
    cout << "execution time = " << ((tmb1.time-tmb.time) + (tmb1.millitm-tmb.millitm)/1000.0) << endl;
    if(options["uniform"] == 1) {
      cout << "maximum number of reachable states = " << reachablestates << endl;
      cout << "number of uniform strategies = " << num_of_strategies << endl;
    } else {
      reachablestates = reach.CountMinterm(v->size());
      cout << "number of reachable states = " << reachablestates << endl;
    }
    unsigned long memoryinuse = bddmgr->ReadMemoryInUse();
    memoryinuse = (memoryinuse < threadmem) ? threadmem : memoryinuse;
    cout << "BDD memory in use = " << memoryinuse << endl;
    if (options["bdd_stats"] == 1) {
      bddmgr->info();
    }
    //delete_cex(countex, idbdd, cextr);
    in_st = reach = para->bddmgr->bddZero();
    delete satisfied;
  }
 clearmemory:
  free_mcmas_memory(para);
  free_cudd_memory(para);
}
