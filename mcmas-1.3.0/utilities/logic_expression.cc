#include <ctime>
#include "types.hh"
#include "utilities.hh"

using namespace std;

logic_expression::logic_expression(unsigned char o, expression * e1,
                                   expression * e2)
{
  op = o;
  operands[0] = e1;
  operands[1] = e2;
}

logic_expression::~logic_expression()
{
	/* 0: variable, 1: bool value, 2: int value, 3: enum value, 4: action 
     5: plus, 6: minus, 7: times, 8: divide (arithmetic_expression)
     9: &, 10: |, 11: ~, 12: ^ (bit_expression)
   */
	for(int i=0; i<2; i++) {
		switch(operands[i]->get_type()) {
		case 0: /*delete (variable *) operands[i];*/ break;
		case 1: delete (bool_value *) operands[i]; break;
		case 2: delete (int_value *) operands[i]; break;
		case 3: delete (enum_value *) operands[i]; break;
		case 4: delete (laction *) operands[i]; break;
		case 5: 
		case 6: 
		case 7: 
		case 8: delete (arithmetic_expression *) operands[i]; break;
		case 9: 
		case 10: 
		case 11: 
		case 12: delete (bit_expression *) operands[i]; break;			
		}
	}
}

unsigned char
logic_expression::get_op()
{
  return op;
}

expression *
logic_expression::get_operand(unsigned char i)
{
  if (i > 1) {
    cout << "error: logic operand " << i << " does not exist!" << endl;
    exit(1);
  } else if (operands[i] == NULL) {
    cout << "error: logic operand " << i << " is undefined!" << endl;
    exit(1);
  } else
    return (operands[i]);
}

bool
logic_expression::equal_to(logic_expression * expr)
{
  if (op == expr->get_op())
    return ((expression *) (operands[0]))->equal_to(expr->get_operand(0)) &&
      ((expression *) (operands[1]))->equal_to(expr->get_operand(1));

  return false;
}

bool
logic_expression::equal_to(expression * e1, expression * e2)
{
	return ((expression *) (operands[0]))->equal_to(e1) &&
		((expression *) (operands[1]))->equal_to(e2);
}

string
logic_expression::to_string()
{
  string opstr;
  if (op == 0)
    opstr = "=";
  else if (op == 1)
    opstr = "<>";
  else if (op == 2)
    opstr = "<";
  else if (op == 3)
    opstr = "<=";
  else if (op == 4)
    opstr = ">";
  else if (op == 5)
    opstr = ">=";
  return ((expression *) (operands[0]))->to_string() + opstr +
    ((expression *) (operands[1]))->to_string();
}

