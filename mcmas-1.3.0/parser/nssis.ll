%{
# include <cstdlib>
# include <errno.h>
# include <limits.h>
# include <string>
# include "mcmas-driver.hh"
# include "nssis.hh"

# undef yywrap
# define yywrap() 1

#define yyterminate() return token::END_OF_FILE
%}

%option noyywrap nounput batch debug

id    [a-zA-Z][a-zA-Z_0-9]*
int   [0-9]+
blank [ \t\r]

%{
# define YY_USER_ACTION  yylloc->columns (yyleng);
%}

%%
%{
  yylloc->step ();
%}
{blank}+   yylloc->step ();
[\n]+      yylloc->lines (yyleng); yylloc->step ();

%{
typedef yy::mcmas_parser::token token;
%}
"--".*			; /* comment */
"Semantics"		return(token::SEMANTICS);
"MultiAssignment"	return(token::MULTIASSIGNMENT);
"SingleAssignment"	return(token::SINGLEASSIGNMENT);
"MA"			return(token::MULTIASSIGNMENT);
"SA"			return(token::SINGLEASSIGNMENT);
"Agent"			return(token::AGENT);
"RedStates"             return(token::REDSTATES); 
"GreenStates"           return(token::GREENSTATES); 
"Actions"		return(token::ACTIONS);
"Action"		return(token::ACTION);
"Protocol"		return(token::PROTOCOL);
"Evolution"		return(token::EVOLUTION);
"Evaluation"		return(token::EVALUATION);
"InitStates"		return(token::INITSTATES);
"Groups"		return(token::GROUPS);
"Fairness"		return(token::FAIRNESS);
"Formulae"              return(token::FORMULAE);
"end"			return(token::END);
"Environment"           return(token::ENVIRONMENT);
"Obsvars"               return(token::OBSVARS);
"Lobsvars"              return(token::LOBSVARS);
"Vars"                  return(token::VARS);
"boolean"               return(token::BOOLEAN);
"true"                  return(token::BTRUE);
"false"                 return(token::BFALSE);
"Other"    		return(token::OTHER);
"("			return(token::LB);
")"			return(token::RB);
"{"			return(token::LCB);
"}"			return(token::RCB);
"<"			return(token::LT);
">"			return(token::GT);
"<="                    return(token::LE);
">="                    return(token::GE);
"<>"                    return(token::NEQ);
"if"			return(token::IF);
"="			return(token::EQ);
"and"			return(token::AND);
"or"			return(token::OR);
"->"                    return(token::IMPLIES);
"LTL"                   return(token::LTLPREFIX);
"CTL*"                  return(token::CTLSPREFIX);
"AG"                    return(token::AG);
"EG"                    return(token::EG);
"AX"                    return(token::AX);
"EX"                    return(token::EX);
"X"                     return(token::X);
"F"                     return(token::F);
"G"                     return(token::G);
"AF"                    return(token::AF);
"EF"                    return(token::EF);
"A"                     return(token::A);
"E"                     return(token::E);
"U"                     return(token::UNTIL);
"K"                     return(token::K);
"GK"                    return(token::GK);
"GCK"                   return(token::GCK);
"O"                     return(token::O);
"DK"                    return(token::DK);
"!"			return(token::NOT);
":"			return(token::COLON);
","			return(token::COMMA);
"."			return(token::DOT);
";"			return(token::SEMICOLON);
".."                    return(token::TO);
"-"                     return(token::MINUS);
"+"                     return(token::PLUS);
"*"                     return(token::TIMES);
"/"                     return(token::DIVIDE);
"&"                     return(token::BITAND);
"|"                     return(token::BITOR);
"~"                     return(token::BITNOT);
"^"                     return(token::BITXOR);
"["                     return(token::LSB);
"]"                     return(token::RSB);
"?"                     return(token::QUESTION);

{id}			{ yylval->sval = new std::string(yytext);
			  return(token::ID);
			}
{int}	                { int n = atoi(yytext);
                          yylval->ival = n;
		          return(token::NUMBER);
			}
.                       driver.error (*yylloc, "invalid character");
%%

void
mcmas_driver::scan_begin ()
{
  yy_flex_debug = trace_scanning;
  if (!(yyin = fopen (file.c_str (), "r"))) {
    error (std::string ("cannot open ") + file);
    exit(0);
  }
}

void
mcmas_driver::scan_end ()
{
  fclose (yyin);
}
