#include <ctime>
#include "types.hh"
#include "utilities.hh"
#include "atlk.hh"

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
            op == 64)) {
    return (obj[1]);
  } else if (i == 2 && obj[2] != NULL && (op == 48))
    return (obj[2]);
  else {
    cout << " error: operand " << i << " not found!" << endl;
    exit(1);
  }
}

string
modal_formula::to_string()
{
  // Implemented to maintain backwards compatibility with the original Object definition
  return to_string_const();
}

string
modal_formula::to_string_const() const
{
  if (op == 0)
    return ((atomic_proposition *) obj[0])->to_string();
  else if (op == 1)
    return "(" + ((modal_formula *) obj[0])->to_string() + " && " +
      ((modal_formula *) obj[1])->to_string() + ")";
  else if (op == 2)
    return "(" + ((modal_formula *) obj[0])->to_string() + " || " +
      ((modal_formula *) obj[1])->to_string() + ")";
  else if (op == 3)
    return "(! " + ((modal_formula *) obj[0])->to_string() + ")";
  else if (op == 4)
    return "(" + ((modal_formula *) obj[0])->to_string() + " -> " +
      ((modal_formula *) obj[1])->to_string() + ")";
  else if (op == 5)
    return "TRUE";
  else if (op == 10)
    return "(AG " + ((modal_formula *) obj[0])->to_string() + ")";
  else if (op == 11)
    return "(EG " + ((modal_formula *) obj[0])->to_string() + ")";
  else if (op == 12)
    return "(AX " + ((modal_formula *) obj[0])->to_string() + ")";
  else if (op == 13)
    return "(EX " + ((modal_formula *) obj[0])->to_string() + ")";
  else if (op == 14)
    return "(AF " + ((modal_formula *) obj[0])->to_string() + ")";
  else if (op == 15)
    return "(EF " + ((modal_formula *) obj[0])->to_string() + ")";
  else if (op == 16)
    return "A(" + ((modal_formula *) obj[0])->to_string() + " U " +
      ((modal_formula *) obj[1])->to_string() + ")";
  else if (op == 17)
    return "E(" + ((modal_formula *) obj[0])->to_string() + " U " +
      ((modal_formula *) obj[1])->to_string() + ")";
  else if (op == 30)
    return "K(" + ((modal_formula *) obj[0])->to_string() + ", " +
      ((modal_formula *) obj[1])->to_string() + ")";
  else if (op == 31)
    return "GK(" + ((modal_formula *) obj[0])->to_string() + ", " +
      ((modal_formula *) obj[1])->to_string() + ")";
  else if (op == 32)
    return "GCK(" + ((modal_formula *) obj[0])->to_string() + ", " +
      ((modal_formula *) obj[1])->to_string() + ")";
  else if (op == 40)
    return "O(" + ((modal_formula *) obj[0])->to_string() + ", " +
      ((modal_formula *) obj[1])->to_string() + ")";
  else if (op == 42)
    return "DK(" + ((modal_formula *) obj[0])->to_string() + ", " +
      ((modal_formula *) obj[1])->to_string() + ")";
  else if (op == 45)
    return "(<" + ((modal_formula *) obj[0])->to_string() + ">X " +
      ((modal_formula *) obj[1])->to_string() + ")";
  else if (op == 46)
    return "(<" + ((modal_formula *) obj[0])->to_string() + ">F " +
      ((modal_formula *) obj[1])->to_string() + ")";
  else if (op == 47)
    return "(<" + ((modal_formula *) obj[0])->to_string() + ">G " +
      ((modal_formula *) obj[1])->to_string() + ")";
  else if (op == 48)
    return "<" + ((modal_formula *) obj[0])->to_string() + ">(" +
      ((modal_formula *) obj[1])->to_string() + " U " +
      ((modal_formula *) obj[2])->to_string() + ")";
  else if (op == 50)
    return "(A " + ((modal_formula *) obj[0])->to_string() + ")";
  else if (op == 51)
    return "(E " + ((modal_formula *) obj[0])->to_string() + ")";
  else if (op == 61)
    return "(G " + ((modal_formula *) obj[0])->to_string() + ")";
  else if (op == 62)
    return "(F " + ((modal_formula *) obj[0])->to_string() + ")";
  else if (op == 63)
    return "(X " + ((modal_formula *) obj[0])->to_string() + ")";
  else if (op == 64)
    return "(" + ((modal_formula *) obj[0])->to_string() + " U " +
      ((modal_formula *) obj[1])->to_string() + ")";
  else {
    cout << " error: toString() called on op " << op << " which we don't know "
         << "how to process" << endl;
    exit(1);
  }
}

