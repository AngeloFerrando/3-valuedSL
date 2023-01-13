#include <ctime>
#include "types.hh"
#include "utilities.hh"

using namespace std;

atomic_proposition::atomic_proposition(string * t)
{
  proposition = t;
}

atomic_proposition::~atomic_proposition()
{
}

string
atomic_proposition::get_proposition()
{
  if (proposition == NULL) {
    cout << "atomic proposition is unknown!" << endl;
    exit(1);
  } else
    return *proposition;
}

string
atomic_proposition::to_string()
{
  return get_proposition();
}

