#include <ctime>
#include "types.hh"
#include "utilities.hh"

using namespace std;

basictype::basictype(string * n)
{
  name = n;
  type = 1;
  index_begin = -1;
  index_end = -1;
}

basictype::basictype(string * n, unsigned char t)
{
  name = n;
  type = t;
  index_begin = -1;
  index_end = -1;
}

basictype::~basictype()
{
  //delete name;
}

string
basictype::get_name()
{
  if (name == NULL) {
    cout << "type name is unknown" << endl;
    exit(1);
  }
  return *name;
}

unsigned char
basictype::get_type()
{
  return type;
}

string
basictype::to_string()
{
  return *name + ": boolean";
}

int
basictype::BDD_length()
{
  return 1;
}

void
basictype::set_index_begin(int i)
{
  index_begin = i;
  char buff[5];
  sprintf(buff, "%1d", i);
  string str(buff);
  name_index = "_" + *name + "_" + str;
}

void
basictype::set_index_end(int i)
{
  index_end = i;
}

int
basictype::get_index_begin()
{
  return index_begin;
}

int
basictype::get_index_end()
{
  return index_end;
}

void
basictype::print_value_index()
{
  cout << "true: 1" << endl;
  cout << "false: 0" << endl;
}

void
basictype::print_state(string prefix, BDD state, vector<BDD> v)
{
  cout << prefix << *name << " = ";
  if (state <= v[index_begin])
    cout << "true";
  else
    cout << "false";
}

void
basictype::print_stateXML(ofstream * myfile, BDD state, vector<BDD> v)
{
  *myfile << "        <variable name=\"" << *name << "\">";
  if (state <= v[index_begin])
    *myfile << "true";
  else
    *myfile << "false";
  *myfile << "</variable>\n";
}

string
basictype::state_to_str(BDD state, vector<BDD> v)
{
  ostringstream s;
  s << *name << "=";
  if (state <= v[index_begin])
    s << "true";
  else
    s << "false";
  return s.str();
}

bool
basictype::is_valid_state(BDD state, vector<BDD> v)
{
  return true;
}

ADD
basictype::build_ADD_tree(Cudd * bddmgr, vector<ADD> * addv, map< string,
                          ADD > *ADD_cache)
{
  if (ADD_cache->find(name_index) != ADD_cache->end())
    return ((*ADD_cache)[name_index]);
  int index_begin = get_index_begin();
  ADD add_tree =
    ((*addv)[index_begin] * bddmgr->constant(1)) +
    (~(*addv)[index_begin] * bddmgr->constant(0));
  (*ADD_cache)[name_index] = add_tree;
  return add_tree;
}

BDD
basictype::build_all_BDDs(Cudd * bddmgr, vector<BDD> * v)
{
  return bddmgr->bddOne();
}

void
basictype::build_individual_BDD(Cudd * bddmgr, vector<BDD> *v, vector< BDD* > *bddblocks, unsigned int count) {
	int index_begin = get_index_begin();
	bddblocks->push_back(new BDD((*v)[index_begin]));
	bddblocks->push_back(new BDD(~(*v)[index_begin]));	
}
