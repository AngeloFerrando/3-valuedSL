#include <ctime>
#include "types.hh"
#include "utilities.hh"

using namespace std;

bool_value::bool_value(bool v):expression(1)
{
  value = v;
}

bool_value::~bool_value()
{
}

bool
bool_value::equal_to(bool_value * expr)
{
  return value == expr->get_value();
}

bool
bool_value::equal_to(expression * expr)
{
  if (expr->get_type() == get_type())
    return equal_to((bool_value *) expr);
  return false;
}

bool
bool_value::get_value()
{
  return value;
}

string
bool_value::to_string()
{
  return (value ? "true" : "false");
}

ADD
bool_value::build_ADD_tree(Cudd * bddmgr, vector<ADD> * addv, map< string,
                           ADD > *ADD_cache)
{
  if (value)
    return bddmgr->addOne();
  else
    return bddmgr->addZero();
}

BDD
bool_value::encode_BDD_true(Cudd * bddmgr, vector<BDD> * v)
{
  if (value)
    return bddmgr->bddOne();
  else
    return bddmgr->bddZero();
}

BDD
bool_value::encode_BDD_false(Cudd * bddmgr, vector<BDD> * v)
{
  if (value)
    return bddmgr->bddZero();
  else
    return bddmgr->bddOne();
}

