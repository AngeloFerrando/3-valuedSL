#include <ctime>
#include "types.hh"
#include "utilities.hh"

using namespace std;

evolution_line::evolution_line(vector< assignment * >*a, bool_expression * c)
{
  assignments = a;
  condition = c;
}

evolution_line::~evolution_line()
{
	if(condition->get_op() != 0 || search_logic_expression_table(condition) < 0) 
		delete condition;
	for(unsigned int i=0; i<assignments->size(); i++)
		delete (*assignments)[i];
	delete assignments;
}

vector< assignment * >*evolution_line::get_assignments()
{
  return assignments;
}

bool_expression *
evolution_line::get_condition()
{
  return condition;
}

string
evolution_line::to_string()
{
  string str = "";
  for (vector< assignment * >::iterator i = assignments->begin();
       i != assignments->end(); i++)
    str += (*i)->to_string() + (i == assignments->end() - 1 ? " " : " and ");
  str += " if " + condition->to_string();
  return str;
}

BDD
evolution_line::encode_bdd_assignements(bdd_parameters * para)
{
  BDD tmpbdd = para->bddmgr->bddOne();
  for (vector< assignment * >::iterator i = assignments->begin();
       i != assignments->end(); i++)
    tmpbdd = (*i)->encode_bdd(para, tmpbdd);
  return tmpbdd;
}

bool
evolution_line::check_double_assignment()
{
  bool flag = false;
  set< string > reassigned;
  for (unsigned int j = 0; j < assignments->size() - 1; j++) {
    string var_name = (*assignments)[j]->get_var()->get_variable_name();
    for (unsigned int k = j + 1; k < assignments->size(); k++) {
      string var_name1 = (*assignments)[k]->get_var()->get_variable_name();
      if (var_name == var_name1) {
        reassigned.insert(var_name);
        flag = true;
        break;
      }
    }
  }
  if (reassigned.size() > 0) {
    for (set< string >::iterator i = reassigned.begin();
         i != reassigned.end(); i++)
      cout << "      error: variable " << *i << " is assigned twice or more"
           << endl;
  }
  return flag;
}

BDD
evolution_line::encode_bdd_condition(bdd_parameters * para)
{
  BDD tmpbdd = condition->encode_bdd_flat(para, para->bddmgr->bddOne());
  return tmpbdd;
}

BDD 
evolution_line::encode_bdd_overflow(bdd_parameters * para)
{
  BDD tmpbdd = para->bddmgr->bddZero();
  for (vector< assignment * >::iterator i = assignments->begin();
       i != assignments->end(); i++) {
    tmpbdd += (*i)->encode_bdd_overflow(para);
  }
  tmpbdd *= encode_bdd_condition(para);
  return tmpbdd;
}

vector< evolution_line * >*
evolution_line::extend_to_all_variables(map<string, basictype*>* allvars)
{
  vector< assignment * >*new_assignments;
  bool_expression *
    new_condition;
  vector< evolution_line * >*els = new vector< evolution_line * >;
  els->push_back(this);
  // extend evolution to include all variables in assignments
  for (map< string, basictype * >::iterator j = allvars->begin();
       j != allvars->end(); j++) {
    bool
      found = false;
    for (unsigned int k = 0; k < assignments->size(); k++) {
      variable *
        var = (*assignments)[k]->get_var();
      string
        varname = var->get_variable_name();
      if (varname == j->first) {
        found = true;
        break;
      }
    }

    if (!found) {   // we add this variable to both sides
      unsigned int
        value_type = j->second->get_type();
      string *
        str = new string(j->first);
      variable *
        newvar = new variable(str);
      newvar->set_var_type(j->second);
      if (value_type == 1) {  // boolean type
        vector< evolution_line * >*newels = new vector< evolution_line * >;
        for (unsigned int k = 0; k < els->size(); k++) {
          assignment *
            tmpass = new assignment(str, new bool_value(false));
          variable *
            vr = tmpass->get_var();
          vr->set_var_type(j->second);
          new_assignments =
            new vector< assignment * >((*els)[k]->get_assignments()->begin(),
                                       (*els)[k]->get_assignments()->end());
          new_assignments->push_back(tmpass);
          logic_expression *
            tmplexp = new logic_expression(0, newvar, new bool_value(false));
          bool_expression *
            tmpbexp = new bool_expression(0, tmplexp);
          new_condition =
            new bool_expression(1, (*els)[k]->get_condition(), tmpbexp);
          evolution_line *
            newline = new evolution_line(new_assignments, new_condition);
          newels->push_back(newline);
          tmpass = new assignment(str, new bool_value(true));
          vr = tmpass->get_var();
          vr->set_var_type(j->second);
          new_assignments =
            new vector< assignment * >((*els)[k]->get_assignments()->begin(),
                                       (*els)[k]->get_assignments()->end());
          new_assignments->push_back(tmpass);
          tmplexp = new logic_expression(0, newvar, new bool_value(true));
          tmpbexp = new bool_expression(0, tmplexp);
          new_condition =
            new bool_expression(1, (*els)[k]->get_condition(), tmpbexp);
          newline = new evolution_line(new_assignments, new_condition);
          newels->push_back(newline);
        }
        els = newels;
      } else if (value_type == 2) { // rangedint
        vector< evolution_line * >*newels = new vector< evolution_line * >;
        rangedint *
          rint = (rangedint *) (j->second);
        for (unsigned int k = 0; k < els->size(); k++)
          for (int t = rint->get_lowerbound(); t <= rint->get_upperbound();
               t++) {
            assignment *
              tmpass = new assignment(str, new int_value(t));
            variable *
              vr = tmpass->get_var();
            vr->set_var_type(j->second);
            new_assignments =
              new vector<
              assignment * >((*els)[k]->get_assignments()->begin(),
                             (*els)[k]->get_assignments()->end());
            new_assignments->push_back(tmpass);
            logic_expression *
              tmplexp = new logic_expression(0, newvar, new int_value(t));
            bool_expression *
              tmpbexp = new bool_expression(0, tmplexp);
            new_condition =
              new bool_expression(1, (*els)[k]->get_condition(), tmpbexp);
            evolution_line *
              newline = new evolution_line(new_assignments, new_condition);
            newels->push_back(newline);
          }
        els = newels;
      } else {      // enumerate
        vector< evolution_line * >*newels = new vector< evolution_line * >;
        enumerate *
          enu = (enumerate *) (j->second);
        set< string > *val = enu->get_enumvalue();
        for (unsigned int k = 0; k < els->size(); k++)
          for (set< string >::iterator t = val->begin(); t != val->end();
               t++) {
            string *
              s = new string(*t);
            assignment *
              tmpass = new assignment(str, new enum_value(s));
            variable *
              vr = tmpass->get_var();
            vr->set_var_type(j->second);
            new_assignments =
              new vector<
              assignment * >((*els)[k]->get_assignments()->begin(),
                             (*els)[k]->get_assignments()->end());
            new_assignments->push_back(tmpass);
            logic_expression *
              tmplexp = new logic_expression(0, newvar, new enum_value(s));
            bool_expression *
              tmpbexp = new bool_expression(0, tmplexp);
            new_condition =
              new bool_expression(1, (*els)[k]->get_condition(), tmpbexp);
            evolution_line *
              newline = new evolution_line(new_assignments, new_condition);
            newels->push_back(newline);
          }
        els = newels;
      }
    }
  }
  return els;
}
