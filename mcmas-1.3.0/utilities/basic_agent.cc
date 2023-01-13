#include <ctime>
#include "types.hh"
#include "utilities.hh"

using namespace std;

basic_agent::basic_agent(string * n,
                         map< string, variable * >*lv,
                         map< string, basictype * >*v0,
                         vector< basictype * >*vecv0,
                         map< string, basictype * >*v1,
                         vector< basictype * >*vecv1,
                         bool_expression * r,
                         set< string > *v2,
                         vector< protocol_line * >*v3,
                         vector< evolution_line * >*v4)
{
  name = n;
  lobsvars = lv;
  obsvars = v0;
  vars = v1;
  vec_obsvars = vecv0;
  vec_vars = vecv1;
  actions = v2;
  protocol = v3;
  evolution = v4;
  redstates = r;
  action_indices = new map< string, vector< bool > *>;
  generate_action_bdd_value();
}

basic_agent::~basic_agent()
{
  if(lobsvars) {
    for(map< string, variable * >::iterator i=lobsvars->begin(); i!=lobsvars->end(); i++)
      delete i->second;
    delete lobsvars;
  }
  if(obsvars) {
    for(map< string, basictype * >::iterator i=obsvars->begin(); i!=obsvars->end(); i++)
      delete i->second;
    delete obsvars;
    delete vec_obsvars;
  }
  if(vars) {
    for(map< string, basictype * >::iterator i=vars->begin(); i!=vars->end(); i++)
      delete i->second;
    delete vars;
    delete vec_vars;
  }
  if(redstates)
    delete redstates;
  if(actions)
    delete actions;
  if(protocol) {
    for(unsigned int i=0; i<protocol->size(); i++)
      delete (*protocol)[i];
    delete protocol;
  }
  if(evolution) {
    for(unsigned int i=0; i<evolution->size(); i++)
      delete (*evolution)[i];
    delete evolution;
  }
}

string
basic_agent::get_name()
{
  if (name == NULL) {
    cout << " error: name in agent is undefined!" << endl;
    exit(1);
  } else
    return *name;
}

string *
basic_agent::get_name_point()
{
  return name;
}

map< string, basictype * >*basic_agent::get_obsvars()
{
  return obsvars;
}

vector< basictype * >*basic_agent::get_vec_obsvars()
{
  return vec_obsvars;
}

vector< basictype * >*basic_agent::get_vec_vars()
{
  return vec_vars;
}

map< string, variable * >*basic_agent::get_lobsvars()
{
  return lobsvars;
}

map< string, basictype * >*basic_agent::get_vars()
{
  return vars;
}

basictype *
basic_agent::get_basictype_by_name(string varname)
{
  if (obsvars != NULL) {
    if (obsvars->find(varname) != obsvars->end())
      return (*obsvars)[varname];
  }
  if (vars != NULL) {
    if (vars->find(varname) != vars->end())
      return (*vars)[varname];
  }
  return NULL;
}

set< string > *basic_agent::get_actions()
{
  return actions;
}

vector< protocol_line * >*basic_agent::get_protocol()
{
  return protocol;
}

vector< evolution_line * >*basic_agent::get_evolution()
{
  return evolution;
}

bool_expression *
basic_agent::get_redstates()
{
  return redstates;
}

string
basic_agent::to_string()
{
  string str = "Agent " + *name + "\n";

  if (obsvars != NULL && obsvars->size() > 0) {
    str += "Obsvars:\n";
    for (map< string, basictype * >::iterator i = obsvars->begin();
         i != obsvars->end(); i++)
      str += "    " + (*i).second->to_string() + ";\n";
    str += "end Obsvars\n";
  }

  str += "Vars:\n";
  for (map< string, basictype * >::iterator i = vars->begin();
       i != vars->end(); i++)
    str += "    " + (*i).second->to_string() + ";\n";
  str += "end Vars\nRedStates:\n    ";
  if (redstates == NULL)
    str += "";
  else
    str += redstates->to_string() + ";";
  str += "\nend RedStates\nActions = { ";
  unsigned int k = 0;
  unsigned int bound = (unsigned int) actions->size() - 1;
  for (set< string >::iterator i = actions->begin(); i != actions->end();
       i++) {
    if (k == bound)
      str += *i + " ";
    else
      str += *i + ", ";
    k++;
  }
  str += "}\nProtocol:\n";
  for (vector< protocol_line * >::iterator i = protocol->begin();
       i != protocol->end(); i++)
    str += "    " + (*i)->to_string() + ";\n";
  str += "end Protocol\nEvolution:\n";
  for (vector< evolution_line * >::iterator i = evolution->begin();
       i != evolution->end(); i++)
    str += "    " + (*i)->to_string() + ";\n";
  str += "end Evolution\n";
  str += "end Agent\n";
  return str;
}

