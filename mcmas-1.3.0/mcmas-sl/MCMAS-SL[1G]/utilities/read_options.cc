#include <string.h>
#include "utilities.hh"

#define NAME "mcmas"

extern string key_variable[2];
extern string cex_prefix; 

void
print_help(void)
{
  cout << "Usage: " << NAME << " [OPTIONS] FILE " << endl;
  cout << "Example: " << NAME << " -v 3 -u myfile.ispl" << endl;
  cout << endl << "Options: " << endl;
  cout << "  -s \t \t Interactive execution" << endl;

  cout << endl;

  cout << "  -v Number \t verbosity level ( 1 -- 6 )" << endl;
  cout << "  -u \t \t Print BDD statistics " << endl;

  cout << endl;

  cout << "  -e Number \t Choose the way to generate reachable state space (1 -- 3, default 2)" << endl;
  cout << "  -o Number \t Choose the way to order BDD variables (1 -- 4, default 2)" << endl;
  cout << "  -g Number \t Choose the way to group BDD variables (1 -- 3, default 3)" << endl;
  cout << "  -d Number \t Choose the point to disable dynamic BDD reordering (0 -- 3, default 3)" << endl;
  cout << "  -nobddcache \t disable internal BDD cache" << endl;

  cout << endl;

  cout << "  -k \t \t Check deadlock in the model" << endl;
  cout << "  -a \t \t Check arithmetic overflow in the model" << endl;

  cout << endl;

  cout << "  -c Number \t Choose the way to display counterexamples/witness executions (1 -- 3)" << endl;
  cout << "  -p Path \t Choose the path to store files for counterexamples" << endl;
  cout << "  -solutions \t Show full perfect recall solutions" << endl;

  cout << endl;

  cout << "  -f Number \t Choose the level of generating ATL strategies (1 -- 4)"  << endl;
  cout << "  -l Number \t Choose the level of generating ATL counterexamples (1 -- 2)"  << endl;
  cout << "  -w \t \t Try to choose new states when generating ATL strategies"  << endl;

  cout << endl;

  cout << "  -n \t \t Disable comparison between an enumeration type and its strict subset"  << endl;

  cout << endl;

  cout << "  -t Number \t Thread branching for SLK model checking"  << endl;
  cout << "  -sd Number \t Use separate determinisation for SL[1G] model checking (0 -- 1, default 1)" << endl;

  cout << endl;

  cout << "  -h \t \t This screen" << endl;
}

