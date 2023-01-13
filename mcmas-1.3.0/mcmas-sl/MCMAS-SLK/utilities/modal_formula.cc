#include <ctime>
#include "types.hh"
#include "strategy_logic.hh"
#include "utilities.hh"

using namespace std;

modal_formula::modal_formula(atomic_proposition * obj1)
{       // term
  op = 0;
  obj[0] = obj1;
}

modal_formula::modal_formula(unsigned char o, modal_formula * f1)
{       // sigle operand formula
  op = o;
  obj[0] = f1;
}

modal_formula::modal_formula(unsigned char o, modal_formula * f1,
                             modal_formula * f2)
{       // two operands formula
  op = o;
  obj[0] = f1;
  obj[1] = f2;
}

modal_formula::modal_formula(unsigned char o, modal_formula * f1,
                             modal_formula * f2, modal_formula * f3)
{       // three operands formula
  op = o;
  obj[0] = f1;
  obj[1] = f2;
  obj[2] = f3;
}

modal_formula::modal_formula(modal_formula * f)
{
  op = f->op;
  for (unsigned int i = 0; i < 3; i++) {
    obj[i] = f->obj[i];
  }
}

modal_formula::~modal_formula()
{
}

unsigned char
modal_formula::get_op()
{
  return op;
}

Object *
modal_formula::get_operand(unsigned char i)
{
  if (i == 0 && obj[0] != NULL)
    return (obj[0]);
  else if (i == 1 && obj[1] != NULL &&
           (op == 1 || op == 2 || op == 4 || op == 16 || op == 17 ||
            op == 30 || op == 31 || op == 32 || op == 40 ||
            op == 42 || op == 45 || op == 46 || op == 47 || op == 48 ||
            op == 50 || op == 51 || op == 52 || op == 56)) {
    return (obj[1]);
  } else if (i == 2 && obj[2] != NULL && (op == 48 || op == 52))
    return (obj[2]);
  else {
    cout << " error: operand " << (int) i << " not found!" << endl;
    exit(1);
  }
}

string
modal_formula::to_string()
{
  switch (op) {
    case 0:
      return ((atomic_proposition *) obj[0])->to_string();
    case 1:
      return "(" + ((modal_formula *) obj[0])->to_string() + " && " +
        ((modal_formula *) obj[1])->to_string() + ")";
    case 2:
      return "(" + ((modal_formula *) obj[0])->to_string() + " || " +
        ((modal_formula *) obj[1])->to_string() + ")";
    case 3:
      return "(! " + ((modal_formula *) obj[0])->to_string() + ")";
    case 4:
      return "(" + ((modal_formula *) obj[0])->to_string() + " -> " +
        ((modal_formula *) obj[1])->to_string() + ")";
    case 10:
      return "(AG " + ((modal_formula *) obj[0])->to_string() + ")";
    case 11:
      return "(EG " + ((modal_formula *) obj[0])->to_string() + ")";
    case 12:
      return "(AX " + ((modal_formula *) obj[0])->to_string() + ")";
    case 13:
      return "(EX " + ((modal_formula *) obj[0])->to_string() + ")";
    case 14:
      return "(AF " + ((modal_formula *) obj[0])->to_string() + ")";
    case 15:
      return "(EF " + ((modal_formula *) obj[0])->to_string() + ")";
    case 16:
      return "A(" + ((modal_formula *) obj[0])->to_string() + " U " +
        ((modal_formula *) obj[1])->to_string() + ")";
    case 17:
      return "E(" + ((modal_formula *) obj[0])->to_string() + " U " +
        ((modal_formula *) obj[1])->to_string() + ")";
    case 30:
      return "K(" + ((modal_formula *) obj[0])->to_string() + ", " +
        ((modal_formula *) obj[1])->to_string() + ")";
    case 31:
      return "GK(" + ((modal_formula *) obj[0])->to_string() + ", " +
        ((modal_formula *) obj[1])->to_string() + ")";
    case 32:
      return "GCK(" + ((modal_formula *) obj[0])->to_string() + ", " +
        ((modal_formula *) obj[1])->to_string() + ")";
    case 40:
      return "O(" + ((modal_formula *) obj[0])->to_string() + ", " +
        ((modal_formula *) obj[1])->to_string() + ")";
    case 42:
      return "DK(" + ((modal_formula *) obj[0])->to_string() + ", " +
        ((modal_formula *) obj[1])->to_string() + ")";
    case 45:
      return "(<" + ((modal_formula *) obj[0])->to_string() + ">X " +
        ((modal_formula *) obj[1])->to_string() + ")";
    case 46:
      return "(<" + ((modal_formula *) obj[0])->to_string() + ">F " +
        ((modal_formula *) obj[1])->to_string() + ")";
    case 47:
      return "(<" + ((modal_formula *) obj[0])->to_string() + ">G " +
        ((modal_formula *) obj[1])->to_string() + ")";
    case 48:
      return "<" + ((modal_formula *) obj[0])->to_string() + ">(" +
        ((modal_formula *) obj[1])->to_string() + " U " +
        ((modal_formula *) obj[2])->to_string() + ")";
    case 50:
      return "<<" + ((modal_formula *) obj[0])->to_string() + ">> " +
        ((modal_formula *) obj[1])->to_string();
    case 51:
      return "[[" + ((modal_formula *) obj[0])->to_string() + "]] " +
        ((modal_formula *) obj[1])->to_string();
    case 52:
      return "(" + ((modal_formula *) obj[0])->to_string() + ", " +
        ((modal_formula *) obj[1])->to_string() + ") " +
        ((modal_formula *) obj[2])->to_string();
    case 53:
      return "X " + ((modal_formula *) obj[0])->to_string();
    case 54:
      return "F " + ((modal_formula *) obj[0])->to_string();
    case 55:
      return "G " + ((modal_formula *) obj[0])->to_string();
    case 56:
      return "(" + ((modal_formula *) obj[0])->to_string() + " U " +
        ((modal_formula *) obj[1])->to_string() + ")";
    default:
      return "@@@INVALID FORMULA@@@";
  }
}

bool
modal_formula::check_atomic_proposition()
{
  set<string> variables;
  set<string> agents;
  return check_atomic_proposition(0, &variables, &agents);
}

bool
modal_formula::check_atomic_proposition(unsigned char type,
                                        set<string> *variables,
                                        set<string> *agents)
{
  // type = 0: atomic proposition
  // type = 1: agent
  // type = 2: group
  // type = 3: agent or group
  bool b1, b2, b3;

  switch (op) {
    case 1:       // AND
    case 2:       // OR
    case 4:       // IMPLIES
    case 16:      // AU
    case 17:      // EU
      b1 = ((modal_formula *) obj[0])->check_atomic_proposition(0, variables,
          agents);
      b2 = ((modal_formula *) obj[1])->check_atomic_proposition(0, variables,
          agents);
      return (b1 && b2);
    case 3:       // NOT
    case 10:      // AG
    case 11:      // EG
    case 12:      // AX
    case 13:      // EX
    case 14:      // AF
    case 15:      // EF
      return ((modal_formula *) obj[0])->check_atomic_proposition(0, variables,
          agents);
    case 30:      // K
      b1 = ((modal_formula *) obj[0])->check_atomic_proposition(1, variables,
          agents);
      b2 = ((modal_formula *) obj[1])->check_atomic_proposition(0, variables,
          agents);
      return (b1 && b2);
    case 40:      // O -- Does it allow a group name to appear? 
      b1 = ((modal_formula *) obj[0])->check_atomic_proposition(1, variables,
          agents);
      b2 = ((modal_formula *) obj[1])->check_atomic_proposition(0, variables,
          agents);
      return (b1 && b2);
    case 31:      // GK
    case 32:      // GCK
    case 42:      // DK
    case 45:      // ATL X
    case 46:      // ATL F
    case 47:      // ATL G
      b1 = ((modal_formula *) obj[0])->check_atomic_proposition(2, variables,
          agents);
      b2 = ((modal_formula *) obj[1])->check_atomic_proposition(0, variables,
          agents);
      return (b1 && b2);
    case 48:      // ATL U
      b1 = ((modal_formula *) obj[0])->check_atomic_proposition(2, variables,
          agents);
      b2 = ((modal_formula *) obj[1])->check_atomic_proposition(0, variables,
          agents);
      b3 = ((modal_formula *) obj[2])->check_atomic_proposition(0, variables,
          agents);
      return (b1 && b2 && b3);
    case 50:      // SL <<x>>
    case 51:      // SL [[x]]
      return check_sl_quantifier_syntax(variables, agents);
    case 52:      // SL (a, x)
      return check_sl_binding_syntax(variables, agents);
    case 53:      // SL X
    case 54:      // SL F
    case 55:      // SL G
      b1 = check_sl_temporal_syntax(agents);
      b2 = ((modal_formula *) obj[0])->check_atomic_proposition(0, variables,
          agents);
      return b1 && b2;
    case 56:      // SL U
      b1 = check_sl_temporal_syntax(agents);
      b2 = ((modal_formula *) obj[0])->check_atomic_proposition(0, variables,
          agents);
      b3 = ((modal_formula *) obj[1])->check_atomic_proposition(0, variables,
          agents);
      return b1 && b2 && b3;
    case 0:       // A leaf node
      string name = ((atomic_proposition *) obj[0])->get_proposition();
      switch (type) {
        case 0:
          if (is_evaluation->find(name) == is_evaluation->end()) {
            cout << "    atomic proposition " << name << " is not defined." <<
              endl;
            return false;
          } else
            return true;
        case 1:
          if (is_agents->find(name) == is_agents->end()) {
            cout << "    agent " << name << " is not defined." << endl;
            return false;
          } else
            return true;
        case 2:
          if (is_groups->find(name) == is_groups->end()) {
            cout << "    group " << name << " is not defined." << endl;
            return false;
          } else
            return true;
        case 3:
          if (is_agents->find(name) == is_agents->end() &&
              is_groups->find(name) == is_groups->end()) {
            cout << "    agent " << name << " is not defined." << endl;
            return false;
          } else
            return true;
      }
  }
  return false;
}

bool
modal_formula::check_sl_quantifier_syntax(set<string> *variables,
                                          set<string> *agents)
{
  // Add the variable to the set of quantified variables.
  string variable_name = ((atomic_proposition *)
      ((modal_formula *) obj[0])->obj[0])->get_proposition();
  bool newly_defined = variables->insert(variable_name).second;

  bool result = ((modal_formula *) obj[1])->check_atomic_proposition(0,
      variables, agents);

  // Remove the variable from the set of quantified variables (unless
  // redefined).
  if (newly_defined) {
    variables->erase(variable_name);
  }

  return result;
}

bool
modal_formula::check_sl_binding_syntax(set<string> *variables, 
                                       set<string> *agents)
{
  string variable_name = ((atomic_proposition *)
      ((modal_formula *) obj[1])->obj[0])->get_proposition();

  // Check that the variable is quantified.
  bool quantified = variables->find(variable_name) != variables->end();
  if (!quantified) {
    cout << "    strategy variable " << variable_name <<
        " is not quantified." << endl;
  }

  // Add the agent to the set of bound agents.
  string agent_name = ((atomic_proposition *)
      ((modal_formula *) obj[0])->obj[0])->get_proposition();
  bool newly_bound = agents->insert(agent_name).second;

  bool b1 = ((modal_formula *) obj[0])->check_atomic_proposition(1,
      variables, agents);
  bool b2 = ((modal_formula *) obj[2])->check_atomic_proposition(0,
      variables, agents);

  // Remove the agent from the set of bound agents (unless re-bound).
  if (newly_bound) {
    agents->erase(agent_name);
  }

  return quantified && b1 && b2;
}

bool
modal_formula::check_sl_temporal_syntax(set<string> *agents)
{
  bool all_bound = true;
  for (map<string, basic_agent *>::iterator i = is_agents->begin();
       i != is_agents->end(); i++) {
    if (agents->find(i->first) == agents->end()) {
      cout << "    agent " << i->first << " is not bound to a strategy" << 
          " variable before a temporal operator is applied." << endl;
      all_bound = false;
    }
  }
  return all_bound;
}

set<basic_agent *>
modal_formula::get_sharing_agents(string variable_name)
{
  set<basic_agent *> sharing_agents;
  get_sharing_agents(variable_name, &sharing_agents);
  return sharing_agents;
}

void
modal_formula::get_sharing_agents(string variable_name,
                                  set<basic_agent *> *sharing_agents)
{
  switch (op) {
    case 0:
      break;
    case 1:     // AND
    case 2:     // OR
    case 4:     // IMPLIES
    case 16:    // AU (see check_AU)
    case 17:    // EU
    case 56:    // SL operator U
      ((modal_formula *) obj[0])->get_sharing_agents(variable_name,
          sharing_agents);
      ((modal_formula *) obj[1])->get_sharing_agents(variable_name,
          sharing_agents);
      break;
    case 3:     // NOT
    case 10:    // AG p = !EF !p
    case 11:    // EG
    case 12:    // AX p = ! EX !p
    case 13:    // EX
    case 14:    // AF p = !EG !p
    case 15:    // EF p = p \lor EX EF p
    case 53:    // SL operator X
    case 54:    // SL operator F
    case 55:    // SL operator G
      ((modal_formula *) obj[0])->get_sharing_agents(variable_name,
          sharing_agents);
      break;
    case 30:    // K
    case 31:    // Everybody knows
    case 32:    // Common knowledge
    case 40:    // O
    case 42:    // Distributed knowledge
    case 45:    // ATL operator X
    case 46:    // ATL operator F
    case 47:    // ATL operator G
      ((modal_formula *) obj[1])->get_sharing_agents(variable_name,
          sharing_agents);
      break;
    case 48:    // ATL operator U
      ((modal_formula *) obj[1])->get_sharing_agents(variable_name,
          sharing_agents);
      ((modal_formula *) obj[2])->get_sharing_agents(variable_name,
          sharing_agents);
      break;
    case 50:    // SL operator <<x>>
    case 51:    // SL operator [[x]]
      {
        string quantified_variable_name = ((atomic_proposition *)
            ((modal_formula *) obj[0])->obj[0])->get_proposition();
        if (quantified_variable_name != variable_name) {
          ((modal_formula *) obj[1])->get_sharing_agents(variable_name,
              sharing_agents);
        }
        break;
      }
    case 52:    // SL operator (a, x)
      {
        string quantified_variable_name = ((atomic_proposition *)
            ((modal_formula *) obj[1])->obj[0])->get_proposition();
        if (quantified_variable_name == variable_name) {
          string agent_name = ((atomic_proposition *)
              ((modal_formula *) obj[0])->obj[0])->get_proposition();
          sharing_agents->insert(is_agents->find(agent_name)->second);
        }
        ((modal_formula *) obj[2])->get_sharing_agents(variable_name,
            sharing_agents);
        break;
      }
  }
}

BDD
modal_formula::check_formula(bdd_parameters * para)
{
  map<string, strategy *> variables;
  map<string, strategy *> agents;
  return check_formula(para, &variables, &agents);
}