int
basic_agent::state_BDD_length()
{
  int count = 0;
  count += obsvars_BDD_length();
  if (vars != NULL)
    for (map< string, basictype * >::iterator i = vars->begin();
         i != vars->end(); i++)
      count += (*i).second->BDD_length();
  return count;
}

int
basic_agent::obsvars_BDD_length()
{
  int count = 0;
  if (obsvars != NULL)
    for (map< string, basictype * >::iterator i = obsvars->begin();
         i != obsvars->end(); i++)
      count += (*i).second->BDD_length();
  return count;
}

unsigned int
basic_agent::actions_BDD_length()
{
  if (actions == NULL || actions->size() == 0)
    return 0;
  return log_2((unsigned int) actions->size());
}

void
basic_agent::set_action_index_begin(int i)
{
  action_index_begin = i;
}

void
basic_agent::set_action_index_end(int i)
{
  action_index_end = i;
}

void
basic_agent::set_var_index_begin(int i)
{
  var_index_begin = i;
}

void
basic_agent::set_var_index_end(int i)
{
  var_index_end = i;
}

int
basic_agent::get_action_index_begin()
{
  return action_index_begin;
}

int
basic_agent::get_action_index_end()
{
  return action_index_end;
}

int
basic_agent::get_var_index_begin()
{
  return var_index_begin;
}

int
basic_agent::get_var_index_end()
{
  return var_index_end;
}

void
basic_agent::generate_action_bdd_value()
{
  int size = actions_BDD_length();
  if (size == 0)
    return;
  vector< bool > base(size, false);
  for (set< string >::iterator i = actions->begin(); i != actions->end();
       i++) {
    vector< bool > *temp = new vector< bool > (base);
    pair < string, vector< bool > *>p(*i, temp);
    action_indices->insert(p);
    for (int j = size - 1; j >= 0; j--) {
      if (base[j])
        base[j] = false;
      else {
        base[j] = true;
        break;
      }
    }
  }
}

void
basic_agent::print_value_index()
{
  for (map< string, vector< bool > *>::iterator i = action_indices->begin();
       i != action_indices->end(); i++) {
    cout << i->first << ": ";
    for (unsigned int j = 0; j < i->second->size(); j++)
      cout << ((*(i->second))[j] ? 1 : 0);
    cout << endl;
  }
}

map< string, vector< bool > *>*basic_agent::get_action_indices()
{
  return action_indices;
}

int
basic_agent::allocate_BDD_2_variables(int start)
{
  set_var_index_begin(start);
  int count = start;

  if (vec_obsvars != NULL)
    for (unsigned int i = 0; i < vec_obsvars->size(); i++) {
      int l = (*vec_obsvars)[i]->BDD_length();
      (*vec_obsvars)[i]->set_index_begin(count);
      (*vec_obsvars)[i]->set_index_end(count + l - 1);
      count += l;
    }
  if (vec_vars != NULL)
    for (unsigned int i = 0; i < vec_vars->size(); i++) {
      int l = (*vec_vars)[i]->BDD_length();
      (*vec_vars)[i]->set_index_begin(count);
      (*vec_vars)[i]->set_index_end(count + l - 1);
      count += l;
    }

  set_var_index_end(count - 1);
  return count;
}

int
basic_agent::allocate_BDD_2_actions(int start)
{
  set_action_index_begin(start);
  int end = start + actions_BDD_length();
  set_action_index_end(end - 1);
  return end;
}

BDD
basic_agent::encode_action(bdd_parameters * para, string act)
{
  map< string, vector< bool > *>::iterator k = action_indices->find(act);
  if (k != action_indices->end()) {
    BDD temp = para->bddmgr->bddOne();
    vector< bool > *b = (*k).second;
    for (int i = action_index_begin; i <= action_index_end; i++)
      temp =
        temp *
        ((*b)[i - action_index_begin] ? (*para->a)[i] : !(*para->a)[i]);
    return temp;
  }
  return para->bddmgr->bddZero();
}

