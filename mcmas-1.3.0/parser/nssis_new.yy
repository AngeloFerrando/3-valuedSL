%skeleton "lalr1.cc"                          /*  -*- C++ -*- */
%require "2.4.1"
%defines
%define "parser_class_name" "mcmas_parser"

%code requires {
#define USE(VALUE) /*empty*/

# include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include "types.hh"

class mcmas_driver;
}

%parse-param { mcmas_driver& driver }
%lex-param   { mcmas_driver& driver }

%locations
%initial-action
{
  // Initialize the initial location.
  @$.begin.filename = @$.end.filename = &driver.file;
};

%debug
%error-verbose

%union {
  int ival;
  string* sval;
  map<string, basictype *>* map_basictype;
  pair<map<string, basictype *>*, vector<basictype*>*>* map_vec_basictype;
  basictype* _basictype;
  set<string>* set_string;
  vector<evolution_line*>* vector_evolution_line;
  evolution_line* _evolution_line;
  vector<assignment*>* vector_assignment;
  bool_expression* _bool_expression;
  arithmetic_expression* _arithmetic_expression;
  bit_expression* _bit_expression;
  expression* _expression;
  basic_agent* _basic_agent;
  vector<protocol_line*>* vector_protocol_line;
  protocol_line* _protocol_line;
  unsigned char _unsigned_char;
  bool_value* _bool_value;
  modal_formula* _modal_formula;
  fairness_expression* _fairness_expression;
  pair<modal_formula*, modal_formula*>* dual_modal_formula;
  pair<string*, modal_formula*>* ID_modal_formula;
  pair<pair<string*, string*>*, modal_formula*>* ID_ID_modal_formula;
  pair<fairness_expression*, fairness_expression*>* dual_fairness_expression;
  pair<string*, fairness_expression*>* ID_fairness_expression;
  pair<pair<string*, string*>*, fairness_expression*>* ID_ID_fairness_expression;
  map<string, variable*>* map_string_variable;
}

%{
#include "mcmas-driver.hh"

  extern map < string, int > options;
  extern vector<string *> *string_table;
  extern vector<variable *> *variable_table;
  extern vector<bool_expression *> *logic_expression_table;
  extern vector<bool_expression *> *logic_expression_table1;
  extern map<string, basic_agent *> *is_agents;
  extern vector<basic_agent *> *agents;
  extern map<string, bool_expression *> *is_evaluation;
  extern bool_expression *is_istates;
  extern map<string, set<string> > *is_groups;
  extern vector<modal_formula> *is_formulae;
  extern vector<fairness_expression *> *is_fairness;

  extern int search_string_table(string *s);
  extern int search_variable_table(variable *v);
  extern int search_logic_expression_table(expression *e1, expression *e2);
  extern int search_logic_expression_table1(expression *e1, expression *e2);
%}

%token        END_OF_FILE      0 "end of file"
%token AGENT ACTIONS PROTOCOL EVOLUTION END LB RB LCB RCB LT GT IF EQ AND
%token ENVIRONMENT OBSVARS VARS BOOLEAN BTRUE BFALSE TO LE GE NEQ MINUS PLUS TIMES DIVIDE 
%token ACTION REDSTATES GREENSTATES FAIRNESS OTHER LOBSVARS 
%token OR NOT COLON COMMA DOT SEMICOLON EVALUATION INITSTATES GROUPS
%token FORMULAE LTLPREFIX CTLSPREFIX IMPLIES AG EG AX EX AF EF A E UNTIL K GK GCK O DK
%token MULTIASSIGNMENT SINGLEASSIGNMENT SEMANTICS
%token BITAND BITOR BITNOT BITXOR /* bit operators */
%token X F G 
%token LSB RSB QUESTION
%token <sval> ID "identifier"
%token <ival> NUMBER "number"

%left LB RB LT GT LE GE NEQ
%left ID
%right IMPLIES
%left OR BITOR BITXOR
%left AND BITAND
%left NOT BITNOT
%left EX AX EF AF EG AG E A UNTIL 
%left K GK GCK O DK X F G
%left EQ 
%left DOT

%type <map_vec_basictype> obsvardef
%type <map_vec_basictype> varidlist
%type <map_vec_basictype> vardef
%type <map_vec_basictype> envardef

%type <_basictype> onevardef
%type <ival> integer
%type <set_string> enumlist
%type <map_string_variable> lobsvarsdef
%type <map_string_variable> lobsvaridlist
%type <vector_evolution_line> envevdef
%type <vector_evolution_line> envevdeflist
%type <_evolution_line> envevline
%type <vector_assignment> boolresult
%type <vector_assignment> boolresult1
%type <_expression> expr1
%type <_expression> term1
%type <_expression> element1
%type <_expression> expr2
%type <_expression> term2
%type <_expression> element2
%type <_expression> expr3
%type <_expression> term3
%type <_expression> element3
%type <_expression> expr4
%type <_expression> term4
%type <_expression> factor4
%type <_expression> element4
%type <_expression> expr5
%type <_expression> term5
%type <_expression> factor5
%type <_expression> element5
%type <_expression> expr6
%type <_expression> term6
%type <_expression> factor6
%type <_expression> element6
%type <_bool_expression> enlboolcond
%type <_bool_expression> lboolcond
%type <_bool_expression> eboolcond
%type <_bool_expression> enrboolcond
%type <_bool_expression> rboolcond
%type <_bool_expression> enreddef
%type <_bool_expression> reddef
%type <_expression> varvalue1
%type <_expression> varvalue2
%type <_expression> varvalue3
%type <_expression> varvalue4
%type <_basic_agent> agent
%type <set_string> actiondef
%type <set_string> enactiondef
%type <set_string> actionidlist
%type <vector_protocol_line> enprotdef
%type <vector_protocol_line> protdef
%type <vector_protocol_line> enprotdeflist
%type <vector_protocol_line> protdeflist
%type <_protocol_line> enprotline
%type <_protocol_line> protline
%type <_protocol_line> otherbranch
%type <set_string> enabledidlist
%type <vector_evolution_line> evdef
%type <vector_evolution_line> evdeflist
%type <_evolution_line> evline
%type <_bool_expression> gboolcond
%type <_unsigned_char> logicop
%type <_bool_value> boolvalue
%type <_bool_expression> evaboolcond
%type <_bool_expression> isboolcond
%type <set_string> namelist
%type <sval> agentname
%type <_modal_formula> formula
%type <_modal_formula> ltlformula
%type <_modal_formula> pathformula
%type <_modal_formula> ctlsformula
%type <_modal_formula> terminalformula
%type <_fairness_expression> fformula

%type <ival> lobsprefix
%type <ival> lobssuffix
%type <ival> redprefix
%type <ival> redsuffix
%type <ival> envprefix
%type <ival> envsuffix
%type <ival> groupprefix
%type <ival> groupsuffix
%type <ival> actprefix
%type <ival> actsuffix
%type <ival> evprefix
%type <ival> evsuffix
%type <ival> iniprefix
%type <ival> inisuffix
%type <ival> forprefix
%type <ival> forsuffix
%type <ival> fairprefix
%type <ival> fairsuffix
%type <ival> evaprefix
%type <ival> evasuffix
%type <ival> protprefix
%type <ival> protsuffix
%type <ival> plprefix
%type <ival> plsuffix
%type <ival> obsprefix
%type <ival> obssuffix
%type <ival> varprefix
%type <ival> varsuffix
%type <ival> agprefix
%type <ival> agsuffix
%type <sval> atlprefix
%type <dual_modal_formula> untilprefix
%type <ID_modal_formula> epistemicprefix
%type <ID_modal_formula> gepistemicprefix
%type <ID_modal_formula> epistemicprefixltl
%type <ID_modal_formula> gepistemicprefixltl
%type <ID_modal_formula> epistemicprefixctls
%type <ID_modal_formula> gepistemicprefixctls
%type <dual_fairness_expression> untilprefixfair
%type <ID_fairness_expression> epistemicprefixfair
%type <ID_fairness_expression> gepistemicprefixfair
%type <ival> gplprefix
%type <ival> gplsufffix


%printer    { debug_stream () << *$$; } "identifier"
%destructor { delete $$; } "identifier"
%destructor { delete $$; } obsvardef
%destructor { delete $$; } varidlist
%destructor { delete $$; } onevardef
%destructor { delete $$; } enumlist
%destructor { delete $$; } vardef
%destructor { delete $$; } envardef
%destructor { delete $$; } envevdef
%destructor { delete $$; } envevdeflist
%destructor { delete $$; } envevline
%destructor { delete $$; } boolresult
%destructor { delete $$; } lboolcond
%destructor { delete $$; } eboolcond
%destructor { delete $$; } rboolcond
%destructor { delete $$; } reddef
%destructor { delete $$; } varvalue1
%destructor { delete $$; } varvalue2
%destructor { delete $$; } varvalue3
%destructor { delete $$; } varvalue4
%destructor { delete $$; } agent
%destructor { delete $$; } actiondef
%destructor { delete $$; } enactiondef
%destructor { delete $$; } actionidlist
%destructor { delete $$; } protdef
%destructor { delete $$; } enprotdef
%destructor { delete $$; } protdeflist
%destructor { delete $$; } protline
%destructor { delete $$; } enabledidlist
%destructor { delete $$; } evdef
%destructor { delete $$; } evdeflist
%destructor { delete $$; } evline
%destructor { delete $$; } gboolcond
%destructor { delete $$; } boolvalue
%destructor { delete $$; } evaboolcond
%destructor { delete $$; } isboolcond
%destructor { delete $$; } namelist
%destructor { delete $$; } agentname
%destructor { delete $$; } formula

%printer    { debug_stream () << $$; } "number"

%%
%start eis;
eis: is
| semantics is
;

semantics: SEMANTICS EQ MULTIASSIGNMENT SEMICOLON {
    options["smv"] = 0;
 }
| SEMANTICS EQ SINGLEASSIGNMENT SEMICOLON  {
    options["smv"] = 1;
 }
| error {
  driver.syntax_error = true;
 }
;

is: environment agents evaluation istates groups fairness formulae
| environment agents evaluation istates groups formulae
| environment agents evaluation istates fairness formulae
| environment agents evaluation istates formulae
| agents evaluation istates groups fairness formulae {
  basic_agent *env = new basic_agent((*string_table)[0], NULL, new map<string, basictype *>, new vector<basictype *>,
				     new map<string, basictype *>, new vector<basictype *>, NULL, new set<string>, 
				     new vector<protocol_line*>, new vector<evolution_line *>);
  (*is_agents)["Environment"] = env;
  agents->insert(agents->begin(), env);
 }
| agents evaluation istates groups formulae  {
  basic_agent *env = new basic_agent((*string_table)[0], NULL, new map<string, basictype *>, new vector<basictype *>, 
				     new map<string, basictype *>, new vector<basictype *>, NULL, new set<string>, 
				     new vector<protocol_line*>, new vector<evolution_line *>);
  (*is_agents)["Environment"] = env;
  agents->insert(agents->begin(), env);
 }
| agents evaluation istates fairness formulae  {
  basic_agent *env = new basic_agent((*string_table)[0], NULL, new map<string, basictype *>, new vector<basictype *>, 
				     new map<string, basictype *>, new vector<basictype *>, NULL, new set<string>, 
				     new vector<protocol_line*>, new vector<evolution_line *>);
  (*is_agents)["Environment"] = env;
  agents->insert(agents->begin(), env);
 }
| agents evaluation istates formulae {
  basic_agent *env = new basic_agent((*string_table)[0], NULL, new map<string, basictype *>, new vector<basictype *>, 
				     new map<string, basictype *>, new vector<basictype *>, NULL, new set<string>, 
				     new vector<protocol_line*>, new vector<evolution_line *>);
  (*is_agents)["Environment"] = env;
  agents->insert(agents->begin(), env);
 };


/* definition of agent Enviroment */
envprefix: AGENT ENVIRONMENT {
  $$ = 1;
 }
| error ENVIRONMENT {
  $$ = 0;
  driver.syntax_error = true;
 }
| AGENT error {
  $$ = 0;
  driver.syntax_error = true;
 }
| error {
  $$ = 0;
  driver.syntax_error = true;
 };
envsuffix: END AGENT {
  $$ = 1;
 }
| error AGENT {
  $$ = 0;
  driver.syntax_error = true;
 }
| END error {
  $$ = 0;
  driver.syntax_error = true;
 }
| error {
  $$ = 0;
  driver.syntax_error = true;
 };

environment: envprefix obsvardef envardef enreddef enactiondef enprotdef envevdef envsuffix {
  if($1==1 && $2!=NULL && $3!=NULL && $5!=NULL && $6!=NULL && $7!=NULL && $8==1) { // redstates is NULL if no red state at all
    basic_agent *env = new basic_agent((*string_table)[0], NULL, $2->first, $2->second, $3->first, $3->second, $4, $5, $6, $7);
    (*is_agents)["Environment"] = env;
    agents->push_back(env);
  }
 }
| envprefix obsvardef envardef enactiondef enprotdef envevdef envsuffix {
  if($1==1 && $2!=NULL && $3!=NULL && $4!=NULL && $5!=NULL && $6!=NULL && $7==1) { // redstates is NULL if no red state at all
    basic_agent *env = new basic_agent((*string_table)[0], NULL, $2->first, $2->second, $3->first, $3->second, NULL, $4, $5, $6);
    (*is_agents)["Environment"] = env;
    agents->push_back(env);
  }
 }
| envprefix envardef enreddef enactiondef enprotdef envevdef envsuffix {
  if($1==1 && $2!=NULL && $4!=NULL && $5!=NULL && $6!=NULL && $7==1) { // redstates is NULL if no red state at all
    basic_agent *env = new basic_agent((*string_table)[0], NULL, new map<string, basictype *>, new vector<basictype *>, $2->first, $2->second, $3, $4, $5, $6);
    (*is_agents)["Environment"] = env;
    agents->push_back(env);
  }
 }
| envprefix envardef enactiondef enprotdef envevdef envsuffix {
  if($1==1 && $2!=NULL && $3!=NULL && $4!=NULL && $5!=NULL && $6==1) { // redstates is NULL if no red state at all
    basic_agent *env = new basic_agent((*string_table)[0], NULL, new map<string, basictype *>, new vector<basictype *>, $2->first, $2->second, NULL, $3, $4, $5);
    (*is_agents)["Environment"] = env;
    agents->push_back(env);
  }
 }