BDD
modal_formula::check_formula(bdd_parameters * para,
                             map<string, strategy *> *variables,
                             map<string, strategy *> *agents)
{
  BDD result, rel, af, phi1, phi2;
  string name, name1;
  Object *id;

  switch (op) {
    case 0:     // leaf
      {
        name = ((atomic_proposition *) obj[0])->get_proposition();
        if(options["nobddcache"] == 0)
          if (para->BDD_cache->find(name) != para->BDD_cache->end())
            return ((*para->BDD_cache)[name]);
        bool_expression *simple = is_evaluation->find(name)->second;
        result = simple->encode_bdd_flat(para, para->bddmgr->bddOne()) * (*para->reach);
        if(options["nobddcache"] == 0)
          (*para->BDD_cache)[name] = result;
        break;
      }
    case 1:     // AND
      result = ((modal_formula *) obj[0])->check_formula(para, variables,
          agents) * ((modal_formula *) obj[1])->check_formula(para, variables,
          agents);
      break;
    case 2:     // OR
      result = ((modal_formula *) obj[0])->check_formula(para, variables,
          agents) + ((modal_formula *) obj[1])->check_formula(para, variables,
          agents);
      break;
    case 3:     // NOT
      result = !((modal_formula *) obj[0])->check_formula(para, variables,
          agents);
      break;
    case 4:     // IMPLIES
      phi1 = !(((modal_formula *) obj[0])->check_formula(para, variables,
          agents)) * (*para->reach);
      phi2 = ((modal_formula *) obj[1])->check_formula(para, variables, agents);
      result = phi1 + phi2;
      break;
    case 10:      // AG p = !EF !p
      phi1 = (!((modal_formula *) obj[0])->check_formula(para, variables,
          agents)) * (*para->reach);
      result = !check_EF(phi1, para);
      break;
    case 11:      // EG 
      phi1 = ((modal_formula *) obj[0])->check_formula(para, variables, agents);
      result = check_EG(phi1, para);
      break;
    case 12:      // AX p = ! EX !p
      phi1 = (!((modal_formula *) obj[0])->check_formula(para, variables,
          agents)) * (*para->reach);
      result = !check_EX(phi1, para);
      break;
    case 13:      // EX
      phi1 = ((modal_formula *) obj[0])->check_formula(para, variables, agents);
      result = check_EX(phi1, para);
      break;
    case 14:      // AF p = !EG !p
      phi1 = (!((modal_formula *) obj[0])->check_formula(para, variables,
          agents)) * (*para->reach);
      result = !check_EG(phi1, para);
      break;
    case 15:      // EF p = p \lor EX EF p
      phi1 = ((modal_formula *) obj[0])->check_formula(para, variables, agents);
      result = check_EF(phi1, para);
      break;
    case 16:      // AU (see check_AU)
      phi1 = ((modal_formula *) obj[0])->check_formula(para, variables, agents);
      phi2 = ((modal_formula *) obj[1])->check_formula(para, variables, agents);
      result = check_AU(phi1, phi2, para);
      break;
    case 17:      // EU
      phi1 = ((modal_formula *) obj[0])->check_formula(para, variables, agents);
      phi2 = ((modal_formula *) obj[1])->check_formula(para, variables, agents);
      result = check_EU(phi1, phi2, para);
      break;
    case 30:      // K
      id = ((modal_formula *) obj[0])->get_operand(0);
      name = ((atomic_proposition *) id)->get_proposition();
      af = !((modal_formula *) obj[1])->check_formula(para, variables, agents) *
          (*para->reach);
      result = (*para->reach) - get_nK_states(&af, name, para);
      break;
    case 31:      // Everybody knows
      id = ((modal_formula *) obj[0])->get_operand(0);
      name = ((atomic_proposition *) id)->get_proposition();
      af = ((modal_formula *) obj[1])->check_formula(para, variables, agents);
      result = check_GK(af, name, para);
      break;
    case 32:      // Common knowledge
      id = ((modal_formula *) obj[0])->get_operand(0);
      name = ((atomic_proposition *) id)->get_proposition();
      af = ((modal_formula *) obj[1])->check_formula(para, variables, agents);
      result = check_GCK(af, name, para);
      break;
    case 40:      // O
      id = ((modal_formula *) obj[0])->get_operand(0);
      name = ((atomic_proposition *) id)->get_proposition();
      af = !((modal_formula *) obj[1])->check_formula(para, variables, agents) *
          (*para->reach);
      result = !check_nO(af, name, para);
      break;
    case 42:      // Distributed knowledge
      id = ((modal_formula *) obj[0])->get_operand(0);
      name = ((atomic_proposition *) id)->get_proposition();
      af = ((modal_formula *) obj[1])->check_formula(para, variables, agents);
      result = check_DK(((modal_formula *) obj[1])->check_formula(para,
          variables, agents), name, para);
      break;
    case 45:      // ATL operator X
      id = ((modal_formula *) obj[0])->get_operand(0);
      name = ((atomic_proposition *) id)->get_proposition();
      phi1 = ((modal_formula *) obj[1])->check_formula(para, variables, agents);
      result = check_ATLX(phi1, name, para);
      break;
    case 46:      // ATL operator F
      id = ((modal_formula *) obj[0])->get_operand(0);
      name = ((atomic_proposition *) id)->get_proposition();
      phi1 = ((modal_formula *) obj[1])->check_formula(para, variables, agents);
      result =
        check_ATLU(para->bddmgr->bddOne(), phi1, name, para);
      break;
    case 47:      // ATL operator G
      id = ((modal_formula *) obj[0])->get_operand(0);
      name = ((atomic_proposition *) id)->get_proposition();
      phi1 = ((modal_formula *) obj[1])->check_formula(para, variables, agents);
      result = check_ATLG(phi1, name, para);
      break;
    case 48:      // ATL operator U
      id = ((modal_formula *) obj[0])->get_operand(0);
      name = ((atomic_proposition *) id)->get_proposition();
      phi1 = ((modal_formula *) obj[1])->check_formula(para, variables, agents);
      phi2 = ((modal_formula *) obj[2])->check_formula(para, variables, agents);
      result = check_ATLU(phi1, phi2, name, para);
      break;
    case 50:      // SL operator <<x>>
      {
        int previous_next_bdd_variable = next_bdd_variable;
        pair<BDD, strategy> subresult = check_sl_quantified_subformula(para,
            variables, agents);
        result = check_SL_EXISTS(subresult.first, &subresult.second, para);
        next_bdd_variable = previous_next_bdd_variable;
        break;
      }
    case 51:      // SL operator [[x]]
      {
        int previous_next_bdd_variable = next_bdd_variable;
        pair<BDD, strategy> subresult = check_sl_quantified_subformula(para,
            variables, agents);
        result = check_SL_FORALL(subresult.first, &subresult.second, para);
        next_bdd_variable = previous_next_bdd_variable;
        break;
      }
    case 52:      // SL operator (a, x)
      result = check_sl_binding_subformula(para, variables, agents);
      break;
    case 53:      // SL operator X
      phi1 = ((modal_formula *) obj[0])->check_formula(para, variables,
          agents) * (*para->reach);
      result = check_SL_X(phi1, agents, para);
      break;
    case 54:      // SL operator F
      phi1 = ((modal_formula *) obj[0])->check_formula(para, variables,
          agents) * (*para->reach);
      result = check_SL_F(phi1, agents, para);
      break;
    case 55:      // SL operator G
      phi1 = ((modal_formula *) obj[0])->check_formula(para, variables,
          agents) * (*para->reach);
      result = check_SL_G(phi1, agents, para);
      break;
    case 56:      // SL operator U
      phi1 = ((modal_formula *) obj[0])->check_formula(para, variables,
          agents) * (*para->reach);
      phi2 = ((modal_formula *) obj[1])->check_formula(para, variables,
          agents) * (*para->reach);
      result = check_SL_U(phi1, phi2, agents, para);
      break;
  }
  return result * (*para->reach);
}

pair<BDD, strategy>
modal_formula::check_sl_quantified_subformula(bdd_parameters * para,
    map<string, strategy *> *variables, map<string, strategy *> *agents)
{
  string variable_name = ((atomic_proposition *)
      ((modal_formula *) obj[0])->obj[0])->get_proposition();

  // Build the new strategy.
  modal_formula *subformula = (modal_formula *) obj[1];
  strategy new_strategy = build_strategy(variable_name, subformula, para);

  // Store the previous strategy and assign the new one.
  strategy *previous_strategy = NULL;
  map<string, strategy *>::iterator position = variables->find(variable_name);
  if (position != variables->end()) {
    previous_strategy = position->second;
    position->second = &new_strategy;
  } else {
    position = variables->insert(make_pair(variable_name, &new_strategy)).first;
  }

  // Calculate the subresult.
  BDD phi = (subformula->check_formula(para, variables, agents)) *
      (*para->reach);

  // Restore the previous strategy.
  if (previous_strategy != NULL) {
    position->second = previous_strategy;
  } else {
    variables->erase(position);
  }

  return make_pair(phi, new_strategy);
}

BDD
modal_formula::check_sl_binding_subformula(bdd_parameters * para,
                                           map<string, strategy *> *variables,
                                           map<string, strategy *> *agents)
{
  string agent_name = ((atomic_proposition *)
      ((modal_formula *) obj[0])->obj[0])->get_proposition();
  string variable_name = ((atomic_proposition *)
      ((modal_formula *) obj[1])->obj[0])->get_proposition();

  // Get the new strategy.
  strategy *new_strategy = variables->find(variable_name)->second;

  // Store the previous strategy and assign the new one.
  strategy *previous_strategy = NULL;
  map<string, strategy *>::iterator position = agents->find(agent_name);
  if (position != agents->end()) {
    previous_strategy = position->second;
    position->second = new_strategy;
  } else {
    position = agents->insert(make_pair(agent_name, new_strategy)).first;
  }

  // Store previous SL restriction BDD.
  bool oldCalRestrictSL = para->calRestrictSL;
  BDD *oldRestrictSL = para->restrictSL;
  para->calRestrictSL = true;
  para->restrictSL = NULL;

  // Calculate the subresult.
  modal_formula *subformula = (modal_formula *) obj[2];
  BDD phi = (subformula->check_formula(para, variables, agents)) *
      (*para->reach);

  // Restore previous SL restriction BDD.
  if (para->restrictSL != NULL) {
    delete para->restrictSL;
  }
  para->calRestrictSL = oldCalRestrictSL;
  para->restrictSL = oldRestrictSL;

  // Restore the previous strategy.
  if (previous_strategy != NULL) {
    position->second = previous_strategy;
  } else {
    agents->erase(position);
  }

  return phi;
}

modal_formula *
modal_formula::push_negations(unsigned int level)
{
  switch (op) {
  case 0:     // leaf
    {
      return new modal_formula(this);
      break;
    }
  case 1:     // AND
  case 2:     //OR
    {
      modal_formula *m =
        new modal_formula(op,
                          ((modal_formula *) obj[0])->push_negations(level),
                          ((modal_formula *) obj[1])->push_negations(level));
      return m;
      break;
    }
  case 3:     // NOT
    {
      if (((modal_formula *) obj[0])->get_op() == 0) {
        // Just copy and return
        return new modal_formula(this);
      } else {
        // Need to push down negation
        modal_formula *nextformula = (modal_formula *) obj[0];
        unsigned char nextop = nextformula->get_op();

        switch (nextop) {
        case 1:   // AND
          {
            modal_formula *m1 =
              new modal_formula(3,
                                (modal_formula *) nextformula->
                                get_operand(0));
            modal_formula *m2 =
              new modal_formula(3,
                                (modal_formula *) nextformula->
                                get_operand(1));
            modal_formula *result =
              new modal_formula(2, m1->push_negations(level),
                                m2->push_negations(level));
            return result;
            break;
          }
        case 2:   // OR
          {
            modal_formula *m1 =
              new modal_formula(3,
                                (modal_formula *) nextformula->
                                get_operand(0));
            modal_formula *m2 =
              new modal_formula(3,
                                (modal_formula *) nextformula->
                                get_operand(1));
            modal_formula *result =
              new modal_formula(1, m1->push_negations(level),
                                m2->push_negations(level));
            return result;
            break;
          }
        case 3:   // NOT: negation of negation, remove both.
          {
            return ((modal_formula *) nextformula->get_operand(0))->
              push_negations(level);
            break;
          }
        case 4:   // IMPLIES, !(a -> b) = a & !b
          {
            modal_formula *m2 =
              new modal_formula(3,
                                (modal_formula *) nextformula->
                                get_operand(1));
            modal_formula *result =
              new modal_formula(1,
                                ((modal_formula *) nextformula->
                                 get_operand(0))->push_negations(level),
                                m2->push_negations(level));
            return result;
            break;
          }
        case 10:    // AG: !AG=EF !
          {
            modal_formula *m1 =
              new modal_formula(3,
                                (modal_formula *) nextformula->
                                get_operand(0));
            modal_formula *result =
              new modal_formula(15, m1->push_negations(level + 1));
            return result;
            break;
          }
        case 11:    // EG: !EG=AF! 
          {
            modal_formula *m1 =
              new modal_formula(3,
                                (modal_formula *) nextformula->
                                get_operand(0));
            modal_formula *result =
              new modal_formula(14, m1->push_negations(level + 1));
            return result;
            break;
          }
        case 12:    // AX
          {
            modal_formula *m1 =
              new modal_formula(3,
                                (modal_formula *) nextformula->
                                get_operand(0));
            modal_formula *result =
              new modal_formula(13, m1->push_negations(level + 1));
            return result;
            break;
          }
        case 13:    // EX
          {
            modal_formula *m1 =
              new modal_formula(3,
                                (modal_formula *) nextformula->
                                get_operand(0));
            modal_formula *result =
              new modal_formula(12, m1->push_negations(level + 1));
            return result;
            break;
          }
        case 14:    // AF : !AF=EG!
          {
            modal_formula *m1 =
              new modal_formula(3,
                                (modal_formula *) nextformula->
                                get_operand(0));
            modal_formula *result =
              new modal_formula(11, m1->push_negations(level + 1));
            return result;
            break;
          }
        case 15:    // EF : !EF=AG!
          {
            modal_formula *m1 =
              new modal_formula(3,
                                (modal_formula *) nextformula->
                                get_operand(0));
            modal_formula *result =
              new modal_formula(10, m1->push_negations(level + 1));
            return result;
            break;
          }
        case 16:    // AU : a messy one: A[aUb] = ! (E[!bU(!a&!b)] | EG(!b)) (p.216 huth-ryan)
          {
            modal_formula *notb =
              new modal_formula(3,
                                (modal_formula *) nextformula->
                                get_operand(1));
            modal_formula *nota =
              new modal_formula(3,
                                (modal_formula *) nextformula->
                                get_operand(0));
            modal_formula *egnotb = new modal_formula(11, notb);
            modal_formula *notanotb = new modal_formula(1, nota, notb);
            modal_formula *until =
              new modal_formula(17, notb->push_negations(level + 1),
                                notanotb->push_negations(level + 1));
            modal_formula *result =
              new modal_formula(2, until, egnotb->push_negations(level + 1));
            return result;
            break;
          }
        case 17:    // EU: not sure, see above: E[aUb] = ! (A[!bU(!a&!b)] | AG(!b))
          {
            modal_formula *notb = new modal_formula(3,
                                                    (modal_formula *)
                                                    nextformula->
                                                    get_operand(1));
            modal_formula *nota = new modal_formula(3,
                                                    (modal_formula *)
                                                    nextformula->
                                                    get_operand(0));
            modal_formula *agnotb = new modal_formula(11, notb);
            modal_formula *notanotb = new modal_formula(1, nota, notb);
            modal_formula *until =
              new modal_formula(16, notb->push_negations(level + 1),
                                notanotb->push_negations(level + 1));
            modal_formula *result =
              new modal_formula(2, until, agnotb->push_negations(level + 1));
            return result;
            break;
          }
        case 40:    // not O_i \phi => EF (g_i and not \phi) 
          if (level == 0) {
            Object *id =
              ((modal_formula *) nextformula->get_operand(0))->get_operand(0);
            string name = ((atomic_proposition *) id)->get_proposition();
            string *newap = new string(name + ".GreenStates");
            modal_formula *newformula =
              new modal_formula(3,
                                (modal_formula *) nextformula->
                                get_operand(1));
            modal_formula *newformula1 = newformula->push_negations(1);
            modal_formula *newformula2 =
              new modal_formula(new atomic_proposition(newap));
            modal_formula *newformula3 =
              new modal_formula(15,
                                new modal_formula(1, newformula2,
                                                  newformula1));
            return newformula3;
          }
        case 50:    // not <<x>> \phi => [[x]] not \phi
          {
            modal_formula *m1 =
                new modal_formula(3,
                                  (modal_formula *) nextformula->
                                  get_operand(1));
            modal_formula *result =
                new modal_formula(51,
                                  (modal_formula *) nextformula->get_operand(0),
                                  m1->push_negations(level));
            return result;
            break;
          }
        case 51:    // not [[x]] \phi => <<x>> not \phi
          {
            modal_formula *m1 =
                new modal_formula(3,
                                  (modal_formula *) nextformula->
                                  get_operand(1));
            modal_formula *result =
                new modal_formula(50,
                                  (modal_formula *) nextformula->get_operand(0),
                                  m1->push_negations(level));
            return result;
            break;
          }
        case 52:    // not (a, x) \phi => (a, x) not \phi
          {
            modal_formula *m1 =
                new modal_formula(3,
                                  (modal_formula *) nextformula->
                                  get_operand(2));
            modal_formula *result =
                new modal_formula(52,
                                  (modal_formula *) nextformula->get_operand(0),
                                  (modal_formula *) nextformula->get_operand(1),
                                  m1->push_negations(level));
            return result;
            break;
          }
        case 53:    // not X \phi => X not \phi
          {
            modal_formula *m1 =
                new modal_formula(3,
                                  (modal_formula *) nextformula->
                                  get_operand(0));
            modal_formula *result =
                new modal_formula(53, m1->push_negations(level + 1));
            return result;
            break;
          }
        case 54:    // not F \phi => G not \phi
          {
            modal_formula *m1 =
                new modal_formula(3,
                                  (modal_formula *) nextformula->
                                  get_operand(0));
            modal_formula *result =
                new modal_formula(55, m1->push_negations(level + 1));
            return result;
            break;
          }
        case 55:    // not G \phi => F not \phi
          {
            modal_formula *m1 =
                new modal_formula(3,
                                  (modal_formula *) nextformula->
                                  get_operand(0));
            modal_formula *result =
                new modal_formula(54, m1->push_negations(level + 1));
            return result;
            break;
          }
        case 56:    // !(a U b) => (!b U (!a and !b)) or G !b
          {
            modal_formula *nota =
                new modal_formula(3,
                                  (modal_formula *) nextformula->
                                  get_operand(0));
            modal_formula *notb =
                new modal_formula(3,
                                  (modal_formula *) nextformula->
                                  get_operand(1));
            modal_formula *gnotb = new modal_formula(55, notb);
            modal_formula *notanotb = new modal_formula(1, nota, notb);
            modal_formula *until =
                new modal_formula(56, notb->push_negations(level + 1),
                                  notanotb->push_negations(level + 1));
            modal_formula *result =
                new modal_formula(2, until, gnotb->push_negations(level));
            return result;
            break;
          }
        default:{
          // Nothing to do for K etc:
          // Just copy and return
          return new modal_formula(this);
          break;
        }
        }     // end switch nextop in else:
      }       // end else
    }       // end case 3 (NOT)
  case 4:     // IMPLIES : a->b=!a|b
    {
      modal_formula *m1 = new modal_formula(3, (modal_formula *) obj[0]);
      modal_formula *result =
        new modal_formula(2, m1->push_negations(level),
                          ((modal_formula *) obj[1])->push_negations(level));
      return result;
      break;
    }
  case 10:
  case 11:
  case 12:
  case 13:
  case 14:
  case 15:
  case 53:
  case 54:
  case 55:
    {
      // Temporal is the first, SLX, SLF, SLG
      modal_formula *m =
        new modal_formula(op,
                          ((modal_formula *) obj[0])->push_negations(level +
                                                                     1));
      return m;
      break;
    }
  case 16:
  case 17:
  case 56:
    {
      // EU, AU, SLU, binary operators:
      modal_formula *m =
        new modal_formula(op,
                          ((modal_formula *) obj[0])->push_negations(level +
                                                                     1),
                          ((modal_formula *) obj[1])->push_negations(level +
                                                                     1));
      return m;
      break;
    }
  case 48:
    {
      // ATLU are the second and third thing
      modal_formula *m =
        new modal_formula(op, ((modal_formula *) obj[0]),
                          ((modal_formula *) obj[1])->push_negations(level +
                                                                     1),
                          ((modal_formula *) obj[2])->push_negations(level +
                                                                     1));
      return m;
      break;
    }
  case 52:
    {
      // SL agent binding
      modal_formula *m =
          new modal_formula(op, ((modal_formula *) obj[0]),
                            ((modal_formula *) obj[1]),
                            ((modal_formula *) obj[2])->push_negations(level +
                                                                       1));
      return m;
      break;
    }
  default:
    {
      // Epistemic and deontic, ATLX, ATLG, ATLF, SL quantifiers, is the second
      modal_formula *m =
        new modal_formula(op, ((modal_formula *) obj[0]),
                          ((modal_formula *) obj[1])->push_negations(level +
                                                                     1));
      return m;
      break;
    }
  }       // end top case
}