bool
modal_formula::check_atomic_proposition(unsigned char type)
{
  // type=0: atomic proposition, type=1: agent, type=2: group, type=3: agent or group
  bool b1, b2, b3;
  switch (op) {
  case 1:     // AND
  case 2:     // OR
  case 4:     // IMPLIES
  case 16:      // AU
  case 17:      // EU
  case 64:      // LTL/CTL* path U
    b1 = ((modal_formula *) obj[0])->check_atomic_proposition(0);
    b2 = ((modal_formula *) obj[1])->check_atomic_proposition(0);
    return (b1 && b2);
  case 3:     // NOT
  case 10:      // AG
  case 11:      // EG
  case 12:      // AX
  case 13:      // EX
  case 14:      // AF
  case 15:      // EF
  case 50:      // A
  case 51:      // E
  case 61:      // LTL/CTL* path F
  case 62:      // LTL/CTL* path G
  case 63:      // LTL/CTL* path X
    return ((modal_formula *) obj[0])->check_atomic_proposition(0);
  case 30:      // K
    b1 = ((modal_formula *) obj[0])->check_atomic_proposition(1);
    b2 = ((modal_formula *) obj[1])->check_atomic_proposition(0);
    return (b1 && b2);
  case 40:      // O -- Does it allow a group name to appear? 
    b1 = ((modal_formula *) obj[0])->check_atomic_proposition(1);
    b2 = ((modal_formula *) obj[1])->check_atomic_proposition(0);
    return (b1 && b2);
  case 31:      // GK
  case 32:      // GCK
  case 42:      // DK
  case 45:      // ATL X
  case 46:      // ATL F
  case 47:      // ATL G
    b1 = ((modal_formula *) obj[0])->check_atomic_proposition(2);
    b2 = ((modal_formula *) obj[1])->check_atomic_proposition(0);
    return (b1 && b2);
  case 48:      // ATL U
    b1 = ((modal_formula *) obj[0])->check_atomic_proposition(2);
    b2 = ((modal_formula *) obj[1])->check_atomic_proposition(0);
    b3 = ((modal_formula *) obj[2])->check_atomic_proposition(0);
    return (b1 && b2 && b3);
  case 0:     // A leaf node
    {
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
  case 5: // True
    {
      return true;      
    }
  }
  return false;
}

BDD
modal_formula::check_formula(bdd_parameters * para)
{
  BDD result, rel, af, phi1, phi2;
  string name, name1;
  Object *id;

  switch (op) {
  case 0:{      // leaf
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
    result = ((modal_formula *) obj[0])->check_formula(para) *
      ((modal_formula *) obj[1])->check_formula(para);
    break;
  case 2:     // OR
    result = ((modal_formula *) obj[0])->check_formula(para) +
      ((modal_formula *) obj[1])->check_formula(para);
    break;
  case 3:     // NOT
    result = !((modal_formula *) obj[0])->check_formula(para);
    break;
  case 4:     // IMPLIES
    {
      BDD res1 = !(((modal_formula *) obj[0])->check_formula(para)) * (*para->reach);
      BDD res2 = ((modal_formula *) obj[1])->check_formula(para);
      result = res1 + res2;
      break;
    }
  case 5:       // True
    {
      result = para->bddmgr->bddOne();
      break;
    }
  case 10:      // AG p = !EF !p
    phi1 = (!((modal_formula *) obj[0])->check_formula(para)) * (*para->reach);
    result = !check_EF(phi1, para);
    break;
  case 11:      // EG 
    phi1 = ((modal_formula *) obj[0])->check_formula(para);
    result = check_EG(phi1, para);
    break;
  case 12:      // AX p = ! EX !p
    phi1 = (!((modal_formula *) obj[0])->check_formula(para)) * (*para->reach);
    result = !check_EX(phi1, para);
    break;
  case 13:      // EX
    phi1 = ((modal_formula *) obj[0])->check_formula(para);
    result = check_EX(phi1, para);
    break;
  case 14:      // AF p = !EG !p
    phi1 = (!((modal_formula *) obj[0])->check_formula(para)) * (*para->reach);
    result = !check_EG(phi1, para);
    break;
  case 15:      // EF p = p \lor EX EF p
    phi1 = ((modal_formula *) obj[0])->check_formula(para);
    result = check_EF(phi1, para);
    break;
  case 16:      // AU (see check_AU)
    phi1 = ((modal_formula *) obj[0])->check_formula(para);
    phi2 = ((modal_formula *) obj[1])->check_formula(para);
    result = check_AU(phi1, phi2, para);
    break;
  case 17:      // EU
    phi1 = ((modal_formula *) obj[0])->check_formula(para);
    phi2 = ((modal_formula *) obj[1])->check_formula(para);
    result = check_EU(phi1, phi2, para);
    break;
  case 30:      // K
    {
      id = ((modal_formula *) obj[0])->get_operand(0);
      name = ((atomic_proposition *) id)->get_proposition();
      af = !((modal_formula *) obj[1])->check_formula(para) * (*para->reach);
      result = (*para->reach) - get_nK_states(&af, name, para);
      break;
    }
  case 31:      // Everybody knows
    id = ((modal_formula *) obj[0])->get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    af = ((modal_formula *) obj[1])->check_formula(para);
    result = check_GK(af, name, para);
    break;
  case 32:      // Common knowledge
    id = ((modal_formula *) obj[0])->get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    af = ((modal_formula *) obj[1])->check_formula(para);
    result = check_GCK(af, name, para);
    break;
  case 40:      // O
    id = ((modal_formula *) obj[0])->get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    af = !((modal_formula *) obj[1])->check_formula(para) * (*para->reach);
    result =
      !check_nO(af, name, para);
    break;
  case 42:      // Distributed knowledge
    id = ((modal_formula *) obj[0])->get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    af = ((modal_formula *) obj[1])->check_formula(para);
    result = check_DK(((modal_formula *) obj[1])->check_formula(para),
                      name, para);
    break;
  case 45:      // ATL operator X
    if(options["nobddcache"] == 0) {
      name1 = to_string();
      if (para->BDD_cache->find(name1) != para->BDD_cache->end())
        return ((*para->BDD_cache)[name1]);
    }

    id = ((modal_formula *) obj[0])->get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    phi1 = ((modal_formula *) obj[1])->check_formula(para);

    if(options["ATLsemantics"] == 0) { // original (semi-fo semantics)
      result = check_ATLX(phi1, name, para);
    } else { 
      // new semantics defined in "Reasoning about Strategies under Partial 
      // Observability and Fairness Constraints", Busard, Pecheur, Qu, 
      // Raimondi, 2013
      
      BDD fair_gamma = check_fair_gamma_FO(name, para);
      BDD nfair_gamma = check_nfair_gamma_FO(name, para);

      if(!is_fairness->empty()) { 
        // full observability semantics
        result = *para->reach - check_ATLX_negation(fair_gamma - phi1, name, para);
        if(options["debug"] == 1) {
          BDD result1 = check_ATLX(phi1+nfair_gamma, name, para);
          if(result != result1) {
            cout << "result: ";
            result.print(para->v->size(), 2);
            cout << "result1: ";
            result1.print(para->v->size(), 2);
          } else {
            cout << "Good news: result == result1" << endl;
          }
        }
      } else
        result = check_ATLX(phi1, name, para);

      if(options["ATLsemantics"] == 2) { // partial observable semantics
        BDD result_fair = result; // * fair_gamma;            
        BDD fo_strat = check_suc_strat(result_fair, phi1/* * fair_gamma*/, name, para) * fair_gamma;
  
        result = generate_uniform_strategies(para->bddmgr->bddOne(), phi1, op, fo_strat, name, nfair_gamma, para);
      } 
      
    }
    if(options["nobddcache"] == 0)
      (*para->BDD_cache)[name1] = result;
    break;
  case 46:      // ATL operator F
    if(options["nobddcache"] == 0) {
      name1 = to_string();
      if (para->BDD_cache->find(name1) != para->BDD_cache->end())
        return ((*para->BDD_cache)[name1]);
    }

    id = ((modal_formula *) obj[0])->get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    phi1 = ((modal_formula *) obj[1])->check_formula(para);

    if(options["ATLsemantics"] == 0) { // original (semi-fo semantics)
      if(options["debug"] == 1) {
        cout << "fair_reach: ";
        para->reach->print(para->v->size(), 1);
      }
      result = check_ATLU(para->bddmgr->bddOne(), phi1, name, para);
      if(options["debug"] == 1) {
        cout << "ATLF result: ";
        result.print(para->v->size(), 2);
      }
    } else {
      // new semantics defined in "Reasoning about Strategies under Partial 
      // Observability and Fairness Constraints", Busard, Pecheur, Qu, 
      // Raimondi, 2013
      
      BDD fair_gamma = check_fair_gamma_FO(name, para);
      BDD nfair_gamma = check_nfair_gamma_FO(name, para);

      if(!is_fairness->empty()) { 
        // full observable semantics
        result = *para->reach - check_ATLG_negation(fair_gamma - phi1, name, para);
        if(options["debug"] == 1) {
          BDD result1 = check_ATLU_fair_fo(para->bddmgr->bddOne(), phi1, nfair_gamma, name, para);
        } 
      } else
        result = check_ATLU(para->bddmgr->bddOne(), phi1, name, para);

      if(options["ATLsemantics"] == 2) { // partial observable semantics
        BDD result_fair = (result - phi1); // * fair_gamma;           
        BDD fo_strat = check_suc_strat(result_fair, result/* * fair_gamma*/, name, para) * fair_gamma;
        if(options["debug"] == 1) {
          BDD fo_strat1 = !is_fairness->empty() ? check_ATLU_fair_po(para->bddmgr->bddOne(), phi1, nfair_gamma, name, para):
            check_ATLU_po(para->bddmgr->bddOne(), phi1, name, para);
          fo_strat1 *= result_fair;

          if(fo_strat1 != fo_strat)
            cout << "ATTENTION: fo_strat1 != fo_strat" << endl;
        }
        // recursively split <state, action> pair to get uniform strategies
        result = generate_uniform_strategies(para->bddmgr->bddOne(), phi1, op, fo_strat, name, nfair_gamma, para);
				if(options["debug"] == 1) {
					cout << "ATLF result: ";
					print_states(result, *(para->v), para->bddmgr);
				}
      } 
      
    }
    if(options["nobddcache"] == 0)
      (*para->BDD_cache)[name1] = result;
    break;
  case 47:      // ATL operator G
    if(options["nobddcache"] == 0) {
      name1 = to_string();
      if (para->BDD_cache->find(name1) != para->BDD_cache->end())
        return ((*para->BDD_cache)[name1]);
    }

    id = ((modal_formula *) obj[0])->get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    phi1 = ((modal_formula *) obj[1])->check_formula(para);

    if(options["ATLsemantics"] == 0) { // original (semi-fo semantics)
      result = check_ATLG(phi1, name, para);
      if(options["debug"] == 1) {
        cout << "ATLG result: ";
        result.print(para->v->size(), 1);
      }
    } else {
      // new semantics defined in "Reasoning about Strategies under Partial 
      // Observability and Fairness Constraints", Busard, Pecheur, Qu, 
      // Raimondi, 2013
      
      BDD fair_gamma = check_fair_gamma_FO(name, para);
      BDD nfair_gamma = check_nfair_gamma_FO(name, para);

      if(!is_fairness->empty()) { 
        // full observable semantics
        result = *para->reach - check_ATLF_negation(*para->reach - phi1, name, para);
        if(options["debug"] == 1) {
          BDD result1 = check_ATLG_fair_fo(phi1, nfair_gamma, name, para);
          if(result != result1) {
            cout << "result: ";
            result.print(para->v->size(), 2);
            cout << "result1: ";
            result1.print(para->v->size(), 2);
          } else {
            cout << "Good news: result == result1" << endl;
          }
        }
      } else
        result = check_ATLG(phi1, name, para);

      if(options["ATLsemantics"] == 2) { // partial observable semantics
				BDD result_fair = result; // * fair_gamma;           
        BDD fo_strat = check_suc_strat(result_fair, result/* * fair_gamma*/, name, para) * fair_gamma;
        if(options["debug"] == 1) {
          BDD fo_strat1 = !is_fairness->empty() ? check_ATLU_fair_po(para->bddmgr->bddOne(), phi1, nfair_gamma, name, para):
            check_ATLU_po(para->bddmgr->bddOne(), phi1, name, para);
          fo_strat1 *= result_fair;

          if(fo_strat1 != fo_strat)
            cout << "ATTENTION: fo_strat1 != fo_strat" << endl;
        }
        // recursively split <state, action> pair to get uniform strategies
        result = generate_uniform_strategies(para->bddmgr->bddOne(), phi1, op, fo_strat, name, nfair_gamma, para);
      } 
      
    }
    if(options["nobddcache"] == 0)
      (*para->BDD_cache)[name1] = result;
    break;
  case 48:      // ATL operator U
    if(options["nobddcache"] == 0) {
      name1 = to_string();
      if (para->BDD_cache->find(name1) != para->BDD_cache->end())
        return ((*para->BDD_cache)[name1]);
    }

    id = ((modal_formula *) obj[0])->get_operand(0);
    name = ((atomic_proposition *) id)->get_proposition();
    phi1 = ((modal_formula *) obj[1])->check_formula(para);
    phi2 = ((modal_formula *) obj[2])->check_formula(para);

    if(options["ATLsemantics"] == 0) { // original (semi-fo semantics)
      result = check_ATLU(phi1, phi2, name, para);
    } else {
      // new semantics defined in "Reasoning about Strategies under Partial 
      // Observability and Fairness Constraints", Busard, Pecheur, Qu, 
      // Raimondi, 2013
      
      BDD fair_gamma = check_fair_gamma_FO(name, para);
      BDD nfair_gamma = check_nfair_gamma_FO(name, para);

      if(!is_fairness->empty()) { 
        // full observable semantics
        result = *para->reach - check_ATLW_negation((*para->reach - phi2), 
                                              (*para->reach - phi1) * (*para->reach - phi2) * fair_gamma, name, para);
        if(options["debug"] == 1) {
          BDD result1 = check_ATLU_fair_fo(phi1, phi2, nfair_gamma, name, para);
          if(result != result1) {
            cout << "result: ";
            result.print(para->v->size(), 2);
            cout << "result1: ";
            result1.print(para->v->size(), 2);
          } else {
            cout << "Good news: result == result1" << endl;
          }
        }
      } else
        result = check_ATLU(phi1, phi2, name, para);
  
      if(options["ATLsemantics"] == 2) { // partial observable semantics
				BDD result_fair = (result - phi2); // * fair_gamma;           
        BDD fo_strat = check_suc_strat(result_fair, result/* * fair_gamma*/, name, para) * fair_gamma;
        if(options["debug"] == 1) {
          BDD fo_strat1 = !is_fairness->empty() ? check_ATLU_fair_po(phi1, phi2, nfair_gamma, name, para):
            check_ATLU_po(phi1, phi2, name, para);
          fo_strat1 *= result_fair;

          if(fo_strat1 != fo_strat) {
            cout << "ATTENTION: fo_strat1 != fo_strat" << endl;
						cout << "fo_strat: ";
            fo_strat.print(para->v->size() + para->a->size(), 2);
            cout << "fo_strat1: ";
            fo_strat1.print(para->v->size() + para->a->size(), 2);
						cout << "use fo_strat1" << endl;
						fo_strat = fo_strat1;
					}
        }
        // recursively split <state, action> pair to get uniform strategies
        result = generate_uniform_strategies(phi1, phi2, op, fo_strat, name, nfair_gamma, para);
      } 
    if(options["nobddcache"] == 0)
      (*para->BDD_cache)[name1] = result;
    break;
    }
  case 50:      // A f = !E! f
    {
      modal_formula* negation = new modal_formula(3, new modal_formula(51, new modal_formula(3, (modal_formula*) obj[0])));
      result = negation->check_formula(para);
      break;
    }
  case 51:      // E path
  {
    // Performs the construction of a tableau and executes CTL model checking with fairness
    // on the product of said tableau and the original model
    // See: "Another Look at LTL Model Checking", Clarke, Grumberg & Hamaguchi 1994.

    para->calReachRT = true; // Force recalculation of the cached transition relation to account for the tableau

    if (((modal_formula *) obj[0])->is_NonTemporal()) {
      // Optimisation: no need to compute non-temporal formulae over states
      return ((modal_formula *) obj[0])->check_formula(para);
    }

    // Remove Gs
    modal_formula* new_formula = remove_path_gs()->push_negations(0);
    if (options["debug"] >= 1) {
      cout << "removing Gs: " << new_formula->to_string() << endl;
    }

    // Check for nested epistemic modalities or path quantifiers, and check their inner LTL specifications first.
    map<modal_formula*, BDD> epistemic_path_values;
    ((modal_formula *) new_formula->obj[0])->compute_epistemic_path_subformulae(para, &epistemic_path_values);

    // Determine the elementary formulas
    set<modal_formula*> elementary_formulas = *((modal_formula *) new_formula->obj[0])->get_elementary_formulas();

    // Allocate new state variables for the elementary formulas
    int old_bdd_size = para->bddmgr->ReadSize();
    int offset = 0;
    map<modal_formula*, int> index_map;

    for (set<modal_formula*>::iterator it = elementary_formulas.begin();
         it != elementary_formulas.end(); ++it, ++offset) {
      modal_formula* formula = *it;
      if (options["debug"] >= 1)
        cout << "found elementary formula:" << formula->to_string() << endl;

      vector<BDD>* prestates = para->v;
      vector<BDD>* poststates = para->pv;

      prestates->push_back(para->bddmgr->bddVar(old_bdd_size + offset));
      poststates->push_back(para->bddmgr->bddVar(old_bdd_size + elementary_formulas.size() + offset));
      index_map[formula] = old_bdd_size + offset;
    }

    // Compute transition relation for the tableau
    BDD tableau = new_formula->build_path_tableau(para, index_map);
    if (options["debug"] >= 1) {
      cout << "LTL tableau:" << endl;
      tableau.PrintCover();
      cout << "End LTL tableau." << endl;
    }

    // Consistency check
    BDD rules = new_formula->build_consistency_rules(para, index_map, epistemic_path_values);
    tableau *= rules;

    // Set up fairness constraints.
    vector<BDD> fairness_bdds;
    ((modal_formula *) new_formula->obj[0])->get_path_fairness_constraints(para, index_map, &fairness_bdds);

    if (options["debug"] >= 1) {
      cout << "Fairness constraints: " << endl;
      for (vector<BDD>::iterator it = fairness_bdds.begin(); it != fairness_bdds.end(); ++it) {
        it->PrintCover();
      }
    }

    // Compose tableau and agents
    para->vRT->push_back(tableau);
    agents->push_back(NULL); // force the utility methods to look at the new element of vRT

    // Compute reachable states again
    BDD fintab_reachables = check_EX(para->bddmgr->bddOne(), para);
    BDD prev = para->bddmgr->bddOne();
    while (prev != fintab_reachables) {
      prev = fintab_reachables;
      fintab_reachables = check_EX(fintab_reachables, para);
    }
    fairness_bdds.push_back(fintab_reachables);

    // Compute EG True given eventualities are satisfied
    BDD result_fair = check_EG_fair(para->bddmgr->bddOne(), para, fairness_bdds);

    // if state satisfies EG True and f, then there is an infinite path with f
    BDD f_states = (((modal_formula *) new_formula->obj[0])->check_path_sat(para, index_map, 0)) * rules;
    if (options["debug"] >= 1) {
      cout << "BDD for subformula satisfiability yields:" << endl;
      result_fair.PrintCover();
    }
    result_fair *= f_states;

    // Find the *states* satisfying E f
    for (size_t i = 0; i < 2 * elementary_formulas.size(); ++i) {
      result_fair = result_fair.ExistAbstract(para->bddmgr->bddVar(old_bdd_size + i));
    }

    // And we're... done!
    result = result_fair;
    if (options["debug"] >= 1) {
      cout << "BDD for E f" << endl;
      result.PrintCover();
    }

    // Cleanup, if we aren't generating counterexamples (if we are, then we can only do this later!)
    para->vRT->pop_back();
    agents->pop_back();
    for (size_t i = 0; i < elementary_formulas.size(); ++i) {
      para->v->pop_back();
      para->pv->pop_back();
    }
    para->calReachRT = true; // Force recalculation - the cache can be very weird
    break;
  }
  case 61:      // LTL/CTL* path G
  case 62:      // LTL/CTL* path F
  case 63:      // LTL/CTL* path X
  case 64:      // LTL/CTL* path U
    cout << "Error - check_formula() should never be called directly on a path modality!" << endl;
    cout << "Please contact MCMAS developers. The offending formula was: " << to_string() << endl;
    exit(1);
  }
  return result * (*para->reach);
}

/**
 * Gets the elementary formulas associated with an LTL formula.
 * (see the Clarke, Grumberg and Hamaguchi paper "Another Look at LTL Model Checking")
 * It is the responsibility of the caller to free memory accordingly.
 * We adapt the construction to deal with CTL*K, by treating top-level epistemic and path subformulae as atomic
 * propositions. Their truth values are calculated separately and are used when building the consistency rules.
 */
set<modal_formula*>*
modal_formula::get_elementary_formulas() {
  set<modal_formula*>* elementary_formulas = new set<modal_formula*>();
  switch (op) {
    case 0: // atom
    case 30: // K
    case 31: // GK
    case 32: // Common knowledge
    case 42: // Distributed knowledge
    case 50: // A
    case 51: // E
      {
        elementary_formulas->insert(this);
        break;
      }
    case 1: // and
    case 2: // or
    case 4: // implies
      {
        set<modal_formula*>* lhs_elems = ((modal_formula *) obj[0])->get_elementary_formulas();
        set<modal_formula*>* rhs_elems = ((modal_formula *) obj[1])->get_elementary_formulas();
        elementary_formulas->insert(lhs_elems->begin(), lhs_elems->end());
        elementary_formulas->insert(rhs_elems->begin(), rhs_elems->end());
        break;
      }
    case 3: // not
      {
        set<modal_formula*>* child_elems = ((modal_formula *) obj[0])->get_elementary_formulas();
        elementary_formulas->insert(child_elems->begin(), child_elems->end());
        break;
      }
    case 62: // F p -> {X(F p)} union el(p) - adaptation of Clarke paper p.5
      {
        set<modal_formula*>* child_elems = ((modal_formula *) obj[0])->get_elementary_formulas();
        elementary_formulas->insert(child_elems->begin(), child_elems->end());

        modal_formula* next_this = new modal_formula(63, this);
        elementary_formulas->insert(next_this);
        break;
      }
    case 63: // X p -> {X p} union el(p) - Clarke paper p.5
      {
        set<modal_formula*>* child_elems = ((modal_formula *) obj[0])->get_elementary_formulas();
        elementary_formulas->insert(child_elems->begin(), child_elems->end());
        elementary_formulas->insert(this);
        break;
      }
    case 64: // p U q -> {X(p U q)} union el(p) union el(q) - Clarke paper p.5
      {
        set<modal_formula*>* lhs_elems = ((modal_formula *) obj[0])->get_elementary_formulas();
        set<modal_formula*>* rhs_elems = ((modal_formula *) obj[1])->get_elementary_formulas();
        elementary_formulas->insert(lhs_elems->begin(), lhs_elems->end());
        elementary_formulas->insert(rhs_elems->begin(), rhs_elems->end());

        modal_formula* next_this = new modal_formula(63, this);
        elementary_formulas->insert(next_this);
        break;
      }
  }
  return elementary_formulas;
}

/**
 * Implements the sat function for the tableau construction (see Clarke, Grumberg and Hamaguchi for more
 * detail) with BDDs.
 */
BDD
modal_formula::check_path_sat(bdd_parameters* para,
                              const map<modal_formula*, int>& index_map,
                              int additional_offset) {
  if (index_map.find(this) != index_map.end()) {
    // This is an elementary formula.
    return para->bddmgr->bddVar(index_map.find(this)->second + additional_offset);
  }
  // Not an elementary formula
  string target = string("(X ") + to_string() + ")";
  int offset = -1;
  switch (op) {
    case 1: // and
      return ((modal_formula *) obj[0])->check_path_sat(para, index_map, additional_offset) *
             ((modal_formula *) obj[1])->check_path_sat(para, index_map, additional_offset);
    case 2: // or
      return ((modal_formula *) obj[0])->check_path_sat(para, index_map, additional_offset) +
             ((modal_formula *) obj[1])->check_path_sat(para, index_map, additional_offset);
    case 3: // not
      return !((modal_formula *) obj[0])->check_path_sat(para, index_map, additional_offset);
    case 4: // implies: A -> B = \not A or B
      return (!(((modal_formula *) obj[0])->check_path_sat(para, index_map, additional_offset))) +
             ((modal_formula *) obj[1])->check_path_sat(para, index_map, additional_offset);
    case 62: // F: F p = (true U p), so sat(F p) = sat(true U p) = sat(p) U sat(X(true U p)) = sat(p) U sat(X(F p))
      for (map<modal_formula*, int>::const_iterator it = index_map.begin(); it != index_map.end(); ++it) {
        if (it->first->to_string() == target) {
          offset = it->second;
          break;
        }
      }
      return ((modal_formula *) obj[0])->check_path_sat(para, index_map, additional_offset)
             + para->bddmgr->bddVar(offset + additional_offset);
    case 64: // U
      for (map<modal_formula*, int>::const_iterator it = index_map.begin(); it != index_map.end(); ++it) {
        if (it->first->to_string() == target) {
          offset = it->second;
          break;
        }
      }
      return ((modal_formula *) obj[1])->check_path_sat(para, index_map, additional_offset) +
              (((modal_formula *) obj[0])->check_path_sat(para, index_map, additional_offset)
               * para->bddmgr->bddVar(offset + additional_offset));
  }
  cout << "An error occurred concerning unimplemented functionality in check_path_sat. " << "(op " << (int) op << ", "
       << "formula " << to_string() << "). Please contact MCMAS developers." << endl;
  exit(1);
  return para->bddmgr->bddOne();
}

/**
 * Returns a BDD for the transition relation for the tableau by enforcing if and only if constraints between elementary
 * formulas X p and the underlying formulas p.
 */
BDD
modal_formula::build_path_tableau(bdd_parameters* para,
                                 const map<modal_formula*, int>& index_map) {
  BDD result_bdd = para->bddmgr->bddOne();
  int num_elementary_formulas = index_map.size();
  for (map<modal_formula*, int>::const_iterator it = index_map.begin(); it != index_map.end(); ++it) {
    if(it->first->op == 63) {
      // This is an elementary formula beginning with X, which we need to consider.
      // state satisfies X g -> next state satisfies g
      BDD x_g = it->first->check_path_sat(para, index_map, 0);
      BDD next_g = ((modal_formula *) it->first->obj[0])->check_path_sat(para, index_map, num_elementary_formulas);
      result_bdd *= (!x_g + next_g);
      // and vice versa
      result_bdd *= (x_g + !next_g);
    }
  }
  return result_bdd;
}

/**
 * Returns a BDD for the set of consistency rules linking variables in the tableau (which are typically expressed
 * in the Evaluation section, but are not necessarily BDD variables) with actual BDD variables in the model.
 */
BDD
modal_formula::build_consistency_rules(bdd_parameters* para,
                                       const map<modal_formula *, int>& index_map,
                                       map<modal_formula *, BDD> epistemic_path_values) {
  BDD result_bdd = para->bddmgr->bddOne();
  for (map<modal_formula*, int>::const_iterator it = index_map.begin(); it != index_map.end(); ++it) {
    BDD formula_states;
    switch (it->first->op) {
      case 0: // Atomic proposition
      {
        formula_states = it->first->check_formula(para);
        break;
      }
      case 30: // K
      case 31: // GK
      case 32: // Common knowledge
      case 42: // Distributed knowledge
      case 50: // A
      case 51: // E
      {
        formula_states = epistemic_path_values[it->first];
        break;
      }
      default: // Not something we're interested in
      {
        continue;
      }
    }
    // We need to check under what conditions the elementary formula actually holds.

    // Add if-and-only-if constraint between the tableau variable and its meaning in the underlying BDD.
    result_bdd *= (para->bddmgr->bddVar(it->second) * formula_states)
                  + (!(para->bddmgr->bddVar(it->second)) * !formula_states);
  }
  return result_bdd;
}

/**
 * Populates fairness_bdds with BDDs corresponding to the fairness constraints that need to be checked along with
 * EG T, to ensure that all eventuality constraints are satisfied.
 */
void
modal_formula::get_path_fairness_constraints(bdd_parameters* para,
                                            const map<modal_formula*, int>& index_map,
                                            vector<BDD>* fairness_bdds) {
  switch (op) {
    case 0: // elementary formula
    case 50: // A
    case 51: // E
      return;
    case 1: // and
    case 2: // or
    case 4: // implies
      ((modal_formula *) obj[0])->get_path_fairness_constraints(para, index_map, fairness_bdds);
      ((modal_formula *) obj[1])->get_path_fairness_constraints(para, index_map, fairness_bdds);
      return;
    case 3: // not
    case 63: // X
      ((modal_formula *) obj[0])->get_path_fairness_constraints(para, index_map, fairness_bdds);
      return;
    case 62: // F p = (true U p)
    {
      modal_formula negated_formula = modal_formula(3, this);
      modal_formula sat_formula = modal_formula(2, &negated_formula, ((modal_formula *) obj[0]));
      fairness_bdds->push_back(sat_formula.check_path_sat(para, index_map, 0));
      ((modal_formula *) obj[0])->get_path_fairness_constraints(para, index_map, fairness_bdds);
      return;
    }
    case 64: // U
    {
      modal_formula negated_formula = modal_formula(3, this);
      modal_formula sat_formula = modal_formula(2, &negated_formula, ((modal_formula *) obj[1]));
      fairness_bdds->push_back(sat_formula.check_path_sat(para, index_map, 0));
      ((modal_formula *) obj[0])->get_path_fairness_constraints(para, index_map, fairness_bdds);
      ((modal_formula *) obj[1])->get_path_fairness_constraints(para, index_map, fairness_bdds);
      return;
    }
  }
  return;
}

/**
 * Rewrite Gs in path formulae as !F! as it is easier to work with F as opposed to G (e.g. for fairness constraints)
 */
modal_formula*
modal_formula::remove_path_gs() {
  switch(op) {
    case 0: // elementary formula
      return new modal_formula(op, (modal_formula *) obj[0]);
    case 1: // binary ops
    case 2:
    case 4:
    case 64: // U
    {
      modal_formula* temp_obj_0 = ((modal_formula *) obj[0])->remove_path_gs();
      modal_formula* temp_obj_1 = ((modal_formula *) obj[1])->remove_path_gs();
      return new modal_formula(op, temp_obj_0, temp_obj_1);
    }
    case 3: // not
    case 50: // A
    case 51: // E
    case 62: // F
    case 63: // X
    {
      modal_formula* temp_obj_0 = ((modal_formula *) obj[0])->remove_path_gs();
      return new modal_formula(op, temp_obj_0);
    }
    case 30: // K
    case 31: // GK
    case 32: // Common knowledge
    case 42: // Distributed knowledge
    {
      modal_formula* temp_obj_1 = ((modal_formula *) obj[1])->remove_path_gs();
      return new modal_formula(op, (modal_formula *) obj[0], temp_obj_1);
    }
    case 61: // G = !F!
    {
      modal_formula* child = ((modal_formula *) obj[0])->remove_path_gs();
      modal_formula* inner_not = new modal_formula(3, child);
      modal_formula* f = new modal_formula(62, inner_not);
      modal_formula* outer_not = new modal_formula(3, f);
      return outer_not;
    }
  }
}

/**
 * Computes BDDs for the states in which all top-level epistemic and path subformulae of the current CTL*K path formula
 * holds, and populates the result_map with the relevant values.
 */
void
modal_formula::compute_epistemic_path_subformulae(bdd_parameters* para, map<modal_formula*, BDD>* result_map) {
  switch(op) {
    case 0: // atomic proposition
      return;
    case 1: // binary ops
    case 2:
    case 4:
    case 64: // U
    {
      ((modal_formula *) obj[0])->compute_epistemic_path_subformulae(para, result_map);
      ((modal_formula *) obj[1])->compute_epistemic_path_subformulae(para, result_map);
      return;
    }
    case 3: // not
    case 61: // G
    case 62: // F
    case 63: // X
    {
      ((modal_formula *) obj[0])->compute_epistemic_path_subformulae(para, result_map);
      return;
    }
    case 30: // K
    case 31: // GK
    case 32: // Common knowledge
    case 42: // Distributed knowledge
    case 50: // A
    case 51: // E
    {
      result_map->insert(make_pair(this, check_formula(para)));
      return;
    }
  }
}

modal_formula *
modal_formula::push_negations(unsigned int level)
{
  switch (op) {
  case 0:     // leaf
    {
      return this;
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
        return this;
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
        case 50:
        {
          // ! A f = E ! f
          modal_formula *m1 =
            new modal_formula(3,
                              (modal_formula *) nextformula->
                              get_operand(0));
          modal_formula *result =
            new modal_formula(51, m1->push_negations(level + 1));
          return result;
          break;
        }
        case 51:
        {
          // ! E f = A ! f
          modal_formula *m1 =
            new modal_formula(3,
                              (modal_formula *) nextformula->
                              get_operand(0));
          modal_formula *result =
            new modal_formula(50, m1->push_negations(level + 1));
          return result;
          break;
        }
        case 61:
        case 62:
        case 63:
        {
          // The main purpose of push negation for these is to get rid of !!s which cause tableau weirdness.
          modal_formula *m1 = (modal_formula *) nextformula->get_operand(0);
          modal_formula *result =
                  new modal_formula(3, new modal_formula(nextop, m1->push_negations(level + 1)));
          return result;
          break;
        }
        case 64:
        {
          // The main purpose of push negation for these is to get rid of !!s which cause tableau weirdness.
          modal_formula *m1 = (modal_formula *) nextformula->get_operand(0);
          modal_formula *m2 = (modal_formula *) nextformula->get_operand(1);
          modal_formula *result = new modal_formula(3,
                  new modal_formula(nextop, m1->push_negations(level + 1),
                                    m2->push_negations(level + 1)));
          return result;
          break;
        }
        default:{
          // Nothing to do for K etc:
          // Just copy and return
          return this;
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
  case 50:
  case 51:
  case 61:
  case 62:
  case 63:
    {
      // Temporal is the first
      modal_formula *m =
        new modal_formula(op,
                          ((modal_formula *) obj[0])->push_negations(level +
                                                                     1));
      return m;
      break;
    }
  case 16:
  case 17:
  case 64:
    {
      // CTL EU and AU, LTL U, binary operators:
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
  default:
    {
      // Epistemic and deontic, ATLX, ATLG, ATLF, is the second
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
  case 50: // we now support LTL and CTL*'s A something.
    return true;
  case 45:      // ATL 
  case 46:
  case 47:
  case 48:
    if (options["atlcex"] > 0)
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

    // We also check CTL*'s E-formulas
  case 51:
    return true;
  }
  return false;
}

/** return true if there is no temporal operator in the formula.
 ** do not check the formula inside epistemic operators */
bool
modal_formula::is_NonTemporal()
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
              is_NonTemporal() & ((modal_formula *) obj[1])->is_NonTemporal());
    }
  case 3:     // NOT
    {
      return ((modal_formula *) obj[0])->is_NonTemporal();
    }
  }
  return false;
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
modal_formula::build_cex(BDD * state, unsigned int index, bdd_parameters * para, 
                         vector< vector< int >*>* countex, map< int, BDD * >* idbdd, 
                         vector< vector< transition * >*>* cextr)
{
  vector< BDD * >tmpresult; // a vector to store the states of the witness
  vector< int >desc;    // This is a vector of state id (see global variables countex and idbdd)
  vector< transition * >desctr; // This is a vector of transitions (see golbal var cextr)

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
      bool r1 = ((modal_formula *) obj[0])->build_cex(state, index, para, countex, idbdd, cextr);
      if (!r1)
        return false;
      bool r2 = ((modal_formula *) obj[1])->build_cex(state, index, para, countex, idbdd, cextr);
      if (!r2)
        return false;
      return true;
      break;
    }
  case 2:     // OR
    {
      bool r1;
      modal_formula *left = ((modal_formula *) obj[1]);
      BDD res = left->check_formula(para);

      if ((*state) <= res) {
        r1 = left->build_cex(state, index, para, countex, idbdd, cextr);
        if (!r1)
          return false;
      } else {
        modal_formula *right = ((modal_formula *) obj[0]);
        r1 = right->build_cex(state, index, para, countex, idbdd, cextr);
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
        BDD last = check_formula(para); // the last state of fixpoint computation
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
          reachablefromlast *= (*para->reach);
    
          BDD abdd = reachablefromlast * last;
          if (abdd == para->bddmgr->bddZero()) {
            return false;
          }
    
          Q = abdd * T;   // if this is not false, we found a loop
          if (Q == para->bddmgr->bddZero()) {
            BDD curstate = abdd.PickOneMinterm(*para->v);
      
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
        // cout << "start from" << endl;
        // print_state(*state, *(para->v));
        vector< vector < BDD* >* > Qh;
        BDD f = ((modal_formula *) obj[0])->check_formula(para);
        BDD last = check_EG_fair(f, para);

        for(unsigned int j=0; j<is_fairness->size(); j++) {
          BDD hf = (*is_fairness)[j]->get_bdd_representation();
          vector< BDD* >* qh = new vector< BDD* >();
          check_EU_Qh(last, last * hf, para, qh);
          Qh.push_back(qh);
        }


        // cout << "Number of qh = " << Qh.size() << endl;
        //   for(unsigned int i=0; i<Qh.size(); i++) {
        //   cout << "qh[" << i << "] = " << Qh[i]->size() << endl;
        //   for(unsigned int j=0; j<Qh[i]->size(); j++) {
        //   cout << "Qh[" << i << "][" << j << "]:";
        //   (*Qh[i])[j]->print(2, 2);
        //   }
        //   }
  
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
            // cout << "current result: " << endl;
            // tmpresult.back()->PrintCover();
            BDD reachablefromlast = compute_successors(tmpresult.back(), para->bddmgr, para->vRT, para->a, para->v, para->pv) * (*para->reach);
            // cout << "  reachablefromlast:";
            // reachablefromlast.print(2, 2);
            BDD successors = reachablefromlast * last;
            // cout << "  successors:";
            // successors.print(2, 2);
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
                    t = tmp.PickOneMinterm(*para->v);
                    // cout << "pick" << endl;
                    // t.PrintCover();
                    // cout << "endpick" << endl;

                    if(count == 0) {
                      //predecessors = check_EU(last, t, para);
                      //loopbegin = t;
                      loopstart = tmpresult.size();
                    }

                    // print_state(t, *(para->v));
                    count++;
        
                    // cout << "find a fair state: i = " << i << ", j = " << j << ", count = " << count << endl;

                    break;
                  }
                }
              }
              // Dead code?
              if(j<is_fairness->size())
                break;
              i++;
            }
            if(!restart) {
              // choose fairness constraint j with Q_i^h
              // cout << "  compute path to fairness " << j << endl;
              tmpresult.push_back(new BDD(t));
              // cout << "  add a state to tmpresult: size = " << tmpresult.size() << endl;
              vector< BDD* >* qh = Qh[j];
              while(i > 0) {
                BDD next = compute_successors(tmpresult.back(), para->bddmgr, para->vRT, para->a, para->v, para->pv) * (*para->reach);
                next = next * last;
                next = next * *((*qh)[i-1]);
                if(next == para->bddmgr->bddZero()) {
                  cout << "find a deadlock 0: i = " << i << endl;
                  exit(0);
                }
                t = next.PickOneMinterm(*para->v);
                    // cout << "add" << endl;
                    // t.PrintCover();
                    // cout << "endadd" << endl;
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
                // cout << "compute the predecessors for closing cycle" << endl;
                // predecessors.PrintCover();
                // cout << "done" << endl;
              }
            } else {
              // cout << "cannot find a fair loop. restart the computation." << endl;
              break;
            }
          }
        } while(restart == true);

        // compute loopstart: find a path from the last state in tempresult to loopbegin
        //cout << "compute loopstart" << endl;
        //if(loopbegin != *tmpresult.back()) {
        // cout << "final" << endl;
        // for (vector<BDD*>::iterator it = tmpresult.begin(); it != tmpresult.end(); ++it)
        //   (*it)->PrintCover();
        // loopbegin.PrintCover();
        // cout << "finalend" << endl;
        if(loopbegin * *tmpresult.back() == para->bddmgr->bddZero()) {
          vector< BDD > S;
          BDD sum = loopbegin;
          BDD Y = loopbegin, X = *tmpresult.back();
          while(Y * X == para->bddmgr->bddZero()) {
            Y = predecessors * check_EX(Y, para);
            Y -= sum;
            sum += Y;
            S.push_back(Y);
            // cout << "y" << endl;
            // Y.PrintCover();
            // cout << "yend" << endl;
            if(Y == para->bddmgr->bddZero()) {
              // cout << "Find a deadlock in counterexample generation for EG under fairness. Please report it to MCMAS developers." << endl;
              // This is not necessarily wrong! It may be that we had a loop that found SCCs but cannot close the loop, *yet* the final state as built above is 
              // in a different SCC or has access to a different SCC that also happens to satisfy the same fairness constraint as the component we wanted to 
              // return to. Return to the first part of the cycle detection algorithm, using our current state...
              goto EG_start;
            }
          }
          S.pop_back();

          while(S.size() > 0) {
            X = compute_successors(&X, para->bddmgr, para->vRT, para->a, para->v, para->pv);
            X = X * S.back();
            S.pop_back();
            X = X.PickOneMinterm(*para->v);
            tmpresult.push_back(new BDD(X));
          }
          Y = compute_successors(tmpresult.back(), para->bddmgr, para->vRT, para->a, para->v, para->pv); 
          Y *= loopbegin;
          Y = Y.PickOneMinterm(*para->v);
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
                  // cout << "find a dead end. restart" << endl;
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
                Y = Y.PickOneMinterm(*para->v);
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
        if ((*(*tmpri)) <= ((modal_formula *) obj[0])->check_formula(para)) {
          if (tmpri == tmpresult.begin())
            ((modal_formula *) obj[0])->build_cex(*tmpri, index, para, countex, idbdd, cextr);
          else
            ((modal_formula *) obj[0])->build_cex(*tmpri, ++position1, para, countex, idbdd, cextr);
        }
      }
      
      return true;
    }
  case 13:      // EX
    {
      tmpresult.push_back(new BDD(*state));

      //vector< BDD * >S; // a vector to store the stages of the fixpoint computation

      BDD p = ((modal_formula *) obj[0])->check_formula(para);

      p = p.SwapVariables(*para->pv, *para->v); // The set of "next" states where p is true.

      BDD aset1 = timesRT(state, para->bddmgr, para->vRT, para->a);

      aset1 = aset1 * p;  // the set above where, additionally, p holds
      if (aset1 == para->bddmgr->bddZero())
        return false;

      aset1 = aset1.SwapVariables(*para->v, *para->pv); // swap back

      BDD curstate = aset1.PickOneMinterm(*para->v);
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

      return ((modal_formula *) obj[0])->build_cex(tmpresult[1], scount,
                                                   para, countex, idbdd, cextr);
    }
  case 15:      // EF
    {
      vector< BDD > S; // a vector to store the stages of the fixpoint computation
      BDD p = ((modal_formula *) obj[0])->check_formula(para);
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
        curstate = aset2.PickOneMinterm(*para->v);
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
                  (tmpresult.size() == 1 ? index : scount), para, countex, idbdd, cextr);
    }
  case 17:      // EU
    {
      vector< BDD >S; // a vector to store the stages of the fixpoint computation

      BDD p = ((modal_formula *) obj[0])->check_formula(para);
      BDD q = ((modal_formula *) obj[1])->check_formula(para);

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
        curstate = aset2.PickOneMinterm(*para->v);

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
            ((modal_formula *) obj[0])->check_formula(para)) {
          if (i == 0)
            ((modal_formula *) obj[0])->build_cex(tmpresult[i], index, para, countex, idbdd, cextr);
          else
            ((modal_formula *) obj[0])->build_cex(tmpresult[i], ++position1,
                                                  para, countex, idbdd, cextr);
        }
      }
      return ((modal_formula *) obj[1])->
        build_cex(tmpresult[tmpresult.size() - 1],
                  (tmpresult.size() == 1 ? index : scount), para, countex, idbdd, cextr);
    }

  case 45:{     // ATLX witness
    if(options["ATLsemantics"] > 0 || !is_fairness->empty())
      goto ATL_no_cex;
    BDD p = ((modal_formula *) obj[1])->check_formula(para);

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
      nextstate = nextstate.PickOneMinterm(*para->pv);

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
      return ((modal_formula *) obj[1])->build_cex(tmpresult[1], scount,
                                                   para, countex, idbdd, cextr);
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
        BDD successor = nextstate.PickOneMinterm(*para->pv);
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
          ((modal_formula *) obj[1])->build_cex(tmpresult[i], /* ++position1 */
                                                gi->second, para, countex, idbdd, cextr);
        }
      }

      return true;
    }
  }

  case 46:{     // ATL operator F
    if(options["ATLsemantics"] > 0 || !is_fairness->empty())
      goto ATL_no_cex;
    vector< BDD >S; // a vector to store the stages of the fixpoint computation
    BDD p = ((modal_formula *) obj[1])->check_formula(para);
    BDD tmp = para->bddmgr->bddOne();
    BDD q = p;
    BDD curstate = *state;  // the current state
    vector< BDD >tmp_actions;
    BDD freach = para->bddmgr->bddOne();
    if (!is_fairness->empty()) {
      freach = para->reach->SwapVariables(*para->v, *para->pv);
    }

    if (options["fullatl"] > 0) {
      BDD last = check_formula(para); // the last state of fixpoint computation
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
              BDD source = missed.PickOneMinterm(*para->v);
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
            BDD successor = nextstate.PickOneMinterm(*para->pv);
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
              BDD predecessor = predecessors.PickOneMinterm(*para->v);
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
            ((modal_formula *) obj[1])->build_cex(*tmpri, gi->second, para, countex, idbdd, cextr);
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
        curstate = aset1.PickOneMinterm(*para->v);
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
                  (tmpresult.size() == 1 ? index : scount), para, countex, idbdd, cextr);
    }
  }

  case 47:{     // ATL operator G
    if(options["ATLsemantics"] > 0 || !is_fairness->empty())
      goto ATL_no_cex;
    BDD p = ((modal_formula *) obj[1])->check_formula(para);
    p = p.SwapVariables(*para->v, *para->pv);
    BDD last = check_formula(para); // the last state of fixpoint computation
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
            BDD source = missed.PickOneMinterm(*para->v);
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
          BDD successor = nextstate.PickOneMinterm(*para->pv);
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
            BDD predecessor = predecessors.PickOneMinterm(*para->v);
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
          ((modal_formula *) obj[1])->build_cex(*tmpri, gi->second, para, countex, idbdd, cextr);
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
          BDD curstate = abdd.PickOneMinterm(*para->v);
          tmpresult.push_back(new BDD(curstate));
          BDD action = Exists(para->bddmgr, para->v, good_succ * curstate).PickOneMinterm(*para->a);
          tmp_actions.push_back(action);
          T = T + curstate;
        } else {
          BDD curstate = Q.PickOneMinterm(*para->v);
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
          ((modal_formula *) obj[1])->build_cex(*tmpri, index, para, countex, idbdd, cextr);
        else
          ((modal_formula *) obj[1])->build_cex(*tmpri, ++position1, para, countex, idbdd, cextr);
      }

      return true;
    }
  }

  case 48:{     // ATL operator U
    if(options["ATLsemantics"] > 0 || !is_fairness->empty())
      goto ATL_no_cex;
    vector< BDD >S; // a vector to store the stages of the fixpoint computation
    vector< BDD >tmp_actions;
    BDD p = ((modal_formula *) obj[1])->check_formula(para);
    BDD q = ((modal_formula *) obj[2])->check_formula(para);
    BDD freach = para->bddmgr->bddOne();
    if (!is_fairness->empty()) {
      freach = para->reach->SwapVariables(*para->v, *para->pv);
    }       

    if (options["fullatl"] > 0) {
      BDD last = check_formula(para); // the last state of fixpoint computation
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
              BDD source = missed.PickOneMinterm(*para->v);
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
            BDD successor = nextstate.PickOneMinterm(*para->pv);
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
              BDD predecessor = predecessors.PickOneMinterm(*para->v);
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
            ((modal_formula *) obj[1])->build_cex(*tmpri, gi->second, para, countex, idbdd, cextr);
          else
            ((modal_formula *) obj[2])->build_cex(*tmpri, gi->second, para, countex, idbdd, cextr);
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
        curstate = aset1.PickOneMinterm(*para->v);
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
            ((modal_formula *) obj[1])->check_formula(para)) {
          if (i == 0)
            ((modal_formula *) obj[1])->build_cex(tmpresult[i], index, para, countex, idbdd, cextr);
          else
            ((modal_formula *) obj[1])->build_cex(tmpresult[i], ++position1, para, countex, idbdd, cextr);
        }
      }
      return ((modal_formula *) obj[2])->
        build_cex(tmpresult[tmpresult.size() - 1], (tmpresult.size() == 1 ? index : scount), para, countex, idbdd, cextr);
    }
  }

  case 0:
  case 5:
  case 10:      // AG
  case 12:      // AX
  case 14:      // AF
  case 16:      // AU
  case 30:
  case 31:
  case 32:
  case 40:
  case 42:{
    ATL_no_cex:
    BDD p;
    if(options["nobddcache"] == 0) {
      name = to_string();
      if (para->BDD_cache->find(name) != para->BDD_cache->end())
	p = (*para->BDD_cache)[name];
      else 
	p = check_formula(para);
    } else
      p = check_formula(para);

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

  case 51: // E
  {
    // To model check E \phi, we build the tableau again, and then use the counterexample generation techniques for EG T.
    // I'd prefer if we still have the tableau around, but this would be a first experiment.

    para->calReachRT = true; // Force recalculation of the cached transition relation to account for the tableau

    // Remove Gs
    modal_formula* new_formula = remove_path_gs()->push_negations(0);

    // Check for nested epistemic modalities or path quantifiers, and check their inner LTL specifications first.
    map<modal_formula*, BDD> epistemic_path_values;
    ((modal_formula *) new_formula->obj[0])->compute_epistemic_path_subformulae(para, &epistemic_path_values);

    // Determine the elementary formulas
    set<modal_formula*> elementary_formulas = *((modal_formula *) new_formula->obj[0])->get_elementary_formulas();

    // Allocate new state variables for the elementary formulas
    int old_bdd_size = para->bddmgr->ReadSize();
    int offset = 0;
    map<modal_formula*, int> index_map;

    for (set<modal_formula*>::iterator it = elementary_formulas.begin();
         it != elementary_formulas.end(); ++it, ++offset) {
      modal_formula* formula = *it;
      if (options["debug"] >= 1)
        cout << "found elementary formula:" << formula->to_string() << endl;

      vector<BDD>* prestates = para->v;
      vector<BDD>* poststates = para->pv;

      prestates->push_back(para->bddmgr->bddVar(old_bdd_size + offset));
      poststates->push_back(para->bddmgr->bddVar(old_bdd_size + elementary_formulas.size() + offset));
      index_map[formula] = old_bdd_size + offset;
    }

    // Compute transition relation for the tableau
    BDD tableau = new_formula->build_path_tableau(para, index_map);
    if (options["debug"] >= 1) {
      cout << "LTL tableau:" << endl;
      tableau.PrintCover();
      cout << "End LTL tableau." << endl;
    }

    // Consistency check
    BDD rules = new_formula->build_consistency_rules(para, index_map, epistemic_path_values);
    tableau *= rules;

    // Set up fairness constraints.
    vector<BDD> fairness_bdds;
    ((modal_formula *) new_formula->obj[0])->get_path_fairness_constraints(para, index_map, &fairness_bdds);

    if (options["debug"] >= 1) {
      cout << "Fairness constraints: " << endl;
      for (vector<BDD>::iterator it = fairness_bdds.begin(); it != fairness_bdds.end(); ++it) {
        it->PrintCover();
      }
    }

    // Add the fairness constraints
    for (vector<BDD>::iterator it = fairness_bdds.begin(); it != fairness_bdds.end(); ++it) {
      fairness_expression* dummy_expr = new fairness_expression(NULL);
      dummy_expr->set_bdd_representation(*it);
      is_fairness->push_back(dummy_expr);
    }

    // Compose tableau and agents
    para->vRT->push_back(tableau);
    agents->push_back(NULL); // force the utility methods to look at the new element of vRT
    
    // Compute reachable states again
    BDD fintab_reachables = check_EX(para->bddmgr->bddOne(), para);
    BDD prev = para->bddmgr->bddOne();
    while (prev != fintab_reachables) {
      prev = fintab_reachables;
      fintab_reachables = check_EX(fintab_reachables, para);
    }
    fairness_bdds.push_back(fintab_reachables);

    // Compute EG True given eventualities are satisfied
    modal_formula* spec = new modal_formula(11, new modal_formula(5, NULL));

    // This enforces that the automaton is followed
    modal_formula* val = ((modal_formula *) new_formula->obj[0]);
    BDD sat_bdd = val->check_path_sat(para, index_map, 0);
    sat_bdd *= rules;
    *state *= sat_bdd;
    bool successful_cex = spec->build_cex(state, index, para, countex, idbdd, cextr);

    // Cleanup
    para->vRT->pop_back();
    agents->pop_back();
    for (size_t i = 0; i < elementary_formulas.size(); ++i) {
      para->v->pop_back();
      para->pv->pop_back();
    }
    for (size_t i = 0; i < fairness_bdds.size(); ++i) {
      is_fairness->pop_back();
    }
    para->calReachRT = true; // Force recalculation - the cache can be very weird

    return successful_cex;
  }

    // leaf
  case 3:{
    modal_formula *argument = ((modal_formula *) obj[0]);

    if (argument->get_op() == 0) {

      // It's the negation of an atom

      BDD p = check_formula(para);

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
          !((modal_formula *) (argument->get_operand(1)))->check_formula(para) * (*para->reach);

        aset1 = get_K_states(formula, state, name, para);
      } else if (argument->get_op() == 31) {
        id = agentid->get_operand(0);
        name = ((atomic_proposition *) id)->get_proposition();
        formula = ((modal_formula *) (argument->get_operand(1)))->check_formula(para) * (*para->reach);
        aset1 = check_GK(formula, name, para);

        aset1 = !aset1 * !formula * (*para->reach);
        aset1 = get_GK_states(aset1, state, name, para);
      } else if (argument->get_op() == 32) {
        id = agentid->get_operand(0);
        name = ((atomic_proposition *) id)->get_proposition();
        formula = ((modal_formula *) (argument->get_operand(1)))->check_formula(para);
        aset1 = !check_GCK(formula, name, para) * (*para->reach);

        aset1 = aset1 * !formula;
        aset1 = get_GK_states(aset1, state, name, para);
      } else if (argument->get_op() == 40) {  // O
        id = agentid->get_operand(0);
        name = ((atomic_proposition *) id)->get_proposition();
        formula = !((modal_formula *) (argument->get_operand(1)))->check_formula(para) * (*para->reach);
        aset1 = check_nO(formula, name, para) * (*para->reach);
      } else if (argument->get_op() == 42) {
        id = agentid->get_operand(0);
        name = ((atomic_proposition *) id)->get_proposition();
        formula = ((modal_formula *) argument->get_operand(1))->check_formula(para) * (*para->reach);
        aset1 = check_DK(formula, name, para);

        aset1 = !aset1 * !formula * (*para->reach);
        aset1 = get_DK_states(aset1, state, name, para);
      }

      if (aset1 == para->bddmgr->bddZero())
        return false;

      BDD curstate = aset1.PickOneMinterm(*para->v);
      if (curstate == *state) {
        aset1 = aset1 - curstate;
        if (aset1 != para->bddmgr->bddZero())
          curstate = aset1.PickOneMinterm(*para->v);
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

        return fcex->build_cex(tmpresult[1], scount, para, countex, idbdd, cextr);
      } else
        return true;
    } else if ((argument->get_op() == 45 || argument->get_op() == 46
                || argument->get_op() == 47 || argument->get_op() == 48)
               && options["atlcex"] > 0) {
      if (argument->get_op() == 45) { // ATLX
        BDD p = ((modal_formula *) (argument->get_operand(1)))->check_formula(para);

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
          BDD successor = onetran.PickOneMinterm(*para->pv);
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
            nphi.build_cex(tmpresult[i], gi->second, para, countex, idbdd, cextr);
          }
        }

        return true;
      } else if (argument->get_op() == 46) {  // ATLF
        BDD p = ((modal_formula *) (argument->get_operand(1)))->check_formula(para);
        BDD p1 = p.SwapVariables(*para->v, *para->pv);
        tmpresult.push_back(new BDD(*state));
        if (index >= idbdd->size())
          idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
        map< string, int >statekeys;
        string strkey = state_to_str(*tmpresult[0], *para->v);
        statekeys[strkey] = index;

        BDD last = argument->check_formula(para); // the last state of fixpoint computation    

        BDD atltree = *state;
        BDD Y = atltree;
        BDD lastprime = last.SwapVariables(*para->v, *para->pv);
        while (Y != para->bddmgr->bddZero()) {
          BDD tmpy = Y;
          BDD newy = para->bddmgr->bddZero();

          // get all successor states
          while (tmpy != para->bddmgr->bddZero()) {
            BDD predecessor = tmpy.PickOneMinterm(*para->v);
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

              BDD successor = onetran.PickOneMinterm(*para->pv);
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
            nphi.build_cex(tmpresult[i], gi->second, para, countex, idbdd, cextr);
          }
        }

        return true;
      } else if (argument->get_op() == 47) {  // ATLG
        BDD p = ((modal_formula *) (argument->get_operand(1)))->check_formula(para);
        BDD p1 = p.SwapVariables(*para->v, *para->pv);
        tmpresult.push_back(new BDD(*state));
        if (index >= idbdd->size())
          idbdd->insert(pair < int, BDD * >(index, (tmpresult[0])));
        if (*state * p == para->bddmgr->bddZero()) {
          if (options["atlcex"] == 2) {
            modal_formula nphi(3, (modal_formula *) (argument->get_operand(1)));
            nphi.build_cex(state, index, para, countex, idbdd, cextr);
          }
          return true;
        }
        map< string, int >statekeys;
        string strkey = state_to_str(*tmpresult[0], *para->v);
        statekeys[strkey] = index;

        BDD last = argument->check_formula(para); // the last state of fixpoint computation    

        BDD atltree = *state;
        BDD Y = atltree;
        BDD lastprime = last.SwapVariables(*para->v, *para->pv);
        while (Y != para->bddmgr->bddZero()) {
          BDD tmpy = Y;
          BDD newy = para->bddmgr->bddZero();

          // get all successor states
          while (tmpy != para->bddmgr->bddZero()) {
            BDD predecessor = tmpy.PickOneMinterm(*para->v);
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

              BDD successor = onetran.PickOneMinterm(*para->pv);
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
            nphi.build_cex(tmpresult[i], gi->second, para, countex, idbdd, cextr);
          }
        }

        return true;
      } else {    // ATLU
        BDD p =
          ((modal_formula *) (argument->get_operand(1)))->
          check_formula(para);
        BDD q =
          ((modal_formula *) (argument->get_operand(2)))->
          check_formula(para);
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
            nphi.build_cex(state, index, para, countex, idbdd, cextr);
          }
          return true;
        }
        map< string, int >statekeys;
        string strkey = state_to_str(*tmpresult[0], *para->v);
        statekeys[strkey] = index;

        BDD last = argument->check_formula(para); // the last state of fixpoint computation    

        BDD atltree = *state;
        BDD Y = atltree;
        BDD lastprime = last.SwapVariables(*para->v, *para->pv);
        while (Y != para->bddmgr->bddZero()) {
          BDD tmpy = Y;
          BDD newy = para->bddmgr->bddZero();

          // get all successor states
          while (tmpy != para->bddmgr->bddZero()) {
            BDD predecessor = tmpy.PickOneMinterm(*para->v);
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

              BDD successor = onetran.PickOneMinterm(*para->pv);
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
            nphi.build_cex(tmpresult[i], gi->second, para, countex, idbdd, cextr);
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

