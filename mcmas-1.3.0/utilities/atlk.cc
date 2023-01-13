#include "utilities.hh"
#include "atlk.hh"
#include "cuddInt.h"

static unsigned int uniform_strategy_counter;
map< string, map< string, vector< BDD* >* >* >* integerBDDs = NULL;
map< string, map< string, BDD* >* >* enumerateBDDs = NULL;

extern bool *satisfied;
extern unsigned int num_of_satisfied;
extern double reachablestates;
extern unsigned int num_of_strategies;

void do_model_checking(bdd_parameters * para);
void do_statespace_generation(bdd_parameters * para);

void
build_enumerate_BDDs(bdd_parameters * para)
{
  for (map < string, basic_agent * >::iterator i = is_agents->begin();
       i != is_agents->end(); i++) {
    basic_agent* agent = i->second;
    map< string, basictype * > *obsvars = agent->get_obsvars();
    map< string, basictype * > *vars = agent->get_vars();
    map< string, BDD* >* agentBDDs = NULL;
    if(obsvars != NULL && obsvars->size() > 0) {
      for (map< string, basictype * >::iterator j = obsvars->begin();
           j != obsvars->end(); j++) {
        basictype *bt = j->second;
        if(bt->get_type() == 3 && !((enumerate*)bt)->is_power_of_two()) {
          BDD tmp = ((enumerate*)bt)->build_all_BDDs(para->bddmgr, para->v);
          agentBDDs = agentBDDs == NULL? new map< string, BDD* > : agentBDDs;
          (*agentBDDs)[j->first] = new BDD(tmp);
          if(options["debug"] == 1) {
            cout << j->first << " in " << i->first << " has " << ((enumerate*)bt)->get_number_of_elements() << " values" << endl;
          }
        }
      }
    }
    if(vars != NULL && vars->size() > 0) {
      for (map< string, basictype * >::iterator j = vars->begin();
           j != vars->end(); j++) {
        basictype *bt = j->second;
        if(bt->get_type() == 3 && !((enumerate*)bt)->is_power_of_two()) {
          BDD tmp = ((enumerate*)bt)->build_all_BDDs(para->bddmgr, para->v);
          agentBDDs = agentBDDs == NULL? new map< string, BDD* > : agentBDDs;
          (*agentBDDs)[j->first] = new BDD(tmp);
          if(options["debug"] == 1) {
            cout << j->first << " in " << i->first << " has " << ((enumerate*)bt)->get_number_of_elements() << " values" << endl;
          }
        }
      }
    }
    if(agentBDDs != NULL) {
      enumerateBDDs = enumerateBDDs == NULL ? new map< string, map< string, BDD* >* > : enumerateBDDs;
      (*enumerateBDDs)[i->first] = agentBDDs; 
    }
  }
}

void
clear_enumerate_BDDs(bdd_parameters * para)
{
  if(enumerateBDDs != NULL) {
    for (map < string, map< string, BDD* >* >::iterator i = enumerateBDDs->begin();
         i != enumerateBDDs->end(); i++) {
      map< string, BDD* >* agentBDDs = i->second;
      for (map< string, BDD* >::iterator j = agentBDDs->begin();
           j != agentBDDs->end(); j++) {
        delete j->second;
      }
      delete agentBDDs;
    }
    delete enumerateBDDs;
  }
}