bool
modal_formula::is_ACTLK_new()
{
  /* Return TRUE if the first operator in the formula is ACTL (i.e., only A quantifiers and
   * K and negation only in front of propositions.
   * All the negations should have been pushed down already.
   */

  switch (op) {
  case 0:     // leaf
    {
      return true;
      break;
    }
  case 1:     // AND
    {
      return (((modal_formula *) obj[0])->
              is_ACTLK_new() & ((modal_formula *) obj[1])->is_ACTLK_new());
      break;
    }
  case 2:     // OR
    {
      return (((modal_formula *) obj[0])->
              is_ACTLK_new() & ((modal_formula *) obj[1])->is_ACTLK_new());
      break;
    }
  case 3:     // NOT
    {
      return true;
      break;
    }
  case 4:     // IMPLIES
    {
      // Again, this should not be here.
      if (((modal_formula *) obj[0])->get_op() == 0) {
        return ((modal_formula *) obj[1])->is_ACTLK_new();
      } else {
        return false;
      }
      break;
    }

  case 10:      // AG
  case 12:      // AX
  case 14:      // AF
  case 16:      // AU
    {
      return true;
    }
  case 11:      // EG 
  case 13:      // EX
  case 15:      // EF
  case 17:      // EU
    {
      return false;
      break;
    }

  case 30:
  case 31:
  case 32:
  case 40:
  case 42:
    return true;
  case 45:      // ATL 
  case 46:
  case 47:
  case 48:
    if (options["atlcex"] > 0)
      return true;
  case 51:      // SL [[x]]
    return true;
  }

  return false;
}

bool
modal_formula::is_ECTLK_new()
{
  /* Return TRUE if the first operator in the formula is ECTL (i.e., only E quantifiers and
   * \neg K, i.e., negation only in front of propositions and K operator
   */

  switch (op) {
  case 0:     // leaf
    {
      return true;
      break;
    }
  case 1:     // AND
    {
      return (((modal_formula *) obj[0])->
              is_ECTLK_new() & ((modal_formula *) obj[1])->is_ECTLK_new());
      break;
    }
  case 2:     // OR
    {
      return (((modal_formula *) obj[0])->
              is_ECTLK_new() & ((modal_formula *) obj[1])->is_ECTLK_new());
      break;
    }
  case 3:     // NOT
    {
      return true;
      break;
    }
  case 4:     // IMPLIES
    {
      if (((modal_formula *) obj[0])->get_op() == 0) {
        return ((modal_formula *) obj[1])->is_ECTLK_new();
      } else {
        return false;
      }
      break;
    }

  case 10:      // AG
  case 12:      // AX
  case 14:      // AF
  case 16:      // AU
    {
      return false;
    }
  case 11:      // EG 
  case 13:      // EX
  case 15:      // EF
  case 17:      // EU
    {
      return true;
    }
  case 30:
  case 31:
  case 32:
  case 40:
  case 42:
    // Now we check ATL formulas
  case 45:      // ATL operator X
  case 46:      // ATL operator F
  case 47:      // ATL operator G
  case 48:      // ATL operator U
    return true;
  case 50:      // ATL operator <<x>>
    return true;
  }
  return false;
}

/** return true if there is no temporal operator in the formula.
 ** do not check the formula inside epistemic operators */
bool
modal_formula::is_NoCTL()
{
  switch (op) {
  case 0:     // leaf
  case 30:
  case 31:
  case 32:
  case 40:
  case 42:
    {
      return true;
    }
  case 1:     // AND
  case 2:     // OR
  case 4:     // IMPLIES
    {
      return (((modal_formula *) obj[0])->
              is_NoCTL() & ((modal_formula *) obj[1])->is_NoCTL());
    }
  case 3:     // NOT
    {
      return ((modal_formula *) obj[0])->is_NoCTL();
    }
  }
  return false;
}

void
generate_index(int *current_index, int *next_index)
{
  *current_index = *next_index;
  *next_index = ++scount + 1;
}

/* Generate a witness for an ECTLK formula (i.e.  acounterexample
 * for an ACTLK formula), see
 * Clarke et al., "Tree-like counterexamples in model checking"
 * See the algorithm in Figure 7. Essentially, this procedure builds a tree 
 * representing a witness for the formula.
 * Returns false if the witness cannot be built (maybe because starting from
 * the wrong initial state)
 */
/** index is used to retrieve the index of the state */
bool
modal_formula::build_cex(BDD *state, unsigned int index, bdd_parameters *para,
                         vector<vector<int> *> *countex,
                         map<int, BDD *> *idbdd,
                         vector<vector<transition *> *> *cextr,
                         map<string, pair<strategy, BDD> > *strategies)
{
  map<string, strategy *> variables;
  map<string, strategy *> agents;
  return build_cex(
      state, index, para, countex, idbdd, cextr, &variables, &agents,
      strategies);
}

