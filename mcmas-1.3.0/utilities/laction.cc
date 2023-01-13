#include <ctime>
#include "types.hh"
#include "utilities.hh"

using namespace std;

laction::laction():expression(4)
{
  agent_name = NULL;
  agent = NULL;
}

laction::laction(string * a_n):expression(4)
{
  agent_name = a_n;
  agent = NULL;
}

laction::laction(string * a_n, basic_agent * ag):expression(4)
{
  agent_name = a_n;
  agent = ag;
}

laction::~laction()
{
}

bool
laction::equal_to(laction * expr)
{
  if (agent_name == NULL && expr->is_agent_name_null())
    return true;
  if (agent_name != NULL && !expr->is_agent_name_null())
    return agent_name->compare(expr->get_agent_name()) == 0;
  return false;
}

bool
laction::equal_to(expression * expr)
{
  if (expr->get_type() == get_type())
    return equal_to((laction *) expr);
  return false;
}

void
laction::set_agent_name(string * a_n)
{
  agent_name = a_n;
}

string
laction::get_agent_name()
{
  if (agent_name == NULL) {
    cout << "agent name in laction is unknown!" << endl;
    exit(1);
  } else
    return *agent_name;
}

void
laction::set_agent(basic_agent * a)
{
  if (agent == NULL)
    agent = a;
}

basic_agent *
laction::get_agent()
{
  return agent;
}

bool
laction::is_agent_name_null()
{
  return agent_name == NULL;
}

string
laction::to_string()
{
  return (agent_name == NULL ? "" : *agent_name + ".") + "Action";
}

ADD
laction::build_ADD_tree(Cudd * bddmgr, vector<ADD> * addv, map< string,
                        ADD > *ADD_cache)
{
  return bddmgr->addZero();
}

BDD
laction::encode_BDD_true(Cudd * bddmgr, vector<BDD> * v)
{
  return bddmgr->bddZero();
}

BDD
laction::encode_BDD_false(Cudd * bddmgr, vector<BDD> * v)
{
  return bddmgr->bddZero();
}

