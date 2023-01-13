#include <ctime>
#include "types.hh"
#include "utilities.hh"

using namespace std;

enumerate::enumerate(string * n, set< string > *s):basictype(n, 3)
{
  enumvalue = s;
  value_index = new map< string, vector< bool > *>;
  bdd_length = enumvalue == NULL ? 0 : log_2((int) enumvalue->size());
  set_value_index();
}

enumerate::~enumerate()
{
  delete enumvalue;
	for(map< string, vector< bool > * >::iterator i=value_index->begin(); i!=value_index->end(); i++)
		delete i->second;
	delete value_index;
}

set< string > *
enumerate::get_enumvalue()
{
  return enumvalue;
}

bool
enumerate::is_power_of_two()
{
  return enumvalue->size() == (unsigned int)(1 << bdd_length);
}

int
enumerate::is_valid_value(string s)
{
  if (enumvalue == NULL) {
    cout << "enum list is unknown" << endl;
    exit(1);
  }
  return (enumvalue->find(s) != enumvalue->end());
}

string
enumerate::to_string()
{
  string str = ": { ";
  int k = 0;
  int j = (int) enumvalue->size() - 1;
  for (set< string >::iterator i = enumvalue->begin(); i != enumvalue->end();
       i++) {
    if (k == j)
      str += *i + " ";
    else
      str += *i + ", ";
    k++;
  }
  str += "}";
  return get_name() + str;
}

int
enumerate::BDD_length()
{
  return bdd_length;
}

unsigned int 
enumerate::get_number_of_elements()
{
  return enumvalue->size();
}

void
enumerate::set_value_index()
{
  int size = BDD_length();
  vector< bool > base(size, false);
  for (set< string >::iterator i = enumvalue->begin(); i != enumvalue->end();
       i++) {
    vector< bool > *temp = new vector< bool > (base);
    pair < string, vector< bool > *>p(*i, temp);
    value_index->insert(p);
    for (int j = size - 1; j >= 0; j--) {
      if (base[j])
        base[j] = false;
      else {
        base[j] = true;
        break;
      }
    }
  }
}

void
enumerate::print_value_index()
{
  for (map< string, vector< bool > *>::iterator i = value_index->begin();
       i != value_index->end(); i++) {
    cout << i->first << ": ";
    for (unsigned int j = 0; j < i->second->size(); j++)
      cout << ((*(i->second))[j] ? 1 : 0);
    cout << endl;
  }
}

vector< bool > *enumerate::get_value_index(string value)
{
  if (value_index != NULL) {
    map< string, vector< bool > *>::iterator i = value_index->find(value);
    if (i != value_index->end())
      return i->second;
  }
  return NULL;
}

string
enumerate::find_value_by_index(vector< bool > index)
{
  for (map< string, vector< bool > *>::iterator i = value_index->begin();
       i != value_index->end(); i++) {
    bool flag = true;
    for (unsigned int j = 0; j < i->second->size(); j++)
      if ((*(i->second))[j] != index[j]) {
        flag = false;
        break;
      }
    if (flag)
      return i->first;
  }
  return "";
}

void
enumerate::print_state(string prefix, BDD state, vector<BDD> v)
{
  int index_begin = get_index_begin();
  int index_end = get_index_end();
  cout << prefix << get_name() << " = ";
  cout.flush();
  vector< bool > index;
  for (int i = index_begin; i <= index_end; i++)
    if (state <= v[i])
      index.push_back(true);
    else
      index.push_back(false);
  string value = find_value_by_index(index);
  cout << value;
}

void
enumerate::print_stateXML(ofstream * myfile, BDD state, vector<BDD> v)
{
  int index_begin = get_index_begin();
  int index_end = get_index_end();
  *myfile << "        <variable name=\"" << get_name() << "\">";

  vector< bool > index;
  for (int i = index_begin; i <= index_end; i++)
    if (state <= v[i])
      index.push_back(true);
    else
      index.push_back(false);
  string value = find_value_by_index(index);
  *myfile << value;
  *myfile << "</variable>\n";
}

string
enumerate::state_to_str(BDD state, vector<BDD> v)
{
  ostringstream s;
  int index_begin = get_index_begin();
  int index_end = get_index_end();
  s << get_name() << "=";

  vector< bool > index;
  for (int i = index_begin; i <= index_end; i++)
    if (state <= v[i])
      index.push_back(true);
    else
      index.push_back(false);
  string value = find_value_by_index(index);
  s << value;
  return s.str();
}