bool
logic_expression::check_evolution(map< string, basictype * >*obsvars,
                                  map< string, basictype * >*vars,
                                  string agent_name, map< string,
                                  basic_agent * >*global_actions)
{
  unsigned char left = operands[0]->get_type(); // left hand side
  unsigned char right = operands[1]->get_type();  // right hand side
  bool left_var = true;
  bool right_var = true;

  if (left == 4) {
    map< string, basic_agent * >::iterator p;
    string act_name = ((variable *) operands[1])->get_variable_name();
    bool f = ((laction *) operands[0])->is_agent_name_null();
    string ag_name =
      f ? agent_name : ((laction *) operands[0])->get_agent_name();

    p = global_actions->find(ag_name);
    if (p == global_actions->end()) {
      cout << "        action " << act_name << " is not found in agent " <<
        ag_name << endl;
      return false;
    }

    if (f) {
      ((laction *) operands[0])->set_agent_name(new string(agent_name));
      ((laction *) operands[0])->set_agent((*p).second);
    } else
      ((laction *) operands[0])->set_agent((*p).second);

    set< string > *acts = (*p).second->get_actions();
    set< string >::iterator s = acts->find(act_name);
    if (s == acts->end()) {
      cout << "        action " << act_name << " is not found in agent " <<
        ag_name << endl;
      return false;
    } else
      return true;
  } else if (left == 0) { // left hand side is a variable, or an enumerate value 
    variable *v1 = ((variable *) operands[0]);
    string vs = v1->get_variable_name();
    map< string, basictype * >::iterator p;
    if (v1->is_agent_name_null()) { // local variable
      p = vars->find(vs);
      if (p == vars->end())
        left_var = false;
    } else {
      p = obsvars->find(vs);
      if (p == obsvars->end())
        left_var = false;
    }
    if (right == 0) {   // right hand side could be a variable or a enumerate value
      variable *v2 = ((variable *) operands[1]);
      string vs1 = v2->get_variable_name();
      map< string, basictype * >::iterator p1;
      if (v2->is_agent_name_null()) { // local variable
        p1 = vars->find(vs1);
        if (p1 == vars->end())
          right_var = false;
      } else {
        p1 = obsvars->find(vs1);
        if (p1 == obsvars->end())
          right_var = false;
      }
      if (left_var && right_var) {  // both sides are variables
        //check if both sides have the same type.
        unsigned char t1 = p->second->get_type(); //lhs' type
        unsigned char t2 = p1->second->get_type();  //rhs' type
        if (t1 == t2) {   // same type
          if (t1 == 3) {  // enumerate type
            if (op != 0 && op != 1) {
              cout <<
                "        only '=' and '<>' are allowed for enumeration variables."
                   << endl;
              return false;
            }
            set< string > *s1 = ((enumerate *) (p->second))->get_enumvalue();
            set< string > *s2 =
              ((enumerate *) (p1->second))->get_enumvalue();
            if (options["subset"] == 0) {
              if (s1->size() == s2->size()) { // same size
                bool equal = true;
                for (set< string >::iterator i = s1->begin(); i != s1->end();
                     i++)
                  if (s2->find(*i) == s2->end()) {
                    equal = false;
                    break;
                  }
                if (equal) {
                  // add a link in variable to its type
                  ((variable *) operands[0])->set_var_type(p->second);
                  ((variable *) operands[1])->set_var_type(p1->second);
                  return true;
                } else {
                  cout << "        " << vs << " and " << vs1 <<
                    " do not have the same enumerate type." << endl;
                  return false;
                }
              } else {
                cout << "        " << vs << " and " << vs1 <<
                  " do not have the same enumerate type." << endl;
                return false;
              }
            } else {
              bool equal = true;
              if (s1->size() < s2->size()) {  // same size
                for (set< string >::iterator i = s1->begin(); i != s1->end();
                     i++)
                  if (s2->find(*i) == s2->end()) {
                    equal = false;
                    break;
                  }
                if (equal) {
                  // add a link in variable to its type
                  ((variable *) operands[0])->set_var_type(p->second);
                  ((variable *) operands[1])->set_var_type(p1->second);
                  return true;
                } else {
                  cout << "        " << vs << " is not a subset of " << vs1 <<
                    "." << endl;
                  return false;
                }
              } else {
                for (set< string >::iterator i = s2->begin(); i != s2->end();
                     i++)
                  if (s1->find(*i) == s1->end()) {
                    equal = false;
                    break;
                  }
                if (equal) {
                  // add a link in variable to its type
                  ((variable *) operands[0])->set_var_type(p->second);
                  ((variable *) operands[1])->set_var_type(p1->second);
                  return true;
                } else {
                  cout << "        " << vs1 << " is not a subset of " << vs <<
                    "." << endl;
                  return false;
                }
              }
            }
          } else {
            if (t1 == 1 && op != 0 && op != 1) {
              cout <<
                "        only '=' and '<>' are allowed for boolean variables."
                   << endl;
              return false;
            }
            ((variable *) operands[0])->set_var_type(p->second);
            ((variable *) operands[1])->set_var_type(p1->second);
            return true;
          }
        } else {
          cout << "        " << vs << " and " << vs1 <<
            " have different type." << endl;
          return false;
        }
      } else if (left_var && !right_var) {  // lhs is a variable and rhs is an enumerate value
        if (op != 0 && op != 1) {
          cout <<
            "        only '=' and '<>' are allowed for enumeration variables."
               << endl;
          return false;
        }
        unsigned char t1 = p->second->get_type(); //lhs' type
        if (t1 == 3) {    // lhs must be enumerate
          set< string > *s1 = ((enumerate *) (p->second))->get_enumvalue();
          if (s1->find(vs1) != s1->end()) { //find a matched value in the enumerate type
            // add a link in lhs to its type
            ((variable *) operands[0])->set_var_type(p->second);
            //change the rhs to be an enumerate value
            operands[1] = new enum_value(new string(vs1));
            return true;
          } else {
            cout << "        " << vs << " does not have the value " << vs1 <<
              endl;
            return false;
          }
        } else {
          cout << "        " << vs << " must have an enumerate type." << endl;
          return false;
        }
      } else if (!left_var && right_var) {  // lhs is an enumerate value and rhs is a variable
        if (op != 0 && op != 1) {
          cout <<
            "        only '=' and '<>' are allowed for enumeration variables."
               << endl;
          return false;
        }
        unsigned char t2 = p1->second->get_type();  //rhs' type
        if (t2 == 3) {    // rhs must be enumerate
          set< string > *s2 = ((enumerate *) (p1->second))->get_enumvalue();
          if (s2->find(vs) != s2->end()) {  //find a matched value in the enumerate type
            // add a link in rhs to its type
            ((variable *) operands[1])->set_var_type(p1->second);
            //change the lhs to be an enumerate value
            operands[0] = new enum_value(new string(vs));
            return true;
          } else {
            cout << "        " << vs1 << " does not have the value " << vs <<
              endl;
            return false;
          }
        } else {
          cout << "        " << vs1 << " must have an enumerate type." <<
            endl;
          return false;
        }
      } else {
        cout << "        " << vs << " or " << vs1 << " must be a variable." <<
          endl;
        return false;
      }
    } else if (left_var) {
      left = p->second->get_type();
      if (right == 1) {   // right hand side is a boolean value
        if (left != 1) {
          cout << "         " << vs << " in " << to_string() <<
            " is not a Boolean variable." << endl;
          return false;
        }
        if (op == 0 || op == 1) { // only equality is allowed here
          // add a link in variable to its type
          ((variable *) operands[0])->set_var_type(p->second);
          return true;
        } else {
          cout << "        only equality or inequality test is allowed in " <<
            to_string() << "." << endl;
          return false;
        }
      } else if (right == 2) {  // right hand side is an integer
        if (left != 2) {
          cout << "         " << vs << " in " << to_string() <<
            " is not a bounded integer variable." << endl;
          return false;
        }
        int vs1 = ((int_value *) operands[1])->get_value();
        if (((rangedint *) (p->second))->is_valid_value(vs1)) { // the value is in the correct range
          // add a link in variable to its type
          ((variable *) operands[0])->set_var_type(p->second);
          return true;
        } else {
          cout << "        " << vs1 << " is out of bound in " << to_string()
               << "." << endl;
          return false;
        }
      } else if (right == 3) {  // right hand side is an enumerate value. It cannot happen. But we still check it.
        cout << "        enumerate value cannot appear here." << endl;
        if (left != 3) {
          cout << "         " << vs << " in " << to_string() <<
            " is not an enumeration variable." << endl;
          return false;
        }
        if (op == 0 || op == 1) { // only equality is allowed here
          string vs1 = ((enum_value *) operands[1])->get_value();
          set< string > *s1 = ((enumerate *) (p->second))->get_enumvalue();
          if (s1->find(vs1) != s1->end()) { //find a matched value in the enumerate type
            // add a link in lhs to its type
            ((variable *) operands[0])->set_var_type(p->second);
            return true;
          } else {
            cout << "        " << vs << " does not have the value " << vs1 <<
              endl;
            return false;
          }
        } else {
          cout << "        only equality or inequality test is allowed in " <<
            to_string() << "." << endl;
          return false;
        }
      } else if (right >= 5 && right <= 8) {  // right hand side is an arithmetic expression
        if (left == 2 &&
            ((arithmetic_expression *) operands[1])->
            check_var_and_value(obsvars, vars)) {
          // add a link in lhs to its type
          ((variable *) operands[0])->set_var_type(p->second);
          return true;
        } else {
          cout << "        " << vs << "does not have integer type or " <<
            ((arithmetic_expression *) operands[1])->to_string() <<
            " is not a correct arithmetic expression." << endl;
          return false;
        }
      } else {      // right hand side is a bit expression
        if (op > 1) {
          cout << "        only equality or inequality test is allowed in " <<
            to_string() << "." << endl;
          return false;
        }
        if (left == 1 &&
            ((bit_expression *) operands[1])->check_var_and_value(obsvars,
                                                                  vars)) {
          // add a link in lhs to its type
          ((variable *) operands[0])->set_var_type(p->second);
          return true;
        } else {
          cout << "        " << vs << "does not have boolean type or " <<
            ((bit_expression *) operands[1])->to_string() <<
            " is not a correct bit expression." << endl;
          return false;
        }
      }
    } else {
      cout << "        " << vs << " must be a variable." << endl;
      return false;
    }
  } else if (right == 0) {  // right hand side is a variable 
    variable *v2 = ((variable *) operands[1]);
    string vs1 = ((variable *) operands[1])->get_variable_name();
    map< string, basictype * >::iterator p1;
    if (v2->is_agent_name_null()) { // local variable
      p1 = vars->find(vs1);
      if (p1 == vars->end())
        right_var = false;
    } else {
      p1 = obsvars->find(vs1);
      if (p1 == obsvars->end())
        right_var = false;
    }
    if (right_var) {
      right = p1->second->get_type();
      if (left == 1) {    // left hand side is a boolean value
        if (right != 1) {
          cout << "         " << vs1 << " in " << to_string() <<
            " is not a Boolean variable." << endl;
          return false;
        }
        if (op == 0 || op == 1) { // only equality is allowed here
          // add a link in variable to its type
          ((variable *) operands[1])->set_var_type(p1->second);
          return true;
        } else {
          cout << "        only equality or inequality test is allowed in " <<
            to_string() << "." << endl;
          return false;
        }
      } else if (left == 2) { // left hand side is an integer
        if (right != 2) {
          cout << "         " << vs1 << " in " << to_string() <<
            " is not a bounded integer variable." << endl;
          return false;
        }
        int vs = ((int_value *) operands[0])->get_value();
        if (((rangedint *) (p1->second))->is_valid_value(vs)) { // the value is in the correct range
          // add a link in variable to its type
          ((variable *) operands[1])->set_var_type(p1->second);
          return true;
        } else {
          cout << "        " << vs << " is out of bound in " << to_string() <<
            "." << endl;
          return false;
        }
      } else if (left == 3) { // left hand side is an enumerate value. It cannot happen. But we still check it.
        if (right != 3) {
          cout << "         " << vs1 << " in " << to_string() <<
            " is not an enumeration  variable." << endl;
          return false;
        }
        if (op == 0 || op == 1) { // only equality is allowed here
          string vs = ((enum_value *) operands[0])->get_value();
          set< string > *s2 = ((enumerate *) (p1->second))->get_enumvalue();
          if (s2->find(vs) != s2->end()) {  //find a matched value in the enumerate type
            // add a link in lhs to its type
            ((variable *) operands[1])->set_var_type(p1->second);
            return true;
          } else {
            cout << "        " << vs1 << " does not have the value " << vs <<
              endl;
            return false;
          }
        } else {
          cout << "        only equality or inequality test is allowed in " <<
            to_string() << "." << endl;
          return false;
        }
      } else if (left >= 5 && left <= 8) {  // left hand side is an arithmetic expression
        if (right == 2 &&
            ((arithmetic_expression *) operands[0])->
            check_var_and_value(obsvars, vars)) {
          // add a link in lhs to its type
          ((variable *) operands[1])->set_var_type(p1->second);
          return true;
        } else {
          cout << "        " << vs1 << "does not have integer type or " <<
            ((arithmetic_expression *) operands[0])->to_string() <<
            " is not a correct arithmetic expression." << endl;
          return false;
        }
      } else {      // left hand side is a bit expression
        if (op > 1) {
          cout << "        only equality or inequality test is allowed in " <<
            to_string() << "." << endl;
          return false;
        }
        if (right == 1 &&
            ((bit_expression *) operands[0])->check_var_and_value(obsvars,
                                                                  vars)) {
          // add a link in lhs to its type
          ((variable *) operands[1])->set_var_type(p1->second);
          return true;
        } else {
          cout << "        " << vs1 << "does not have boolean type or " <<
            ((bit_expression *) operands[0])->to_string() <<
            " is not a correct bit expression." << endl;
          return false;
        }
      }
    } else {
      cout << "        " << vs1 << " must be a variable." << endl;
      return false;
    }
  } else if (left >= 5 && left <= 8) {  // left hand side is an arithmetic expression
    if (right == 2)   // rhs is an integer
      return ((arithmetic_expression *) operands[0])->
        check_var_and_value(obsvars, vars);
    else if (right >= 5 && right <= 8)  // rhs is an arithmetic expression
      return ((arithmetic_expression *) operands[0])->
        check_var_and_value(obsvars, vars)
        && ((arithmetic_expression *) operands[1])->
        check_var_and_value(obsvars, vars);
    else {
      cout << "        right hand side in " << to_string() <<
        " has a wrong type." << endl;
      return false;
    }
  } else if (right >= 5 && right <= 8) {  //right  hand side is an arithmetic expression
    if (left == 2)    // lhs is an integer
      return ((arithmetic_expression *) operands[1])->
        check_var_and_value(obsvars, vars);
    else {
      cout << "        left hand side in " << to_string() <<
        " has a wrong type." << endl;
      return false;
    }
  } else if (left >= 9 && left <= 12) { // left hand side is a bit expression
    if (op > 1) {
      cout << "        only equality or inequality test is allowed in " <<
        to_string() << "." << endl;
      return false;
    }
    if (right == 1)   // rhs is a boolean value
      return ((bit_expression *) operands[0])->check_var_and_value(obsvars,
                                                                   vars);
    else if (right >= 9 && right <= 12) // rhs is a bit expression
      return ((bit_expression *) operands[0])->check_var_and_value(obsvars,
                                                                   vars)
        && ((bit_expression *) operands[1])->check_var_and_value(obsvars,
                                                                 vars);
    else {
      cout << "        right hand side in " << to_string() <<
        " has a wrong type." << endl;
      return false;
    }
  } else if (right >= 9 && right <= 12) { //right  hand side is a bit expression
    if (op > 1) {
      cout << "        only equality or inequality test is allowed in " <<
        to_string() << "." << endl;
      return false;
    }
    if (left == 1)    // lhs is a boolean value
      return ((bit_expression *) operands[1])->check_var_and_value(obsvars,
                                                                   vars);
    else {
      cout << "        left hand side in " << to_string() <<
        " has a wrong type." << endl;
      return false;
    }
  }

  cout << "        illegal logic expression: " << to_string() << endl;
  return false;
}

