/* A Bison parser, made by GNU Bison 2.5.  */

/* Skeleton interface for Bison LALR(1) parsers in C++
   
      Copyright (C) 2002-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C++ LALR(1) parser skeleton written by Akim Demaille.  */

#ifndef PARSER_HEADER_H
# define PARSER_HEADER_H

/* "%code requires" blocks.  */

/* Line 35 of lalr1.cc  */
#line 6 "parser/nssis_new.yy"

#define USE(VALUE) /*empty*/

# include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include "types.hh"

class mcmas_driver;



/* Line 35 of lalr1.cc  */
#line 63 "parser/nssis.hh"


#include <string>
#include <iostream>
#include "stack.hh"
#include "location.hh"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


namespace yy {

/* Line 35 of lalr1.cc  */
#line 93 "parser/nssis.hh"

  /// A Bison parser.
  class mcmas_parser
  {
  public:
    /// Symbol semantic values.
#ifndef YYSTYPE
    union semantic_type
    {

/* Line 35 of lalr1.cc  */
#line 37 "parser/nssis_new.yy"

  int ival;
  string* sval;
  map<string, basictype *>* map_basictype;
  pair<map<string, basictype *>*, vector<basictype*>*>* map_vec_basictype;
  basictype* _basictype;
  set<string>* set_string;
  vector<evolution_line*>* vector_evolution_line;
  evolution_line* _evolution_line;
  vector<assignment*>* vector_assignment;
  bool_expression* _bool_expression;
  arithmetic_expression* _arithmetic_expression;
  bit_expression* _bit_expression;
  expression* _expression;
  basic_agent* _basic_agent;
  vector<protocol_line*>* vector_protocol_line;
  protocol_line* _protocol_line;
  unsigned char _unsigned_char;
  bool_value* _bool_value;
  modal_formula* _modal_formula;
  fairness_expression* _fairness_expression;
  pair<modal_formula*, modal_formula*>* dual_modal_formula;
  pair<string*, modal_formula*>* ID_modal_formula;
  pair<pair<string*, string*>*, modal_formula*>* ID_ID_modal_formula;
  pair<fairness_expression*, fairness_expression*>* dual_fairness_expression;
  pair<string*, fairness_expression*>* ID_fairness_expression;
  pair<pair<string*, string*>*, fairness_expression*>* ID_ID_fairness_expression;
  map<string, variable*>* map_string_variable;
  bool boolean_flag;



/* Line 35 of lalr1.cc  */
#line 139 "parser/nssis.hh"
    };
#else
    typedef YYSTYPE semantic_type;
#endif
    /// Symbol locations.
    typedef location location_type;
    /// Tokens.
    struct token
    {
      /* Tokens.  */
   enum yytokentype {
     END_OF_FILE = 0,
     AGENT = 258,
     ACTIONS = 259,
     PROTOCOL = 260,
     EVOLUTION = 261,
     END = 262,
     LB = 263,
     RB = 264,
     LCB = 265,
     RCB = 266,
     LSB = 267,
     RSB = 268,
     LT = 269,
     GT = 270,
     IF = 271,
     EQ = 272,
     AND = 273,
     ENVIRONMENT = 274,
     OBSVARS = 275,
     VARS = 276,
     BOOLEAN = 277,
     BTRUE = 278,
     BFALSE = 279,
     TO = 280,
     LE = 281,
     GE = 282,
     NEQ = 283,
     MINUS = 284,
     PLUS = 285,
     TIMES = 286,
     DIVIDE = 287,
     ACTION = 288,
     REDSTATES = 289,
     GREENSTATES = 290,
     FAIRNESS = 291,
     OTHER = 292,
     LOBSVARS = 293,
     OR = 294,
     NOT = 295,
     COLON = 296,
     COMMA = 297,
     DOT = 298,
     SEMICOLON = 299,
     EVALUATION = 300,
     INITSTATES = 301,
     GROUPS = 302,
     FORMULAE = 303,
     IMPLIES = 304,
     AG = 305,
     EG = 306,
     AX = 307,
     EX = 308,
     AF = 309,
     EF = 310,
     A = 311,
     E = 312,
     UNTIL = 313,
     K = 314,
     GK = 315,
     GCK = 316,
     O = 317,
     DK = 318,
     MULTIASSIGNMENT = 319,
     SINGLEASSIGNMENT = 320,
     SEMANTICS = 321,
     BITAND = 322,
     BITOR = 323,
     BITNOT = 324,
     BITXOR = 325,
     X = 326,
     F = 327,
     G = 328,
     PERFECTRECALL = 329,
     ID = 330,
     NUMBER = 331,
     QUANTIFIER = 332
   };

    };
    /// Token type.
    typedef token::yytokentype token_type;