void
build_integer_BDDs(bdd_parameters * para)
{
  for (map < string, basic_agent * >::iterator i = is_agents->begin();
       i != is_agents->end(); i++) {
    basic_agent* agent = i->second;
    map< string, basictype * > *obsvars = agent->get_obsvars();
    map< string, basictype * > *vars = agent->get_vars();
    map< string, vector< BDD* >* >* agentBDDs = NULL;
    if(obsvars != NULL && obsvars->size() > 0) {
      for (map< string, basictype * >::iterator j = obsvars->begin();
           j != obsvars->end(); j++) {
        basictype *bt = j->second;
        if(bt->get_type() == 2 && !((rangedint*)bt)->is_power_of_two()) {
          // build individual bdd for each integer value
          vector< BDD* >* bddblocks = new vector< BDD* >;
          ((rangedint*)bt)->build_individual_BDD(para->bddmgr, para->v, bddblocks, ((rangedint*)bt)->get_length());
          agentBDDs = agentBDDs == NULL? new map< string, vector< BDD* >* > : agentBDDs;
          (*agentBDDs)[j->first] = bddblocks;
          if(options["debug"] == 1) {
            cout << j->first << " in " << i->first << " has " << bddblocks->size() << " values" << endl;
          }
        }
      }
    }
    if(vars != NULL && vars->size() > 0) {
      for (map< string, basictype * >::iterator j = vars->begin();
           j != vars->end(); j++) {
        basictype *bt = j->second;
        if(bt->get_type() == 2 && !((rangedint*)bt)->is_power_of_two()) {
          // build individual bdd for each integer value
          vector< BDD* >* bddblocks = new vector< BDD* >;
          ((rangedint*)bt)->build_individual_BDD(para->bddmgr, para->v, bddblocks, ((rangedint*)bt)->get_length());
          agentBDDs = agentBDDs == NULL? new map< string, vector< BDD* >* > : agentBDDs;
          (*agentBDDs)[j->first] = bddblocks;
          if(options["debug"] == 1) {
            cout << j->first << " in " << i->first << " has " << bddblocks->size() << " values" << endl;
          }
        }
      }
    }
    if(agentBDDs != NULL) {
      integerBDDs = integerBDDs == NULL ? new map< string, map< string, vector< BDD* >* >* > : integerBDDs;
      (*integerBDDs)[i->first] = agentBDDs; 
    }
  }
}

void
clear_integer_BDDs(bdd_parameters * para)
{
  if(integerBDDs != NULL) {
    for (map < string, map< string, vector< BDD* >* >* >::iterator i = integerBDDs->begin();
         i != integerBDDs->end(); i++) {
      map< string, vector< BDD* >* >* agentBDDs = i->second;
      for (map< string, vector< BDD* >* >::iterator j = agentBDDs->begin();
           j != agentBDDs->end(); j++) {
        vector< BDD* >* bddblocks = j->second;
        for(unsigned int k=0; k<bddblocks->size(); k++)
          delete (*bddblocks)[k];
        delete bddblocks;
      }
      delete agentBDDs;
    }
    delete integerBDDs;
  }
}

void
traverse_uniform_strategies_aux(vector<vector<BDD*>*>* uniform_prots, unsigned int agent_index, bdd_parameters * para)
{
  if(agent_index == agents->size()) {
    num_of_strategies++;
    // generate state space
    if(para->reach)
      delete para->reach;
    do_statespace_generation(para);
    double num_of_states = para->reach->CountMinterm(para->v->size());
    if(options["quiet"] == 0)
      cout << "  Strategy " << num_of_strategies << ":  number of reachable states = " << num_of_states << endl;
    //para->reach->print(2, 2);
    if(num_of_states > reachablestates)
      reachablestates = num_of_states;
    // do model checking
    do_model_checking(para);
  } else {
    // pick up a uniform protocol from the current agent
    vector<BDD*>* uni_prot = (*uniform_prots)[agent_index];
    /*for(unsigned int i=0; i<uni_prot->size(); i++) {
      (*uni_prot)[i]->print(2, 2);
      }*/
    for(unsigned int i=0; i<uni_prot->size() && num_of_satisfied<is_formulae->size(); i++) {
      (*para->vprot)[agent_index] = *(*uni_prot)[i];
      //cout << "i =" << i << ", number of satisfied = " << num_of_satisfied << endl;
      BDD tmpRT = (*para->vevol)[agent_index] * *(*uni_prot)[i];
      (*para->vRT)[agent_index] = tmpRT;
      traverse_uniform_strategies_aux(uniform_prots, agent_index+1, para);
    }
  }
}

void
traverse_uniform_strategies(vector<vector<BDD*>*>* uniform_prots, bdd_parameters * para)
{
  if (options["quiet"] == 0 || options["simulation"] == 0) {
    cout << "Verifying formulae under uniform strategies..." << endl;
  }

  traverse_uniform_strategies_aux(uniform_prots, 0, para); 

  for (unsigned int i = 0; i < is_formulae->size(); i++) {
    if (options["quiet"] == 0)
      cout << "  Formula number " << i+1 << ": " <<
        (*is_formulae)[i].to_string() << ", is " << (satisfied[i] ? "TRUE" : "FALSE")
           << " in the model" << endl;
    else
      cout << (satisfied[i] ? "TRUE" : "FALSE") << endl;
  }
  if (options["quiet"] == 0)
    cout << "done, " << is_formulae->size() << " formulae successfully read and checked" << endl;
}