bool
logic_expression::check_global_consistency(map< string, map< string,
                                           basictype * > >*vars)
{
  unsigned char left = operands[0]->get_type(); // left hand side
  unsigned char right = operands[1]->get_type();  // right hand side
  bool left_var = true;
  bool right_var = true;

  if (left == 0) {    // left hand side is a variable, or an enumerate value 
    variable *v1 = ((variable *) operands[0]);
    string vs = v1->get_variable_name();
    bool left_defined = true;
    map< string, basictype * >::iterator p;
    if (v1->is_agent_name_null())
      left_var = false;
    else {
      string ag_name = v1->get_agent_name();
      map< string, map< string, basictype * > >::iterator gp =
        vars->find(ag_name);
      if (gp == vars->end()) {
        cout << "    undefined agent " << ag_name << endl;
        left_defined = false;
      } else {
        p = gp->second.find(vs);
        if (p == gp->second.end()) {  // the variable is not defined
          cout << "        variable " << vs << " is not defined in agent " <<
            ag_name << endl;
          left_defined = false;
        }
      }
    }
    if (right == 0) {   // right hand side could be a variable or a enumerate value
      variable *v2 = ((variable *) operands[1]);
      string vs1 = v2->get_variable_name();
      bool right_defined = true;
      map< string, basictype * >::iterator p1;
      if (v2->is_agent_name_null())
        right_var = false;
      else {
        string ag_name = v2->get_agent_name();
        map< string, map< string, basictype * > >::iterator gp =
          vars->find(ag_name);
        if (gp == vars->end()) {
          cout << "    undefined agent " << ag_name << endl;
          right_defined = false;
        } else {
          p1 = gp->second.find(vs1);
          if (p1 == gp->second.end()) { // the variable is not defined
            cout << "        variable " << vs1 << " is not defined in agent "
                 << ag_name << endl;
            right_defined = false;
          }
        }
      }
      if (!left_defined || !right_defined)
        return false;
      if (left_var && right_var) {  // both sides are variables
        //check if both sides have the same type.
        unsigned char t1 = p->second->get_type(); //lhs' type
        unsigned char t2 = p1->second->get_type();  //rhs' type
        if (t1 == t2) {   // same type
          if (t1 == 3) {  // enumerate type
            if (op != 0 && op != 1) {
              cout <<
                "        only '=' and '<>' are allowed for enumeration variables."
                   << endl;
              return false;
            }
            set< string > *s1 = ((enumerate *) (p->second))->get_enumvalue();
            set< string > *s2 =
              ((enumerate *) (p1->second))->get_enumvalue();
            if (options["subset"] == 0) {
              if (s1->size() == s2->size()) { // same size
                bool equal = true;
                for (set< string >::iterator i = s1->begin(); i != s1->end();
                     i++)
                  if (s2->find(*i) == s2->end()) {
                    equal = false;
                    break;
                  }
                if (equal) {
                  // add a link in variable to its type
                  ((variable *) operands[0])->set_var_type(p->second);
                  ((variable *) operands[1])->set_var_type(p1->second);
                  return true;
                } else {
                  cout << "        " << vs << " and " << vs1 <<
                    " do not have the same enumerate type." << endl;
                  return false;
                }
              } else {
                cout << "        " << vs << " and " << vs1 <<
                  " do not have the same enumerate type." << endl;
                return false;
              }
            } else {
              bool equal = true;
              if (s1->size() < s2->size()) {  // same size
                for (set< string >::iterator i = s1->begin(); i != s1->end();
                     i++)
                  if (s2->find(*i) == s2->end()) {
                    equal = false;
                    break;
                  }
                if (equal) {
                  // add a link in variable to its type
                  ((variable *) operands[0])->set_var_type(p->second);
                  ((variable *) operands[1])->set_var_type(p1->second);
                  return true;
                } else {
                  cout << "        " << vs << " is not a subset of " << vs1 <<
                    "." << endl;
                  return false;
                }
              } else {
                for (set< string >::iterator i = s2->begin(); i != s2->end();
                     i++)
                  if (s1->find(*i) == s1->end()) {
                    equal = false;
                    break;
                  }
                if (equal) {
                  // add a link in variable to its type
                  ((variable *) operands[0])->set_var_type(p->second);
                  ((variable *) operands[1])->set_var_type(p1->second);
                  return true;
                } else {
                  cout << "        " << vs1 << " is not a subset of " << vs <<
                    "." << endl;
                  return false;
                }
              }
            }
          } else {
            if (t1 == 1 && op != 0 && op != 1) {
              cout <<
                "        only '=' and '<>' are allowed for boolean variables."
                   << endl;
              return false;
            }
            ((variable *) operands[0])->set_var_type(p->second);
            ((variable *) operands[1])->set_var_type(p1->second);
            return true;
          }
        } else {
          cout << "        " << vs << " and " << vs1 <<
            " have different type." << endl;
          return false;
        }
      } else if (left_var && !right_var) {  // lhs is a variable and rhs is an enumerate value
        if (op != 0 && op != 1) {
          cout <<
            "        only '=' and '<>' are allowed for enumeration variables."
               << endl;
          return false;
        }
        unsigned char t1 = p->second->get_type(); //lhs' type
        if (t1 == 3) {    // lhs must be enumerate
          set< string > *s1 = ((enumerate *) (p->second))->get_enumvalue();
          if (s1->find(vs1) != s1->end()) { //find a matched value in the enumerate type
            // add a link in lhs to its type
            ((variable *) operands[0])->set_var_type(p->second);
            //change the rhs to be an enumerate value
            operands[1] = new enum_value(new string(vs1));
            return true;
          } else {
            cout << "        " << vs << " does not have the value " << vs1 <<
              endl;
            return false;
          }
        } else {
          cout << "        " << vs << " must have an enumerate type." << endl;
          return false;
        }
      } else if (!left_var && right_var) {  // lhs is an enumerate value and rhs is a variable
        if (op != 0 && op != 1) {
          cout <<
            "        only '=' and '<>' are allowed for enumeration variables."
               << endl;
          return false;
        }
        unsigned char t2 = p1->second->get_type();  //rhs' type
        if (t2 == 3) {    // rhs must be enumerate
          set< string > *s2 = ((enumerate *) (p1->second))->get_enumvalue();
          if (s2->find(vs) != s2->end()) {  //find a matched value in the enumerate type
            // add a link in rhs to its type
            ((variable *) operands[1])->set_var_type(p1->second);
            //change the lhs to be an enumerate value
            operands[0] = new enum_value(new string(vs));
            return true;
          } else {
            cout << "        " << vs1 << " does not have the value " << vs <<
              endl;
            return false;
          }
        } else {
          cout << "        " << vs1 << " must have an enumerate type." <<
            endl;
          return false;
        }
      } else {
        cout << "        " << vs << " or " << vs1 << " must be a variable." <<
          endl;
        return false;
      }
    } else if (left_var) {
      if (!left_defined)
        return false;
      left = p->second->get_type();
      if (right == 1) {   // right hand side is a boolean value
        if (left != 1) {
          cout << "         " << vs << " in " << to_string() <<
            " is not a Boolean variable." << endl;
          return false;
        }
        if (op == 0 || op == 1) { // only equality is allowed here
          // add a link in variable to its type
          ((variable *) operands[0])->set_var_type(p->second);
          return true;
        } else {
          cout << "        only equality or inequality test is allowed in " <<
            to_string() << "." << endl;
          return false;
        }
      } else if (right == 2) {  // right hand side is an integer
        if (left != 2) {
          cout << "         " << vs << " in " << to_string() <<
            " is not a bounded integer variable." << endl;
          return false;
        }
        int vs1 = ((int_value *) operands[1])->get_value();
        if (((rangedint *) (p->second))->is_valid_value(vs1)) { // the value is in the correct range
          // add a link in variable to its type
          ((variable *) operands[0])->set_var_type(p->second);
          return true;
        } else {
          cout << "        " << vs1 << " is out of bound in " << to_string()
               << "." << endl;
          return false;
        }
      } else if (right == 3) {  // right hand side is an enumerate value. It cannot happen. But we still check it.
        if (left != 3) {
          cout << "         " << vs << " in " << to_string() <<
            " is not an enumeration variable." << endl;
          return false;
        }
        if (op == 0 || op == 1) { // only equality is allowed here
          string vs1 = ((enum_value *) operands[1])->get_value();
          set< string > *s1 = ((enumerate *) (p->second))->get_enumvalue();
          if (s1->find(vs1) != s1->end()) { //find a matched value in the enumerate type
            // add a link in lhs to its type
            ((variable *) operands[0])->set_var_type(p->second);
            return true;
          } else {
            cout << "        " << vs << " does not have the value " << vs1 <<
              endl;
            return false;
          }
        } else {
          cout << "        only equality or inequality test is allowed in " <<
            to_string() << "." << endl;
          return false;
        }
      } else if (right >= 5 && right <= 8) {  // right hand side is an arithmetic expression
        if (left == 2 &&
            ((arithmetic_expression *) operands[1])->
            check_var_and_value(vars)) {
          // add a link in lhs to its type
          ((variable *) operands[0])->set_var_type(p->second);
          return true;
        } else {
          cout << "        " << vs << "does not have integer type or " <<
            ((arithmetic_expression *) operands[1])->to_string() <<
            " is not a correct arithmetic expression." << endl;
          return false;
        }
      } else {      // right hand side is a bit expression   
        if (op > 1) {
          cout << "        only equality or inequality test is allowed in " <<
            to_string() << "." << endl;
          return false;
        }
        if (left == 1 &&
            ((bit_expression *) operands[1])->check_var_and_value(vars)) {
          // add a link in lhs to its type
          ((variable *) operands[0])->set_var_type(p->second);
          return true;
        } else {
          cout << "        " << vs << "does not have boolean type or " <<
            ((bit_expression *) operands[1])->to_string() <<
            " is not a correct bit expression." << endl;
          return false;
        }
      }
    } else {
      cout << "        " << vs << " must be a variable." << endl;
      return false;
    }
  } else if (right == 0) {  // right hand side is a variable 
    variable *v2 = ((variable *) operands[1]);
    string vs1 = ((variable *) operands[1])->get_variable_name();
    map< string, basictype * >::iterator p1;
    if (v2->is_agent_name_null())
      right_var = false;
    else {
      string ag_name = v2->get_agent_name();
      map< string, map< string, basictype * > >::iterator gp =
        vars->find(ag_name);
      if (gp == vars->end()) {
        cout << "    undefined agent " << ag_name << endl;
        return false;
      }
      p1 = gp->second.find(vs1);
      if (p1 == gp->second.end()) { // the variable is not defined
        cout << "        variable " << vs1 << " is not defined in agent " <<
          ag_name << endl;
        return false;
      }
    }
    if (right_var) {
      right = p1->second->get_type();
      if (left == 1) {    // left hand side is a boolean value 
        if (right != 1) {
          cout << "         " << vs1 << " in " << to_string() <<
            " is not a Boolean variable." << endl;
          return false;
        }
        if (op == 0 || op == 1) { // only equality is allowed here
          // add a link in variable to its type
          ((variable *) operands[1])->set_var_type(p1->second);
          return true;
        } else {
          cout << "        only equality or inequality test is allowed in " <<
            to_string() << "." << endl;
          return false;
        }
      } else if (left == 2) { // left hand side is an integer
        if (right != 2) {
          cout << "         " << vs1 << " in " << to_string() <<
            " is not a Boolean variable." << endl;
          return false;
        }
        int vs = ((int_value *) operands[0])->get_value();
        if (((rangedint *) (p1->second))->is_valid_value(vs)) { // the value is in the correct range
          // add a link in variable to its type
          ((variable *) operands[1])->set_var_type(p1->second);
          return true;
        } else {
          cout << "        " << vs << " is out of bound in " << to_string() <<
            "." << endl;
          return false;
        }
      } else if (left == 3) { // left hand side is an enumerate value. It cannot happen. But we still check it.
        if (right != 3) {
          cout << "         " << vs1 << " in " << to_string() <<
            " is not an enumeration variable." << endl;
          return false;
        }
        if (op == 0 || op == 1) { // only equality is allowed here
          string vs = ((enum_value *) operands[0])->get_value();
          set< string > *s2 = ((enumerate *) (p1->second))->get_enumvalue();
          if (s2->find(vs) != s2->end()) {  //find a matched value in the enumerate type
            // add a link in lhs to its type
            ((variable *) operands[1])->set_var_type(p1->second);
            return true;
          } else {
            cout << "        " << vs1 << " does not have the value " << vs <<
              endl;
            return false;
          }
        } else {
          cout << "        only equality or inequality test is allowed in " <<
            to_string() << "." << endl;
          return false;
        }
      } else if (left >= 5 && left <= 8) {  // left hand side is an arithmetic expression
        if (right == 2 &&
            ((arithmetic_expression *) operands[0])->
            check_var_and_value(vars)) {
          // add a link in lhs to its type
          ((variable *) operands[1])->set_var_type(p1->second);
          return true;
        } else {
          cout << "        " << vs1 << "does not have integer type or " <<
            ((arithmetic_expression *) operands[0])->to_string() <<
            " is not a correct arithmetic expression." << endl;
          return false;
        }
      } else {      // left hand side is a bit expression
        if (op > 1) {
          cout << "        only equality or inequality test is allowed in " <<
            to_string() << "." << endl;
          return false;
        }
        if (right == 1 &&
            ((bit_expression *) operands[0])->check_var_and_value(vars)) {
          // add a link in lhs to its type
          ((variable *) operands[1])->set_var_type(p1->second);
          return true;
        } else {
          cout << "        " << vs1 << "does not have boolean type or " <<
            ((bit_expression *) operands[0])->to_string() <<
            " is not a correct bit expression." << endl;
          return false;
        }
      }
    } else {
      cout << "        " << vs1 << " must be a variable." << endl;
      return false;
    }
  } else if (left >= 5 && left <= 8) {  // left hand side is an arithmetic expression
    if (right == 2)   // rhs is an integer
      return ((arithmetic_expression *) operands[0])->
        check_var_and_value(vars);
    else if (right >= 5 && right <= 8)  // rhs is an arithmetic expression
      return ((arithmetic_expression *) operands[0])->
        check_var_and_value(vars)
        && ((arithmetic_expression *) operands[1])->check_var_and_value(vars);
    else {
      cout << "        right hand side in " << to_string() <<
        " has a wrong type." << endl;
      return false;
    }
  } else if (right >= 5 && right <= 8) {  //right  hand side is an arithmetic expression
    if (left == 2)    // lhs is an integer
      return ((arithmetic_expression *) operands[1])->
        check_var_and_value(vars);
    else {
      cout << "        left hand side in " << to_string() <<
        " has a wrong type." << endl;
      return false;
    }
  } else if (left >= 9 && left <= 12) { // left hand side is a bit expression
    if (op > 1) {
      cout << "        only equality or inequality test is allowed in " <<
        to_string() << "." << endl;
      return false;
    }
    if (right == 1)   // rhs is a boolean value
      return ((bit_expression *) operands[0])->check_var_and_value(vars);
    else if (right >= 9 && right <= 12) // rhs is a bit expression
      return ((bit_expression *) operands[0])->check_var_and_value(vars) &&
        ((bit_expression *) operands[1])->check_var_and_value(vars);
    else {
      cout << "        right hand side in " << to_string() <<
        " has a wrong type." << endl;
      return false;
    }
  } else if (right >= 9 && right <= 12) { //right  hand side is a bit expression
    if (op > 1) {
      cout << "        only equality or inequality test is allowed in " <<
        to_string() << "." << endl;
      return false;
    }
    if (left == 1)    // lhs is a boolean value
      return ((bit_expression *) operands[1])->check_var_and_value(vars);
    else {
      cout << "        left hand side in " << to_string() <<
        " has a wrong type." << endl;
      return false;
    }
  }

  cout << "        illegal logic expression: " << to_string() << endl;
  return false;
}

