#ifndef UTILITIES_HH
# define UTILITIES_HH
#include <vector>
#include <cmath>
#include "types.hh"
#include "cuddObj.hh"

using namespace std;

extern "C++" {
  inline int log_2(int x) {
    if(x==1)
      return 1;
    else
      return (int)ceil(log2(x));
  }
  BDD Exists(Cudd *bddmgr, vector<BDD>* v, BDD x);
  BDD Exists(Cudd *bddmgr, vector<BDD>* v, vector<BDD>* a, BDD x);
  BDD Exists(Cudd * bddmgr, vector<BDD> * v, BDD x, unsigned int start, unsigned int end);
  BDD Abstract_key_var(Cudd * bddmgr, vector<BDD> * v, BDD x, int index_begin, int index_end);
  ADD ADDExists(Cudd * bddmgr, vector<ADD> v, ADD x);
  BDD check_EX (BDD next, bdd_parameters *para);
  BDD check_EF (BDD p, bdd_parameters *para);
  BDD check_EG (BDD p, bdd_parameters *para);
  BDD check_EU(BDD p, BDD q, bdd_parameters *para);
  BDD check_AU(BDD p, BDD q, bdd_parameters *para);
  BDD check_nK (BDD next, BDD RK, bdd_parameters *para);
  BDD check_nO (BDD next, string name, bdd_parameters *para);
  BDD check_GK (BDD next, string name, bdd_parameters *para);
  BDD check_DK (BDD next, string name, bdd_parameters *para);
  BDD check_GCK (BDD next, string name, bdd_parameters *para);
	BDD check_ATLG_aux(BDD p, string grpname, bdd_parameters * para);
	BDD check_ATLX(BDD next, string grpname, bdd_parameters *para);
  BDD check_ATLG(BDD p, string grpname, bdd_parameters *para);
  BDD check_ATLU(BDD q1, BDD q2, string grpname, bdd_parameters *para);  

  BDD check_EU_Qh(BDD p, BDD q, bdd_parameters * para, vector< BDD* >* qh);
  BDD check_EG_fair_Qh(BDD p, bdd_parameters * para, vector< vector < BDD* >* >* Qh);
  BDD check_EG_fair (BDD p, bdd_parameters *para);
  BDD check_EG_fair (BDD p, bdd_parameters *para, vector<BDD> additional_bdds);
  BDD check_EF_fair (BDD p, BDD fair_reach, bdd_parameters *para);
  BDD check_EX_fair (BDD p, BDD fair_reach, bdd_parameters *para);
  BDD check_EU_fair(BDD p, BDD q, BDD fair_reach, bdd_parameters *para);
  BDD check_nO_fair (BDD next, string name, BDD fair_reach, bdd_parameters *para);
  BDD check_GK_fair (BDD next, string name, BDD fair_reach, bdd_parameters *para);
  BDD check_DK_fair (BDD next, string name, BDD fair_reach, bdd_parameters *para);
  BDD check_GCK_fair (BDD next, string name, BDD fair_reach, bdd_parameters *para);
  BDD check_ATLX_fair(BDD next, string grpname, BDD fair_reach, bdd_parameters *para);
  BDD check_ATLG_fair(BDD p, string grpname, bdd_parameters *para);
  BDD check_ATLU_fair(BDD q1, BDD q2, string grpname, BDD fair_reach, bdd_parameters *para);  

  BDD get_K_states(BDD aset1, BDD *state, string name, bdd_parameters *para);
  BDD get_nK_states(BDD *state, string name, bdd_parameters *para);
  BDD get_nK_states_fair(BDD *state, string name, BDD fair_reach, bdd_parameters *para);
  BDD get_GK_states(BDD aset1, BDD *state, string name, bdd_parameters *para);
  BDD get_DK_states(BDD aset1, BDD *state, string name, bdd_parameters *para);

  DdNode * addApplyLT(DdManager* mgr, DdNode ** n1, DdNode ** n2);
  DdNode * addApplyLE(DdManager* mgr, DdNode ** n1, DdNode ** n2);
  DdNode * addApplyGT(DdManager* mgr, DdNode ** n1, DdNode ** n2);
  DdNode * addApplyGE(DdManager* mgr, DdNode ** n1, DdNode ** n2);
  DdNode * addApplyEQ(DdManager* mgr, DdNode ** n1, DdNode ** n2);
  DdNode * addApplyNEQ(DdManager* mgr, DdNode ** n1, DdNode ** n2);

  ADD addLT(Cudd * bddmgr, ADD a1, ADD a2);
  ADD addLE(Cudd * bddmgr, ADD a1, ADD a2);
  ADD addGT(Cudd * bddmgr, ADD a1, ADD a2);
  ADD addGE(Cudd * bddmgr, ADD a1, ADD a2);
  ADD addEQ(Cudd * bddmgr, ADD a1, ADD a2);
  ADD addNEQ(Cudd * bddmgr, ADD a1, ADD a2);
  // Calculate X * RT with local transition relations
  BDD timesTrans(BDD *from, BDD *to, vector<BDD> *vRT);

  // Remove actions from X * RT
  BDD timesRT(BDD *state, Cudd *bddmgr, vector<BDD> *vRT, vector<BDD> *a);
  BDD compute_successors(BDD *state, Cudd * bddmgr, vector<BDD> * vRT, vector<BDD> * a, vector<BDD> *v, vector<BDD> *pv);
  int search_string_table(string *s);
  int search_variable_table(variable *v);
  int search_logic_expression_table(bool_expression *le);
  int search_logic_expression_table1(bool_expression *le);
  int search_logic_expression_table(expression *e1, expression *e2);
  int search_logic_expression_table1(expression *e1, expression *e2);
}