BDD
check_ATLX_strat(BDD next, string grpname, bdd_parameters * para)
{
  BDD actagtin = para->bddmgr->bddOne();        // Actions of agents in group
  BDD actagtout = para->bddmgr->bddOne();       // Actions of agents NOT in group
  int begin, end;
  map < string, set < string > >::iterator gi = is_groups->find(grpname);
  set < string > names_g = gi->second;  // the list of agt names in groups
  for (map < string, basic_agent * >::iterator i = is_agents->begin();
       i != is_agents->end(); i++) {
    begin = i->second->get_action_index_begin();
    end = i->second->get_action_index_end();
    if (names_g.find(i->first) == names_g.end()) {
      for (int j = begin; j <= end; j++) {
        actagtout = actagtout * (*para->a)[j];
      }}

    else {
      for (int j = begin; j <= end; j++) {
        actagtin = actagtin * (*para->a)[j];
      }}} 
  BDD partial = (!next) * (*para->reach);

  partial = partial.SwapVariables(*para->v, *para->pv);
  for (unsigned int i = 0; i < agents->size(); i++)
    partial = partial * (*para->vevol)[i];
  partial = Exists(para->bddmgr, para->pv, partial);
  partial = partial * (*para->reach);

  for (unsigned int i = 0; i < agents->size(); i++)
    partial = partial * (*para->vprot)[i];
  partial = partial.ExistAbstract(actagtout);

  partial = (!partial) * (*para->reach);
  for (unsigned int i = 0; i < agents->size(); i++)
    partial = partial * (*para->vprot)[i];
  partial = partial.ExistAbstract(actagtout);

  return partial;
}

BDD
check_ATL_NFair(string grpname, bdd_parameters * para)
{
  BDD tmp = para->bddmgr->bddOne();
  BDD q = para->bddmgr->bddZero();
  while (q != tmp) {
    tmp = q;
    for (vector < fairness_expression * >::iterator fi =
           is_fairness->begin(); fi != is_fairness->end(); fi++) {
      BDD hf = (*fi)->get_bdd_representation(); // The BDD for the fairness constraint
      BDD nhf = (*para->reach) - hf;
      BDD tmp1 = tmp + nhf;
      BDD tmp2 = check_ATLG_aux(tmp1, grpname, para);
      
      q += check_ATLX(tmp2, grpname, para);
    }
  }
  return q;
}

// compute fair_gamma for [Gamma]
BDD 
check_fair_gamma_FO(string grpname, bdd_parameters * para)
{
  BDD fair_gamma = *para->reach;
  if(!is_fairness->empty()) { 
    if(para->fair_gamma_FO == NULL) {
      para->fair_gamma_FO = new map< string, BDD* >();
    }
    map< string, BDD* >::iterator it = para->fair_gamma_FO->find(grpname);
    if(it == para->fair_gamma_FO->end()) {
      if(options["verbosity"] > 0) 
        cout << "Building fair_gamma under partial observability semantics..." << endl;
      // compute fair reachable states under fo semantics
      fair_gamma = check_ATLG_negation(para->bddmgr->bddOne(), grpname, para);
      para->fair_gamma_FO->insert(pair<string, BDD*>(grpname, new BDD(fair_gamma)));
    } else
      fair_gamma = *(it->second);
  }
  return fair_gamma;
}

// compute nfair_gamma for <Gamma>
BDD 
check_nfair_gamma_FO(string grpname, bdd_parameters * para)
{
  BDD nfair_gamma = para->bddmgr->bddZero();
  if(!is_fairness->empty()) { 
    if(para->nfair_gamma_FO == NULL) {
      para->nfair_gamma_FO = new map< string, BDD* >();
    }
    map< string, BDD* >::iterator it = para->nfair_gamma_FO->find(grpname);
    if(it == para->nfair_gamma_FO->end()) {
      if(options["verbosity"] > 0) 
        cout << "Building nfair_gamma under partial observability semantics..." << endl;
      // compute fair reachable states under fo semantics
      nfair_gamma = check_ATL_NFair(grpname, para);
      para->nfair_gamma_FO->insert(pair<string, BDD*>(grpname, new BDD(nfair_gamma)));
    } else 
      nfair_gamma = *(it->second);
  }
  return nfair_gamma;
}

BDD
check_ATLG_fair_fo_strat(BDD p, BDD nfair, BDD strategies, vector<string> *agent_names, bdd_parameters * para)
{
  BDD tmp = p + nfair;
  BDD q = para->bddmgr->bddOne();
  while (q != tmp) {
    q = tmp;
    tmp = p * check_ATLX_fo_strat(tmp, strategies, agent_names, para);
  }
  return q;
}

