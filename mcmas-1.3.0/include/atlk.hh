#ifndef ATLK_HH
# define ATLK_HH
#include <vector>
#include <cmath>
#include "types.hh"
#include "cuddObj.hh"

using namespace std;

void build_enumerate_BDDs(bdd_parameters * para);
void clear_enumerate_BDDs(bdd_parameters * para);
void build_integer_BDDs(bdd_parameters * para);
void clear_integer_BDDs(bdd_parameters * para);
void traverse_uniform_strategies(vector<vector<BDD*>*>* uniform_prots, bdd_parameters * para);
BDD check_ATLX_negation (BDD next, string grpname, bdd_parameters * para);
BDD check_ATLU_negation (BDD p, BDD q, string grpname, bdd_parameters *para);
BDD check_ATLW_negation (BDD p, BDD q, string grpname, bdd_parameters *para);
BDD check_ATLF_negation (BDD q, string grpname, bdd_parameters *para);
BDD check_ATLG_negation (BDD p, string grpname, bdd_parameters *para);
BDD check_ATLX_strat(BDD next, string grpname, bdd_parameters * para);
BDD check_suc_strat(BDD source, BDD next, string grpname, bdd_parameters * para);
BDD generate_uniform_strategies(BDD p1, BDD p2, unsigned char op, BDD SA, string grpname, BDD nfair, bdd_parameters * para);
BDD split_uniform_strategies(BDD p1, BDD p2, unsigned char op, unsigned int agent_index, string grpname, vector<string> *agent_names, BDD SA, BDD strategies, BDD nfair, bdd_parameters * para);
BDD check_ATLX_fo_strat(BDD next, BDD strat, vector<string> *agent_names, bdd_parameters * para);
BDD check_ATL_NFair(string grpname, bdd_parameters * para);
BDD check_ATLG_fair_fo_strat(BDD p, BDD nfair, BDD strategies, vector<string> *agent_names, bdd_parameters * para);
BDD check_ATLG_fair_fo(BDD p, BDD nfair, string grpname, bdd_parameters * para);
BDD check_fair_gamma_FO(string grpname, bdd_parameters * para);
BDD check_nfair_gamma_FO(string grpname, bdd_parameters * para);
BDD check_ATLU_fair_fo(BDD p1, BDD p2, BDD nfair, string grpname, bdd_parameters * para);
BDD check_ATLU_fair_fo_strat(BDD p1, BDD p2, BDD nfair, BDD strategies, vector<string> *agent_names, bdd_parameters * para);
BDD check_ATLU_fair_po_aux(BDD p1, BDD p2, BDD p2_strat, string grpname, bdd_parameters * para);
BDD check_ATLU_fair_po(BDD p1, BDD p2, BDD nfair, string grpname, bdd_parameters * para);
BDD check_ATLU_fo_strat(BDD q1, BDD q2, BDD strat, vector<string> *agent_names, bdd_parameters * para);
BDD check_ATLU_po(BDD q1, BDD q2, string grpname, bdd_parameters * para);

// BDD check_ATLX_fo_strat_action(BDD next, BDD strat, vector<string> *agent_names, bdd_parameters * para);

#endif // ! ATLK_HH
