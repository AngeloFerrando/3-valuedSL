#include <ctime>
#include "types.hh"
#include "utilities.hh"

using namespace std;

bool_expression::bool_expression()
{
  op = 4;     // encode "other" branch in protocol
}

bool_expression::bool_expression(unsigned char o, Object * obj1)
{       // single operand
  op = o;
  operands[0] = obj1;
  operands[1] = NULL;
}

bool_expression::bool_expression(unsigned char o, Object * obj1,
                                 Object * obj2)
{       // two operands
  op = o;
  operands[0] = obj1;
  operands[1] = obj2;
}

bool_expression::~bool_expression()
{
	switch (op) {
	case 0:
		//delete (logic_expression *)operands[0];
		break;
	case 1:
	case 2:
		if(((bool_expression *)operands[0])->get_op() != 0)
			delete (bool_expression *)operands[0]; 
		if(((bool_expression *)operands[1])->get_op() != 0)
			delete (bool_expression *)operands[1];
		break;
	case 3:
		if(((bool_expression *)operands[0])->get_op() != 0)
			delete (bool_expression *)operands[0];
		break;
	}
}

unsigned char
bool_expression::get_op()
{
  return op;
}

bool
bool_expression::is_other_branch()
{
  if (op == 4)
    return true;
  else
    return false;
}

Object *
bool_expression::get_operand(unsigned char i)
{
  if (i > 1 || (i == 1 && (op == 0 || op == 3))) {
    cout << "error: bool operand " << i << " does not exist!" << endl;
    exit(1);
  } else if (operands[i] == NULL) {
    cout << "error: bool operand " << i << " is undefined!" << endl;
    exit(1);
  } else
    return (operands[i]);
}

bool
bool_expression::equal_to(bool_expression * expr)
{
  if (op == expr->get_op())
    switch (op) {
    case 0:
      return ((logic_expression *) (operands[0]))->
        equal_to((logic_expression *) expr->get_operand(0));
    case 1:
    case 2:
      return ((bool_expression *) (operands[0]))->
        equal_to((bool_expression *) expr->get_operand(0))
        && ((bool_expression *) (operands[1]))->
        equal_to((bool_expression *) expr->get_operand(1));
    case 3:
      return ((bool_expression *) (operands[0]))->
        equal_to((bool_expression *) expr->get_operand(0));
    case 4:
    case 5:
      return true;
    }

  return false;
}

bool
bool_expression::equal_to(expression * e1, expression * e2)
{
  if (op == 0) {
    return ((logic_expression *)operands[0])->equal_to(e1, e2);
  }

  return false;
}

string
bool_expression::to_string()
{
  if (op == 0)
    return ((logic_expression *) (operands[0]))->to_string();
  else if (op == 1)
    return ((bool_expression *) (operands[0]))->to_string() + " and " +
      ((bool_expression *) (operands[1]))->to_string();
  else if (op == 2)
    return ((bool_expression *) (operands[0]))->to_string() + " or " +
      ((bool_expression *) (operands[1]))->to_string();
  else if (op == 3)
    return "! " + ((bool_expression *) (operands[0]))->to_string();
  else if (op == 4)
    return "Other";
  else if (op == 5)
    return "TRUE";
  else if (op == 6)
    return "FALSE";
  return "error: should not happen.";
}

bool
bool_expression::check_var_and_value_flat(map< string, basictype * >*obsvars,
                                          map< string, basictype * >*vars,
                                          string agent_name, map< string,
                                          basic_agent * >*global_actions)
{
  if (op == 0)      // logic_expression
    return ((logic_expression *) operands[0])->check_evolution(obsvars, vars,
                                                               agent_name,
                                                               global_actions);
  else if (op == 3)   // not operaror
    return ((bool_expression *) operands[0])->
      check_var_and_value_flat(obsvars, vars, agent_name, global_actions);
  else if (op == 1 || op == 2) {
    vector< bool_expression * >*expr_vector =
      new vector< bool_expression * >();
    ((bool_expression *) operands[0])->collect_exprs(expr_vector, op);
    ((bool_expression *) operands[1])->collect_exprs(expr_vector, op);
    bool result = true;
    for (unsigned int i = 0; i < expr_vector->size(); i++) {
      result = result
        && (*expr_vector)[i]->check_var_and_value_flat(obsvars, vars,
                                                       agent_name,
                                                       global_actions);
    }
    return result;
  } else if (op == 4)
    return true;
  else
    return false;
}