| envprefix obsvardef enreddef enactiondef enprotdef envevdef envsuffix {
  if($1==1 && $2!=NULL && $4!=NULL && $5!=NULL && $6!=NULL && $7==1) { // redstates is NULL if no red state at all
    basic_agent *env = new basic_agent((*string_table)[0], NULL, $2->first, $2->second, new map<string, basictype *>, new vector<basictype *>, $3, $4, $5, $6);
    (*is_agents)["Environment"] = env;
    agents->push_back(env);
  }
 }
| envprefix obsvardef enactiondef enprotdef envevdef envsuffix {
  if($1==1 && $2!=NULL && $3!=NULL && $4!=NULL && $5!=NULL && $6==1) { // redstates is NULL if no red state at all
    basic_agent *env = new basic_agent((*string_table)[0], NULL, $2->first, $2->second, new map<string, basictype *>, new vector<basictype *>, NULL, $3, $4, $5);
    (*is_agents)["Environment"] = env;
    agents->push_back(env);
  }
 }
| envprefix enreddef enactiondef enprotdef envevdef envsuffix {
  if($1==1 && $3!=NULL && $4!=NULL && $5!=NULL && $6==1) { // redstates is NULL if no red state at all
    basic_agent *env = new basic_agent((*string_table)[0], NULL, new map<string, basictype *>, new vector<basictype *>, 
				       new map<string, basictype *>, new vector<basictype *>, $2, $3, $4, $5);
    (*is_agents)["Environment"] = env;
    agents->push_back(env);
  }
 }
| envprefix enactiondef enprotdef envevdef envsuffix {
  if($1==1 && $2!=NULL && $3!=NULL && $4!=NULL && $5==1) { // redstates is NULL if no red state at all
    basic_agent *env = new basic_agent((*string_table)[0], NULL, new map<string, basictype *>, new vector<basictype *>, 
				       new map<string, basictype *>, new vector<basictype *>, NULL, $2, $3, $4);
    (*is_agents)["Environment"] = env;
    agents->push_back(env);
  }
 }
| error {
  driver.syntax_error = true;
  };

/* definition of observable variables */
obsprefix: OBSVARS COLON {
  $$ = 1;
 }
| error COLON {
  $$ = 0;
  driver.syntax_error = true;
 }
| OBSVARS error {
  $$ = 0;
  driver.syntax_error = true;
 }
| error {
  $$ = 0;
  driver.syntax_error = true;
 };
obssuffix: END OBSVARS {
  $$ = 1;
 }
| error OBSVARS {
  $$ = 0;
  driver.syntax_error = true;
 }
| END error {
  $$ = 0;
  driver.syntax_error = true;
 }
| error {
  $$ = 0;
  driver.syntax_error = true;
 };
obsvardef: obsprefix varidlist obssuffix {
  if($1==1 && $3==1)
    $$ = $2;
  else
    $$ = NULL;
 }
| obsprefix obssuffix {
  if($1==1 && $2==1) {
    map<string, basictype *>* a = new map<string, basictype *>;
    vector<basictype *>* b = new vector<basictype *>;
    $$ = new pair<map<string, basictype *>*, vector<basictype *>* >(a, b);
  } else
    $$ = NULL;
 };
varidlist: onevardef SEMICOLON {
  if($1!=NULL) {
    map<string, basictype *>* a = new map<string, basictype *>;
    vector<basictype *>* b = new vector<basictype *>;
    $$ = new pair<map<string, basictype *>*, vector<basictype *>* >(a, b);
    (*a)[$1->get_name()] = $1;
    b->push_back($1);
  } else
    $$ = NULL;
 }
| onevardef error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
 }
| varidlist onevardef SEMICOLON {
  if($1!=NULL && $2!=NULL) {
    if($1->first->find($2->get_name()) != $1->first->end()) {
			if (options["quiet"] == 0)			
				cout << "warning: type " << $2->get_name() << " has already been defined." << endl;
    } else { 
      (*($1->first))[$2->get_name()] = $2;
      $1->second->push_back($2);
      $$ = $1;
    }
  } else
    $$ = NULL;
 }
| varidlist onevardef error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
  USE($2);
 }
| error {
  $$ = NULL;
  driver.syntax_error = true;
  };

onevardef: ID COLON BOOLEAN {
  if($1!=NULL) {
    int i = search_string_table($1);
    if(i>=0) {
      $$ = new basictype((*string_table)[i]);
      free($1);
    } else {
      $$ = new basictype($1);
      string_table->push_back($1);
    }
  } else
    $$ = NULL;
 }
| ID COLON error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
 }
| ID error BOOLEAN {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
 }
| ID COLON integer TO integer {
  if($1!=NULL) {
    if($3>$5)
      cout << "Error: the lower bound " << $3 << " is greater than the upper bound " << $5 << endl;
    int i = search_string_table($1);
    if(i>=0) {
      $$ = new rangedint((*string_table)[i], $3, $5);
      free($1);
    } else {
      $$ = new rangedint($1, $3, $5);
      string_table->push_back($1);
    }
  }
  else
    $$ = NULL;
 }
| ID error integer TO integer {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
 }
| ID COLON integer error integer {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
 }
| ID error integer error integer {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
 }
| ID COLON LCB enumlist RCB {
  if($1!=NULL && $4!=NULL) {
    int i = search_string_table($1);
    if(i>=0) {
      $$ = new enumerate((*string_table)[i], $4);
      free($1);
    } else {
      $$ = new enumerate($1, $4);
      string_table->push_back($1);
    }
  } else
    $$ = NULL;
 }
| ID error enumlist RCB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
  USE($3);
 }
| ID COLON LCB enumlist error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
  USE($4);
 }
| ID error enumlist error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
  USE($3);
 }
| error {
  $$ = NULL;
  driver.syntax_error = true;
 }; 
enumlist: ID {
  if($1!=NULL) {
    $$ = new set<string>;
    $$->insert(*$1);
    free ($1);
  } else
    $$ = NULL;
 }
| enumlist COMMA ID {
  if($1!=NULL && $3!=NULL) {
    pair<set<string>::iterator, bool> ret = $1->insert(*$3);
    if(!ret.second && options["quiet"] == 0)
      cout << "warning: " << *$3 << " has been defined for the enum type." << endl;
    $$ = $1;
    free ($3);
  } else
    $$ = NULL;
	USE($1);
 }
| enumlist error ID {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
  USE($3);
 }
| error {
  $$ = NULL;
  driver.syntax_error = true;
  };
integer: NUMBER {
  $$ = $1;
 }
| MINUS NUMBER {
  $$ = 0-$2;
 }
| error NUMBER {
  $$ = -1;
  driver.syntax_error = true;
 }
| error {
  $$ = -1;
  driver.syntax_error = true;
  };
/* definition of non-observable variables in Environment.
   can be null*/
varprefix: VARS COLON {
  $$ = 1;
 }
| error COLON {
  $$ = 0;
  driver.syntax_error = true;
 }
| VARS error {
  $$ = 0;
  driver.syntax_error = true;
 }
| error {
  $$ = 0;
  driver.syntax_error = true;
 };
varsuffix: END VARS {
  $$ = 1;
 }
| error VARS {
  $$ = 0;
  driver.syntax_error = true;
 }
| END error {
  $$ = 0;
  driver.syntax_error = true;
 }
| error {
  $$ = 0;
  driver.syntax_error = true;
 };
envardef: varprefix varidlist varsuffix {
  if($1==1 && $3==1)
    $$ = $2;
  else
    $$ = NULL;
 }
| varprefix varsuffix {
  if($1==1 && $2==1) {
    map<string, basictype *>* a = new map<string, basictype *>;
    vector<basictype *>* b = new vector<basictype *>;
    $$ = new pair<map<string, basictype *>*, vector<basictype *>* >(a, b);
  } else
    $$ = NULL;
 } 
| error {
  $$ = NULL;
  driver.syntax_error = true;
  };

/* definition of non-observable variables */
vardef: varprefix varidlist varsuffix {
  if($1==1 && $3==1)
    $$ = $2;
  else
    $$ = NULL;
 } 
| error {
  $$ = NULL;
  driver.syntax_error = true;
  };

/* Definition of red states */
redprefix: REDSTATES COLON {
  $$ = 1;
 }
| REDSTATES error {
  $$ = 0;
  driver.syntax_error = true;
 }
| error COLON {
  $$ = 0;
  driver.syntax_error = true;
 }
| error {
  $$ = 0;
  driver.syntax_error = true;
 };
redsuffix: END REDSTATES {
  $$ = 1;
 }
| error REDSTATES {
  $$ = 0;
  driver.syntax_error = true;
 }
| END error {
  $$ = 0;
  driver.syntax_error = true;
 }
| error {
  $$ = 0;
  driver.syntax_error = true;
 };

enreddef: redprefix enrboolcond redsuffix {
  if($1==1 && $3==1)
    $$ = $2;
  else
    $$ = NULL;
 } 
| redprefix redsuffix {
  $$ = NULL; 
 }
| error {
  $$ = NULL;
  driver.syntax_error = true;
  };

reddef: redprefix rboolcond redsuffix {
  if($1==1 && $3==1)
    $$ = $2;
  else
    $$ = NULL;
 } 
| redprefix redsuffix {
  $$ = NULL; 
 }
| error {
  $$ = NULL;
  driver.syntax_error = true;
  };

enrboolcond: enlboolcond SEMICOLON {
  $$ = $1;
  }
| enlboolcond error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
  }
| error {
  $$ = NULL;
  driver.syntax_error = true;
  };

rboolcond: lboolcond SEMICOLON {
  $$ = $1;
  }
| lboolcond error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
  }
| error {
  $$ = NULL;
  driver.syntax_error = true;
  };

/* Evolution definition for Environment.
   can be null. */
evprefix: EVOLUTION COLON {
  $$ = 1;
 }
| error COLON {
  $$ = 0;
  driver.syntax_error = true;
 }
| EVOLUTION error {
  $$ = 0;
  driver.syntax_error = true;
 }
| error {
  $$ = 0;
  driver.syntax_error = true;
 };
evsuffix: END EVOLUTION {
  $$ = 1;
 }
| error EVOLUTION {
  $$ = 0;
  driver.syntax_error = true;
 }
| END error {
  $$ = 0;
  driver.syntax_error = true;
 }
| error {
  $$ = 0;
  driver.syntax_error = true;
 };
envevdef: evprefix envevdeflist evsuffix {
  if($1==1 && $3==1)
    $$ = $2;
  else
    $$ = NULL;
 }
| evprefix evsuffix {
  if($1==1 && $2==1)
    $$ = new vector<evolution_line *>;
  else
    $$ = NULL;
 };
envevdeflist: envevline {
  if($1!=NULL) {
    $$ = new vector<evolution_line *>;
    $$->push_back($1);
  } else
    $$ = NULL;
 }
| envevdeflist envevline {
  if($1!=NULL && $2!=NULL) {
    $1->push_back($2);
    $$ = $1;
  } else
    $$ = NULL;
 }
| error {
  $$ = NULL;
  driver.syntax_error = true;
  };
envevline: boolresult IF eboolcond SEMICOLON {
  if($1!=NULL && $3!=NULL) 
    $$ = new evolution_line($1, $3);
  else
    $$ = NULL;
 }
| error {
  $$ = NULL;
  driver.syntax_error = true;
  };
boolresult: LB boolresult RB {
  $$ = $2;
 }
| boolresult AND boolresult {
  if($1!=NULL && $3!=NULL) {
    $$ = $1;
    vector<assignment*>::iterator i;
    for(i=$3->begin(); i != $3->end(); i++)
      $$->push_back(*i);
  } else
    $$ = NULL;
 }
| ID EQ expr4 {
  if($1!=NULL && $3!=NULL) {
    assignment *a;
    int i = search_string_table($1);
    if(i>=0) {
      a = new assignment((*string_table)[i], $3);
      free($1);
    } else {
      a = new assignment($1, $3);
      string_table->push_back($1);
    }
    $$ = new vector<assignment*>;
    $$->push_back(a);
  } else
    $$ = NULL;
 }
| error {
  $$ = NULL;
  driver.syntax_error = true;
  }; 

boolresult1: LB boolresult1 RB {
  $$ = $2;
 }
| boolresult1 AND boolresult1 {
  if($1!=NULL && $3!=NULL) {
    $$ = $1;
    vector<assignment*>::iterator i;
    for(i=$3->begin(); i != $3->end(); i++)
      $$->push_back(*i);
  } else
    $$ = NULL;
 }
| ID EQ expr5 {
  if($1!=NULL && $3!=NULL) {
    assignment *a;
    int i = search_string_table($1);
    if(i>=0) {
      a = new assignment((*string_table)[i], $3);
      free($1);
    } else {
      a = new assignment($1, $3);
      string_table->push_back($1);
    }
    $$ = new vector<assignment*>;
    $$->push_back(a);
  } else
    $$ = NULL;
 }
| error {
  $$ = NULL;
  driver.syntax_error = true;
  }; 

agents: agent {
  if($1!=NULL) {
    (*is_agents)[$1->get_name()] = $1;
    agents->push_back($1);
  } 
 }
| agents agent {
  if($2!=NULL) {
    if(is_agents->find($2->get_name()) != is_agents->end()) {
			if (options["quiet"] == 0)
				cout << "warning: agent " << $2->get_name() << " already exists." << endl;
    } else
      agents->push_back($2);
    (*is_agents)[$2->get_name()] = $2;
  }
 }
| error {
  driver.syntax_error = true;
  };

agprefix: AGENT  {
  $$ = 1;
 }
| error {
  $$ = 0;
  driver.syntax_error = true;
 };
agsuffix: END AGENT {
  $$ = 1;
 }
| error AGENT {
  $$ = 0;
  driver.syntax_error = true;
 }
| END error {
  $$ = 0;
  driver.syntax_error = true;
 }
| error {
  $$ = 0;
  driver.syntax_error = true;
 };