    /// Build a parser object.
    mcmas_parser (mcmas_driver& driver_yyarg);
    virtual ~mcmas_parser ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

  private:
    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Generate an error message.
    /// \param state   the state where the error occurred.
    /// \param tok     the lookahead token.
    virtual std::string yysyntax_error_ (int yystate, int tok);

#if YYDEBUG
    /// \brief Report a symbol value on the debug stream.
    /// \param yytype       The token type.
    /// \param yyvaluep     Its semantic value.
    /// \param yylocationp  Its location.
    virtual void yy_symbol_value_print_ (int yytype,
					 const semantic_type* yyvaluep,
					 const location_type* yylocationp);
    /// \brief Report a symbol on the debug stream.
    /// \param yytype       The token type.
    /// \param yyvaluep     Its semantic value.
    /// \param yylocationp  Its location.
    virtual void yy_symbol_print_ (int yytype,
				   const semantic_type* yyvaluep,
				   const location_type* yylocationp);
#endif


    /// State numbers.
    typedef int state_type;
    /// State stack type.
    typedef stack<state_type>    state_stack_type;
    /// Semantic value stack type.
    typedef stack<semantic_type> semantic_stack_type;
    /// location stack type.
    typedef stack<location_type> location_stack_type;

    /// The state stack.
    state_stack_type yystate_stack_;
    /// The semantic value stack.
    semantic_stack_type yysemantic_stack_;
    /// The location stack.
    location_stack_type yylocation_stack_;

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    /// Internal symbol numbers.
    typedef unsigned char token_number_type;
    /* Tables.  */
    /// For a state, the index in \a yytable_ of its portion.
    static const short int yypact_[];
    static const short int yypact_ninf_;

    /// For a state, default reduction number.
    /// Unless\a  yytable_ specifies something else to do.
    /// Zero means the default is an error.
    static const unsigned short int yydefact_[];

    static const short int yypgoto_[];
    static const short int yydefgoto_[];

    /// What to do in a state.
    /// \a yytable_[yypact_[s]]: what to do in state \a s.
    /// - if positive, shift that token.
    /// - if negative, reduce the rule which number is the opposite.
    /// - if zero, do what YYDEFACT says.
    static const short int yytable_[];
    static const short int yytable_ninf_;

    static const short int yycheck_[];

    /// For a state, its accessing symbol.
    static const unsigned char yystos_[];

    /// For a rule, its LHS.
    static const unsigned char yyr1_[];
    /// For a rule, its RHS length.
    static const unsigned char yyr2_[];

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#endif

    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *n);

#if YYDEBUG
    /// A type to store symbol numbers and -1.
    typedef short int rhs_number_type;
    /// A `-1'-separated list of the rules' RHS.
    static const rhs_number_type yyrhs_[];
    /// For each rule, the index of the first RHS symbol in \a yyrhs_.
    static const unsigned short int yyprhs_[];
    /// For each rule, its source line number.
    static const unsigned short int yyrline_[];
    /// For each scanner token number, its symbol number.
    static const unsigned short int yytoken_number_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();

    /* Debugging.  */
    int yydebug_;
    std::ostream* yycdebug_;
#endif

    /// Convert a scanner token number \a t to a symbol number.
    token_number_type yytranslate_ (int t);

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg        Why this token is reclaimed.
    /// \param yytype       The symbol type.
    /// \param yyvaluep     Its semantic value.
    /// \param yylocationp  Its location.
    inline void yydestruct_ (const char* yymsg,
			     int yytype,
			     semantic_type* yyvaluep,
			     location_type* yylocationp);

    /// Pop \a n symbols the three stacks.
    inline void yypop_ (unsigned int n = 1);

    /* Constants.  */
    static const int yyeof_;
    /* LAST_ -- Last index in TABLE_.  */
    static const int yylast_;
    static const int yynnts_;
    static const int yyempty_;
    static const int yyfinal_;
    static const int yyterror_;
    static const int yyerrcode_;
    static const int yyntokens_;
    static const unsigned int yyuser_token_number_max_;
    static const token_number_type yyundef_token_;

    /* User arguments.  */
    mcmas_driver& driver;
  };

} // yy

/* Line 35 of lalr1.cc  */
#line 406 "parser/nssis.hh"



#endif /* ! defined PARSER_HEADER_H */
