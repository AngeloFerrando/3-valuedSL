#include <ctime>
#include "types.hh"
#include "utilities.hh"

using namespace std;

rangedint::rangedint(string * n, int l, int u):basictype(n, 2)
{
  lowerbound = l;
  upperbound = u;
  bdd_length = log_2(upperbound - lowerbound + 1);
  power_two = 1;
  power_two = power_two << bdd_length;
  half_power = 1;
  half_power = half_power << (bdd_length - 1);
  half_power += lowerbound;
}

rangedint::~rangedint()
{
}

int
rangedint::get_lowerbound()
{
  return lowerbound;
}

int
rangedint::get_upperbound()
{
  return upperbound;
}

int
rangedint::get_length()
{
  return upperbound - lowerbound + 1;
}

bool
rangedint::is_power_of_two()
{
	return power_two == upperbound - lowerbound + 1;
}

bool
rangedint::is_valid_value(int i)
{
  return (i <= upperbound && i >= lowerbound);
}

string
rangedint::to_string()
{
  ostringstream o, p;
  o << lowerbound;
  p << upperbound;
  return get_name() + ": " + o.str() + " .. " + p.str();
}

int
rangedint::BDD_length()
{
  return bdd_length;
}

void
rangedint::print_value_index()
{
  for (int k = lowerbound; k <= upperbound; k++) {
    cout << k << ": ";
    vector< int >*v = get_value_index(k);
    for (unsigned int j = 0; j < v->size(); j++)
      cout << ((*v)[j] == 1 ? "1" : ((*v)[j] == -1 ? "0" : "_"));
    cout << endl;
  }
}

vector< int >*
rangedint::get_value_index(int value)
{
  if (value >= lowerbound && value <= upperbound) {
    vector< int >*temp = new vector< int >(bdd_length, -1);
    if (power_two + lowerbound == upperbound + 1) {
      int distance = value - lowerbound;
      for (int i = bdd_length - 1; i >= 0; i--) {
        if ((distance & 1) == 1)
          (*temp)[i] = 1;
        distance >>= 1;
      }
    } else {
      int index = value - half_power;
      if (index < 0) {
        int distance = value - lowerbound;
        for (int i = bdd_length - 2; i >= 0; i--) {
          if ((distance & 1) == 1)
            (*temp)[i] = 1;
          distance >>= 1;
        }
        if (value - lowerbound > upperbound - half_power)
          (*temp)[bdd_length - 1] = 0;
      } else {
        int distance = index;
        for (int i = bdd_length - 2; i >= 0; i--) {
          if ((distance & 1) == 1)
            (*temp)[i] = 1;
          distance >>= 1;
        }
        (*temp)[bdd_length - 1] = 1;
      }
    }
    return temp;
  }
  return NULL;
}

int
rangedint::find_value_by_index(vector< bool > index)
{
  int value = 0;
  if (power_two + lowerbound == upperbound + 1) {
    for (unsigned int i = 0; i < index.size(); i++) {
      value <<= 1;
      value += (index[i] == true ? 1 : 0);
    }
    return value + lowerbound;
  } else {
    for (unsigned int i = 0; i < index.size() - 1; i++) {
      value <<= 1;
      value += (index[i] == true ? 1 : 0);
    }
    if (value > upperbound - half_power || index[bdd_length - 1] == false)
      return value + lowerbound;
    else
      return value + half_power;
  }
}

void
rangedint::print_state(string prefix, BDD state, vector<BDD> v)
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
  int value = find_value_by_index(index);
  cout << value;
}

void
rangedint::print_stateXML(ofstream * myfile, BDD state, vector<BDD> v)
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
  int value = find_value_by_index(index);
  *myfile << value;
  *myfile << "</variable>\n";

}

string
rangedint::state_to_str(BDD state, vector<BDD> v)
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
  int value = find_value_by_index(index);
  s << value;
  return s.str();
}

bool
rangedint::is_valid_state(BDD state, vector<BDD> v)
{
  int index_begin = get_index_begin();
  int index_end = get_index_end();
  vector< bool > index;
  for (int i = index_begin; i <= index_end; i++)
    if (state <= v[i])
      index.push_back(true);
    else
      index.push_back(false);
  int value = find_value_by_index(index);
  if (value > upperbound)
    return false;
  else
    return true;
}

ADD
rangedint::build_ADD_tree(Cudd * bddmgr, vector<ADD> * addv, map< string, ADD > *ADD_cache)
{
  if (ADD_cache->find(name_index) != ADD_cache->end())
    return ((*ADD_cache)[name_index]);
  int index_begin = get_index_begin();
  ADD add_tree = bddmgr->addZero();
  for (int i = lowerbound; i <= upperbound; i++) {
    vector< int >*v = get_value_index(i);
    ADD path = bddmgr->constant(i);
    for (unsigned int j = 0; j < v->size(); j++)
      if ((*v)[j] == 1)
        path *= (*addv)[index_begin + j];
      else if ((*v)[j] == -1)
        path *= ~(*addv)[index_begin + j];
    add_tree += path;
  }
  (*ADD_cache)[name_index] = add_tree;
  return add_tree;
}

BDD
rangedint::build_all_BDDs(Cudd * bddmgr, vector<BDD> * v)
{
  return bddmgr->bddOne();
}

void
rangedint::build_individual_BDD(Cudd * bddmgr, vector<BDD> *v, vector< BDD* > *bddblocks, unsigned int count) {
	int index_begin = get_index_begin();
	unsigned int length = upperbound - lowerbound + 1;
	if(length > count) {
		unsigned int portion = (unsigned int)(length/count);
		unsigned int reminder = length%count;
		int it = lowerbound;
		for(unsigned int i=0; i<reminder; i++) {
			BDD bdd_tree = bddmgr->bddZero();
			for(unsigned int k=0; k<=portion; k++) {
				vector< int > *vindex = get_value_index(it++);
				BDD path = bddmgr->bddOne();
				for (unsigned int j = 0; j < vindex->size(); j++)
					if ((*vindex)[j] == 1)
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
				vector< int > *vindex = get_value_index(it++);
				BDD path = bddmgr->bddOne();
				for (unsigned int j = 0; j < vindex->size(); j++)
					if ((*vindex)[j] == 1)
						path *= (*v)[index_begin + j];
					else
						path *= ~(*v)[index_begin + j];
				bdd_tree += path;
			}
			bddblocks->push_back(new BDD(bdd_tree));
		}		
	} else {
		for (int i = lowerbound; i <= upperbound; i++) {
			vector< int >*vindex = get_value_index(i);
			BDD path = bddmgr->bddOne();
			for (unsigned int j = 0; j < vindex->size(); j++)
				if ((*vindex)[j] == 1)
					path *= (*v)[index_begin + j];
				else if ((*vindex)[j] == -1)
					path *= ~(*v)[index_begin + j];
      bddblocks->push_back(new BDD(path));
		}
	}
}