BDD
check_ATLG_fair_fo(BDD p, BDD nfair, string grpname, bdd_parameters * para)
{
  BDD tmp = p + nfair;
  BDD q = para->bddmgr->bddOne();
  while (q != tmp) {
    q = tmp;
    tmp = p * check_ATLX(tmp, grpname, para);
  }
  return q;
}

BDD
check_ATLU_fair_fo_strat_aux(BDD p1, BDD p2, BDD strategies, vector<string> *agent_names, bdd_parameters * para)
{
  BDD tmp = p1;
  BDD q = para->bddmgr->bddOne();
  while (q != tmp) {
    q = tmp;
    tmp = p1 * (p2 + check_ATLX_fo_strat(tmp, strategies, agent_names, para));
  }
  return q;
}

BDD
check_ATLU_fair_fo_strat(BDD p1, BDD p2, BDD nfair, BDD strategies, vector<string> *agent_names, bdd_parameters * para)
{
  if(!is_fairness->empty()) { 
    BDD p = p1 + p2 + nfair;
    BDD tmp = para->bddmgr->bddOne();
    BDD q = para->bddmgr->bddZero();
    while (q != tmp) {
      tmp = q;
      q = para->bddmgr->bddZero();
      for (vector < fairness_expression * >::iterator fi =
             is_fairness->begin(); fi != is_fairness->end(); fi++) {
        BDD hf = (*fi)->get_bdd_representation(); // The BDD for the fairness constraint
        BDD nhf = (*para->reach) - hf;
        BDD tmp1 = (tmp + nhf) * p;
        BDD tmp2 = check_ATLU_fair_fo_strat_aux(tmp1, p2, strategies, agent_names, para);
  
        q += check_ATLX_fo_strat(tmp2, strategies, agent_names, para);
      }
      q += p2;
      q *= p;
    }
    
    return q;
  } else
    return check_ATLU_fo_strat(p1, p2, strategies, agent_names, para);
}

BDD
check_ATLU_fair_fo_aux(BDD p1, BDD p2, string grpname, bdd_parameters * para)
{
  BDD tmp = p1;
  BDD q = para->bddmgr->bddOne();
  while (q != tmp) {
    q = tmp;
    tmp = p1 * (p2 + check_ATLX(tmp, grpname, para));
  }
  return q;
}

BDD
check_ATLU_fair_fo(BDD p1, BDD p2, BDD nfair, string grpname, bdd_parameters * para)
{
  BDD p = p1 + p2 + nfair;
  BDD tmp = para->bddmgr->bddOne();
  BDD q = para->bddmgr->bddZero();
  while (q != tmp) {
    tmp = q;
    q = para->bddmgr->bddZero();
    for (vector < fairness_expression * >::iterator fi =
           is_fairness->begin(); fi != is_fairness->end(); fi++) {
      BDD hf = (*fi)->get_bdd_representation(); // The BDD for the fairness constraint
      BDD nhf = (*para->reach) - hf;
      BDD tmp1 = (tmp + nhf) * p;
      BDD tmp2 = check_ATLU_fair_fo_aux(tmp1, p2, grpname, para);
      q += check_ATLX(tmp2, grpname, para);
    }
    q += p2;
    q *= p;
  }
  return q;
}

BDD
check_ATLU_fair_po_aux(BDD p1, BDD p2, BDD p2_strat, string grpname, bdd_parameters * para)
{
  BDD tmp = p1;
  BDD result = p2_strat;
  BDD q = para->bddmgr->bddOne();
  while (q != tmp) {
    q = tmp;
    result = p1 * (p2_strat + check_ATLX_strat(tmp, grpname, para));
    tmp = Exists(para->bddmgr, para->a, result) * (*para->reach);
  }
  return result;
}

BDD 
generate_state_action(BDD p, string grpname, bdd_parameters * para)
{
  BDD result = para->bddmgr->bddOne();
  map < string, set < string > >::iterator gi = is_groups->find(grpname);
  set < string > names_g = gi->second;  // the list of agt names in groups
  for(unsigned int i=0; i<agents->size(); i++) {
    if (names_g.find((*agents)[i]->get_name()) != names_g.end()) {
      basic_agent *agent = (*agents)[i];
      BDD localstateaction = agent->project_local_state(&p, para->bddmgr, para->v);
      localstateaction = (*para->vprot)[i];
      result *= localstateaction;
    }
  }
  return result;
}