BDD
basic_agent::encode_protocol(bdd_parameters * para)
{
  BDD bddprot = para->bddmgr->bddZero();
  BDD nullaction = para->bddmgr->bddOne();
  if (protocol->size() == 0)
    return para->bddmgr->bddOne();
  if(protocol->back()->get_condition()->is_other_branch()) {
    for (vector< protocol_line * >::iterator i = protocol->begin();
         i != protocol->end(); i++) {
      bool_expression *condition = (*i)->get_condition();
      BDD tmpcond = para->bddmgr->bddOne();
      if (!condition->is_other_branch()) {
        tmpcond = condition->encode_bdd_flat(para, para->bddmgr->bddOne());
        nullaction = nullaction * !tmpcond;
      } else
        tmpcond = nullaction;
      
      BDD tmpact = para->bddmgr->bddZero();
      set< string > *actions = (*i)->get_actions();
      for (set< string >::iterator j = actions->begin(); j != actions->end();
           j++) {
        tmpact = tmpact + encode_action(para, *j);
      }
      
      BDD oneline = tmpcond * tmpact;
      
      bddprot = bddprot + oneline;
    }
  } else {
    for (vector< protocol_line * >::iterator i = protocol->begin();
         i != protocol->end(); i++) {
      bool_expression *condition = (*i)->get_condition();
      BDD tmpcond = para->bddmgr->bddOne();
      tmpcond = condition->encode_bdd_flat(para, para->bddmgr->bddOne());
      
      BDD tmpact = para->bddmgr->bddZero();
      set< string > *actions = (*i)->get_actions();
      for (set< string >::iterator j = actions->begin(); j != actions->end();
           j++) {
        tmpact = tmpact + encode_action(para, *j);
      }
      
      BDD oneline = tmpcond * tmpact;
      
      bddprot = bddprot + oneline;
    }
  }
  return bddprot;
}

BDD
basic_agent::encode_evolution(bdd_parameters * para)
{
  BDD bddevol = para->bddmgr->bddZero();
  BDD lastcond = para->bddmgr->bddOne();

  for (vector< evolution_line * >::iterator i = evolution->begin();
       i != evolution->end(); i++) {
    vector< assignment * >*assignments = (*i)->get_assignments();
    map< string, basictype * >*mp = new map< string, basictype * >;
    if (obsvars != NULL)
      for (map< string, basictype * >::iterator j = obsvars->begin();
           j != obsvars->end(); j++) {
        bool found = false;
        for (unsigned int k = 0; k < assignments->size(); k++) {
          variable *var = (*assignments)[k]->get_var();
          string varname = var->get_variable_name();
          if (varname == j->first) {
            found = true;
            break;
          }
        }

        if (!found)   // we add this variable to both sides
          mp->insert(*j);
      }

    if (vars != NULL)
      for (map< string, basictype * >::iterator j = vars->begin();
           j != vars->end(); j++) {
        bool found = false;
        for (unsigned int k = 0; k < assignments->size(); k++) {
          variable *var = (*assignments)[k]->get_var();
          string varname = var->get_variable_name();
          if (varname == j->first) {
            found = true;
            break;
          }
        }

        if (!found)   // we add this variable to both sides
          mp->insert(*j);
      }

    BDD bddassignment = (*i)->encode_bdd_assignements(para);
    BDD bddcondition = (*i)->encode_bdd_condition(para);
    vector<BDD> x, y;
    for (map< string, basictype * >::iterator j = mp->begin();
         j != mp->end(); j++) {
      int begin = j->second->get_index_begin();
      int end = j->second->get_index_end();
      for (int k = begin; k <= end; k++) {
        //bddassignment *=
        //  ((!(*para->v)[k] + (*para->pv)[k]) * ((*para->v)[k] + !(*para->pv)[k]));
        x.push_back((*para->v)[k]);
        y.push_back((*para->pv)[k]);
      }
    }
    if(x.size() > 0)
      bddassignment *= para->bddmgr->Xeqy(x, y);
    lastcond = lastcond * !bddcondition;

    bddevol = bddevol + (bddassignment * bddcondition);
  }

  BDD dnc = para->bddmgr->bddOne();
  int begin, end;
  if (obsvars != NULL)
    for (map< string, basictype * >::iterator i = obsvars->begin();
         i != obsvars->end(); i++) {
      basictype *var_type = (*i).second;
      begin = var_type->get_index_begin();
      end = var_type->get_index_end();
      for (int j = begin; j <= end; j++)
        dnc *= // ((!(*para->v)[j] + (*para->pv)[j]) * ((*para->v)[j] + !(*para->pv)[j]));
					((*para->v)[j] * (*para->pv)[j]) + ((!(*para->v)[j] * !(*para->pv)[j]));
    }
  if (vars != NULL) {
    for (map< string, basictype * >::iterator i = vars->begin();
         i != vars->end(); i++) {
      basictype *var_type = (*i).second;
      begin = var_type->get_index_begin();
      end = var_type->get_index_end();
      for (int j = begin; j <= end; j++)
        dnc *= //((!(*para->v)[j] + (*para->pv)[j]) * ((*para->v)[j] + !(*para->pv)[j]));
					((*para->v)[j] * (*para->pv)[j]) + ((!(*para->v)[j] * !(*para->pv)[j]));
    }
  }
  lastcond *= dnc;
  return bddevol + lastcond;
}

