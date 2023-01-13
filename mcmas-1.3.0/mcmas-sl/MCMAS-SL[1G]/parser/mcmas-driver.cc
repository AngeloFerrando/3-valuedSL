
#include "mcmas-driver.hh"
#include "nssis.hh"

mcmas_driver::mcmas_driver () 
  : trace_scanning (false), trace_parsing (false)
{
  syntax_error = false;
}

mcmas_driver::~mcmas_driver ()
{
}

void
mcmas_driver::parse (const std::string &f)
{
  file = f;
  scan_begin ();
  yy::mcmas_parser parser (*this);
  parser.set_debug_level (trace_parsing);
  parser.parse ();
  scan_end ();
}

void
mcmas_driver::error (const yy::location& l, const std::string& m)
{
  std::cerr << l << ": " << m << std::endl;
  syntax_error = true;
}

void
mcmas_driver::error (const std::string& m)
{
  std::cerr << m << std::endl;
  syntax_error = true;
}