bool
read_options(int argc, char *argv[]) {
  options["verbosity"] = 0;
  options["bdd_stats"] = 0;
  options["cex"] = 0;
  options["solutions"] = 0;
  options["simulation"] = 0;
  options["quiet"] = 0;
  options["experiment"] = 2;
  options["smv"] = 0;
  options["fullatl"] = 0;
  options["atlnewstate"] = 0;
  options["atlcex"] = 0;
  options["subset"] = 1;
  options["ordering"] = 2;
  options["dao"] = 3;
  options["bddgroup"] = 3;
  options["deadlock"] = 0;
  options["overflow"] = 0;
  options["nobddcache"] = 0;
  options["threadbranching"] = 0;
  options["separate_determinization"] = 1;

  bool wrongpara = false;

  std::string verb("-v");
  std::string binfo("-bdd_stats");
  std::string help("-h");
  std::string help2("--help");
  std::string cex("-c");
  std::string solutions("-solutions");
  std::string simulation("-s");
  std::string quiet("-q");
  std::string experiment("-e");
  std::string cexoutdir("-cex_prefix");
  std::string fullatl("-fullatl");
  std::string atlnewstate("-atlnewstate");
  std::string atlcex("-atlcex");
  std::string subset("-nosubset");
  std::string ordering("-o");
  std::string dao("-dao");
  std::string bddgroup("-bddgroup");
  std::string deadlock("-k");
  std::string overflow("-a");

  std::string binfo1("-u");
  std::string cexoutdir1("-p");
  std::string fullatl1("-f");
  std::string atlnewstate1("-w");
  std::string atlcex1("-l");
  std::string subset1("-n");
  std::string dao1("-d");
  std::string bddgroup1("-g");
  std::string nobddcache("-nobddcache");

  std::string threadbranching("-t");
  std::string separate_determinization("-separate_determinization");
  std::string separate_determinization1("-sd");

  for (int i = 1; i < argc - 1; ++i) {
    if (binfo == argv[i] || binfo1 == argv[i]) {
      options["bdd_stats"] = 1;
    } else if (cex == argv[i]) {
      string s;
      s = argv[++i];    // consume the argument
      options["cex"] = atoi(s.c_str());

      if (options["cex"] < 0 || options["cex"] > 3) {
        cout << "Parameter " << options["cex"] <<
          " is not allowed in -c option." << endl;
        wrongpara = true;
      }
    } else if (solutions == argv[i]) {
      options["solutions"] = 1;
    } else if (verb == argv[i]) {
      string s;
      s = argv[++i];    // consume the argument
      options["verbosity"] = atoi(s.c_str());

      if (options["verbosity"] < 0 || options["verbosity"] > 6) {
        cout << "Parameter " << options["verbosity"] <<
          " is not allowed in -v option." << endl;
        wrongpara = true;
      }
    } else if ((help == argv[i]) || (help2 == argv[i])) {
      print_help();
      wrongpara = true;
    } else if (simulation == argv[i]) {
      options["simulation"] = 1;
    } else if (atlcex == argv[i] || atlcex1 == argv[i]) {
      string s;
      s = argv[++i];    // consume the argument
      options["atlcex"] = atoi(s.c_str());
      if (options["atlcex"] < 0 || options["atlcex"] > 2) {
        cout << "Parameter " << options["atlcex"] <<
          " is not allowed in -atlcex option." << endl;
        wrongpara = true;
      }
    } else if (fullatl == argv[i] || fullatl1 == argv[i]) {
      string s;
      s = argv[++i];    // consume the argument
      options["fullatl"] = atoi(s.c_str());
      if (options["fullatl"] < 0 || options["fullatl"] > 4) {
        cout << "Parameter " << options["fullatl"] <<
          " is not allowed in -fullatl option." << endl;
        wrongpara = true;
      }
    } else if (atlnewstate == argv[i] || atlnewstate1 == argv[i]) {
      options["atlnewstate"] = 1;
    } else if (ordering == argv[i]) {
      string s;
      s = argv[++i];
      options["ordering"] = atoi(s.c_str());
      if (options["ordering"] < 1 || options["ordering"] > 4) {
        cout << "Parameter " << options["ordering"] <<
          " is not allowed in -o option." << endl;
        wrongpara = true;
      }
    } else if (subset == argv[i] || subset1 == argv[i]) {
      options["subset"] = 0;
    } else if (dao == argv[i] || dao1 == argv[i]) {
      string s;
      s = argv[++i];    // consume the argument
      options["dao"] = atoi(s.c_str());

      if (options["dao"] < 0 || options["dao"] > 3) {
        cout << "Parameter " << options["verbosity"] <<
          " is not allowed in -dao option." << endl;
        wrongpara = true;
      }
    } else if (bddgroup == argv[i] || bddgroup1 == argv[i]) {
      string s;
      s = argv[++i];    // consume the argument
      options["bddgroup"] = atoi(s.c_str());

      if (options["bddgroup"] < 0 || options["bddgroup"] > 3) {
        cout << "Parameter " << options["verbosity"] <<
          " is not allowed in -bddgroup option." << endl;
        wrongpara = true;
      }
    } else if (quiet == argv[i]) {
      options["quiet"] = 1;
    } else if (deadlock == argv[i]) {
      options["deadlock"] = 1;
    } else if (overflow == argv[i]) {
      options["overflow"] = 1;
    } else if (experiment == argv[i]) {
      string s;
      s = argv[++i];    // consume the argument
      options["experiment"] = atoi(s.c_str());
      if (options["experiment"] < 1 || options["experiment"] > 3) {
        cout << "Parameter " << options["experiment"] <<
          " is not allowed in -e option." << endl;
        wrongpara = true;
      }
    } else if (cexoutdir == argv[i] || cexoutdir1 == argv[i]) {
      string s;
      s = argv[++i];    // consume the argument
      cex_prefix = s;
      if(cex_prefix.at(cex_prefix.length()-1) != '\\' || 
         cex_prefix.at(cex_prefix.length()-1) != '/')
        cex_prefix += "/";
    } else if (nobddcache == argv[i]) {
      options["nobddcache"] = 1;
    } else if (threadbranching == argv[i]) {
      string s;
      s = argv[++i];    // consume the argument
      options["threadbranching"] = atoi(s.c_str());
      if (options["threadbranching"] < 0) {
        cout << "Parameter " << options["threadbranching"] <<
            " is not allowed in " << argv[i - 1] << " option." << endl;
        wrongpara = true;
      }
    } else if (separate_determinization == argv[i] ||
               separate_determinization1 == argv[i]) {
      string s = argv[++i];    // consume the argument
      options["separate_determinization"] = atoi(s.c_str());
      if (options["separate_determinization"] < 0 ||
          options["separate_determinization"] > 1) {
        cout << "Parameter " << options["separate_determinization"] <<
            " is not allowed in " << argv[i - 1] << " option." << endl;
        wrongpara = true;
      }
    } else {
      cout << NAME << " invalid option: " << argv[i] << endl;
      print_help();
			wrongpara = true;
      //exit(1);
    }
  }

	return wrongpara;
}