BDD
basic_agent::encode_evolution_smv(bdd_parameters * para)
{
  vector< evolution_line * >tmpevol(evolution->begin(), evolution->end());
  map< string, BDD > tmpbdds;

  while (tmpevol.size() > 0) {
    evolution_line *evoline = tmpevol[0];
    tmpevol.erase(tmpevol.begin());
    vector< assignment * >*assignments = evoline->get_assignments();
    variable *var = (*assignments)[0]->get_var();
    string varname = var->get_variable_name();

    BDD bddassignment = evoline->encode_bdd_assignements(para);
    BDD bddcondition = evoline->encode_bdd_condition(para);
    BDD tmplast = !bddcondition;
    BDD linebdd = bddassignment * bddcondition;

    unsigned int i = 0;
    while (i < tmpevol.size()) {
      evolution_line *evoline1 = tmpevol[i];
      vector< assignment * >*assignments1 = evoline1->get_assignments();
      variable *var1 = (*assignments1)[0]->get_var();
      if (varname.compare(var1->get_variable_name()) == 0) {
        BDD bddassignment1 = evoline1->encode_bdd_assignements(para);
        BDD bddcondition1 = evoline1->encode_bdd_condition(para);
        linebdd += bddassignment1 * bddcondition1;
        tmplast *= !bddcondition1;
        tmpevol.erase(tmpevol.begin() + i);
      } else
        i++;
    }

    basictype *var_type = var->get_var_type();
    int begin = var_type->get_index_begin();
    int end = var_type->get_index_end();
    for (int j = begin; j <= end; j++)
      tmplast *=
        ((!(*para->v)[j] + (*para->pv)[j]) * ((*para->v)[j] +
                                              !(*para->pv)[j]));

    linebdd += tmplast;
    tmpbdds[varname] = linebdd;
  }

  BDD dnc = para->bddmgr->bddOne();
  int begin, end;
  if (obsvars != NULL)
    for (map< string, basictype * >::iterator i = obsvars->begin();
         i != obsvars->end(); i++) {
      if (tmpbdds.find(i->first) == tmpbdds.end()) {
        basictype *var_type = (*i).second;
        begin = var_type->get_index_begin();
        end = var_type->get_index_end();
        for (int j = begin; j <= end; j++)
          dnc =
            dnc * ((!(*para->v)[j] + (*para->pv)[j]) *
                   ((*para->v)[j] + !(*para->pv)[j]));
      }
    }
  if (vars != NULL)
    for (map< string, basictype * >::iterator i = vars->begin();
         i != vars->end(); i++) {
      if (tmpbdds.find(i->first) == tmpbdds.end()) {
        basictype *var_type = (*i).second;
        begin = var_type->get_index_begin();
        end = var_type->get_index_end();
        for (int j = begin; j <= end; j++)
          dnc =
            dnc * ((!(*para->v)[j] + (*para->pv)[j]) *
                   ((*para->v)[j] + !(*para->pv)[j]));
      }
    }

  for (map< string, BDD >::iterator i = tmpbdds.begin(); i != tmpbdds.end();
       i++)
    dnc *= i->second;

  return dnc;
}

BDD
basic_agent::encode_greenstates(bdd_parameters * para)
{
  if (redstates == NULL)
    return para->bddmgr->bddOne();
  else {
    BDD tmp = redstates->encode_bdd_flat(para, para->bddmgr->bddOne());
    return (!tmp).SwapVariables(*para->v, *para->pv);
  }
}

void
basic_agent::print_variable_BDD_encoding()
{
  if (obsvars != NULL)
    for (map< string, basictype * >::iterator i = obsvars->begin();
         i != obsvars->end(); i++) {
      int begin = i->second->get_index_begin();
      int end = i->second->get_index_end();
      cout << "----- " << i->
        first << ": " << begin << " .. " << end << " -----" << endl;
      basictype *b = i->second;
      if (b->get_type() == 2) //rangeint
        ((rangedint *) b)->print_value_index();
      else if (b->get_type() == 3)  //enumerate
        ((enumerate *) b)->print_value_index();
      else
        b->print_value_index();
    }
  if (vars != NULL)
    for (map< string, basictype * >::iterator i = vars->begin();
         i != vars->end(); i++) {
      int begin = i->second->get_index_begin();
      int end = i->second->get_index_end();
      cout << "----- " << i->
        first << ": " << begin << " .. " << end << " -----" << endl;
      basictype *b = i->second;
      if (b->get_type() == 2) //rangeint
        ((rangedint *) b)->print_value_index();
      else if (b->get_type() == 3)  //enumerate
        ((enumerate *) b)->print_value_index();
      else
        b->print_value_index();
    }
}

