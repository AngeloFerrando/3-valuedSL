#include <setjmp.h>
#include <signal.h>
#include "utilities.hh"

extern string cex_prefix;    
extern bdd_parameters * parameters;

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
print_state(BDD state, vector<BDD> v)
{
  for (unsigned int i = 0; i < agents->size(); i++) {
    cout << "Agent " << (*agents)[i]->get_name() << endl;
    (*agents)[i]->print_state("  ", state, v);
  }
}

void 
print_states(BDD states, vector<BDD> v, Cudd* bddmgr) 
{
  BDD tmp = states;
  int k = 0;
  while(tmp != bddmgr->bddZero()) {
    cout << "------------ state " << k << " ------------" << endl;
    BDD state = tmp.PickOneMinterm(v);
    for(unsigned int i=0; i<agents->size(); i++) {
      cout << "Agent " << (*agents)[i]->get_name() << endl;
      (*agents)[i]->print_state("  ", state, v);
    }
    tmp = tmp - state;
    k++;
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
    if ((*agents)[i] != NULL && !(*agents)[i]->is_valid_state(state, v))
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
        if ((*i).second->get_type() == 3)
          a *= ((enumerate *) (*i).second)->build_all_BDDs(bddmgr, v);
    map< string, basictype * >*vars = (*agents)[j]->get_vars();
    if (vars != NULL && vars->size() > 0)
      for (map< string, basictype * >::iterator i = vars->begin();
           i != vars->end(); i++)
        if ((*i).second->get_type() == 3)
          a *= ((enumerate *) (*i).second)->build_all_BDDs(bddmgr, v);
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
      if ((*i).second->get_type() == 3)
        a *= ((enumerate *) (*i).second)->build_all_BDDs(bddmgr, v);
  map< string, basictype * >*vars = (*agents)[j]->get_vars();
  if (vars != NULL && vars->size() > 0)
    for (map< string, basictype * >::iterator i = vars->begin();
         i != vars->end(); i++)
      if ((*i).second->get_type() == 3)
        a *= ((enumerate *) (*i).second)->build_all_BDDs(bddmgr, v);
  return a;
}

void 
produce_witness(bdd_parameters *para, BDD state, string name) 
{
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

void 
free_mcmas_memory(bdd_parameters *para) 
{
  for(unsigned int i=0; i<agents->size(); i++)
    delete (*agents)[i];
  delete agents;
  delete is_agents;
	delete is_agents_index;
  for(map<string, bool_expression *>::iterator it = is_evaluation->begin(); it != is_evaluation->end(); it++) {
    if((it->first).compare("_init") != 0 || it->second->get_op() != 0)
      delete it->second;
  }
  delete is_evaluation;
  delete is_groups;
  delete is_formulae;
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

void 
free_cudd_memory(bdd_parameters *para) 
{
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

void 
clear_cex(vector< vector< int >*>* countex, map< int, BDD * >* idbdd, 
               vector< vector< transition * >*>* cextr) 
{
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

void 
delete_cex(vector< vector< int >*>* countex, map< int, BDD * >* idbdd, 
                vector< vector< transition * >*>* cextr) 
{
  //clear_cex(countex, idbdd, cextr);
  delete countex;
  delete idbdd;
  delete cextr;
}

