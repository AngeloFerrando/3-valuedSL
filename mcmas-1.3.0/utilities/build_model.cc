#include <sys/timeb.h>
#include "utilities.hh"

void produce_witness(bdd_parameters *para, BDD state, string name);
BDD compute_reach(BDD in_st, vector<BDD> *v, vector<BDD> *pv, 
                  vector<BDD> *a, vector<BDD> *vRT, Cudd *bddmgr,
                  unsigned int *acounter1, int id, unsigned long *threadmem);
void 
do_statespace_generation(bdd_parameters * para)
{
  if ((options["quiet"] == 0 || options["simulation"] == 0) && options["uniform"] == 0) {
    cout << "Building reachable state space..." << endl;
  }

  struct timeb t0, t1;
  if (options["quiet"] == 0 && options["verbosity"] > 1)
    ftime(&t0);

  unsigned int acounter1 = 1;
  unsigned long threadmem = 0;
  BDD reach = compute_reach(*para->in_st, para->v, para->pv, para->a, para->vRT, para->bddmgr, &acounter1, 1, &threadmem);
    
  //time_t t2 = time(0);  
  para->reach = new BDD(reach);

  if (options["dao"] > 0) // 1: all disable, 2: after transition relation, 3: after reachable states
    Cudd_AutodynDisable(para->bddmgr->getManager());

  if (options["verbosity"] > 2)
    cout << "Done." << endl;

  if (options["quiet"] == 0 && options["verbosity"] > 1) {
    ftime(&t1);
    cout << "It took " << ((t1.time-t0.time) + (t1.millitm-t0.millitm)/1000.0) << " seconds to generate state space." << endl;
  }

  // Check deadlock of the model
  if(options["deadlock"] == 1) {
    BDD ex = check_EX(para->bddmgr->bddOne(), para);
    bool satisfaction = ex == reach;

    if(satisfaction) {
      if(options["quiet"] == 0) 
        cout << "There is no deadlock state in the model!" << endl;
    } else {  
      BDD diff = reach - ex;
      BDD state = diff.PickOneMinterm(*para->v);
      
      if(options["quiet"] == 0) {
        cout << "Attention: there are deadlock states in the model!" << endl;
        cout << "The following state does not have any successors." << endl;
        print_state(state, *para->v);
        cout << "----------------------------------------" << endl;
      }
  
      if(options["cex"] > 0) 
        produce_witness(para, state, "deadlock");   
    }
  }
  
  // Check arithmetic overflow in the model
  if (options["overflow"] == 1) {
    BDD state;
    bool flag = false;
    BDD rc = reach;
    unsigned int i, j=0;
    for(i=0; i<agents->size(); i++)
      rc *= (*para->vprot)[i];
    for(i=0; i<agents->size(); i++) {
      vector< evolution_line * >* evolution = (*agents)[i]->get_evolution();
      for(j=0; j<evolution->size(); j++) {
        BDD bddevline = (*evolution)[j]->encode_bdd_overflow(para);
        bddevline *= rc;
        if(bddevline != para->bddmgr->bddZero()) {
          state = bddevline.PickOneMinterm(*para->v);
          flag = true;
          break;
        }
      }
      if(flag)
        break;
    }
    if(flag) {
      if(options["quiet"] == 0) {
        cout << "Evolution item " << j+1 << " in Agent " << (*agents)[i]->get_name()
             << " can cause overflow in the following state: " << endl;
        print_state(state, *para->v);
        cout << "----------------------------------------" << endl;
      }
      if(options["cex"] > 0) 
        produce_witness(para, state, "overflow");
    }
  }

}
