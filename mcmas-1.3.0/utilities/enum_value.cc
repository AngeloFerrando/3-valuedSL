#include <ctime>
#include "types.hh"
#include "utilities.hh"

using namespace std;

enum_value::enum_value(string * v):expression(3)
{
  value = v;
}

enum_value::~enum_value()
{
}

bool
enum_value::equal_to(enum_value * expr)
{
  return value->compare(expr->get_value()) == 0;
}

bool
enum_value::equal_to(expression * expr)
{
  if (expr->get_type() == get_type())
    return equal_to((enum_value *) expr);
  return false;
}

string
enum_value::get_value()
{
  if (value == NULL) {
    cout << "enum value is unknown!" << endl;
    exit(1);
  } else
    return *value;
}

string
enum_value::to_string()
{
  return get_value();
}

ADD
enum_value::build_ADD_tree(Cudd * bddmgr, vector<ADD> * addv, map< string,
                           ADD > *ADD_cache)
{
  return bddmgr->addZero();
}

BDD
enum_value::encode_BDD_true(Cudd * bddmgr, vector<BDD> * v)
{
  return bddmgr->bddZero();
}

BDD
enum_value::encode_BDD_false(Cudd * bddmgr, vector<BDD> * v)
{
  return bddmgr->bddZero();
}
