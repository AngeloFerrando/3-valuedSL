#ifndef MCMAS_TYPES_HH
#define MCMAS_TYPES_HH
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>
#include <set>
#include <vector>
#include <string>
#include <map>
#include "cuddObj.hh"

#define MAX_ID_LENGTH 50

typedef bool** bool_ptr_ptr; 
typedef bool* bool_ptr; 
typedef char* char_ptr; 
typedef int* int_ptr; 

using namespace std;

//#define num_of_threads 4
//#define num_of_threads1 2
//#define num_of_blocks 8
//#define time_of_iteration 5


class bool_expression;

struct bdd_parameters
{
  Cudd *bddmgr;
  size_t num_of_agents;
  bool_expression *istates;
  vector<BDD> *vRT;
  vector<BDD> *vevol;
  vector<BDD> *vprot;
  BDD *in_st;
  BDD *reach;
  vector< BDD * >*vec_in_st;
  vector< BDD * >*vec_reach;
  vector< BDD * >*vec_reachRT;
  vector< bool_expression * >*vec_istates;
  vector< BDD * >*vec_formula;
  bool merge;
  unsigned int id;
  vector<BDD> *v;
  vector<BDD> *pv;
  vector<ADD> *addv;
  vector<ADD> *addpv;
  vector<BDD> *a;
  BDD *reachRT;
  bool calReachRT;
  int tableau_vars; // used in path formulae
  bool_ptr_ptr results;
  map< string, BDD > *BDD_cache;
  map< string, ADD > *ADD_cache;
  map< string, BDD* > *fair_gamma_FO;
  map< string, BDD* > *nfair_gamma_FO;
  pid_t tid;
  pthread_mutex_t *mutex;
};

struct bdd_parameters1
{
  Cudd *bddmgr;
  Cudd *bddmgr1;
  size_t num_of_agents;
  vector<BDD> *vRT;
  BDD *reach;
  vector<BDD *> *vec_in_st;
  unsigned int *sp;
	unsigned int *sleep_count;
  bool merge;
  unsigned int id;
  vector<BDD> *v;
  vector<BDD> *pv;
  vector<BDD> *a;
  pthread_mutex_t *mutex;
	pthread_cond_t *cond;
	bool *termination;
  BDD **reach1;
};


typedef BDD* BDD_ptr; 
typedef BDD** BDD_ptr_ptr; 
typedef vector<BDD*> * vec_BDD_ptr;
typedef vector<BDD*> ** vec_BDD_ptr_ptr;
typedef bdd_parameters* bdd_parameters_ptr;
typedef bdd_parameters** bdd_parameters_ptr_ptr;
typedef bdd_parameters1* bdd_parameters1_ptr;
typedef bdd_parameters1** bdd_parameters1_ptr_ptr;



/** definition of basic type and some extended types. 
    Boolean type does not extend the basic type.
*/
class basictype
{
  string *name;
  unsigned char type;		// 1: boolean, 2: rangedint, 3: enumerate
  int index_begin;		// the index of bdd variables in the vector
  int index_end;
public:
  string name_index;
  basictype(string * n);
  basictype(string * n, unsigned char t);
  virtual ~basictype();
  string get_name();
  unsigned char get_type();
  virtual string to_string();
  virtual int BDD_length();
  void set_index_begin(int i);
  void set_index_end(int i);
  int get_index_begin();
  int get_index_end();
  void print_value_index();
  virtual void print_state(string prefix, BDD state, vector<BDD> v);
  virtual void print_stateXML(ofstream * myfile, BDD state, vector<BDD> v);
  virtual string state_to_str(BDD state, vector<BDD> v);
  virtual bool is_valid_state(BDD state, vector<BDD> v);
  virtual ADD build_ADD_tree(Cudd * bddmgr, vector<ADD> * addv, map< string, ADD > *ADD_cache);
  virtual BDD build_all_BDDs(Cudd * bddmgr, vector<BDD> * v);
  virtual void build_individual_BDD(Cudd * bddmgr, vector<BDD> *v, vector< BDD* > *bddblocks, unsigned int count);
};