agent: agprefix ID vardef reddef actiondef protdef evdef agsuffix {
  if($1==1 && $2!=NULL && $3!=NULL && 
     $5!=NULL && $6!=NULL && $7!=NULL && $8==1) {// redstates is NULL if no red state at all
    int i = search_string_table($2);
    if(i>=0) {
      $$ = new basic_agent((*string_table)[i], NULL, NULL, NULL, $3->first, $3->second, $4, $5, $6, $7);
      free($2);
    } else {
      $$ = new basic_agent($2, NULL, NULL, NULL, $3->first, $3->second, $4, $5, $6, $7);
      string_table->push_back($2);
    }
  } else
    $$ = NULL;
 } 
| agprefix ID vardef actiondef protdef evdef agsuffix {
  if($1==1 && $2!=NULL && $3!=NULL && 
     $4!=NULL && $5!=NULL && $6!=NULL && $7==1) {// redstates is NULL if no red state at all
    int i = search_string_table($2);
    if(i>=0) {
      $$ = new basic_agent((*string_table)[i], NULL, NULL, NULL, $3->first, $3->second, NULL, $4, $5, $6);
      free($2);
    } else {
      $$ = new basic_agent($2, NULL, NULL, NULL, $3->first, $3->second, NULL, $4, $5, $6);
      string_table->push_back($2);
    }
  } else
    $$ = NULL;
 } 
| agprefix ID lobsvarsdef vardef reddef actiondef protdef evdef agsuffix {
  if($1==1 && $2!=NULL && $4!=NULL && 
     $6!=NULL && $7!=NULL && $8!=NULL && $9==1) {// redstates is NULL if no red state at all
    int i = search_string_table($2);
    if(i>=0) {
      $$ = new basic_agent((*string_table)[i], $3, NULL, NULL, $4->first, $4->second, $5, $6, $7, $8);
      free($2);
    } else {
      $$ = new basic_agent($2, $3, NULL, NULL, $4->first, $4->second, $5, $6, $7, $8);
      string_table->push_back($2);
    }
  } else
    $$ = NULL;
 } 
| agprefix ID lobsvarsdef vardef actiondef protdef evdef agsuffix {
  if($1==1 && $2!=NULL && 
     $4!=NULL && $5!=NULL && $6!=NULL && $7!=NULL && $8==1) {// redstates is NULL if no red state at all
    int i = search_string_table($2);
    if(i>=0) {
      $$ = new basic_agent((*string_table)[i], $3, NULL, NULL, $4->first, $4->second, NULL, $5, $6, $7);
      free($2);
    } else {
      $$ = new basic_agent($2, $3, NULL, NULL, $4->first, $4->second, NULL, $5, $6, $7);
      string_table->push_back($2);
    }
  } else
    $$ = NULL;
 } 
| error {
  $$ = NULL;
  driver.syntax_error = true;
  };

/* local observable variable */
lobsprefix: LOBSVARS EQ LCB {
  $$ = 1;
 }
| error EQ LCB {
  $$ = 0;
  driver.syntax_error = true;
 }
| LOBSVARS error LCB {
  $$ = 0;
  driver.syntax_error = true;
 }
| LOBSVARS EQ error {
  $$ = 0;
  driver.syntax_error = true;
 }
| error LCB {
  $$ = 0;
  driver.syntax_error = true;
 }
| LOBSVARS error {
  $$ = 0;
  driver.syntax_error = true;
 }
| error EQ error {
  $$ = 0;
  driver.syntax_error = true;
 }
| error {
  $$ = 0;
  driver.syntax_error = true;
 };
lobssuffix: RCB SEMICOLON {
  $$ = 1;
 }
| RCB error {
  $$ = 0;
  driver.syntax_error = true;
 }
| error SEMICOLON {
  $$ = 0;
  driver.syntax_error = true;
 }
| error {
  $$ = 0;
  driver.syntax_error = true;
 };
lobsvarsdef: lobsprefix lobsvaridlist lobssuffix {
  if($1==1 && $3==1)
    $$ = $2;
  else
    $$ = NULL;
 }
| lobsprefix lobssuffix {
  $$ = NULL;
 }
| error {
  $$ = NULL;
  driver.syntax_error = true;
  };
lobsvaridlist: ID {
  if($1!=NULL) {
    $$ = new map<string, variable *>;
    if($$->find(*$1) != $$->end() && options["quiet"] == 0)
      cout << "warning: local observable variable " << *$1 << " has already been defined." << endl;
    int i = search_string_table($1);
    if(i>=0) {
      (*$$)[*$1] = new variable((*string_table)[0], (*string_table)[i]);
      free($1);
    } else {
      (*$$)[*$1] = new variable((*string_table)[0], $1);
      string_table->push_back($1);
    }
  } else
    $$ = NULL;
 }
| lobsvaridlist COMMA ID {
  if($1!=NULL && $3!=NULL) {
    if($1->find(*$3) != $$->end() && options["quiet"] == 0)
      cout << "warning: local observable variable " << *$3 << " has already been defined." << endl;
    int i = search_string_table($3);
    if(i>=0) {
      (*$1)[*$3] = new variable((*string_table)[0], (*string_table)[i]);
      free($3);
    } else {
      (*$1)[*$3] = new variable((*string_table)[0], $3);
      string_table->push_back($3);
    }
    $$ = $1;
  } else
    $$ = NULL;
 }
| lobsvaridlist error ID {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
  USE($3);
 }
| error {
  $$ = NULL;
  driver.syntax_error = true;
  };

/* ACTIONS in Environment.
   can be null */
actprefix: ACTIONS EQ LCB {
  $$ = 1;
 }
| error EQ LCB {
  $$ = 0;
  driver.syntax_error = true;
 }
| ACTIONS error LCB {
  $$ = 0;
  driver.syntax_error = true;
 }
| ACTIONS EQ error {
  $$ = 0;
  driver.syntax_error = true;
 }
| error LCB {
  $$ = 0;
  driver.syntax_error = true;
 }
| ACTIONS error {
  $$ = 0;
  driver.syntax_error = true;
 }
| error EQ error {
  $$ = 0;
  driver.syntax_error = true;
 }
| error {
  $$ = 0;
  driver.syntax_error = true;
 };
actsuffix: RCB SEMICOLON {
  $$ = 1;
 }
| RCB error {
  $$ = 0;
  driver.syntax_error = true;
 }
| error SEMICOLON {
  $$ = 0;
  driver.syntax_error = true;
 }
| error {
  $$ = 0;
  driver.syntax_error = true;
 };
enactiondef: actprefix actionidlist actsuffix {
  if($1==1 && $3==1)
    $$ = $2;
  else
    $$ = NULL;
 }
| actprefix actsuffix {
  if($1==1 && $2==1)
    $$ = new set<string>;
  else
    $$ = NULL;
 }
| error {
  $$ = NULL;
  driver.syntax_error = true;
  };

/* ACTIONS */
actiondef: actprefix actionidlist actsuffix {
  if($1==1 && $3==1) 
    $$ = $2;
  else
    $$ = NULL;
 }
| error {
  $$ = NULL;
  driver.syntax_error = true;
  };
actionidlist: ID {
  if($1!=NULL) {
    $$ = new set<string>;
    $$->insert(*$1);
    free ($1);
  } else
    $$ = NULL;
 }
| actionidlist COMMA ID {
  if($1!=NULL && $3!=NULL) {
    pair<set<string>::iterator, bool> ret = $1->insert(*$3);
    if(!ret.second && options["quiet"] == 0)
      cout << "warning: action " << *$3 << " has been defined." << endl;
    $$ = $1;
    free ($3);
  } else
    $$ = NULL;
 }
| actionidlist error ID {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
  USE($3);
 }
| error {
  $$ = NULL;
  driver.syntax_error = true;
  };

/* PROTOCOL in Environment.
   can be null */
protprefix: PROTOCOL COLON {
  $$ = 1;
 }
| error COLON {
  $$ = 0;
  driver.syntax_error = true;
 }
| PROTOCOL error {
  $$ = 0;
  driver.syntax_error = true;
 }
| error {
  $$ = 0;
  driver.syntax_error = true;
 };
protsuffix: END PROTOCOL {
  $$ = 1;
 }
| error PROTOCOL {
  $$ = 0;
  driver.syntax_error = true;
 }
| END error {
  $$ = 0;
  driver.syntax_error = true;
 }
| error {
  $$ = 0;
  driver.syntax_error = true;
 };

enprotdef: protprefix enprotdeflist protsuffix {
  if($1==1 && $3==1) 
    $$ = $2;
  else
    $$ = NULL;
 }
| protprefix enprotdeflist otherbranch protsuffix {
  if($1==1 && $4==1) {
    $$ = $2;
    $$->push_back($3);
  }
  else
    $$ = NULL;
 }
| protprefix otherbranch protsuffix {
  if($1==1 && $3==1) {
    $$ = new vector<protocol_line*>;
    $$->push_back($2);;
  }
  else
    $$ = NULL;
 }
| protprefix protsuffix {
  if($1==1 && $2==1) 
    $$ = new vector<protocol_line*>;
  else
    $$ = NULL;
 }
| error {
  $$ = NULL;
  driver.syntax_error = true;
  };

/* PROTOCOL */
protdef: protprefix  protdeflist  protsuffix {
  if($1==1 && $3==1) 
    $$ = $2;
  else
    $$ = NULL;
 }
| protprefix protdeflist otherbranch protsuffix {
  if($1==1 && $4==1) {
    $$ = $2;
    $$->push_back($3);
  }
  else
    $$ = NULL;
 }
| protprefix otherbranch protsuffix {
  if($1==1 && $3==1) {
    $$ = new vector<protocol_line*>;
    $$->push_back($2);;
  }
  else
    $$ = NULL;
 }
| error {
  $$ = NULL;
  driver.syntax_error = true;
  };

enprotdeflist: enprotline {
  if($1!=NULL) {
    $$ = new vector<protocol_line*>;
    $$->push_back($1);
  } else
    $$ = NULL;
 }
| enprotdeflist enprotline {
  if($1!=NULL && $2!=NULL) {
    $1->push_back($2);
    $$ = $1;
  } else
    $$ = NULL;
 }
| error {
  $$ = NULL;
  driver.syntax_error = true;
  };

protdeflist: protline {
  if($1!=NULL) {
    $$ = new vector<protocol_line*>;
    $$->push_back($1);
  } else
    $$ = NULL;
 }
| protdeflist protline {
  if($1!=NULL && $2!=NULL) {
    $1->push_back($2);
    $$ = $1;
  } else
    $$ = NULL;
 }
| error {
  $$ = NULL;
  driver.syntax_error = true;
  };

plprefix: COLON LCB {
  $$ = 1;
 }
| error LCB {
  $$ = 0;
  driver.syntax_error = true;
 }
| COLON error {
  $$ = 0;
  driver.syntax_error = true;
 }
| error {
  $$ = 0;
  driver.syntax_error = true;
 };
plsuffix: RCB SEMICOLON {
  $$ = 1;
 }
| error SEMICOLON {
  $$ = 0;
  driver.syntax_error = true;
 }
| RCB error {
  $$ = 0;
  driver.syntax_error = true;
 }
| error {
  $$ = 0;
  driver.syntax_error = true;
 };
enprotline: enlboolcond plprefix enabledidlist plsuffix {
  if($1!=NULL && $2==1 && $3!=NULL && $4==1) 
    $$ = new protocol_line($1, $3);
  else
    $$ = NULL;
 }
| error {
  $$ = NULL;
  driver.syntax_error = true;
  };

protline: lboolcond plprefix enabledidlist plsuffix {
  if($1!=NULL && $2==1 && $3!=NULL && $4==1) 
    $$ = new protocol_line($1, $3);
  else
    $$ = NULL;
 }
| error {
  $$ = NULL;
  driver.syntax_error = true;
  };

otherbranch: OTHER plprefix enabledidlist plsuffix {
  if($2==1 && $3!=NULL && $4==1) 
    $$ = new protocol_line(new bool_expression(), $3);
  else
    $$ = NULL;
 }
| error plprefix enabledidlist plsuffix {
  $$ = NULL;
  driver.syntax_error = true;
  USE($3);
 };

enabledidlist: ID {
  if($1!=NULL) {
    $$ = new set<string>;
    $$->insert(*$1);
    free ($1);
  } else
    $$ = NULL;
 }
| enabledidlist COMMA ID {
  if($1!=NULL && $3!=NULL) {
    pair<set<string>::iterator, bool> ret = $1->insert(*$3);
    if(!ret.second && options["quiet"] == 0)
      cout << "warning: action " << *$3 << " is repeated." << endl;
    $$ = $1;
    free ($3);
  } else
    $$ = NULL;
 }
| enabledidlist error ID {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
  USE($3);
 }
| error {
  $$ = NULL;
  driver.syntax_error = true;
  };


/* EVOLUTION DEFINITION */
evdef: evprefix evdeflist evsuffix {
  if($1==1 && $3==1)
    $$ = $2;
  else
    $$ = NULL;
}
| error {
  $$ = NULL;
  driver.syntax_error = true;
  };
evdeflist: evline {
  if($1!=NULL) {
    $$ = new vector<evolution_line*>;
    $$->push_back($1);
  } else
    $$ = NULL;
 }
| evdeflist evline {
  if($1!=NULL && $2!=NULL) {
    $1->push_back($2);
    $$ = $1;
  } else
    $$ = NULL;
 }
| error {
  $$ = NULL;
  driver.syntax_error = true;
  };

evline: boolresult1 IF gboolcond SEMICOLON {
  if($1!=NULL)
    $$ = new evolution_line($1, $3);
  else
    $$ = NULL;
 }
| boolresult1 error gboolcond SEMICOLON {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
  USE($3);
 }
| boolresult1 IF gboolcond error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
  USE($3);
 }
| boolresult1 error gboolcond error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
  USE($3);
 }
| error {
  $$ = NULL;
  driver.syntax_error = true;
  };

enlboolcond: LB enlboolcond RB { 
  $$ = $2; 
 }
