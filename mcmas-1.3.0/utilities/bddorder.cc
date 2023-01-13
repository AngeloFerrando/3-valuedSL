#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <cctype>
#include <ctime>
#include "types.hh"
#include "utilities.hh"
#include "cuddObj.hh"

void allocate_bdd_variables(vector<BDD> *v, vector<ADD> *addv, 
                            vector<BDD> *pv, vector<ADD> *addpv,
                            vector<BDD> *a, Cudd *bddmgr) {
  if (options["ordering"] == 1) {
    for (int i = 0; i < states_count; i++) {
      v->push_back(bddmgr->bddVar(i));
      pv->push_back(bddmgr->bddVar(states_count + i));
      if(addv != NULL) {
        addv->push_back(bddmgr->addVar(i));
        addpv->push_back(bddmgr->addVar(states_count + i));
      }
    }
    for (int i = 0; i < actions_count; i++)
      a->push_back(bddmgr->bddVar(states_count * 2 + i));
    if (options["bddgroup"] >= 2)
      for (unsigned int i = 0; i < agents->size(); i++) {
        basic_agent *agent = (*agents)[i];
        vector< basictype * >*vec_obsvars = agent->get_vec_obsvars();
        vector< basictype * >*vec_vars = agent->get_vec_vars();
        if (vec_obsvars != NULL)
          for (unsigned int j = 0; j < vec_obsvars->size(); j++) {
            int a1 = (*vec_obsvars)[j]->get_index_begin();
            int a2 = (*vec_obsvars)[j]->get_index_end();
            Cudd_MakeTreeNode(bddmgr->getManager(), a1,
                              a2 - a1 + 1, MTR_DEFAULT);
            Cudd_MakeTreeNode(bddmgr->getManager(),
                              states_count + a1, a2 - a1 + 1,
                              MTR_DEFAULT);
          }
        if (vec_vars != NULL)
          for (unsigned int j = 0; j < vec_vars->size(); j++) {
            int a1 = (*vec_vars)[j]->get_index_begin();
            int a2 = (*vec_vars)[j]->get_index_end();
            Cudd_MakeTreeNode(bddmgr->getManager(), a1,
                              a2 - a1 + 1,
                              MTR_DEFAULT);
            Cudd_MakeTreeNode(bddmgr->getManager(),
                              states_count + a1, a2 - a1 + 1,
                              MTR_DEFAULT);
          }
      }
    if (options["bddgroup"] == 3) {
      int l = 0;
      for (unsigned int i = 0; i < agents->size(); i++) {
        Cudd_MakeTreeNode(bddmgr->getManager(),
                          states_count * 2 + l,
                          (*agents)[i]->actions_BDD_length(),
                          MTR_DEFAULT);
        l += (*agents)[i]->actions_BDD_length();
      }
    }
  } else if (options["ordering"] == 2) {
    int tmp_sum = 0;
    //int tmp_states_count = 0;
    //int tmp_actions_count = 0;
    for (unsigned int i = 0; i < agents->size(); i++) {
      for (int j = 0; j < (*agents)[i]->state_BDD_length(); j++) {
        v->push_back(bddmgr->bddVar(tmp_sum + j * 2));
        pv->push_back(bddmgr->bddVar(tmp_sum + j * 2 + 1));
        if(addv != NULL) {
          addv->push_back(bddmgr->addVar(tmp_sum + j * 2));
          addpv->push_back(bddmgr->addVar(tmp_sum + j * 2 + 1));
        }
        if (options["bddgroup"] == 1)
          Cudd_MakeTreeNode(bddmgr->getManager(),
                            tmp_sum + j * 2, 2, MTR_FIXED);
      }

      if (options["bddgroup"] >= 2) {
        basic_agent *agent = (*agents)[i];
        vector< basictype * >*vec_obsvars = agent->get_vec_obsvars();
        vector< basictype * >*vec_vars = agent->get_vec_vars();
        int l = 0;
        if (vec_obsvars != NULL)
          for (unsigned int k = 0; k < vec_obsvars->size(); k++) {
            Cudd_MakeTreeNode(bddmgr->getManager(),
                              tmp_sum + l,
                              (*vec_obsvars)[k]->BDD_length() * 2,
                              MTR_DEFAULT);
            l += (*vec_obsvars)[k]->BDD_length() * 2;
          }
        if (vec_vars != NULL)
          for (unsigned int k = 0; k < vec_vars->size(); k++) {
            Cudd_MakeTreeNode(bddmgr->getManager(),
                              tmp_sum + l,
                              (*vec_vars)[k]->BDD_length() * 2,
                              MTR_DEFAULT);
            l += (*vec_vars)[k]->BDD_length() * 2;
          }
      }
      tmp_sum += (*agents)[i]->state_BDD_length() * 2;
      //tmp_states_count += (*agents)[i]->state_BDD_length();
      for (unsigned int j = 0; j < (*agents)[i]->actions_BDD_length(); j++) {
        a->push_back(bddmgr->bddVar(tmp_sum + j));
      }
      if (options["bddgroup"] == 3)
        Cudd_MakeTreeNode(bddmgr->getManager(), tmp_sum,
                          (*agents)[i]->actions_BDD_length(),
                          MTR_DEFAULT);
      tmp_sum += (*agents)[i]->actions_BDD_length();
      //tmp_actions_count += (*agents)[i]->actions_BDD_length();
    }
  } else if (options["ordering"] == 3) {
    int tmp_sum = 0;
    //int tmp_states_count = 0;
    //int tmp_actions_count = 0;
    for (unsigned int i = 0; i < agents->size(); i++) {
      for (int j = 0; j < (*agents)[i]->state_BDD_length(); j++) {
        v->push_back(bddmgr->bddVar(tmp_sum + j));
        if(addv != NULL) 
          addv->push_back(bddmgr->addVar(tmp_sum + j));
      }
      if (options["bddgroup"] >= 2) {
        basic_agent *agent = (*agents)[i];
        vector< basictype * >*vec_obsvars = agent->get_vec_obsvars();
        vector< basictype * >*vec_vars = agent->get_vec_vars();
        int l = 0;
        if (vec_obsvars != NULL)
          for (unsigned int k = 0; k < vec_obsvars->size(); k++) {
            Cudd_MakeTreeNode(bddmgr->getManager(),
                              tmp_sum + l,
                              (*vec_obsvars)[k]->BDD_length(),
                              MTR_DEFAULT);
            l += (*vec_obsvars)[k]->BDD_length();
          }
        if (vec_vars != NULL)
          for (unsigned int k = 0; k < vec_vars->size(); k++) {
            Cudd_MakeTreeNode(bddmgr->getManager(),
                              tmp_sum + l,
                              (*vec_vars)[k]->BDD_length(),
                              MTR_DEFAULT);
            l += (*vec_vars)[k]->BDD_length();
          }
      }
      tmp_sum += (*agents)[i]->state_BDD_length();
      for (unsigned int j = 0; j < (*agents)[i]->actions_BDD_length(); j++) {
        a->push_back(bddmgr->bddVar(tmp_sum + j));
      }
      if (options["bddgroup"] == 3)
        Cudd_MakeTreeNode(bddmgr->getManager(), tmp_sum,
                          (*agents)[i]->actions_BDD_length(),
                          MTR_DEFAULT);
      tmp_sum += (*agents)[i]->actions_BDD_length();
      //tmp_actions_count += (*agents)[i]->actions_BDD_length();
      for (int j = 0; j < (*agents)[i]->state_BDD_length(); j++) {
        pv->push_back(bddmgr->bddVar(tmp_sum + j));
        if(addpv != NULL) 
          addpv->push_back(bddmgr->addVar(tmp_sum + j));
      }
      if (options["bddgroup"] >= 2) {
        basic_agent *agent = (*agents)[i];
        vector< basictype * >*vec_obsvars = agent->get_vec_obsvars();
        vector< basictype * >*vec_vars = agent->get_vec_vars();
        int l = 0;
        if (vec_obsvars != NULL)
          for (unsigned int k = 0; k < vec_obsvars->size(); k++) {
            Cudd_MakeTreeNode(bddmgr->getManager(),
                              tmp_sum + l,
                              (*vec_obsvars)[k]->BDD_length(),
                              MTR_DEFAULT);
            l += (*vec_obsvars)[k]->BDD_length();
          }
        if (vec_vars != NULL)
          for (unsigned int k = 0; k < vec_vars->size(); k++) {
            Cudd_MakeTreeNode(bddmgr->getManager(),
                              tmp_sum + l,
                              (*vec_vars)[k]->BDD_length(),
                              MTR_DEFAULT);
            l += (*vec_vars)[k]->BDD_length();
          }
      }
      //tmp_states_count += (*agents)[i]->state_BDD_length();
      tmp_sum += (*agents)[i]->state_BDD_length();
    }
  } else if (options["ordering"] == 4) {
    int tmp_sum = 0;
    int tmp_states_count = 0;
    int tmp_actions_count = 0;
    for (unsigned int i = 0; i < agents->size(); i++) {
      for (int j = 0; j < (*agents)[i]->state_BDD_length(); j++) {
        v->push_back(bddmgr->bddVar(tmp_sum + j));
        pv->push_back(bddmgr->bddVar(tmp_sum + (*agents)[i]->state_BDD_length() + j));
        if(addv != NULL) {
          addv->push_back(bddmgr->addVar(tmp_sum + j));
          addpv->push_back(bddmgr->addVar(tmp_sum + (*agents)[i]->state_BDD_length() + j));
        }
      }
      if (options["bddgroup"] >= 2) {
        basic_agent *agent = (*agents)[i];
        vector< basictype * >*vec_obsvars = agent->get_vec_obsvars();
        vector< basictype * >*vec_vars = agent->get_vec_vars();
        int l = 0;
        if (vec_obsvars != NULL)
          for (unsigned int k = 0; k < vec_obsvars->size(); k++) {
            Cudd_MakeTreeNode(bddmgr->getManager(),
                              tmp_sum + l,
                              (*vec_obsvars)[k]->BDD_length(),
                              MTR_DEFAULT);
            Cudd_MakeTreeNode(bddmgr->getManager(),
                              tmp_sum +
                              (*agents)[i]->state_BDD_length() + l,
                              (*vec_obsvars)[k]->BDD_length(),
                              MTR_DEFAULT);
            l += (*vec_obsvars)[k]->BDD_length();
          }
        if (vec_vars != NULL)
          for (unsigned int k = 0; k < vec_vars->size(); k++) {
            Cudd_MakeTreeNode(bddmgr->getManager(),
                              tmp_sum + l,
                              (*vec_vars)[k]->BDD_length(),
                              MTR_DEFAULT);
            Cudd_MakeTreeNode(bddmgr->getManager(),
                              tmp_sum +
                              (*agents)[i]->state_BDD_length() + l,
                              (*vec_vars)[k]->BDD_length(),
                              MTR_DEFAULT);
            l += (*vec_vars)[k]->BDD_length();
          }
      }
      tmp_sum += (*agents)[i]->state_BDD_length() * 2;
      //tmp_states_count += (*agents)[i]->state_BDD_length();
      for (unsigned int j = 0; j < (*agents)[i]->actions_BDD_length(); j++) {
        a->push_back(bddmgr->bddVar(tmp_sum + j));
      }
      if (options["bddgroup"] == 3)
        Cudd_MakeTreeNode(bddmgr->getManager(), tmp_sum,
                          (*agents)[i]->actions_BDD_length(),
                          MTR_DEFAULT);
      tmp_sum += (*agents)[i]->actions_BDD_length();
      //tmp_actions_count += (*agents)[i]->actions_BDD_length();
    }
  }
}