class enumerate:public basictype
{
  set< string > *enumvalue;
  map< string, vector< bool > *>*value_index;
  int bdd_length;
public:
  enumerate(string * n, set< string > *s);
  ~enumerate();
  set< string > *get_enumvalue();
  int is_valid_value(string s);
  string to_string();
  int BDD_length();
  unsigned int get_number_of_elements();
  bool is_power_of_two();
  void set_value_index();
  void print_value_index();
  vector< bool > *get_value_index(string value);
  string find_value_by_index(vector< bool > index);
  void print_state(string prefix, BDD state, vector<BDD> v);
  void print_stateXML(ofstream * myfile, BDD state, vector<BDD> v);
  string state_to_str(BDD state, vector<BDD> v);
  bool is_valid_state(BDD state, vector<BDD> v);
  ADD build_ADD_tree(Cudd * bddmgr, vector<ADD> * addv, map< string, ADD > *ADD_cache);
  BDD build_all_BDDs(Cudd * bddmgr, vector<BDD> * v);
  void build_individual_BDD(Cudd * bddmgr, vector<BDD> *v, vector< BDD* > *bddblocks, unsigned int count);
};

class rangedint:public basictype
{
  int lowerbound;
  int upperbound;
  int power_two;
  int half_power;
  int bdd_length;
public:
  rangedint(string * n, int l, int u);
  ~rangedint();
  int get_lowerbound();
  int get_upperbound();
	int get_length();
	bool is_power_of_two();
  bool is_valid_value(int i);
  string to_string();
  int BDD_length();
  void print_value_index();
  vector< int >*get_value_index(int value);
  int find_value_by_index(vector< bool > index);
  void print_state(string prefix, BDD state, vector<BDD> v);
  void print_stateXML(ofstream * myfile, BDD state, vector<BDD> v);
  string state_to_str(BDD state, vector<BDD> v);
  bool is_valid_state(BDD state, vector<BDD> v);
  ADD build_ADD_tree(Cudd * bddmgr, vector<ADD> * addv, map< string, ADD > *ADD_cache);
  BDD build_all_BDDs(Cudd * bddmgr, vector<BDD> * v);
  void build_individual_BDD(Cudd * bddmgr, vector<BDD> *v, vector< BDD* > *bddblocks, unsigned int count);
};

class Object
{
public:
  virtual ~ Object();
  virtual string to_string();
};

class expression
{
  /* 0: variable, 1: bool value, 2: int value, 3: enum value, 4: action 
     5: plus, 6: minus, 7: times, 8: divide (arithmetic_expression)
     9: &, 10: |, 11: ~, 12: ^ (bit_expression)
   */
  unsigned char type;
public:
  expression(unsigned char i);
  virtual ~ expression();
  unsigned char get_type();
  virtual string to_string();
  virtual ADD build_ADD_tree(Cudd * bddmgr, vector<ADD> * addv, map< string,
			     ADD > *ADD_cache);
  virtual BDD encode_BDD_true(Cudd * bddmgr, vector<BDD> * v);
  virtual BDD encode_BDD_false(Cudd * bddmgr, vector<BDD> * v);
  virtual bool equal_to(expression * expr);
};

class variable:public expression
{
  string *agent_name;		// agent that the variable belongs to
  string *name;			// variable name
  basictype *var_type;
public:
  variable(string * a_n, string * n);
  variable(string * n);
  variable(string * a_n, string * n, basictype * v_t);
  ~variable();
  void set_agent_name(string * a_n);
  string get_agent_name();
  bool is_agent_name_null();
  string get_variable_name();
  string *get_variable_name_point();
  string to_string();
  void set_var_type(basictype * t);
  basictype *get_var_type();
  ADD build_ADD_tree(Cudd * bddmgr, vector<ADD> * addv, map< string,
		     ADD > *ADD_cache);
  bool equal_to(variable * expr);
  bool equal_to(expression * expr);
  BDD encode_BDD_true(Cudd * bddmgr, vector<BDD> * v);
  BDD encode_BDD_false(Cudd * bddmgr, vector<BDD> * v);
};

class basic_agent;