| error enlboolcond RB { 
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| LB enlboolcond error { 
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| error enlboolcond error { 
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| enlboolcond AND enlboolcond {
  if($1!=NULL && $3!=NULL)
    $$ = new bool_expression(1, $1, $3);
  else
    $$ = NULL;
 }
| enlboolcond OR enlboolcond {
  if($1!=NULL && $3!=NULL)
    $$ = new bool_expression(2, $1, $3);
  else
    $$ = NULL;
 }
| enlboolcond error enlboolcond {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
  USE($3);
 }
| NOT enlboolcond {
  if($2!=NULL)
    $$ = new bool_expression(3, $2);
  else
    $$ = NULL;
 }
| error enlboolcond {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| expr4 logicop expr4 {
  if($1!=NULL && $3!=NULL) {
    logic_expression *expr = new logic_expression($2, $1, $3);
    $$ = new bool_expression(0,  expr);
  } else
    $$ = NULL;
 }
| error {
  $$ = NULL;
  driver.syntax_error = true;
  };

lboolcond: LB lboolcond RB { 
  $$ = $2; 
 }
| error lboolcond RB { 
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| LB lboolcond error { 
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| error lboolcond error { 
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| lboolcond AND lboolcond {
  if($1!=NULL && $3!=NULL)
    $$ = new bool_expression(1, $1, $3);
  else
    $$ = NULL;
 }
| lboolcond OR lboolcond {
  if($1!=NULL && $3!=NULL)
    $$ = new bool_expression(2, $1, $3);
  else
    $$ = NULL;
 }
| lboolcond error lboolcond {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
  USE($3);
 }
| NOT lboolcond {
  if($2!=NULL)
    $$ = new bool_expression(3, $2);
  else
    $$ = NULL;
 }
| error lboolcond {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| expr5 logicop expr5 {
  if($1!=NULL && $3!=NULL) {
    logic_expression *expr = new logic_expression($2, $1, $3);
    $$ = new bool_expression(0,  expr);
  } else
    $$ = NULL;
 }
| error {
  $$ = NULL;
  driver.syntax_error = true;
 };

expr1: expr1 PLUS term1 {
  if($1!=NULL && $3!=NULL) {
    $$ = new arithmetic_expression(5, $1, $3);
  } else
    $$ = NULL;
 }
| expr1 MINUS term1 {
  if($1!=NULL && $3!=NULL) {
    $$ = new arithmetic_expression(6, $1, $3);
  } else
    $$ = NULL;
 }
| expr1 error term1 {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
 }
| term1 {
  $$ = $1;
  };
term1: term1 TIMES element1 {
  if($1!=NULL && $3!=NULL) {
    $$ = new arithmetic_expression(7, $1, $3);
  } else
    $$ = NULL;
 }
| term1 DIVIDE element1 {
  if($1!=NULL && $3!=NULL) {
    $$ = new arithmetic_expression(8, $1, $3);
  } else
    $$ = NULL;
 }
| term1 error element1 {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
 }
| element1 {
  $$ = $1;
  };
element1: LB expr1 RB {
  $$ = $2;
  }
| error expr1 RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| LB expr1 error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| varvalue1  {
  $$ = $1;
  };

expr4: expr4 BITOR term4 {
  if($1!=NULL && $3!=NULL) {
    $$ = new bit_expression(10, $1, $3);
  } else
    $$ = NULL;
 }
| expr4 BITXOR term4 {
  if($1!=NULL && $3!=NULL) {
    $$ = new bit_expression(12, $1, $3);
  } else
    $$ = NULL;
 }
| expr4 error term4 {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
 }
| term4 {
  $$ = $1;
  };
term4: term4 BITAND factor4 {
  if($1!=NULL && $3!=NULL) {
    $$ = new bit_expression(9, $1, $3);
  } else
    $$ = NULL;
 }
| term4 error factor4 {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
 }
| factor4 {
  $$ = $1;
  };
factor4: BITNOT element4 {
  if($2!=NULL) {
    $$ = new bit_expression(11, $2, NULL);
  } else
    $$ = NULL;
 }
| error element4 {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| element4 {
  $$ = $1;
  };
element4: LB expr4 RB {
  $$ = $2;
  }
| error expr4 RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| LB expr4 error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| expr1 {
  $$ = $1;
  };

expr5: expr5 BITOR term5 {
  if($1!=NULL && $3!=NULL) {
    $$ = new bit_expression(10, $1, $3);
  } else
    $$ = NULL;
 }
| expr5 BITXOR term5 {
  if($1!=NULL && $3!=NULL) {
    $$ = new bit_expression(12, $1, $3);
  } else
    $$ = NULL;
 }
| expr5 error term5 {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
 }
| term5 {
  $$ = $1;
  };
term5: term5 BITAND factor5 {
  if($1!=NULL && $3!=NULL) {
    $$ = new bit_expression(9, $1, $3);
  } else
    $$ = NULL;
 }
| term5 error factor5 {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
 }
| factor5 {
  $$ = $1;
  };
factor5: BITNOT element5 {
  if($2!=NULL) {
    $$ = new bit_expression(11, $2, NULL);
  } else
    $$ = NULL;
 }
| error element5 {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| element5 {
  $$ = $1;
  };
element5: LB expr5 RB {
  $$ = $2;
  }
| error expr5 RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| LB expr5 error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| expr2 {
  $$ = $1;
  };

expr6: expr6 BITOR term6 {
  if($1!=NULL && $3!=NULL) {
    $$ = new bit_expression(10, $1, $3);
  } else
    $$ = NULL;
 }
| expr6 BITXOR term6 {
  if($1!=NULL && $3!=NULL) {
    $$ = new bit_expression(12, $1, $3);
  } else
    $$ = NULL;
 }
| expr6 error term6 {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
 }
| term6 {
  $$ = $1;
  };
term6: term6 BITAND factor6 {
  if($1!=NULL && $3!=NULL) {
    $$ = new bit_expression(9, $1, $3);
  } else
    $$ = NULL;
 }
| term6 error factor6 {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
 }
| factor6 {
  $$ = $1;
  };
factor6: BITNOT element6 {
  if($2!=NULL) {
    $$ = new bit_expression(11, $2, NULL);
  } else
    $$ = NULL;
 }
| error element6 {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| element6 {
  $$ = $1;
  };
element6: LB expr6 RB {
  $$ = $2;
  }
| error expr6 RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| LB expr6 error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| expr3 {
  $$ = $1;
  };

expr2: expr2 PLUS term2 {
  if($1!=NULL && $3!=NULL) {
    $$ = new arithmetic_expression(5, $1, $3);
  } else
    $$ = NULL;
 }
| expr2 MINUS term2 {
  if($1!=NULL && $3!=NULL) {
    $$ = new arithmetic_expression(6, $1, $3);
  } else
    $$ = NULL;
 }
| expr2 error term2 {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
 }
| term2 {
  $$ = $1;
  };
term2: term2 TIMES element2 {
  if($1!=NULL && $3!=NULL) {
    $$ = new arithmetic_expression(7, $1, $3);
  } else
    $$ = NULL;
 }
| term2 DIVIDE element2 {
  if($1!=NULL && $3!=NULL) {
    $$ = new arithmetic_expression(8, $1, $3);
  } else
    $$ = NULL;
 }
| term2 error element2 {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
 }
| element2 {
  $$ = $1;
  };
element2: LB expr2 RB {
  $$ = $2;
  }
| error expr2 RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| LB expr2 error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| varvalue2  {
  $$ = $1;
  };
expr3: expr3 PLUS term3 {
  if($1!=NULL && $3!=NULL) {
    $$ = new arithmetic_expression(5, $1, $3);
  } else
    $$ = NULL;
 }
| expr3 MINUS term3 {
  if($1!=NULL && $3!=NULL) {
    $$ = new arithmetic_expression(6, $1, $3);
  } else
    $$ = NULL;
 }
| expr3 error term3 {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
 }
| term3 {
  $$ = $1;
  };
term3: term3 TIMES element3 {
  if($1!=NULL && $3!=NULL) {
    $$ = new arithmetic_expression(7, $1, $3);
  } else
    $$ = NULL;
 }
| term3 DIVIDE element3 {
  if($1!=NULL && $3!=NULL) {
    $$ = new arithmetic_expression(8, $1, $3);
  } else
    $$ = NULL;
 }
| term3 error element3 {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
 }
| element3 {
  $$ = $1;
  };
element3: LB expr3 RB {
  $$ = $2;
  }
| error expr3 RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| LB expr3 error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| varvalue3 {
  $$ = $1;
  };



eboolcond: LB eboolcond RB { 
  $$ = $2; 
 }
| error eboolcond RB { 
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| LB eboolcond error { 
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| error eboolcond error { 
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| eboolcond AND eboolcond {
  if($1!=NULL && $3!=NULL)
    $$ = new bool_expression(1, $1, $3);
  else
    $$ = NULL;
 }
| eboolcond OR eboolcond {
  if($1!=NULL && $3!=NULL)
    $$ = new bool_expression(2, $1, $3);
  else
    $$ = NULL;
 }
| eboolcond error eboolcond {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
  USE($3);
 }
| NOT eboolcond {
  if($2!=NULL)
    $$ = new bool_expression(3, $2);
  else
    $$ = NULL;
 }
| error eboolcond {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| expr4 logicop expr4 {
  if($1!=NULL && $3!=NULL) {
    logic_expression *expr = new logic_expression($2, $1, $3);
    $$ = new bool_expression(0,  expr);
  } else
    $$ = NULL;
 }
| ACTION EQ ID {
  if($3!=NULL) {
    laction *a = new laction();
    variable *v;
    int i = search_string_table($3);
    if(i>=0) {
      v = new variable((*string_table)[i]);
      free($3);
    } else {
      v = new variable($3);
      string_table->push_back($3);
    }
    logic_expression *expr = new logic_expression(0, a, v);
    $$ = new bool_expression(0,  expr);
  } else
    $$ = NULL;
 }
| error EQ ID {
  $$ = NULL;
  driver.syntax_error = true;
  USE($3);
 }
| ACTION error ID {
  $$ = NULL;
  driver.syntax_error = true;
  USE($3);
 }
| error ID {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| ID DOT ACTION EQ ID {
  if($1!=NULL && $5!=NULL) {
    laction *a;
    int i = search_string_table($1);
    if(i>=0) {
      a = new laction((*string_table)[i]);
      free($1);
    } else {
      a = new laction($1);
      string_table->push_back($1);
    }
    variable *v;
    int j = search_string_table($5);
    if(j>=0) {
      if(i>=0)
	v = new variable((*string_table)[i], (*string_table)[j]);
      else
	v = new variable($1, (*string_table)[j]);
      free($5);
    } else {
      if(i>=0)
	v = new variable((*string_table)[i], $5);
      else
	v = new variable($1, $5);
      string_table->push_back($5);
    }
    i = search_logic_expression_table(a, v);
    if(i>=0) {
      $$ = (*logic_expression_table)[i];
      delete a;
      delete v;
    } else {
			logic_expression *expr = new logic_expression(0, a, v);
			bool_expression *bexpr = new bool_expression(0,  expr);
      $$ = bexpr;
      logic_expression_table->push_back(bexpr);
    }
  } else
    $$ = NULL;
 }
| ID error ACTION EQ ID {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
  USE($5);
 }
| ID DOT error EQ ID {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
  USE($5);
 }
| ID DOT ACTION error ID {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
  USE($5);
 }
| ID error EQ ID {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
  USE($4);
 }
| ID DOT error ID {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
  USE($4);
 }
| ID error ACTION error ID {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
  USE($5);
 }
| ID error ID {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
  USE($3);
 }
| error {
  $$ = NULL;
  driver.syntax_error = true;
  };

logicop: LT {
  $$ = 2;
 }
| LE {
  $$ = 3;
  }
| GT {
  $$ = 4;
  }
| GE {
  $$ = 5;
  }
| EQ {
  $$ = 0;
  }
| NEQ {
  $$ = 1;
  };

/* global boolean condition definition used in normal agents */
gboolcond: LB gboolcond RB { 
  $$ = $2; 
 }
| error gboolcond RB { 
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| LB gboolcond error { 
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| error gboolcond error { 
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| gboolcond AND gboolcond {
  if($1!=NULL && $3!=NULL)
    $$ = new bool_expression(1, $1, $3);
  else
    $$ = NULL;
 }
| gboolcond OR gboolcond {
  if($1!=NULL && $3!=NULL)
    $$ = new bool_expression(2, $1, $3);
  else
    $$ = NULL;
 }
| gboolcond error gboolcond {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
  USE($3);
 }
| NOT gboolcond {
  if($2!=NULL)
    $$ = new bool_expression(3, $2);
  else
    $$ = NULL;
 }
| error gboolcond {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| expr5 logicop expr5 {
  if($1!=NULL && $3!=NULL) {
    logic_expression *expr = new logic_expression($2, $1, $3);
    $$ = new bool_expression(0,  expr);
  } else
    $$ = NULL;
 }
| ACTION EQ ID {
  if($3!=NULL) {
    laction *a = new laction();
    variable *v;
    int i = search_string_table($3);
    if(i>=0) {
      v = new variable((*string_table)[i]);
      free($3);
    } else {
      v = new variable($3);
      string_table->push_back($3);
    }
    logic_expression *expr = new logic_expression(0, a, v);
    $$ = new bool_expression(0,  expr);
  } else
    $$ = NULL;
 }
| error EQ ID {
  $$ = NULL;
  driver.syntax_error = true;
  USE($3);
 }
| ACTION error ID {
  $$ = NULL;
  driver.syntax_error = true;
  USE($3);
 }
| error ID {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| ID DOT ACTION EQ ID {
  if($1!=NULL && $5!=NULL) {
    laction *a;
    int i = search_string_table($1);
    if(i>=0) {
      a = new laction((*string_table)[i]);
      free($1);
    } else {
      a = new laction($1);
      string_table->push_back($1);
    }
    variable *v;
    int j = search_string_table($5);
    if(j>=0) {
      if(i>=0)
	v = new variable((*string_table)[i], (*string_table)[j]);
      else
	v = new variable($1, (*string_table)[j]);
      free($5);
    } else {
      if(i>=0)
	v = new variable((*string_table)[i], $5);
      else
	v = new variable($1, $5);
      string_table->push_back($5);
    }
    logic_expression *expr = new logic_expression(0, a, v);
    $$ = new bool_expression(0,  expr);
  } else 
    $$ = NULL;
 }
| ID error ACTION EQ ID {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
  USE($5);
 }
| ID DOT error EQ ID {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
  USE($5);
 }
| ID DOT ACTION error ID {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
  USE($5);
 }
| ID error EQ ID {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
  USE($4);
 }
| ID DOT error ID {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
  USE($4);
 }
| ID error ACTION error ID {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
  USE($5);
 }
| ID error ID {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
  USE($3);
 }
| ENVIRONMENT DOT ACTION EQ ID {
  if($5!=NULL) {
    laction *a = new laction((*string_table)[0]);
    variable *v;
    int j = search_string_table($5);
    if(j>=0) {
      v = new variable((*string_table)[0], (*string_table)[j]);
      free($5);
    } else { 
      v = new variable((*string_table)[0], $5);
      string_table->push_back($5);
    }
    logic_expression *expr = new logic_expression(0, a, v);
    $$ = new bool_expression(0,  expr);
  } else
    $$ = NULL;
 }
| ENVIRONMENT DOT error EQ ID {
  $$ = NULL;
  driver.syntax_error = true;
  USE($5);
 }
| ENVIRONMENT DOT ACTION error ID {
  $$ = NULL;
  driver.syntax_error = true;
  USE($5);
 }
| ENVIRONMENT error EQ ID {
  $$ = NULL;
  driver.syntax_error = true;
  USE($4);
 }
| ENVIRONMENT DOT error ID {
  $$ = NULL;
  driver.syntax_error = true;
  USE($4);
 }
| ENVIRONMENT error ACTION error ID {
  $$ = NULL;
  driver.syntax_error = true;
  USE($5);
 }
| ENVIRONMENT error ID {
  $$ = NULL;
  driver.syntax_error = true;
  USE($3);
 }
| error {
  $$ = NULL;
  driver.syntax_error = true;
  };

/* Variable values */
varvalue1: boolvalue {
  $$ = $1;
 }
| ID {
    int i = search_string_table($1);
    if(i>=0) {
      $$ = new variable((*string_table)[i]);
      free($1);
    } else {
      $$ = new variable($1); // can be enumerate value. Will be decided during global syntax checking
      string_table->push_back($1);
    }
  }
| integer {
  $$ = new int_value($1);
  };
boolvalue: BTRUE {
  $$ = new bool_value(true);
  }
| BFALSE {
  $$ = new bool_value(false);
  };

varvalue2: boolvalue {
  $$ = $1;
 }
| ID {
    int i = search_string_table($1);
    if(i>=0) {
      $$ = new variable((*string_table)[i]);
      free($1);
    } else {
      $$ = new variable($1); // can be enumerate value. Will be decided during global syntax checking
      string_table->push_back($1);
    }
  }
| ENVIRONMENT DOT ID {
    int i = search_string_table($3);
    variable *var;
    if(i>=0) {
      var = new variable((*string_table)[0], (*string_table)[i]);
      free($3);
    } else {
      var = new variable((*string_table)[0], $3); 
      string_table->push_back($3);
    }
    i = search_variable_table(var);
    if(i>=0) {
      $$ = (*variable_table)[i];
      delete var;
    } else {
      $$ = var;
      variable_table->push_back(var);
    }
  }
| error DOT ID {
  $$ = NULL;
  driver.syntax_error = true;
  USE($3);
  }
| ENVIRONMENT error ID {
  $$ = NULL;
  driver.syntax_error = true;
  USE($3);
  }
| integer {
  $$ = new int_value($1);
  };
varvalue3: boolvalue {
  $$ = $1;
 }
| ID {
    int i = search_string_table($1);
    if(i>=0) {
      $$ = new variable((*string_table)[i]);
      free($1);
    } else {
      $$ = new variable($1); // can be enumerate value. Will be decided during global syntax checking
      string_table->push_back($1);
    }
  }
| ID DOT ID {
    int i = search_string_table($1);
    int j = search_string_table($3);
    variable *var;
    if(i>=0) {
      if(j>=0) {
	var = new variable((*string_table)[i], (*string_table)[j]);
	free($3);
      } else {
	var = new variable((*string_table)[i], $3);
	string_table->push_back($3);
      }
      free($1);
    } else {
      if(j>=0) {
	var = new variable($1, (*string_table)[j]);
	free($3);
      } else {
	var = new variable($1, $3);
	string_table->push_back($3);
      }
      string_table->push_back($1);
    }
    i = search_variable_table(var);
    if(i>=0) {
      $$ = (*variable_table)[i];
      delete var;
    } else {
      $$ = var;
      variable_table->push_back(var);
    }
  }
| ID error ID {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
  USE($3);
  }
| ENVIRONMENT DOT ID {
    int i = search_string_table($3);
    variable *var;
    if(i>=0) {
      var = new variable((*string_table)[0], (*string_table)[i]);
      free($3);
    } else {
      var = new variable((*string_table)[0], $3); 
      string_table->push_back($3);
    }
    i = search_variable_table(var);
    if(i>=0) {
      $$ = (*variable_table)[i];
      delete var;
    } else {
      $$ = var;
      variable_table->push_back(var);
    }
  }
| error DOT ID {
  $$ = NULL;
  driver.syntax_error = true;
  USE($3);
  }
| ENVIRONMENT error ID {
  $$ = NULL;
  driver.syntax_error = true;
  USE($3);
  }
| integer {
  $$ = new int_value($1);
  };
/* Initial value of a variable */
varvalue4: boolvalue {
  $$ = $1;
 }
| ID {
    int i = search_string_table($1);
    if(i>=0) {
      $$ = new enum_value((*string_table)[i]);
      free($1);
    } else {
      $$ = new enum_value($1); // can be enumerate value. Will be decided during global syntax checking
      string_table->push_back($1);
    }
  }
| integer {
  $$ = new int_value($1);
  };

/* EVALUATION */
evaprefix: EVALUATION {
  $$ = 1;
 };
evasuffix: END EVALUATION {
  $$ = 1;
 }
| error EVALUATION {
  $$ = 0;
  driver.syntax_error = true;
 }
| END error {
  $$ = 0;
  driver.syntax_error = true;
 }
| error {
  $$ = 0;
  driver.syntax_error = true;
  };
evaluation: evaprefix evalist evasuffix
| error {
  driver.syntax_error = true;
  };

evalist: ID IF evaboolcond SEMICOLON {
  if($1!=NULL && $3!=NULL) {
    (*is_evaluation)[*$1] = $3;
    free($1);
  } 
 }
| ID error evaboolcond SEMICOLON {
  driver.syntax_error = true;
  USE($1);
  USE($3);
 }
| ID IF evaboolcond error {
  driver.syntax_error = true;
  USE($1);
  USE($3);
 }
| ID error evaboolcond error {
  driver.syntax_error = true;
  USE($1);
  USE($3);
 }
| evalist ID IF evaboolcond SEMICOLON {
  if($2!=NULL && $4!=NULL) {
    if(is_evaluation->find(*$2) != is_evaluation->end() && options["quiet"] == 0)
      cout << "warning: atomic proposition " << *$2 << " has already been defined." << endl;
    (*is_evaluation)[*$2] = $4;
    free($2);
  }
 }
| evalist ID error evaboolcond SEMICOLON {
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| evalist ID IF evaboolcond error {
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| evalist ID error evaboolcond error {
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| error {
  driver.syntax_error = true;
  };

evaboolcond: LB evaboolcond RB { 
  $$ = $2; 
 }
| error evaboolcond RB { 
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| LB evaboolcond error { 
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| error evaboolcond error { 
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| evaboolcond AND evaboolcond {
  if($1!=NULL && $3!=NULL)
    $$ = new bool_expression(1, $1, $3);
  else
    $$ = NULL;
 }
| evaboolcond OR evaboolcond {
  if($1!=NULL && $3!=NULL)
    $$ = new bool_expression(2, $1, $3);
  else
    $$ = NULL;
 }
| evaboolcond error evaboolcond {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);USE($3);
 }
| NOT evaboolcond {
  if($2!=NULL)
    $$ = new bool_expression(3, $2);
  else
    $$ = NULL;
 }
| error evaboolcond {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| expr6 logicop expr6 {
  if($1!=NULL && $3!=NULL) {
    logic_expression *expr = new logic_expression($2, $1, $3);
    $$ = new bool_expression(0,  expr);
  } else
    $$ = NULL;
 }
| error {
  $$ = NULL;
  driver.syntax_error = true;
  };



/* INITIAL STATES */
iniprefix: INITSTATES {
  $$ = 1;
 }
| error {
  $$ = 0;
  driver.syntax_error = true;
 }
inisuffix: SEMICOLON END INITSTATES {
  $$ = 1;
 }
| error END INITSTATES {
  $$ = 0;
  driver.syntax_error = true;
 }
| SEMICOLON error INITSTATES {
  $$ = 0;
  driver.syntax_error = true;
 }
| SEMICOLON END error {
  $$ = 0;
  driver.syntax_error = true;
 }
| error INITSTATES {
  $$ = 0;
  driver.syntax_error = true;
 }
| SEMICOLON error {
  $$ = 0;
  driver.syntax_error = true;
 }
| error END error {
  $$ = 0;
  driver.syntax_error = true;
 }
| error {
  $$ = 0;
  driver.syntax_error = true;
  }
istates: iniprefix isboolcond inisuffix {
  if($1==1 && $3==1)
    is_istates = $2; 
 }
| error {
  driver.syntax_error = true;
  };

isboolcond: LB isboolcond RB { 
  $$ = $2; 
}
| error isboolcond RB { 
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| LB isboolcond error { 
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| error isboolcond error { 
  $$ = NULL;
  driver.syntax_error = true;
  USE($2)
 }
| isboolcond AND isboolcond {
  if($1!=NULL && $3!=NULL)
    $$ = new bool_expression(1, $1, $3);
  else
    $$ = NULL;
 }
| isboolcond OR isboolcond {
  if($1!=NULL && $3!=NULL)
    $$ = new bool_expression(2, $1, $3);
  else
    $$ = NULL;
 }
| isboolcond error isboolcond {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);USE($3);
 }
| NOT isboolcond {
  if($2!=NULL)
    $$ = new bool_expression(3, $2);
  else
    $$ = NULL;
 }
| error isboolcond {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| ID DOT ID EQ ID DOT ID {
  if($1!=NULL && $3!=NULL && $5!=NULL && $7!=NULL) {
    int i = search_string_table($1);
    int j = search_string_table($3);
    variable *v;
    if(i>=0) {
      if(j>=0) {
	v = new variable((*string_table)[i], (*string_table)[j]);
	free($3);
      } else {
	v = new variable((*string_table)[i], $3);
	string_table->push_back($3);
      }
      free($1);
    } else {
      if(j>=0) {
	v = new variable($1, (*string_table)[j]);
	free($3);
      } else {
	v = new variable($1, $3);
	string_table->push_back($3);
      }
      string_table->push_back($1);
    }
    i = search_variable_table(v);
    if(i>=0) {
      delete v;
      v = (*variable_table)[i];
    } else {
      variable_table->push_back(v);
    }

    i = search_string_table($5);
    j = search_string_table($7);
    variable *v1;
    if(i>=0) {
      if(j>=0) {
	v1 = new variable((*string_table)[i], (*string_table)[j]);
	free($7);
      } else {
	v1 = new variable((*string_table)[i], $7);
	string_table->push_back($7);
      }
      free($5);
    } else {
      if(j>=0) {
	v1 = new variable($5, (*string_table)[j]);
	free($7);
      } else {
	v1 = new variable($5, $7);
	string_table->push_back($7);
      }
      string_table->push_back($5);
    }
    i = search_variable_table(v1);
    if(i>=0) {
      delete v1;
      v1 = (*variable_table)[i];
    } else {
      variable_table->push_back(v1);
    }

    i = search_logic_expression_table1(v, v1);
    if(i>=0) {
      $$ = (*logic_expression_table1)[i];
      free($5);
    } else {
			logic_expression *e = new logic_expression(0, v, v1);
			bool_expression *bexpr = new bool_expression(0, e);
      $$ = bexpr;
      logic_expression_table1->push_back(bexpr);
    }    
  } else
    $$ = NULL;
 }
| ID DOT ID EQ ENVIRONMENT DOT ID {
  if($1!=NULL && $3!=NULL && $7!=NULL) {
    int i = search_string_table($1);
    int j = search_string_table($3);
    variable *v;
    if(i>=0) {
      if(j>=0) {
	v = new variable((*string_table)[i], (*string_table)[j]);
	free($3);
      } else {
	v = new variable((*string_table)[i], $3);
	string_table->push_back($3);
      }
      free($1);
    } else {
      if(j>=0) {
	v = new variable($1, (*string_table)[j]);
	free($3);
      } else {
	v = new variable($1, $3);
	string_table->push_back($3);
      }
      string_table->push_back($1);
    }
    i = search_variable_table(v);
    if(i>=0) {
      delete v;
      v = (*variable_table)[i];
    } else {
      variable_table->push_back(v);
    }

    j = search_string_table($7);
    variable *v1;
    if(j>=0) {
      v1 = new variable((*string_table)[0], (*string_table)[j]);
      free($7);
    } else {
      v1 = new variable((*string_table)[0], $7);
      string_table->push_back($7);
    }
    
    i = search_variable_table(v1);
    if(i>=0) {
      delete v1;
      v1 = (*variable_table)[i];
    } else {
      variable_table->push_back(v1);
    }

    i = search_logic_expression_table1(v, v1);
    if(i>=0) {
      $$ = (*logic_expression_table1)[i];
    } else {
			logic_expression *e = new logic_expression(0, v, v1);
			bool_expression *bexpr = new bool_expression(0, e);
      $$ = bexpr;
      logic_expression_table1->push_back(bexpr);
    }    
  } else
    $$ = NULL;
 }
| ENVIRONMENT DOT ID EQ ID DOT ID {
  if($3!=NULL && $5!=NULL && $7!=NULL) {
    int j = search_string_table($3);
    variable *v;
    if(j>=0) {
      v = new variable((*string_table)[0], (*string_table)[j]);
      free($3);
    } else {
      v = new variable((*string_table)[0], $3);
      string_table->push_back($3);
    }
    int i = search_variable_table(v);
    if(i>=0) {
      delete v;
      v = (*variable_table)[i];
    } else {
      variable_table->push_back(v);
    }

    i = search_string_table($5);
    j = search_string_table($7);
    variable *v1;
    if(i>=0) {
      if(j>=0) {
	v1 = new variable((*string_table)[i], (*string_table)[j]);
	free($7);
      } else {
	v1 = new variable((*string_table)[i], $7);
	string_table->push_back($7);
      }
      free($5);
    } else {
      if(j>=0) {
	v1 = new variable($5, (*string_table)[j]);
	free($7);
      } else {
	v1 = new variable($5, $7);
	string_table->push_back($7);
      }
      string_table->push_back($5);
    }
    i = search_variable_table(v1);
    if(i>=0) {
      delete v1;
      v1 = (*variable_table)[i];
    } else {
      variable_table->push_back(v1);
    }

    i = search_logic_expression_table1(v, v1);
    if(i>=0) {
      $$ = (*logic_expression_table1)[i];
      free($5);
    } else {
			logic_expression *e = new logic_expression(0, v, v1);
			bool_expression *bexpr = new bool_expression(0, e);
      $$ = bexpr;
      logic_expression_table1->push_back(bexpr);
    }    
  } else
    $$ = NULL;
 }
| ID DOT ID EQ varvalue4 {
  if($1!=NULL && $3!=NULL && $5!=NULL) {
    int i = search_string_table($1);
    int j = search_string_table($3);
    variable *v;
    if(i>=0) {
      if(j>=0) {
	v = new variable((*string_table)[i], (*string_table)[j]);
	free($3);
      } else {
	v = new variable((*string_table)[i], $3);
	string_table->push_back($3);
      }
      free($1);
    } else {
      if(j>=0) {
	v = new variable($1, (*string_table)[j]);
	free($3);
      } else {
	v = new variable($1, $3);
	string_table->push_back($3);
      }
      string_table->push_back($1);
    }
    i = search_variable_table(v);
    if(i>=0) {
      delete v;
      v = (*variable_table)[i];
    } else {
      variable_table->push_back(v);
    }
    i = search_logic_expression_table1(v, $5);
    if(i>=0) {
      $$ = (*logic_expression_table1)[i];
      free($5);
    } else {
			logic_expression *e = new logic_expression(0, v, $5);
			bool_expression *bexpr = new bool_expression(0, e);
      $$ = bexpr;
      logic_expression_table1->push_back(bexpr);
    }    
  } else
    $$ = NULL;
 }
| ID error ID EQ varvalue4 {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
  USE($3);
  USE($5);
 }
| ID DOT ID error varvalue4 {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
  USE($3);
  USE($5);
 }
| ID error ID error varvalue4 {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
  USE($3);
  USE($5);
 }
| ENVIRONMENT DOT ID EQ ENVIRONMENT DOT ID {
  if($3!=NULL && $7!=NULL) {
    int j = search_string_table($3);
    variable *v;
    if(j>=0) {
      v = new variable((*string_table)[0], (*string_table)[j]);
      free($3);
    } else {
      v = new variable((*string_table)[0], $3);
      string_table->push_back($3);
    }
    int i = search_variable_table(v);
    if(i>=0) {
      delete v;
      v = (*variable_table)[i];
    } else {
      variable_table->push_back(v);
    }

    j = search_string_table($7);
    variable *v1;
    if(j>=0) {
      v1 = new variable((*string_table)[0], (*string_table)[j]);
      free($7);
    } else {
      v1 = new variable((*string_table)[0], $7);
      string_table->push_back($7);
    }
    i = search_variable_table(v1);
    if(i>=0) {
      delete v1;
      v1 = (*variable_table)[i];
    } else {
      variable_table->push_back(v1);
    }

    i = search_logic_expression_table1(v, v1);
    if(i>=0) {
      $$ = (*logic_expression_table1)[i];
    } else {
			logic_expression *e = new logic_expression(0, v, v1);
			bool_expression *bexpr = new bool_expression(0, e);
      $$ = bexpr;
      logic_expression_table1->push_back(bexpr);
    }    
  } else
    $$ = NULL;
 }
| ENVIRONMENT DOT ID EQ varvalue4 {	
  if($3!=NULL && $5!=NULL) {
    int j = search_string_table($3);
    variable *v;
    if(j>=0) {
      v = new variable((*string_table)[0], (*string_table)[j]);
      free($3);
    } else {
      v = new variable((*string_table)[0], $3);
      string_table->push_back($3);
    }
    j = search_variable_table(v);
    if(j>=0) {
      delete v;
      v = (*variable_table)[j];
    } else {
      variable_table->push_back(v);
    }
    j = search_logic_expression_table1(v, $5);
    if(j>=0) {
      $$ = (*logic_expression_table1)[j];
      free($5);
    } else {
			logic_expression *e = new logic_expression(0, v, $5);
			bool_expression *bexpr = new bool_expression(0, e);
      $$ = bexpr;
      logic_expression_table1->push_back(bexpr);
    }    
  } else
    $$ = NULL;
 }
| ENVIRONMENT error ID EQ varvalue4 {
  $$ = NULL;
  driver.syntax_error = true;
  USE($3);
  USE($5);
 }
| ENVIRONMENT DOT ID error varvalue4 {
  $$ = NULL;
  driver.syntax_error = true;
  USE($3);
  USE($5);
 }
| ENVIRONMENT error ID error varvalue4 {
  $$ = NULL;
  driver.syntax_error = true;
  USE($3);
  USE($5);
 }
| error ID EQ varvalue4 {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| error DOT ID error varvalue4 {
  $$ = NULL;
  driver.syntax_error = true;
  USE($3);
  USE($5);
 }
| error ID error varvalue4 {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| error {
  $$ = NULL;
  driver.syntax_error = true;
  };


/* Groups (not necessary) */
groupprefix: GROUPS {
  $$ = 1;
 }
| error {
  $$ = 0;
  driver.syntax_error = true;
 }
groupsuffix: END GROUPS {
  $$ = 1;
 }
| error GROUPS {
  $$ = 0;
  driver.syntax_error = true;
 }
| END error {
  $$ = 0;
  driver.syntax_error = true;
 }
| error {
  $$ = 0;
  driver.syntax_error = true;
  }
groups: groupprefix groupdeflist groupsuffix
| groupprefix  groupsuffix // allow not to define groups
| error {
  driver.syntax_error = true;
  };

gplprefix: EQ LCB {
  $$ = 1;
 }
| error LCB {
  $$ = 0;
  driver.syntax_error = true;
 }
| EQ error {
  $$ = 0;
  driver.syntax_error = true;
 }
| error {
  $$ = 0;
  driver.syntax_error = true;
  };
gplsufffix: RCB SEMICOLON {
  $$ = 1;
 }
| error SEMICOLON {
  $$ = 0;
  driver.syntax_error = true;
 }
| RCB error {
  $$ = 0;
  driver.syntax_error = true;
 }
| error {
  $$ = 0;
  driver.syntax_error = true;
  };
groupdeflist: ID gplprefix namelist gplsufffix {
  if($1!=NULL && $2==1 && $3!=NULL && $4==1) {
    (*is_groups)[*$1] = *$3;
    free($1);
  }
 }
| groupdeflist ID gplprefix namelist gplsufffix {
  if($2!=NULL && $3==1 && $4!=NULL && $5==1) {
    if(is_groups->find(*$2) != is_groups->end() && options["quiet"] == 0)
      cout << "warning: group " << *$2 << " already exists." << endl; 
    (*is_groups)[*$2] = *$4;
    free($2);
  }
 }
| error {
  driver.syntax_error = true;
  };

namelist: agentname {
  if($1!=NULL) {
    $$ = new set<string>;
    $$->insert(*$1);
  } else
    $$ = NULL;
 }
| namelist COMMA agentname {
  if($1!=NULL && $3!=NULL) {
    pair<set<string>::iterator, bool> ret = $1->insert(*$3);
    if(!ret.second && options["quiet"] == 0)
      cout << "warning: agent " << *$3 << " in group definition is redundant." << endl;
    $$ = $1;
  } else
    $$ = NULL;
 }
| namelist error agentname {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);USE($3);
 }
| error {
  $$ = NULL;
  driver.syntax_error = true;
  };
agentname: ENVIRONMENT {
  $$ = (*string_table)[0];
 }
| ID {
    int i = search_string_table($1);
    if(i>=0) {
      $$ = (*string_table)[i];
      free($1);
    } else {
      $$ = $1;
      string_table->push_back($1);
    }
  }
| error {
  $$ = NULL;
  driver.syntax_error = true;
  };


/* FAIRNES FORMULAE (boolean) */
fairprefix: FAIRNESS {
  $$ = 1;
 }
| error {
  $$ = 0;
  driver.syntax_error = true;
 }
fairsuffix: END FAIRNESS {
  $$ = 1;
 }
| error FAIRNESS {
  $$ = 0;
  driver.syntax_error = true;
 }
| END error {
  $$ = 0;
  driver.syntax_error = true;
 }
| error {
  $$ = 0;
  driver.syntax_error = true;
  }
fairness: fairprefix fairsuffix
| fairprefix fformlist fairsuffix;

fformlist: fformula SEMICOLON { 
  if($1!=NULL)
    is_fairness->push_back($1);
 }
| fformula error {
  driver.syntax_error = true;
  USE($1);
 }
| fformlist fformula SEMICOLON { 
  if($2!=NULL)
    is_fairness->push_back($2); 
 }
| fformlist fformula error {
  driver.syntax_error = true;
  USE($2);
 }
| error {
  driver.syntax_error = true;
  };

untilprefixfair: LB fformula UNTIL fformula RB{
  if($2!=NULL && $4!=NULL)
    $$ = new pair<fairness_expression *, fairness_expression *>($2, $4);
  else
    $$ = NULL;
 }
| error fformula UNTIL fformula RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);USE($4);
 }
| LB fformula error fformula RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);USE($4);
 }
| LB fformula UNTIL fformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);USE($4);
 }
| error fformula error fformula RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);USE($4);
 }
| error fformula UNTIL fformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);USE($4);
 }
| LB fformula error fformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);USE($4);
 }
| error fformula error fformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);USE($4);
 };
epistemicprefixfair: LB ID COMMA fformula RB{
    if($2!=NULL && $4!=NULL) {
      int i = search_string_table($2);
      if(i>=0) {
	$$ = new pair<string *, fairness_expression *>((*string_table)[i], $4);
	free($2);
      } else {
	$$ = new pair<string *, fairness_expression *>($2, $4);
	string_table->push_back($2);
      }
    } else
      $$ = NULL;
 }
| error ID COMMA fformula RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| LB ID error fformula RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| LB ID COMMA fformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| error ID error fformula RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| error ID COMMA fformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| LB ID error fformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| error ID error fformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| LB ENVIRONMENT COMMA fformula RB{
  if($4!=NULL)
    $$ = new pair<string *, fairness_expression *>((*string_table)[0], $4);
  else
    $$ = NULL;
 }
| error ENVIRONMENT COMMA fformula RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($4);
 }
| LB ENVIRONMENT error fformula RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($4);
 }
| LB ENVIRONMENT COMMA fformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($4);
 }
| error ENVIRONMENT error fformula RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($4);
 }
| error ENVIRONMENT COMMA fformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($4);
 }
| LB ENVIRONMENT error fformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($4);
 }
| error ENVIRONMENT error fformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($4);
 };
gepistemicprefixfair: LB ID COMMA fformula RB{
    if($2!=NULL && $4!=NULL) {
      int i = search_string_table($2);
      if(i>=0) {
	$$ = new pair<string *, fairness_expression *>((*string_table)[i], $4);
	free($2);
      } else {
	$$ = new pair<string *, fairness_expression *>($2, $4);
	string_table->push_back($2);
      }
    } else
      $$ = NULL;
 }
| error ID COMMA fformula RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| LB ID error fformula RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| LB ID COMMA fformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| error ID error fformula RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| error ID COMMA fformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| LB ID error fformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| error ID error fformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 };

fformula: LB fformula RB { 
  $$ = $2; 
 }
| error fformula RB { 
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| LB fformula error { 
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| error fformula error { 
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| fformula AND fformula {
  if($1!=NULL && $3!=NULL)
    $$ = new fairness_expression(1, $1, $3);
  else
    $$ = NULL;
 }
| fformula OR fformula {
  if($1!=NULL && $3!=NULL)
    $$ = new fairness_expression(2, $1, $3);
  else
    $$ = NULL;
 }
| fformula error fformula {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);USE($3);
 }
| NOT fformula {
  if($2!=NULL)
    $$ = new fairness_expression(3, $2);
  else
    $$ = NULL;
 }
| error fformula {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| fformula IMPLIES fformula {
  if($1!=NULL && $3!=NULL)
    $$ = new fairness_expression(4, $1, $3);
  else
    $$ = NULL;
 }
| AG fformula {
  if($2!=NULL)
    $$ = new fairness_expression(10, $2);
  else
    $$ = NULL;
 }
| EG fformula {
  if($2!=NULL)
    $$ = new fairness_expression(11, $2);
  else
    $$ = NULL;
  }
| AX fformula {
  if($2!=NULL)
    $$ = new fairness_expression(12, $2);
  else
    $$ = NULL;
 }
| EX fformula {
  if($2!=NULL)
    $$ = new fairness_expression(13, $2);
  else
    $$ = NULL;
 }
| AF fformula {
  if($2!=NULL)
    $$ = new fairness_expression(14, $2);
  else
    $$ = NULL;
 }
| EF fformula {
  if($2!=NULL)
    $$ = new fairness_expression(15, $2);
  else
    $$ = NULL;
 }
| A untilprefixfair {
  if($2!=NULL) {
    $$ = new fairness_expression(16, $2->first, $2->second);
    free($2);
  }
  else
    $$ = NULL;
 }
| E untilprefixfair {
  if($2!=NULL) {
    $$ = new fairness_expression(17, $2->first, $2->second);
    free($2);
  }
  else
    $$ = NULL;
 }
| K epistemicprefixfair {
  if($2!=NULL) {
    atomic_proposition *ap = new atomic_proposition($2->first);
    fairness_expression *a = new fairness_expression(ap);
    $$ = new fairness_expression(30, a, $2->second);
    free($2);
  } else
    $$ = NULL;
 }
| GK gepistemicprefixfair {
  // Knowledge in a group (everybody knows)
  if($2!=NULL) {
    atomic_proposition *ap = new atomic_proposition($2->first);
    fairness_expression *a = new fairness_expression(ap);
    $$ = new fairness_expression(31, a, $2->second);
    free($2);
  } else
    $$ = NULL;
 }
| GCK gepistemicprefixfair {
  // Common knowledge in a group
  if($2!=NULL) {
    atomic_proposition *ap = new atomic_proposition($2->first);
    fairness_expression *a = new fairness_expression(ap);
    $$ = new fairness_expression(32, a, $2->second);
    free($2);
  } else
    $$ = NULL;
 }
| O epistemicprefixfair {
  // deontic operator
  if($2!=NULL) {
    atomic_proposition *ap = new atomic_proposition($2->first);
    fairness_expression *a = new fairness_expression(ap);
    $$ = new fairness_expression(40, a, $2->second);
    free($2);
  } else
    $$ = NULL;
 }
| DK gepistemicprefixfair {
  // Distributed knowledge in a group
  if($2!=NULL) {
    atomic_proposition *ap = new atomic_proposition($2->first);
    fairness_expression *a = new fairness_expression(ap);
    $$ = new fairness_expression(42, a, $2->second);
    free($2);
  } else
    $$ = NULL;
 }
| error epistemicprefixfair { 
  $$ = NULL;
  if($2 != NULL)
    free($2);
  driver.syntax_error = true;
 }
| error gepistemicprefixfair { 
  $$ = NULL;
  if($2 != NULL)
    free($2);
  driver.syntax_error = true;
 }
| ID {	
  if($1!=NULL) {
    int i = search_string_table($1);
    atomic_proposition *ap;
    if(i>=0) {
      ap = new atomic_proposition((*string_table)[i]);
      free($1);
    } else {
      ap = new atomic_proposition($1);
      string_table->push_back($1);
    }
    $$ = new fairness_expression(ap);
  } else
    $$ = NULL;
  }
| ID DOT GREENSTATES {
  if($1!=NULL) {
    string *newname = new string(*$1 + ".GreenStates");
    atomic_proposition *ap;
    int i = search_string_table(newname);
    if(i>=0) {
      ap = new atomic_proposition((*string_table)[i]);
      free(newname);
    } else {
      ap = new atomic_proposition(newname);
      string_table->push_back(newname);
    }
    free($1);
    $$ = new fairness_expression(ap);
  } else
    $$ = NULL;
 }
| ID DOT REDSTATES {
  if($1!=NULL) {
    string *newname = new string(*$1 + ".RedStates");
    atomic_proposition *ap;
    int i = search_string_table(newname);
    if(i>=0) {
      ap = new atomic_proposition((*string_table)[i]);
      free(newname);
    } else {
      ap = new atomic_proposition(newname);
      string_table->push_back(newname);
    }
    free($1);
    $$ = new fairness_expression(ap);
  } else
    $$ = NULL;
 }
| ENVIRONMENT DOT GREENSTATES {
    string *newname = new string("Environment.GreenStates");
    atomic_proposition *ap;
    int i = search_string_table(newname);
    if(i>=0) {
      ap = new atomic_proposition((*string_table)[i]);
      free(newname);
    } else {
      ap = new atomic_proposition(newname);
      string_table->push_back(newname);
    }
    $$ = new fairness_expression(ap);
 }
| ENVIRONMENT DOT REDSTATES {
  string *newname = new string("Environment.RedStates");
  atomic_proposition *ap;
  int i = search_string_table(newname);
  if(i>=0) {
    ap = new atomic_proposition((*string_table)[i]);
    free(newname);
  } else {
    ap = new atomic_proposition(newname);
    string_table->push_back(newname);
  }
  $$ = new fairness_expression(ap);
 }
| ID DOT error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
 }
| ID error GREENSTATES {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
 }
| ID error REDSTATES {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
 }
| error {
  $$ = NULL;
  driver.syntax_error = true;
  };


/* FORMULAE TO CHECK */
forprefix: FORMULAE {
  $$ = 1;
 }
| error {
  $$ = 0;
  driver.syntax_error = true;
 }
forsuffix: END FORMULAE {
  $$ = 1;
 }
| error FORMULAE {
  $$ = 0;
  driver.syntax_error = true;
 }
| END error {
  $$ = 0;
  driver.syntax_error = true;
 }
| error {
  $$ = 0;
  driver.syntax_error = true;
  }
formulae: forprefix formlist forsuffix;

formlist: formula SEMICOLON { 
  if($1!=NULL) {
    is_formulae->push_back(*$1);
  }
 }
| CTLSPREFIX ctlsformula SEMICOLON {
  if($2!=NULL) {
    is_formulae->push_back(*$2);
  }
}
| LTLPREFIX ltlformula SEMICOLON {
  if($2!=NULL) {
    is_formulae->push_back(modal_formula(50, $2));
  }
}
| formula error {
  driver.syntax_error = true;
  USE($1);
 }
| ctlsformula error {
  driver.syntax_error = true;
  USE($1);
 }
| pathformula error {
  driver.syntax_error = true;
  USE($1);
 }
| formlist formula SEMICOLON {
  if($2!=NULL) {
    is_formulae->push_back(*$2); 
  }
 }
| formlist CTLSPREFIX ctlsformula SEMICOLON {
  if($3!=NULL) {
    is_formulae->push_back(*$3);
  }
 }
| formlist LTLPREFIX ltlformula SEMICOLON {
  if($3!=NULL) {
    is_formulae->push_back(modal_formula(50, $3));
  }
 }
| formlist formula error {
  driver.syntax_error = true;
  USE($2);
 }
| formlist CTLSPREFIX ctlsformula error {
  driver.syntax_error = true;
  USE($3);
 }
| error {
  driver.syntax_error = true;
  };

atlprefix: LT ID GT {
    int i = search_string_table($2);
    if(i>=0) {
      $$ = (*string_table)[i];
      free($2);
    } else {
      $$ = $2;
      string_table->push_back($2);
    }
 }
| LT ID error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| error ID GT { 
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 };
untilprefix: LB formula UNTIL formula RB{
  if($2!=NULL && $4!=NULL)
    $$ = new pair<modal_formula *, modal_formula *>($2, $4);
  else
    $$ = NULL;
 }
| error formula UNTIL formula RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);USE($4);
 }
| LB formula error formula RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);USE($4);
 }
| LB formula UNTIL formula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);USE($4);
 }
| error formula error formula RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);USE($4);
 }
| error formula UNTIL formula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);USE($4);
 }
