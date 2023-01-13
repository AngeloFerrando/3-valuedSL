#include <ctime>
#include "types.hh"
#include "utilities.hh"

using namespace std;

variable::variable(string * a_n, string * n):expression(0)
{
  agent_name = a_n;
  name = n;
  var_type = NULL;
}

variable::variable(string * n):expression(0)
{
  agent_name = NULL;
  name = n;
  var_type = NULL;
}

variable::variable(string * a_n, string * n, basictype * v_t):expression(0)
{
  agent_name = a_n;
  name = n;
  var_type = v_t;
}

variable::~variable()
{
}

bool
variable::equal_to(variable * expr)
{
  if (agent_name == NULL && expr->is_agent_name_null())
    return (name->compare(expr->get_variable_name())) == 0;
  else if (agent_name != NULL && !expr->is_agent_name_null())
    return ((name->compare(expr->get_variable_name())) == 0) &&
      ((agent_name->compare(expr->get_agent_name())) == 0);
  return false;
}

bool
variable::equal_to(expression * expr)
{
  if (expr->get_type() == get_type())
    return equal_to((variable *) expr);
  return false;
}

void
variable::set_agent_name(string * a_n)
{
  agent_name = a_n;
}

string
variable::get_agent_name()
{
  if (agent_name == NULL) {
    cout << "error: the agent name of the given variable is undefined!" <<
      endl;
    exit(1);
  } else
    return *agent_name;
}

string *
variable::get_variable_name_point()
{
  return name;
}

bool
variable::is_agent_name_null()
{
  return agent_name == NULL;
}

string
variable::get_variable_name()
{
  if (name == NULL) {
    cout << "error: the name of the given variable is undefined!" << endl;
    exit(1);
  } else
    return *name;
}

string
variable::to_string()
{
  return (agent_name == NULL ? "" : *agent_name + ".") + get_variable_name();
}

void
variable::set_var_type(basictype * t)
{
  if (var_type == NULL)
    var_type = t;
}

basictype *
variable::get_var_type()
{
  return var_type;
}

ADD
variable::build_ADD_tree(Cudd * bddmgr, vector<ADD> * addv, map< string,
                         ADD > *ADD_cache)
{
  if (var_type == NULL) {
    if (options["quiet"] == 0)
      cout << "Warning: var_type in " << to_string() << " is NULL" << endl;
    return bddmgr->addZero();
  }
  if (var_type->get_type() == 2)
    return ((rangedint *) var_type)->build_ADD_tree(bddmgr, addv, ADD_cache);
  else
    return bddmgr->addZero();
}

BDD
variable::encode_BDD_true(Cudd * bddmgr, vector<BDD> * v)
{
  if (var_type->get_type() == 1) {
    int begin = ((rangedint *) var_type)->get_index_begin();
    return (*v)[begin];
  }
  return bddmgr->bddZero();
}

BDD
variable::encode_BDD_false(Cudd * bddmgr, vector<BDD> * v)
{
  if (var_type->get_type() == 1) {
    int begin = ((rangedint *) var_type)->get_index_begin();
    return !(*v)[begin];
  }
  return bddmgr->bddZero();
}

