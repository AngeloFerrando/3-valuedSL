#include "utilities.hh"
#include "cuddInt.h"

BDD
Exists(Cudd * bddmgr, vector<BDD> * v, BDD x)
{
  BDD tmp = bddmgr->bddOne();   // Always true
  for (unsigned int j = 0; j < v->size(); j++) {
    tmp = tmp * (*v)[j];
  } return x.ExistAbstract(tmp);
}

BDD
Exists(Cudd * bddmgr, vector<BDD> * v, vector<BDD> * a, BDD x)
{
  BDD tmp = bddmgr->bddOne();   // Always true
  for (unsigned int j = 0; j < v->size(); j++) {
    tmp = tmp * (*v)[j];
  } 
  for (unsigned int j = 0; j < a->size(); j++) {
    tmp = tmp * (*a)[j];
  }
  return x.ExistAbstract(tmp);
}

BDD
Exists(Cudd * bddmgr, vector<BDD> * v, BDD x, unsigned int start, unsigned int end)
{
  BDD tmp = bddmgr->bddOne();   // Always true
  for (unsigned int j = start; j <= end; j++) {
    tmp = tmp * (*v)[j];
  } return x.ExistAbstract(tmp);
}

BDD
Abstract_key_var(Cudd * bddmgr, vector<BDD> * v, BDD x, int index_begin, int index_end)
{
  BDD tmp = bddmgr->bddOne();   // Always true
  for (int j = 0; j < index_begin; j++) {
    tmp = tmp * (*v)[j];
  }
  for (unsigned int j = index_end+1; j < v->size(); j++) {
    tmp = tmp * (*v)[j];
  } 
  return x.ExistAbstract(tmp);
}

ADD
ADDExists(Cudd * bddmgr, vector<ADD> v, ADD x)
{
  ADD tmp = bddmgr->addOne();   // Always true
  for (unsigned int j = 0; j < v.size(); j++) {
    tmp = tmp * v[j];
  } 
  return x.ExistAbstract(tmp);
}

BDD
timesTrans(BDD * from, BDD * to, vector<BDD> * vRT)
{
  BDD result;
  result = (*from) * (*to) * (*vRT)[0];
  for (unsigned int i = 1; i < agents->size(); i++)
    result *= (*vRT)[i];
  return result;
}

BDD
timesRT(BDD * state, Cudd * bddmgr, vector<BDD> * vRT, vector<BDD> * a)
{
  BDD result;
  result = (*state) * (*vRT)[0];
  for (unsigned int i = 1; i < agents->size(); i++)
    result *= (*vRT)[i];
  result = Exists(bddmgr, a, result);
  return result;
}

BDD 
compute_successors(BDD *state, Cudd * bddmgr, vector<BDD> * vRT, vector<BDD> * a, vector<BDD> *v, vector<BDD> *pv)
{
  BDD result = timesRT(state, bddmgr, vRT, a);
  result = Exists(bddmgr, v, result);
  result = result.SwapVariables(*v, *pv);
  return result;
}

BDD
check_EX(BDD next, bdd_parameters * para)
{
  // Computes the preimage
  if(options["nobddcache"] == 0) {
    if (para->calReachRT) {
      BDD reachRT1 = *para->reach;
      for (unsigned int i = 0; i < agents->size(); i++)
        reachRT1 *= (*para->vRT)[i];
      para->reachRT = new BDD(reachRT1);
      para->calReachRT = false;
    }
  }
  BDD result = next.SwapVariables(*para->v, *para->pv); // Now it's the next state
  if(options["nobddcache"] == 0)
    result = result * (*para->reachRT);
  else {
    for (unsigned int i = 0; i < agents->size(); i++)
      result *= (*para->vRT)[i];
  }
  result = Exists(para->bddmgr, para->pv, result);      // States from which...
  result = Exists(para->bddmgr, para->a, result);       //Exists a joint action...
  result = result * (*para->reach);
  return result;
}

BDD
check_EF(BDD p, bdd_parameters * para)
{
  // Computes the fixpoint iterating false
  BDD tmp = para->bddmgr->bddOne();
  BDD q = para->bddmgr->bddZero();
  while (q != tmp) {
    tmp = q;
    q = p + check_EX(tmp, para);
  }
  return q * (*para->reach);
}

