#ifndef LTLK_HH
#define LTLK_HH
#include <vector>
#include <cmath>
#include "types.hh"
#include "cuddObj.hh"

using namespace std;

set<modal_formula*>* get_elementary_formulas(modal_formula* formula);
BDD check_path_sat(modal_formula* formula,
                   bdd_parameters* para,
                   const map<modal_formula*, BDD>& index_map,
                   const map<modal_formula*, BDD>& next_index_map,
                   bool next);
modal_formula* remove_path_gs(modal_formula* formula);
BDD build_path_tableau(bdd_parameters* para, 
	                   const map<modal_formula*, BDD>& index_map,
	                   const map<modal_formula*, BDD>& next_index_map);
BDD build_consistency_rules(bdd_parameters * para, 
                            const map<modal_formula *, BDD>& index_map, 
                            map<modal_formula *, BDD> epistemic_path_values);
void get_path_fairness_constraints(modal_formula* formula,
                                   bdd_parameters* para,
                                   const map<modal_formula*, BDD>& index_map,
                                   const map<modal_formula*, BDD>& next_index_map,
                                   vector<BDD>* fairness_bdds);
BDD build_and_check_tableau_model_checking(modal_formula* formula, bdd_parameters* para);
pair<BDD, int> build_and_check_tableau(modal_formula* formula, bdd_parameters* para);
void destroy_tableau(int num_elementary_formulas,bdd_parameters* para);

#endif // ! LTLK_HH