void
basic_agent::print_state(string prefix, BDD state, vector<BDD> v)
{
  if (obsvars != NULL)
    for (map< string, basictype * >::iterator i = obsvars->begin();
         i != obsvars->end(); i++) {
      i->second->print_state(prefix, state, v);
      cout << endl;
    }
  if (vars != NULL)
    for (map< string, basictype * >::iterator i = vars->begin();
         i != vars->end(); i++) {
      i->second->print_state(prefix, state, v);
      cout << endl;
    }
}

bool
basic_agent::is_valid_state(BDD state, vector<BDD> v)
{
  if (obsvars != NULL)
    for (map< string, basictype * >::iterator i = obsvars->begin();
         i != obsvars->end(); i++) {
      if (!i->second->is_valid_state(state, v))
        return false;
    }
  if (vars != NULL)
    for (map< string, basictype * >::iterator i = vars->begin();
         i != vars->end(); i++) {
      if (!i->second->is_valid_state(state, v))
        return false;
    }
  return true;
}

void
basic_agent::print_action(BDD state, vector<BDD> a)
{
  vector< bool > index;
  for (int i = action_index_begin; i <= action_index_end; i++)
    if (state <= a[i])
      index.push_back(true);
    else
      index.push_back(false);
  for (map< string, vector< bool > *>::iterator i = action_indices->begin();
       i != action_indices->end(); i++) {
    bool flag = true;
    for (unsigned int j = 0; j < i->second->size(); j++)
      if ((*(i->second))[j] != index[j]) {
        flag = false;
        break;
      }
    if (flag) {
      cout << i->first;
      return;
    }
  }
}

bool
basic_agent::is_valid_action(BDD state, vector<BDD> a)
{
  if (action_indices->size() == 0)
    return true;
  vector< bool > index;
  for (int i = action_index_begin; i <= action_index_end; i++)
    if (state <= a[i])
      index.push_back(true);
    else
      index.push_back(false);
  for (map< string, vector< bool > *>::iterator i = action_indices->begin();
       i != action_indices->end(); i++) {
    bool flag = true;
    for (unsigned int j = 0; j < i->second->size(); j++)
      if ((*(i->second))[j] != index[j]) {
        flag = false;
        break;
      }
    if (flag) {
      return true;
    }
  }
  return false;
}

set< string > *basic_agent::get_obs_enum_values()
{
  if (obsvars != NULL) {
    set< string > *tmpset = new set< string >;
    for (map< string, basictype * >::iterator i = obsvars->begin();
         i != obsvars->end(); i++)
      if (i->second->get_type() == 3) {
        set< string > *varset = ((enumerate *) (i->second))->get_enumvalue();
        tmpset->insert(varset->begin(), varset->end());
      }
    return tmpset;
  }
  return NULL;
}

bool
basic_agent::check_var_against_enum_values(set< string > *obsenum)
{
  bool flag = true;
  set< string > *tmpset = new set< string >;
  if (vars != NULL)
    for (map< string, basictype * >::iterator i = vars->begin();
         i != vars->end(); i++)
      if (i->second->get_type() == 3) {
        set< string > *varset = ((enumerate *) (i->second))->get_enumvalue();
        tmpset->insert(varset->begin(), varset->end());
      }
  if (obsenum != NULL)
    tmpset->insert(obsenum->begin(), obsenum->end());
  if (obsvars != NULL)
    for (map< string, basictype * >::iterator i = obsvars->begin();
         i != obsvars->end(); i++)
      if (tmpset->find(i->first) != tmpset->end()) {
        flag = false;
        cout << "variable " << i->
          first << " has been used as a enumerate value." << endl;
      }
  if (vars != NULL)
    for (map< string, basictype * >::iterator i = vars->begin();
         i != vars->end(); i++)
      if (tmpset->find(i->first) != tmpset->end()) {
        flag = false;
        cout << "variable " << i->
          first << " has been used as a enumerate value." << endl;
      }
  return flag;
}

bool
basic_agent::check_lobsvars(map< string, basictype * >*envars)
{
  if (lobsvars != NULL && lobsvars->size() > 0)
    for (map< string, variable * >::iterator i = lobsvars->begin();
         i != lobsvars->end(); i++) {
      map< string, basictype * >::iterator j;
      if (envars != NULL && (j = envars->find(i->first)) != envars->end())
        i->second->set_var_type(j->second);
      else {
        cout << "local observable variable " << i->
          first << " is not defined in the environment." << endl;
        return false;
      }
    }
  return true;
}

