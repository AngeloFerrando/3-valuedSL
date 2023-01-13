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
#include <limits>
#include "types.hh"
#include "utilities.hh"
#include "cuddObj.hh"

#define MAXINISTATES 100
#define MAXTRANSITIONS 100
#define MAXSTACKDEPTH 100

extern vector<string *> *string_table;
extern vector<bool_expression *> *logic_expression_table;
extern vector<bool_expression *> *logic_expression_table1;
extern vector<variable *> *variable_table;
extern map<string, basic_agent *> *is_agents;
extern vector<basic_agent *> *agents;
extern map<string, bool_expression *> *is_evaluation;
extern bool_expression *is_istates;
extern map<string, set<string> > *is_groups;
extern vector<modal_formula> *is_formulae;
extern vector<fairness_expression *> *is_fairness;
extern map < string, int > options;
extern Cudd_ReorderingType REORDERING;

extern BDD append_variable_BDDs(Cudd *bddmgr, vector<BDD> *v, BDD a);
extern bool is_valid_state(BDD state, vector<BDD> v);
extern bool is_valid_action(BDD state, vector<BDD> a);
extern bool find_same_state(map<string, int> *statehash, string state);
extern void print_action_1(BDD state, vector<BDD> a);
extern string state_to_str(BDD state, vector<BDD> v);
extern void print_state(BDD state, vector<BDD> v);
extern void print_action(BDD state, vector<BDD> a);
extern BDD Exists(Cudd *bddmgr, vector<BDD>* v, BDD x);

map<string, map<string, vector<BDD*>* >* >*
integer_variable_BDDs(Cudd * bddmgr, vector<BDD> * v)
{
  map<string, map<string, vector<BDD*>* >* >* int_vars = NULL;
  for (unsigned int j = 0; j < agents->size(); j++) {
    map<string, vector<BDD*>* >* int_var = NULL;
    map< string, basictype * >*obsvars = (*agents)[j]->get_obsvars();
    if (obsvars != NULL && obsvars->size() > 0)
      for (map< string, basictype * >::iterator i =
             obsvars->begin(); i != obsvars->end(); i++) {
        if ((*i).second->get_type() == 2) {
          rangedint *x = (rangedint *) (*i).second;
          unsigned int d = (unsigned int) (x->get_upperbound() - x->get_lowerbound() + 1);
          if(d & (d-1)) {
            vector<BDD*> *bddblocks = new vector<BDD*>();
            x->build_individual_BDD(bddmgr, v, bddblocks, d);
            if(int_var == NULL)
              int_var = new map<string, vector<BDD*>* >();
            (*int_var)[i->first] = bddblocks;
          }
        }
      }
    map< string, basictype * >*vars = (*agents)[j]->get_vars();
    if (vars != NULL && vars->size() > 0)
      for (map< string, basictype * >::iterator i = vars->begin();
           i != vars->end(); i++) {
        if ((*i).second->get_type() == 2) {
          rangedint *x = (rangedint *) (*i).second;
          unsigned int d = (unsigned int) (x->get_upperbound() - x->get_lowerbound() + 1);
          if(d & (d-1)) {
            vector<BDD*> *bddblocks = new vector<BDD*>();
            x->build_individual_BDD(bddmgr, v, bddblocks, d);
            if(int_var == NULL)
              int_var = new map<string, vector<BDD*>* >();
            (*int_var)[i->first] = bddblocks;
          }
        }
      }
    if(int_var != NULL) {
      if(int_vars == NULL)
        int_vars = new map<string, map<string, vector<BDD*>* >* >();
      (*int_vars)[(*agents)[j]->get_name()] = int_var;
    }
  }
  return int_vars;
}