bool
bool_expression::check_evolution_flat(map< string, basictype * >*obsvars,
                                      map< string, basictype * >*vars,
                                      string agent_name, map< string,
                                      basic_agent * >*global_actions)
{
  if (op == 0)      // logic_expression
    return ((logic_expression *) operands[0])->check_evolution(obsvars, vars,
                                                               agent_name,
                                                               global_actions);
  else if (op == 3)   // not operaror
    return ((bool_expression *) operands[0])->check_evolution_flat(obsvars,
                                                                   vars,
                                                                   agent_name,
                                                                   global_actions);
  else if (op == 1 || op == 2) {
    vector< bool_expression * >*expr_vector =
      new vector< bool_expression * >();
    ((bool_expression *) operands[0])->collect_exprs(expr_vector, op);
    ((bool_expression *) operands[1])->collect_exprs(expr_vector, op);
    bool result = true;
    for (unsigned int i = 0; i < expr_vector->size(); i++) {
      result = result
        && (*expr_vector)[i]->check_evolution_flat(obsvars, vars, agent_name,
                                                   global_actions);
    }
    return result;
  } else
    return false;
}

bool
bool_expression::check_global_consistency_flat(map< string, map< string,
                                               basictype * > >*vars)
{
  if (op == 0)      // logic_expression
    return ((logic_expression *) operands[0])->check_global_consistency(vars);
  else if (op == 3)   // not operaror
    return ((bool_expression *) operands[0])->
      check_global_consistency_flat(vars);
  else if (op == 1 || op == 2) {
    vector< bool_expression * >*expr_vector =
      new vector< bool_expression * >();
    ((bool_expression *) operands[0])->collect_exprs(expr_vector, op);
    ((bool_expression *) operands[1])->collect_exprs(expr_vector, op);
    bool result = true;
    for (unsigned int i = 0; i < expr_vector->size(); i++) {
      result = result
        && (*expr_vector)[i]->check_global_consistency_flat(vars);
    }
    return result;
  } else
    return false;
}

void
bool_expression::collect_exprs(vector< bool_expression * >*expr_vector,
                               unsigned int type)
{
  if (op == type) {
    ((bool_expression *) operands[0])->collect_exprs(expr_vector, type);
    ((bool_expression *) operands[1])->collect_exprs(expr_vector, type);
  } else
    expr_vector->push_back(this);
}

BDD
bool_expression::encode_bdd_flat(bdd_parameters * para, BDD base)
{
  if (op == 0) {    // logic_expression
    return ((logic_expression *) operands[0])->encode_bdd(para, base);
  } else if (op == 3) {   // not operaror
    return !((bool_expression *) operands[0])->encode_bdd_flat(para, base);
  } else if (op == 1) {   // and operaror
    vector< bool_expression * >*expr_vector =
      new vector< bool_expression * >();
    ((bool_expression *) operands[0])->collect_exprs(expr_vector, op);
    ((bool_expression *) operands[1])->collect_exprs(expr_vector, op);
    BDD result = para->bddmgr->bddOne();
    for (unsigned int i = 0; i < expr_vector->size(); i++) {
      result = result * (*expr_vector)[i]->encode_bdd_flat(para, base);
    }
    return result;
  } else if (op == 2) {   // or operaror
    vector< bool_expression * >*expr_vector =
      new vector< bool_expression * >();
    ((bool_expression *) operands[0])->collect_exprs(expr_vector, op);
    ((bool_expression *) operands[1])->collect_exprs(expr_vector, op);
    BDD result = para->bddmgr->bddZero();
    for (unsigned int i = 0; i < expr_vector->size(); i++) {
      result = result + (*expr_vector)[i]->encode_bdd_flat(para, base);
    }
    return result;
  } else if (op == 5) {   // true
    return para->bddmgr->bddOne();
  } else if (op == 6) {   // false
    return para->bddmgr->bddZero();
  } else {
    return base;
  }
}