BDD
check_ATLU_fair_po(BDD p1, BDD p2, BDD nfair, string grpname, bdd_parameters * para)
{
  BDD p = p1 + p2 + nfair;
  BDD p2_strat = generate_state_action(p2, grpname, para);
  BDD tmp = para->bddmgr->bddOne();
  BDD q = para->bddmgr->bddZero();
  BDD result = q;
  while (q != tmp) {
    tmp = q;
    q = para->bddmgr->bddZero();
    for (vector < fairness_expression * >::iterator fi =
           is_fairness->begin(); fi != is_fairness->end(); fi++) {
      BDD hf = (*fi)->get_bdd_representation(); // The BDD for the fairness constraint
      BDD nhf = (*para->reach) - hf;
      BDD tmp1 = (tmp + nhf) * p;
      BDD tmp2 = check_ATLU_fair_po_aux(tmp1, p2, p2_strat, grpname, para);
      
      q += check_ATLX_strat(tmp2, grpname, para);
    }
    q += p2_strat;
    q *= p;
    result = q;
    q = Exists(para->bddmgr, para->a, q) * (*para->reach);
  }
  return result;
}

BDD
check_ATLU_po(BDD q1, BDD q2, string grpname, bdd_parameters * para)
{
  BDD q2_strat = generate_state_action(q2, grpname, para);
  BDD r = para->bddmgr->bddZero();
  BDD t = q2;
  BDD result = q2_strat;
  while (t != r) {
    r = t;
    result = result + check_ATLX_strat(r, grpname, para) * q1;
    t = Exists(para->bddmgr, para->a, result) * (*para->reach);
  }
  return result;
}

BDD
check_suc_strat(BDD source, BDD next, string grpname, bdd_parameters * para)
{
  BDD actagtin = para->bddmgr->bddOne();        // Actions of agents in group
  BDD actagtout = para->bddmgr->bddOne();       // Actions of agents NOT in group
  int begin, end;
  map < string, set < string > >::iterator gi = is_groups->find(grpname);
  set < string > names_g = gi->second;  // the list of agt names in groups
  for (map < string, basic_agent * >::iterator i = is_agents->begin();
       i != is_agents->end(); i++) {
    begin = i->second->get_action_index_begin();
    end = i->second->get_action_index_end();
    if (names_g.find(i->first) == names_g.end()) {
      for (int j = begin; j <= end; j++) {
        actagtout = actagtout * (*para->a)[j];
      }}

    else {
      for (int j = begin; j <= end; j++) {
        actagtin = actagtin * (*para->a)[j];
      }}} 

  BDD nonext = (!next);
  nonext = nonext.SwapVariables(*para->v, *para->pv);
  
  BDD strat = source;
  for (unsigned int i = 0; i < agents->size(); i++)
    strat *= (*para->vRT)[i];

  BDD bad = strat;
  bad *= nonext;
  bad = Exists(para->bddmgr, para->pv, bad);
  bad = bad.ExistAbstract(actagtout);

  strat = source;
  for (unsigned int i = 0; i < agents->size(); i++)
    strat *= (*para->vprot)[i];
  strat = strat.ExistAbstract(actagtout);

  strat = strat - bad;
  return strat;
}

BDD
split_uniform_strategies_aux(BDD p1, BDD p2, unsigned char op, unsigned int agent_index, string grpname, vector<string> *agent_names, BDD SA, BDD strategies, BDD localstate, BDD localstateaction, vector<BDD> *lv, vector<BDD> *va, BDD nfair, bdd_parameters * para) 
{
  if(localstate == para->bddmgr->bddZero()) {
    return split_uniform_strategies(p1, p2, op, agent_index + 1, grpname, agent_names, SA, strategies, nfair, para);
  } /*else if(options["newpo"] == 1) {
      BDD newstrategies = para->bggmgr->bddOne();
      for (unsigned int i = 0; i < agents->size(); i++)
      newstrategies *= (*para->vRT)[i];
      BDD partial = Exists(para->bddmgr, para->a, strategies);
      newstrategies -= partial;

      // recompute \phi under fo using known <state, action> pairs
      BDD result = para->bggmgr->bddZero();
      switch(op) {
      case 45:      // ATL operator X
      result = check_ATLX_fo_strat_action(p2 + nfair, newstrategies, agent_names, para);
      break;
      case 46:      // ATL operator F
      result = check_ATLU_fair_fo_strat_action(p1, p2, nfair, newstrategies, agent_names, para);                                
      break;
      case 47:      // ATL operator G
      result = check_ATLG_fair_fo_strat_action(p2, nfair, newstrategies, agent_names, para);
      break;
      case 48:      // ATL operator U 
      result = check_ATLU_fair_fo_strat_action(p1, p2, nfair, newstrategies, agent_names, para);
      break;
      }

      // recompute local state action pairs and local states
      BDD SA1 = SA;
      SA1 *= localstate;
      // use split_uniform_strategies to split state action pairs
      return split_uniform_strategies(p1, p2, op, agent_index, grpname, agent_names, SA1, strategies, nfair, para);
      }*/ else {
    BDD s = localstate.PickOneMinterm(*lv);
    string agname = (*agent_names)[agent_index];
    basic_agent *agent = (*is_agents)[agname];
    s = agent->compute_whole_state_for_integer(s, para);
    BDD newlocalstate = localstate - s;
    BDD sas = localstateaction * s;
    BDD result = para->bddmgr->bddZero();
    while(sas != para->bddmgr->bddZero()) {
      BDD sa = sas.PickOneMinterm(*va); // check if it is correct
      sas -= sa;
      BDD strat = strategies + sa;
      // calling nested split
      result += split_uniform_strategies_aux(p1, p2, op, agent_index, grpname, agent_names, SA, strat, newlocalstate, localstateaction, lv, va, nfair, para);
    }
    return result;
  }
}