BDD
check_EG(BDD p, bdd_parameters * para)
{
  // Computes the fixpoint iterating false
  if(is_fairness->empty()) {
    BDD tmp = para->bddmgr->bddZero();
    BDD q = para->bddmgr->bddOne();
    while (q != tmp) {
      tmp = q;
      BDD x = check_EX(tmp, para);
      q = p * x;
    }
    return q;
  } else
    return check_EG_fair(p, para);
}

BDD
check_EU(BDD p, BDD q, bdd_parameters * para)
{                               // See Huth-Ryan, pag. 180
  BDD W = p;
  BDD X = *para->reach;
  BDD Y = q;
  while (X != Y) {
    X = Y;
    Y = Y + (W * check_EX(Y, para));
  }
  return Y;
}

BDD
check_EU_Qh(BDD p, BDD q, bdd_parameters * para, vector< BDD* >* qh)
{       
  BDD W = p;
  BDD X = *para->reach;
  BDD Y = q;
  BDD Z = Y;
  qh->push_back(new BDD(Y));
  while (X != Y) {
    X = Y;
    Z = W * check_EX(Z, para);
    Z = Z - Y;
    Y = Y + Z;
    if(X != Y)
      qh->push_back(new BDD(Z));
  }
  return Y;
}

BDD
check_AU(BDD p, BDD q, bdd_parameters * para)
{                               // Tricky one, see Huth Ryan pag. 167 and 179
  BDD result =
    !(check_EU(!q, !p * !q, para) + check_EG(!q, para)) * (*para->reach);
  return result;
}

BDD
check_AU_RT(BDD p, BDD q, int k, bdd_parameters * para)
{                               
	BDD allAU = q;
	for(int i=1; i<=k; i++) {
		// get predecesors of allAU
		BDD t = check_EX(allAU, para);
		// remove states that are included in AU^0 - AU^(i-1) already
		t -= allAU;
		if(t == para->bddmgr->bddZero())
			break;
		// get states that can reach states outside allAU
		BDD t1 = check_EX(*para->reach - allAU, para);
		// remove from t the states that can reach states outside allAU
		t -= t1;
		// remove from t the states that do not satisfy p
		t *= p;
		if(t != para->bddmgr->bddZero()) {
			allAU += t;
		} else 
			break;
	}

  return allAU;
}

BDD
check_EU_RT(BDD p, BDD q, int k, bdd_parameters * para)
{                               
	BDD allEU = q;
	BDD lastEU = q;
	for(int i=1; i<=k; i++) {
		// get predecesors of allEU
		BDD t = check_EX(lastEU, para);
		// remove states that are included in EU^0 - EU^(i-1) already
		t -= allEU;
		// remove from t the states that do not satisfy p
		t *= p;
		if(t != para->bddmgr->bddZero()) {
			allEU += t;
			lastEU = t;
		} else 
			break;
	}

  return allEU;
}

BDD
check_nO(BDD next, string name, bdd_parameters * para)
{
  // Check deontic
  next = next.SwapVariables(*para->v, *para->pv);       // Now it's the next state
  BDD RO = (*is_agents)[name]->encode_greenstates(para);
  BDD result = Exists(para->bddmgr, para->pv, RO * next * (*para->reach));      // States from which...
  return result;
}

BDD
check_GK(BDD next, string name, bdd_parameters * para)
{
  set < string > gi = (*is_groups)[name];
  BDD tmp = para->bddmgr->bddZero();
  BDD ntmp = (*para->reach) - next;
  for (set < string >::iterator igs = gi.begin(); igs != gi.end(); igs++) {
    basic_agent *agent = (*is_agents)[*igs];
    tmp += agent->project_local_state(&ntmp, para->bddmgr, para->v);
  }
  tmp = (*para->reach) - tmp;
  return tmp;
}

