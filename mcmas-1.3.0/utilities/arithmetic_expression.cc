#include <ctime>
#include "types.hh"
#include "utilities.hh"

using namespace std;

arithmetic_expression::arithmetic_expression(unsigned char o, expression * e1, expression * e2):expression(o)
{
  operands[0] = e1;
  operands[1] = e2;
}

arithmetic_expression::~arithmetic_expression()
{
	for(int i=0; i<2; i++) {
		switch(operands[i]->get_type()) {
			//case 0: delete (variable *) operands[i]; break;
		case 2: delete (int_value *) operands[i]; break;
		case 5: 
		case 6: 
		case 7: 
		case 8: delete (arithmetic_expression *) operands[i]; break;
		}
	}
}

expression *
arithmetic_expression::get_operand(unsigned char i)
{
  if (i > 1) {
    cout << "error: arithmetic operand " << i << " does not exist!" << endl;
    exit(1);
  } else if (operands[i] == NULL) {
    cout << "error: arithmetic operand " << i << " is undefined!" << endl;
    exit(1);
  } else
    return (operands[i]);
}

bool
arithmetic_expression::equal_to(arithmetic_expression * expr)
{
  unsigned int op = get_type();
  if (op == expr->get_type())
    return ((expression *) (operands[0]))->equal_to(expr->get_operand(0)) &&
      ((expression *) (operands[1]))->equal_to(expr->get_operand(1));

  return false;
}

bool
arithmetic_expression::equal_to(expression * expr)
{
  if (expr->get_type() == get_type())
    return equal_to((arithmetic_expression *) expr);
  return false;
}

string
arithmetic_expression::to_string()
{
  string opstr;
  unsigned int op = get_type();
  if (op == 0)
    return ((expression *) (operands[0]))->to_string();
  else if (op == 5)
    opstr = "+";
  else if (op == 6)
    opstr = "-";
  else if (op == 7)
    opstr = "*";
  else if (op == 8)
    opstr = "/";
  return ((expression *) (operands[0]))->to_string() + " " + opstr + " " +
    ((expression *) (operands[1]))->to_string();
}

bool
arithmetic_expression::check_var_and_value(map< string,
                                           basictype * >*obsvars,
                                           map< string, basictype * >*vars)
{
  bool flag = true;
  unsigned char left = operands[0]->get_type(); // left hand side
  unsigned char right = operands[1]->get_type();  // right hand side
  if (left == 0) {    // left hand side is a variable
    variable *var = (variable *) operands[0];
    string vs = var->get_variable_name();
    if (var->is_agent_name_null()) {
      map< string, basictype * >::iterator p = vars->find(vs);
      if (p == vars->end()) {
        cout << "        variable " << vs << " is not defined." << endl;
        flag = false;
      } else
        var->set_var_type(p->second);
    } else if (var->get_agent_name() == "Environment") {
      map< string, basictype * >::iterator p = obsvars->find(vs);
      if (p == obsvars->end()) {
        cout << "        variable " << vs << " is not defined." << endl;
        flag = false;
      } else
        var->set_var_type(p->second);
    } else {
      cout << "        variable " << vs << " is not defined." << endl;
      flag = false;
    }
  } else if (left >= 5 && left <= 8) {  //lhs is an arithmetic expression
    flag =
      ((arithmetic_expression *) operands[0])->check_var_and_value(obsvars,
                                                                   vars);
  } else if (left != 2) { // lhs is not an integer
    cout << "        left hand side in" << to_string() << " has a wrong type."
         << endl;
    flag = false;
  }

  if (right == 0) {   // right hand side is a variable
    variable *var = (variable *) operands[1];
    string vs = var->get_variable_name();
    if (var->is_agent_name_null()) {
      map< string, basictype * >::iterator p = vars->find(vs);
      if (p == vars->end()) {
        cout << "        variable " << vs << " is not defined." << endl;
        flag = false;
      } else
        var->set_var_type(p->second);
    } else if (var->get_agent_name() == "Environment") {
      map< string, basictype * >::iterator p = obsvars->find(vs);
      if (p == obsvars->end()) {
        cout << "        variable " << vs << " is not defined." << endl;
        flag = false;
      } else
        var->set_var_type(p->second);
    } else {
      cout << "        variable " << vs << " is not defined." << endl;
      flag = false;
    }
  } else if (right >= 5 && right <= 8) {  //lhs is an arithmetic expression
    flag =
      ((arithmetic_expression *) operands[1])->check_var_and_value(obsvars,
                                                                   vars)
      && flag;
  } else if (right != 2) {  // lhs is not an integer
    cout << "        right hand side in" << to_string() <<
      " has a wrong type." << endl;
    flag = false;
  }
  return flag;
}