class laction:public expression
{
  string *agent_name;		// agent that the action belongs to
  basic_agent *agent;
public:
  laction();
  laction(string * a_n);
  laction(string * a_n, basic_agent * ag);
  ~laction();
  void set_agent_name(string * a_n);
  string get_agent_name();
  void set_agent(basic_agent * a);
  basic_agent *get_agent();
  bool is_agent_name_null();
  string to_string();
  ADD build_ADD_tree(Cudd * bddmgr, vector<ADD> * addv, map< string,
		     ADD > *ADD_cache);
  bool equal_to(laction * expr);
  bool equal_to(expression * expr);
  BDD encode_BDD_true(Cudd * bddmgr, vector<BDD> * v);
  BDD encode_BDD_false(Cudd * bddmgr, vector<BDD> * v);
};

class bool_value:public expression
{
  bool value;			// 0: false, 1: true
public:
  bool_value(bool v);
  ~bool_value();
  bool get_value();
  string to_string();
  ADD build_ADD_tree(Cudd * bddmgr, vector<ADD> * addv, map< string,
		     ADD > *ADD_cache);
  bool equal_to(bool_value * expr);
  bool equal_to(expression * expr);
  BDD encode_BDD_true(Cudd * bddmgr, vector<BDD> * v);
  BDD encode_BDD_false(Cudd * bddmgr, vector<BDD> * v);
};

class int_value:public expression
{
  int value;
public:
  int_value(int v);
  ~int_value();
  int get_value();
  string to_string();
  ADD build_ADD_tree(Cudd * bddmgr, vector<ADD> * addv, map< string,
		     ADD > *ADD_cache);
  bool equal_to(int_value * expr);
  bool equal_to(expression * expr);
  BDD encode_BDD_true(Cudd * bddmgr, vector<BDD> * v);
  BDD encode_BDD_false(Cudd * bddmgr, vector<BDD> * v);
};

class enum_value:public expression
{
  string *value;
public:
  enum_value(string * v);
  ~enum_value();
  string get_value();
  string to_string();
  ADD build_ADD_tree(Cudd * bddmgr, vector<ADD> * addv, map< string,
		     ADD > *ADD_cache);
  bool equal_to(enum_value * expr);
  bool equal_to(expression * expr);
  BDD encode_BDD_true(Cudd * bddmgr, vector<BDD> * v);
  BDD encode_BDD_false(Cudd * bddmgr, vector<BDD> * v);
};

class arithmetic_expression:public expression
{
  expression *operands[2];
public:
  arithmetic_expression(unsigned char o, expression * e1, expression * e2);
  ~arithmetic_expression();
  expression *get_operand(unsigned char i);
  string to_string();
  // check if variables and their value inside this expression are defined
  bool check_var_and_value(map< string, basictype * >*obsvars, map< string,
			   basictype * >*vars);
  bool check_var_and_value(map< string, map< string, basictype * > >*vars);
  ADD build_ADD_tree(Cudd * bddmgr, vector<ADD> * addv, map< string,
		     ADD > *ADD_cache);
  bool equal_to(arithmetic_expression * expr);
  bool equal_to(expression * expr);
  BDD encode_BDD_true(Cudd * bddmgr, vector<BDD> * v);
  BDD encode_BDD_false(Cudd * bddmgr, vector<BDD> * v);
};

class bit_expression:public expression
{
  expression *operands[2];
public:
  bit_expression(unsigned char o, expression * e1, expression * e2);
  ~bit_expression();
  expression *get_operand(unsigned char i);
  string to_string();
  // check if variables and their value inside this expression are defined
  bool check_var_and_value(map< string, basictype * >*obsvars, map< string,
			   basictype * >*vars);
  bool check_var_and_value(map< string, map< string, basictype * > >*vars);
  ADD build_ADD_tree(Cudd * bddmgr, vector<ADD> * addv, map< string,
		     ADD > *ADD_cache);
  bool equal_to(bit_expression * expr);
  bool equal_to(expression * expr);
  BDD encode_BDD_true(Cudd * bddmgr, vector<BDD> * v);
  BDD encode_BDD_false(Cudd * bddmgr, vector<BDD> * v);
};

class logic_expression:public Object
{
  unsigned char op;		// 0: =, 1: <>, 2: <, 3: <=, 4: >, 5: >=
  expression *operands[2];
public:
  logic_expression(unsigned char o, expression * e1, expression * e2);
  ~logic_expression();
  unsigned char get_op();
  expression *get_operand(unsigned char i);
  string to_string();
  // check if variables and their value inside this expression are defined
  bool check_evolution(map< string, basictype * >*obsvars, map< string,
		       basictype * >*vars, string agent_name, map< string,
		       basic_agent * >*global_actions);
  // global check of initial states and evaluation function
  bool check_global_consistency(map< string, map< string,
				basictype * > >*vars);
  BDD encode_bdd(bdd_parameters * para, BDD base);
  bool equal_to(logic_expression * expr);
  bool equal_to(expression * e1, expression * e2);
};