extern map < string, int > options;
extern map<string, basic_agent *> *is_agents;
extern map<string, int> *is_agents_index;
extern vector<basic_agent *> *agents;
extern map<string, bool_expression *> *is_evaluation;
extern bool_expression *is_istates;
extern map<string, set<string> > *is_groups;
extern vector<modal_formula> *is_formulae;
extern vector<fairness_expression *> *is_fairness;
extern int obsvars_bdd_length;
extern int envars_bdd_length;
//extern BDD fair_reach;
//extern vector< vector<int> * > *countex; // For counterexamples
//extern map<int, BDD *> *idbdd;
extern int scount;
//extern vector < vector <transition *> *> *cextr;
extern vector<string *> *string_table;
extern vector<variable *> *variable_table;
extern vector<bool_expression *> *logic_expression_table;
extern vector<bool_expression *> *logic_expression_table1;
extern void print_state(BDD state, vector<BDD> v);
extern void print_states(BDD states, vector<BDD> v, Cudd* bddmgr);
extern void print_action(BDD state, vector<BDD> a);
extern string state_to_str(BDD state, vector<BDD> v);
extern BDD append_variable_BDDs(Cudd * bddmgr, vector<BDD> * v, BDD a);
extern int export_model(bdd_parameters * para, BDD *is, vector< vector< int >*> *countex, map< int, BDD * > *idbdd, vector< vector< transition * >*> *cextr);
extern void print_cex(bdd_parameters * para, string fname, string str_head, map< int, BDD * > *idbdd, vector< vector< transition * >*> *cextr);
extern void clear_cex(vector< vector< int >*>* countex, map< int, BDD * >* idbdd, vector< vector< transition * >*>* cextr);
extern void delete_cex(vector< vector< int >*>* countex, map< int, BDD * >* idbdd, vector< vector< transition * >*>* cextr);

extern int states_count;
extern int actions_count;

extern bool force_atlk;
extern map< string, map< string, vector< BDD* >* >* >* integerBDDs;
extern map< string, map< string, BDD* >* >* enumerateBDDs;

#endif // ! UTILITIES_HH
