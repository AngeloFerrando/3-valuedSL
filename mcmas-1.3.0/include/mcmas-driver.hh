#ifndef MCMAS_DRIVER_HH
# define MCMAS_DRIVER_HH
# include <string>
# include <map>
# include "../parser/nssis.hh"
// Announce to Flex the prototype we want for lexing function, ...
# define YY_DECL yy::mcmas_parser::token_type yylex (yy::mcmas_parser::semantic_type* yylval, yy::mcmas_parser::location_type* yylloc, mcmas_driver& driver)
// ... and declare it for the parser's sake.

class mcmas_driver;

YY_DECL;
// Conducting the whole scanning and parsing of MCMAS.
class mcmas_driver
{
public:
  mcmas_driver ();
  virtual ~mcmas_driver ();

  bool syntax_error;
  // Handling the scanner.
  void scan_begin ();
  void scan_end ();
  bool trace_scanning;
  // Handling the parser.
  void parse (const std::string& f);
  std::string file;
  bool trace_parsing;
  // Error handling.
  void error (const yy::location& l, const std::string& m);
  void error (const std::string& m);
};
#endif // ! MCMAS_DRIVER_HH