class bool_expression:public Object
{
  unsigned char op;		// 0: logic_expression, 1: and, 2: or, 3: not, 4: other, 5: true, 6: false
  // only the operands[0] is used if op == 0 or 3
  Object *operands[2];
public:
  bool_expression();
  bool_expression(unsigned char o, Object * obj1);	// single operand
  bool_expression(unsigned char o, Object * obj1, Object * obj2);	// two operands
  ~bool_expression();
  unsigned char get_op();
  bool is_other_branch();
  Object *get_operand(unsigned char i);
  string to_string();
  // check if variables and their value inside this expression are defined
  bool check_var_and_value_flat(map< string, basictype * >*obsvars,
				map< string, basictype * >*vars,
				string agent_name, map< string,
				basic_agent * >*global_actions);
  // global check of evolution function
  bool check_evolution_flat(map< string, basictype * >*obsvars, map< string,
			    basictype * >*vars, string agent_name,
			    map< string, basic_agent * >*global_actions);
  // global check of initial states and evaluation function
  bool check_global_consistency_flat(map< string, map< string,
				     basictype * > >*vars);
  void collect_exprs(vector< bool_expression * >*expr_vector,
		     unsigned int type);
  BDD encode_bdd_flat(bdd_parameters * para, BDD base);
  bool equal_to(bool_expression * expr);
  bool equal_to(expression * e1, expression * e2);
};

class atomic_proposition:public Object
{
  string *proposition;
public:
  atomic_proposition(string * t);
  ~atomic_proposition();
  string get_proposition();
  string to_string();
};

class basic_agent;
class fairness_expression;
class transition;

class modal_formula:public Object
{
  /* 0: term, 1=AND, 2=OR, 3=NOT, 4=IMPLIES, 5=TRUE (internally used only),
     10=AG, 11=EG, 12=AX, 13=EX, 14=AF, 15=EF, 16=AU, 17=EU,
     30=K, 31=GK (everybody knows), 32=GCK (commond knowledge),
     40=O (deontic), 42=DK (distributed knowledge),
     45=<group>X (atl quantifier for X),
     46=<group>F (atl quantifier for F),
     47=<group>G (atl quantifier for G),
     48=<group> U (atl quantifier for U),
     50=A, 51=E, 60 = LTL prefix,
     61=G, 62=F, 63=X, 64=U,
   */
  unsigned char op;
  Object *obj[3];
public:
  modal_formula(atomic_proposition * obj1);	// term
  modal_formula(unsigned char o, modal_formula * f1);	// sigle operand formula
  modal_formula(unsigned char o, modal_formula * f1, modal_formula * f2);	// two operands formula
  modal_formula(unsigned char o, modal_formula * f1, modal_formula * f2, modal_formula * f3);	// three operands formula
  ~modal_formula();
  unsigned char get_op();
  Object *get_operand(unsigned char i);
  string to_string();
  string to_string_const() const;
  bool check_atomic_proposition(unsigned char type);
  BDD check_formula(bdd_parameters * para);
  //BDD check_formula_fair(bdd_parameters * para, BDD fair_reach);

  modal_formula *push_negations(unsigned int level);
  bool is_ACTLK_new();
  bool is_ECTLK_new();
  set<modal_formula*>* get_elementary_formulas();
  bool is_NonTemporal();
  bool build_cex(BDD * state, unsigned int index, bdd_parameters * para,
		 vector< vector< int >*>* countex, map< int, BDD * >* idbdd,
		 vector< vector< transition * >*>* cextr);
  /*bool build_cex_fair(BDD * state, unsigned int index, BDD fair_reach, bdd_parameters * para,
		      vector< vector< int >*>* countex, map< int, BDD * >* idbdd,
		      vector< vector< transition * >*>* cextr);*/

private:
  BDD check_path_sat(bdd_parameters * para, const map<modal_formula *, int>& index_map, int additional_offset);
  BDD build_path_tableau(bdd_parameters * para, const map<modal_formula *, int>& index_map);
  BDD build_consistency_rules(bdd_parameters * para, const map<modal_formula *, int>& index_map, map<modal_formula *, BDD> epistemic_path_values);
  void get_path_fairness_constraints(bdd_parameters * para, const map<modal_formula *, int>& index_map, vector<BDD> * fairness_bdds);
  modal_formula* remove_path_gs();
  void compute_epistemic_path_subformulae(bdd_parameters * para, map<modal_formula*, BDD>* result_map);
};