bool
arithmetic_expression::check_var_and_value(map< string, map< string,
                                           basictype * > >*vars)
{
  bool flag = true;
  unsigned char left = operands[0]->get_type(); // left hand side
  unsigned char right = operands[1]->get_type();  // right hand side
  if (left == 0) {    // left hand side is a variable
    variable *var = (variable *) operands[0];
    string vs = var->get_variable_name();
    if (var->is_agent_name_null()) {
      cout << "        variable " << vs << " must be accompanied by agent" <<
        endl;
      flag = false;
    } else {
      string ag_name = var->get_agent_name();
      map< string, map< string, basictype * > >::iterator gp =
        vars->find(ag_name);
      if (gp == vars->end()) {
        cout << "    undefined agent " << ag_name << endl;
        return false;
      }
      map< string, basictype * >::iterator p = gp->second.find(vs);
      if (p == gp->second.end()) {
        cout << "        variable " << vs << " is not defined in agent " <<
          ag_name << endl;
        flag = false;
      } else
        var->set_var_type(p->second);
    }
  } else if (left >= 5 && left <= 8) {  //lhs is an arithmetic expression
    flag = ((arithmetic_expression *) operands[0])->check_var_and_value(vars);
  } else if (left != 2) { // lhs is not an integer
    cout << "        left hand side in" << to_string() << " has a wrong type."
         << endl;
    flag = false;
  }

  if (right == 0) {   // right hand side is a variable
    variable *var1 = (variable *) operands[1];
    string vs1 = var1->get_variable_name();
    if (var1->is_agent_name_null()) {
      cout << "        variable " << vs1 << " must be accompanied by agent" <<
        endl;
      flag = false;
    } else {
      string ag_name = var1->get_agent_name();
      map< string, map< string, basictype * > >::iterator gp =
        vars->find(ag_name);
      if (gp == vars->end()) {
        cout << "    undefined agent " << ag_name << endl;
        return false;
      }
      map< string, basictype * >::iterator p = gp->second.find(vs1);
      if (p == gp->second.end()) {
        cout << "        variable " << vs1 << " is not defined in agent " <<
          ag_name << endl;
        flag = false;
      } else
        var1->set_var_type(p->second);
    }
  } else if (right >= 5 && right <= 8) {  //lhs is an arithmetic expression
    flag = ((arithmetic_expression *) operands[1])->check_var_and_value(vars)
      && flag;
  } else if (right != 2) {  // lhs is not an integer
    cout << "        right hand side in" << to_string() <<
      " has a wrong type." << endl;
    flag = false;
  }
  return flag;
}

ADD
arithmetic_expression::build_ADD_tree(Cudd * bddmgr, vector<ADD> * addv,
                                      map< string, ADD > *ADD_cache)
{
  unsigned char op = get_type();
  ADD res;
  ADD lhs = operands[0]->build_ADD_tree(bddmgr, addv, ADD_cache);
  ADD rhs = operands[1]->build_ADD_tree(bddmgr, addv, ADD_cache);
  if (op == 5) {    // plus
    res = lhs + rhs;
  } else if (op == 6) {   // minus
    res = lhs - rhs;
  } else if (op == 7) {   // times
    res = lhs * rhs;
  } else {      // divide
    res = lhs.Divide(rhs);
  }
  return res;
}

BDD
arithmetic_expression::encode_BDD_true(Cudd * bddmgr, vector<BDD> * v)
{
  return bddmgr->bddZero();
}

BDD
arithmetic_expression::encode_BDD_false(Cudd * bddmgr, vector<BDD> * v)
{
  return bddmgr->bddZero();
}