void
clear_integer_BDDs(map<string, map<string, vector<BDD*>* >* >* int_vars)
{
  if(int_vars != NULL) {
    for (map<string, map<string, vector<BDD*>* >* >::iterator iter =
           int_vars->begin(); iter != int_vars->end(); iter++) {
      map<string, vector<BDD*>* >* int_var = iter->second;
      for (map<string, vector<BDD*>* >::iterator iter1 =
             int_var->begin(); iter1 != int_var->end(); iter1++) {
        vector<BDD*>* bddblocks = iter1->second;
        for(unsigned int i=0; i<bddblocks->size(); i++)
          delete (*bddblocks)[i];
        delete bddblocks;
      }
      delete int_var;
    }
    delete int_vars;
  }
}

BDD
complete_integer_BDDs(Cudd * bddmgr, vector<BDD> * v, BDD a, map<string, map<string, vector<BDD*>* >* >* int_vars)
{
  if(int_vars != NULL) {
    BDD b = a;
    for (map<string, map<string, vector<BDD*>* >* >::iterator iter =
           int_vars->begin(); iter != int_vars->end(); iter++) {
      map<string, vector<BDD*>* >* int_var = iter->second;
      basic_agent *agent = (*is_agents)[iter->first];
      map< string, basictype * >*obsvars = agent->get_obsvars();
      map< string, basictype * >*vars = agent->get_vars();
     
      for (map<string, vector<BDD*>* >::iterator iter1 =
             int_var->begin(); iter1 != int_var->end(); iter1++) {
        vector<BDD*>* bddblocks = iter1->second;
        rangedint *x = NULL;
        if(obsvars != NULL) {
          map< string, basictype * >::iterator p = obsvars->find(iter1->first);
          if( p != obsvars->end()) 
            x = (rangedint *)p->second;
        }
        if(x == NULL && vars != NULL) {
          map< string, basictype * >::iterator p = vars->find(iter1->first);
          if( p != vars->end()) 
            x = (rangedint *)p->second;
        }
        int index_begin = x->get_index_begin();
        int index_end = x->get_index_end();
        BDD tmp = bddmgr->bddOne();
        for (int j = index_begin; j <= index_end; j++)
          tmp = tmp * (*v)[j];
        for(unsigned int i=0; i<bddblocks->size(); i++) {
          if(b * (*(*bddblocks)[i]) != bddmgr->bddZero()) {
            b = b.ExistAbstract(tmp);
            b = b * (*(*bddblocks)[i]); 
            break;
          }
        }
      }
    }
    return b;
  } else
    return a;
}