BDD
check_DK(BDD next, string name, bdd_parameters * para)
{
  set < string > gi = (*is_groups)[name];
  BDD tmp = para->bddmgr->bddOne();
  BDD ntmp = (*para->reach) - next;
  vector<BDD> *v = para->v;

  if(gi.find((*agents)[0]->get_name()) == gi.end()) {
    map< string, basictype * >*envars = (*agents)[0]->get_vars();
    if(envars != NULL && envars->size() > 0) {
      set<string> *alllobs = new set<string>();
      for (set < string >::iterator igs = gi.begin(); igs != gi.end(); igs++) {
        basic_agent *agent = (*is_agents)[*igs];
        map< string, variable * >* lobs = agent->get_lobsvars();
        if (lobs != NULL && lobs->size() > 0)
          for (map< string, variable * >::iterator i = lobs->begin(); i != lobs->end(); i++)
            alllobs->insert(i->first);
      }
                        
      for (map< string, basictype * >::iterator i = envars->begin();
           i != envars->end(); i++) {
        if (alllobs->find(i->first) == alllobs->end()) {  
          basictype *bt = i->second;
          int index_begin = bt->get_index_begin();
          int index_end = bt->get_index_end();
          for (int j = index_begin; j <= index_end; j++)
            tmp = tmp * (*v)[j];
        }
      }
      delete alllobs;
    }
  }

  for (unsigned int i=1; i<agents->size(); i++) {
    basic_agent *agent = (*agents)[i];
    if(gi.find(agent->get_name()) == gi.end()) {
      int index_begin = agent->get_var_index_begin();
      int index_end = agent->get_var_index_end();
      for (int j = index_begin; j <= index_end; j++) {
        tmp = tmp * (*v)[j];
      }
    }
                
  }

  tmp = (*para->reach) - ntmp.ExistAbstract(tmp);
  return tmp;
}

BDD
check_GCK(BDD next, string name, bdd_parameters * para)
{
  // GCK p = GK(p * GCK(p)) see fhmv:rak, section 11.5
  BDD tmp = *para->reach;
  BDD tmp2 = next;
  set < string > gi = (*is_groups)[name];
  while (tmp != tmp2) {
    tmp2 = tmp;
    tmp = next * tmp;
    BDD ntmp = (*para->reach) - tmp;
    tmp = para->bddmgr->bddZero();
    for (set < string >::iterator igs = gi.begin(); igs != gi.end(); igs++) {
      basic_agent *agent = (*is_agents)[*igs];
      tmp += agent->project_local_state(&ntmp, para->bddmgr, para->v);
    }
    tmp = (*para->reach) - tmp;
  }
  return tmp;
}

BDD
check_ATLX(BDD next, string grpname, bdd_parameters * para)
{
  BDD result = para->bddmgr->bddZero();
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

  result = partial.ExistAbstract(actagtin) * (*para->reach);
  return result;
}

BDD
check_ATLG_aux(BDD p, string grpname, bdd_parameters * para)
{
  BDD tmp = p;
  BDD q = para->bddmgr->bddOne();
  while (q != tmp) {
    q = tmp;
    tmp = p * check_ATLX(tmp, grpname, para);
  }
  return q;
}

BDD
check_ATLG(BDD p, string grpname, bdd_parameters * para)
{
  if(is_fairness->empty()) {
    return check_ATLG_aux(p, grpname, para);
  } else
    return check_ATLG_fair(p, grpname, para);
}

BDD
check_ATLU(BDD q1, BDD q2, string grpname, bdd_parameters * para)
{
  BDD r = para->bddmgr->bddZero();
  BDD t = q2;
  while (t != r) {
    r = t;
    t = r + check_ATLX(r, grpname, para) * q1;
  }
  return r;
}

BDD
check_ATLX_fair(BDD next, string grpname, BDD fair_reach,
                bdd_parameters * para)
{
  return check_ATLX(next * fair_reach, grpname, para);
}

BDD
check_ATLG_fair(BDD p, string grpname, bdd_parameters * para)
{
  BDD tmp = para->bddmgr->bddZero();
  BDD q = para->bddmgr->bddOne();
  BDD fc_bdd = para->bddmgr->bddOne();
  while (q != tmp) {
    tmp = q;
    for (vector < fairness_expression * >::iterator fi =
           is_fairness->begin(); fi != is_fairness->end(); fi++) {
      BDD hf = (*fi)->get_bdd_representation(); // The BDD for the fairness constraint
      BDD tmp1 = check_ATLU(p, q * hf, grpname, para);
      
      fc_bdd = fc_bdd * check_ATLX(tmp1, grpname, para);
    }
    q = p * fc_bdd;
  }
  return q;
}

BDD
check_ATLU_fair(BDD q1, BDD q2, string grpname, BDD fair_reach,
                bdd_parameters * para)
{
  return check_ATLU(q1, q2 * fair_reach, grpname, para);
}

BDD
check_EG_fair(BDD p, bdd_parameters * para)
{
  // Computes the fixpoint iterating false
  // See "Efficient generation of counterexamples and witnesses in
  // symbolic model checking", Clarke Grumberg McMillan Zhao, 1995
  // Section 4, p.3
  return check_EG_fair(p, para, vector<BDD>());
}