void
basic_agent::print_stateXML(ofstream * myfile, BDD state, vector<BDD> v)
{
  if (obsvars != NULL)
    for (map< string, basictype * >::iterator i = obsvars->begin();
         i != obsvars->end(); i++) {
      i->second->print_stateXML(myfile, state, v);
    }
  if (vars != NULL)
    for (map< string, basictype * >::iterator i = vars->begin();
         i != vars->end(); i++) {
      i->second->print_stateXML(myfile, state, v);
    }
}

string
basic_agent::state_to_str(BDD state, vector<BDD> v)
{
  ostringstream s;
  if (obsvars != NULL)
    for (map< string, basictype * >::iterator i = obsvars->begin();
         i != obsvars->end(); i++) {
      s << "    " << i->second->state_to_str(state, v) << "\n";
    }
  if (vars != NULL)
    for (map< string, basictype * >::iterator i = vars->begin();
         i != vars->end(); i++) {
      s << "    " << i->second->state_to_str(state, v) << "\n";
    }
  return s.str();
}

string
basic_agent::action_to_str(BDD state, vector<BDD> a)
{
  ostringstream s;
  vector< bool > index;
  for (int i = action_index_begin; i <= action_index_end; i++)
    if (state <= a[i])
      index.push_back(true);
    else
      index.push_back(false);
  for (map< string, vector< bool > *>::iterator i = action_indices->begin();
       i != action_indices->end(); i++) {
    bool flag = true;
    for (unsigned int j = 0; j < i->second->size(); j++)
      if ((*(i->second))[j] != index[j]) {
        flag = false;
        break;
      }
    if (flag) {
      s << i->first;
    }
  }
  return s.str();
}

BDD
basic_agent::project_local_state(BDD * state, Cudd * bddmgr, vector<BDD> * v)
{
  BDD tmp = bddmgr->bddOne(); // Always true

  if (lobsvars != NULL && lobsvars->size() > 0) {
    map< string, basictype * >*envars = (*agents)[0]->get_vars();
    for (map< string, basictype * >::iterator i = envars->begin();
         i != envars->end(); i++) {
      if (lobsvars->find(i->first) == lobsvars->end()) {  // i->first is not local observable variable 
        basictype *bt = i->second;
        int index_begin = bt->get_index_begin();
        int index_end = bt->get_index_end();
        for (int j = index_begin; j <= index_end; j++)
          tmp = tmp * (*v)[j];
      }
    }
    for (int j = envars_bdd_length; j < get_var_index_begin(); j++) {
      tmp = tmp * (*v)[j];
    }
  } else {
    for (int j = obsvars_bdd_length; j < get_var_index_begin(); j++) {
      tmp = tmp * (*v)[j];
    }
  }

  for (unsigned int j = get_var_index_end() + 1; j < v->size(); j++) {
    tmp = tmp * (*v)[j];
  }

  return state->ExistAbstract(tmp);
}

BDD
basic_agent::project_local_trans(BDD * trans, Cudd * bddmgr, vector<BDD> * v,
                                 vector<BDD> * pv)
{
  BDD tmp = bddmgr->bddOne(); // Always true

  for (int j = 0; j < get_var_index_begin(); j++) {
    tmp = tmp * (*v)[j];
    tmp = tmp * (*pv)[j];
  }

  for (unsigned int j = get_var_index_end() + 1; j < v->size(); j++) {
    tmp = tmp * (*v)[j];
    tmp = tmp * (*pv)[j];
  }

  return trans->ExistAbstract(tmp);
}

BDD
basic_agent::project_local_actions(BDD * SA, Cudd * bddmgr, vector<BDD> * a)
{
  BDD tmp = bddmgr->bddOne(); // Always true

  for (int j = 0; j < get_action_index_begin(); j++) {
    tmp = tmp * (*a)[j];
  }
  for (unsigned int j = get_action_index_end()+1; j < a->size(); j++) {
    tmp = tmp * (*a)[j];
  }

  return SA->ExistAbstract(tmp);
}

vector<BDD>
basic_agent::get_BDDvector(Cudd * bddmgr, vector<BDD> * v, vector<BDD> * pv)
{
  int begin = get_var_index_begin();
  int end = get_var_index_end();
  vector<BDD> tmp;
  int k = 0;

  for (int j = begin; j <= end; j++)
    tmp[k++] = (*v)[j];

  for (int j = begin; j <= end; j++)
    tmp[k++] = (*pv)[j];

  return tmp;
}

basictype*
basic_agent::get_var_def(string varname) {
  if (obsvars != NULL) {
    map< string, basictype * >::iterator i = obsvars->find(varname);
    if(i != obsvars->end())
      return i->second;
  }
  if (vars != NULL) {
    map< string, basictype * >::iterator i = vars->find(varname);
    if(i != vars->end())
      return i->second;
  }
    
  return NULL;
}