BDD
split_uniform_strategies(BDD p1, BDD p2, unsigned char op, unsigned int agent_index, string grpname, vector<string> *agent_names, BDD SA, BDD strategies, BDD nfair, bdd_parameters * para) 
{
  BDD result = para->bddmgr->bddZero();

  if(agent_index == agent_names->size()) {
    // verify formula on uniform strategy
    BDD next = Exists(para->bddmgr, para->a, SA);
    switch(op) {
    case 45:      // ATL operator X
      result = check_ATLX_fo_strat(p2 + nfair, strategies, agent_names, para);
      break;
    case 46:      // ATL operator F
      result = check_ATLU_fair_fo_strat(p1, p2, nfair, strategies, agent_names, para);                          
      break;
    case 47:      // ATL operator G
      result = check_ATLG_fair_fo_strat(p2, nfair, strategies, agent_names, para);
      break;
    case 48:      // ATL operator U 
      result = check_ATLU_fair_fo_strat(p1, p2, nfair, strategies, agent_names, para);
      break;
    }
    result *= check_DK(result, grpname, para);
    uniform_strategy_counter ++;
    if(options["verbosity"] > 0 && uniform_strategy_counter % options["counter"] == 0) {
      cout << "Processed " << uniform_strategy_counter << " uniform strategies" << endl;
    }
  } else {
    string agname = (*agent_names)[agent_index];
    basic_agent *agent = (*is_agents)[agname];
    BDD localstateaction = agent->project_local_state(&SA, para->bddmgr, para->v);
    localstateaction = agent->project_local_actions(&localstateaction, para->bddmgr, para->a);
    BDD localstate = Exists(para->bddmgr, para->a, localstateaction);

    if(localstate != para->bddmgr->bddZero()) {
      // add to strategies the <state action> pairs not quantified by localstate
      int k = (*is_agents_index)[agname];
      BDD xlocalstateaction = (*para->vprot)[k] * (!localstate);

      if(options["debug"] == 1) {
        /*cout << "FO strategies:";
          BDD tmp = strategies + xlocalstateaction;
          tmp.print(para->v->size() + para->a->size(), 2);*/

        cout << "localstateaction:";
        localstateaction.print(para->v->size() + para->a->size(), 2);   
      }

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
      map< string, variable * > *lobsvars = agent->get_lobsvars();
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
      lv.insert(lv.end(), para->v->begin()+agent->get_var_index_begin(), para->v->begin()+agent->get_var_index_end()+1);
      BDD s = localstate.PickOneMinterm(lv);
      localstate -= s;
      BDD sas = localstateaction * s;
     
      vector<BDD> va(lv.begin(), lv.end());
      va.insert(va.end(), para->a->begin()+agent->get_action_index_begin(), para->a->begin()+agent->get_action_index_end()+1);
      while(sas != para->bddmgr->bddZero()) {
        BDD sa = sas.PickOneMinterm(va); // check if it is correct
        sas -= sa;
        BDD strat = strategies + xlocalstateaction + sa;
        // calling nested split
        result += split_uniform_strategies_aux(p1, p2, op, agent_index, grpname, agent_names, SA, strat, localstate, localstateaction, &lv, &va, nfair, para);
      }
    }
  }
  return result;
}