BDD
check_EG_fair(BDD p, bdd_parameters * para, vector<BDD> additional_bdds)
{
  // Computes the fixpoint iterating false
  // See "Efficient generation of counterexamples and witnesses in
  // symbolic model checking", Clarke Grumberg McMillan Zhao, 1995
  // Section 4, p.3
  BDD tmp = para->bddmgr->bddZero();
  BDD q = para->bddmgr->bddOne();
  BDD fc_bdd = para->bddmgr->bddOne();
  while (q != tmp) {
    tmp = q;
    for (vector < fairness_expression * >::iterator fi =
           is_fairness->begin(); fi != is_fairness->end(); fi++) {
      BDD hf = (*fi)->get_bdd_representation(); // The BDD for the fairness constraint
      BDD tmp1 = check_EU(p, q * hf, para);
      fc_bdd = fc_bdd * check_EX(tmp1, para);
    }
    for (vector < BDD >::iterator it =
            additional_bdds.begin(); it != additional_bdds.end(); ++it) {
      BDD tmp1 = check_EU(para->bddmgr->bddOne(), q * (*it), para);
      fc_bdd = fc_bdd * check_EX(tmp1, para);
    }
    q = p * fc_bdd;
  }
  return q;
}

BDD
check_EG_fair_Qh(BDD p, bdd_parameters * para, vector< vector < BDD* >* >* Qh) 
{
  if(Qh->empty()) {
    for(unsigned int k=0; k<is_fairness->size(); k++) 
      Qh->push_back(new vector< BDD* >());
  }
  
  BDD tmp = para->bddmgr->bddZero();
  BDD q = para->bddmgr->bddOne();
  BDD fc_bdd = para->bddmgr->bddOne();
  //int x = 0;
  while (q != tmp) {
    tmp = q;
    //x = 0;
    for (unsigned int k=0; k<is_fairness->size(); k++) {
      BDD hf = (*is_fairness)[k]->get_bdd_representation(); // The BDD for the fairness constraint
      vector< BDD* >* qh = (*Qh)[k];
      if(!qh->empty()) {
        for(unsigned int j=0; j<qh->size(); j++) {
          BDD* t = qh->back();
          qh->pop_back();
          delete t;
        }
      }
      BDD tmp1 = check_EU_Qh(p, q * hf, para, qh);
      fc_bdd = fc_bdd * check_EX(tmp1, para);
      //x++;
    }
    q = p * fc_bdd;
  }
  return q;
}

BDD
check_EF_fair(BDD p, BDD fair_reach, bdd_parameters * para)
{
  return check_EU_fair(*para->reach, p, fair_reach, para);
}

BDD
check_EX_fair(BDD p, BDD fair_reach, bdd_parameters * para)
{
  return check_EX(p * fair_reach, para);
}

BDD
check_EU_fair(BDD p, BDD q, BDD fair_reach, bdd_parameters * para)
{
  return check_EU(p * fair_reach, q * fair_reach, para);
}

BDD
check_nO_fair(BDD next, string name, BDD fair_reach, bdd_parameters * para)
{
  // Check deontic
  next = next.SwapVariables(*para->v, *para->pv);       // Now it's the next state
  BDD RO = (*is_agents)[name]->encode_greenstates(para);
  BDD result = Exists(para->bddmgr, para->pv, RO * next * fair_reach);  // States from which...
  return result;
}

BDD
check_GK_fair(BDD next, string name, BDD fair_reach, bdd_parameters * para)
{
  set < string > gi = (*is_groups)[name];
  BDD tmp = para->bddmgr->bddZero();
  BDD ntmp = fair_reach - next;
  for (set < string >::iterator igs = gi.begin(); igs != gi.end(); igs++) {
    basic_agent *agent = (*is_agents)[*igs];
    tmp += agent->project_local_state(&ntmp, para->bddmgr, para->v);
  }
  tmp = (*para->reach) - tmp;
  return tmp;
}

BDD
check_DK_fair(BDD next, string name, BDD fair_reach, bdd_parameters * para)
{
  set < string > gi = (*is_groups)[name];
  BDD tmp = para->bddmgr->bddOne();
  BDD ntmp = fair_reach - next;
  for (set < string >::iterator igs = gi.begin(); igs != gi.end(); igs++) {
    basic_agent *agent = (*is_agents)[*igs];
    tmp *= agent->project_local_state(&ntmp, para->bddmgr, para->v);
  }
  tmp = (*para->reach) - tmp;
  return tmp;
}