BDD
basic_agent::compute_whole_state_for_integer(BDD s, bdd_parameters * para)
{
  if(integerBDDs == NULL)
    return s;
  BDD newstate = s;
  if (lobsvars != NULL && lobsvars->size() > 0) {
    map< string, basictype * >*envars = (*agents)[0]->get_vars();
    map< string, vector< BDD*>* > *agentBDDs = NULL;
    for (map< string, basictype * >::iterator i = envars->begin();
         i != envars->end(); i++) {
      if (lobsvars->find(i->first) != lobsvars->end()) {
	basictype *bt = i->second;
	if(bt->get_type() == 2 && !((rangedint*)bt)->is_power_of_two()) {
	  agentBDDs = agentBDDs==NULL ? (*integerBDDs)["Environment"] : agentBDDs;
	  vector< BDD* > *bddblocks = (*agentBDDs)[i->first];
	  for(unsigned int k=0; k<bddblocks->size(); k++)
	    if(s * *(*bddblocks)[k] != para->bddmgr->bddZero()) {
	      BDD tmp = Exists(para->bddmgr, para->v, newstate, (unsigned int)bt->get_index_begin(), (unsigned int)bt->get_index_end());
	      newstate = tmp * *(*bddblocks)[k];
	      break;
	    }
	}
      }
    }
  }

  map< string, basictype * > *envobsvars = (*agents)[0]->get_obsvars();
  if (envobsvars != NULL && envobsvars->size() > 0) {
    map< string, vector< BDD*>* > *agentBDDs = NULL;
    for (map< string, basictype * >::iterator i = envobsvars->begin();
         i != envobsvars->end(); i++) {
      basictype *bt = i->second;
      if(bt->get_type() == 2 && !((rangedint*)bt)->is_power_of_two()) {
	agentBDDs = agentBDDs==NULL ? (*integerBDDs)["Environment"] : agentBDDs;
	vector< BDD* > *bddblocks = (*agentBDDs)[i->first];
	for(unsigned int k=0; k<bddblocks->size(); k++)
	  if(s * *(*bddblocks)[k] != para->bddmgr->bddZero()) {
	    BDD tmp = Exists(para->bddmgr, para->v, newstate, (unsigned int)bt->get_index_begin(), (unsigned int)bt->get_index_end());
	    newstate = tmp * *(*bddblocks)[k];
	    break;
	  }
      }
    }
  }

  if (vars != NULL && vars->size() > 0) {
    map< string, vector< BDD*>* > *agentBDDs = NULL;
    for (map< string, basictype * >::iterator i = vars->begin();
         i != vars->end(); i++) {
      basictype *bt = i->second;
      if(bt->get_type() == 2 && !((rangedint*)bt)->is_power_of_two()) {
	agentBDDs = agentBDDs==NULL ? (*integerBDDs)[*name] : agentBDDs;
	vector< BDD* > *bddblocks = (*agentBDDs)[i->first];
	for(unsigned int k=0; k<bddblocks->size(); k++)
	  if(s * *(*bddblocks)[k] != para->bddmgr->bddZero()) {
	    BDD tmp = Exists(para->bddmgr, para->v, newstate, (unsigned int)bt->get_index_begin(), (unsigned int)bt->get_index_end());
	    newstate = tmp * *(*bddblocks)[k];
	    break;
	  }
      }
    }
  }
  return newstate;
}

BDD
basic_agent::reduce_whole_state_for_enumerate(BDD s, bdd_parameters * para)
{
  if(enumerateBDDs == NULL)
    return s;
  BDD newstate = s;
  if (lobsvars != NULL && lobsvars->size() > 0) {
    map< string, basictype * >*envars = (*agents)[0]->get_vars();
    map< string, BDD* > *agentBDDs = NULL;
    for (map< string, basictype * >::iterator i = envars->begin();
         i != envars->end(); i++) {
      if (lobsvars->find(i->first) != lobsvars->end()) {
	basictype *bt = i->second;
	if(bt->get_type() == 3 && !((enumerate*)bt)->is_power_of_two()) {
	  agentBDDs = agentBDDs==NULL ? (*enumerateBDDs)["Environment"] : agentBDDs;
	  newstate *= *(*agentBDDs)[i->first];
	}
      }
    }
  }

  map< string, basictype * > *envobsvars = (*agents)[0]->get_obsvars();
  if (envobsvars != NULL && envobsvars->size() > 0) {
    map< string, BDD* > *agentBDDs = NULL;
    for (map< string, basictype * >::iterator i = envobsvars->begin();
         i != envobsvars->end(); i++) {
      basictype *bt = i->second;
      if(bt->get_type() == 3 && !((enumerate*)bt)->is_power_of_two()) {
	agentBDDs = agentBDDs==NULL ? (*enumerateBDDs)["Environment"] : agentBDDs;
	newstate *= *(*agentBDDs)[i->first];
      }
    }
  }

  if (vars != NULL && vars->size() > 0) {
    map< string, BDD* > *agentBDDs = NULL;
    for (map< string, basictype * >::iterator i = vars->begin();
         i != vars->end(); i++) {
      basictype *bt = i->second;
      if(bt->get_type() == 3 && !((enumerate*)bt)->is_power_of_two()) {
	agentBDDs = agentBDDs==NULL ? (*enumerateBDDs)[*name] : agentBDDs;
	newstate *= *(*agentBDDs)[i->first];
      }
    }
  }
  return newstate;
}