| LB formula error formula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);USE($4);
 }
| error formula error formula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);USE($4);
 };
epistemicprefix: LB ID COMMA formula RB{
    if($2!=NULL && $4!=NULL) {
      int i = search_string_table($2);
      if(i>=0) {
	$$ = new pair<string *, modal_formula *>((*string_table)[i], $4);
	free($2);
      } else {
	$$ = new pair<string *, modal_formula *>($2, $4);
	string_table->push_back($2);
      }
    } else
    $$ = NULL;
 }
| error ID COMMA formula RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| LB ID error formula RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| LB ID COMMA formula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| error ID error formula RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| error ID COMMA formula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| LB ID error formula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| error ID error formula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| LB ENVIRONMENT COMMA formula RB{
  if($4!=NULL)
    $$ = new pair<string *, modal_formula *>((*string_table)[0], $4);
  else
    $$ = NULL;
 }
| error ENVIRONMENT COMMA formula RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($4);
 }
| LB ENVIRONMENT error formula RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($4);
 }
| LB ENVIRONMENT COMMA formula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($4);
 }
| error ENVIRONMENT error formula RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($4);
 }
| error ENVIRONMENT COMMA formula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($4);
 }
| LB ENVIRONMENT error formula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($4);
 }
| error ENVIRONMENT error formula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($4);
 };