BDD
check_GCK_fair(BDD next, string name, BDD fair_reach,
               bdd_parameters * para)
{
  // GCK p = GK(p * GCK(p)) see fhmv:rak, section 11.5
  BDD tmp = *para->reach;
  BDD tmp2 = next;
  set < string > gi = (*is_groups)[name];
  while (tmp != tmp2) {
    tmp2 = tmp;
    tmp = next * tmp;
    BDD ntmp = fair_reach - tmp;
    tmp = para->bddmgr->bddZero();
    for (set < string >::iterator igs = gi.begin(); igs != gi.end(); igs++) {
      basic_agent *agent = (*is_agents)[*igs];
      tmp += agent->project_local_state(&ntmp, para->bddmgr, para->v);
    }
    tmp = (*para->reach) - tmp;
  }
  return tmp;
}

BDD
get_K_states(BDD aset1, BDD * state, string name, bdd_parameters * para)
{
  basic_agent *agent = (*is_agents)[name];
  BDD localstate = agent->project_local_state(state, para->bddmgr, para->v);
  return aset1 * localstate;
}

BDD
get_nK_states(BDD * state, string name, bdd_parameters * para)
{
  basic_agent *agent = (*is_agents)[name];
  BDD localstate = agent->project_local_state(state, para->bddmgr, para->v);
  return (*para->reach) * localstate;
}

BDD
get_nK_states_fair(BDD * state, string name, BDD fair_reach,
                   bdd_parameters * para)
{
  basic_agent *agent = (*is_agents)[name];
  BDD localstate = agent->project_local_state(state, para->bddmgr, para->v);
  return fair_reach * localstate;
}

BDD
get_GK_states(BDD aset1, BDD * state, string name, bdd_parameters * para)
{
  BDD tmpaset1 = para->bddmgr->bddZero();
  set < string > names_g = (*is_groups)[name];
  for (set < string >::iterator igs = names_g.begin(); igs != names_g.end();
       igs++) {
    basic_agent *agent = (*is_agents)[*igs];
    BDD localstate = agent->project_local_state(state, para->bddmgr, para->v);
    tmpaset1 = tmpaset1 + (aset1 * localstate);
  }
  return tmpaset1;
}

BDD
get_DK_states(BDD aset1, BDD * state, string name, bdd_parameters * para)
{
  BDD tmpaset1 = aset1;
  set < string > names_g = (*is_groups)[name];
  for (set < string >::iterator igs = names_g.begin(); igs != names_g.end();
       igs++) {
    basic_agent *agent = (*is_agents)[*igs];
    BDD localstate = agent->project_local_state(state, para->bddmgr, para->v);
    tmpaset1 = tmpaset1 * localstate;
  }
  return tmpaset1;
}

DdNode *
addApplyLT(DdManager * mgr, DdNode ** n1, DdNode ** n2)
{
  DdNode *F, *G;
  F = *n1;
  G = *n2;
  if (F->index == CUDD_CONST_INDEX && G->index == CUDD_CONST_INDEX) {
    if (F->type.value < G->type.value)
      return mgr->one;

    else
      return mgr->zero;
  }
  return (NULL);
}

ADD
addLT(Cudd * bddmgr, ADD a1, ADD a2)
{
  DdNode *n1 = a1.getNode();
  DdNode *n2 = a2.getNode();
  DdNode *result = Cudd_addApply(bddmgr->getManager(), &addApplyLT, n1, n2);
  ADD res(*bddmgr, result);
  return res;
}

DdNode *
addApplyGT(DdManager * mgr, DdNode ** n1, DdNode ** n2)
{
  DdNode *F, *G;
  F = *n1;
  G = *n2;
  if (F->index == CUDD_CONST_INDEX && G->index == CUDD_CONST_INDEX) {
    if (F->type.value > G->type.value)
      return mgr->one;

    else
      return mgr->zero;
  }
  return (NULL);
}

ADD
addGT(Cudd * bddmgr, ADD a1, ADD a2)
{
  DdNode *n1 = a1.getNode();
  DdNode *n2 = a2.getNode();
  DdNode *result = Cudd_addApply(bddmgr->getManager(), &addApplyGT, n1, n2);
  ADD res(*bddmgr, result);
  return res;
}

