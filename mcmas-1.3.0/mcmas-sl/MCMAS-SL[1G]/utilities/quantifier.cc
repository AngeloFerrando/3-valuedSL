#include "sl_perfect_recall.hh"
#include <sstream>


quantifier::quantifier(const string & variable_name, bool existential,
                       bool auxiliary, const vector<basic_agent *> & agents):
    variable_name(variable_name), existential(existential),
    auxiliary(auxiliary), agents(agents)
{
}

quantifier::quantifier(const string & variable_name, bool existential,
                       bool auxiliary):
    variable_name(variable_name), existential(existential),
    auxiliary(auxiliary)
{
}

const string &
quantifier::get_variable_name() const
{
  return variable_name;
}

bool
quantifier::is_existential() const
{
  return existential;
}

bool
quantifier::is_auxiliary() const
{
  return auxiliary;
}

const vector<basic_agent *> &
quantifier::get_agents() const
{
  return agents;
}

string
quantifier::get_quantifier() const
{
  if (is_existential()) {
    return "<<" + get_variable_name() + ">>";
  } else {
    return "[[" + get_variable_name() + "]]";
  }
}

string
quantifier::get_bindings() const
{
  ostringstream s;
  for (unsigned int i = 0; i < get_agents().size(); i++) {
    s << "(" << get_agents()[i]->get_name() << ", " << get_variable_name()
        << ")";
  }
  return s.str();
}