/* A fairness expression is a modal formula.
 */
class fairness_expression:public modal_formula
{
  BDD bdd_representation;	// Its representation (i.e. the set of reachable states
  // in which the expression is true, as a BDD
public:
  fairness_expression(atomic_proposition * obj1);	// term
  fairness_expression(unsigned char o, modal_formula * f1);
  fairness_expression(unsigned char o, modal_formula * f1,
		      modal_formula * f2);
  fairness_expression(unsigned char o, modal_formula * f1,
		      modal_formula * f2, modal_formula * f3);
  BDD get_bdd_representation();
  void set_bdd_representation(BDD bddrep);
  void delete_bdd_representation(bdd_parameters *para);
};

/*
definition of one line in protocol
*/
class protocol_line
{
  bool_expression *condition;	// enabling condition
  set< string > *actions;
public:
  protocol_line(bool_expression * c, set< string > *a);
  ~protocol_line();
  bool_expression *get_condition();
  set< string > *get_actions();
  string to_string();
};

/*
definition of an assignment 
*/
class assignment
{
  variable *var;
  expression *var_value;
public:
  assignment(string * name, expression * value);
  ~assignment();
  variable *get_var();
  expression *get_var_value();
  string to_string();
  bool check_var_and_value(map< string, basictype * >*obsvars, map< string,
			   basictype * >*vars);
  BDD encode_bdd(bdd_parameters * para, BDD base);
  BDD encode_bdd_overflow(bdd_parameters * para);
};

/*
  defition of one basic line in evolution function
*/
class evolution_line
{
  vector< assignment * >*assignments;
  bool_expression *condition;
public:
  evolution_line(vector< assignment * >*a, bool_expression * c);
  ~evolution_line();
  vector< assignment * >*get_assignments();
  bool_expression *get_condition();
  string to_string();
  BDD encode_bdd_assignements(bdd_parameters * para);
  BDD encode_bdd_condition(bdd_parameters * para);
  bool check_double_assignment();
  vector< evolution_line * >*extend_to_all_variables(map< string,
						      basictype *
						      >*allvars);
  BDD encode_bdd_overflow(bdd_parameters * para);
};

/*
  Basic definition of agents
  includes non-observable variables, red states, 
  actions, protocol and evolution function
*/
class basic_agent
{
  string *name;			// agent name
  map< string, variable * >*lobsvars;	// local observable variables
  map< string, basictype * >*obsvars;	// observable variables
  map< string, basictype * >*vars;	// non-observable variables
  vector< basictype * >*vec_obsvars;	// observable variables
  vector< basictype * >*vec_vars;	// non-observable variables
  bool_expression *redstates;	// red states
  set< string > *actions;	// local actions
  vector< protocol_line * >*protocol;	// local protocol
  vector< evolution_line * >*evolution;	// evolution function
  int action_index_begin;
  int action_index_end;
  int var_index_begin;
  int var_index_end;
  map< string, vector< bool > *>*action_indices;	// store index of variables for actions
public:
  basic_agent(string * n, map< string, variable * >*lv,
	      map< string, basictype * >*v0,
	      vector< basictype * >*vecv0,
	      map< string, basictype * >*v1,
	      vector< basictype * >*vecv1,
	      bool_expression * r,
	      set< string > *v2, vector< protocol_line * >*v3,
	      vector< evolution_line * >*v4);
  virtual ~ basic_agent();
  string get_name();
  string *get_name_point();
  map< string, basictype * >*get_obsvars();
  map< string, variable * >*get_lobsvars();
  vector< basictype * >*get_vec_obsvars();
  vector< basictype * >*get_vec_vars();
  map< string, basictype * >*get_vars();
  basictype *get_basictype_by_name(string varname);
  set< string > *get_actions();
  vector< protocol_line * >*get_protocol();
  vector< evolution_line * >*get_evolution();
  bool_expression *get_redstates();
  string to_string();
  int state_BDD_length();
  int obsvars_BDD_length();
  unsigned int actions_BDD_length();
  void set_action_index_begin(int i);
  void set_action_index_end(int i);
  int get_action_index_begin();
  int get_action_index_end();
  void set_var_index_begin(int i);
  void set_var_index_end(int i);
  int get_var_index_begin();
  int get_var_index_end();
  void generate_action_bdd_value();
  void print_value_index();
  map< string, vector< bool > *>*get_action_indices();
  int allocate_BDD_2_variables(int start);
  int allocate_BDD_2_actions(int start);
  BDD encode_action(bdd_parameters * para, string act);
  BDD encode_protocol(bdd_parameters * para);
  BDD encode_evolution(bdd_parameters * para);
  BDD encode_evolution_smv(bdd_parameters * para);