void exec_simulation(void *ptr) {
  bdd_parameters *para;
  para = (bdd_parameters *)ptr;
  Cudd* bddmgr = para->bddmgr; 
  vector<BDD> *v = para->v;
  vector<ADD> *addv = para->addv;
  vector<BDD> *pv = para->pv;
  vector<ADD> *addpv = para->addpv;
  vector<BDD> *a = para->a;
  vector<BDD> *vevol = para->vevol;
  vector<BDD> *vprot = para->vprot;
  vector<BDD> *vRT = para->vRT;
  BDD in_st;

  Cudd_AutodynEnable(bddmgr->getManager(), REORDERING);
  in_st = is_istates->encode_bdd_flat(para, bddmgr->bddOne());
  in_st = append_variable_BDDs(bddmgr, v, in_st);
  if (in_st==bddmgr->bddZero()) {
    cout << "No initial state. Check your model!" << endl;
    return;
  }

  map<string, map<string, vector<BDD*>* >* >* int_vars = integer_variable_BDDs(bddmgr, v);

  for (unsigned int i=0; i<agents->size(); i++) {
    vprot->push_back((*agents)[i]->encode_protocol(para));
    if(options["smv"] == 0)
      vevol->push_back((*agents)[i]->encode_evolution(para));
    else
      vevol->push_back((*agents)[i]->encode_evolution_smv(para));
    vRT->push_back((*vprot)[i] * (*vevol)[i]);
  }
  REORDERING = options["dyn"] == 1 ? CUDD_REORDER_GROUP_SIFT : CUDD_REORDER_SIFT; 
  Cudd_AutodynEnable(bddmgr->getManager(), REORDERING);  
  vector<BDD> inistates;
  int count=0;
  BDD is = in_st;
  map<string, int> statehash;
  while (count<MAXINISTATES && is != bddmgr->bddZero()) {
    if(count >= inistates.size())
      inistates.push_back(is.PickOneMinterm(*v));
    else
      inistates[count] = is.PickOneMinterm(*v);
    is = is - inistates[count];
    if (is_valid_state(inistates[count], *v)) {
      string state = state_to_str(inistates[count], *v);
      if(!find_same_state(&statehash, state)) {
        statehash[state] = 1;
        count++;
      }
    }
  }
  if(options["quiet"] == 0) {
    if (count==MAXINISTATES && is != bddmgr->bddZero())
      cout << "There are too many initial states. Please specify more initial values."
           << endl;
    while (true) {
      vector<BDD> stack;
      int sp = 0;
      cout << endl << "--------- Initial state ---------" << endl;
      int isindex = 0;
      print_state(inistates[isindex], *v);
      cout << "----------------------------" << endl;
      if (count>1) {
        bool choose = false;
        string c;
        while (!choose) {
          if (isindex==0)
            cout << "Is this the initial state? [Y(es), N(ext), E(xit)]: ";
          else if (isindex==count-1)
            cout << "Is this the initial state? [Y(es), P(revious), E(xit)]: ";
          else
            cout << "Is this the initial state? [Y(es), N(ext), P(revious), E(xit)]: ";
          cin >> c;
          transform(c.begin(), c.end(), c.begin(),
                    (int(*)(int))tolower);
          if (c=="y" || c=="yes") {
            choose = true;
            break;
          } else if ((isindex<count-1) && (c=="n" || c =="next")) {
            isindex++;
            cout << endl << "--------- Initial state ---------"
                 << endl;
            print_state(inistates[isindex], *v);
            cout << "----------------------------" << endl;
          } else if (isindex>0 && (c=="p" || c=="previous")) {
            isindex--;
            cout << endl << "--------- Initial state ---------"
                 << endl;
            print_state(inistates[isindex], *v);
            cout << "----------------------------" << endl;
          } else if (c=="e" || c=="exit" || cin.eof()) {
            return;
          }
          else
            cout << "Please choose one option!" << endl;
        }
      }
      stack.push_back(inistates[isindex]); // initial state
      sp++;
      while (true) {
        vector<BDD> enabled;
        int tcount = 0;
        BDD newstates;
        int tran = -2;
        if (sp>=MAXSTACKDEPTH) {
          cout <<"Maximum stack depth is reached. Please type 0 to backtrack or -1 to quit immediately: ";
          while (!(cin >> tran) || (tran!=-1 && tran!=0)) {
            if (cin.eof())
              return;
            cout << "Error. You have entered an invalid input." << endl;
            cout << "Maximum stack depth is reached. Please type 0 to backtrack or -1 to quit immediately: ";
            cin.clear();
            cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
          }
        } else {
          newstates = stack[sp-1];// next state
          for(unsigned int k=0; k<agents->size(); k++)
            newstates *= (*vRT)[k];
          BDD transitions = newstates;
          if(newstates != bddmgr->bddZero()) {
            while (tcount<MAXTRANSITIONS && transitions != bddmgr->bddZero()) {
              if(tcount >= enabled.size())
                enabled.push_back(transitions.PickOneMinterm(*a));
              else
                enabled[tcount] = transitions.PickOneMinterm(*a);
              transitions-=enabled[tcount];
              if (is_valid_action(enabled[tcount], *a))
                tcount++;
            }
          }
          if (tcount==MAXTRANSITIONS && transitions != bddmgr->bddZero())
            cout << "There are too many enabled actions. We only pick up 100 of them." << endl;
          if (tcount>0) {
            cout << "Enabled actions: "<< endl;
            for (int i=0; i<tcount; i++) {
              cout << i+1 << " : ";
              print_action(enabled[i], *a);
            }
            cout << "Please choose one, or type 0 to backtrack or -1 to quit: " << endl;
            while (!(cin >> tran) || (tran<-1 || tran>tcount)) {
              if (cin.eof())
                return;
              cout << "Error. You have entered an invalid input." << endl;
              cout << "Please choose one, or type 0 to backtrack or -1 to quit: " << endl;
              cin.clear();
              cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
            }
          } else {
            if(sp > 1 || count > 1) {
              cout << "There is no enabled action. Please type 0 to backtrack or -1 to quit immediately: ";
              while(!(cin >> tran) || (tran!=-1 && tran!=0)) {
                if (cin.eof())
                  return;
                cout << "Error. You have entered an invalid input." << endl;
                cout << "Maximum stack depth is reached. Please type 0 to backtrack or -1 to quit immediately: ";
                cin.clear();
                cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
              }
            } else {
              cout << "There is no enabled action in the initial state. Simulation exits." << endl;
              return;
            }
          }
        }
        if(tran==-1 || cin.eof()) {
          return;
        }
        else if(tran==0 && sp>1) {
          stack[--sp] = bddmgr->bddZero();
          continue;
        } else if(tran==0 && sp==1) {
          stack[--sp] = bddmgr->bddZero();
          break;
        } else {
          newstates *= enabled[tran-1];
          BDD tmpstate = Exists(bddmgr, v, newstates); // clear state variables
          tmpstate = tmpstate.SwapVariables(*v, *pv);
          tmpstate = Exists(bddmgr, a, tmpstate); // clear action variables
          tmpstate = append_variable_BDDs(bddmgr, v, tmpstate);
          int count1=0;
          vector<BDD> succstates;
          statehash.clear();
          while (count1<MAXINISTATES && tmpstate != bddmgr->bddZero()) {
            if(count1 >= succstates.size())
              succstates.push_back(tmpstate.PickOneMinterm(*v));
            else
              succstates[count1] = tmpstate.PickOneMinterm(*v);
            succstates[count1] = complete_integer_BDDs(bddmgr, v, succstates[count1], int_vars);
            tmpstate = tmpstate - succstates[count1];
            if (is_valid_state(succstates[count1], *v)) {
              string state = state_to_str(succstates[count1], *v);
              if(!find_same_state(&statehash, state)) {
                statehash[state] = 1;
                count1++;
              }
            }
          }
          if (count1==MAXINISTATES && tmpstate != bddmgr->bddZero())
            cout
              << "There are too many states. Please refine your model."
              << endl;
          else if(count1>1)
            cout << "Warning: there is more than one successor state." << endl;
          cout << endl << "--------- Current state ---------" << endl;
          int succindex = 0;
          print_state(succstates[succindex], *v);
          cout << "----------------------------" << endl;
          if (count1>1) {
            bool choose = false;
            string c;
            while (!choose) {
              if (succindex==0)
                cout
                  << "Is this the current state? [Y(es), N(ext), E(xit)]: ";
              else if (succindex==count1 -1)
                cout
                  << "Is this the current state? [Y(es), P(revious), E(xit)]: ";
              else
                cout
                  << "Is this the current state? [Y(es), N(ext), P(revious), E(xit)]: ";
              cin >> c;
              transform(c.begin(), c.end(), c.begin(),
                        (int(*)(int))tolower);
              if (c=="y" || c=="yes") {
                choose = true;
                break;
              } else if ((succindex<count1-1) && (c=="n" || c =="next")) {
                succindex++;
                cout << endl << "--------- Current state ---------"
                     << endl;
                print_state(succstates[succindex], *v);
                cout << "----------------------------" << endl;
              } else if (succindex>0 && (c=="p" || c=="previous")) {
                succindex--;
                cout << endl << "--------- Initial state ---------"
                     << endl;
                print_state(succstates[succindex], *v);
                cout << "----------------------------" << endl;
              } else if (c=="e" || c=="exit") {
                return;
              }
              else
                cout << "Please choose one option!" << endl;
            }
          }
          if(sp >= stack.size()) {
            stack.push_back(succstates[succindex]);
            sp++;
          } else
            stack[sp++] = succstates[succindex];
        }
      }
    }
  } else {
    while (true) {
      vector<BDD> stack;
      int sp = 0;
      for(int k=0; k<count; k++) {
        cout << endl << "-- State " << (k+1) << " --" << endl;
        print_state(inistates[k], *v);
      }
      cout << "Done." << endl;
      int isindex = 0;;
      cin >> isindex;
      if(isindex==-1 || cin.eof()) {
        return;
      }
      if(sp >= stack.size()) {
        stack.push_back(inistates[isindex-1]);
        sp++;
      } else
        stack[sp++] = inistates[isindex-1]; // initial state
      while (true) {
        vector<BDD> enabled;
        int tcount = 0;
        BDD newstates;
        int tran = -2;
        if (sp>=MAXSTACKDEPTH) {
          while (tran!=-1 && tran!=0) {
            cout <<"Maximum stack depth is reached. Please backtrack or quit.";
            cin >> tran;
          }
        } else {
          newstates = stack[sp-1];// next state
          for(unsigned int k=0; k<agents->size(); k++)
            newstates *= (*vRT)[k];
          BDD transitions = newstates;
          if(newstates != bddmgr->bddZero()) {
            while (tcount<MAXTRANSITIONS && transitions != bddmgr->bddZero()) {
              if(tcount >= enabled.size())
                enabled.push_back(transitions.PickOneMinterm(*a));
              else
                enabled[tcount] = transitions.PickOneMinterm(*a);
              transitions-=enabled[tcount];
              if (is_valid_action(enabled[tcount], *a))
                tcount++;
            }
          }
          if (tcount>0) {
            for (int i=0; i<tcount; i++) {
              cout << "-- transition "<< (i+1) << " --" << endl;
              print_action_1(enabled[i], *a);
            }
            cout << "Done." << endl;
            while (tran<-1 || tran>tcount) {
              cin >> tran;
            }
          } else {
            if(sp > 1 || count > 1) {
              cout << "There is no enabled action. Please backtrack or quit.";
              cin >> tran;
            } else {
              cout << "There is no enabled action in the initial state." << endl;
              return;
            }
          }
        }
        if(tran==-1 || cin.eof()){
          return;
        }
        else if(tran==0 && sp>1) {
          stack[--sp] = bddmgr->bddZero();
          continue;
        } else if(tran==0 && sp==1) {
          stack[--sp] = bddmgr->bddZero();
          break;
        } else {
          newstates *= enabled[tran-1];
          BDD tmpstate = Exists(bddmgr, v, newstates); // clear state variables
          tmpstate = tmpstate.SwapVariables(*v, *pv);
          tmpstate = Exists(bddmgr, a, tmpstate); // clear action variables
          tmpstate = append_variable_BDDs(bddmgr, v, tmpstate);
          int count1=0;
          vector<BDD> succstates;
          statehash.clear();
          while (count1<MAXINISTATES && tmpstate != bddmgr->bddZero()) {
            if(count1 >= succstates.size())
              succstates.push_back(tmpstate.PickOneMinterm(*v));
            else
              succstates[count1] = tmpstate.PickOneMinterm(*v);
            succstates[count1] = complete_integer_BDDs(bddmgr, v, succstates[count1], int_vars);
            tmpstate = tmpstate - succstates[count1];
            if (is_valid_state(succstates[count1], *v)) {
              string state = state_to_str(succstates[count1], *v);
              if(!find_same_state(&statehash, state)) {
                statehash[state] = 1;
                count1++;
              }
            }
          }
          for(int k=0; k<count1; k++) {
            cout << endl << "-- State " << (k+1) << " --" << endl;
            print_state(succstates[k], *v);
          }
          cout << "Done." << endl;
          int succindex = 0;
          cin >> succindex;
          if(succindex == -1){
            return;
          }
          if(succindex > 0) {
            if(sp >= stack.size()) {
              stack.push_back(succstates[succindex-1]);
              sp++;
            } else
              stack[sp++] = succstates[succindex-1];
          }
        }
      }
    }
  }
  clear_integer_BDDs(int_vars);
}
