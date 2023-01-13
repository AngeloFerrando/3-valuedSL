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

// #define num_of_threads1 2
// #define num_of_blocks 2
// #define time_of_iteration 5

extern Cudd_ReorderingType REORDERING;

extern void *compute_reach_parallel( void *ptr );
extern void allocate_bdd_variables(vector<BDD> *v, vector<ADD> *addv, 
                                   vector<BDD> *pv, vector<ADD> *addpv,
                                   vector<BDD> *a, Cudd *bddmgr);

BDD compute_reach(BDD in_st, vector<BDD> *v, vector<BDD> *pv, 
                  vector<BDD> *a, vector<BDD> *vRT, Cudd *bddmgr,
                  unsigned int *acounter1, int id, unsigned long *threadmem) {
  BDD reach;

  /*BDD cubev = bddmgr->bddOne();	
  for (int j = 0; j < v->count(); j++) 
    cubev = cubev * (*v)[j];
  BDD cubea = bddmgr->bddOne();	
	for (int j = 0; j < a->count(); j++) 
	cubea = cubea * (*a)[j]; */

  if (options["experiment"] == 1) {
    reach = bddmgr->bddZero();
    BDD q1 = in_st;
    BDD next1 = bddmgr->bddZero();
    
    while (q1 != reach) {
      if (options["verbosity"] > 0)
        cout << "    Computing depth " << *acounter1 << endl;
      
      reach = q1;
      next1 = q1;
      for (unsigned int k = 0; k < agents->size(); k++)
        next1 *= (*vRT)[k];
      next1 = Exists(bddmgr, v, next1);
      next1 = next1.SwapVariables(*v, *pv);
      next1 = Exists(bddmgr, a, next1); // Clear actions.
      
      q1 = q1 + next1;
      (*acounter1)++;
    }
    
    if (options["verbosity"] > 2) {
      cout << "Done" << endl;
    }
  } else if (options["experiment"] == 2) {  // BMC goes here
    reach = in_st;
    BDD q1 = bddmgr->bddZero();
    BDD next1 = in_st;
    while (true) {
      if (options["verbosity"] > 0)
        cout << "    Computing depth " << *acounter1 << endl;
      
      for (unsigned int k = 0; k < agents->size(); k++)
        next1 *= (*vRT)[k];
 			next1 = Exists(bddmgr, v, next1);
      next1 = next1.SwapVariables(*v, *pv);
      next1 = Exists(bddmgr, a, next1); // Clear actions.
			q1 = reach + next1;
      (*acounter1)++;
      
      if (q1 == reach)
        break;
      else
        reach = q1;
    }
    
    if (options["verbosity"] > 2) {
      cout << "Done" << endl;
    }
  } else {  
    reach = in_st;
    BDD next1 = in_st;
    while (true) {
      if (options["verbosity"] > 0)
        cout << "    Computing depth " << *acounter1 << endl;
      
      for (unsigned int k = 0; k < agents->size(); k++)
        next1 *= (*vRT)[k];
			next1 = Exists(bddmgr, v, next1);
      next1 = next1.SwapVariables(*v, *pv);
      next1 = Exists(bddmgr, a, next1); // Clear actions.
      next1 = next1 - reach;
      (*acounter1)++;
      
      if (next1 == bddmgr->bddZero())
        break;
      else
        reach = reach + next1;
    }
    
    if (options["verbosity"] > 2) {
      cout << "Done" << endl;
    }
  }

  return reach;
}