  BDD encode_greenstates(bdd_parameters * para);
  void print_variable_BDD_encoding();
  void print_state(string prefix, BDD state, vector<BDD> v);
  void print_action(BDD state, vector<BDD> a);
  bool is_valid_state(BDD state, vector<BDD> v);
  bool is_valid_action(BDD state, vector<BDD> a);
  void print_stateXML(ofstream * myfile, BDD state, vector<BDD> v);
  string state_to_str(BDD state, vector<BDD> v);
  string action_to_str(BDD state, vector<BDD> v);
	basictype *get_var_def(string varname);

  /*
   * delete all local states of other agent
   */
  BDD project_local_state(BDD * state, Cudd * bddmgr, vector<BDD> * v);
  BDD project_local_actions(BDD * SA, Cudd * bddmgr, vector<BDD> * a);

  vector<BDD> get_BDDvector(Cudd * bddmgr, vector<BDD> * v, vector<BDD> * pv);
  BDD project_local_trans(BDD * trans, Cudd * bddmgr, vector<BDD> * v,
			  vector<BDD> * pv);
  /* 
   * collect all enumerate values defined for observable values
   */
  set< string > *get_obs_enum_values();
  /*
   * check a variable has the same name as a enumerate values
   */
  bool check_var_against_enum_values(set < string > *obsenum);

  /*
   * check if local observable variables have been defined in the environment
   */
  bool check_lobsvars(map< string, basictype * >*envars);

  BDD compute_whole_state_for_integer(BDD s, bdd_parameters * para);
  BDD reduce_whole_state_for_enumerate(BDD s, bdd_parameters * para);
  vector< BDD > get_localstate_BDD_vector(bdd_parameters * para);
  vector< BDD* > *split_protocol(BDD prot, bdd_parameters * para);
};

/*
 This class defines a transition between two states.
 It is used for counterexample display  
 */
class transition
{
  BDD *from;			// The origin of the transition (a state)
  int fromid;			// the id of the from state
  BDD *to;			// The destination of the transition
  int toid;			// the id of the destination state.
  bool temporal;		// true means it is a temporal transition
  string epistemic1;
  string epistemic2;
  BDD *label;			// If it is a temporal transition, the joint action enabling it.
public:
  transition(BDD * from, int fromid, BDD * to, int toid, BDD * label);
  transition(BDD * from, int fromid, BDD * to, int toid, string epistemic1,
	     BDD * label);
  transition(BDD * from, int fromid, BDD * to, int toid, string epistemic1,
	     string epistemic2, BDD * label);
  transition();
  ~transition();
  BDD *getfrom();
  BDD *getto();
  BDD *getlabel();
  int getfromid();
  int gettoid();
  void setfrom(BDD * from);
  void setto(BDD * to);
  void setlabel(BDD * label);
  void setfromid(int fromid);
  void settoid(int toid);
  void print(vector<BDD> * v, vector<BDD> * a);
  void printXML(ofstream * myfile, vector<BDD> * v);
  void to_str(ofstream * myfile, vector<BDD> * a);
  string index_to_string(vector<BDD> * a);

  bool isTemporal();
  string getEpistemic1();
  string getEpistemic2();
};

#endif // ! MCMAS_TYPES_HH
