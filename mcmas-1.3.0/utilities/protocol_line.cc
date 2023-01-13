#include <ctime>
#include "types.hh"
#include "utilities.hh"

using namespace std;

protocol_line::protocol_line(bool_expression * c, set< string > *a)
{
  condition = c;
  actions = a;
}

protocol_line::~protocol_line()
{
	delete condition;
	delete actions;
}

bool_expression *
protocol_line::get_condition()
{
  return condition;
}

set< string > *protocol_line::get_actions()
{
  return actions;
}

string
protocol_line::to_string()
{
  string str = "{ ";
  unsigned int k = 0;
  unsigned int j = (unsigned int) actions->size() - 1;
  for (set< string >::iterator i = actions->begin(); i != actions->end();
       i++) {
    if (k == j)
      str += *i + " ";
    else
      str += *i + ", ";
    k++;
  }
  str += "}";
  return condition->to_string() + ": " + str;
}