BDD 
generate_uniform_strategies(BDD p1, BDD p2, unsigned char op, BDD SA, string grpname, BDD nfair, bdd_parameters * para) 
{
  // collect all <state, action> pair
  set < string > names_g = is_groups->find(grpname)->second;
  vector<string> names(names_g.begin(), names_g.end());
  uniform_strategy_counter = 0;
  return split_uniform_strategies(p1, p2, op, 0, grpname, &names, SA, para->bddmgr->bddZero(), nfair, para);
}

BDD
check_ATLX_negation(BDD next, string grpname, bdd_parameters * para)
{
  BDD all_pre = check_EX(next, para);
  BDD neg_next = (!next) * (*para->reach);
  BDD non_pre = check_ATLX(neg_next, grpname, para);
  BDD result = (all_pre - non_pre) * (*para->reach);

  return result;  
}

/*BDD 
  check_ATLX_fo_strat_action(BDD next, BDD strat, vector<string> *agent_names, bdd_parameters * para) {
  BDD actagtin = para->bddmgr->bddOne();        // Actions of agents in group
  BDD actagtout = para->bddmgr->bddOne();       // Actions of agents NOT in group
  int begin, end;
  set < string > names_g(agent_names->begin(), agent_names->end());  // the list of agt names in groups
  for (map < string, basic_agent * >::iterator i = is_agents->begin();
  i != is_agents->end(); i++) {
  begin = i->second->get_action_index_begin();
  end = i->second->get_action_index_end();
  if (names_g.find(i->first) == names_g.end()) {
  for (int j = begin; j <= end; j++) {
  actagtout = actagtout * (*para->a)[j];
  }}

  else {
  for (int j = begin; j <= end; j++) {
  actagtin = actagtin * (*para->a)[j];
  }}} 
  BDD partial = (!next) * (*para->reach);

  partial = partial.SwapVariables(*para->v, *para->pv);
  for (unsigned int i = 0; i < agents->size(); i++)
  partial = partial * (*para->vRT)[i];
  partial *= (*para->reach);
        
  // Use strat to restrict the behaviour
  partial *= strat;

  partial = Exists(para->bddmgr, para->pv, partial);
  partial = partial.ExistAbstract(actagtout);
  partial = partial * (*para->reach);

  /* partial = partial.SwapVariables(*para->v, *para->pv);
  for (unsigned int i = 0; i < agents->size(); i++)
  partial = partial * (*para->vevol)[i];
  partial = Exists(para->bddmgr, para->pv, partial);
  partial = partial * (*para->reach);

  for (unsigned int i = 0; i < agents->size(); i++)
  partial = partial * (*para->vprot)[i];
  partial *= strat;
  partial = partial.ExistAbstract(actagtout);* /

  /*partial = (!partial) * (*para->reach);
  for (unsigned int i = 0; i < agents->size(); i++)
  partial = partial * (*para->vprot)[i];
  // Use strat to restrict the behaviour
  partial *= strat;
  partial = partial.ExistAbstract(actagtout);* /

  BDD result = next.SwapVariables(*para->v, *para->pv);
  for (unsigned int i = 0; i < agents->size(); i++)
  result = result * (*para->vRT)[i];
  result *= (*para->reach);
        
  // Use strat to restrict the behaviour
  result *= strat;
  result = Exists(para->bddmgr, para->pv, result);
  result = result.ExistAbstract(actagtout);
  result = result - partial;

  result = result * (*para->reach);
  return result;  
  } */