BDD
logic_expression::encode_bdd(bdd_parameters * para, BDD base)
{
  int lhstype = operands[0]->get_type();
  int rhstype = operands[1]->get_type();
  BDD tmpbdd = base;
  BDD tmpbdd1 = para->bddmgr->bddOne();
  int begin, end, begin1;

  if (lhstype == 4) {   // left hand side is an action
    laction *la = (laction *) operands[0];
    basic_agent *ba = la->get_agent();
    begin = ba->get_action_index_begin();
    end = ba->get_action_index_end();
    string act_name = ((variable *) operands[1])->get_variable_name();
    map< string, vector< bool > *>::iterator k =
      ba->get_action_indices()->find(act_name);
    vector< bool > *b = (*k).second;
    for (int i = begin; i <= end; i++)
      tmpbdd = tmpbdd * ((*b)[i - begin] ? (*para->a)[i] : !(*para->a)[i]);
  } else if (lhstype == 0 && rhstype == 0) {  // two variables
    basictype *var_type = ((variable *) operands[0])->get_var_type();
    basictype *var_type1 = ((variable *) operands[1])->get_var_type();
    if (var_type->get_type() != var_type1->get_type()) {
      cout << "Error: only two variables in both sides of " << to_string() <<
        " have different types" << endl;
      exit(0);
    }
    begin = var_type->get_index_begin();
    begin1 = var_type1->get_index_begin();
    if (var_type->get_type() == 1) {  // bool
      if (op != 0 && op != 1) {
        cout << "Error: only EQ and NEQ on bool types are allowed in " <<
          to_string() << endl;
        exit(0);
      }
      tmpbdd1 *=
        ((!(*para->v)[begin] + (*para->v)[begin1]) * ((*para->v)[begin] +
                                                      !(*para->v)[begin1]));
      if (op == 1)
        tmpbdd *= !tmpbdd1;
      else
        tmpbdd *= tmpbdd1;
    } else if (var_type->get_type() == 2) { // rangedint
      ADD rhs =
        ((rangedint *) var_type1)->build_ADD_tree(para->bddmgr, para->addv,
                                                  para->ADD_cache);
      ADD lhs =
        ((rangedint *) var_type)->build_ADD_tree(para->bddmgr, para->addv,
                                                 para->ADD_cache);
      ADD result;
      if (op == 0)
        result = addEQ(para->bddmgr, lhs, rhs);
      else if (op == 1)
        result = addNEQ(para->bddmgr, lhs, rhs);
      else if (op == 2)
        result = addLT(para->bddmgr, lhs, rhs);
      else if (op == 3)
        result = addLE(para->bddmgr, lhs, rhs);
      else if (op == 4)
        result = addGT(para->bddmgr, lhs, rhs);
      else if (op == 5)
        result = addGE(para->bddmgr, lhs, rhs);
      tmpbdd *= result.BddThreshold(1);
    } else {      // enumerate
      if (op != 0 && op != 1) {
        cout << "Error: only EQ and NEQ on enumerate types are allowed in " <<
          to_string() << endl;
        exit(0);
      }
      set< string > *enums1 = ((enumerate *) var_type)->get_enumvalue();
      set< string > *enums2 = ((enumerate *) var_type1)->get_enumvalue();
      if (enums1->size() == enums2->size()) {
        ADD rhs =
          ((enumerate *) var_type1)->build_ADD_tree(para->bddmgr, para->addv,
                                                    para->ADD_cache);
        ADD lhs =
          ((enumerate *) var_type)->build_ADD_tree(para->bddmgr, para->addv,
                                                   para->ADD_cache);
        ADD result =
          (op == 0) ? addEQ(para->bddmgr, lhs, rhs) : addNEQ(para->bddmgr,
                                                             lhs, rhs);
        tmpbdd *= result.BddThreshold(1);
      } else {
        end = var_type->get_index_end();
        int end1 = var_type1->get_index_end();
        BDD tmpbdd2 = para->bddmgr->bddZero();
        set< string > *enums =
          (enums1->size() < enums2->size())? enums1 : enums2;
        for (set< string >::iterator i = enums->begin(); i != enums->end();
             i++) {
          vector< bool > *vb = ((enumerate *) var_type)->get_value_index(*i);
          vector< bool > *vb1 =
            ((enumerate *) var_type1)->get_value_index(*i);
          BDD tmpbdd3 = para->bddmgr->bddOne();
          for (int i = end; i >= begin; i--)
            if ((*vb)[i - begin])
              tmpbdd3 *= (*para->v)[i];
            else
              tmpbdd3 *= !(*para->v)[i];
          for (int i = end1; i >= begin1; i--)
            if ((*vb1)[i - begin1])
              tmpbdd3 *= (*para->v)[i];
            else
              tmpbdd3 *= !(*para->v)[i];
          tmpbdd2 += tmpbdd3;
        }

        if (op == 1)
          tmpbdd *= !tmpbdd2;
        else
          tmpbdd *= tmpbdd2;
      }
    }
  } else if ((lhstype == 1 && rhstype < 9) || (rhstype == 1 && lhstype < 9)) {  // bool value
    variable *var =
      lhstype == 0 ? (variable *) operands[0] : (variable *) operands[1];
    bool_value *value =
      lhstype == 1 ? (bool_value *) operands[0] : (bool_value *) operands[1];
    basictype *var_type = var->get_var_type();
    begin = var_type->get_index_begin();
    if (value->get_value())
      tmpbdd1 *= (*para->v)[begin];
    else
      tmpbdd1 *= !(*para->v)[begin];
    if (op == 1)
      tmpbdd *= !tmpbdd1;
    else
      tmpbdd *= tmpbdd1;
  } else if ((lhstype >= 9 && lhstype <= 12) || (rhstype >= 9 && rhstype <= 12)) {  // bit expression
    BDD lhsbdd, rhsbdd;
		if (lhstype == 1) { // lhs is a constant
			bool_value *value = (bool_value *) operands[0];
			if(value->get_value())
				tmpbdd1 = ((bit_expression *) operands[1])->encode_BDD_true(para->bddmgr, para->v);
			else
				tmpbdd1 = ((bit_expression *) operands[1])->encode_BDD_false(para->bddmgr, para->v);
		} else if (rhstype == 1) { // rhs is a constant
			bool_value *value = (bool_value *) operands[1];
			if(value->get_value())
				tmpbdd1 = ((bit_expression *) operands[0])->encode_BDD_true(para->bddmgr, para->v);
			else
				tmpbdd1 = ((bit_expression *) operands[0])->encode_BDD_false(para->bddmgr, para->v);
		} else if (lhstype == 0) { // lhs is a variable
			variable *var = (variable *) operands[0];
			basictype *var_type = var->get_var_type();
			begin = var_type->get_index_begin();
			tmpbdd1 = ((*para->v)[begin] * ((bit_expression *) operands[1])->encode_BDD_true(para->bddmgr, para->v)) + 
				(!(*para->v)[begin] * ((bit_expression *) operands[1])->encode_BDD_false(para->bddmgr, para->v));
		} else if (rhstype == 0) { // rhs is a variable
			variable *var = (variable *) operands[1];
			basictype *var_type = var->get_var_type();
			begin = var_type->get_index_begin();
			tmpbdd1 = ((*para->v)[begin] * ((bit_expression *) operands[0])->encode_BDD_true(para->bddmgr, para->v)) + 
				(!(*para->v)[begin] * ((bit_expression *) operands[0])->encode_BDD_false(para->bddmgr, para->v));
		} else { // both lhs and rhs are bit expressions
			tmpbdd1 = (((bit_expression *) operands[0])->encode_BDD_true(para->bddmgr, para->v) * ((bit_expression *) operands[1])->encode_BDD_true(para->bddmgr, para->v)) + 
				(((bit_expression *) operands[0])->encode_BDD_false(para->bddmgr, para->v) * ((bit_expression *) operands[1])->encode_BDD_false(para->bddmgr, para->v));
		}

    if (op == 1)
      tmpbdd *= !tmpbdd1;
    else
      tmpbdd *= tmpbdd1;
  } else if (lhstype == 3 || rhstype == 3) {  // enumerate value
    variable *var =
      lhstype == 0 ? (variable *) operands[0] : (variable *) operands[1];
    basictype *var_type = var->get_var_type();
    begin = var_type->get_index_begin();
    end = var_type->get_index_end();
    string value =
      lhstype ==
      3 ? ((enum_value *) operands[0])->
      get_value() : ((enum_value *) operands[1])->get_value();
    vector< bool > *vb = ((enumerate *) var_type)->get_value_index(value);
    for (int i = end; i >= begin; i--)
      if ((*vb)[i - begin])
        tmpbdd1 *= (*para->v)[i];
      else
        tmpbdd1 *= !(*para->v)[i];
    if (op == 1)
      tmpbdd *= !tmpbdd1;
    else
      tmpbdd *= tmpbdd1;
  } else {      // arithmetic expression
    ADD lhs = lhstype == 0 ?
      ((variable *) operands[0])->build_ADD_tree(para->bddmgr, para->addv,
                                                 para->
                                                 ADD_cache) : (lhstype ==
                                                               2 ? para->
                                                               bddmgr->
                                                               constant(((int_value *) operands[0])->get_value()) : ((arithmetic_expression *) operands[0])->build_ADD_tree(para->bddmgr, para->addv, para->ADD_cache));
    ADD rhs =
      rhstype == 0 ? ((variable *) operands[1])->build_ADD_tree(para->bddmgr,
                                                                para->addv,
                                                                para->
                                                                ADD_cache)
      : (rhstype ==
         2 ? para->bddmgr->constant(((int_value *) operands[1])->
                                    get_value()) : ((arithmetic_expression *)
                                                    operands[1])->
         build_ADD_tree(para->bddmgr, para->addv, para->ADD_cache));
    ADD result;

    if (op == 0)
      result = addEQ(para->bddmgr, lhs, rhs);
    else if (op == 1)
      result = addNEQ(para->bddmgr, lhs, rhs);
    else if (op == 2)
      result = addLT(para->bddmgr, lhs, rhs);
    else if (op == 3)
      result = addLE(para->bddmgr, lhs, rhs);
    else if (op == 4)
      result = addGT(para->bddmgr, lhs, rhs);
    else if (op == 5)
      result = addGE(para->bddmgr, lhs, rhs);

    tmpbdd *= result.BddThreshold(1);
  }

  return tmpbdd;
}

