#include "utilities.hh"
#include <sys/timeb.h>
#include <queue> 

using namespace std;

extern string cex_prefix;  
extern bool *satisfied;
extern unsigned int num_of_satisfied;
bool is_valid_state(BDD state, vector<BDD> v);

void 
do_model_checking(bdd_parameters * para)
{
  if (options["quiet"] == 0 && options["uniform"] == 0)
    cout << "Checking formulae..." << endl;

  BDD fair_reach;
  BDD in_st = *(para->in_st);
        
  struct timeb tmb_mc, tmb_mc1;
  if(options["verbosity"] > 1) 
    ftime(&tmb_mc);
    
  string str = "_init";
  (*is_evaluation)[str] = is_istates;
  modal_formula *init = new modal_formula(new atomic_proposition(&str));

  if (!is_fairness->empty()) {
		if(para->fair_gamma_FO != NULL) {
			for(map<string, BDD*>::iterator it = para->fair_gamma_FO->begin(); it != para->fair_gamma_FO->end(); it++) 
				delete it->second;
			delete para->fair_gamma_FO;
			para->fair_gamma_FO = NULL;
		}
		if(para->nfair_gamma_FO != NULL) {
			for(map<string, BDD*>::iterator it = para->nfair_gamma_FO->begin(); it != para->nfair_gamma_FO->end(); it++) 
				delete it->second;
			delete para->nfair_gamma_FO;
			para->nfair_gamma_FO = NULL;
		}
    if ((options["quiet"] == 0 || options["simulation"] == 0) && options["uniform"]==0)
      cout << "Building set of fair states..." << endl;
    for (vector< fairness_expression * >::iterator i =
           is_fairness->begin(); i != is_fairness->end(); i++) {
      BDD fairset = (*i)->check_formula(para);
      (*i)->set_bdd_representation(fairset);
    }
    // This is a set of "fair" states (the beginning of a fair computation)
    fair_reach = check_EG_fair(para->bddmgr->bddOne(), para);
    delete para->reach;
    para->reach = new BDD(fair_reach);
    in_st *= fair_reach;
  }       // end if
  (*para->BDD_cache)["_init"] = in_st;

  vector< vector< int >*> *countex = new vector< vector< int >*>;
  map< int, BDD * > *idbdd = new map< int, BDD * >;
  vector< vector< transition * >*> *cextr = new vector< vector< transition * >*>;

  if ((options["quiet"] == 0 || options["simulation"] == 0) && options["uniform"] == 0)
    cout << "Verifying properties..." << endl;

  // Check if fair_reach is empty bdd
  if (!is_fairness->empty() && fair_reach == para->bddmgr->bddZero()) {
    if (options["quiet"] == 0)
      cout << "  Warning: ";
    cout << "The fairness constraint does not hold in any paths." << endl;
  }

  char buff[20];
  for (unsigned int i = 0; i < is_formulae->size(); i++) {
    struct timeb tmb_formula, tmb_formula1;
    if(options["verbosity"] > 1) 
      ftime(&tmb_formula);

    if(satisfied[i] /*&& options["debug"] == 0*/)
      continue;
    set< string > trans_set;
    scount = 0;
    bool satisfaction = false;
    modal_formula f(4, init, &((*is_formulae)[i]));
    BDD result = f.check_formula(para);

    satisfaction = result == *para->reach;
    satisfied[i] = satisfaction;
    num_of_satisfied = satisfaction? num_of_satisfied+1 : num_of_satisfied;
    if(options["uniform"] == 0) {
      if (options["quiet"] == 0)
        cout << "  Formula number " << i+1 << ": " <<
          (*is_formulae)[i].to_string() << ", is " << (satisfaction ? "TRUE" : "FALSE")
             << " in the model" << endl;
      else
        cout << (satisfaction ? "TRUE" : "FALSE") << endl;
    }

    if ((options["cex"] >= 1)) {
      // Computing counterexample / witness
      BDD *is = new BDD(in_st);
      
      scount = 0;
      
      modal_formula *g = options["uniform"] == 1 ? NULL : (*is_formulae)[i].push_negations(0);

      string str_head;
      bool done = false;
      bool hascex = false;

      if (satisfaction && options["uniform"] == 1) {
        hascex = true;
        str_head = "statespace";
        
				scount = export_model(para, is, countex, idbdd, cextr);
				if(scount > 0)
					done = true;
      } else if ((satisfaction) && !(g->is_NonTemporal()) && (g->is_ECTLK_new())) {
        // True and ECTLK: can print witness
        hascex = true;
        str_head = "witness";
  
        if (options["quiet"] == 0)
          cout << "  The following is a witness for the formula: " << endl;
  
        while ((*is) != para->bddmgr->bddZero()) {
          BDD curinitstate = is->PickOneMinterm(*para->v);
    
          if (is_valid_state(curinitstate, *para->v)) {
            bool cexresult = g->build_cex(&curinitstate, 0, para, countex, idbdd, cextr);
            if (cexresult) {
              done = true;
              break;
            } else {
              *is = *is - curinitstate;
              scount = 0;
              clear_cex(countex, idbdd, cextr);
            }
          }
        }
      } else if (!satisfaction && options["uniform"] == 0) {
        // False and ACTLK: can print counterexample
        if (options["quiet"] == 0)
          cout <<
            "  The following is a counterexample for the formula: " << endl;
        hascex = true;
        str_head = "counterexample";
  
        *is = *is - result;
        if(g->is_ACTLK_new()) {
          // Negation of the formula:
          modal_formula fcex1(3, g);
          modal_formula *fcex = fcex1.push_negations(0);
          //cout << "fcex = " << fcex->to_string() << endl;
          while (*is != para->bddmgr->bddZero()) {
            BDD curinitstate = is->PickOneMinterm(*para->v);
            //print_state(curinitstate, *v);

            if (is_valid_state(curinitstate, *para->v)) {
              bool cexresult = fcex->build_cex(&curinitstate, 0, para, countex, idbdd, cextr);
              if (cexresult) {
                done = true;
                break;
              } else {
                *is = *is - curinitstate;
                scount = 0;
                clear_cex(countex, idbdd, cextr);
              }
            }
          }
          if(fcex != &fcex1)
            delete fcex;
        } else {
          done = true;
          BDD init_state = is->PickOneMinterm(*para->v);
          idbdd->insert(pair < int, BDD * >(0, new BDD(init_state)));
          vector< int >desc;    
          desc.push_back(0);
          countex->push_back(new vector< int >(desc));  
        }
      } else if (satisfaction) {
        if (options["quiet"] == 0)
          cout <<
            "    -- Sorry it is not possible to compute witnesses for non-ECTLK formulae"
               << endl;
      } 
  
      if(hascex) {
        if (!done) {
          if (options["quiet"] == 0) {
            cout <<
              "A " << str_head << " exists but could not be generated." << endl;
          }
        } else {
          if (options["cex"] == 1 || options["cex"] == 3) {
            for (int ac = 0; ac < (int) countex->size(); ac++) {
              cout << "   < ";
              for (int j = 0; j < (int) countex->at(ac)->size(); j++) {
                cout << countex->at(ac)->at(j) << " ";
              }
              cout << "> " << endl;
            }
      
            cout << "  States description: " << endl;
            for (map< int, BDD * >::iterator iter =
                   idbdd->begin(); iter != idbdd->end(); iter++) {
        
              cout << "------------- State: " << iter->first << " -----------------" << endl;
              print_state(*iter->second, *para->v);
              cout << "----------------------------------------" << endl;
            }
          }
          if (options["cex"] == 2 || options["cex"] == 3) {
						sprintf(buff, "%1d", i + 1);
						string fname = cex_prefix + "formula" + buff;
						sprintf(buff, "%1d", i);
						print_cex(para, fname, str_head + buff, idbdd, cextr);
          }
          clear_cex(countex, idbdd, cextr);
        }
      } 
      delete is;
      delete g;
    }
    if(options["verbosity"] > 1) {
      ftime(&tmb_formula1);
      cout << "  time for checking formula " << i+1 << " = " << ((tmb_formula1.time-tmb_formula.time) + (tmb_formula1.millitm-tmb_formula.millitm)/1000.0) << endl;
    }     
  }

  if (options["quiet"] == 0 && options["uniform"] == 0)
    cout << "done, " << is_formulae->size() << " formulae successfully read and checked" << endl;

  if(options["verbosity"] > 1) {
    ftime(&tmb_mc1);
    cout << "time for model checking = " << ((tmb_mc1.time-tmb_mc.time) + (tmb_mc1.millitm-tmb_mc.millitm)/1000.0) << endl;
  }

  delete init;
  if(!is_fairness->empty())
    fair_reach = para->bddmgr->bddZero();
}