vector< BDD >
basic_agent::get_localstate_BDD_vector(bdd_parameters * para)
{
  vector<BDD> lv;
  map< string, basictype * > *obsvars = (*agents)[0]->get_obsvars();
  if(obsvars != NULL && obsvars->size() > 0) {
    for (map< string, basictype * >::iterator i = obsvars->begin(); i != obsvars->end(); i++) {
      basictype *bt = i->second;
      int index_begin = bt->get_index_begin();
      int index_end = bt->get_index_end();
      lv.insert(lv.end(), para->v->begin()+index_begin, para->v->begin()+index_end+1);
    }
  }
  map< string, variable * > *lobsvars = get_lobsvars();
  if (lobsvars != NULL && lobsvars->size() > 0) {
    map< string, basictype * >*envars = (*agents)[0]->get_vars();
    for (map< string, basictype * >::iterator i = envars->begin(); i != envars->end(); i++) {
      if (lobsvars->find(i->first) != lobsvars->end()) {  // i->first is local observable variable 
	basictype *bt = i->second;
	int index_begin = bt->get_index_begin();
	int index_end = bt->get_index_end();
	lv.insert(lv.end(), para->v->begin()+index_begin, para->v->begin()+index_end+1);
      }
    }
  }
  lv.insert(lv.end(), para->v->begin()+get_var_index_begin(), para->v->begin()+get_var_index_end()+1);
  return lv;
}

vector< BDD* >*
basic_agent::split_protocol(BDD prot, bdd_parameters * para)
{
  BDD tmpprot = prot;
  //cout << "prot:";
  //prot.print(2, 2);

  tmpprot = reduce_whole_state_for_enumerate(tmpprot, para);
  //cout << "tmpprot:";
  //tmpprot.print(2, 2);

  vector< BDD > lv = get_localstate_BDD_vector(para);

  vector< BDD* > *newprot = new vector< BDD* >;
  vector< BDD* > *newprot1 = new vector< BDD* >;
  
  newprot->push_back(new BDD(para->bddmgr->bddZero()));
  vector< BDD > action_vector;
  action_vector.insert(action_vector.end(), para->a->begin()+get_action_index_begin(), para->a->begin()+get_action_index_end()+1);

  while(tmpprot != para->bddmgr->bddZero()) {
    // pick up an arbitrary local state
    BDD localstate = tmpprot.PickOneMinterm(lv);
    //cout << "localstate:";
    //localstate.print(2, 2);

    // complete state for integer values
    localstate = compute_whole_state_for_integer(localstate, para);
    //cout << "newlocalstate:";
    //localstate.print(2, 2);

    BDD protline = tmpprot * localstate;
    // remove the chosen local state from the protocol
    tmpprot -= localstate;
    //cout << "newprot:";
    //tmpprot.print(2, 2);

    // split actions
    BDD acts = Exists(para->bddmgr, para->v, protline);
    //cout << "acts:";
    //acts.print(2, 2);
    while(acts != para->bddmgr->bddZero()) {
      // pick up an action
      BDD act = acts.PickOneMinterm(action_vector);
      //cout << "act:";
      //act.print(2, 2);

      acts -= act;
      //cout << "newacts:";
      //acts.print(2, 2);
      // construct a uniform strategy
      BDD protline = localstate * act;      
      for(unsigned int i=0; i<newprot->size(); i++) 
	newprot1->push_back(new BDD(*(*newprot)[i] + protline));
    }
    //cout << "checkpoint 6: " << newprot1->size() << endl;
    //exit(0);
    for(unsigned int x=0; x<newprot->size(); x++)
      delete (*newprot)[x];
    delete newprot;
    newprot = newprot1;;
    newprot1 = new vector < BDD* >;
  }
  delete newprot1;
  if(options["debug"] == 1)
    cout << newprot->size() << " uniform protocols" << endl;
  return newprot;
}