gepistemicprefix: LB ID COMMA formula RB{
    if($2!=NULL && $4!=NULL) {
      int i = search_string_table($2);
      if(i>=0) {
	$$ = new pair<string *, modal_formula *>((*string_table)[i], $4);
	free($2);
      } else {
	$$ = new pair<string *, modal_formula *>($2, $4);
	string_table->push_back($2);
      }
    } else
      $$ = NULL;
 }
| error ID COMMA formula RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| LB ID error formula RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| LB ID COMMA formula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| error ID error formula RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| error ID COMMA formula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| LB ID error formula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| error ID error formula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 };

formula: LB formula RB { 
  $$ = $2; 
 }
| error formula RB { 
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| LB formula error { 
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| error formula error { 
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| formula AND formula {
  if($1!=NULL && $3!=NULL)
    $$ = new modal_formula(1, $1, $3);
  else
    $$ = NULL;
 }
| formula OR formula {
  if($1!=NULL && $3!=NULL)
    $$ = new modal_formula(2, $1, $3);
  else
    $$ = NULL;
 }
| formula error formula {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);USE($3);
 }
| NOT formula {
  if($2!=NULL)
    $$ = new modal_formula(3, $2);
  else
    $$ = NULL;
 }
| error formula {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| formula IMPLIES formula {
  if($1!=NULL && $3!=NULL)
    $$ = new modal_formula(4, $1, $3);
  else
    $$ = NULL;
 }
| AG formula {
  if($2!=NULL)
    $$ = new modal_formula(10, $2);
  else
    $$ = NULL;
 }
| EG formula {
  if($2!=NULL)
    $$ = new modal_formula(11, $2);
  else
    $$ = NULL;
  }
| AX formula {
  if($2!=NULL)
    $$ = new modal_formula(12, $2);
  else
    $$ = NULL;
 }
| EX formula {
  if($2!=NULL)
    $$ = new modal_formula(13, $2);
  else
    $$ = NULL;
 }
| AF formula {
  if($2!=NULL)
    $$ = new modal_formula(14, $2);
  else
    $$ = NULL;
 }
| EF formula {
  if($2!=NULL)
    $$ = new modal_formula(15, $2);
  else
    $$ = NULL;
 }
| A untilprefix {
  if($2!=NULL) {
    $$ = new modal_formula(16, $2->first, $2->second);
    free($2);
  }
  else
    $$ = NULL;
 }
| E untilprefix {
  if($2!=NULL) {
    $$ = new modal_formula(17, $2->first, $2->second);
    free($2);
  }
  else
    $$ = NULL;
 }
| K epistemicprefix {
  if($2!=NULL) {
    atomic_proposition *ap = new atomic_proposition($2->first);
    modal_formula *a = new modal_formula(ap);
    $$ = new modal_formula(30, a, $2->second);
    free($2);
  } else
    $$ = NULL;
 }
| GK gepistemicprefix {
  // Knowledge in a group (everybody knows)
  if($2!=NULL) {
    atomic_proposition *ap = new atomic_proposition($2->first);
    modal_formula *a = new modal_formula(ap);
    $$ = new modal_formula(31, a, $2->second);
    free($2);
  } else
    $$ = NULL;
 }
| GCK gepistemicprefix {
  // Common knowledge in a group
  if($2!=NULL) {
    atomic_proposition *ap = new atomic_proposition($2->first);
    modal_formula *a = new modal_formula(ap);
    $$ = new modal_formula(32, a, $2->second);
    free($2);
  } else
    $$ = NULL;
 }
| O epistemicprefix {
  // deontic operator
  if($2!=NULL) {
    atomic_proposition *ap = new atomic_proposition($2->first);
    modal_formula *a = new modal_formula(ap);
    $$ = new modal_formula(40, a, $2->second);
    free($2);
  } else
    $$ = NULL;
 }
| DK gepistemicprefix {
  // Distributed knowledge in a group
  if($2!=NULL) {
    atomic_proposition *ap = new atomic_proposition($2->first);
    modal_formula *a = new modal_formula(ap);
    $$ = new modal_formula(42, a, $2->second);
    free($2);
  } else
    $$ = NULL;
 }
| error epistemicprefix { 
  $$ = NULL;
  driver.syntax_error = true;
 }
| error gepistemicprefix { 
  $$ = NULL;
  driver.syntax_error = true;
 }
| atlprefix X formula {
  // ATL X operator
  if($1!=NULL && $3!=NULL) {
    atomic_proposition *ap = new atomic_proposition($1);
    modal_formula *a = new modal_formula(ap);
    $$ = new modal_formula(45, a, $3);
  } else
    $$ = NULL;
 }
| atlprefix F formula {
  // ATL F operator
  if($1!=NULL && $3!=NULL) {
    atomic_proposition *ap = new atomic_proposition($1);
    modal_formula *a = new modal_formula(ap);
    $$ = new modal_formula(46, a, $3);
  } else
    $$ = NULL;
 }
| atlprefix G formula {
  // ATL G operator
  if($1!=NULL && $3!=NULL) {
    atomic_proposition *ap = new atomic_proposition($1);
    modal_formula *a = new modal_formula(ap);
    $$ = new modal_formula(47, a, $3);
  } else
    $$ = NULL;
 }
| atlprefix error formula {
  $$ = NULL;
  driver.syntax_error = true;
  USE($3);
 }
| atlprefix untilprefix {
  // ATL U operator
  if($1!=NULL && $2!=NULL) {
    atomic_proposition *ap = new atomic_proposition($1);
    modal_formula *a = new modal_formula(ap);
    $$ = new modal_formula(48, a, $2->first, $2->second);
    free($2);
  } else {
    if($2 != NULL)
       free($2);
    if($1 != NULL)
      free($1);
    $$ = NULL;
  }
 }
| terminalformula {
  $$ = $1;
};

/* LTL */
ltlformula: LB ltlformula RB {
  $$ = $2;
 }
| error ltlformula RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| LB ltlformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| error ltlformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| ltlformula AND ltlformula {
  if($1!=NULL && $3!=NULL)
    $$ = new modal_formula(1, $1, $3);
  else
    $$ = NULL;
 }
| ltlformula OR ltlformula {
  if($1!=NULL && $3!=NULL)
    $$ = new modal_formula(2, $1, $3);
  else
    $$ = NULL;
 }
| ltlformula error ltlformula {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);USE($3);
 }
| NOT ltlformula {
  if($2!=NULL)
    $$ = new modal_formula(3, $2);
  else
    $$ = NULL;
 }
| ltlformula IMPLIES ltlformula {
  if($1!=NULL && $3!=NULL)
    $$ = new modal_formula(4, $1, $3);
  else
    $$ = NULL;
 }
| G ltlformula {
  // LTL G operator
  if($2!=NULL) {
    $$ = new modal_formula(61, $2);
  } else {
    $$ = NULL;
  }
 }
| F ltlformula {
  // LTL F operator
  if($2!=NULL) {
    $$ = new modal_formula(62, $2);
  } else {
    $$ = NULL;
  }
 }
| X ltlformula {
  // LTL X operator
  if($2!=NULL) {
    $$ = new modal_formula(63, $2);
  } else {
    $$ = NULL;
  }
 }
| ltlformula UNTIL ltlformula {
  // LTL U operator.
  if($1!=NULL && $3!=NULL) {
    $$ = new modal_formula(64, $1, $3);
  }
  else {
    if($1!=NULL) {
      free($1);
    }
    if($3!=NULL) {
      free($3);
    }
    $$ = NULL;
  }
 }
| terminalformula {
  $$ = $1;
 }
| K epistemicprefixltl {
  if($2!=NULL) {
    atomic_proposition *ap = new atomic_proposition($2->first);
    modal_formula *a = new modal_formula(ap);
    $$ = new modal_formula(30, a, new modal_formula(50, $2->second)); // A(...)
    free($2);
  } else
    $$ = NULL;
 }
| GK gepistemicprefixltl {
  // Knowledge in a group (everybody knows)
  if($2!=NULL) {
    atomic_proposition *ap = new atomic_proposition($2->first);
    modal_formula *a = new modal_formula(ap);
    $$ = new modal_formula(31, a, new modal_formula(50, $2->second)); // A(...)
    free($2);
  } else
    $$ = NULL;
 }
| GCK gepistemicprefixltl {
  // Common knowledge in a group
  if($2!=NULL) {
    atomic_proposition *ap = new atomic_proposition($2->first);
    modal_formula *a = new modal_formula(ap);
    $$ = new modal_formula(32, a, new modal_formula(50, $2->second)); // A(...)
    free($2);
  } else
    $$ = NULL;
 }
| DK gepistemicprefixltl {
  // Distributed knowledge in a group
  if($2!=NULL) {
    atomic_proposition *ap = new atomic_proposition($2->first);
    modal_formula *a = new modal_formula(ap);
    $$ = new modal_formula(42, a, new modal_formula(50, $2->second)); // A(...)
    free($2);
  } else
    $$ = NULL;
 };

epistemicprefixltl: LB ID COMMA ltlformula RB{
    if($2!=NULL && $4!=NULL) {
      int i = search_string_table($2);
      if(i>=0) {
	$$ = new pair<string *, modal_formula *>((*string_table)[i], $4);
	free($2);
      } else {
	$$ = new pair<string *, modal_formula *>($2, $4);
	string_table->push_back($2);
      }
    } else
    $$ = NULL;
 }
| error ID COMMA ltlformula RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| LB ID error ltlformula RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| LB ID COMMA ltlformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| error ID error ltlformula RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| error ID COMMA ltlformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| LB ID error ltlformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| error ID error ltlformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| LB ENVIRONMENT COMMA ltlformula RB{
  if($4!=NULL)
    $$ = new pair<string *, modal_formula *>((*string_table)[0], $4);
  else
    $$ = NULL;
 }
| error ENVIRONMENT COMMA ltlformula RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($4);
 }
| LB ENVIRONMENT error ltlformula RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($4);
 }