bool
modal_formula::build_cex(BDD *state, unsigned int index, bdd_parameters *para, 
                         vector<vector<int> *> *countex,
                         map<int, BDD *> *idbdd,
                         vector<vector<transition *> *> *cextr,
                         map<string, strategy *> *variables,
                         map<string, strategy *> *agents,
                         map<string, pair<strategy, BDD> > *strategies)
{
  vector< BDD * >tmpresult; // a vector to store the states of the witness
  vector< int >desc;    // This is a vector of state id (see global variables countex and idbdd)
  vector< transition * >desctr; // This is a vector of transitions (see golbal var cextr)

  int current_index = index;
  int next_index = scount + 1;

  Object *id;
  string name;

  BDD actagtin = para->bddmgr->bddOne();  // Actions of agents in group
  BDD actagtout = para->bddmgr->bddOne(); // Actions of agents NOT in group
  if (op == 45 || op == 46 || op == 47 || op == 48 ||
      (op == 3 && ((modal_formula *) obj[0])->get_op() >= 45
       && ((modal_formula *) obj[0])->get_op() <= 48)) {
    int begin, end;
    id = op != 3 ? ((modal_formula *) obj[0])->get_operand(0) :
      ((modal_formula *) ((modal_formula *) obj[0])->get_operand(0))->
      get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    map< string, set< string > >::iterator gi = is_groups->find(name);
    set< string > names_g = gi->second; // the list of agt names in groups

    for (map< string, basic_agent * >::iterator i = is_agents->begin();
         i != is_agents->end(); i++) {
      begin = i->second->get_action_index_begin();
      end = i->second->get_action_index_end();
      if (names_g.find(i->first) == names_g.end())
        for (int j = begin; j <= end; j++)
          actagtout = actagtout * (*para->a)[j];
      else
        for (int j = begin; j <= end; j++)
          actagtin = actagtin * (*para->a)[j];
    }
  }

  switch (op) {
  case 1:     // AND
    {
      bool r1 = ((modal_formula *) obj[0])->build_cex(
          state, index, para, countex, idbdd, cextr, variables, agents,
          strategies);
      if (!r1)
        return false;
      bool r2 = ((modal_formula *) obj[1])->build_cex(
          state, index, para, countex, idbdd, cextr, variables, agents,
          strategies);
      if (!r2)
        return false;
      return true;
      break;
    }
  case 2:     // OR
    {
      bool r1;
      modal_formula *left = ((modal_formula *) obj[1]);
      BDD res = left->check_formula(para, variables, agents);

      if ((*state) <= res) {
        r1 = left->build_cex(
            state, index, para, countex, idbdd, cextr, variables, agents,
            strategies);
        if (!r1)
          return false;
      } else {
        modal_formula *right = ((modal_formula *) obj[0]);
        r1 = right->build_cex(
            state, index, para, countex, idbdd, cextr, variables, agents,
            strategies);
      }
      return r1;
      break;
    }
  case 11:      // EG 
    {
      //vector< BDD * >S; // a vector to store the stages of the computation
      tmpresult.push_back(new BDD(*state));
      int loopstart = -1; // the position where the loop starts

      if(is_fairness->empty()) {
        BDD last = check_formula(para, variables, agents); // the last state of fixpoint computation
        // Need to find a cycle here
  
        int j = 0;
  
        BDD Q = para->bddmgr->bddZero();
        BDD T = para->bddmgr->bddZero() + *state;
  
        // BDD tmp = para->bddmgr->bddZero();
        // BDD q = para->bddmgr->bddOne();
        // BDD fc_bdd = para->bddmgr->bddOne();
        // while (q != tmp) {
        //  tmp = q;
        //  for (vector < fairness_expression * >::iterator fi =
        //         is_fairness->begin(); fi != is_fairness->end(); fi++) {
        //    BDD hf = (*fi)->get_bdd_representation(); // The BDD for the fairness constraint
        //    BDD tmp1 = check_EU(p, q * hf, para);
        //    fc_bdd = fc_bdd * check_EX(tmp1, para);
        //  }
        //  q = p * fc_bdd;
        // }
  
        while (Q == para->bddmgr->bddZero()) {
          j++;
    
          BDD reachablefromlast =
            timesRT(tmpresult[j - 1], para->bddmgr, para->vRT, para->a);
    
          reachablefromlast = Exists(para->bddmgr, para->v, reachablefromlast);
          reachablefromlast =
            reachablefromlast.SwapVariables(*para->v, *para->pv);
    
          BDD abdd = reachablefromlast * last;
          if (abdd == para->bddmgr->bddZero()) {
            return false;
          }
    
          Q = abdd * T;   // if this is not false, we found a loop
          if (Q == para->bddmgr->bddZero()) {
            BDD curstate = pick_combination_minterm(abdd, variables, para);
      
            tmpresult.push_back(new BDD(curstate));
      
            T = T + curstate;
          } else {
            break;
          }
        }
    
        for (unsigned int acounter = 0; acounter < tmpresult.size(); acounter++) {
          if ((Q * (*tmpresult[acounter])) != para->bddmgr->bddZero()) {
            loopstart = acounter;
            break;
          }
        } 
      } else {
        //cout << "start from" << endl;
        //print_state(*state, *(para->v));
        vector< vector < BDD* >* > Qh;
        BDD f = ((modal_formula *) obj[0])->check_formula(para, variables, agents);
        BDD last = check_EG_fair(f, para);
				
				for(unsigned int j=0; j<is_fairness->size(); j++) {
					BDD hf = (*is_fairness)[j]->get_bdd_representation();
					vector< BDD* >* qh = new vector< BDD* >();
					check_EU_Qh(last, last * hf, para, qh);
					Qh.push_back(qh);
				}


        /*cout << "Number of qh = " << Qh.size() << endl;
				for(unsigned int i=0; i<Qh.size(); i++) {
          cout << "qh[" << i << "] = " << Qh[i]->size() << endl;
          for(unsigned int j=0; j<Qh[i]->size(); j++) {
						cout << "Qh[" << i << "][" << j << "]:";
						(*Qh[i])[j]->print(2, 2);
						}
				}*/
  
        unsigned int count;
        BDD predecessors;
        bool restart;
        bool *processed;
        BDD loopbegin;
				unsigned int lp1, lp2;
			EG_start: // -----------------------------------------------------------------------
        do {
          processed = new bool[is_fairness->size()];
          for(unsigned int k=0; k<is_fairness->size(); k++)
            processed[k] = false;
          count = 0;
          restart = false;
          while(count < is_fairness->size()) {
            BDD reachablefromlast = compute_successors(tmpresult.back(), para->bddmgr, para->vRT, para->a, para->v, para->pv);
            //cout << "  reachablefromlast:";
            //reachablefromlast.print(2, 2);
            BDD successors = reachablefromlast * last;
            //cout << "  successors:";
            //successors.print(2, 2);
            unsigned int i=0, j=0; 
            BDD t;
            while(true) {
              for(j=0; j<is_fairness->size(); j++) {
                if(!processed[j]) {
                  vector< BDD* >* qh = Qh[j];
                  if(i >= qh->size()) {
                    restart = true;
                    break;
                  }
                  BDD tmp = successors * (*(*qh)[i]);
                  if(count > 0)
                    tmp = tmp * predecessors;
                  if(tmp != para->bddmgr->bddZero()) {
                    processed[j] = true;
										t = pick_combination_minterm(tmp, variables, para);
										if(count == 0) {
											//predecessors = check_EU(last, t, para);
											//loopbegin = t;
											loopstart = tmpresult.size();
										}

                    //print_state(t, *(para->v));
                    count++;
        
                    //cout << "find a fair state: i = " << i << ", j = " << j << ", count = " << count << endl;

                    break;
                  }
                }
              }
              if(j<is_fairness->size())
                break;
              i++;
            }
            if(!restart) {
              // choose fairness constraint j with Q_i^h
              //cout << "  compute path to fairness " << j << endl;
              tmpresult.push_back(new BDD(t));
              //cout << "  add a state to tmpresult: size = " << tmpresult.size() << endl;
              vector< BDD* >* qh = Qh[j];
              while(i > 0) {
                BDD next = compute_successors(tmpresult.back(), para->bddmgr, para->vRT, para->a, para->v, para->pv);
                next = next * last;
                next = next * *((*qh)[i-1]);
								if(next == para->bddmgr->bddZero()) {
									cout << "find a deadlock 0: i = " << i << endl;
									exit(0);
								}
                t = pick_combination_minterm(next, variables, para);
                tmpresult.push_back(new BDD(t));
                i--;
              } 
							if(count == 1) {
								// compute the predecessor for closing cycle
								lp1 = 0;
								lp2 = tmpresult.size()-1;
								loopbegin = para->bddmgr->bddZero();
								for(unsigned int k=0; k<tmpresult.size(); k++) {
									loopbegin += *(tmpresult[k]);
								}
								predecessors = check_EU(last, loopbegin, para);
							}
            } else {
              //cout << "cannot find a fair loop. restart the computation." << endl;
              break;
            }    
          }
        } while(restart == true);

        // compute loopstart: find a path from the last state in tempresult to loopbegin
        //cout << "compute loopstart" << endl;
        //if(loopbegin != *tmpresult.back()) {
				if(loopbegin * *tmpresult.back() == para->bddmgr->bddZero()) {
					//cout << "loopbegin != *tmpresult.back()" << endl;
          vector< BDD > S;
          BDD sum = loopbegin;
          BDD Y = loopbegin, X = *tmpresult.back();
          while(Y * X == para->bddmgr->bddZero()) {
            Y = predecessors * check_EX(Y, para);
            Y -= sum;
            sum += Y;
            S.push_back(Y);
						if(Y == para->bddmgr->bddZero()) {
							cout << "Find a deadlock in counterexample generation for EG under fairness. Please report it to MCMAS developers." << endl;
							exit(0);
						}
          }
          S.pop_back();

          while(S.size() > 0) {
            X = compute_successors(&X, para->bddmgr, para->vRT, para->a, para->v, para->pv);
            X = X * S.back();
            S.pop_back();
            X = pick_combination_minterm(X, variables, para);
            tmpresult.push_back(new BDD(X));
          }
					Y = compute_successors(tmpresult.back(), para->bddmgr, para->vRT, para->a, para->v, para->pv); 
					Y *= loopbegin;
					Y = pick_combination_minterm(Y, variables, para);
					for(unsigned int k=lp1; k<=lp2; k++) {
						if(*tmpresult[k] == Y) {
							loopstart = k;
							break;
						}
					}
					//} else if(loopstart == tmpresult.size()-1) { // need to find a selfloop or a circular path 
				} else {
					for(unsigned int k=lp1; k<=lp2; k++) {
						if(*tmpresult[k] == *tmpresult.back()) {
							loopstart = k;
							//cout << "loopstart = " << loopstart << ", tmpresult.size = " << tmpresult.size() << endl;
							break;
						}
					}
					if(loopstart == tmpresult.size()-1) {
						// the last state is a part of the prefix of the lasso
						loopbegin = *tmpresult.back();
						vector< BDD > S;
						BDD sum;
						BDD Y = loopbegin;
						predecessors = check_EU(last, Y, para);
						Y = predecessors * check_EX(Y, para);
						if(Y * loopbegin == para->bddmgr->bddZero()) { // no selfloop
							//cout << "Y * loopbegin == para->bddmgr->bddZero()" << endl;
							sum = Y;
							S.push_back(Y);
							do {
								Y = predecessors * check_EX(Y, para);
								Y -= sum;
								sum += Y;
								S.push_back(Y);
								if(Y == para->bddmgr->bddZero()) {
									//cout << "find a dead end. restart" << endl;
									S.clear();
									goto EG_start;
								}
							} while(Y * loopbegin == para->bddmgr->bddZero());
							S.pop_back();
							Y = loopbegin;
							while(S.size() > 0) {
								Y = compute_successors(&Y, para->bddmgr, para->vRT, para->a, para->v, para->pv);
								Y = Y * S.back();
								S.pop_back();
								Y = pick_combination_minterm(Y, variables, para);
								tmpresult.push_back(new BDD(Y));
							}
						}
					} else {
						BDD *ptr = tmpresult.back();
						tmpresult.pop_back();
						if(loopstart >= tmpresult.size())
							loopstart--;
						delete ptr;
					}
				}
        for(unsigned int i=0; i<Qh.size(); i++) {
          for(unsigned int j=0; j<Qh[i]->size(); j++) {
            delete (*Qh[i])[j];
          }
          delete Qh[i];
        }  
      }

      //cout << "generate transitions ..." << endl;
      //cout << "number states = " << tmpresult.size() << ", loopstart = " << loopstart << endl;
      

      unsigned int numberofstates = (unsigned int) tmpresult.size() - 1;  // (the last one is NOT repeated)
      if (loopstart == -1) {
        if (options["quiet"] == 0) {
          cout << "Witness generation for EG:" << endl;
          cout << "THERE IS A PROBLEM HERE, PLEASE REPORT THIS ERROR" << endl;
        }
        return false;
      }
      // building transitions
      // first go to the last loop state
      int position1 = scount;
      for (unsigned int acounter = 0; acounter < numberofstates; acounter++) {
        BDD from = *tmpresult[acounter];
        BDD to = tmpresult[acounter + 1]->SwapVariables(*para->v, *para->pv);
        BDD actions = timesTrans(&from, &to, para->vRT);
        actions = Exists(para->bddmgr, para->v, actions);
        actions = Exists(para->bddmgr, para->pv, actions);
        BDD action = actions.PickOneMinterm(*para->a);
        if (acounter == 0) {
          desctr.push_back(new transition(&from, index, &to, ++scount, &action));
          if (index >= idbdd->size())
            idbdd->insert(pair < int, BDD * >(index, (tmpresult[acounter])));
          desc.push_back(index);
        } else {
          desctr.
            push_back(new transition(&from, scount, &to, scount + 1, &action));
          idbdd->insert(pair < int, BDD * >(scount, (tmpresult[acounter])));
          desc.push_back(scount++);
        }
      }
      
      // Now add the loop back
      
      BDD from = *tmpresult[numberofstates];
      BDD to = tmpresult[loopstart]->SwapVariables(*para->v, *para->pv);
      BDD actions = timesTrans(&from, &to, para->vRT);
      actions = Exists(para->bddmgr, para->v, actions);
      actions = Exists(para->bddmgr, para->pv, actions);
      BDD action = actions.PickOneMinterm(*para->a);
      
      if (loopstart == 0) {
        if (numberofstates == 0) {
          desctr.push_back(new transition(&from, index, &to, index, &action));
          if (index >= idbdd->size())
            idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
    
          desc.push_back(index);
        } else {
          desctr.push_back(new transition(&from, scount, &to, index, &action));
          idbdd->insert(pair < int, BDD * >(scount, (tmpresult[numberofstates])));
    
          desc.push_back(scount);
        }
        desc.push_back(index);
      } else {
        int loopposition = position1 + loopstart;
        desctr.push_back(new transition(&from, scount, &to, loopposition, &action));    
        idbdd->insert(pair < int, BDD * >(scount, (tmpresult[numberofstates])));
        desc.push_back(scount);
        desc.push_back(loopposition);
      }
      countex->push_back(new vector< int >(desc));
      
      cextr->push_back(new vector< transition * >(desctr));
      
      // Print witness for all states in the path      
      for (vector< BDD * >::iterator tmpri = tmpresult.begin();
           tmpri != tmpresult.end(); tmpri++) {
        if ((*(*tmpri)) <= ((modal_formula *) obj[0])->check_formula(para, variables, agents)) {
          if (tmpri == tmpresult.begin())
            ((modal_formula *) obj[0])->build_cex(
                *tmpri, index, para, countex, idbdd, cextr, variables, agents,
                strategies);
          else
            ((modal_formula *) obj[0])->build_cex(
                *tmpri, ++position1, para, countex, idbdd, cextr, variables,
                agents, strategies);
        }
      }
      
      return true;
    }
  case 13:      // EX
    {
      tmpresult.push_back(new BDD(*state));

      //vector< BDD * >S; // a vector to store the stages of the fixpoint computation

      BDD p = ((modal_formula *) obj[0])->check_formula(para, variables, agents);

      p = p.SwapVariables(*para->pv, *para->v); // The set of "next" states where p is true.

      BDD aset1 = timesRT(state, para->bddmgr, para->vRT, para->a);

      aset1 = aset1 * p;  // the set above where, additionally, p holds
      if (aset1 == para->bddmgr->bddZero())
        return false;

      aset1 = aset1.SwapVariables(*para->v, *para->pv); // swap back

      BDD curstate = pick_combination_minterm(aset1, variables, para);
      tmpresult.push_back(new BDD(curstate));

      BDD from = *tmpresult[0];
      BDD to = tmpresult[1]->SwapVariables(*para->v, *para->pv);
      BDD actions = timesTrans(&from, &to, para->vRT);
      actions = Exists(para->bddmgr, para->v, actions);
      actions = Exists(para->bddmgr, para->pv, actions);
      BDD action = actions.PickOneMinterm(*para->a);
      desctr.push_back(new transition(&from, index, &to, scount + 1, &action));
      if (index >= idbdd->size())
        idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
      desc.push_back(index);
      desc.push_back(++scount);
      countex->push_back(new vector< int >(desc));
      idbdd->insert(pair < int, BDD * >(scount, (tmpresult[1])));
      cextr->push_back(new vector< transition * >(desctr));

      return ((modal_formula *) obj[0])->build_cex(
          tmpresult[1], scount, para, countex, idbdd, cextr, variables, agents,
          strategies);
    }
  case 15:      // EF
    {
      vector< BDD > S; // a vector to store the stages of the fixpoint computation
      BDD p = ((modal_formula *) obj[0])->check_formula(para, variables, agents);
      BDD tmp = para->bddmgr->bddOne();
      BDD q = p;
      BDD curstate = para->bddmgr->bddOne();  // the current state

      int n = 0;

      do {
        S.push_back(q*(*para->reach));
        tmp = q;
        q = p + check_EX(tmp, para);
        n++;
      } while (q != tmp);

      int j = 0;

      while (!(curstate <= S[0])) {
        BDD aset1;
        if (j == 0) {
          aset1 = (*state);
        } else {
          aset1 =
            Exists(para->bddmgr, para->v,
                   timesRT(&curstate, para->bddmgr, para->vRT, para->a));
          aset1 = aset1.SwapVariables(*para->v, *para->pv);
        }
        BDD aset2 = aset1 * S[n - j - 1];

        if (aset2 == para->bddmgr->bddZero()) {
          return false;
        }
        curstate = pick_combination_minterm(aset2, variables, para);
        tmpresult.push_back(new BDD(curstate));

        j++;

      }

      // building transitions
      for (int i = 0; i < (int) tmpresult.size() - 1; i++) {
        BDD from = *tmpresult[i];
        BDD to = tmpresult[i + 1]->SwapVariables(*para->v, *para->pv);
        BDD actions = timesTrans(&from, &to, para->vRT);
        actions = Exists(para->bddmgr, para->v, actions);
        actions = Exists(para->bddmgr, para->pv, actions);
        BDD action = actions.PickOneMinterm(*para->a);
        if (i == 0) {
          desctr.
            push_back(new transition(&from, index, &to, ++scount, &action));
          if (index >= idbdd->size())
            idbdd->insert(pair < int, BDD * >(index, (tmpresult[i])));
          desc.push_back(index);
        } else {
          desctr.
            push_back(new transition(&from, scount, &to, scount + 1, &action));
          idbdd->insert(pair < int, BDD * >(scount, (tmpresult[i])));
          desc.push_back(scount++);
        }
      }
      if (tmpresult.size() == 1) {
        if (index >= idbdd->size())
          idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
      } else {
        desc.push_back(scount);
        idbdd->insert(pair < int,
                      BDD * >(scount, (tmpresult[tmpresult.size() - 1])));
        countex->push_back(new vector< int >(desc));
        cextr->push_back(new vector< transition * >(desctr));
      }

      return ((modal_formula *) obj[0])->
        build_cex(tmpresult[tmpresult.size() - 1],
                  (tmpresult.size() == 1 ? index : scount), para, countex,
                  idbdd, cextr, variables, agents, strategies);
    }
  case 17:      // EU
    {
      vector< BDD >S; // a vector to store the stages of the fixpoint computation

      BDD p = ((modal_formula *) obj[0])->check_formula(para, variables, agents);
      BDD q = ((modal_formula *) obj[1])->check_formula(para, variables, agents);

      BDD tmp1 = para->bddmgr->bddOne();
      BDD curstate = para->bddmgr->bddOne();  // the current state

      int n = 0;

      BDD tmp2 = q;
      while (tmp1 != tmp2) {
        tmp1 = tmp2;
        tmp2 = tmp2 + (p * check_EX(tmp2, para));
        S.push_back(tmp1);
        n++;
      }

      int j = 0;

      while (!(curstate <= S[0])) {
        BDD aset1;
        if (j == 0) {
          aset1 = (*state);
        } else {
          aset1 =
            Exists(para->bddmgr, para->v,
                   timesRT(&curstate, para->bddmgr, para->vRT, para->a));
          aset1 = aset1.SwapVariables(*para->v, *para->pv);
        }
        BDD aset2 = aset1 * S[n - j - 1];

        if (aset2 == para->bddmgr->bddZero()) {
          return false;
        }
        curstate = pick_combination_minterm(aset2, variables, para);

        /* print state */
        tmpresult.push_back(new BDD(curstate));

        j++;

      }

      int position1 = scount;

      // transitions
      for (int i = 0; i < (int) tmpresult.size() - 1; i++) {
        BDD from = *tmpresult[i];
        BDD to = tmpresult[i + 1]->SwapVariables(*para->v, *para->pv);
        BDD actions = timesTrans(&from, &to, para->vRT);
        actions = Exists(para->bddmgr, para->v, actions);
        actions = Exists(para->bddmgr, para->pv, actions);
        BDD action = actions.PickOneMinterm(*para->a);
        if (i == 0) {
          desctr.
            push_back(new transition(&from, index, &to, ++scount, &action));
          if (index >= idbdd->size())
            idbdd->insert(pair < int, BDD * >(index, (tmpresult[i])));
          desc.push_back(index);
        } else {
          desctr.
            push_back(new transition(&from, scount, &to, scount + 1, &action));
          idbdd->insert(pair < int, BDD * >(scount, (tmpresult[i])));
          desc.push_back(scount++);
        }
      }
      if (tmpresult.size() == 1) {
        if (index >= idbdd->size())
          idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
      } else {
        desc.push_back(scount);
        idbdd->insert(pair < int,
                      BDD * >(scount, (tmpresult[tmpresult.size() - 1])));
        countex->push_back(new vector< int >(desc));

        cextr->push_back(new vector< transition * >(desctr));
      }

      for (unsigned int i = 0; i < tmpresult.size() - 1; i++) {
        if ((*tmpresult[i]) <=
            ((modal_formula *) obj[0])->check_formula(para, variables, agents)) {
          if (i == 0)
            ((modal_formula *) obj[0])->build_cex(
                tmpresult[i], index, para, countex, idbdd, cextr, variables,
                agents, strategies);
          else
            ((modal_formula *) obj[0])->build_cex(
                tmpresult[i], ++position1, para, countex, idbdd, cextr,
                variables, agents, strategies);
        }
      }
      return ((modal_formula *) obj[1])->
        build_cex(tmpresult[tmpresult.size() - 1],
                  (tmpresult.size() == 1 ? index : scount), para, countex,
                  idbdd, cextr, variables, agents, strategies);
    }

  case 45:{     // ATLX witness
    BDD p = ((modal_formula *) obj[1])->check_formula(para, variables, agents);

    tmpresult.push_back(new BDD(*state));

    // get all successor states
    BDD successors = *state;
    for (unsigned int i = 0; i < agents->size(); i++)
      successors = successors * (*para->vRT)[i];

    // get successors that do not satisfy operator[1], i.e., \phi in <name>X \phi
    p = p.SwapVariables(*para->v, *para->pv);
    BDD bad_succ = successors - p;
		// remove unfair successor states
		if (!is_fairness->empty()) {
			BDD freach = para->reach->SwapVariables(*para->v, *para->pv);
			bad_succ = bad_succ * freach;
		}

    // get actions that cannot force the system move the successors that satisfy \phi
    BDD bad_actions = bad_succ.ExistAbstract(actagtout);
    bad_actions = Exists(para->bddmgr, para->pv, bad_actions);
    bad_actions = Exists(para->bddmgr, para->v, bad_actions);

    // get successors that satisfy \phi
    BDD good_succ = successors * p;

    // remove successors that are reached by bad actions
    good_succ = good_succ - (good_succ * bad_actions);
    if (good_succ == para->bddmgr->bddZero())
      return false;
    BDD good_succ_tran = good_succ;
    good_succ = Exists(para->bddmgr, para->v, good_succ);

    // get one successor that reached by good actions
    BDD nextstate = Exists(para->bddmgr, para->a, good_succ);

    //options["fullatl"]=1;

    if (options["fullatl"] == 0) {
      nextstate = pick_next_combination_minterm(nextstate, variables, para);

      // get the set of actions
      BDD action =
        Exists(para->bddmgr, para->pv,
               good_succ * nextstate).PickOneMinterm(*para->a);

      // put the next state in the stack
      tmpresult.
        push_back(new BDD(nextstate.SwapVariables(*para->v, *para->pv)));

      BDD from = *tmpresult[0];
      BDD to = tmpresult[1]->SwapVariables(*para->v, *para->pv);
      desctr.
        push_back(new transition(&from, index, &to, scount + 1, &action));
      if (index >= idbdd->size())
        idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
      desc.push_back(index);
      desc.push_back(++scount);
      countex->push_back(new vector< int >(desc));
      idbdd->insert(pair < int, BDD * >(scount, (tmpresult[1])));
      cextr->push_back(new vector< transition * >(desctr));
      return ((modal_formula *) obj[1])->build_cex(
          tmpresult[1], scount, para, countex, idbdd, cextr, variables, agents,
          strategies);
    } else {
      map< string, int >statekeys;

      if (index >= idbdd->size())
        idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
      string strkey = state_to_str(*tmpresult[0], *para->v);
      statekeys[strkey] = index;

      desc.push_back(index);

      if (options["fullatl"] >= 3) {
        BDD pvstate = state->SwapVariables(*para->v, *para->pv);
        BDD YY = good_succ_tran;
        if (options["atlnewstate"] == 1) {
          BDD tmpYY = good_succ_tran - pvstate;
          if (tmpYY != para->bddmgr->bddZero())
            YY = tmpYY;
        }
        BDD tmpaction = YY.PickOneMinterm(*para->a);
        tmpaction = Exists(para->bddmgr, para->v, tmpaction);
        tmpaction = Exists(para->bddmgr, para->pv, tmpaction);
        tmpaction = tmpaction.ExistAbstract(actagtout);
        good_succ_tran = good_succ_tran * tmpaction;
        good_succ = Exists(para->bddmgr, para->v, good_succ_tran);
        nextstate = Exists(para->bddmgr, para->a, good_succ);
      }

      do {
        BDD successor = pick_next_combination_minterm(nextstate, variables, para);
        nextstate = nextstate - successor;

        // put the next state in the stack
        tmpresult.
          push_back(new BDD(successor.SwapVariables(*para->v, *para->pv)));

        // get the set of actions
        BDD action = Exists(para->bddmgr, para->pv, good_succ * successor);

        do {
          BDD oneaction = action.PickOneMinterm(*para->a);
          action = action - oneaction;
          BDD from = *tmpresult[0];
          BDD to = tmpresult[tmpresult.size() - 1]->SwapVariables(*para->v, *para->pv);
          strkey = state_to_str(*tmpresult[tmpresult.size() - 1], *para->v);
          map< string, int >::iterator gi = statekeys.find(strkey);
          if (gi == statekeys.end()) {
            idbdd->insert(pair < int, BDD * >(++scount, (tmpresult[tmpresult.size() - 1])));
            statekeys[strkey] = scount;
            desctr.push_back(new transition(&from, index, &to, scount, &oneaction));
            desc.push_back(scount);
          } else {
            desctr.push_back(new transition(&from, index, &to, gi->second, &oneaction));
            desc.push_back(gi->second);
          }
          countex->push_back(new vector< int >(desc));

          cextr->push_back(new vector< transition * >(desctr));
          desc.pop_back();
          desctr.pop_back();
        } while (action != para->bddmgr->bddZero());
      } while (nextstate != para->bddmgr->bddZero());
      if (options["fullatl"] % 2 == 0) {
        for (unsigned int i = 1; i < tmpresult.size(); i++) {
          string strkey = state_to_str(*tmpresult[i], *para->v);
          map< string, int >::iterator gi = statekeys.find(strkey);
          ((modal_formula *) obj[1])->build_cex(
              tmpresult[i], /* ++position1 */ gi->second, para, countex, idbdd,
              cextr, variables, agents, strategies);
        }
      }

      return true;
    }
  }

  case 46:{     // ATL operator F
    vector< BDD >S; // a vector to store the stages of the fixpoint computation
    BDD p = ((modal_formula *) obj[1])->check_formula(para, variables, agents);
    BDD tmp = para->bddmgr->bddOne();
    BDD q = p;
    BDD curstate = *state;  // the current state
    vector< BDD >tmp_actions;
		BDD freach = para->bddmgr->bddOne();
		if (!is_fairness->empty()) {
			freach = para->reach->SwapVariables(*para->v, *para->pv);
		}

    if (options["fullatl"] > 0) {
      BDD last = check_formula(para, variables, agents); // the last state of fixpoint computation
      tmpresult.push_back(new BDD(*state));
      map< string, int >statekeys;
      if (index >= idbdd->size())
        idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
      string strkey = state_to_str(*tmpresult[0], *para->v);

      statekeys[strkey] = index;
      if (*tmpresult[0] * p == para->bddmgr->bddZero()) {
        BDD atltree = *state;
        if (atltree * last == para->bddmgr->bddZero())
          return false;
        BDD Y = atltree;
        BDD lastprime = last.SwapVariables(*para->v, *para->pv);
        //int depth = 0;

        BDD paststate;
        if (options["atlnewstate"] == 1)
          paststate = para->bddmgr->bddZero();  // store states that have been visited

        while (Y != para->bddmgr->bddZero()) {
          // Compute all successors
          for (unsigned int i = 0; i < agents->size(); i++)
            Y = Y * (*para->vRT)[i];
					// remove unfair successor states
					if (!is_fairness->empty()) {
						Y = Y * freach;
					}
          // Compute successors that do not satisfy the ATLF formula
          BDD badstates = Y * (!lastprime);

          // Remove successor states; keep actions and source states only
          badstates = Exists(para->bddmgr, para->pv, badstates);
          badstates = badstates * (*para->reach);

          // Pick up bad actions executed by the opponents
          badstates = badstates.ExistAbstract(actagtout);

          // Pick up successors that either do not satisfy the ATLG formula or cannot reached by any strategy
          Y = Y - badstates;

          // keep only one strategy
          if (options["fullatl"] >= 3) {
            BDD allsources = Exists(para->bddmgr, para->a, Y);
            allsources = Exists(para->bddmgr, para->pv, allsources);
            BDD missed = allsources;
            BDD YY = para->bddmgr->bddZero();
            while (missed != para->bddmgr->bddZero()) {
              BDD source = pick_combination_minterm(missed, variables, para);
              BDD trans = source * Y;
              if (options["atlnewstate"] == 1) {
                BDD sourcetarget =
                  source.SwapVariables(*para->v, *para->pv);
                paststate += sourcetarget;
                BDD newtrans = trans - paststate;
                if (newtrans != para->bddmgr->bddZero())
                  trans = newtrans;
              }
              BDD strategy = trans.PickOneMinterm(*para->a);
              strategy = strategy.ExistAbstract(actagtout);
              strategy = Y * strategy;
              YY += strategy;
              BDD heads = Exists(para->bddmgr, para->a, strategy);
              heads = Exists(para->bddmgr, para->pv, heads);
              missed = missed - heads;
            }
            Y = YY;
          }

          BDD Y1 = Exists(para->bddmgr, para->v, Y);
          Y1 = Exists(para->bddmgr, para->a, Y1);

          // Now we need to store the actions
          BDD nextstate = Y1;
          BDD good_succ = Y;
          do {
            BDD successor = pick_next_combination_minterm(nextstate, variables, para);
            nextstate = nextstate - successor;
            BDD to = successor.SwapVariables(*para->v, *para->pv);
            strkey = state_to_str(to, *para->v);
            map< string, int >::iterator gi = statekeys.find(strkey);
            int to_index;
            if (gi == statekeys.end()) {
              tmpresult.push_back(new BDD(to));
              idbdd->insert(pair < int, BDD * >(++scount, tmpresult.back()));
              statekeys[strkey] = scount;
              // put the next state in the stack
              to_index = scount;
            } else
              to_index = gi->second;

            // compute all predecessors that have the selected successor
            BDD predecessors = good_succ * successor;
            do {
              BDD predecessor = pick_combination_minterm(predecessors, variables, para);
              predecessors = predecessors - predecessor;
              BDD from = predecessor;
              strkey = state_to_str(predecessor, *para->v);
              gi = statekeys.find(strkey);
              if (gi == statekeys.end()) {
                cout << "  cannot find state: " << strkey << endl;
                exit(0);
              }
              int from_index = gi->second;
              desc.push_back(from_index);

              // get the set of actions
              BDD action = Exists(para->bddmgr, para->pv, good_succ * successor * predecessor);
              action = Exists(para->bddmgr, para->v, action);
              do {
                BDD oneaction = action.PickOneMinterm(*para->a);
                action = action - oneaction;

                desctr.push_back(new transition(&from, from_index, &to, to_index, &oneaction));
                cextr->push_back(new vector< transition * >(desctr));
                desctr.pop_back();
              } while (action != para->bddmgr->bddZero());
              desc.push_back(to_index);
              countex->push_back(new vector< int >(desc));
              desc.pop_back();
              desc.pop_back();
            } while (predecessors != para->bddmgr->bddZero());
          } while (nextstate != para->bddmgr->bddZero());

          // move the frontier to the good successors
          Y = Y1;
          Y = Y.SwapVariables(*para->v, *para->pv);
          Y = Y - atltree;
          atltree += Y;
          Y -= p;
        }
      }
      // Generate tree for every state in the atl tree
      if (options["fullatl"] % 2 == 0) {
        for (vector< BDD * >::iterator tmpri = tmpresult.begin();
             tmpri != tmpresult.end(); tmpri++) {
          string strkey = state_to_str(*(*tmpri), *para->v);
          map< string, int >::iterator gi = statekeys.find(strkey);
          if (**tmpri * p != para->bddmgr->bddZero())
            ((modal_formula *) obj[1])->build_cex(
                *tmpri, gi->second, para, countex, idbdd, cextr, variables,
                agents, strategies);
        }
      }
      return true;
    } else {
      int n = 0, j = 0;
      S.push_back(q);
      while (*state * q == para->bddmgr->bddZero()) {
        q = check_ATLX(q, name, para);
        S.push_back(q);
        n++;
      }

      while (j <= n) {
        BDD aset1;
        BDD good_succ = para->bddmgr->bddZero();
        if (j == 0) {
          aset1 = (*state);
        } else {
          tmp = curstate;
          for (unsigned int i = 0; i < agents->size(); i++)
            tmp = tmp * (*para->vRT)[i];
          BDD pq = S[n - j].SwapVariables(*para->v, *para->pv);
          BDD bad_succ = tmp - pq;
          BDD bad_actions = bad_succ.ExistAbstract(actagtout);
          bad_actions = Exists(para->bddmgr, para->pv, bad_actions);
          bad_actions = Exists(para->bddmgr, para->v, bad_actions);
          good_succ = tmp * pq;
          good_succ = good_succ - (good_succ * bad_actions);
          good_succ =
            Exists(para->bddmgr, para->v, good_succ).SwapVariables(*para->v,
                                                                   *para->
                                                                   pv);
          aset1 = Exists(para->bddmgr, para->a, good_succ);
        }
        if (aset1 == para->bddmgr->bddZero())
          return false;
        curstate = pick_combination_minterm(aset1, variables, para);
        tmpresult.push_back(new BDD(curstate));
        if (j > 0) {
          BDD action =
            Exists(para->bddmgr, para->v,
                   good_succ * curstate).PickOneMinterm(*para->a);
          tmp_actions.push_back(action);
        }
        j++;
      }

      // building transitions
      for (int i = 0; i < (int) tmpresult.size() - 1; i++) {
        BDD from = *tmpresult[i];
        BDD to = tmpresult[i + 1]->SwapVariables(*para->v, *para->pv);
        BDD action = tmp_actions[i];
        if (i == 0) {
          desctr.push_back(new transition(&from, index, &to, ++scount, &action));
          if (index >= idbdd->size())
            idbdd->insert(pair < int, BDD * >(index, (tmpresult[i])));
          desc.push_back(index);
        } else {
          desctr.push_back(new transition(&from, scount, &to, scount + 1, &action));
          idbdd->insert(pair < int, BDD * >(scount, (tmpresult[i])));
          desc.push_back(scount++);
        }
      }

      if (tmpresult.size() == 1) {
        if (index >= idbdd->size())
          idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
      } else {
        desc.push_back(scount);
        idbdd->insert(pair < int, BDD * >(scount, (tmpresult[tmpresult.size() - 1])));
        countex->push_back(new vector< int >(desc));
        cextr->push_back(new vector< transition * >(desctr));
      }

      return ((modal_formula *) obj[1])->
        build_cex(tmpresult[tmpresult.size() - 1],
                  (tmpresult.size() == 1 ? index : scount), para, countex,
                  idbdd, cextr, variables, agents, strategies);
    }
  }

  case 47:{     // ATL operator G
    BDD p = ((modal_formula *) obj[1])->check_formula(para, variables, agents);
    p = p.SwapVariables(*para->v, *para->pv);
    BDD last = check_formula(para, variables, agents); // the last state of fixpoint computation
    tmpresult.push_back(new BDD(*state));
    vector< BDD >tmp_actions;
		BDD freach = para->bddmgr->bddOne();
		if (!is_fairness->empty()) {
			freach = para->reach->SwapVariables(*para->v, *para->pv);
		}				

    if (options["fullatl"] > 0) {
      map< string, int >statekeys;
      if (index >= idbdd->size())
        idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
      string strkey = state_to_str(*tmpresult[0], *para->v);

      statekeys[strkey] = index;
      BDD atltree = *state;
      if (atltree * last == para->bddmgr->bddZero())
        return false;
      BDD Y = atltree;
      BDD lastprime = last.SwapVariables(*para->v, *para->pv);
      BDD paststate;
      if (options["atlnewstate"] == 1)
        paststate = para->bddmgr->bddZero();  // store states that have been visited
      while (Y != para->bddmgr->bddZero()) {
        // Compute all successors
        for (unsigned int i = 0; i < agents->size(); i++)
          Y = Y * (*para->vRT)[i];
				// remove unfair successor states
				if (!is_fairness->empty()) {
					Y = Y * freach;
				}
         // Compute successors that do not satisfy the ATLG formula
        BDD badstates = Y * (!lastprime);

        // Remove successor states; keep actions and source states only
        badstates = Exists(para->bddmgr, para->pv, badstates);
        badstates = badstates * (*para->reach);

        // Pick up bad actions executed by the opponents
        badstates = badstates.ExistAbstract(actagtout);

        // Pick up successors that either do not satisfy the ATLG formula or cannot reached by any strategy
        Y = Y - badstates;

        // keep only one strategy
        if (options["fullatl"] >= 3) {
          BDD allsources = Exists(para->bddmgr, para->a, Y);
          allsources = Exists(para->bddmgr, para->pv, allsources);
          BDD missed = allsources;
          BDD YY = para->bddmgr->bddZero();
          while (missed != para->bddmgr->bddZero()) {
            BDD source = pick_combination_minterm(missed, variables, para);
            BDD trans = source * Y;
            if (options["atlnewstate"] == 1) {
              BDD sourcetarget = source.SwapVariables(*para->v, *para->pv);
              paststate += sourcetarget;
              BDD newtrans = trans - paststate;
              if (newtrans != para->bddmgr->bddZero())
                trans = newtrans;
            }
            BDD strategy = trans.PickOneMinterm(*para->a);
            strategy = strategy.ExistAbstract(actagtout);
            strategy = Y * strategy;
            YY += strategy;
            BDD heads = Exists(para->bddmgr, para->a, strategy);
            heads = Exists(para->bddmgr, para->pv, heads);
            missed = missed - heads;
          }
          Y = YY;
        }

        BDD Y1 = Exists(para->bddmgr, para->v, Y);
        Y1 = Exists(para->bddmgr, para->a, Y1);

        // Now we need to store the actions
        BDD nextstate = Y1;
        BDD good_succ = Y;
        do {
          BDD successor = pick_next_combination_minterm(nextstate, variables, para);
          nextstate = nextstate - successor;
          BDD to = successor.SwapVariables(*para->v, *para->pv);
          strkey = state_to_str(to, *para->v);
          map< string, int >::iterator gi = statekeys.find(strkey);
          int to_index;
          if (gi == statekeys.end()) {
            tmpresult.push_back(new BDD(to));
            idbdd->insert(pair < int, BDD * >(++scount, tmpresult.back()));
            statekeys[strkey] = scount;
            // put the next state in the stack
            to_index = scount;
          } else
            to_index = gi->second;

          // compute all predecessors that have the selected successor
          BDD predecessors = good_succ * successor;
          do {
            BDD predecessor = pick_combination_minterm(predecessors, variables, para);
            predecessors = predecessors - predecessor;
            BDD from = predecessor;
            strkey = state_to_str(predecessor, *para->v);
            gi = statekeys.find(strkey);
            if (gi == statekeys.end()) {
              cout << "  cannot find state: " << strkey << endl;
              exit(0);
            }
            int from_index = gi->second;
            desc.push_back(from_index);

            // get the set of actions
            BDD action = Exists(para->bddmgr, para->pv, good_succ * successor * predecessor);
            action = Exists(para->bddmgr, para->v, action);
            do {
              BDD oneaction = action.PickOneMinterm(*para->a);
              action = action - oneaction;

              desctr.push_back(new transition(&from, from_index, &to, to_index, &oneaction));
              cextr->push_back(new vector< transition * >(desctr));
              desctr.pop_back();
            } while (action != para->bddmgr->bddZero());
            desc.push_back(to_index);
            countex->push_back(new vector< int >(desc));
            desc.pop_back();
            desc.pop_back();
          } while (predecessors != para->bddmgr->bddZero());
        } while (nextstate != para->bddmgr->bddZero());

        // move the frontier to the good successors
        Y = Y1;
        Y = Y.SwapVariables(*para->v, *para->pv);
        Y = Y - atltree;
        atltree += Y;
      }
      // Generate tree for every state in the atl tree
      if (options["fullatl"] % 2 == 0) {
        for (vector< BDD * >::iterator tmpri = tmpresult.begin();
             tmpri != tmpresult.end(); tmpri++) {
          string strkey = state_to_str(*(*tmpri), *para->v);
          map< string, int >::iterator gi = statekeys.find(strkey);
          ((modal_formula *) obj[1])->build_cex(
              *tmpri, gi->second, para, countex, idbdd, cextr, variables,
              agents, strategies);
        }
      }
      return true;
    } else {
      vector< BDD >S; // a vector to store the stages of the computation
      int j = 0;
      BDD Q = para->bddmgr->bddZero();
      BDD T = *state;
      while (Q == para->bddmgr->bddZero()) {
        j++;
        //BDD reachablefromlast = timesRT(tmpresult[j-1]);
        BDD reachablefromlast = *tmpresult[j - 1];
        for (unsigned int i = 0; i < agents->size(); i++)
          reachablefromlast = reachablefromlast * (*para->vRT)[i];
        // copied from ATLX case
        BDD bad_succ = reachablefromlast - p;
        BDD bad_actions = bad_succ.ExistAbstract(actagtout);
        bad_actions = Exists(para->bddmgr, para->pv, bad_actions);
        bad_actions = Exists(para->bddmgr, para->v, bad_actions);
        BDD good_succ = reachablefromlast * p;
        good_succ = good_succ - (good_succ * bad_actions);
        good_succ = Exists(para->bddmgr, para->v, good_succ).SwapVariables(*para->v, *para->pv);
        reachablefromlast = Exists(para->bddmgr, para->a, good_succ);

        BDD abdd = reachablefromlast * last;
        if (abdd == para->bddmgr->bddZero())
          return false;

        Q = abdd * T;   // if this is not false, we found a loop
        if (Q == para->bddmgr->bddZero()) {
          BDD curstate = pick_combination_minterm(abdd, variables, para);
          tmpresult.push_back(new BDD(curstate));
          BDD action = Exists(para->bddmgr, para->v, good_succ * curstate).PickOneMinterm(*para->a);
          tmp_actions.push_back(action);
          T = T + curstate;
        } else {
          BDD curstate = pick_combination_minterm(Q, variables, para);
          BDD action = Exists(para->bddmgr, para->v, good_succ * curstate).PickOneMinterm(*para->a);
          tmp_actions.push_back(action);
          break;
        }
      }
      unsigned int numberofstates = (unsigned int) tmpresult.size() - 1;  // (the last one is NOT repeated)
      int loopstart = -1; // the position where the loop starts
      for (unsigned int acounter = 0; acounter <= numberofstates; acounter++) {
        if ((Q * (*tmpresult[acounter])) != para->bddmgr->bddZero()) {
          loopstart = acounter;
          break;
        }
      }

      if (loopstart == -1) {
        if (options["quiet"] == 0) {
          cout << "Witness generation for ATLG:" << endl;
          cout << "THERE IS A PROBLEM HERE, PLEASE REPORT THIS ERROR" <<
            endl;
        }
        return false;
      }
      // building transitions
      // first go to the last loop state
      int position1 = scount;
      for (unsigned int acounter = 0; acounter < numberofstates; acounter++) {
        BDD from = *tmpresult[acounter];
        BDD to = tmpresult[acounter + 1]->SwapVariables(*para->v, *para->pv);
        BDD action = tmp_actions[acounter];
        if (acounter == 0) {
          desctr.push_back(new transition(&from, index, &to, ++scount, &action));
          if (index >= idbdd->size())
            idbdd->insert(pair < int, BDD * >(index, (tmpresult[acounter])));
          desc.push_back(index);
        } else {
          desctr.push_back(new transition(&from, scount, &to, scount + 1, &action));
          idbdd->insert(pair < int, BDD * >(scount, (tmpresult[acounter])));
          desc.push_back(scount++);
        }
      }

      // Now add the loop back
      BDD from = *tmpresult[numberofstates];
      BDD to = tmpresult[loopstart]->SwapVariables(*para->v, *para->pv);
      BDD action = tmp_actions[tmp_actions.size() - 1];

      if (loopstart == 0) {
        if (numberofstates == 0) {
          desctr.push_back(new transition(&from, index, &to, index, &action));
          if (index >= idbdd->size())
            idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));

          desc.push_back(index);
        } else {
          desctr.push_back(new transition(&from, scount, &to, index, &action));
          idbdd->insert(pair < int, BDD * >(scount, (tmpresult[numberofstates])));

          desc.push_back(scount);
        }
        desc.push_back(index);
      } else {
        int loopposition = position1 + loopstart;
        desctr.
          push_back(new transition(&from, scount, &to, loopposition, &action));

        idbdd->insert(pair < int, BDD * >(scount, (tmpresult[numberofstates])));
        desc.push_back(scount);
        desc.push_back(loopposition);
      }
      countex->push_back(new vector< int >(desc));

      cextr->push_back(new vector< transition * >(desctr));

      // Print witness for all states in the path
      for (vector< BDD * >::iterator tmpri = tmpresult.begin();
           tmpri != tmpresult.end(); tmpri++) {
        if (tmpri == tmpresult.begin())
          ((modal_formula *) obj[1])->build_cex(
              *tmpri, index, para, countex, idbdd, cextr, variables, agents,
              strategies);
        else
          ((modal_formula *) obj[1])->build_cex(
              *tmpri, ++position1, para, countex, idbdd, cextr, variables,
              agents, strategies);
      }

      return true;
    }
  }

  case 48:{     // ATL operator U
    vector< BDD >S; // a vector to store the stages of the fixpoint computation
    vector< BDD >tmp_actions;
    BDD p = ((modal_formula *) obj[1])->check_formula(para, variables, agents);
    BDD q = ((modal_formula *) obj[2])->check_formula(para, variables, agents);
		BDD freach = para->bddmgr->bddOne();
		if (!is_fairness->empty()) {
			freach = para->reach->SwapVariables(*para->v, *para->pv);
		}				

    if (options["fullatl"] > 0) {
      BDD last = check_formula(para, variables, agents); // the last state of fixpoint computation
      tmpresult.push_back(new BDD(*state));
      map< string, int >statekeys;
      if (index >= idbdd->size())
        idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
      string strkey = state_to_str(*tmpresult[0], *para->v);

      statekeys[strkey] = index;
      if (*tmpresult[0] * q == para->bddmgr->bddZero()) {
        BDD atltree = *state;
        if (atltree * last == para->bddmgr->bddZero())
          return false;
        BDD Y = atltree;
        BDD lastprime = last.SwapVariables(*para->v, *para->pv);
        //int depth = 0;
        BDD paststate;
        if (options["atlnewstate"] == 1)
          paststate = para->bddmgr->bddZero();  // store states that have been visited

        while (Y != para->bddmgr->bddZero()) {
          for (unsigned int i = 0; i < agents->size(); i++)
            Y = Y * (*para->vRT)[i];
					// remove unfair successor states
					if (!is_fairness->empty()) {
						Y = Y * freach;
					}
          // Compute successors that do not satisfy the ATLG formula
          BDD badstates = Y * (!lastprime);

          // Remove successor states; keep actions and source states only
          badstates = Exists(para->bddmgr, para->pv, badstates);
          badstates = badstates * (*para->reach);

          // Pick up bad actions executed by the opponents
          badstates = badstates.ExistAbstract(actagtout);

          // Pick up successors that either do not satisfy the ATLG formula or cannot reached by any strategy
          Y = Y - badstates;

          // keep only one strategy
          if (options["fullatl"] >= 3) {
            BDD allsources = Exists(para->bddmgr, para->a, Y);
            allsources = Exists(para->bddmgr, para->pv, allsources);
            BDD missed = allsources;
            BDD YY = para->bddmgr->bddZero();
            while (missed != para->bddmgr->bddZero()) {
              BDD source = pick_combination_minterm(missed, variables, para);
              BDD trans = source * Y;
              if (options["atlnewstate"] == 1) {
                BDD sourcetarget =
                  source.SwapVariables(*para->v, *para->pv);
                paststate += sourcetarget;
                BDD newtrans = trans - paststate;
                if (newtrans != para->bddmgr->bddZero())
                  trans = newtrans;
              }
              BDD strategy = trans.PickOneMinterm(*para->a);
              strategy = strategy.ExistAbstract(actagtout);
              strategy = Y * strategy;
              YY += strategy;
              BDD heads = Exists(para->bddmgr, para->a, strategy);
              heads = Exists(para->bddmgr, para->pv, heads);
              missed = missed - heads;
            }
            Y = YY;
          }

          BDD Y1 = Exists(para->bddmgr, para->v, Y);
          Y1 = Exists(para->bddmgr, para->a, Y1);

          // Now we need to store the actions
          BDD nextstate = Y1;
          BDD good_succ = Y;
          do {
            BDD successor = pick_next_combination_minterm(nextstate, variables, para);
            nextstate = nextstate - successor;
            BDD to = successor.SwapVariables(*para->v, *para->pv);
            strkey = state_to_str(to, *para->v);
            map< string, int >::iterator gi = statekeys.find(strkey);
            int to_index;
            if (gi == statekeys.end()) {
              tmpresult.push_back(new  BDD(to));
              idbdd->insert(pair < int, BDD * >(++scount, tmpresult.back()));
              statekeys[strkey] = scount;
              // put the next state in the stack
              to_index = scount;
            } else
              to_index = gi->second;

            // compute all predecessors that have the selected successor
            BDD predecessors = good_succ * successor;
            do {
              BDD predecessor = pick_combination_minterm(predecessors, variables, para);
              predecessors = predecessors - predecessor;
              BDD from = predecessor;
              strkey = state_to_str(predecessor, *para->v);
              gi = statekeys.find(strkey);
              if (gi == statekeys.end()) {
                cout << "  cannot find state: " << strkey << endl;
                exit(0);
              }
              int from_index = gi->second;
              desc.push_back(from_index);

              // get the set of actions
              BDD action = Exists(para->bddmgr, para->pv, good_succ * successor * predecessor);
              action = Exists(para->bddmgr, para->v, action);
              do {
                BDD oneaction = action.PickOneMinterm(*para->a);
                action = action - oneaction;

                desctr.push_back(new transition(&from, from_index, &to, to_index, &oneaction));
                cextr->push_back(new vector< transition * >(desctr));
                desctr.pop_back();
              } while (action != para->bddmgr->bddZero());
              desc.push_back(to_index);
              countex->push_back(new vector< int >(desc));
              desc.pop_back();
              desc.pop_back();
            } while (predecessors != para->bddmgr->bddZero());
          } while (nextstate != para->bddmgr->bddZero());

          // move the frontier to the good successors
          Y = Y1;
          Y = Y.SwapVariables(*para->v, *para->pv);
          Y = Y - atltree;
          atltree += Y;
          Y -= q;
        }
      }
      // Generate tree for every state in the atl tree
      if (options["fullatl"] % 2 == 0) {
        for (vector< BDD * >::iterator tmpri = tmpresult.begin();
             tmpri != tmpresult.end(); tmpri++) {
          string strkey = state_to_str(*(*tmpri), *para->v);
          map< string, int >::iterator gi = statekeys.find(strkey);
          if (**tmpri * q == para->bddmgr->bddZero())
            ((modal_formula *) obj[1])->build_cex(
                *tmpri, gi->second, para, countex, idbdd, cextr, variables,
                agents, strategies);
          else
            ((modal_formula *) obj[2])->build_cex(
                *tmpri, gi->second, para, countex, idbdd, cextr, variables,
                agents, strategies);
        }
      }
      return true;
    } else {
      BDD tmp1 = q;
      BDD curstate = para->bddmgr->bddOne();  // the current state
      int n = 0, j = 0;
      S.push_back(tmp1);
      while (*state * tmp1 == para->bddmgr->bddZero()) {
        tmp1 = check_ATLX(tmp1, name, para) * p;
        S.push_back(tmp1);
        n++;
      }
      while (j <= n) {
        BDD aset1;
        BDD good_succ = para->bddmgr->bddZero();
        if (j == 0) {
          aset1 = (*state);
        } else {
          tmp1 = curstate;
          for (unsigned int i = 0; i < agents->size(); i++)
            tmp1 = tmp1 * (*para->vRT)[i];
          BDD pq = S[n - j].SwapVariables(*para->v, *para->pv);
          BDD bad_succ = tmp1 - pq;
          BDD bad_actions = bad_succ.ExistAbstract(actagtout);
          bad_actions = Exists(para->bddmgr, para->pv, bad_actions);
          bad_actions = Exists(para->bddmgr, para->v, bad_actions);
          good_succ = tmp1 * pq;
          good_succ = good_succ - (good_succ * bad_actions);
          good_succ = Exists(para->bddmgr, para->v, good_succ).SwapVariables(*para->v, *para->pv);
          aset1 = Exists(para->bddmgr, para->a, good_succ);
        }
        if (aset1 == para->bddmgr->bddZero())
          return false;
        curstate = pick_combination_minterm(aset1, variables, para);
        tmpresult.push_back(new BDD(curstate));
        if (j > 0) {
          BDD action = Exists(para->bddmgr, para->v, good_succ * curstate).PickOneMinterm(*para->a);
          tmp_actions.push_back(action);
        }
        j++;
      }

      int position1 = scount;

      // transitions
      for (int i = 0; i < (int) tmpresult.size() - 1; i++) {
        BDD from = *tmpresult[i];
        BDD to = tmpresult[i + 1]->SwapVariables(*para->v, *para->pv);
        BDD action = tmp_actions[i];
        if (i == 0) {
          desctr.
            push_back(new transition(&from, index, &to, ++scount, &action));
          if (index >= idbdd->size())
            idbdd->insert(pair < int, BDD * >(index, (tmpresult[i])));
          desc.push_back(index);
        } else {
          desctr.
            push_back(new transition(&from, scount, &to, scount + 1, &action));
          idbdd->insert(pair < int, BDD * >(scount, (tmpresult[i])));
          desc.push_back(scount++);
        }
      }
      if (tmpresult.size() == 1) {
        if (index >= idbdd->size())
          idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
      } else {
        desc.push_back(scount);
        idbdd->insert(pair < int, BDD * >(scount, (tmpresult[tmpresult.size() - 1])));
        countex->push_back(new vector< int >(desc));

        cextr->push_back(new vector< transition * >(desctr));
      }

      for (unsigned int i = 0; i < tmpresult.size() - 1; i++) {
        if ((*tmpresult[i]) <=
            ((modal_formula *) obj[1])->check_formula(para, variables, agents)) {
          if (i == 0)
            ((modal_formula *) obj[1])->build_cex(
                tmpresult[i], index, para, countex, idbdd, cextr, variables,
                agents, strategies);
          else
            ((modal_formula *) obj[1])->build_cex(
                tmpresult[i], ++position1, para, countex, idbdd, cextr,
                variables, agents, strategies);
        }
      }
      return ((modal_formula *) obj[2])->
        build_cex(tmpresult[tmpresult.size() - 1],
                  (tmpresult.size() == 1 ? index : scount), para, countex,
                  idbdd, cextr, variables, agents, strategies);
    }
  }

  case 50:      // SL <<x>>
    {
      bool result;
      string variable_name = ((atomic_proposition *)
        ((modal_formula *) obj[0])->obj[0])->get_proposition();

      // Build the new strategy.
      modal_formula *subformula = (modal_formula *) obj[1];
      strategy new_strategy = build_strategy(variable_name, subformula, para);

      // Store the previous strategy and assign the new one.
      strategy *previous_strategy = NULL;
      map<string, strategy *>::iterator position = variables->find(
          variable_name);
      if (position != variables->end()) {
        previous_strategy = position->second;
        position->second = &new_strategy;
      } else {
        position = variables->insert(
            make_pair(variable_name, &new_strategy)).first;
      }

      // Calculate the subresult.
      BDD phi = subformula->check_formula(para, variables, agents);
      BDD combinations = phi * (*state);

      if (combinations == para->bddmgr->bddZero()) {
        result = false;
      } else {
        //cout << "Combination for strategy '" << variable_name << "'" << endl;

        BDD combination = (combinations * (
            *new_strategy.get_valid_restrictions())).PickOneMinterm(
            *new_strategy.get_bdd_variables());
        BDD restricted_state = (*state) * combination;

        strategies->insert(make_pair(variable_name, make_pair(
            new_strategy, restricted_state)));

        result = subformula->build_cex(&restricted_state, index, para, countex,
            idbdd, cextr, variables, agents, strategies);
      }

      // Restore the previous strategy.
      if (previous_strategy != NULL) {
        position->second = previous_strategy;
      } else {
        variables->erase(position);
      }

      return result;
    }

  case 52:      // SL (a, x)
    {
      bool result;
      string agent_name = ((atomic_proposition *)
          ((modal_formula *) obj[0])->obj[0])->get_proposition();
      string variable_name = ((atomic_proposition *)
          ((modal_formula *) obj[1])->obj[0])->get_proposition();

      // Get the new strategy.
      strategy *new_strategy = variables->find(variable_name)->second;

      // Store the previous strategy and assign the new one.
      strategy *previous_strategy = NULL;
      map<string, strategy *>::iterator position = agents->find(agent_name);
      if (position != agents->end()) {
        previous_strategy = position->second;
        position->second = new_strategy;
      } else {
        position = agents->insert(make_pair(agent_name, new_strategy)).first;
      }

      // Store previous SL restriction BDD.
      bool oldCalRestrictSL = para->calRestrictSL;
      BDD *oldRestrictSL = para->restrictSL;
      para->calRestrictSL = true;
      para->restrictSL = NULL;

      // Calculate the subresult.
      modal_formula *subformula = (modal_formula *) obj[2];
      result = subformula->build_cex(state, index, para, countex, idbdd, cextr,
          variables, agents, strategies);

      // Restore previous SL restriction BDD.
      if (para->restrictSL != NULL) {
        delete para->restrictSL;
      }
      para->calRestrictSL = oldCalRestrictSL;
      para->restrictSL = oldRestrictSL;

      // Restore the previous strategy.
      if (previous_strategy != NULL) {
        position->second = previous_strategy;
      } else {
        agents->erase(position);
      }

      return result;
    }

  case 53:      // SLX
    {
      // Calculate next states.
      BDD result = ((modal_formula *) obj[0])->check_formula(
          para, variables, agents);
      result = result.SwapVariables(*para->pv, *para->v);
      result = result * (*state) * SL_transition(agents, para);
      if (result == para->bddmgr->bddZero()) {
        return false;
      }

      // Pick an arbitrary next state and action.
      result = result.SwapVariables(*para->v, *para->pv);
      BDD next_state = pick_combination_minterm(result, variables, para);
      BDD action = result.PickOneMinterm(*para->a);

      // Add the transition.
      desctr.push_back(new transition(
          state, current_index, &next_state, next_index, &action));
      idbdd->insert(make_pair(current_index, new BDD(*state)));
      idbdd->insert(make_pair(next_index, new BDD(next_state)));
      desc.push_back(current_index);
      desc.push_back(next_index);
      countex->push_back(new vector<int>(desc));
      cextr->push_back(new vector<transition *>(desctr));
      generate_index(&current_index, &next_index);

      return ((modal_formula *) obj[0])->build_cex(
          &next_state, current_index, para, countex, idbdd, cextr, variables,
          agents, strategies);
    }

  case 56:      // SLU
    {
      BDD p = ((modal_formula *) obj[0])->check_formula(
          para, variables, agents);
      BDD q = ((modal_formula *) obj[1])->check_formula(
          para, variables, agents);
      BDD S = SL_transition(agents, para);

      // Calculate steps.
      vector<BDD> steps;
      BDD tmp1 = q;
      BDD tmp2 = para->bddmgr->bddZero();
      while (tmp1 != tmp2) {
        steps.push_back(tmp1);
        tmp2 = tmp1;
        tmp1 = tmp1 + p * check_SL_X(tmp1, agents, para);
      }

      // Find at which step the state is.
      size_t j = 0;
      for (; j < steps.size(); j++) {
        if ((*state) <= steps[j]) {
          break;
        }
      }
      if (j == steps.size()) {
        return false;
      }

      // Generate all transitions and states.
      BDD from = *state;
      for (size_t i = j; i > 0; i--) {
        BDD result = (from * S).SwapVariables(
            *para->v, *para->pv) * steps[i - 1];
        if (result == para->bddmgr->bddZero()) {
          return false;
        }

        BDD to = pick_combination_minterm(result, variables, para);
        BDD action = result.PickOneMinterm(*para->a);

        desctr.push_back(new transition(
            &from, current_index, &to, next_index, &action));
        idbdd->insert(make_pair(current_index, new BDD(from)));
        desc.push_back(current_index);
        generate_index(&current_index, &next_index);

        from = to;
      }

      desc.push_back(current_index);
      idbdd->insert(make_pair(current_index, new BDD(from)));
      countex->push_back(new vector<int>(desc));
      cextr->push_back(new vector<transition *>(desctr));

      /*for (unsigned int i = 0; i < tmpresult.size() - 1; i++) {
        if ((*tmpresult[i]) <=
            ((modal_formula *) obj[0])->check_formula(para, variables, agents)) {
          if (i == 0)
            ((modal_formula *) obj[0])->build_cex(
                tmpresult[i], index, para, countex, idbdd, cextr, variables,
                agents, strategies);
          else
            ((modal_formula *) obj[0])->build_cex(
                tmpresult[i], ++position1, para, countex, idbdd, cextr,
                variables, agents, strategies);
        }
      }*/

      return ((modal_formula *) obj[1])->build_cex(
          &from, current_index, para, countex, idbdd, cextr, variables, agents,
          strategies);
    }

  case 54:      // SLF
    {
      BDD p = ((modal_formula *) obj[0])->check_formula(
          para, variables, agents);
      BDD S = SL_transition(agents, para);

      // Calculate steps.
      vector<BDD> steps;
      BDD tmp1 = p;
      BDD tmp2 = para->bddmgr->bddZero();
      while (tmp1 != tmp2) {
        steps.push_back(tmp1);
        tmp2 = tmp1;
        tmp1 = tmp1 + check_SL_X(tmp1, agents, para);
      }

      // Find at which step the state is.
      size_t j = 0;
      for (; j < steps.size(); j++) {
        if ((*state) <= steps[j]) {
          break;
        }
      }
      if (j == steps.size()) {
        return false;
      }

      // Generate all transitions and states.
      BDD from = *state;
      for (size_t i = j; i > 0; i--) {
        BDD result = (from * S).SwapVariables(
            *para->v, *para->pv) * steps[i - 1];
        if (result == para->bddmgr->bddZero()) {
          return false;
        }

        BDD to = pick_combination_minterm(result, variables, para);
        BDD action = result.PickOneMinterm(*para->a);

        desctr.push_back(new transition(
            &from, current_index, &to, next_index, &action));
        idbdd->insert(make_pair(current_index, new BDD(from)));
        desc.push_back(current_index);
        generate_index(&current_index, &next_index);

        from = to;
      }

      desc.push_back(current_index);
      idbdd->insert(make_pair(current_index, new BDD(from)));
      countex->push_back(new vector<int>(desc));
      cextr->push_back(new vector<transition *>(desctr));

      return ((modal_formula *) obj[0])->build_cex(
          &from, current_index, para, countex, idbdd, cextr, variables, agents,
          strategies);
    }

  case 55:      // SLG
    {
      tmpresult.push_back(new BDD(*state));

      BDD fixpoint = check_formula(para, variables, agents);
      BDD S = SL_transition(agents, para);

      // Find the loop.
      BDD Q = para->bddmgr->bddZero();
      BDD T = para->bddmgr->bddZero() + *state;

      while (Q == para->bddmgr->bddZero()) {
        BDD reachablefromlast = S * (*tmpresult[tmpresult.size() - 1]);
        reachablefromlast = Exists(para->bddmgr, para->a, reachablefromlast);
        reachablefromlast = Exists(para->bddmgr, para->v, reachablefromlast);
        reachablefromlast = reachablefromlast.SwapVariables(
            *para->v, *para->pv);

        BDD reach_fixpoint = reachablefromlast * fixpoint;
        if (reach_fixpoint == para->bddmgr->bddZero()) {
          return false;
        }

        Q = reach_fixpoint * T;
        if (Q == para->bddmgr->bddZero()) {
          BDD curstate = pick_combination_minterm(
              reach_fixpoint, variables, para);
          tmpresult.push_back(new BDD(curstate));
          T = T + curstate;
        } else {
          break;
        }
      }

      // Find where the loop starts.
      size_t loopstart = 0;
      for (; loopstart < tmpresult.size(); loopstart++) {
        if (Q * (*tmpresult[loopstart]) != para->bddmgr->bddZero()) {
          break;
        }
      }
      if (loopstart == tmpresult.size()) {
        return false;
      }

      // Generate all transitions and states.
      int loopstart_index = -1;
      for (size_t i = 0; i < tmpresult.size() - 1; i++) {
        if (i == loopstart) {
          loopstart_index = current_index;
        }
        BDD from = *tmpresult[i];
        BDD to = tmpresult[i + 1]->SwapVariables(*para->v, *para->pv);
        BDD action = (from * to * S).PickOneMinterm(*para->a);
        desctr.push_back(new transition(
            &from, current_index, &to, next_index, &action));
        idbdd->insert(pair<int, BDD *>(current_index, (tmpresult[i])));
        desc.push_back(current_index);
        generate_index(&current_index, &next_index);
      }

      // Add the loop back.
      BDD from = *tmpresult[tmpresult.size() - 1];
      BDD to = tmpresult[loopstart]->SwapVariables(*para->v, *para->pv);
      BDD action = (from * to * S).PickOneMinterm(*para->a);
      desctr.push_back(new transition(
          &from, current_index, &to, loopstart_index, &action));
      idbdd->insert(pair<int, BDD *>(
          current_index, tmpresult[tmpresult.size() - 1]));
      desc.push_back(current_index);
      desc.push_back(loopstart_index);

      countex->push_back(new vector<int>(desc));
      cextr->push_back(new vector<transition *>(desctr));

      /*// Print witness for all states in the path
      for (vector< BDD * >::iterator tmpri = tmpresult.begin();
           tmpri != tmpresult.end(); tmpri++) {
        if ((*(*tmpri)) <= ((modal_formula *) obj[0])->check_formula(para, variables, agents)) {
          if (tmpri == tmpresult.begin())
            ((modal_formula *) obj[0])->build_cex(
                *tmpri, index, para, countex, idbdd, cextr, variables, agents,
                strategies);
          else
            ((modal_formula *) obj[0])->build_cex(
                *tmpri, ++position1, para, countex, idbdd, cextr, variables,
                agents, strategies);
        }
      }*/

      return true;
    }

  case 0:
  case 10:      // AG
  case 12:      // AX
  case 14:      // AF
  case 16:      // AU
  case 51:      // SL [[x]]
  case 30:
  case 31:
  case 32:
  case 40:
  case 42:{
    BDD p = check_formula(para, variables, agents);

    if ((*state) <= p) {
      if (idbdd->size() == 0) {
        idbdd->insert(pair < int, BDD * >(index, (new BDD(*state))));
        desc.push_back(index);
        countex->push_back(new vector< int >(desc));
      }

      return true;
    } else {
      return false;
    }

  }

    // leaf
  case 3:{
    modal_formula *argument = ((modal_formula *) obj[0]);

    if (argument->get_op() == 0) {

      // It's the negation of an atom

      BDD p = check_formula(para, variables, agents);

      if ((*state) <= p) {
        if (idbdd->size() == 0) {
          idbdd->insert(pair < int, BDD * >(index, ((new BDD(*state)))));
          desc.push_back(index);
          countex->push_back(new vector< int >(desc));
        }

        return true;
      } else {
        return false;
      }
    } else if (argument->get_op() == 30 || argument->get_op() == 31
               || argument->get_op() == 40 || argument->get_op() == 32
               || argument->get_op() == 42) {
      // it's the negation of K
      tmpresult.push_back(new BDD(*state));

      // Finding the position of the agent:
      string name, name1;
      Object *id;
      modal_formula *agentid = (modal_formula *) (argument->get_operand(0));
      BDD aset1;
      BDD rel;
      BDD formula;
      if (argument->get_op() == 30) {
        id = agentid->get_operand(0);
        name = ((atomic_proposition *) id)->get_proposition();
        formula =
          !((modal_formula *) (argument->get_operand(1)))->check_formula(para, variables, agents) * (*para->reach);

        aset1 = get_K_states(formula, state, name, para);
      } else if (argument->get_op() == 31) {
        id = agentid->get_operand(0);
        name = ((atomic_proposition *) id)->get_proposition();
        formula = ((modal_formula *) (argument->get_operand(1)))->check_formula(para, variables, agents) * (*para->reach);
        aset1 = check_GK(formula, name, para);

        aset1 = !aset1 * !formula * (*para->reach);
        aset1 = get_GK_states(aset1, state, name, para);
      } else if (argument->get_op() == 32) {
        id = agentid->get_operand(0);
        name = ((atomic_proposition *) id)->get_proposition();
        formula = ((modal_formula *) (argument->get_operand(1)))->check_formula(para, variables, agents);
        aset1 = !check_GCK(formula, name, para) * (*para->reach);

        aset1 = aset1 * !formula;
        aset1 = get_GK_states(aset1, state, name, para);
      } else if (argument->get_op() == 40) {  // O
        id = agentid->get_operand(0);
        name = ((atomic_proposition *) id)->get_proposition();
        formula = !((modal_formula *) (argument->get_operand(1)))->check_formula(para, variables, agents) * (*para->reach);
        aset1 = check_nO(formula, name, para) * (*para->reach);
      } else if (argument->get_op() == 42) {
        id = agentid->get_operand(0);
        name = ((atomic_proposition *) id)->get_proposition();
        formula = ((modal_formula *) argument->get_operand(1))->check_formula(para, variables, agents) * (*para->reach);
        aset1 = check_DK(formula, name, para);

        aset1 = !aset1 * !formula * (*para->reach);
        aset1 = get_DK_states(aset1, state, name, para);
      }

      if (aset1 == para->bddmgr->bddZero())
        return false;

      BDD curstate = pick_combination_minterm(aset1, variables, para);
      if (curstate == *state) {
        aset1 = aset1 - curstate;
        if (aset1 != para->bddmgr->bddZero())
          curstate = pick_combination_minterm(aset1, variables, para);
      }
      tmpresult.push_back(new BDD(curstate));

      BDD from = *tmpresult[0];
      BDD to = tmpresult[1]->SwapVariables(*para->v, *para->pv);
      BDD action = para->bddmgr->bddOne();
      if (argument->get_op() == 30 || argument->get_op() == 31
          || argument->get_op() == 32 || argument->get_op() == 40
          || argument->get_op() == 42)
        desctr.push_back(new transition(&from, index, &to, scount + 1, name, &action));
      if (index >= idbdd->size())
        idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
      desc.push_back(index);
      desc.push_back(++scount);
      countex->push_back(new vector< int >(desc));
      idbdd->insert(pair < int, BDD * >(scount, (tmpresult[1])));

      cextr->push_back(new vector< transition * >(desctr));
      if (argument->get_op() != 40) {
        modal_formula *fcex;
        if (argument->get_op() == 30 || argument->get_op() == 31
            || argument->get_op() == 32 || argument->get_op() == 42)
          fcex = new modal_formula(3, ((modal_formula *) (argument->get_operand(1))));
        else
          fcex = new modal_formula(3, ((modal_formula *) (argument-> get_operand(2))));
        fcex = fcex->push_negations(1);

        //cout << fcex->to_string() << endl;

        return fcex->build_cex(
            tmpresult[1], scount, para, countex, idbdd, cextr, variables,
            agents, strategies);
      } else
        return true;
    } else if ((argument->get_op() == 45 || argument->get_op() == 46
                || argument->get_op() == 47 || argument->get_op() == 48)
               && options["atlcex"] > 0) {
      if (argument->get_op() == 45) { // ATLX
        BDD p = ((modal_formula *) (argument->get_operand(1)))->check_formula(para, variables, agents);

        tmpresult.push_back(new BDD(*state));

        // get all successor states
        BDD successors = *state;
        for (unsigned int i = 0; i < agents->size(); i++)
          successors = successors * (*para->vRT)[i];

        BDD allactions = Exists(para->bddmgr, para->pv, successors);
        allactions = Exists(para->bddmgr, para->v, allactions);
        allactions = allactions.ExistAbstract(actagtout);

        // get successors that do not satisfy operator[1], i.e., \phi in <name>X \phi
        p = p.SwapVariables(*para->v, *para->pv);
        BDD bad_succ = successors - p;

        map< string, int >statekeys;

        if (index >= idbdd->size())
          idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
        string strkey = state_to_str(*tmpresult[0], *para->v);
        statekeys[strkey] = index;

        desc.push_back(index);
        do {
          BDD oneaction = allactions.PickOneMinterm(*para->a);

          BDD onetran = oneaction.ExistAbstract(actagtout);
          allactions = allactions - onetran;

          onetran *= bad_succ;
          BDD successor = pick_next_combination_minterm(onetran, variables, para);
          oneaction = (onetran * successor).PickOneMinterm(*para->a);

          // put the next state in the stack
          tmpresult.
            push_back(new
                      BDD(successor.SwapVariables(*para->v, *para->pv)));

          // get the set of actions
          BDD from = *tmpresult[0];
          BDD to = *tmpresult.back();
          strkey = state_to_str(to, *para->v);
          map< string, int >::iterator gi = statekeys.find(strkey);
          if (gi == statekeys.end()) {
            idbdd->insert(pair < int, BDD * >(++scount, (tmpresult[tmpresult.size() - 1])));
            statekeys[strkey] = scount;
            desctr.push_back(new transition(&from, index, &to, scount, &oneaction));
            desc.push_back(scount);
          } else {
            desctr.push_back(new transition(&from, index, &to, gi->second, &oneaction));
            desc.push_back(gi->second);
          }
          countex->push_back(new vector< int >(desc));

          cextr->push_back(new vector< transition * >(desctr));
          desc.pop_back();
          desctr.pop_back();
        } while (allactions != para->bddmgr->bddZero());
        if (options["atlcex"] == 2) {
          for (unsigned int i = 1; i < tmpresult.size(); i++) {
            string strkey = state_to_str(*tmpresult[i], *para->v);
            map< string, int >::iterator gi = statekeys.find(strkey);
            modal_formula nphi(3, (modal_formula *) (argument->get_operand(1)));
            nphi.build_cex(
                tmpresult[i], gi->second, para, countex, idbdd, cextr,
                variables, agents, strategies);
          }
        }

        return true;
      } else if (argument->get_op() == 46) {  // ATLF
        BDD p = ((modal_formula *) (argument->get_operand(1)))->check_formula(para, variables, agents);
        BDD p1 = p.SwapVariables(*para->v, *para->pv);
        tmpresult.push_back(new BDD(*state));
        if (index >= idbdd->size())
          idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
        map< string, int >statekeys;
        string strkey = state_to_str(*tmpresult[0], *para->v);
        statekeys[strkey] = index;

        BDD last = argument->check_formula(para, variables, agents); // the last state of fixpoint computation    

        BDD atltree = *state;
        BDD Y = atltree;
        BDD lastprime = last.SwapVariables(*para->v, *para->pv);
        while (Y != para->bddmgr->bddZero()) {
          BDD tmpy = Y;
          BDD newy = para->bddmgr->bddZero();

          // get all successor states
          while (tmpy != para->bddmgr->bddZero()) {
            BDD predecessor = pick_combination_minterm(tmpy, variables, para);
            tmpy -= predecessor;
            BDD from = predecessor;
            strkey = state_to_str(predecessor, *para->v);
            map< string, int >::iterator gi = statekeys.find(strkey);
            if (gi == statekeys.end()) {
              cout << "  ATLF counterexample - cannot find state: " <<
                strkey << endl;
              exit(0);
            }
            int from_index = gi->second;
            desc.push_back(from_index);

            BDD successors = predecessor;
            for (unsigned int i = 0; i < agents->size(); i++)
              successors *= (*para->vRT)[i];

            BDD allactions = Exists(para->bddmgr, para->pv, successors);
            allactions = Exists(para->bddmgr, para->v, allactions);
            allactions = allactions.ExistAbstract(actagtout);

            // get successors that do not satisfy operator[1], i.e., \phi in <name>X \phi
            BDD bad_succ1 = successors - lastprime; // \not ATLF p
            do {
              BDD oneaction = allactions.PickOneMinterm(*para->a);

              BDD onetran = oneaction.ExistAbstract(actagtout);
              allactions = allactions - onetran;
              onetran = onetran * bad_succ1;

              BDD successor = pick_next_combination_minterm(onetran, variables, para);
              BDD succ1 = successor.SwapVariables(*para->v, *para->pv);
              oneaction = (onetran * successor).PickOneMinterm(*para->a);

              // get the set of actions
              BDD to = succ1;
              strkey = state_to_str(succ1, *para->v);
              gi = statekeys.find(strkey);
              if (gi == statekeys.end()) {
                newy += succ1;  // succ1 \models \phi
                tmpresult.push_back(new BDD(succ1));

                idbdd->insert(pair < int, BDD * >(++scount, tmpresult.back()));
                statekeys[strkey] = scount;
                desctr.push_back(new transition(&from, from_index, &to, scount, &oneaction));
                desc.push_back(scount);
              } else {
                desctr.push_back(new transition(&from, from_index, &to, gi->second, &oneaction));
                desc.push_back(gi->second);
              }
              countex->push_back(new vector< int >(desc));

              cextr->push_back(new vector< transition * >(desctr));
              desc.pop_back();
              desctr.pop_back();
            } while (allactions != para->bddmgr->bddZero());
            desc.pop_back();
          }
          Y = newy;
        }
        if (options["atlcex"] == 2) {
          for (unsigned int i = 0; i < tmpresult.size(); i++) {
            string strkey = state_to_str(*tmpresult[i], *para->v);
            map< string, int >::iterator gi = statekeys.find(strkey);
            modal_formula nphi(3, (modal_formula *) (argument->get_operand(1)));
            nphi.build_cex(
                tmpresult[i], gi->second, para, countex, idbdd, cextr,
                variables, agents, strategies);
          }
        }

        return true;
      } else if (argument->get_op() == 47) {  // ATLG
        BDD p = ((modal_formula *) (argument->get_operand(1)))->check_formula(para, variables, agents);
        BDD p1 = p.SwapVariables(*para->v, *para->pv);
        tmpresult.push_back(new BDD(*state));
        if (index >= idbdd->size())
          idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
        if (*state * p == para->bddmgr->bddZero()) {
          if (options["atlcex"] == 2) {
            modal_formula nphi(3, (modal_formula *) (argument->get_operand(1)));
            nphi.build_cex(
                state, index, para, countex, idbdd, cextr, variables, agents,
                strategies);
          }
          return true;
        }
        map< string, int >statekeys;
        string strkey = state_to_str(*tmpresult[0], *para->v);
        statekeys[strkey] = index;

        BDD last = argument->check_formula(para, variables, agents); // the last state of fixpoint computation    

        BDD atltree = *state;
        BDD Y = atltree;
        BDD lastprime = last.SwapVariables(*para->v, *para->pv);
        while (Y != para->bddmgr->bddZero()) {
          BDD tmpy = Y;
          BDD newy = para->bddmgr->bddZero();

          // get all successor states
          while (tmpy != para->bddmgr->bddZero()) {
            BDD predecessor = pick_combination_minterm(tmpy, variables, para);
            tmpy -= predecessor;
            BDD from = predecessor;
            strkey = state_to_str(predecessor, *para->v);
            map< string, int >::iterator gi = statekeys.find(strkey);
            if (gi == statekeys.end()) {
              cout << "  ATLG counterexample - cannot find state: " <<
                strkey << endl;
              exit(0);
            }
            int from_index = gi->second;
            desc.push_back(from_index);

            BDD successors = predecessor;
            for (unsigned int i = 0; i < agents->size(); i++)
              successors *= (*para->vRT)[i];

            BDD allactions = Exists(para->bddmgr, para->pv, successors);
            allactions = Exists(para->bddmgr, para->v, allactions);
            allactions = allactions.ExistAbstract(actagtout);

            // get successors that do not satisfy operator[1], i.e., \phi in <name>X \phi
            BDD bad_succ = successors - p1; // \not \phi
            BDD bad_succ1 = successors - lastprime; // \not ATLG \phi
            do {
              BDD oneaction = allactions.PickOneMinterm(*para->a);
              BDD onetran = oneaction.ExistAbstract(actagtout);
              allactions = allactions - onetran;
              BDD onetran1 = onetran * bad_succ;
              if (onetran1 == para->bddmgr->bddZero())
                onetran = onetran * bad_succ1;
              else
                onetran = onetran1;

              BDD successor = pick_next_combination_minterm(onetran, variables, para);
              BDD succ1 = successor.SwapVariables(*para->v, *para->pv);
              oneaction = (onetran * successor).PickOneMinterm(*para->a);

              // get the set of actions
              BDD to = succ1;
              strkey = state_to_str(succ1, *para->v);
              gi = statekeys.find(strkey);
              if (gi == statekeys.end()) {
                if (onetran1 == para->bddmgr->bddZero())
                  newy += succ1;  // succ1 \models \phi
                else {   // put the next state in the stack
                  // TODO: check correctness
                  tmpresult.push_back(new BDD(succ1));

                  idbdd->insert(pair < int, BDD * >(++scount, tmpresult.back()));
                }
                statekeys[strkey] = scount;
                desctr.push_back(new transition(&from, from_index, &to, scount, &oneaction));
                desc.push_back(scount);
              } else {
                desctr.
                  push_back(new
                            transition(&from, from_index, &to, gi->second,
                                       &oneaction));
                desc.push_back(gi->second);
              }
              countex->push_back(new vector< int >(desc));

              cextr->push_back(new vector< transition * >(desctr));
              desc.pop_back();
              desctr.pop_back();
            } while (allactions != para->bddmgr->bddZero());
            desc.pop_back();
          }
          Y = newy;
        }
        if (options["atlcex"] == 2) {
          for (unsigned int i = 0; i < tmpresult.size(); i++) {
            string strkey = state_to_str(*tmpresult[i], *para->v);
            map< string, int >::iterator gi = statekeys.find(strkey);
            modal_formula nphi(3,
                               (modal_formula *) (argument->
                                                  get_operand(1)));
            nphi.build_cex(
                tmpresult[i], gi->second, para, countex, idbdd, cextr,
                variables, agents, strategies);
          }
        }

        return true;
      } else {    // ATLU
        BDD p =
          ((modal_formula *) (argument->get_operand(1)))->
          check_formula(para, variables, agents);
        BDD q =
          ((modal_formula *) (argument->get_operand(2)))->
          check_formula(para, variables, agents);
        BDD pq = p + q;
        BDD pq1 = pq.SwapVariables(*para->v, *para->pv);
        tmpresult.push_back(new BDD(*state));
        if (index >= idbdd->size())
          idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
        if (*state * p == para->bddmgr->bddZero()) {
          if (options["atlcex"] == 2) {
            modal_formula nphi(3,
                               (modal_formula *) (argument->
                                                  get_operand(1)));
            nphi.build_cex(
                state, index, para, countex, idbdd, cextr, variables, agents,
                strategies);
          }
          return true;
        }
        map< string, int >statekeys;
        string strkey = state_to_str(*tmpresult[0], *para->v);
        statekeys[strkey] = index;

        BDD last = argument->check_formula(para, variables, agents); // the last state of fixpoint computation    

        BDD atltree = *state;
        BDD Y = atltree;
        BDD lastprime = last.SwapVariables(*para->v, *para->pv);
        while (Y != para->bddmgr->bddZero()) {
          BDD tmpy = Y;
          BDD newy = para->bddmgr->bddZero();

          // get all successor states
          while (tmpy != para->bddmgr->bddZero()) {
            BDD predecessor = pick_combination_minterm(tmpy, variables, para);
            tmpy -= predecessor;
            BDD from = predecessor;
            strkey = state_to_str(predecessor, *para->v);
            map< string, int >::iterator gi = statekeys.find(strkey);
            if (gi == statekeys.end()) {
              cout << "  ATLU counterexample - cannot find state: " <<
                strkey << endl;
              exit(0);
            }
            int from_index = gi->second;
            desc.push_back(from_index);

            BDD successors = predecessor;
            for (unsigned int i = 0; i < agents->size(); i++)
              successors *= (*para->vRT)[i];

            BDD allactions = Exists(para->bddmgr, para->pv, successors);
            allactions = Exists(para->bddmgr, para->v, allactions);
            allactions = allactions.ExistAbstract(actagtout);

            // get successors that do not satisfy operator[1], i.e., \phi in <name>X \phi
            BDD bad_succ = successors - pq1;  // \not p \and \not q
            BDD bad_succ1 = successors - lastprime; // \not ATL( p U q)
            do {
              BDD oneaction = allactions.PickOneMinterm(*para->a);

              BDD onetran = oneaction.ExistAbstract(actagtout);
              allactions = allactions - onetran;
              BDD onetran1 = onetran * bad_succ;
              if (onetran1 == para->bddmgr->bddZero())
                onetran = onetran * bad_succ1;
              else
                onetran = onetran1;

              BDD successor = pick_next_combination_minterm(onetran, variables, para);
              BDD succ1 = successor.SwapVariables(*para->v, *para->pv);
              oneaction = (onetran * successor).PickOneMinterm(*para->a);

              // get the set of actions
              BDD to = succ1;
              strkey = state_to_str(succ1, *para->v);
              gi = statekeys.find(strkey);
              if (gi == statekeys.end()) {
                if (onetran1 == para->bddmgr->bddZero())
                  newy += succ1;  // succ1 \models \phi
                else {   // put the next state in the stack
                  // TODO: check correctness
                  tmpresult.push_back(new BDD(succ1));

                  idbdd->insert(pair < int, BDD * >(++scount, tmpresult.back()));
                }
                statekeys[strkey] = scount;
                desctr.
                  push_back(new
                            transition(&from, from_index, &to, scount,
                                       &oneaction));
                desc.push_back(scount);
              } else {
                desctr.
                  push_back(new
                            transition(&from, from_index, &to, gi->second,
                                       &oneaction));
                desc.push_back(gi->second);
              }
              countex->push_back(new vector< int >(desc));

              cextr->push_back(new vector< transition * >(desctr));
              desc.pop_back();
              desctr.pop_back();
            } while (allactions != para->bddmgr->bddZero());
            desc.pop_back();
          }
          Y = newy;
        }
        if (options["atlcex"] == 2) {
          for (unsigned int i = 0; i < tmpresult.size(); i++) {
            string strkey = state_to_str(*tmpresult[i], *para->v);
            map< string, int >::iterator gi = statekeys.find(strkey);
            modal_formula nphi(3,
                               (modal_formula *) (argument->
                                                  get_operand(2)));
            nphi.build_cex(
                tmpresult[i], gi->second, para, countex, idbdd, cextr,
                variables, agents, strategies);
          }
        }

        return true;
      }
    }
  }
  default:
    {
      if (options["quiet"] == 0)
        cout << " OPERATOR CURRENTLY NOT SUPPORTED IN WITNESS/COUNTEREXAMPLE";
      return false;
    }
  }
  if (options["quiet"] == 0)
    cout <<
      " AN ERROR HAS OCCURREND IN THE GENERATION OF WITNESS/COUNTEREXAMPLE";
  return false;

}

BDD
pick_combination_minterm(BDD bdd, map<string, strategy *> *variables,
                         bdd_parameters *para)
{
  vector<BDD> v(*para->v);
  for (map<string, strategy *>::iterator i = variables->begin();
       i != variables->end(); i++) {
    copy(i->second->get_bdd_variables()->begin(),
         i->second->get_bdd_variables()->end(), back_inserter(v));
    bdd = bdd * (*i->second->get_valid_restrictions());
  }
  return bdd.PickOneMinterm(v);
}

BDD
pick_next_combination_minterm(BDD bdd, map<string, strategy *> *variables,
                              bdd_parameters *para)
{
  return pick_combination_minterm(
      bdd.SwapVariables(*para->v, *para->pv), variables, para).SwapVariables(
      *para->v, *para->pv);
}