DdNode *
addApplyEQ(DdManager * mgr, DdNode ** n1, DdNode ** n2)
{
  DdNode *F, *G;
  F = *n1;
  G = *n2;
  if (F->index == CUDD_CONST_INDEX && G->index == CUDD_CONST_INDEX) {
    if (F->type.value == G->type.value)
      return mgr->one;

    else
      return mgr->zero;
  }
  return (NULL);
}

ADD
addEQ(Cudd * bddmgr, ADD a1, ADD a2)
{
  DdNode *n1 = a1.getNode();
  DdNode *n2 = a2.getNode();
  DdNode *result = Cudd_addApply(bddmgr->getManager(), &addApplyEQ, n1, n2);
  ADD res(*bddmgr, result);
  return res;
}

DdNode *
addApplyGE(DdManager * mgr, DdNode ** n1, DdNode ** n2)
{
  DdNode *F, *G;
  F = *n1;
  G = *n2;
  if (F->index == CUDD_CONST_INDEX && G->index == CUDD_CONST_INDEX) {
    if (F->type.value >= G->type.value)
      return mgr->one;

    else
      return mgr->zero;
  }
  return (NULL);
}

ADD
addGE(Cudd * bddmgr, ADD a1, ADD a2)
{
  DdNode *n1 = a1.getNode();
  DdNode *n2 = a2.getNode();
  DdNode *result = Cudd_addApply(bddmgr->getManager(), &addApplyGE, n1, n2);
  ADD res(*bddmgr, result);
  return res;
}

DdNode *
addApplyLE(DdManager * mgr, DdNode ** n1, DdNode ** n2)
{
  DdNode *F, *G;
  F = *n1;
  G = *n2;
  if (F->index == CUDD_CONST_INDEX && G->index == CUDD_CONST_INDEX) {
    if (F->type.value <= G->type.value)
      return mgr->one;

    else
      return mgr->zero;
  }
  return (NULL);
}

ADD
addLE(Cudd * bddmgr, ADD a1, ADD a2)
{
  DdNode *n1 = a1.getNode();
  DdNode *n2 = a2.getNode();
  DdNode *result = Cudd_addApply(bddmgr->getManager(), &addApplyLE, n1, n2);
  ADD res(*bddmgr, result);
  return res;
}

DdNode *
addApplyNEQ(DdManager * mgr, DdNode ** n1, DdNode ** n2)
{
  DdNode *F, *G;
  F = *n1;
  G = *n2;
  if (F->index == CUDD_CONST_INDEX && G->index == CUDD_CONST_INDEX) {
    if (F->type.value != G->type.value)
      return mgr->one;

    else
      return mgr->zero;
  }
  return (NULL);
}

ADD
addNEQ(Cudd * bddmgr, ADD a1, ADD a2)
{
  DdNode *n1 = a1.getNode();
  DdNode *n2 = a2.getNode();
  DdNode *result = Cudd_addApply(bddmgr->getManager(), &addApplyNEQ, n1, n2);
  ADD res(*bddmgr, result);
  return res;
}

int
search_string_table(string * s)
{
  for (unsigned int i = 0; i < string_table->size(); i++)
    if (s->compare(*(*string_table)[i]) == 0)
      return i;
  return -1;
}

int
search_variable_table(variable * v)
{
  for (unsigned int i = 0; i < variable_table->size(); i++)
    if (v->equal_to((*variable_table)[i]))
      return i;
  return -1;
}

int
search_logic_expression_table(bool_expression * le)
{
  for (unsigned int i = 0; i < logic_expression_table->size(); i++)
    if (le->equal_to((*logic_expression_table)[i]))
      return i;
  return -1;
}
int
search_logic_expression_table(expression * e1, expression * e2)
{
  for (unsigned int i = 0; i < logic_expression_table->size(); i++)
    if (((*logic_expression_table)[i])->equal_to(e1, e2))
      return i;
  return -1;
}

int
search_logic_expression_table1(bool_expression * le)
{
  for (unsigned int i = 0; i < logic_expression_table1->size(); i++)
    if (le->equal_to((*logic_expression_table1)[i]))
      return i;
  return -1;
}
int
search_logic_expression_table1(expression * e1, expression * e2)
{
  for (unsigned int i = 0; i < logic_expression_table1->size(); i++)
    if (((*logic_expression_table1)[i])->equal_to(e1, e2))
      return i;
  return -1;
}
