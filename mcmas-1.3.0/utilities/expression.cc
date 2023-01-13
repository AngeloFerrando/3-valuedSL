#include <ctime>
#include "types.hh"
#include "utilities.hh"

using namespace std;

expression::expression(unsigned char i)
{
  type = i;
}

expression::~expression()
{
}

unsigned char
expression::get_type()
{
  return type;
}

string
expression::to_string()
{
  return "";
}

ADD
expression::build_ADD_tree(Cudd * bddmgr, vector<ADD> * addv, map< string,
                           ADD > *ADD_cache)
{
  return bddmgr->addZero();
}

bool
expression::equal_to(expression * expr)
{
  return type == expr->get_type();
}

BDD
expression::encode_BDD_true(Cudd * bddmgr, vector<BDD> * v)
{
  return bddmgr->bddZero();
}

BDD
expression::encode_BDD_false(Cudd * bddmgr, vector<BDD> * v)
{
  return bddmgr->bddZero();
}

