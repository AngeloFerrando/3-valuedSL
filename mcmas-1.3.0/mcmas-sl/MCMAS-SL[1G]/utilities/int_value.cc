#include <ctime>
#include "types.hh"
#include "utilities.hh"

using namespace std;

int_value::int_value(int v):expression(2)
{
  value = v;
}

int_value::~int_value()
{
}

bool
int_value::equal_to(int_value * expr)
{
  return value == expr->get_value();
}

bool
int_value::equal_to(expression * expr)
{
  if (expr->get_type() == get_type())
    return equal_to((int_value *) expr);
  return false;
}

int
int_value::get_value()
{
  return value;
}

string
int_value::to_string()
{
  ostringstream o;
  o << value;
  return o.str();
}

ADD
int_value::build_ADD_tree(Cudd * bddmgr, vector<ADD> * addv, map< string,
                          ADD > *ADD_cache)
{
  return bddmgr->constant(value);
}

BDD
int_value::encode_BDD_true(Cudd * bddmgr, vector<BDD> * v)
{
  return bddmgr->bddZero();
}

BDD
int_value::encode_BDD_false(Cudd * bddmgr, vector<BDD> * v)
{
  return bddmgr->bddZero();
}