| LB ENVIRONMENT COMMA ltlformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($4);
 }
| error ENVIRONMENT error ltlformula RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($4);
 }
| error ENVIRONMENT COMMA ltlformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($4);
 }
| LB ENVIRONMENT error ltlformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($4);
 }
| error ENVIRONMENT error ltlformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($4);
 };

gepistemicprefixltl: LB ID COMMA ltlformula RB{
    if($2!=NULL && $4!=NULL) {
      int i = search_string_table($2);
      if(i>=0) {
	$$ = new pair<string *, modal_formula *>((*string_table)[i], $4);
	free($2);
      } else {
	$$ = new pair<string *, modal_formula *>($2, $4);
	string_table->push_back($2);
      }
    } else
      $$ = NULL;
 }
| error ID COMMA ltlformula RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| LB ID error ltlformula RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| LB ID COMMA ltlformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| error ID error ltlformula RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| error ID COMMA ltlformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| LB ID error ltlformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| error ID error ltlformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 };

/* CTL*: path formulae */
pathformula: LB pathformula RB {
  $$ = $2; 
 }
| error pathformula RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| LB pathformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| error pathformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| pathformula AND pathformula {
  if($1!=NULL && $3!=NULL)
    $$ = new modal_formula(1, $1, $3);
  else
    $$ = NULL;
 }
