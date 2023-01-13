#include <ctime>
#include "types.hh"
#include "utilities.hh"

using namespace std;

transition::transition(BDD * fr, int frid, BDD * t, int tid, BDD * lab)
{
  from = new BDD((*fr));
  fromid = frid;
  to = new BDD((*t));
  toid = tid;
  label = new BDD((*lab));

  temporal = true;
  epistemic1 = "";
  epistemic2 = "";
}

transition::transition(BDD * fr, int frid, BDD * t, int tid, string name1,
                       BDD * lab)
{
  from = new BDD((*fr));
  fromid = frid;
  to = new BDD((*t));
  toid = tid;
  //type = ty;
  label = new BDD((*lab));

  temporal = false;
  epistemic1 = name1;
  epistemic2 = "";
}

transition::transition(BDD * fr, int frid, BDD * t, int tid, string name1,
                       string name2, BDD * lab)
{
  from = new BDD((*fr));
  fromid = frid;
  to = new BDD((*t));
  toid = tid;
  label = new BDD((*lab));

  temporal = false;
  epistemic1 = name1;
  epistemic2 = name2;
}

transition::transition()
{
  from = new BDD();
  fromid = -1;
  to = new BDD();
  toid = -1;
  label = new BDD();

  temporal = false;
  epistemic1 = "";
  epistemic2 = "";
}

transition::~transition()
{
  delete from;
  delete to;
  delete label;
}

BDD *
transition::getfrom()
{
  return from;
}

BDD *
transition::getto()
{
  return to;
}

BDD *
transition::getlabel()
{
  return label;
}

int
transition::getfromid()
{
  return fromid;
}

int
transition::gettoid()
{
  return toid;
}

void
transition::setfrom(BDD * fr)
{
  from = fr;
}

void
transition::setto(BDD * fr)
{
  to = fr;
}

void
transition::setlabel(BDD * fr)
{
  label = fr;
}

void
transition::setfromid(int frid)
{
  fromid = frid;
}

void
transition::settoid(int frid)
{
  toid = frid;
}

void
transition::print(vector<BDD> * v, vector<BDD> * a)
{
  cout << "------- Transition --------" << endl;
  cout << " From (id): " << fromid << endl;
  for (unsigned int i = 0; i < agents->size(); i++) {
    cout << "    Agent " << (*agents)[i]->get_name() << endl;
    (*agents)[i]->print_state("  ", *from, *v);
  }

  cout << " To (id): " << toid << endl;
  for (unsigned int i = 0; i < agents->size(); i++) {
    cout << "    Agent " << (*agents)[i]->get_name() << endl;
    (*agents)[i]->print_state("  ", *to, *v);
  }

  if (isTemporal()) {
    cout << " Joint action: " << endl;
    for (unsigned int i = 0; i < agents->size(); i++) {
      cout << (*agents)[i]->get_name() << " : ";
      (*agents)[i]->print_action(*label, *a);
      if (i < agents->size() - 1)
        cout << "; ";
      else
        cout << endl;
    }
  }

  cout << "---------------------------" << endl;
}

void
transition::printXML(ofstream * myfile, vector<BDD> * v)
{
  *myfile << "  <transition>\n";
  *myfile << "    <from-id>" << fromid << "</from-id>\n";
  *myfile << "    <to-id>" << toid << "</to-id>\n";
  *myfile << "    <from>\n";
  for (unsigned int i = 0; i < agents->size(); i++) {
    *myfile << "      <agent name=\"" << (*agents)[i]->get_name() << "\">\n";
    (*agents)[i]->print_stateXML(myfile, *from, *v);
    *myfile << "      </agent>\n";
  }
  *myfile << "    </from>\n";
  *myfile << "    <to>\n";
  for (unsigned int i = 0; i < agents->size(); i++) {
    *myfile << "      <agent name=\"" << (*agents)[i]->get_name() << "\">\n";
    (*agents)[i]->print_stateXML(myfile, *to, *v);
    *myfile << "      </agent>\n";
  }
  *myfile << "    </to>\n";
  *myfile << "  </transition>\n";

}

string
transition::index_to_string(vector<BDD> * a)
{
  char buff[20];
  string s = "";
  for (unsigned int i = 0; i < agents->size(); i++) {
    s += (*agents)[i]->action_to_str(*label, *a) + ";";
  }
  sprintf(buff, "%1d->%1d", fromid, toid);
  s += buff;
  return s;
}

void
transition::to_str(ofstream * myfile, vector<BDD> * a)
{
  *myfile << "    " << fromid << " -> " << toid;

  if (isTemporal()) {
    // A temporal transition
    *myfile << "[label=\"<";
    for (unsigned int i = 0; i < agents->size(); i++) {
      string act_str = (*agents)[i]->action_to_str(*label, *a);
      if (act_str != "") {
        *myfile << act_str;
        if (!(i == agents->size() - 1)) {
          *myfile << ";";
        }
      }
    }
    *myfile << ">\"]" << endl;
  } else {
    *myfile << "[label=\"" << epistemic1 << (epistemic2.
                                             empty()? "" : ", ") << epistemic2
            << "\", arrowhead=none, style=dotted]" << endl;
  }
}

bool
transition::isTemporal()
{
  return temporal;
}

string
transition::getEpistemic1()
{
  return epistemic1;
}

string
transition::getEpistemic2()
{
  return epistemic2;
}