BDD 
check_ATLX_fo_strat(BDD next, BDD strat, vector<string> *agent_names, bdd_parameters * para)
{
  BDD actagtin = para->bddmgr->bddOne();        // Actions of agents in group
  BDD actagtout = para->bddmgr->bddOne();       // Actions of agents NOT in group
  int begin, end;
  set < string > names_g(agent_names->begin(), agent_names->end());  // the list of agt names in groups
  for (map < string, basic_agent * >::iterator i = is_agents->begin();
       i != is_agents->end(); i++) {
    begin = i->second->get_action_index_begin();
    end = i->second->get_action_index_end();
    if (names_g.find(i->first) == names_g.end()) {
      for (int j = begin; j <= end; j++) {
        actagtout = actagtout * (*para->a)[j];
      }}

    else {
      for (int j = begin; j <= end; j++) {
        actagtin = actagtin * (*para->a)[j];
      }}} 
  BDD partial = (!next) * (*para->reach);

  partial = partial.SwapVariables(*para->v, *para->pv);
  for (unsigned int i = 0; i < agents->size(); i++)
    partial = partial * (*para->vRT)[i];
  partial *= (*para->reach);
        
  // Use strat to restrict the behaviour
  partial *= strat;

  partial = Exists(para->bddmgr, para->pv, partial);
  partial = partial.ExistAbstract(actagtout);
  partial = partial * (*para->reach);

  /* partial = partial.SwapVariables(*para->v, *para->pv);
     for (unsigned int i = 0; i < agents->size(); i++)
     partial = partial * (*para->vevol)[i];
     partial = Exists(para->bddmgr, para->pv, partial);
     partial = partial * (*para->reach);

     for (unsigned int i = 0; i < agents->size(); i++)
     partial = partial * (*para->vprot)[i];
     partial *= strat;
     partial = partial.ExistAbstract(actagtout);*/

  /*partial = (!partial) * (*para->reach);
    for (unsigned int i = 0; i < agents->size(); i++)
    partial = partial * (*para->vprot)[i];
    // Use strat to restrict the behaviour
    partial *= strat;
    partial = partial.ExistAbstract(actagtout);*/

  BDD result = next.SwapVariables(*para->v, *para->pv);
  for (unsigned int i = 0; i < agents->size(); i++)
    result = result * (*para->vRT)[i];
  result *= (*para->reach);
        
  // Use strat to restrict the behaviour
  result *= strat;
  result = Exists(para->bddmgr, para->pv, result);
  result = result.ExistAbstract(actagtout);
  result = result - partial;

  result = result.ExistAbstract(actagtin) * (*para->reach);
  return result;  
}

BDD
check_ATLU_fo_strat(BDD q1, BDD q2, BDD strat, vector<string> *agent_names, bdd_parameters * para)
{
  BDD r = para->bddmgr->bddZero();
  BDD t = q2;
  while (t != r) {
    r = t;
    t = r + check_ATLX_fo_strat(r, strat, agent_names, para) * q1;
  }
  return r;
}


BDD
check_ATLU_negation(BDD p, BDD q, string grpname, bdd_parameters * para)
{                               
  BDD W = p;
  BDD X = *para->reach;
  BDD Y = q;
  while (X != Y) {
    X = Y;
    Y = Y + (W * check_ATLX_negation(Y, grpname, para));
  }
  return Y;
}

BDD
check_ATLW_negation(BDD p, BDD q, string grpname, bdd_parameters * para)
{                               
  BDD X = check_ATLU_negation(p, q, grpname, para);
  BDD Y = check_ATLG_negation(p, grpname, para);;
  return X + Y;
}


BDD
check_ATLF_negation(BDD q, string grpname, bdd_parameters * para)
{                               
  BDD X = *para->reach;
  BDD Y = q;
  while (X != Y) {
    X = Y;
    Y = Y + check_ATLX_negation(Y, grpname, para);
  }
  return Y;
}

BDD
check_ATLG_fo_fair(BDD p, string grpname, bdd_parameters * para)
{
  // Computes the fixpoint iterating false
  // See "Reasoning about Strategies under Partial Observability and Fairness 
  // Constraints", Busard, Pecheur, Qu, Raimondi, 2013
  // Section 3
  BDD tmp = para->bddmgr->bddZero();
  BDD q = para->bddmgr->bddOne();
  BDD fc_bdd = para->bddmgr->bddOne();
  while (q != tmp) {
    tmp = q;
    for (vector < fairness_expression * >::iterator fi =
           is_fairness->begin(); fi != is_fairness->end(); fi++) {
      BDD hf = (*fi)->get_bdd_representation(); // The BDD for the fairness constraint
      BDD tmp1 = check_ATLU_negation(p, q * hf, grpname, para);
      fc_bdd = fc_bdd * check_ATLX_negation(tmp1, grpname, para);
    }
    q = p * fc_bdd;
  }
  return q;
}

BDD
check_ATLG_negation(BDD p, string grpname, bdd_parameters * para)
{
  // Computes the fixpoint iterating false
  // See "Reasoning about Strategies under Partial Observability and Fairness 
  // Constraints", Busard, Pecheur, Qu, Raimondi, 2013
  // Section 3
  if(is_fairness->empty()) {
    BDD tmp = p;
    BDD q = para->bddmgr->bddOne();
    while (q != tmp) {
      q = tmp;
      tmp = p * check_ATLX_negation(tmp, grpname, para);
    }
    return q;
  } else
    return check_ATLG_fo_fair(p, grpname, para);
}