| pathformula OR pathformula {
  if($1!=NULL && $3!=NULL)
    $$ = new modal_formula(2, $1, $3);
  else
    $$ = NULL;
 }
| pathformula error pathformula {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);USE($3);
 }
| NOT pathformula {
  if($2!=NULL)
    $$ = new modal_formula(3, $2);
  else
    $$ = NULL;
 }
| pathformula IMPLIES pathformula {
  if($1!=NULL && $3!=NULL)
    $$ = new modal_formula(4, $1, $3);
  else
    $$ = NULL;
 }
| pathformula AND ctlsformula {
  if($1!=NULL && $3!=NULL)
    $$ = new modal_formula(1, $1, $3);
  else
    $$ = NULL;
 }
| pathformula OR ctlsformula {
  if($1!=NULL && $3!=NULL)
    $$ = new modal_formula(2, $1, $3);
  else
    $$ = NULL;
 }
| pathformula IMPLIES ctlsformula {
  if($1!=NULL && $3!=NULL)
    $$ = new modal_formula(4, $1, $3);
  else
    $$ = NULL;
 }
| ctlsformula AND pathformula {
  if($1!=NULL && $3!=NULL)
    $$ = new modal_formula(1, $1, $3);
  else
    $$ = NULL;
 }
| ctlsformula OR pathformula {
  if($1!=NULL && $3!=NULL)
    $$ = new modal_formula(2, $1, $3);
  else
    $$ = NULL;
 }
| ctlsformula IMPLIES pathformula {
  if($1!=NULL && $3!=NULL)
    $$ = new modal_formula(4, $1, $3);
  else
    $$ = NULL;
 }
| G pathformula {
  // LTL G operator
  if($2!=NULL) {
    $$ = new modal_formula(61, $2);
  } else {
    $$ = NULL;
  }
 }
| F pathformula {
  // LTL F operator
  if($2!=NULL) {
    $$ = new modal_formula(62, $2);
  } else {
    $$ = NULL;
  }
 }
| X pathformula {
  // LTL X operator
  if($2!=NULL) {
    $$ = new modal_formula(63, $2);
  } else {
    $$ = NULL;
  }
 }
| pathformula UNTIL pathformula {
  // LTL U operator.
  if($1!=NULL && $3!=NULL) {
    $$ = new modal_formula(64, $1, $3);
  }
  else {
    if($1!=NULL) {
      free($1);
    }
    if($3!=NULL) {
      free($3);
    }
    $$ = NULL;
  }
 }
| ctlsformula {
  $$ = $1;
 };

/* CTL*: state formulae */
ctlsformula: LB ctlsformula RB {
  $$ = $2;
 }
| error ctlsformula RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| LB ctlsformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| error pathformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| ctlsformula AND ctlsformula {
  if($1!=NULL && $3!=NULL)
    $$ = new modal_formula(1, $1, $3);
  else
    $$ = NULL;
 }
| ctlsformula OR ctlsformula {
  if($1!=NULL && $3!=NULL)
    $$ = new modal_formula(2, $1, $3);
  else
    $$ = NULL;
 }
| ctlsformula error ctlsformula {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);USE($3);
 }
| NOT ctlsformula {
  if($2!=NULL)
    $$ = new modal_formula(3, $2);
  else
    $$ = NULL;
 }
| error ctlsformula {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
 }
| ctlsformula IMPLIES ctlsformula {
  if($1!=NULL && $3!=NULL)
    $$ = new modal_formula(4, $1, $3);
  else
    $$ = NULL;
 }
| K epistemicprefixctls {
  if($2!=NULL) {
    atomic_proposition *ap = new atomic_proposition($2->first);
    modal_formula *a = new modal_formula(ap);
    $$ = new modal_formula(30, a, $2->second);
    free($2);
  } else
    $$ = NULL;
 }
| GK gepistemicprefixctls {
  // Knowledge in a group (everybody knows)
  if($2!=NULL) {
    atomic_proposition *ap = new atomic_proposition($2->first);
    modal_formula *a = new modal_formula(ap);
    $$ = new modal_formula(31, a, $2->second);
    free($2);
  } else
    $$ = NULL;
 }
| GCK gepistemicprefixctls {
  // Common knowledge in a group
  if($2!=NULL) {
    atomic_proposition *ap = new atomic_proposition($2->first);
    modal_formula *a = new modal_formula(ap);
    $$ = new modal_formula(32, a, $2->second);
    free($2);
  } else
    $$ = NULL;
 }
| DK gepistemicprefixctls {
  // Distributed knowledge in a group
  if($2!=NULL) {
    atomic_proposition *ap = new atomic_proposition($2->first);
    modal_formula *a = new modal_formula(ap);
    $$ = new modal_formula(42, a, $2->second);
    free($2);
  } else
    $$ = NULL;
 }
| error epistemicprefixctls {
  $$ = NULL;
  driver.syntax_error = true;
 }
| error gepistemicprefixctls {
  $$ = NULL;
  driver.syntax_error = true;
 }
| A pathformula {
  if($2!=NULL)
    $$ = new modal_formula(50, $2);
  else
    $$ = NULL;
 }
| E pathformula {
  if($2!=NULL)
    $$ = new modal_formula(51, $2);
  else
    $$ = NULL;
 }
| terminalformula {
  $$ = $1;
};

epistemicprefixctls: LB ID COMMA ctlsformula RB{
    if($2!=NULL && $4!=NULL) {
      int i = search_string_table($2);
      if(i>=0) {
	$$ = new pair<string *, modal_formula *>((*string_table)[i], $4);
	free($2);
      } else {
	$$ = new pair<string *, modal_formula *>($2, $4);
	string_table->push_back($2);
      }
    } else
    $$ = NULL;
 }
| error ID COMMA ctlsformula RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| LB ID error ctlsformula RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| LB ID COMMA ctlsformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| error ID error ctlsformula RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| error ID COMMA ctlsformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| LB ID error ctlsformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| error ID error ctlsformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| LB ENVIRONMENT COMMA ctlsformula RB{
  if($4!=NULL)
    $$ = new pair<string *, modal_formula *>((*string_table)[0], $4);
  else
    $$ = NULL;
 }
| error ENVIRONMENT COMMA ctlsformula RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($4);
 }
| LB ENVIRONMENT error ctlsformula RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($4);
 }
| LB ENVIRONMENT COMMA ctlsformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($4);
 }
| error ENVIRONMENT error ctlsformula RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($4);
 }
| error ENVIRONMENT COMMA ctlsformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($4);
 }
| LB ENVIRONMENT error ctlsformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($4);
 }
| error ENVIRONMENT error ctlsformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($4);
 };

gepistemicprefixctls: LB ID COMMA ctlsformula RB{
    if($2!=NULL && $4!=NULL) {
      int i = search_string_table($2);
      if(i>=0) {
	$$ = new pair<string *, modal_formula *>((*string_table)[i], $4);
	free($2);
      } else {
	$$ = new pair<string *, modal_formula *>($2, $4);
	string_table->push_back($2);
      }
    } else
      $$ = NULL;
 }
| error ID COMMA ctlsformula RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| LB ID error ctlsformula RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| LB ID COMMA ctlsformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| error ID error ctlsformula RB {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| error ID COMMA ctlsformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| LB ID error ctlsformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 }
| error ID error ctlsformula error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($2);
  USE($4);
 };

terminalformula: ID { 
  if($1!=NULL) {
    atomic_proposition *ap;
    int i = search_string_table($1);
    if(i>=0) {
      ap = new atomic_proposition((*string_table)[i]);
      free($1);
    } else {
      ap = new atomic_proposition($1);
      string_table->push_back($1);
    }
    $$ = new modal_formula(ap);
  } else
    $$ = NULL;
  }
| ID DOT GREENSTATES {
  if($1!=NULL) {
    string *newname = new string(*$1 + ".GreenStates");
    atomic_proposition *ap;
    int i = search_string_table(newname);
    if(i>=0) {
      ap = new atomic_proposition((*string_table)[i]);
      free(newname);
    } else {
      ap = new atomic_proposition(newname);
      string_table->push_back(newname);
    }
    free($1);
    $$ = new modal_formula(ap);
  } else
    $$ = NULL;
 }
| ID DOT REDSTATES {
  if($1!=NULL) {
    string *newname = new string(*$1 + ".RedStates");
    atomic_proposition *ap;
    int i = search_string_table(newname);
    if(i>=0) {
      ap = new atomic_proposition((*string_table)[i]);
      free(newname);
    } else {
      ap = new atomic_proposition(newname);
      string_table->push_back(newname);
    }
    free($1);
    $$ = new modal_formula(ap);
  } else
    $$ = NULL;
 }
| ENVIRONMENT DOT GREENSTATES {
    string *newname = new string("Environment.GreenStates");
    atomic_proposition *ap;
    int i = search_string_table(newname);
    if(i>=0) {
      ap = new atomic_proposition((*string_table)[i]);
      free(newname);
    } else {
      ap = new atomic_proposition(newname);
      string_table->push_back(newname);
    }
    $$ = new modal_formula(ap);
 }
| ENVIRONMENT DOT REDSTATES {
  string *newname = new string("Environment.RedStates");
  atomic_proposition *ap;
  int i = search_string_table(newname);
  if(i>=0) {
    ap = new atomic_proposition((*string_table)[i]);
    free(newname);
  } else {
    ap = new atomic_proposition(newname);
    string_table->push_back(newname);
  }
  $$ = new modal_formula(ap);
 }
| ID DOT error {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
 }
| ID error GREENSTATES {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
 }
| ID error REDSTATES {
  $$ = NULL;
  driver.syntax_error = true;
  USE($1);
 }
| error {
  $$ = NULL;
  driver.syntax_error = true;
  };

%%
void
yy::mcmas_parser::error (const yy::mcmas_parser::location_type& l,
                          const std::string& m)
{
  driver.error (l, m);
}