bool
enumerate::is_valid_state(BDD state, vector<BDD> v)
{
  int index_begin = get_index_begin();
  int index_end = get_index_end();
  vector< bool > index;
  for (int i = index_begin; i <= index_end; i++)
    if (state <= v[i])
      index.push_back(true);
    else
      index.push_back(false);
  string value = find_value_by_index(index);
  if (value == "")
    return false;
  else
    return true;
}

ADD
enumerate::build_ADD_tree(Cudd * bddmgr, vector<ADD> * addv, map< string,
                          ADD > *ADD_cache)
{
  if (ADD_cache->find(name_index) != ADD_cache->end())
    return ((*ADD_cache)[name_index]);
  int index_begin = get_index_begin();
  int index = 1;
  ADD add_tree = bddmgr->addZero();
  for (set< string >::iterator i = enumvalue->begin(); i != enumvalue->end();
       i++) {
    vector< bool > *v = get_value_index(*i);
    ADD path = bddmgr->constant(index);
    index++;
    for (unsigned int j = 0; j < v->size(); j++)
      if ((*v)[j])
        path *= (*addv)[index_begin + j];
      else
        path *= ~(*addv)[index_begin + j];
    add_tree += path;
  }
  (*ADD_cache)[name_index] = add_tree;
  return add_tree;
}

BDD
enumerate::build_all_BDDs(Cudd * bddmgr, vector<BDD> * v)
{
  unsigned int length = 1;
  length <<= bdd_length;
  if (enumvalue->size() < length) {
    int index_begin = get_index_begin();
    BDD bdd_tree = bddmgr->bddZero();
    int index = 1;
    for (set< string >::iterator i = enumvalue->begin();
         i != enumvalue->end(); i++) {
      vector< bool > *vindex = get_value_index(*i);
      BDD path = bddmgr->bddOne();
      index++;
      for (unsigned int j = 0; j < vindex->size(); j++)
        if ((*vindex)[j])
          path *= (*v)[index_begin + j];
        else
          path *= ~(*v)[index_begin + j];
      bdd_tree += path;
    }
    return bdd_tree;
  } else
    return bddmgr->bddOne();
}

void
enumerate::build_individual_BDD(Cudd * bddmgr, vector<BDD> *v, vector< BDD* > *bddblocks, unsigned int count) {
	int index_begin = get_index_begin();
	unsigned int length = enumvalue->size();
	if(length > count) {
		unsigned int portion = (unsigned int)(length/count);
		unsigned int reminder = length%count;
		set< string >::iterator it = enumvalue->begin();
		for(unsigned int i=0; i<reminder; i++) {
			BDD bdd_tree = bddmgr->bddZero();
			for(unsigned int k=0; k<=portion; k++) {
				vector< bool > *vindex = get_value_index(*it);
				it++;
				BDD path = bddmgr->bddOne();
				for (unsigned int j = 0; j < vindex->size(); j++)
					if ((*vindex)[j])
						path *= (*v)[index_begin + j];
					else
						path *= ~(*v)[index_begin + j];
				bdd_tree += path;
			}
			bddblocks->push_back(new BDD(bdd_tree));
		}
		for(unsigned int i=reminder; i<count; i++) {
			BDD bdd_tree = bddmgr->bddZero();
			for(unsigned int k=0; k<portion; k++) {
				vector< bool > *vindex = get_value_index(*it);
				it++;
				BDD path = bddmgr->bddOne();
				for (unsigned int j = 0; j < vindex->size(); j++)
					if ((*vindex)[j])
						path *= (*v)[index_begin + j];
					else
						path *= ~(*v)[index_begin + j];
				bdd_tree += path;
			}
			bddblocks->push_back(new BDD(bdd_tree));
		}
	} else {
		for (set< string >::iterator i = enumvalue->begin(); i != enumvalue->end(); i++) {
      vector< bool > *vindex = get_value_index(*i);
      BDD path = bddmgr->bddOne();
      for (unsigned int j = 0; j < vindex->size(); j++)
        if ((*vindex)[j])
          path *= (*v)[index_begin + j];
        else
          path *= ~(*v)[index_begin + j];
      bddblocks->push_back(new BDD(path));
    }
	}
}
