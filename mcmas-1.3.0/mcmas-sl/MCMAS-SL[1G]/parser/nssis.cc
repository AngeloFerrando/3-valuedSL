/* A Bison parser, made by GNU Bison 2.5.  */

/* Skeleton implementation for Bison LALR(1) parsers in C++
   
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


/* First part of user declarations.  */


/* Line 293 of lalr1.cc  */
#line 39 "parser/nssis.cc"


#include "nssis.hh"

/* User implementation prologue.  */

/* Line 299 of lalr1.cc  */
#line 68 "parser/nssis_new.yy"

#include "mcmas-driver.hh"

  extern map < string, int > options;
  extern vector<string *> *string_table;
  extern vector<variable *> *variable_table;
  extern vector<bool_expression *> *logic_expression_table;
  extern vector<bool_expression *> *logic_expression_table1;
  extern map<string, basic_agent *> *is_agents;
  extern vector<basic_agent *> *agents;
  extern map<string, bool_expression *> *is_evaluation;
  extern bool_expression *is_istates;
  extern map<string, set<string> > *is_groups;
  extern vector<modal_formula> *is_formulae;
  extern vector<modal_formula> *is_perfect_recall_formulae;
  extern vector<fairness_expression *> *is_fairness;

  extern int search_string_table(string *s);
  extern int search_variable_table(variable *v);
  extern int search_logic_expression_table(expression *e1, expression *e2);
  extern int search_logic_expression_table1(expression *e1, expression *e2);


/* Line 299 of lalr1.cc  */
#line 72 "parser/nssis.cc"

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* FIXME: INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                               \
 do                                                                    \
   if (N)                                                              \
     {                                                                 \
       (Current).begin = YYRHSLOC (Rhs, 1).begin;                      \
       (Current).end   = YYRHSLOC (Rhs, N).end;                        \
     }                                                                 \
   else                                                                \
     {                                                                 \
       (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;        \
     }                                                                 \
 while (false)
#endif

/* Suppress unused-variable warnings by "using" E.  */
#define YYUSE(e) ((void) (e))

/* Enable debugging if requested.  */
#if YYDEBUG

/* A pseudo ostream that takes yydebug_ into account.  */
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)	\
do {							\
  if (yydebug_)						\
    {							\
      *yycdebug_ << Title << ' ';			\
      yy_symbol_print_ ((Type), (Value), (Location));	\
      *yycdebug_ << std::endl;				\
    }							\
} while (false)

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug_)				\
    yy_reduce_print_ (Rule);		\
} while (false)

# define YY_STACK_PRINT()		\
do {					\
  if (yydebug_)				\
    yystack_print_ ();			\
} while (false)

#else /* !YYDEBUG */

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_REDUCE_PRINT(Rule)
# define YY_STACK_PRINT()

#endif /* !YYDEBUG */

#define yyerrok		(yyerrstatus_ = 0)
#define yyclearin	(yychar = yyempty_)

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {

/* Line 382 of lalr1.cc  */
#line 158 "parser/nssis.cc"

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  mcmas_parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              /* Fall through.  */
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  mcmas_parser::mcmas_parser (mcmas_driver& driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {
  }

  mcmas_parser::~mcmas_parser ()
  {
  }

#if YYDEBUG
  /*--------------------------------.
  | Print this symbol on YYOUTPUT.  |
  `--------------------------------*/

  inline void
  mcmas_parser::yy_symbol_value_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yyvaluep);
    switch (yytype)
      {
        case 75: /* "\"identifier\"" */

/* Line 449 of lalr1.cc  */
#line 231 "parser/nssis_new.yy"
	{ debug_stream () << *(yyvaluep->sval); };

/* Line 449 of lalr1.cc  */
#line 233 "parser/nssis.cc"
	break;
      case 76: /* "\"number\"" */

/* Line 449 of lalr1.cc  */
#line 271 "parser/nssis_new.yy"
	{ debug_stream () << (yyvaluep->ival); };

/* Line 449 of lalr1.cc  */
#line 242 "parser/nssis.cc"
	break;
       default:
	  break;
      }
  }


  void
  mcmas_parser::yy_symbol_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    *yycdebug_ << (yytype < yyntokens_ ? "token" : "nterm")
	       << ' ' << yytname_[yytype] << " ("
	       << *yylocationp << ": ";
    yy_symbol_value_print_ (yytype, yyvaluep, yylocationp);
    *yycdebug_ << ')';
  }
#endif

  void
  mcmas_parser::yydestruct_ (const char* yymsg,
			   int yytype, semantic_type* yyvaluep, location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yymsg);
    YYUSE (yyvaluep);

    YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

    switch (yytype)
      {
        case 75: /* "\"identifier\"" */

/* Line 480 of lalr1.cc  */
#line 232 "parser/nssis_new.yy"
	{ delete (yyvaluep->sval); };

/* Line 480 of lalr1.cc  */
#line 281 "parser/nssis.cc"
	break;
      case 87: /* "obsvardef" */

/* Line 480 of lalr1.cc  */
#line 233 "parser/nssis_new.yy"
	{ delete (yyvaluep->map_vec_basictype); };

/* Line 480 of lalr1.cc  */
#line 290 "parser/nssis.cc"
	break;
      case 88: /* "varidlist" */

/* Line 480 of lalr1.cc  */
#line 234 "parser/nssis_new.yy"
	{ delete (yyvaluep->map_vec_basictype); };

/* Line 480 of lalr1.cc  */
#line 299 "parser/nssis.cc"
	break;
      case 89: /* "onevardef" */

/* Line 480 of lalr1.cc  */
#line 235 "parser/nssis_new.yy"
	{ delete (yyvaluep->_basictype); };

/* Line 480 of lalr1.cc  */
#line 308 "parser/nssis.cc"
	break;
      case 90: /* "enumlist" */

/* Line 480 of lalr1.cc  */
#line 236 "parser/nssis_new.yy"
	{ delete (yyvaluep->set_string); };

/* Line 480 of lalr1.cc  */
#line 317 "parser/nssis.cc"
	break;
      case 94: /* "envardef" */

/* Line 480 of lalr1.cc  */
#line 238 "parser/nssis_new.yy"
	{ delete (yyvaluep->map_vec_basictype); };

/* Line 480 of lalr1.cc  */
#line 326 "parser/nssis.cc"
	break;
      case 95: /* "vardef" */

/* Line 480 of lalr1.cc  */
#line 237 "parser/nssis_new.yy"
	{ delete (yyvaluep->map_vec_basictype); };

/* Line 480 of lalr1.cc  */
#line 335 "parser/nssis.cc"
	break;
      case 99: /* "reddef" */

/* Line 480 of lalr1.cc  */
#line 246 "parser/nssis_new.yy"
	{ delete (yyvaluep->_bool_expression); };

/* Line 480 of lalr1.cc  */
#line 344 "parser/nssis.cc"
	break;
      case 101: /* "rboolcond" */

/* Line 480 of lalr1.cc  */
#line 245 "parser/nssis_new.yy"
	{ delete (yyvaluep->_bool_expression); };

/* Line 480 of lalr1.cc  */
#line 353 "parser/nssis.cc"
	break;
      case 104: /* "envevdef" */

/* Line 480 of lalr1.cc  */
#line 239 "parser/nssis_new.yy"
	{ delete (yyvaluep->vector_evolution_line); };

/* Line 480 of lalr1.cc  */
#line 362 "parser/nssis.cc"
	break;
      case 105: /* "envevdeflist" */

/* Line 480 of lalr1.cc  */
#line 240 "parser/nssis_new.yy"
	{ delete (yyvaluep->vector_evolution_line); };

/* Line 480 of lalr1.cc  */
#line 371 "parser/nssis.cc"
	break;
      case 106: /* "envevline" */

/* Line 480 of lalr1.cc  */
#line 241 "parser/nssis_new.yy"
	{ delete (yyvaluep->_evolution_line); };

/* Line 480 of lalr1.cc  */
#line 380 "parser/nssis.cc"
	break;
      case 107: /* "boolresult" */

/* Line 480 of lalr1.cc  */
#line 242 "parser/nssis_new.yy"
	{ delete (yyvaluep->vector_assignment); };

/* Line 480 of lalr1.cc  */
#line 389 "parser/nssis.cc"
	break;
      case 112: /* "agent" */

/* Line 480 of lalr1.cc  */
#line 251 "parser/nssis_new.yy"
	{ delete (yyvaluep->_basic_agent); };

/* Line 480 of lalr1.cc  */
#line 398 "parser/nssis.cc"
	break;
      case 119: /* "enactiondef" */

/* Line 480 of lalr1.cc  */
#line 253 "parser/nssis_new.yy"
	{ delete (yyvaluep->set_string); };

/* Line 480 of lalr1.cc  */
#line 407 "parser/nssis.cc"
	break;
      case 120: /* "actiondef" */

/* Line 480 of lalr1.cc  */
#line 252 "parser/nssis_new.yy"
	{ delete (yyvaluep->set_string); };

/* Line 480 of lalr1.cc  */
#line 416 "parser/nssis.cc"
	break;
      case 121: /* "actionidlist" */

/* Line 480 of lalr1.cc  */
#line 254 "parser/nssis_new.yy"
	{ delete (yyvaluep->set_string); };

/* Line 480 of lalr1.cc  */
#line 425 "parser/nssis.cc"
	break;
      case 124: /* "enprotdef" */

/* Line 480 of lalr1.cc  */
#line 256 "parser/nssis_new.yy"
	{ delete (yyvaluep->vector_protocol_line); };

/* Line 480 of lalr1.cc  */
#line 434 "parser/nssis.cc"
	break;
      case 125: /* "protdef" */

/* Line 480 of lalr1.cc  */
#line 255 "parser/nssis_new.yy"
	{ delete (yyvaluep->vector_protocol_line); };

/* Line 480 of lalr1.cc  */
#line 443 "parser/nssis.cc"
	break;
      case 127: /* "protdeflist" */

/* Line 480 of lalr1.cc  */
#line 257 "parser/nssis_new.yy"
	{ delete (yyvaluep->vector_protocol_line); };

/* Line 480 of lalr1.cc  */
#line 452 "parser/nssis.cc"
	break;
      case 131: /* "protline" */

/* Line 480 of lalr1.cc  */
#line 258 "parser/nssis_new.yy"
	{ delete (yyvaluep->_protocol_line); };

/* Line 480 of lalr1.cc  */
#line 461 "parser/nssis.cc"
	break;
      case 133: /* "enabledidlist" */

/* Line 480 of lalr1.cc  */
#line 259 "parser/nssis_new.yy"
	{ delete (yyvaluep->set_string); };

/* Line 480 of lalr1.cc  */
#line 470 "parser/nssis.cc"
	break;
      case 134: /* "evdef" */

/* Line 480 of lalr1.cc  */
#line 260 "parser/nssis_new.yy"
	{ delete (yyvaluep->vector_evolution_line); };

/* Line 480 of lalr1.cc  */
#line 479 "parser/nssis.cc"
	break;
      case 135: /* "evdeflist" */

/* Line 480 of lalr1.cc  */
#line 261 "parser/nssis_new.yy"
	{ delete (yyvaluep->vector_evolution_line); };

/* Line 480 of lalr1.cc  */
#line 488 "parser/nssis.cc"
	break;
      case 136: /* "evline" */

/* Line 480 of lalr1.cc  */
#line 262 "parser/nssis_new.yy"
	{ delete (yyvaluep->_evolution_line); };

/* Line 480 of lalr1.cc  */
#line 497 "parser/nssis.cc"
	break;
      case 138: /* "lboolcond" */

/* Line 480 of lalr1.cc  */
#line 243 "parser/nssis_new.yy"
	{ delete (yyvaluep->_bool_expression); };

/* Line 480 of lalr1.cc  */
#line 506 "parser/nssis.cc"
	break;
      case 160: /* "eboolcond" */

/* Line 480 of lalr1.cc  */
#line 244 "parser/nssis_new.yy"
	{ delete (yyvaluep->_bool_expression); };

/* Line 480 of lalr1.cc  */
#line 515 "parser/nssis.cc"
	break;
      case 162: /* "gboolcond" */

/* Line 480 of lalr1.cc  */
#line 263 "parser/nssis_new.yy"
	{ delete (yyvaluep->_bool_expression); };

/* Line 480 of lalr1.cc  */
#line 524 "parser/nssis.cc"
	break;
      case 163: /* "varvalue1" */

/* Line 480 of lalr1.cc  */
#line 247 "parser/nssis_new.yy"
	{ delete (yyvaluep->_expression); };

/* Line 480 of lalr1.cc  */
#line 533 "parser/nssis.cc"
	break;
      case 164: /* "boolvalue" */

/* Line 480 of lalr1.cc  */
#line 264 "parser/nssis_new.yy"
	{ delete (yyvaluep->_bool_value); };

/* Line 480 of lalr1.cc  */
#line 542 "parser/nssis.cc"
	break;
      case 165: /* "varvalue2" */

/* Line 480 of lalr1.cc  */
#line 248 "parser/nssis_new.yy"
	{ delete (yyvaluep->_expression); };

/* Line 480 of lalr1.cc  */
#line 551 "parser/nssis.cc"
	break;
      case 166: /* "varvalue3" */

/* Line 480 of lalr1.cc  */
#line 249 "parser/nssis_new.yy"
	{ delete (yyvaluep->_expression); };

/* Line 480 of lalr1.cc  */
#line 560 "parser/nssis.cc"
	break;
      case 167: /* "varvalue4" */

/* Line 480 of lalr1.cc  */
#line 250 "parser/nssis_new.yy"
	{ delete (yyvaluep->_expression); };

/* Line 480 of lalr1.cc  */
#line 569 "parser/nssis.cc"
	break;
      case 172: /* "evaboolcond" */

/* Line 480 of lalr1.cc  */
#line 265 "parser/nssis_new.yy"
	{ delete (yyvaluep->_bool_expression); };

/* Line 480 of lalr1.cc  */
#line 578 "parser/nssis.cc"
	break;
      case 176: /* "isboolcond" */

/* Line 480 of lalr1.cc  */
#line 266 "parser/nssis_new.yy"
	{ delete (yyvaluep->_bool_expression); };

/* Line 480 of lalr1.cc  */
#line 587 "parser/nssis.cc"
	break;
      case 183: /* "namelist" */

/* Line 480 of lalr1.cc  */
#line 267 "parser/nssis_new.yy"
	{ delete (yyvaluep->set_string); };

/* Line 480 of lalr1.cc  */
#line 596 "parser/nssis.cc"
	break;
      case 184: /* "agentname" */

/* Line 480 of lalr1.cc  */
#line 268 "parser/nssis_new.yy"
	{ delete (yyvaluep->sval); };

/* Line 480 of lalr1.cc  */
#line 605 "parser/nssis.cc"
	break;
      case 201: /* "formula" */

/* Line 480 of lalr1.cc  */
#line 269 "parser/nssis_new.yy"
	{ delete (yyvaluep->_modal_formula); };

/* Line 480 of lalr1.cc  */
#line 614 "parser/nssis.cc"
	break;

	default:
	  break;
      }
  }

  void
  mcmas_parser::yypop_ (unsigned int n)
  {
    yystate_stack_.pop (n);
    yysemantic_stack_.pop (n);
    yylocation_stack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  mcmas_parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  mcmas_parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  mcmas_parser::debug_level_type
  mcmas_parser::debug_level () const
  {
    return yydebug_;
  }

  void
  mcmas_parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif

  inline bool
  mcmas_parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  mcmas_parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  mcmas_parser::parse ()
  {
    /// Lookahead and lookahead in internal form.
    int yychar = yyempty_;
    int yytoken = 0;

    /* State.  */
    int yyn;
    int yylen = 0;
    int yystate = 0;

    /* Error handling.  */
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// Semantic value of the lookahead.
    semantic_type yylval;
    /// Location of the lookahead.
    location_type yylloc;
    /// The locations where the error started and ended.
    location_type yyerror_range[3];

    /// $$.
    semantic_type yyval;
    /// @$.
    location_type yyloc;

    int yyresult;

    YYCDEBUG << "Starting parse" << std::endl;


    /* User initialization code.  */
    
/* Line 565 of lalr1.cc  */
#line 29 "parser/nssis_new.yy"
{
  // Initialize the initial location.
  yylloc.begin.filename = yylloc.end.filename = &driver.file;
}

/* Line 565 of lalr1.cc  */
#line 712 "parser/nssis.cc"

    /* Initialize the stacks.  The initial state will be pushed in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystate_stack_ = state_stack_type (0);
    yysemantic_stack_ = semantic_stack_type (0);
    yylocation_stack_ = location_stack_type (0);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* New state.  */
  yynewstate:
    yystate_stack_.push (yystate);
    YYCDEBUG << "Entering state " << yystate << std::endl;

    /* Accept?  */
    if (yystate == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    /* Backup.  */
  yybackup:

    /* Try to take a decision without lookahead.  */
    yyn = yypact_[yystate];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    /* Read a lookahead token.  */
    if (yychar == yyempty_)
      {
	YYCDEBUG << "Reading a token: ";
	yychar = yylex (&yylval, &yylloc, driver);
      }


    /* Convert token to internal form.  */
    if (yychar <= yyeof_)
      {
	yychar = yytoken = yyeof_;
	YYCDEBUG << "Now at end of input." << std::endl;
      }
    else
      {
	yytoken = yytranslate_ (yychar);
	YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
      }

    /* If the proper action on seeing token YYTOKEN is to reduce or to
       detect an error, take that action.  */
    yyn += yytoken;
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yytoken)
      goto yydefault;

    /* Reduce or error.  */
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
	if (yy_table_value_is_error_ (yyn))
	  goto yyerrlab;
	yyn = -yyn;
	goto yyreduce;
      }

    /* Shift the lookahead token.  */
    YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

    /* Discard the token being shifted.  */
    yychar = yyempty_;

    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* Count tokens shifted since error; after three, turn off error
       status.  */
    if (yyerrstatus_)
      --yyerrstatus_;

    yystate = yyn;
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystate];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    /* If YYLEN is nonzero, implement the default value of the action:
       `$$ = $1'.  Otherwise, use the top of the stack.

       Otherwise, the following line sets YYVAL to garbage.
       This behavior is undocumented and Bison
       users should not rely upon it.  */
    if (yylen)
      yyval = yysemantic_stack_[yylen - 1];
    else
      yyval = yysemantic_stack_[0];

    {
      slice<location_type, location_stack_type> slice (yylocation_stack_, yylen);
      YYLLOC_DEFAULT (yyloc, slice, yylen);
    }
    YY_REDUCE_PRINT (yyn);
    switch (yyn)
      {
	  case 4:

/* Line 690 of lalr1.cc  */
#line 279 "parser/nssis_new.yy"
    {
    options["smv"] = 0;
 }
    break;

  case 5:

/* Line 690 of lalr1.cc  */
#line 282 "parser/nssis_new.yy"
    {
    options["smv"] = 1;
 }
    break;

  case 6:

/* Line 690 of lalr1.cc  */
#line 285 "parser/nssis_new.yy"
    {
  driver.syntax_error = true;
 }
    break;

  case 11:

/* Line 690 of lalr1.cc  */
#line 294 "parser/nssis_new.yy"
    {
  basic_agent *env = new basic_agent((*string_table)[0], NULL, new map<string, basictype *>, new vector<basictype *>,
				     new map<string, basictype *>, new vector<basictype *>, NULL, new set<string>, 
				     new vector<protocol_line*>, new vector<evolution_line *>);
  (*is_agents)["Environment"] = env;
  agents->insert(agents->begin(), env);
 }
    break;

  case 12:

/* Line 690 of lalr1.cc  */
#line 301 "parser/nssis_new.yy"
    {
  basic_agent *env = new basic_agent((*string_table)[0], NULL, new map<string, basictype *>, new vector<basictype *>, 
				     new map<string, basictype *>, new vector<basictype *>, NULL, new set<string>, 
				     new vector<protocol_line*>, new vector<evolution_line *>);
  (*is_agents)["Environment"] = env;
  agents->insert(agents->begin(), env);
 }
    break;

  case 13:

/* Line 690 of lalr1.cc  */
#line 308 "parser/nssis_new.yy"
    {
  basic_agent *env = new basic_agent((*string_table)[0], NULL, new map<string, basictype *>, new vector<basictype *>, 
				     new map<string, basictype *>, new vector<basictype *>, NULL, new set<string>, 
				     new vector<protocol_line*>, new vector<evolution_line *>);
  (*is_agents)["Environment"] = env;
  agents->insert(agents->begin(), env);
 }
    break;

  case 14:

/* Line 690 of lalr1.cc  */
#line 315 "parser/nssis_new.yy"
    {
  basic_agent *env = new basic_agent((*string_table)[0], NULL, new map<string, basictype *>, new vector<basictype *>, 
				     new map<string, basictype *>, new vector<basictype *>, NULL, new set<string>, 
				     new vector<protocol_line*>, new vector<evolution_line *>);
  (*is_agents)["Environment"] = env;
  agents->insert(agents->begin(), env);
 }
    break;

  case 15:

/* Line 690 of lalr1.cc  */
#line 325 "parser/nssis_new.yy"
    {
  (yyval.ival) = 1;
 }
    break;

  case 16:

/* Line 690 of lalr1.cc  */
#line 328 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 17:

/* Line 690 of lalr1.cc  */
#line 332 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 18:

/* Line 690 of lalr1.cc  */
#line 336 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 19:

/* Line 690 of lalr1.cc  */
#line 340 "parser/nssis_new.yy"
    {
  (yyval.ival) = 1;
 }
    break;

  case 20:

/* Line 690 of lalr1.cc  */
#line 343 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 21:

/* Line 690 of lalr1.cc  */
#line 347 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 22:

/* Line 690 of lalr1.cc  */
#line 351 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 23:

/* Line 690 of lalr1.cc  */
#line 356 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(8) - (1)].ival)==1 && (yysemantic_stack_[(8) - (2)].map_vec_basictype)!=NULL && (yysemantic_stack_[(8) - (3)].map_vec_basictype)!=NULL && (yysemantic_stack_[(8) - (5)].set_string)!=NULL && (yysemantic_stack_[(8) - (6)].vector_protocol_line)!=NULL && (yysemantic_stack_[(8) - (7)].vector_evolution_line)!=NULL && (yysemantic_stack_[(8) - (8)].ival)==1) { // redstates is NULL if no red state at all
    basic_agent *env = new basic_agent((*string_table)[0], NULL, (yysemantic_stack_[(8) - (2)].map_vec_basictype)->first, (yysemantic_stack_[(8) - (2)].map_vec_basictype)->second, (yysemantic_stack_[(8) - (3)].map_vec_basictype)->first, (yysemantic_stack_[(8) - (3)].map_vec_basictype)->second, (yysemantic_stack_[(8) - (4)]._bool_expression), (yysemantic_stack_[(8) - (5)].set_string), (yysemantic_stack_[(8) - (6)].vector_protocol_line), (yysemantic_stack_[(8) - (7)].vector_evolution_line));
    (*is_agents)["Environment"] = env;
    agents->push_back(env);
  }
 }
    break;

  case 24:

/* Line 690 of lalr1.cc  */
#line 363 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(7) - (1)].ival)==1 && (yysemantic_stack_[(7) - (2)].map_vec_basictype)!=NULL && (yysemantic_stack_[(7) - (3)].map_vec_basictype)!=NULL && (yysemantic_stack_[(7) - (4)].set_string)!=NULL && (yysemantic_stack_[(7) - (5)].vector_protocol_line)!=NULL && (yysemantic_stack_[(7) - (6)].vector_evolution_line)!=NULL && (yysemantic_stack_[(7) - (7)].ival)==1) { // redstates is NULL if no red state at all
    basic_agent *env = new basic_agent((*string_table)[0], NULL, (yysemantic_stack_[(7) - (2)].map_vec_basictype)->first, (yysemantic_stack_[(7) - (2)].map_vec_basictype)->second, (yysemantic_stack_[(7) - (3)].map_vec_basictype)->first, (yysemantic_stack_[(7) - (3)].map_vec_basictype)->second, NULL, (yysemantic_stack_[(7) - (4)].set_string), (yysemantic_stack_[(7) - (5)].vector_protocol_line), (yysemantic_stack_[(7) - (6)].vector_evolution_line));
    (*is_agents)["Environment"] = env;
    agents->push_back(env);
  }
 }
    break;

  case 25:

/* Line 690 of lalr1.cc  */
#line 370 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(7) - (1)].ival)==1 && (yysemantic_stack_[(7) - (2)].map_vec_basictype)!=NULL && (yysemantic_stack_[(7) - (4)].set_string)!=NULL && (yysemantic_stack_[(7) - (5)].vector_protocol_line)!=NULL && (yysemantic_stack_[(7) - (6)].vector_evolution_line)!=NULL && (yysemantic_stack_[(7) - (7)].ival)==1) { // redstates is NULL if no red state at all
    basic_agent *env = new basic_agent((*string_table)[0], NULL, new map<string, basictype *>, new vector<basictype *>, (yysemantic_stack_[(7) - (2)].map_vec_basictype)->first, (yysemantic_stack_[(7) - (2)].map_vec_basictype)->second, (yysemantic_stack_[(7) - (3)]._bool_expression), (yysemantic_stack_[(7) - (4)].set_string), (yysemantic_stack_[(7) - (5)].vector_protocol_line), (yysemantic_stack_[(7) - (6)].vector_evolution_line));
    (*is_agents)["Environment"] = env;
    agents->push_back(env);
  }
 }
    break;

  case 26:

/* Line 690 of lalr1.cc  */
#line 377 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(6) - (1)].ival)==1 && (yysemantic_stack_[(6) - (2)].map_vec_basictype)!=NULL && (yysemantic_stack_[(6) - (3)].set_string)!=NULL && (yysemantic_stack_[(6) - (4)].vector_protocol_line)!=NULL && (yysemantic_stack_[(6) - (5)].vector_evolution_line)!=NULL && (yysemantic_stack_[(6) - (6)].ival)==1) { // redstates is NULL if no red state at all
    basic_agent *env = new basic_agent((*string_table)[0], NULL, new map<string, basictype *>, new vector<basictype *>, (yysemantic_stack_[(6) - (2)].map_vec_basictype)->first, (yysemantic_stack_[(6) - (2)].map_vec_basictype)->second, NULL, (yysemantic_stack_[(6) - (3)].set_string), (yysemantic_stack_[(6) - (4)].vector_protocol_line), (yysemantic_stack_[(6) - (5)].vector_evolution_line));
    (*is_agents)["Environment"] = env;
    agents->push_back(env);
  }
 }
    break;

  case 27:

/* Line 690 of lalr1.cc  */
#line 384 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(7) - (1)].ival)==1 && (yysemantic_stack_[(7) - (2)].map_vec_basictype)!=NULL && (yysemantic_stack_[(7) - (4)].set_string)!=NULL && (yysemantic_stack_[(7) - (5)].vector_protocol_line)!=NULL && (yysemantic_stack_[(7) - (6)].vector_evolution_line)!=NULL && (yysemantic_stack_[(7) - (7)].ival)==1) { // redstates is NULL if no red state at all
    basic_agent *env = new basic_agent((*string_table)[0], NULL, (yysemantic_stack_[(7) - (2)].map_vec_basictype)->first, (yysemantic_stack_[(7) - (2)].map_vec_basictype)->second, new map<string, basictype *>, new vector<basictype *>, (yysemantic_stack_[(7) - (3)]._bool_expression), (yysemantic_stack_[(7) - (4)].set_string), (yysemantic_stack_[(7) - (5)].vector_protocol_line), (yysemantic_stack_[(7) - (6)].vector_evolution_line));
    (*is_agents)["Environment"] = env;
    agents->push_back(env);
  }
 }
    break;

  case 28:

/* Line 690 of lalr1.cc  */
#line 391 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(6) - (1)].ival)==1 && (yysemantic_stack_[(6) - (2)].map_vec_basictype)!=NULL && (yysemantic_stack_[(6) - (3)].set_string)!=NULL && (yysemantic_stack_[(6) - (4)].vector_protocol_line)!=NULL && (yysemantic_stack_[(6) - (5)].vector_evolution_line)!=NULL && (yysemantic_stack_[(6) - (6)].ival)==1) { // redstates is NULL if no red state at all
    basic_agent *env = new basic_agent((*string_table)[0], NULL, (yysemantic_stack_[(6) - (2)].map_vec_basictype)->first, (yysemantic_stack_[(6) - (2)].map_vec_basictype)->second, new map<string, basictype *>, new vector<basictype *>, NULL, (yysemantic_stack_[(6) - (3)].set_string), (yysemantic_stack_[(6) - (4)].vector_protocol_line), (yysemantic_stack_[(6) - (5)].vector_evolution_line));
    (*is_agents)["Environment"] = env;
    agents->push_back(env);
  }
 }
    break;

  case 29:

/* Line 690 of lalr1.cc  */
#line 398 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(6) - (1)].ival)==1 && (yysemantic_stack_[(6) - (3)].set_string)!=NULL && (yysemantic_stack_[(6) - (4)].vector_protocol_line)!=NULL && (yysemantic_stack_[(6) - (5)].vector_evolution_line)!=NULL && (yysemantic_stack_[(6) - (6)].ival)==1) { // redstates is NULL if no red state at all
    basic_agent *env = new basic_agent((*string_table)[0], NULL, new map<string, basictype *>, new vector<basictype *>, 
				       new map<string, basictype *>, new vector<basictype *>, (yysemantic_stack_[(6) - (2)]._bool_expression), (yysemantic_stack_[(6) - (3)].set_string), (yysemantic_stack_[(6) - (4)].vector_protocol_line), (yysemantic_stack_[(6) - (5)].vector_evolution_line));
    (*is_agents)["Environment"] = env;
    agents->push_back(env);
  }
 }
    break;

  case 30:

/* Line 690 of lalr1.cc  */
#line 406 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(5) - (1)].ival)==1 && (yysemantic_stack_[(5) - (2)].set_string)!=NULL && (yysemantic_stack_[(5) - (3)].vector_protocol_line)!=NULL && (yysemantic_stack_[(5) - (4)].vector_evolution_line)!=NULL && (yysemantic_stack_[(5) - (5)].ival)==1) { // redstates is NULL if no red state at all
    basic_agent *env = new basic_agent((*string_table)[0], NULL, new map<string, basictype *>, new vector<basictype *>, 
				       new map<string, basictype *>, new vector<basictype *>, NULL, (yysemantic_stack_[(5) - (2)].set_string), (yysemantic_stack_[(5) - (3)].vector_protocol_line), (yysemantic_stack_[(5) - (4)].vector_evolution_line));
    (*is_agents)["Environment"] = env;
    agents->push_back(env);
  }
 }
    break;

  case 31:

/* Line 690 of lalr1.cc  */
#line 414 "parser/nssis_new.yy"
    {
  driver.syntax_error = true;
  }
    break;

  case 32:

/* Line 690 of lalr1.cc  */
#line 419 "parser/nssis_new.yy"
    {
  (yyval.ival) = 1;
 }
    break;

  case 33:

/* Line 690 of lalr1.cc  */
#line 422 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 34:

/* Line 690 of lalr1.cc  */
#line 426 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 35:

/* Line 690 of lalr1.cc  */
#line 430 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 36:

/* Line 690 of lalr1.cc  */
#line 434 "parser/nssis_new.yy"
    {
  (yyval.ival) = 1;
 }
    break;

  case 37:

/* Line 690 of lalr1.cc  */
#line 437 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 38:

/* Line 690 of lalr1.cc  */
#line 441 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 39:

/* Line 690 of lalr1.cc  */
#line 445 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 40:

/* Line 690 of lalr1.cc  */
#line 449 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)].ival)==1 && (yysemantic_stack_[(3) - (3)].ival)==1)
    (yyval.map_vec_basictype) = (yysemantic_stack_[(3) - (2)].map_vec_basictype);
  else
    (yyval.map_vec_basictype) = NULL;
 }
    break;

  case 41:

/* Line 690 of lalr1.cc  */
#line 455 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(2) - (1)].ival)==1 && (yysemantic_stack_[(2) - (2)].ival)==1) {
    map<string, basictype *>* a = new map<string, basictype *>;
    vector<basictype *>* b = new vector<basictype *>;
    (yyval.map_vec_basictype) = new pair<map<string, basictype *>*, vector<basictype *>* >(a, b);
  } else
    (yyval.map_vec_basictype) = NULL;
 }
    break;

  case 42:

/* Line 690 of lalr1.cc  */
#line 463 "parser/nssis_new.yy"
    {
  map<string, basictype *>* a = new map<string, basictype *>;
  vector<basictype *>* b = new vector<basictype *>;
  (yyval.map_vec_basictype) = new pair<map<string, basictype *>*, vector<basictype *>* >(a, b);
 }
    break;

  case 43:

/* Line 690 of lalr1.cc  */
#line 468 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)].map_vec_basictype)!=NULL && (yysemantic_stack_[(3) - (2)]._basictype)!=NULL) {
    if((yysemantic_stack_[(3) - (1)].map_vec_basictype)->first->find((yysemantic_stack_[(3) - (2)]._basictype)->get_name()) != (yysemantic_stack_[(3) - (1)].map_vec_basictype)->first->end()) {
			if (options["quiet"] == 0)			
				cout << "warning: type " << (yysemantic_stack_[(3) - (2)]._basictype)->get_name() << " has already been defined." << endl;
    } else { 
      (*((yysemantic_stack_[(3) - (1)].map_vec_basictype)->first))[(yysemantic_stack_[(3) - (2)]._basictype)->get_name()] = (yysemantic_stack_[(3) - (2)]._basictype);
      (yysemantic_stack_[(3) - (1)].map_vec_basictype)->second->push_back((yysemantic_stack_[(3) - (2)]._basictype));
      (yyval.map_vec_basictype) = (yysemantic_stack_[(3) - (1)].map_vec_basictype);
    }
  } else
    (yyval.map_vec_basictype) = NULL;
 }
    break;

  case 44:

/* Line 690 of lalr1.cc  */
#line 481 "parser/nssis_new.yy"
    {
  (yyval.map_vec_basictype) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (1)].map_vec_basictype));
  USE((yysemantic_stack_[(3) - (2)]._basictype));
 }
    break;

  case 45:

/* Line 690 of lalr1.cc  */
#line 487 "parser/nssis_new.yy"
    {
  (yyval.map_vec_basictype) = NULL;
  driver.syntax_error = true;
  }
    break;

  case 46:

/* Line 690 of lalr1.cc  */
#line 492 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)].sval)!=NULL) {
    int i = search_string_table((yysemantic_stack_[(3) - (1)].sval));
    if(i>=0) {
      (yyval._basictype) = new basictype((*string_table)[i]);
      free((yysemantic_stack_[(3) - (1)].sval));
    } else {
      (yyval._basictype) = new basictype((yysemantic_stack_[(3) - (1)].sval));
      string_table->push_back((yysemantic_stack_[(3) - (1)].sval));
    }
  } else
    (yyval._basictype) = NULL;
 }
    break;

  case 47:

/* Line 690 of lalr1.cc  */
#line 505 "parser/nssis_new.yy"
    {
  (yyval._basictype) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (1)].sval));
 }
    break;

  case 48:

/* Line 690 of lalr1.cc  */
#line 510 "parser/nssis_new.yy"
    {
  (yyval._basictype) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (1)].sval));
 }
    break;

  case 49:

/* Line 690 of lalr1.cc  */
#line 515 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(5) - (1)].sval)!=NULL) {
    if((yysemantic_stack_[(5) - (3)].ival)>(yysemantic_stack_[(5) - (5)].ival))
      cout << "Error: the lower bound " << (yysemantic_stack_[(5) - (3)].ival) << " is greater than the upper bound " << (yysemantic_stack_[(5) - (5)].ival) << endl;
    int i = search_string_table((yysemantic_stack_[(5) - (1)].sval));
    if(i>=0) {
      (yyval._basictype) = new rangedint((*string_table)[i], (yysemantic_stack_[(5) - (3)].ival), (yysemantic_stack_[(5) - (5)].ival));
      free((yysemantic_stack_[(5) - (1)].sval));
    } else {
      (yyval._basictype) = new rangedint((yysemantic_stack_[(5) - (1)].sval), (yysemantic_stack_[(5) - (3)].ival), (yysemantic_stack_[(5) - (5)].ival));
      string_table->push_back((yysemantic_stack_[(5) - (1)].sval));
    }
  }
  else
    (yyval._basictype) = NULL;
 }
    break;

  case 50:

/* Line 690 of lalr1.cc  */
#line 531 "parser/nssis_new.yy"
    {
  (yyval._basictype) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (1)].sval));
 }
    break;

  case 51:

/* Line 690 of lalr1.cc  */
#line 536 "parser/nssis_new.yy"
    {
  (yyval._basictype) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (1)].sval));
 }
    break;

  case 52:

/* Line 690 of lalr1.cc  */
#line 541 "parser/nssis_new.yy"
    {
  (yyval._basictype) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (1)].sval));
 }
    break;

  case 53:

/* Line 690 of lalr1.cc  */
#line 546 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(5) - (1)].sval)!=NULL && (yysemantic_stack_[(5) - (4)].set_string)!=NULL) {
    int i = search_string_table((yysemantic_stack_[(5) - (1)].sval));
    if(i>=0) {
      (yyval._basictype) = new enumerate((*string_table)[i], (yysemantic_stack_[(5) - (4)].set_string));
      free((yysemantic_stack_[(5) - (1)].sval));
    } else {
      (yyval._basictype) = new enumerate((yysemantic_stack_[(5) - (1)].sval), (yysemantic_stack_[(5) - (4)].set_string));
      string_table->push_back((yysemantic_stack_[(5) - (1)].sval));
    }
  } else
    (yyval._basictype) = NULL;
 }
    break;

  case 54:

/* Line 690 of lalr1.cc  */
#line 559 "parser/nssis_new.yy"
    {
  (yyval._basictype) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(4) - (1)].sval));
  USE((yysemantic_stack_[(4) - (3)].set_string));
 }
    break;

  case 55:

/* Line 690 of lalr1.cc  */
#line 565 "parser/nssis_new.yy"
    {
  (yyval._basictype) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (1)].sval));
  USE((yysemantic_stack_[(5) - (4)].set_string));
 }
    break;

  case 56:

/* Line 690 of lalr1.cc  */
#line 571 "parser/nssis_new.yy"
    {
  (yyval._basictype) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(4) - (1)].sval));
  USE((yysemantic_stack_[(4) - (3)].set_string));
 }
    break;

  case 57:

/* Line 690 of lalr1.cc  */
#line 577 "parser/nssis_new.yy"
    {
  (yyval._basictype) = NULL;
  driver.syntax_error = true;
 }
    break;

  case 58:

/* Line 690 of lalr1.cc  */
#line 581 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(1) - (1)].sval)!=NULL) {
    (yyval.set_string) = new set<string>;
    (yyval.set_string)->insert(*(yysemantic_stack_[(1) - (1)].sval));
    free ((yysemantic_stack_[(1) - (1)].sval));
  } else
    (yyval.set_string) = NULL;
 }
    break;

  case 59:

/* Line 690 of lalr1.cc  */
#line 589 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)].set_string)!=NULL && (yysemantic_stack_[(3) - (3)].sval)!=NULL) {
    pair<set<string>::iterator, bool> ret = (yysemantic_stack_[(3) - (1)].set_string)->insert(*(yysemantic_stack_[(3) - (3)].sval));
    if(!ret.second && options["quiet"] == 0)
      cout << "warning: " << *(yysemantic_stack_[(3) - (3)].sval) << " has been defined for the enum type." << endl;
    (yyval.set_string) = (yysemantic_stack_[(3) - (1)].set_string);
    free ((yysemantic_stack_[(3) - (3)].sval));
  } else
    (yyval.set_string) = NULL;
	USE((yysemantic_stack_[(3) - (1)].set_string));
 }
    break;

  case 60:

/* Line 690 of lalr1.cc  */
#line 600 "parser/nssis_new.yy"
    {
  (yyval.set_string) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (1)].set_string));
  USE((yysemantic_stack_[(3) - (3)].sval));
 }
    break;

  case 61:

/* Line 690 of lalr1.cc  */
#line 606 "parser/nssis_new.yy"
    {
  (yyval.set_string) = NULL;
  driver.syntax_error = true;
  }
    break;

  case 62:

/* Line 690 of lalr1.cc  */
#line 610 "parser/nssis_new.yy"
    {
  (yyval.ival) = (yysemantic_stack_[(1) - (1)].ival);
 }
    break;

  case 63:

/* Line 690 of lalr1.cc  */
#line 613 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0-(yysemantic_stack_[(2) - (2)].ival);
 }
    break;

  case 64:

/* Line 690 of lalr1.cc  */
#line 616 "parser/nssis_new.yy"
    {
  (yyval.ival) = -1;
  driver.syntax_error = true;
 }
    break;

  case 65:

/* Line 690 of lalr1.cc  */
#line 620 "parser/nssis_new.yy"
    {
  (yyval.ival) = -1;
  driver.syntax_error = true;
  }
    break;

  case 66:

/* Line 690 of lalr1.cc  */
#line 626 "parser/nssis_new.yy"
    {
  (yyval.ival) = 1;
 }
    break;

  case 67:

/* Line 690 of lalr1.cc  */
#line 629 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 68:

/* Line 690 of lalr1.cc  */
#line 633 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 69:

/* Line 690 of lalr1.cc  */
#line 637 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 70:

/* Line 690 of lalr1.cc  */
#line 641 "parser/nssis_new.yy"
    {
  (yyval.ival) = 1;
 }
    break;

  case 71:

/* Line 690 of lalr1.cc  */
#line 644 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 72:

/* Line 690 of lalr1.cc  */
#line 648 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 73:

/* Line 690 of lalr1.cc  */
#line 652 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 74:

/* Line 690 of lalr1.cc  */
#line 656 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)].ival)==1 && (yysemantic_stack_[(3) - (3)].ival)==1)
    (yyval.map_vec_basictype) = (yysemantic_stack_[(3) - (2)].map_vec_basictype);
  else
    (yyval.map_vec_basictype) = NULL;
 }
    break;

  case 75:

/* Line 690 of lalr1.cc  */
#line 662 "parser/nssis_new.yy"
    {
  (yyval.map_vec_basictype) = NULL;
  driver.syntax_error = true;
  }
    break;

  case 76:

/* Line 690 of lalr1.cc  */
#line 668 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)].ival)==1 && (yysemantic_stack_[(3) - (3)].ival)==1)
    (yyval.map_vec_basictype) = (yysemantic_stack_[(3) - (2)].map_vec_basictype);
  else
    (yyval.map_vec_basictype) = NULL;
 }
    break;

  case 77:

/* Line 690 of lalr1.cc  */
#line 674 "parser/nssis_new.yy"
    {
  (yyval.map_vec_basictype) = NULL;
  driver.syntax_error = true;
  }
    break;

  case 78:

/* Line 690 of lalr1.cc  */
#line 680 "parser/nssis_new.yy"
    {
  (yyval.ival) = 1;
 }
    break;

  case 79:

/* Line 690 of lalr1.cc  */
#line 683 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 80:

/* Line 690 of lalr1.cc  */
#line 687 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 81:

/* Line 690 of lalr1.cc  */
#line 691 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 82:

/* Line 690 of lalr1.cc  */
#line 695 "parser/nssis_new.yy"
    {
  (yyval.ival) = 1;
 }
    break;

  case 83:

/* Line 690 of lalr1.cc  */
#line 698 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 84:

/* Line 690 of lalr1.cc  */
#line 702 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 85:

/* Line 690 of lalr1.cc  */
#line 706 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 86:

/* Line 690 of lalr1.cc  */
#line 711 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)].ival)==1 && (yysemantic_stack_[(3) - (3)].ival)==1)
    (yyval._bool_expression) = (yysemantic_stack_[(3) - (2)]._bool_expression);
  else
    (yyval._bool_expression) = NULL;
 }
    break;

  case 87:

/* Line 690 of lalr1.cc  */
#line 717 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL; 
 }
    break;

  case 88:

/* Line 690 of lalr1.cc  */
#line 720 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  }
    break;

  case 89:

/* Line 690 of lalr1.cc  */
#line 725 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)].ival)==1 && (yysemantic_stack_[(3) - (3)].ival)==1)
    (yyval._bool_expression) = (yysemantic_stack_[(3) - (2)]._bool_expression);
  else
    (yyval._bool_expression) = NULL;
 }
    break;

  case 90:

/* Line 690 of lalr1.cc  */
#line 731 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL; 
 }
    break;

  case 91:

/* Line 690 of lalr1.cc  */
#line 734 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  }
    break;

  case 92:

/* Line 690 of lalr1.cc  */
#line 739 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = (yysemantic_stack_[(2) - (1)]._bool_expression);
  }
    break;

  case 93:

/* Line 690 of lalr1.cc  */
#line 742 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(2) - (1)]._bool_expression));
  }
    break;

  case 94:

/* Line 690 of lalr1.cc  */
#line 747 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  }
    break;

  case 95:

/* Line 690 of lalr1.cc  */
#line 752 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = (yysemantic_stack_[(2) - (1)]._bool_expression);
  }
    break;

  case 96:

/* Line 690 of lalr1.cc  */
#line 755 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(2) - (1)]._bool_expression));
  }
    break;

  case 97:

/* Line 690 of lalr1.cc  */
#line 760 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  }
    break;

  case 98:

/* Line 690 of lalr1.cc  */
#line 767 "parser/nssis_new.yy"
    {
  (yyval.ival) = 1;
 }
    break;

  case 99:

/* Line 690 of lalr1.cc  */
#line 770 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 100:

/* Line 690 of lalr1.cc  */
#line 774 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 101:

/* Line 690 of lalr1.cc  */
#line 778 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 102:

/* Line 690 of lalr1.cc  */
#line 782 "parser/nssis_new.yy"
    {
  (yyval.ival) = 1;
 }
    break;

  case 103:

/* Line 690 of lalr1.cc  */
#line 785 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 104:

/* Line 690 of lalr1.cc  */
#line 789 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 105:

/* Line 690 of lalr1.cc  */
#line 793 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 106:

/* Line 690 of lalr1.cc  */
#line 797 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)].ival)==1 && (yysemantic_stack_[(3) - (3)].ival)==1)
    (yyval.vector_evolution_line) = (yysemantic_stack_[(3) - (2)].vector_evolution_line);
  else
    (yyval.vector_evolution_line) = NULL;
 }
    break;

  case 107:

/* Line 690 of lalr1.cc  */
#line 803 "parser/nssis_new.yy"
    {
  (yyval.vector_evolution_line) = new vector<evolution_line *>;
 }
    break;

  case 108:

/* Line 690 of lalr1.cc  */
#line 806 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(2) - (1)].vector_evolution_line)!=NULL && (yysemantic_stack_[(2) - (2)]._evolution_line)!=NULL) {
    (yysemantic_stack_[(2) - (1)].vector_evolution_line)->push_back((yysemantic_stack_[(2) - (2)]._evolution_line));
    (yyval.vector_evolution_line) = (yysemantic_stack_[(2) - (1)].vector_evolution_line);
  } else
    (yyval.vector_evolution_line) = NULL;
 }
    break;

  case 109:

/* Line 690 of lalr1.cc  */
#line 813 "parser/nssis_new.yy"
    {
  (yyval.vector_evolution_line) = NULL;
  driver.syntax_error = true;
  }
    break;

  case 110:

/* Line 690 of lalr1.cc  */
#line 817 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(4) - (1)].vector_assignment)!=NULL && (yysemantic_stack_[(4) - (3)]._bool_expression)!=NULL) 
    (yyval._evolution_line) = new evolution_line((yysemantic_stack_[(4) - (1)].vector_assignment), (yysemantic_stack_[(4) - (3)]._bool_expression));
  else
    (yyval._evolution_line) = NULL;
 }
    break;

  case 111:

/* Line 690 of lalr1.cc  */
#line 823 "parser/nssis_new.yy"
    {
  (yyval._evolution_line) = NULL;
  driver.syntax_error = true;
  }
    break;

  case 112:

/* Line 690 of lalr1.cc  */
#line 827 "parser/nssis_new.yy"
    {
  (yyval.vector_assignment) = (yysemantic_stack_[(3) - (2)].vector_assignment);
 }
    break;

  case 113:

/* Line 690 of lalr1.cc  */
#line 830 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)].vector_assignment)!=NULL && (yysemantic_stack_[(3) - (3)].vector_assignment)!=NULL) {
    (yyval.vector_assignment) = (yysemantic_stack_[(3) - (1)].vector_assignment);
    vector<assignment*>::iterator i;
    for(i=(yysemantic_stack_[(3) - (3)].vector_assignment)->begin(); i != (yysemantic_stack_[(3) - (3)].vector_assignment)->end(); i++)
      (yyval.vector_assignment)->push_back(*i);
  } else
    (yyval.vector_assignment) = NULL;
 }
    break;

  case 114:

/* Line 690 of lalr1.cc  */
#line 839 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)].sval)!=NULL && (yysemantic_stack_[(3) - (3)]._expression)!=NULL) {
    assignment *a;
    int i = search_string_table((yysemantic_stack_[(3) - (1)].sval));
    if(i>=0) {
      a = new assignment((*string_table)[i], (yysemantic_stack_[(3) - (3)]._expression));
      free((yysemantic_stack_[(3) - (1)].sval));
    } else {
      a = new assignment((yysemantic_stack_[(3) - (1)].sval), (yysemantic_stack_[(3) - (3)]._expression));
      string_table->push_back((yysemantic_stack_[(3) - (1)].sval));
    }
    (yyval.vector_assignment) = new vector<assignment*>;
    (yyval.vector_assignment)->push_back(a);
  } else
    (yyval.vector_assignment) = NULL;
 }
    break;

  case 115:

/* Line 690 of lalr1.cc  */
#line 855 "parser/nssis_new.yy"
    {
  (yyval.vector_assignment) = NULL;
  driver.syntax_error = true;
  }
    break;

  case 116:

/* Line 690 of lalr1.cc  */
#line 860 "parser/nssis_new.yy"
    {
  (yyval.vector_assignment) = (yysemantic_stack_[(3) - (2)].vector_assignment);
 }
    break;

  case 117:

/* Line 690 of lalr1.cc  */
#line 863 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)].vector_assignment)!=NULL && (yysemantic_stack_[(3) - (3)].vector_assignment)!=NULL) {
    (yyval.vector_assignment) = (yysemantic_stack_[(3) - (1)].vector_assignment);
    vector<assignment*>::iterator i;
    for(i=(yysemantic_stack_[(3) - (3)].vector_assignment)->begin(); i != (yysemantic_stack_[(3) - (3)].vector_assignment)->end(); i++)
      (yyval.vector_assignment)->push_back(*i);
  } else
    (yyval.vector_assignment) = NULL;
 }
    break;

  case 118:

/* Line 690 of lalr1.cc  */
#line 872 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)].sval)!=NULL && (yysemantic_stack_[(3) - (3)]._expression)!=NULL) {
    assignment *a;
    int i = search_string_table((yysemantic_stack_[(3) - (1)].sval));
    if(i>=0) {
      a = new assignment((*string_table)[i], (yysemantic_stack_[(3) - (3)]._expression));
      free((yysemantic_stack_[(3) - (1)].sval));
    } else {
      a = new assignment((yysemantic_stack_[(3) - (1)].sval), (yysemantic_stack_[(3) - (3)]._expression));
      string_table->push_back((yysemantic_stack_[(3) - (1)].sval));
    }
    (yyval.vector_assignment) = new vector<assignment*>;
    (yyval.vector_assignment)->push_back(a);
  } else
    (yyval.vector_assignment) = NULL;
 }
    break;

  case 119:

/* Line 690 of lalr1.cc  */
#line 888 "parser/nssis_new.yy"
    {
  (yyval.vector_assignment) = NULL;
  driver.syntax_error = true;
  }
    break;

  case 120:

/* Line 690 of lalr1.cc  */
#line 893 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(1) - (1)]._basic_agent)!=NULL) {
    (*is_agents)[(yysemantic_stack_[(1) - (1)]._basic_agent)->get_name()] = (yysemantic_stack_[(1) - (1)]._basic_agent);
    agents->push_back((yysemantic_stack_[(1) - (1)]._basic_agent));
  } 
 }
    break;

  case 121:

/* Line 690 of lalr1.cc  */
#line 899 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(2) - (2)]._basic_agent)!=NULL) {
    if(is_agents->find((yysemantic_stack_[(2) - (2)]._basic_agent)->get_name()) != is_agents->end()) {
			if (options["quiet"] == 0)
				cout << "warning: agent " << (yysemantic_stack_[(2) - (2)]._basic_agent)->get_name() << " already exists." << endl;
    } else
      agents->push_back((yysemantic_stack_[(2) - (2)]._basic_agent));
    (*is_agents)[(yysemantic_stack_[(2) - (2)]._basic_agent)->get_name()] = (yysemantic_stack_[(2) - (2)]._basic_agent);
  }
 }
    break;

  case 122:

/* Line 690 of lalr1.cc  */
#line 909 "parser/nssis_new.yy"
    {
  driver.syntax_error = true;
  }
    break;

  case 123:

/* Line 690 of lalr1.cc  */
#line 913 "parser/nssis_new.yy"
    {
  (yyval.ival) = 1;
 }
    break;

  case 124:

/* Line 690 of lalr1.cc  */
#line 916 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 125:

/* Line 690 of lalr1.cc  */
#line 920 "parser/nssis_new.yy"
    {
  (yyval.ival) = 1;
 }
    break;

  case 126:

/* Line 690 of lalr1.cc  */
#line 923 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 127:

/* Line 690 of lalr1.cc  */
#line 927 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 128:

/* Line 690 of lalr1.cc  */
#line 931 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 129:

/* Line 690 of lalr1.cc  */
#line 936 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(8) - (1)].ival)==1 && (yysemantic_stack_[(8) - (2)].sval)!=NULL && (yysemantic_stack_[(8) - (3)].map_vec_basictype)!=NULL && 
     (yysemantic_stack_[(8) - (5)].set_string)!=NULL && (yysemantic_stack_[(8) - (6)].vector_protocol_line)!=NULL && (yysemantic_stack_[(8) - (7)].vector_evolution_line)!=NULL && (yysemantic_stack_[(8) - (8)].ival)==1) {// redstates is NULL if no red state at all
    int i = search_string_table((yysemantic_stack_[(8) - (2)].sval));
    if(i>=0) {
      (yyval._basic_agent) = new basic_agent((*string_table)[i], NULL, NULL, NULL, (yysemantic_stack_[(8) - (3)].map_vec_basictype)->first, (yysemantic_stack_[(8) - (3)].map_vec_basictype)->second, (yysemantic_stack_[(8) - (4)]._bool_expression), (yysemantic_stack_[(8) - (5)].set_string), (yysemantic_stack_[(8) - (6)].vector_protocol_line), (yysemantic_stack_[(8) - (7)].vector_evolution_line));
      free((yysemantic_stack_[(8) - (2)].sval));
    } else {
      (yyval._basic_agent) = new basic_agent((yysemantic_stack_[(8) - (2)].sval), NULL, NULL, NULL, (yysemantic_stack_[(8) - (3)].map_vec_basictype)->first, (yysemantic_stack_[(8) - (3)].map_vec_basictype)->second, (yysemantic_stack_[(8) - (4)]._bool_expression), (yysemantic_stack_[(8) - (5)].set_string), (yysemantic_stack_[(8) - (6)].vector_protocol_line), (yysemantic_stack_[(8) - (7)].vector_evolution_line));
      string_table->push_back((yysemantic_stack_[(8) - (2)].sval));
    }
  } else
    (yyval._basic_agent) = NULL;
 }
    break;

  case 130:

/* Line 690 of lalr1.cc  */
#line 950 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(7) - (1)].ival)==1 && (yysemantic_stack_[(7) - (2)].sval)!=NULL && (yysemantic_stack_[(7) - (3)].map_vec_basictype)!=NULL && 
     (yysemantic_stack_[(7) - (4)].set_string)!=NULL && (yysemantic_stack_[(7) - (5)].vector_protocol_line)!=NULL && (yysemantic_stack_[(7) - (6)].vector_evolution_line)!=NULL && (yysemantic_stack_[(7) - (7)].ival)==1) {// redstates is NULL if no red state at all
    int i = search_string_table((yysemantic_stack_[(7) - (2)].sval));
    if(i>=0) {
      (yyval._basic_agent) = new basic_agent((*string_table)[i], NULL, NULL, NULL, (yysemantic_stack_[(7) - (3)].map_vec_basictype)->first, (yysemantic_stack_[(7) - (3)].map_vec_basictype)->second, NULL, (yysemantic_stack_[(7) - (4)].set_string), (yysemantic_stack_[(7) - (5)].vector_protocol_line), (yysemantic_stack_[(7) - (6)].vector_evolution_line));
      free((yysemantic_stack_[(7) - (2)].sval));
    } else {
      (yyval._basic_agent) = new basic_agent((yysemantic_stack_[(7) - (2)].sval), NULL, NULL, NULL, (yysemantic_stack_[(7) - (3)].map_vec_basictype)->first, (yysemantic_stack_[(7) - (3)].map_vec_basictype)->second, NULL, (yysemantic_stack_[(7) - (4)].set_string), (yysemantic_stack_[(7) - (5)].vector_protocol_line), (yysemantic_stack_[(7) - (6)].vector_evolution_line));
      string_table->push_back((yysemantic_stack_[(7) - (2)].sval));
    }
  } else
    (yyval._basic_agent) = NULL;
 }
    break;

  case 131:

/* Line 690 of lalr1.cc  */
#line 964 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(9) - (1)].ival)==1 && (yysemantic_stack_[(9) - (2)].sval)!=NULL && (yysemantic_stack_[(9) - (4)].map_vec_basictype)!=NULL && 
     (yysemantic_stack_[(9) - (6)].set_string)!=NULL && (yysemantic_stack_[(9) - (7)].vector_protocol_line)!=NULL && (yysemantic_stack_[(9) - (8)].vector_evolution_line)!=NULL && (yysemantic_stack_[(9) - (9)].ival)==1) {// redstates is NULL if no red state at all
    int i = search_string_table((yysemantic_stack_[(9) - (2)].sval));
    if(i>=0) {
      (yyval._basic_agent) = new basic_agent((*string_table)[i], (yysemantic_stack_[(9) - (3)].map_string_variable), NULL, NULL, (yysemantic_stack_[(9) - (4)].map_vec_basictype)->first, (yysemantic_stack_[(9) - (4)].map_vec_basictype)->second, (yysemantic_stack_[(9) - (5)]._bool_expression), (yysemantic_stack_[(9) - (6)].set_string), (yysemantic_stack_[(9) - (7)].vector_protocol_line), (yysemantic_stack_[(9) - (8)].vector_evolution_line));
      free((yysemantic_stack_[(9) - (2)].sval));
    } else {
      (yyval._basic_agent) = new basic_agent((yysemantic_stack_[(9) - (2)].sval), (yysemantic_stack_[(9) - (3)].map_string_variable), NULL, NULL, (yysemantic_stack_[(9) - (4)].map_vec_basictype)->first, (yysemantic_stack_[(9) - (4)].map_vec_basictype)->second, (yysemantic_stack_[(9) - (5)]._bool_expression), (yysemantic_stack_[(9) - (6)].set_string), (yysemantic_stack_[(9) - (7)].vector_protocol_line), (yysemantic_stack_[(9) - (8)].vector_evolution_line));
      string_table->push_back((yysemantic_stack_[(9) - (2)].sval));
    }
  } else
    (yyval._basic_agent) = NULL;
 }
    break;

  case 132:

/* Line 690 of lalr1.cc  */
#line 978 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(8) - (1)].ival)==1 && (yysemantic_stack_[(8) - (2)].sval)!=NULL && 
     (yysemantic_stack_[(8) - (4)].map_vec_basictype)!=NULL && (yysemantic_stack_[(8) - (5)].set_string)!=NULL && (yysemantic_stack_[(8) - (6)].vector_protocol_line)!=NULL && (yysemantic_stack_[(8) - (7)].vector_evolution_line)!=NULL && (yysemantic_stack_[(8) - (8)].ival)==1) {// redstates is NULL if no red state at all
    int i = search_string_table((yysemantic_stack_[(8) - (2)].sval));
    if(i>=0) {
      (yyval._basic_agent) = new basic_agent((*string_table)[i], (yysemantic_stack_[(8) - (3)].map_string_variable), NULL, NULL, (yysemantic_stack_[(8) - (4)].map_vec_basictype)->first, (yysemantic_stack_[(8) - (4)].map_vec_basictype)->second, NULL, (yysemantic_stack_[(8) - (5)].set_string), (yysemantic_stack_[(8) - (6)].vector_protocol_line), (yysemantic_stack_[(8) - (7)].vector_evolution_line));
      free((yysemantic_stack_[(8) - (2)].sval));
    } else {
      (yyval._basic_agent) = new basic_agent((yysemantic_stack_[(8) - (2)].sval), (yysemantic_stack_[(8) - (3)].map_string_variable), NULL, NULL, (yysemantic_stack_[(8) - (4)].map_vec_basictype)->first, (yysemantic_stack_[(8) - (4)].map_vec_basictype)->second, NULL, (yysemantic_stack_[(8) - (5)].set_string), (yysemantic_stack_[(8) - (6)].vector_protocol_line), (yysemantic_stack_[(8) - (7)].vector_evolution_line));
      string_table->push_back((yysemantic_stack_[(8) - (2)].sval));
    }
  } else
    (yyval._basic_agent) = NULL;
 }
    break;

  case 133:

/* Line 690 of lalr1.cc  */
#line 992 "parser/nssis_new.yy"
    {
  (yyval._basic_agent) = NULL;
  driver.syntax_error = true;
  }
    break;

  case 134:

/* Line 690 of lalr1.cc  */
#line 998 "parser/nssis_new.yy"
    {
  (yyval.ival) = 1;
 }
    break;

  case 135:

/* Line 690 of lalr1.cc  */
#line 1001 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 136:

/* Line 690 of lalr1.cc  */
#line 1005 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 137:

/* Line 690 of lalr1.cc  */
#line 1009 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 138:

/* Line 690 of lalr1.cc  */
#line 1013 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 139:

/* Line 690 of lalr1.cc  */
#line 1017 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 140:

/* Line 690 of lalr1.cc  */
#line 1021 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 141:

/* Line 690 of lalr1.cc  */
#line 1025 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 142:

/* Line 690 of lalr1.cc  */
#line 1029 "parser/nssis_new.yy"
    {
  (yyval.ival) = 1;
 }
    break;

  case 143:

/* Line 690 of lalr1.cc  */
#line 1032 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 144:

/* Line 690 of lalr1.cc  */
#line 1036 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 145:

/* Line 690 of lalr1.cc  */
#line 1040 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 146:

/* Line 690 of lalr1.cc  */
#line 1044 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)].ival)==1 && (yysemantic_stack_[(3) - (3)].ival)==1)
    (yyval.map_string_variable) = (yysemantic_stack_[(3) - (2)].map_string_variable);
  else
    (yyval.map_string_variable) = NULL;
 }
    break;

  case 147:

/* Line 690 of lalr1.cc  */
#line 1050 "parser/nssis_new.yy"
    {
  (yyval.map_string_variable) = NULL;
 }
    break;

  case 148:

/* Line 690 of lalr1.cc  */
#line 1053 "parser/nssis_new.yy"
    {
  (yyval.map_string_variable) = NULL;
  driver.syntax_error = true;
  }
    break;

  case 149:

/* Line 690 of lalr1.cc  */
#line 1057 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(1) - (1)].sval)!=NULL) {
    (yyval.map_string_variable) = new map<string, variable *>;
    if((yyval.map_string_variable)->find(*(yysemantic_stack_[(1) - (1)].sval)) != (yyval.map_string_variable)->end() && options["quiet"] == 0)
      cout << "warning: local observable variable " << *(yysemantic_stack_[(1) - (1)].sval) << " has already been defined." << endl;
    int i = search_string_table((yysemantic_stack_[(1) - (1)].sval));
    if(i>=0) {
      (*(yyval.map_string_variable))[*(yysemantic_stack_[(1) - (1)].sval)] = new variable((*string_table)[0], (*string_table)[i]);
      free((yysemantic_stack_[(1) - (1)].sval));
    } else {
      (*(yyval.map_string_variable))[*(yysemantic_stack_[(1) - (1)].sval)] = new variable((*string_table)[0], (yysemantic_stack_[(1) - (1)].sval));
      string_table->push_back((yysemantic_stack_[(1) - (1)].sval));
    }
  } else
    (yyval.map_string_variable) = NULL;
 }
    break;

  case 150:

/* Line 690 of lalr1.cc  */
#line 1073 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)].map_string_variable)!=NULL && (yysemantic_stack_[(3) - (3)].sval)!=NULL) {
    if((yysemantic_stack_[(3) - (1)].map_string_variable)->find(*(yysemantic_stack_[(3) - (3)].sval)) != (yyval.map_string_variable)->end() && options["quiet"] == 0)
      cout << "warning: local observable variable " << *(yysemantic_stack_[(3) - (3)].sval) << " has already been defined." << endl;
    int i = search_string_table((yysemantic_stack_[(3) - (3)].sval));
    if(i>=0) {
      (*(yysemantic_stack_[(3) - (1)].map_string_variable))[*(yysemantic_stack_[(3) - (3)].sval)] = new variable((*string_table)[0], (*string_table)[i]);
      free((yysemantic_stack_[(3) - (3)].sval));
    } else {
      (*(yysemantic_stack_[(3) - (1)].map_string_variable))[*(yysemantic_stack_[(3) - (3)].sval)] = new variable((*string_table)[0], (yysemantic_stack_[(3) - (3)].sval));
      string_table->push_back((yysemantic_stack_[(3) - (3)].sval));
    }
    (yyval.map_string_variable) = (yysemantic_stack_[(3) - (1)].map_string_variable);
  } else
    (yyval.map_string_variable) = NULL;
 }
    break;

  case 151:

/* Line 690 of lalr1.cc  */
#line 1089 "parser/nssis_new.yy"
    {
  (yyval.map_string_variable) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (1)].map_string_variable));
  USE((yysemantic_stack_[(3) - (3)].sval));
 }
    break;

  case 152:

/* Line 690 of lalr1.cc  */
#line 1095 "parser/nssis_new.yy"
    {
  (yyval.map_string_variable) = NULL;
  driver.syntax_error = true;
  }
    break;

  case 153:

/* Line 690 of lalr1.cc  */
#line 1102 "parser/nssis_new.yy"
    {
  (yyval.ival) = 1;
 }
    break;

  case 154:

/* Line 690 of lalr1.cc  */
#line 1105 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 155:

/* Line 690 of lalr1.cc  */
#line 1109 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 156:

/* Line 690 of lalr1.cc  */
#line 1113 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 157:

/* Line 690 of lalr1.cc  */
#line 1117 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 158:

/* Line 690 of lalr1.cc  */
#line 1121 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 159:

/* Line 690 of lalr1.cc  */
#line 1125 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 160:

/* Line 690 of lalr1.cc  */
#line 1129 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 161:

/* Line 690 of lalr1.cc  */
#line 1133 "parser/nssis_new.yy"
    {
  (yyval.ival) = 1;
 }
    break;

  case 162:

/* Line 690 of lalr1.cc  */
#line 1136 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 163:

/* Line 690 of lalr1.cc  */
#line 1140 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 164:

/* Line 690 of lalr1.cc  */
#line 1144 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 165:

/* Line 690 of lalr1.cc  */
#line 1148 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)].ival)==1 && (yysemantic_stack_[(3) - (3)].ival)==1)
    (yyval.set_string) = (yysemantic_stack_[(3) - (2)].set_string);
  else
    (yyval.set_string) = NULL;
 }
    break;

  case 166:

/* Line 690 of lalr1.cc  */
#line 1154 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(2) - (1)].ival)==1 && (yysemantic_stack_[(2) - (2)].ival)==1)
    (yyval.set_string) = new set<string>;
  else
    (yyval.set_string) = NULL;
 }
    break;

  case 167:

/* Line 690 of lalr1.cc  */
#line 1160 "parser/nssis_new.yy"
    {
  (yyval.set_string) = NULL;
  driver.syntax_error = true;
  }
    break;

  case 168:

/* Line 690 of lalr1.cc  */
#line 1166 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)].ival)==1 && (yysemantic_stack_[(3) - (3)].ival)==1) 
    (yyval.set_string) = (yysemantic_stack_[(3) - (2)].set_string);
  else
    (yyval.set_string) = NULL;
 }
    break;

  case 169:

/* Line 690 of lalr1.cc  */
#line 1172 "parser/nssis_new.yy"
    {
  (yyval.set_string) = NULL;
  driver.syntax_error = true;
  }
    break;

  case 170:

/* Line 690 of lalr1.cc  */
#line 1176 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(1) - (1)].sval)!=NULL) {
    (yyval.set_string) = new set<string>;
    (yyval.set_string)->insert(*(yysemantic_stack_[(1) - (1)].sval));
    free ((yysemantic_stack_[(1) - (1)].sval));
  } else
    (yyval.set_string) = NULL;
 }
    break;

  case 171:

/* Line 690 of lalr1.cc  */
#line 1184 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)].set_string)!=NULL && (yysemantic_stack_[(3) - (3)].sval)!=NULL) {
    pair<set<string>::iterator, bool> ret = (yysemantic_stack_[(3) - (1)].set_string)->insert(*(yysemantic_stack_[(3) - (3)].sval));
    if(!ret.second && options["quiet"] == 0)
      cout << "warning: action " << *(yysemantic_stack_[(3) - (3)].sval) << " has been defined." << endl;
    (yyval.set_string) = (yysemantic_stack_[(3) - (1)].set_string);
    free ((yysemantic_stack_[(3) - (3)].sval));
  } else
    (yyval.set_string) = NULL;
 }
    break;

  case 172:

/* Line 690 of lalr1.cc  */
#line 1194 "parser/nssis_new.yy"
    {
  (yyval.set_string) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (1)].set_string));
  USE((yysemantic_stack_[(3) - (3)].sval));
 }
    break;

  case 173:

/* Line 690 of lalr1.cc  */
#line 1200 "parser/nssis_new.yy"
    {
  (yyval.set_string) = NULL;
  driver.syntax_error = true;
  }
    break;

  case 174:

/* Line 690 of lalr1.cc  */
#line 1207 "parser/nssis_new.yy"
    {
  (yyval.ival) = 1;
 }
    break;

  case 175:

/* Line 690 of lalr1.cc  */
#line 1210 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 176:

/* Line 690 of lalr1.cc  */
#line 1214 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 177:

/* Line 690 of lalr1.cc  */
#line 1218 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 178:

/* Line 690 of lalr1.cc  */
#line 1222 "parser/nssis_new.yy"
    {
  (yyval.ival) = 1;
 }
    break;

  case 179:

/* Line 690 of lalr1.cc  */
#line 1225 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 180:

/* Line 690 of lalr1.cc  */
#line 1229 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 181:

/* Line 690 of lalr1.cc  */
#line 1233 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 182:

/* Line 690 of lalr1.cc  */
#line 1238 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)].ival)==1 && (yysemantic_stack_[(3) - (3)].ival)==1) 
    (yyval.vector_protocol_line) = (yysemantic_stack_[(3) - (2)].vector_protocol_line);
  else
    (yyval.vector_protocol_line) = NULL;
 }
    break;

  case 183:

/* Line 690 of lalr1.cc  */
#line 1244 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(4) - (1)].ival)==1 && (yysemantic_stack_[(4) - (4)].ival)==1) {
    (yyval.vector_protocol_line) = (yysemantic_stack_[(4) - (2)].vector_protocol_line);
    (yyval.vector_protocol_line)->push_back((yysemantic_stack_[(4) - (3)]._protocol_line));
  }
  else
    (yyval.vector_protocol_line) = NULL;
 }
    break;

  case 184:

/* Line 690 of lalr1.cc  */
#line 1252 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)].ival)==1 && (yysemantic_stack_[(3) - (3)].ival)==1) {
    (yyval.vector_protocol_line) = new vector<protocol_line*>;
    (yyval.vector_protocol_line)->push_back((yysemantic_stack_[(3) - (2)]._protocol_line));;
  }
  else
    (yyval.vector_protocol_line) = NULL;
 }
    break;

  case 185:

/* Line 690 of lalr1.cc  */
#line 1260 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(2) - (1)].ival)==1 && (yysemantic_stack_[(2) - (2)].ival)==1) 
    (yyval.vector_protocol_line) = new vector<protocol_line*>;
  else
    (yyval.vector_protocol_line) = NULL;
 }
    break;

  case 186:

/* Line 690 of lalr1.cc  */
#line 1266 "parser/nssis_new.yy"
    {
  (yyval.vector_protocol_line) = NULL;
  driver.syntax_error = true;
  }
    break;

  case 187:

/* Line 690 of lalr1.cc  */
#line 1272 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)].ival)==1 && (yysemantic_stack_[(3) - (3)].ival)==1) 
    (yyval.vector_protocol_line) = (yysemantic_stack_[(3) - (2)].vector_protocol_line);
  else
    (yyval.vector_protocol_line) = NULL;
 }
    break;

  case 188:

/* Line 690 of lalr1.cc  */
#line 1278 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(4) - (1)].ival)==1 && (yysemantic_stack_[(4) - (4)].ival)==1) {
    (yyval.vector_protocol_line) = (yysemantic_stack_[(4) - (2)].vector_protocol_line);
    (yyval.vector_protocol_line)->push_back((yysemantic_stack_[(4) - (3)]._protocol_line));
  }
  else
    (yyval.vector_protocol_line) = NULL;
 }
    break;

  case 189:

/* Line 690 of lalr1.cc  */
#line 1286 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)].ival)==1 && (yysemantic_stack_[(3) - (3)].ival)==1) {
    (yyval.vector_protocol_line) = new vector<protocol_line*>;
    (yyval.vector_protocol_line)->push_back((yysemantic_stack_[(3) - (2)]._protocol_line));;
  }
  else
    (yyval.vector_protocol_line) = NULL;
 }
    break;

  case 190:

/* Line 690 of lalr1.cc  */
#line 1294 "parser/nssis_new.yy"
    {
  (yyval.vector_protocol_line) = NULL;
  driver.syntax_error = true;
  }
    break;

  case 191:

/* Line 690 of lalr1.cc  */
#line 1299 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(1) - (1)]._protocol_line)!=NULL) {
    (yyval.vector_protocol_line) = new vector<protocol_line*>;
    (yyval.vector_protocol_line)->push_back((yysemantic_stack_[(1) - (1)]._protocol_line));
  } else
    (yyval.vector_protocol_line) = NULL;
 }
    break;

  case 192:

/* Line 690 of lalr1.cc  */
#line 1306 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(2) - (1)].vector_protocol_line)!=NULL && (yysemantic_stack_[(2) - (2)]._protocol_line)!=NULL) {
    (yysemantic_stack_[(2) - (1)].vector_protocol_line)->push_back((yysemantic_stack_[(2) - (2)]._protocol_line));
    (yyval.vector_protocol_line) = (yysemantic_stack_[(2) - (1)].vector_protocol_line);
  } else
    (yyval.vector_protocol_line) = NULL;
 }
    break;

  case 193:

/* Line 690 of lalr1.cc  */
#line 1313 "parser/nssis_new.yy"
    {
  (yyval.vector_protocol_line) = NULL;
  driver.syntax_error = true;
  }
    break;

  case 194:

/* Line 690 of lalr1.cc  */
#line 1318 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(1) - (1)]._protocol_line)!=NULL) {
    (yyval.vector_protocol_line) = new vector<protocol_line*>;
    (yyval.vector_protocol_line)->push_back((yysemantic_stack_[(1) - (1)]._protocol_line));
  } else
    (yyval.vector_protocol_line) = NULL;
 }
    break;

  case 195:

/* Line 690 of lalr1.cc  */
#line 1325 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(2) - (1)].vector_protocol_line)!=NULL && (yysemantic_stack_[(2) - (2)]._protocol_line)!=NULL) {
    (yysemantic_stack_[(2) - (1)].vector_protocol_line)->push_back((yysemantic_stack_[(2) - (2)]._protocol_line));
    (yyval.vector_protocol_line) = (yysemantic_stack_[(2) - (1)].vector_protocol_line);
  } else
    (yyval.vector_protocol_line) = NULL;
 }
    break;

  case 196:

/* Line 690 of lalr1.cc  */
#line 1332 "parser/nssis_new.yy"
    {
  (yyval.vector_protocol_line) = NULL;
  driver.syntax_error = true;
  }
    break;

  case 197:

/* Line 690 of lalr1.cc  */
#line 1337 "parser/nssis_new.yy"
    {
  (yyval.ival) = 1;
 }
    break;

  case 198:

/* Line 690 of lalr1.cc  */
#line 1340 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 199:

/* Line 690 of lalr1.cc  */
#line 1344 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 200:

/* Line 690 of lalr1.cc  */
#line 1348 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 201:

/* Line 690 of lalr1.cc  */
#line 1352 "parser/nssis_new.yy"
    {
  (yyval.ival) = 1;
 }
    break;

  case 202:

/* Line 690 of lalr1.cc  */
#line 1355 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 203:

/* Line 690 of lalr1.cc  */
#line 1359 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 204:

/* Line 690 of lalr1.cc  */
#line 1363 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 205:

/* Line 690 of lalr1.cc  */
#line 1367 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(4) - (1)]._bool_expression)!=NULL && (yysemantic_stack_[(4) - (2)].ival)==1 && (yysemantic_stack_[(4) - (3)].set_string)!=NULL && (yysemantic_stack_[(4) - (4)].ival)==1) 
    (yyval._protocol_line) = new protocol_line((yysemantic_stack_[(4) - (1)]._bool_expression), (yysemantic_stack_[(4) - (3)].set_string));
  else
    (yyval._protocol_line) = NULL;
 }
    break;

  case 206:

/* Line 690 of lalr1.cc  */
#line 1373 "parser/nssis_new.yy"
    {
  (yyval._protocol_line) = NULL;
  driver.syntax_error = true;
  }
    break;

  case 207:

/* Line 690 of lalr1.cc  */
#line 1378 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(4) - (1)]._bool_expression)!=NULL && (yysemantic_stack_[(4) - (2)].ival)==1 && (yysemantic_stack_[(4) - (3)].set_string)!=NULL && (yysemantic_stack_[(4) - (4)].ival)==1) 
    (yyval._protocol_line) = new protocol_line((yysemantic_stack_[(4) - (1)]._bool_expression), (yysemantic_stack_[(4) - (3)].set_string));
  else
    (yyval._protocol_line) = NULL;
 }
    break;

  case 208:

/* Line 690 of lalr1.cc  */
#line 1384 "parser/nssis_new.yy"
    {
  (yyval._protocol_line) = NULL;
  driver.syntax_error = true;
  }
    break;

  case 209:

/* Line 690 of lalr1.cc  */
#line 1389 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(4) - (2)].ival)==1 && (yysemantic_stack_[(4) - (3)].set_string)!=NULL && (yysemantic_stack_[(4) - (4)].ival)==1) 
    (yyval._protocol_line) = new protocol_line(new bool_expression(), (yysemantic_stack_[(4) - (3)].set_string));
  else
    (yyval._protocol_line) = NULL;
 }
    break;

  case 210:

/* Line 690 of lalr1.cc  */
#line 1395 "parser/nssis_new.yy"
    {
  (yyval._protocol_line) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(4) - (3)].set_string));
 }
    break;

  case 211:

/* Line 690 of lalr1.cc  */
#line 1401 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(1) - (1)].sval)!=NULL) {
    (yyval.set_string) = new set<string>;
    (yyval.set_string)->insert(*(yysemantic_stack_[(1) - (1)].sval));
    free ((yysemantic_stack_[(1) - (1)].sval));
  } else
    (yyval.set_string) = NULL;
 }
    break;

  case 212:

/* Line 690 of lalr1.cc  */
#line 1409 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)].set_string)!=NULL && (yysemantic_stack_[(3) - (3)].sval)!=NULL) {
    pair<set<string>::iterator, bool> ret = (yysemantic_stack_[(3) - (1)].set_string)->insert(*(yysemantic_stack_[(3) - (3)].sval));
    if(!ret.second && options["quiet"] == 0)
      cout << "warning: action " << *(yysemantic_stack_[(3) - (3)].sval) << " is repeated." << endl;
    (yyval.set_string) = (yysemantic_stack_[(3) - (1)].set_string);
    free ((yysemantic_stack_[(3) - (3)].sval));
  } else
    (yyval.set_string) = NULL;
 }
    break;

  case 213:

/* Line 690 of lalr1.cc  */
#line 1419 "parser/nssis_new.yy"
    {
  (yyval.set_string) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (1)].set_string));
  USE((yysemantic_stack_[(3) - (3)].sval));
 }
    break;

  case 214:

/* Line 690 of lalr1.cc  */
#line 1425 "parser/nssis_new.yy"
    {
  (yyval.set_string) = NULL;
  driver.syntax_error = true;
  }
    break;

  case 215:

/* Line 690 of lalr1.cc  */
#line 1432 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)].ival)==1 && (yysemantic_stack_[(3) - (3)].ival)==1)
    (yyval.vector_evolution_line) = (yysemantic_stack_[(3) - (2)].vector_evolution_line);
  else
    (yyval.vector_evolution_line) = NULL;
}
    break;

  case 216:

/* Line 690 of lalr1.cc  */
#line 1438 "parser/nssis_new.yy"
    {
  (yyval.vector_evolution_line) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (2)].vector_evolution_line));
  }
    break;

  case 217:

/* Line 690 of lalr1.cc  */
#line 1444 "parser/nssis_new.yy"
    {
  (yyval.vector_evolution_line) = new vector<evolution_line*>;
 }
    break;

  case 218:

/* Line 690 of lalr1.cc  */
#line 1447 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(2) - (1)].vector_evolution_line)!=NULL && (yysemantic_stack_[(2) - (2)]._evolution_line)!=NULL) {
    (yysemantic_stack_[(2) - (1)].vector_evolution_line)->push_back((yysemantic_stack_[(2) - (2)]._evolution_line));
    (yyval.vector_evolution_line) = (yysemantic_stack_[(2) - (1)].vector_evolution_line);
  } else
    (yyval.vector_evolution_line) = NULL;
 }
    break;

  case 219:

/* Line 690 of lalr1.cc  */
#line 1455 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(4) - (1)].vector_assignment)!=NULL)
    (yyval._evolution_line) = new evolution_line((yysemantic_stack_[(4) - (1)].vector_assignment), (yysemantic_stack_[(4) - (3)]._bool_expression));
  else
    (yyval._evolution_line) = NULL;
 }
    break;

  case 220:

/* Line 690 of lalr1.cc  */
#line 1461 "parser/nssis_new.yy"
    {
  (yyval._evolution_line) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(4) - (1)].vector_assignment));
  USE((yysemantic_stack_[(4) - (3)]._bool_expression));
 }
    break;

  case 221:

/* Line 690 of lalr1.cc  */
#line 1467 "parser/nssis_new.yy"
    {
  (yyval._evolution_line) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(4) - (1)].vector_assignment));
  USE((yysemantic_stack_[(4) - (3)]._bool_expression));
 }
    break;

  case 222:

/* Line 690 of lalr1.cc  */
#line 1473 "parser/nssis_new.yy"
    {
  (yyval._evolution_line) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(4) - (1)].vector_assignment));
  USE((yysemantic_stack_[(4) - (3)]._bool_expression));
 }
    break;

  case 223:

/* Line 690 of lalr1.cc  */
#line 1479 "parser/nssis_new.yy"
    {
  (yyval._evolution_line) = NULL;
  driver.syntax_error = true;
  }
    break;

  case 224:

/* Line 690 of lalr1.cc  */
#line 1484 "parser/nssis_new.yy"
    { 
  (yyval._bool_expression) = (yysemantic_stack_[(3) - (2)]._bool_expression); 
 }
    break;

  case 225:

/* Line 690 of lalr1.cc  */
#line 1487 "parser/nssis_new.yy"
    { 
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (2)]._bool_expression));
 }
    break;

  case 226:

/* Line 690 of lalr1.cc  */
#line 1492 "parser/nssis_new.yy"
    { 
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (2)]._bool_expression));
 }
    break;

  case 227:

/* Line 690 of lalr1.cc  */
#line 1497 "parser/nssis_new.yy"
    { 
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (2)]._bool_expression));
 }
    break;

  case 228:

/* Line 690 of lalr1.cc  */
#line 1502 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)]._bool_expression)!=NULL && (yysemantic_stack_[(3) - (3)]._bool_expression)!=NULL)
    (yyval._bool_expression) = new bool_expression(1, (yysemantic_stack_[(3) - (1)]._bool_expression), (yysemantic_stack_[(3) - (3)]._bool_expression));
  else
    (yyval._bool_expression) = NULL;
 }
    break;

  case 229:

/* Line 690 of lalr1.cc  */
#line 1508 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)]._bool_expression)!=NULL && (yysemantic_stack_[(3) - (3)]._bool_expression)!=NULL)
    (yyval._bool_expression) = new bool_expression(2, (yysemantic_stack_[(3) - (1)]._bool_expression), (yysemantic_stack_[(3) - (3)]._bool_expression));
  else
    (yyval._bool_expression) = NULL;
 }
    break;

  case 230:

/* Line 690 of lalr1.cc  */
#line 1514 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (1)]._bool_expression));
  USE((yysemantic_stack_[(3) - (3)]._bool_expression));
 }
    break;

  case 231:

/* Line 690 of lalr1.cc  */
#line 1520 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(2) - (2)]._bool_expression)!=NULL)
    (yyval._bool_expression) = new bool_expression(3, (yysemantic_stack_[(2) - (2)]._bool_expression));
  else
    (yyval._bool_expression) = NULL;
 }
    break;

  case 232:

/* Line 690 of lalr1.cc  */
#line 1526 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(2) - (2)]._bool_expression));
 }
    break;

  case 233:

/* Line 690 of lalr1.cc  */
#line 1531 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)]._expression)!=NULL && (yysemantic_stack_[(3) - (3)]._expression)!=NULL) {
    logic_expression *expr = new logic_expression((yysemantic_stack_[(3) - (2)]._unsigned_char), (yysemantic_stack_[(3) - (1)]._expression), (yysemantic_stack_[(3) - (3)]._expression));
    (yyval._bool_expression) = new bool_expression(0,  expr);
  } else
    (yyval._bool_expression) = NULL;
 }
    break;

  case 234:

/* Line 690 of lalr1.cc  */
#line 1538 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  }
    break;

  case 235:

/* Line 690 of lalr1.cc  */
#line 1543 "parser/nssis_new.yy"
    { 
  (yyval._bool_expression) = (yysemantic_stack_[(3) - (2)]._bool_expression); 
 }
    break;

  case 236:

/* Line 690 of lalr1.cc  */
#line 1546 "parser/nssis_new.yy"
    { 
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (2)]._bool_expression));
 }
    break;

  case 237:

/* Line 690 of lalr1.cc  */
#line 1551 "parser/nssis_new.yy"
    { 
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (2)]._bool_expression));
 }
    break;

  case 238:

/* Line 690 of lalr1.cc  */
#line 1556 "parser/nssis_new.yy"
    { 
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (2)]._bool_expression));
 }
    break;

  case 239:

/* Line 690 of lalr1.cc  */
#line 1561 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)]._bool_expression)!=NULL && (yysemantic_stack_[(3) - (3)]._bool_expression)!=NULL)
    (yyval._bool_expression) = new bool_expression(1, (yysemantic_stack_[(3) - (1)]._bool_expression), (yysemantic_stack_[(3) - (3)]._bool_expression));
  else
    (yyval._bool_expression) = NULL;
 }
    break;

  case 240:

/* Line 690 of lalr1.cc  */
#line 1567 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)]._bool_expression)!=NULL && (yysemantic_stack_[(3) - (3)]._bool_expression)!=NULL)
    (yyval._bool_expression) = new bool_expression(2, (yysemantic_stack_[(3) - (1)]._bool_expression), (yysemantic_stack_[(3) - (3)]._bool_expression));
  else
    (yyval._bool_expression) = NULL;
 }
    break;

  case 241:

/* Line 690 of lalr1.cc  */
#line 1573 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (1)]._bool_expression));
  USE((yysemantic_stack_[(3) - (3)]._bool_expression));
 }
    break;

  case 242:

/* Line 690 of lalr1.cc  */
#line 1579 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(2) - (2)]._bool_expression)!=NULL)
    (yyval._bool_expression) = new bool_expression(3, (yysemantic_stack_[(2) - (2)]._bool_expression));
  else
    (yyval._bool_expression) = NULL;
 }
    break;

  case 243:

/* Line 690 of lalr1.cc  */
#line 1585 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(2) - (2)]._bool_expression));
 }
    break;

  case 244:

/* Line 690 of lalr1.cc  */
#line 1590 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)]._expression)!=NULL && (yysemantic_stack_[(3) - (3)]._expression)!=NULL) {
    logic_expression *expr = new logic_expression((yysemantic_stack_[(3) - (2)]._unsigned_char), (yysemantic_stack_[(3) - (1)]._expression), (yysemantic_stack_[(3) - (3)]._expression));
    (yyval._bool_expression) = new bool_expression(0,  expr);
  } else
    (yyval._bool_expression) = NULL;
 }
    break;

  case 245:

/* Line 690 of lalr1.cc  */
#line 1597 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
 }
    break;

  case 246:

/* Line 690 of lalr1.cc  */
#line 1602 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)]._expression)!=NULL && (yysemantic_stack_[(3) - (3)]._expression)!=NULL) {
    (yyval._expression) = new arithmetic_expression(5, (yysemantic_stack_[(3) - (1)]._expression), (yysemantic_stack_[(3) - (3)]._expression));
  } else
    (yyval._expression) = NULL;
 }
    break;

  case 247:

/* Line 690 of lalr1.cc  */
#line 1608 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)]._expression)!=NULL && (yysemantic_stack_[(3) - (3)]._expression)!=NULL) {
    (yyval._expression) = new arithmetic_expression(6, (yysemantic_stack_[(3) - (1)]._expression), (yysemantic_stack_[(3) - (3)]._expression));
  } else
    (yyval._expression) = NULL;
 }
    break;

  case 248:

/* Line 690 of lalr1.cc  */
#line 1614 "parser/nssis_new.yy"
    {
  (yyval._expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (1)]._expression));
 }
    break;

  case 249:

/* Line 690 of lalr1.cc  */
#line 1619 "parser/nssis_new.yy"
    {
  (yyval._expression) = (yysemantic_stack_[(1) - (1)]._expression);
  }
    break;

  case 250:

/* Line 690 of lalr1.cc  */
#line 1622 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)]._expression)!=NULL && (yysemantic_stack_[(3) - (3)]._expression)!=NULL) {
    (yyval._expression) = new arithmetic_expression(7, (yysemantic_stack_[(3) - (1)]._expression), (yysemantic_stack_[(3) - (3)]._expression));
  } else
    (yyval._expression) = NULL;
 }
    break;

  case 251:

/* Line 690 of lalr1.cc  */
#line 1628 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)]._expression)!=NULL && (yysemantic_stack_[(3) - (3)]._expression)!=NULL) {
    (yyval._expression) = new arithmetic_expression(8, (yysemantic_stack_[(3) - (1)]._expression), (yysemantic_stack_[(3) - (3)]._expression));
  } else
    (yyval._expression) = NULL;
 }
    break;

  case 252:

/* Line 690 of lalr1.cc  */
#line 1634 "parser/nssis_new.yy"
    {
  (yyval._expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (1)]._expression));
 }
    break;

  case 253:

/* Line 690 of lalr1.cc  */
#line 1639 "parser/nssis_new.yy"
    {
  (yyval._expression) = (yysemantic_stack_[(1) - (1)]._expression);
  }
    break;

  case 254:

/* Line 690 of lalr1.cc  */
#line 1642 "parser/nssis_new.yy"
    {
  (yyval._expression) = (yysemantic_stack_[(3) - (2)]._expression);
  }
    break;

  case 255:

/* Line 690 of lalr1.cc  */
#line 1645 "parser/nssis_new.yy"
    {
  (yyval._expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (2)]._expression));
 }
    break;

  case 256:

/* Line 690 of lalr1.cc  */
#line 1650 "parser/nssis_new.yy"
    {
  (yyval._expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (2)]._expression));
 }
    break;

  case 257:

/* Line 690 of lalr1.cc  */
#line 1655 "parser/nssis_new.yy"
    {
  (yyval._expression) = (yysemantic_stack_[(1) - (1)]._expression);
  }
    break;

  case 258:

/* Line 690 of lalr1.cc  */
#line 1659 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)]._expression)!=NULL && (yysemantic_stack_[(3) - (3)]._expression)!=NULL) {
    (yyval._expression) = new bit_expression(10, (yysemantic_stack_[(3) - (1)]._expression), (yysemantic_stack_[(3) - (3)]._expression));
  } else
    (yyval._expression) = NULL;
 }
    break;

  case 259:

/* Line 690 of lalr1.cc  */
#line 1665 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)]._expression)!=NULL && (yysemantic_stack_[(3) - (3)]._expression)!=NULL) {
    (yyval._expression) = new bit_expression(12, (yysemantic_stack_[(3) - (1)]._expression), (yysemantic_stack_[(3) - (3)]._expression));
  } else
    (yyval._expression) = NULL;
 }
    break;

  case 260:

/* Line 690 of lalr1.cc  */
#line 1671 "parser/nssis_new.yy"
    {
  (yyval._expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (1)]._expression));
 }
    break;

  case 261:

/* Line 690 of lalr1.cc  */
#line 1676 "parser/nssis_new.yy"
    {
  (yyval._expression) = (yysemantic_stack_[(1) - (1)]._expression);
  }
    break;

  case 262:

/* Line 690 of lalr1.cc  */
#line 1679 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)]._expression)!=NULL && (yysemantic_stack_[(3) - (3)]._expression)!=NULL) {
    (yyval._expression) = new bit_expression(9, (yysemantic_stack_[(3) - (1)]._expression), (yysemantic_stack_[(3) - (3)]._expression));
  } else
    (yyval._expression) = NULL;
 }
    break;

  case 263:

/* Line 690 of lalr1.cc  */
#line 1685 "parser/nssis_new.yy"
    {
  (yyval._expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (1)]._expression));
 }
    break;

  case 264:

/* Line 690 of lalr1.cc  */
#line 1690 "parser/nssis_new.yy"
    {
  (yyval._expression) = (yysemantic_stack_[(1) - (1)]._expression);
  }
    break;

  case 265:

/* Line 690 of lalr1.cc  */
#line 1693 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(2) - (2)]._expression)!=NULL) {
    (yyval._expression) = new bit_expression(11, (yysemantic_stack_[(2) - (2)]._expression), NULL);
  } else
    (yyval._expression) = NULL;
 }
    break;

  case 266:

/* Line 690 of lalr1.cc  */
#line 1699 "parser/nssis_new.yy"
    {
  (yyval._expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(2) - (2)]._expression));
 }
    break;

  case 267:

/* Line 690 of lalr1.cc  */
#line 1704 "parser/nssis_new.yy"
    {
  (yyval._expression) = (yysemantic_stack_[(1) - (1)]._expression);
  }
    break;

  case 268:

/* Line 690 of lalr1.cc  */
#line 1707 "parser/nssis_new.yy"
    {
  (yyval._expression) = (yysemantic_stack_[(3) - (2)]._expression);
  }
    break;

  case 269:

/* Line 690 of lalr1.cc  */
#line 1710 "parser/nssis_new.yy"
    {
  (yyval._expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (2)]._expression));
 }
    break;

  case 270:

/* Line 690 of lalr1.cc  */
#line 1715 "parser/nssis_new.yy"
    {
  (yyval._expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (2)]._expression));
 }
    break;

  case 271:

/* Line 690 of lalr1.cc  */
#line 1720 "parser/nssis_new.yy"
    {
  (yyval._expression) = (yysemantic_stack_[(1) - (1)]._expression);
  }
    break;

  case 272:

/* Line 690 of lalr1.cc  */
#line 1724 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)]._expression)!=NULL && (yysemantic_stack_[(3) - (3)]._expression)!=NULL) {
    (yyval._expression) = new bit_expression(10, (yysemantic_stack_[(3) - (1)]._expression), (yysemantic_stack_[(3) - (3)]._expression));
  } else
    (yyval._expression) = NULL;
 }
    break;

  case 273:

/* Line 690 of lalr1.cc  */
#line 1730 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)]._expression)!=NULL && (yysemantic_stack_[(3) - (3)]._expression)!=NULL) {
    (yyval._expression) = new bit_expression(12, (yysemantic_stack_[(3) - (1)]._expression), (yysemantic_stack_[(3) - (3)]._expression));
  } else
    (yyval._expression) = NULL;
 }
    break;

  case 274:

/* Line 690 of lalr1.cc  */
#line 1736 "parser/nssis_new.yy"
    {
  (yyval._expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (1)]._expression));
 }
    break;

  case 275:

/* Line 690 of lalr1.cc  */
#line 1741 "parser/nssis_new.yy"
    {
  (yyval._expression) = (yysemantic_stack_[(1) - (1)]._expression);
  }
    break;

  case 276:

/* Line 690 of lalr1.cc  */
#line 1744 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)]._expression)!=NULL && (yysemantic_stack_[(3) - (3)]._expression)!=NULL) {
    (yyval._expression) = new bit_expression(9, (yysemantic_stack_[(3) - (1)]._expression), (yysemantic_stack_[(3) - (3)]._expression));
  } else
    (yyval._expression) = NULL;
 }
    break;

  case 277:

/* Line 690 of lalr1.cc  */
#line 1750 "parser/nssis_new.yy"
    {
  (yyval._expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (1)]._expression));
 }
    break;

  case 278:

/* Line 690 of lalr1.cc  */
#line 1755 "parser/nssis_new.yy"
    {
  (yyval._expression) = (yysemantic_stack_[(1) - (1)]._expression);
  }
    break;

  case 279:

/* Line 690 of lalr1.cc  */
#line 1758 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(2) - (2)]._expression)!=NULL) {
    (yyval._expression) = new bit_expression(11, (yysemantic_stack_[(2) - (2)]._expression), NULL);
  } else
    (yyval._expression) = NULL;
 }
    break;

  case 280:

/* Line 690 of lalr1.cc  */
#line 1764 "parser/nssis_new.yy"
    {
  (yyval._expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(2) - (2)]._expression));
 }
    break;

  case 281:

/* Line 690 of lalr1.cc  */
#line 1769 "parser/nssis_new.yy"
    {
  (yyval._expression) = (yysemantic_stack_[(1) - (1)]._expression);
  }
    break;

  case 282:

/* Line 690 of lalr1.cc  */
#line 1772 "parser/nssis_new.yy"
    {
  (yyval._expression) = (yysemantic_stack_[(3) - (2)]._expression);
  }
    break;

  case 283:

/* Line 690 of lalr1.cc  */
#line 1775 "parser/nssis_new.yy"
    {
  (yyval._expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (2)]._expression));
 }
    break;

  case 284:

/* Line 690 of lalr1.cc  */
#line 1780 "parser/nssis_new.yy"
    {
  (yyval._expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (2)]._expression));
 }
    break;

  case 285:

/* Line 690 of lalr1.cc  */
#line 1785 "parser/nssis_new.yy"
    {
  (yyval._expression) = (yysemantic_stack_[(1) - (1)]._expression);
  }
    break;

  case 286:

/* Line 690 of lalr1.cc  */
#line 1789 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)]._expression)!=NULL && (yysemantic_stack_[(3) - (3)]._expression)!=NULL) {
    (yyval._expression) = new bit_expression(10, (yysemantic_stack_[(3) - (1)]._expression), (yysemantic_stack_[(3) - (3)]._expression));
  } else
    (yyval._expression) = NULL;
 }
    break;

  case 287:

/* Line 690 of lalr1.cc  */
#line 1795 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)]._expression)!=NULL && (yysemantic_stack_[(3) - (3)]._expression)!=NULL) {
    (yyval._expression) = new bit_expression(12, (yysemantic_stack_[(3) - (1)]._expression), (yysemantic_stack_[(3) - (3)]._expression));
  } else
    (yyval._expression) = NULL;
 }
    break;

  case 288:

/* Line 690 of lalr1.cc  */
#line 1801 "parser/nssis_new.yy"
    {
  (yyval._expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (1)]._expression));
 }
    break;

  case 289:

/* Line 690 of lalr1.cc  */
#line 1806 "parser/nssis_new.yy"
    {
  (yyval._expression) = (yysemantic_stack_[(1) - (1)]._expression);
  }
    break;

  case 290:

/* Line 690 of lalr1.cc  */
#line 1809 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)]._expression)!=NULL && (yysemantic_stack_[(3) - (3)]._expression)!=NULL) {
    (yyval._expression) = new bit_expression(9, (yysemantic_stack_[(3) - (1)]._expression), (yysemantic_stack_[(3) - (3)]._expression));
  } else
    (yyval._expression) = NULL;
 }
    break;

  case 291:

/* Line 690 of lalr1.cc  */
#line 1815 "parser/nssis_new.yy"
    {
  (yyval._expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (1)]._expression));
 }
    break;

  case 292:

/* Line 690 of lalr1.cc  */
#line 1820 "parser/nssis_new.yy"
    {
  (yyval._expression) = (yysemantic_stack_[(1) - (1)]._expression);
  }
    break;

  case 293:

/* Line 690 of lalr1.cc  */
#line 1823 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(2) - (2)]._expression)!=NULL) {
    (yyval._expression) = new bit_expression(11, (yysemantic_stack_[(2) - (2)]._expression), NULL);
  } else
    (yyval._expression) = NULL;
 }
    break;

  case 294:

/* Line 690 of lalr1.cc  */
#line 1829 "parser/nssis_new.yy"
    {
  (yyval._expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(2) - (2)]._expression));
 }
    break;

  case 295:

/* Line 690 of lalr1.cc  */
#line 1834 "parser/nssis_new.yy"
    {
  (yyval._expression) = (yysemantic_stack_[(1) - (1)]._expression);
  }
    break;

  case 296:

/* Line 690 of lalr1.cc  */
#line 1837 "parser/nssis_new.yy"
    {
  (yyval._expression) = (yysemantic_stack_[(3) - (2)]._expression);
  }
    break;

  case 297:

/* Line 690 of lalr1.cc  */
#line 1840 "parser/nssis_new.yy"
    {
  (yyval._expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (2)]._expression));
 }
    break;

  case 298:

/* Line 690 of lalr1.cc  */
#line 1845 "parser/nssis_new.yy"
    {
  (yyval._expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (2)]._expression));
 }
    break;

  case 299:

/* Line 690 of lalr1.cc  */
#line 1850 "parser/nssis_new.yy"
    {
  (yyval._expression) = (yysemantic_stack_[(1) - (1)]._expression);
  }
    break;

  case 300:

/* Line 690 of lalr1.cc  */
#line 1854 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)]._expression)!=NULL && (yysemantic_stack_[(3) - (3)]._expression)!=NULL) {
    (yyval._expression) = new arithmetic_expression(5, (yysemantic_stack_[(3) - (1)]._expression), (yysemantic_stack_[(3) - (3)]._expression));
  } else
    (yyval._expression) = NULL;
 }
    break;

  case 301:

/* Line 690 of lalr1.cc  */
#line 1860 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)]._expression)!=NULL && (yysemantic_stack_[(3) - (3)]._expression)!=NULL) {
    (yyval._expression) = new arithmetic_expression(6, (yysemantic_stack_[(3) - (1)]._expression), (yysemantic_stack_[(3) - (3)]._expression));
  } else
    (yyval._expression) = NULL;
 }
    break;

  case 302:

/* Line 690 of lalr1.cc  */
#line 1866 "parser/nssis_new.yy"
    {
  (yyval._expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (1)]._expression));
 }
    break;

  case 303:

/* Line 690 of lalr1.cc  */
#line 1871 "parser/nssis_new.yy"
    {
  (yyval._expression) = (yysemantic_stack_[(1) - (1)]._expression);
  }
    break;

  case 304:

/* Line 690 of lalr1.cc  */
#line 1874 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)]._expression)!=NULL && (yysemantic_stack_[(3) - (3)]._expression)!=NULL) {
    (yyval._expression) = new arithmetic_expression(7, (yysemantic_stack_[(3) - (1)]._expression), (yysemantic_stack_[(3) - (3)]._expression));
  } else
    (yyval._expression) = NULL;
 }
    break;

  case 305:

/* Line 690 of lalr1.cc  */
#line 1880 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)]._expression)!=NULL && (yysemantic_stack_[(3) - (3)]._expression)!=NULL) {
    (yyval._expression) = new arithmetic_expression(8, (yysemantic_stack_[(3) - (1)]._expression), (yysemantic_stack_[(3) - (3)]._expression));
  } else
    (yyval._expression) = NULL;
 }
    break;

  case 306:

/* Line 690 of lalr1.cc  */
#line 1886 "parser/nssis_new.yy"
    {
  (yyval._expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (1)]._expression));
 }
    break;

  case 307:

/* Line 690 of lalr1.cc  */
#line 1891 "parser/nssis_new.yy"
    {
  (yyval._expression) = (yysemantic_stack_[(1) - (1)]._expression);
  }
    break;

  case 308:

/* Line 690 of lalr1.cc  */
#line 1894 "parser/nssis_new.yy"
    {
  (yyval._expression) = (yysemantic_stack_[(3) - (2)]._expression);
  }
    break;

  case 309:

/* Line 690 of lalr1.cc  */
#line 1897 "parser/nssis_new.yy"
    {
  (yyval._expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (2)]._expression));
 }
    break;

  case 310:

/* Line 690 of lalr1.cc  */
#line 1902 "parser/nssis_new.yy"
    {
  (yyval._expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (2)]._expression));
 }
    break;

  case 311:

/* Line 690 of lalr1.cc  */
#line 1907 "parser/nssis_new.yy"
    {
  (yyval._expression) = (yysemantic_stack_[(1) - (1)]._expression);
  }
    break;

  case 312:

/* Line 690 of lalr1.cc  */
#line 1910 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)]._expression)!=NULL && (yysemantic_stack_[(3) - (3)]._expression)!=NULL) {
    (yyval._expression) = new arithmetic_expression(5, (yysemantic_stack_[(3) - (1)]._expression), (yysemantic_stack_[(3) - (3)]._expression));
  } else
    (yyval._expression) = NULL;
 }
    break;

  case 313:

/* Line 690 of lalr1.cc  */
#line 1916 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)]._expression)!=NULL && (yysemantic_stack_[(3) - (3)]._expression)!=NULL) {
    (yyval._expression) = new arithmetic_expression(6, (yysemantic_stack_[(3) - (1)]._expression), (yysemantic_stack_[(3) - (3)]._expression));
  } else
    (yyval._expression) = NULL;
 }
    break;

  case 314:

/* Line 690 of lalr1.cc  */
#line 1922 "parser/nssis_new.yy"
    {
  (yyval._expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (1)]._expression));
 }
    break;

  case 315:

/* Line 690 of lalr1.cc  */
#line 1927 "parser/nssis_new.yy"
    {
  (yyval._expression) = (yysemantic_stack_[(1) - (1)]._expression);
  }
    break;

  case 316:

/* Line 690 of lalr1.cc  */
#line 1930 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)]._expression)!=NULL && (yysemantic_stack_[(3) - (3)]._expression)!=NULL) {
    (yyval._expression) = new arithmetic_expression(7, (yysemantic_stack_[(3) - (1)]._expression), (yysemantic_stack_[(3) - (3)]._expression));
  } else
    (yyval._expression) = NULL;
 }
    break;

  case 317:

/* Line 690 of lalr1.cc  */
#line 1936 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)]._expression)!=NULL && (yysemantic_stack_[(3) - (3)]._expression)!=NULL) {
    (yyval._expression) = new arithmetic_expression(8, (yysemantic_stack_[(3) - (1)]._expression), (yysemantic_stack_[(3) - (3)]._expression));
  } else
    (yyval._expression) = NULL;
 }
    break;

  case 318:

/* Line 690 of lalr1.cc  */
#line 1942 "parser/nssis_new.yy"
    {
  (yyval._expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (1)]._expression));
 }
    break;

  case 319:

/* Line 690 of lalr1.cc  */
#line 1947 "parser/nssis_new.yy"
    {
  (yyval._expression) = (yysemantic_stack_[(1) - (1)]._expression);
  }
    break;

  case 320:

/* Line 690 of lalr1.cc  */
#line 1950 "parser/nssis_new.yy"
    {
  (yyval._expression) = (yysemantic_stack_[(3) - (2)]._expression);
  }
    break;

  case 321:

/* Line 690 of lalr1.cc  */
#line 1953 "parser/nssis_new.yy"
    {
  (yyval._expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (2)]._expression));
 }
    break;

  case 322:

/* Line 690 of lalr1.cc  */
#line 1958 "parser/nssis_new.yy"
    {
  (yyval._expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (2)]._expression));
 }
    break;

  case 323:

/* Line 690 of lalr1.cc  */
#line 1963 "parser/nssis_new.yy"
    {
  (yyval._expression) = (yysemantic_stack_[(1) - (1)]._expression);
  }
    break;

  case 324:

/* Line 690 of lalr1.cc  */
#line 1969 "parser/nssis_new.yy"
    { 
  (yyval._bool_expression) = (yysemantic_stack_[(3) - (2)]._bool_expression); 
 }
    break;

  case 325:

/* Line 690 of lalr1.cc  */
#line 1972 "parser/nssis_new.yy"
    { 
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (2)]._bool_expression));
 }
    break;

  case 326:

/* Line 690 of lalr1.cc  */
#line 1977 "parser/nssis_new.yy"
    { 
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (2)]._bool_expression));
 }
    break;

  case 327:

/* Line 690 of lalr1.cc  */
#line 1982 "parser/nssis_new.yy"
    { 
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (2)]._bool_expression));
 }
    break;

  case 328:

/* Line 690 of lalr1.cc  */
#line 1987 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)]._bool_expression)!=NULL && (yysemantic_stack_[(3) - (3)]._bool_expression)!=NULL)
    (yyval._bool_expression) = new bool_expression(1, (yysemantic_stack_[(3) - (1)]._bool_expression), (yysemantic_stack_[(3) - (3)]._bool_expression));
  else
    (yyval._bool_expression) = NULL;
 }
    break;

  case 329:

/* Line 690 of lalr1.cc  */
#line 1993 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)]._bool_expression)!=NULL && (yysemantic_stack_[(3) - (3)]._bool_expression)!=NULL)
    (yyval._bool_expression) = new bool_expression(2, (yysemantic_stack_[(3) - (1)]._bool_expression), (yysemantic_stack_[(3) - (3)]._bool_expression));
  else
    (yyval._bool_expression) = NULL;
 }
    break;

  case 330:

/* Line 690 of lalr1.cc  */
#line 1999 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (1)]._bool_expression));
  USE((yysemantic_stack_[(3) - (3)]._bool_expression));
 }
    break;

  case 331:

/* Line 690 of lalr1.cc  */
#line 2005 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(2) - (2)]._bool_expression)!=NULL)
    (yyval._bool_expression) = new bool_expression(3, (yysemantic_stack_[(2) - (2)]._bool_expression));
  else
    (yyval._bool_expression) = NULL;
 }
    break;

  case 332:

/* Line 690 of lalr1.cc  */
#line 2011 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(2) - (2)]._bool_expression));
 }
    break;

  case 333:

/* Line 690 of lalr1.cc  */
#line 2016 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)]._expression)!=NULL && (yysemantic_stack_[(3) - (3)]._expression)!=NULL) {
    logic_expression *expr = new logic_expression((yysemantic_stack_[(3) - (2)]._unsigned_char), (yysemantic_stack_[(3) - (1)]._expression), (yysemantic_stack_[(3) - (3)]._expression));
    (yyval._bool_expression) = new bool_expression(0,  expr);
  } else
    (yyval._bool_expression) = NULL;
 }
    break;

  case 334:

/* Line 690 of lalr1.cc  */
#line 2023 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (3)].sval)!=NULL) {
    laction *a = new laction();
    variable *v;
    int i = search_string_table((yysemantic_stack_[(3) - (3)].sval));
    if(i>=0) {
      v = new variable((*string_table)[i]);
      free((yysemantic_stack_[(3) - (3)].sval));
    } else {
      v = new variable((yysemantic_stack_[(3) - (3)].sval));
      string_table->push_back((yysemantic_stack_[(3) - (3)].sval));
    }
    logic_expression *expr = new logic_expression(0, a, v);
    (yyval._bool_expression) = new bool_expression(0,  expr);
  } else
    (yyval._bool_expression) = NULL;
 }
    break;

  case 335:

/* Line 690 of lalr1.cc  */
#line 2040 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (3)].sval));
 }
    break;

  case 336:

/* Line 690 of lalr1.cc  */
#line 2045 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (3)].sval));
 }
    break;

  case 337:

/* Line 690 of lalr1.cc  */
#line 2050 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(2) - (2)].sval));
 }
    break;

  case 338:

/* Line 690 of lalr1.cc  */
#line 2055 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(5) - (1)].sval)!=NULL && (yysemantic_stack_[(5) - (5)].sval)!=NULL) {
    laction *a;
    int i = search_string_table((yysemantic_stack_[(5) - (1)].sval));
    if(i>=0) {
      a = new laction((*string_table)[i]);
      free((yysemantic_stack_[(5) - (1)].sval));
    } else {
      a = new laction((yysemantic_stack_[(5) - (1)].sval));
      string_table->push_back((yysemantic_stack_[(5) - (1)].sval));
    }
    variable *v;
    int j = search_string_table((yysemantic_stack_[(5) - (5)].sval));
    if(j>=0) {
      if(i>=0)
	v = new variable((*string_table)[i], (*string_table)[j]);
      else
	v = new variable((yysemantic_stack_[(5) - (1)].sval), (*string_table)[j]);
      free((yysemantic_stack_[(5) - (5)].sval));
    } else {
      if(i>=0)
	v = new variable((*string_table)[i], (yysemantic_stack_[(5) - (5)].sval));
      else
	v = new variable((yysemantic_stack_[(5) - (1)].sval), (yysemantic_stack_[(5) - (5)].sval));
      string_table->push_back((yysemantic_stack_[(5) - (5)].sval));
    }
    i = search_logic_expression_table(a, v);
    if(i>=0) {
      (yyval._bool_expression) = (*logic_expression_table)[i];
      delete a;
      delete v;
    } else {
			logic_expression *expr = new logic_expression(0, a, v);
			bool_expression *bexpr = new bool_expression(0,  expr);
      (yyval._bool_expression) = bexpr;
      logic_expression_table->push_back(bexpr);
    }
  } else
    (yyval._bool_expression) = NULL;
 }
    break;

  case 339:

/* Line 690 of lalr1.cc  */
#line 2095 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (1)].sval));
  USE((yysemantic_stack_[(5) - (5)].sval));
 }
    break;

  case 340:

/* Line 690 of lalr1.cc  */
#line 2101 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (1)].sval));
  USE((yysemantic_stack_[(5) - (5)].sval));
 }
    break;

  case 341:

/* Line 690 of lalr1.cc  */
#line 2107 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (1)].sval));
  USE((yysemantic_stack_[(5) - (5)].sval));
 }
    break;

  case 342:

/* Line 690 of lalr1.cc  */
#line 2113 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(4) - (1)].sval));
  USE((yysemantic_stack_[(4) - (4)].sval));
 }
    break;

  case 343:

/* Line 690 of lalr1.cc  */
#line 2119 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(4) - (1)].sval));
  USE((yysemantic_stack_[(4) - (4)].sval));
 }
    break;

  case 344:

/* Line 690 of lalr1.cc  */
#line 2125 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (1)].sval));
  USE((yysemantic_stack_[(5) - (5)].sval));
 }
    break;

  case 345:

/* Line 690 of lalr1.cc  */
#line 2131 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (1)].sval));
  USE((yysemantic_stack_[(3) - (3)].sval));
 }
    break;

  case 346:

/* Line 690 of lalr1.cc  */
#line 2137 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  }
    break;

  case 347:

/* Line 690 of lalr1.cc  */
#line 2142 "parser/nssis_new.yy"
    {
  (yyval._unsigned_char) = 2;
 }
    break;

  case 348:

/* Line 690 of lalr1.cc  */
#line 2145 "parser/nssis_new.yy"
    {
  (yyval._unsigned_char) = 3;
  }
    break;

  case 349:

/* Line 690 of lalr1.cc  */
#line 2148 "parser/nssis_new.yy"
    {
  (yyval._unsigned_char) = 4;
  }
    break;

  case 350:

/* Line 690 of lalr1.cc  */
#line 2151 "parser/nssis_new.yy"
    {
  (yyval._unsigned_char) = 5;
  }
    break;

  case 351:

/* Line 690 of lalr1.cc  */
#line 2154 "parser/nssis_new.yy"
    {
  (yyval._unsigned_char) = 0;
  }
    break;

  case 352:

/* Line 690 of lalr1.cc  */
#line 2157 "parser/nssis_new.yy"
    {
  (yyval._unsigned_char) = 1;
  }
    break;

  case 353:

/* Line 690 of lalr1.cc  */
#line 2162 "parser/nssis_new.yy"
    { 
  (yyval._bool_expression) = (yysemantic_stack_[(3) - (2)]._bool_expression); 
 }
    break;

  case 354:

/* Line 690 of lalr1.cc  */
#line 2165 "parser/nssis_new.yy"
    { 
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (2)]._bool_expression));
 }
    break;

  case 355:

/* Line 690 of lalr1.cc  */
#line 2170 "parser/nssis_new.yy"
    { 
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (2)]._bool_expression));
 }
    break;

  case 356:

/* Line 690 of lalr1.cc  */
#line 2175 "parser/nssis_new.yy"
    { 
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (2)]._bool_expression));
 }
    break;

  case 357:

/* Line 690 of lalr1.cc  */
#line 2180 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)]._bool_expression)!=NULL && (yysemantic_stack_[(3) - (3)]._bool_expression)!=NULL)
    (yyval._bool_expression) = new bool_expression(1, (yysemantic_stack_[(3) - (1)]._bool_expression), (yysemantic_stack_[(3) - (3)]._bool_expression));
  else
    (yyval._bool_expression) = NULL;
 }
    break;

  case 358:

/* Line 690 of lalr1.cc  */
#line 2186 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)]._bool_expression)!=NULL && (yysemantic_stack_[(3) - (3)]._bool_expression)!=NULL)
    (yyval._bool_expression) = new bool_expression(2, (yysemantic_stack_[(3) - (1)]._bool_expression), (yysemantic_stack_[(3) - (3)]._bool_expression));
  else
    (yyval._bool_expression) = NULL;
 }
    break;

  case 359:

/* Line 690 of lalr1.cc  */
#line 2192 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (1)]._bool_expression));
  USE((yysemantic_stack_[(3) - (3)]._bool_expression));
 }
    break;

  case 360:

/* Line 690 of lalr1.cc  */
#line 2198 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(2) - (2)]._bool_expression)!=NULL)
    (yyval._bool_expression) = new bool_expression(3, (yysemantic_stack_[(2) - (2)]._bool_expression));
  else
    (yyval._bool_expression) = NULL;
 }
    break;

  case 361:

/* Line 690 of lalr1.cc  */
#line 2204 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(2) - (2)]._bool_expression));
 }
    break;

  case 362:

/* Line 690 of lalr1.cc  */
#line 2209 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)]._expression)!=NULL && (yysemantic_stack_[(3) - (3)]._expression)!=NULL) {
    logic_expression *expr = new logic_expression((yysemantic_stack_[(3) - (2)]._unsigned_char), (yysemantic_stack_[(3) - (1)]._expression), (yysemantic_stack_[(3) - (3)]._expression));
    (yyval._bool_expression) = new bool_expression(0,  expr);
  } else
    (yyval._bool_expression) = NULL;
 }
    break;

  case 363:

/* Line 690 of lalr1.cc  */
#line 2216 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (3)].sval)!=NULL) {
    laction *a = new laction();
    variable *v;
    int i = search_string_table((yysemantic_stack_[(3) - (3)].sval));
    if(i>=0) {
      v = new variable((*string_table)[i]);
      free((yysemantic_stack_[(3) - (3)].sval));
    } else {
      v = new variable((yysemantic_stack_[(3) - (3)].sval));
      string_table->push_back((yysemantic_stack_[(3) - (3)].sval));
    }
    logic_expression *expr = new logic_expression(0, a, v);
    (yyval._bool_expression) = new bool_expression(0,  expr);
  } else
    (yyval._bool_expression) = NULL;
 }
    break;

  case 364:

/* Line 690 of lalr1.cc  */
#line 2233 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (3)].sval));
 }
    break;

  case 365:

/* Line 690 of lalr1.cc  */
#line 2238 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (3)].sval));
 }
    break;

  case 366:

/* Line 690 of lalr1.cc  */
#line 2243 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(2) - (2)].sval));
 }
    break;

  case 367:

/* Line 690 of lalr1.cc  */
#line 2248 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(5) - (1)].sval)!=NULL && (yysemantic_stack_[(5) - (5)].sval)!=NULL) {
    laction *a;
    int i = search_string_table((yysemantic_stack_[(5) - (1)].sval));
    if(i>=0) {
      a = new laction((*string_table)[i]);
      free((yysemantic_stack_[(5) - (1)].sval));
    } else {
      a = new laction((yysemantic_stack_[(5) - (1)].sval));
      string_table->push_back((yysemantic_stack_[(5) - (1)].sval));
    }
    variable *v;
    int j = search_string_table((yysemantic_stack_[(5) - (5)].sval));
    if(j>=0) {
      if(i>=0)
	v = new variable((*string_table)[i], (*string_table)[j]);
      else
	v = new variable((yysemantic_stack_[(5) - (1)].sval), (*string_table)[j]);
      free((yysemantic_stack_[(5) - (5)].sval));
    } else {
      if(i>=0)
	v = new variable((*string_table)[i], (yysemantic_stack_[(5) - (5)].sval));
      else
	v = new variable((yysemantic_stack_[(5) - (1)].sval), (yysemantic_stack_[(5) - (5)].sval));
      string_table->push_back((yysemantic_stack_[(5) - (5)].sval));
    }
    logic_expression *expr = new logic_expression(0, a, v);
    (yyval._bool_expression) = new bool_expression(0,  expr);
  } else 
    (yyval._bool_expression) = NULL;
 }
    break;

  case 368:

/* Line 690 of lalr1.cc  */
#line 2279 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (1)].sval));
  USE((yysemantic_stack_[(5) - (5)].sval));
 }
    break;

  case 369:

/* Line 690 of lalr1.cc  */
#line 2285 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (1)].sval));
  USE((yysemantic_stack_[(5) - (5)].sval));
 }
    break;

  case 370:

/* Line 690 of lalr1.cc  */
#line 2291 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (1)].sval));
  USE((yysemantic_stack_[(5) - (5)].sval));
 }
    break;

  case 371:

/* Line 690 of lalr1.cc  */
#line 2297 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(4) - (1)].sval));
  USE((yysemantic_stack_[(4) - (4)].sval));
 }
    break;

  case 372:

/* Line 690 of lalr1.cc  */
#line 2303 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(4) - (1)].sval));
  USE((yysemantic_stack_[(4) - (4)].sval));
 }
    break;

  case 373:

/* Line 690 of lalr1.cc  */
#line 2309 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (1)].sval));
  USE((yysemantic_stack_[(5) - (5)].sval));
 }
    break;

  case 374:

/* Line 690 of lalr1.cc  */
#line 2315 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (1)].sval));
  USE((yysemantic_stack_[(3) - (3)].sval));
 }
    break;

  case 375:

/* Line 690 of lalr1.cc  */
#line 2321 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(5) - (5)].sval)!=NULL) {
    laction *a = new laction((*string_table)[0]);
    variable *v;
    int j = search_string_table((yysemantic_stack_[(5) - (5)].sval));
    if(j>=0) {
      v = new variable((*string_table)[0], (*string_table)[j]);
      free((yysemantic_stack_[(5) - (5)].sval));
    } else { 
      v = new variable((*string_table)[0], (yysemantic_stack_[(5) - (5)].sval));
      string_table->push_back((yysemantic_stack_[(5) - (5)].sval));
    }
    logic_expression *expr = new logic_expression(0, a, v);
    (yyval._bool_expression) = new bool_expression(0,  expr);
  } else
    (yyval._bool_expression) = NULL;
 }
    break;

  case 376:

/* Line 690 of lalr1.cc  */
#line 2338 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (5)].sval));
 }
    break;

  case 377:

/* Line 690 of lalr1.cc  */
#line 2343 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (5)].sval));
 }
    break;

  case 378:

/* Line 690 of lalr1.cc  */
#line 2348 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(4) - (4)].sval));
 }
    break;

  case 379:

/* Line 690 of lalr1.cc  */
#line 2353 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(4) - (4)].sval));
 }
    break;

  case 380:

/* Line 690 of lalr1.cc  */
#line 2358 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (5)].sval));
 }
    break;

  case 381:

/* Line 690 of lalr1.cc  */
#line 2363 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (3)].sval));
 }
    break;

  case 382:

/* Line 690 of lalr1.cc  */
#line 2368 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  }
    break;

  case 383:

/* Line 690 of lalr1.cc  */
#line 2374 "parser/nssis_new.yy"
    {
  (yyval._expression) = (yysemantic_stack_[(1) - (1)]._bool_value);
 }
    break;

  case 384:

/* Line 690 of lalr1.cc  */
#line 2377 "parser/nssis_new.yy"
    {
    int i = search_string_table((yysemantic_stack_[(1) - (1)].sval));
    if(i>=0) {
      (yyval._expression) = new variable((*string_table)[i]);
      free((yysemantic_stack_[(1) - (1)].sval));
    } else {
      (yyval._expression) = new variable((yysemantic_stack_[(1) - (1)].sval)); // can be enumerate value. Will be decided during global syntax checking
      string_table->push_back((yysemantic_stack_[(1) - (1)].sval));
    }
  }
    break;

  case 385:

/* Line 690 of lalr1.cc  */
#line 2387 "parser/nssis_new.yy"
    {
  (yyval._expression) = new int_value((yysemantic_stack_[(1) - (1)].ival));
  }
    break;

  case 386:

/* Line 690 of lalr1.cc  */
#line 2390 "parser/nssis_new.yy"
    {
  (yyval._bool_value) = new bool_value(true);
  }
    break;

  case 387:

/* Line 690 of lalr1.cc  */
#line 2393 "parser/nssis_new.yy"
    {
  (yyval._bool_value) = new bool_value(false);
  }
    break;

  case 388:

/* Line 690 of lalr1.cc  */
#line 2397 "parser/nssis_new.yy"
    {
  (yyval._expression) = (yysemantic_stack_[(1) - (1)]._bool_value);
 }
    break;

  case 389:

/* Line 690 of lalr1.cc  */
#line 2400 "parser/nssis_new.yy"
    {
    int i = search_string_table((yysemantic_stack_[(1) - (1)].sval));
    if(i>=0) {
      (yyval._expression) = new variable((*string_table)[i]);
      free((yysemantic_stack_[(1) - (1)].sval));
    } else {
      (yyval._expression) = new variable((yysemantic_stack_[(1) - (1)].sval)); // can be enumerate value. Will be decided during global syntax checking
      string_table->push_back((yysemantic_stack_[(1) - (1)].sval));
    }
  }
    break;

  case 390:

/* Line 690 of lalr1.cc  */
#line 2410 "parser/nssis_new.yy"
    {
    int i = search_string_table((yysemantic_stack_[(3) - (3)].sval));
    variable *var;
    if(i>=0) {
      var = new variable((*string_table)[0], (*string_table)[i]);
      free((yysemantic_stack_[(3) - (3)].sval));
    } else {
      var = new variable((*string_table)[0], (yysemantic_stack_[(3) - (3)].sval)); 
      string_table->push_back((yysemantic_stack_[(3) - (3)].sval));
    }
    i = search_variable_table(var);
    if(i>=0) {
      (yyval._expression) = (*variable_table)[i];
      delete var;
    } else {
      (yyval._expression) = var;
      variable_table->push_back(var);
    }
  }
    break;

  case 391:

/* Line 690 of lalr1.cc  */
#line 2429 "parser/nssis_new.yy"
    {
  (yyval._expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (3)].sval));
  }
    break;

  case 392:

/* Line 690 of lalr1.cc  */
#line 2434 "parser/nssis_new.yy"
    {
  (yyval._expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (3)].sval));
  }
    break;

  case 393:

/* Line 690 of lalr1.cc  */
#line 2439 "parser/nssis_new.yy"
    {
  (yyval._expression) = new int_value((yysemantic_stack_[(1) - (1)].ival));
  }
    break;

  case 394:

/* Line 690 of lalr1.cc  */
#line 2442 "parser/nssis_new.yy"
    {
  (yyval._expression) = (yysemantic_stack_[(1) - (1)]._bool_value);
 }
    break;

  case 395:

/* Line 690 of lalr1.cc  */
#line 2445 "parser/nssis_new.yy"
    {
    int i = search_string_table((yysemantic_stack_[(1) - (1)].sval));
    if(i>=0) {
      (yyval._expression) = new variable((*string_table)[i]);
      free((yysemantic_stack_[(1) - (1)].sval));
    } else {
      (yyval._expression) = new variable((yysemantic_stack_[(1) - (1)].sval)); // can be enumerate value. Will be decided during global syntax checking
      string_table->push_back((yysemantic_stack_[(1) - (1)].sval));
    }
  }
    break;

  case 396:

/* Line 690 of lalr1.cc  */
#line 2455 "parser/nssis_new.yy"
    {
    int i = search_string_table((yysemantic_stack_[(3) - (1)].sval));
    int j = search_string_table((yysemantic_stack_[(3) - (3)].sval));
    variable *var;
    if(i>=0) {
      if(j>=0) {
	var = new variable((*string_table)[i], (*string_table)[j]);
	free((yysemantic_stack_[(3) - (3)].sval));
      } else {
	var = new variable((*string_table)[i], (yysemantic_stack_[(3) - (3)].sval));
	string_table->push_back((yysemantic_stack_[(3) - (3)].sval));
      }
      free((yysemantic_stack_[(3) - (1)].sval));
    } else {
      if(j>=0) {
	var = new variable((yysemantic_stack_[(3) - (1)].sval), (*string_table)[j]);
	free((yysemantic_stack_[(3) - (3)].sval));
      } else {
	var = new variable((yysemantic_stack_[(3) - (1)].sval), (yysemantic_stack_[(3) - (3)].sval));
	string_table->push_back((yysemantic_stack_[(3) - (3)].sval));
      }
      string_table->push_back((yysemantic_stack_[(3) - (1)].sval));
    }
    i = search_variable_table(var);
    if(i>=0) {
      (yyval._expression) = (*variable_table)[i];
      delete var;
    } else {
      (yyval._expression) = var;
      variable_table->push_back(var);
    }
  }
    break;

  case 397:

/* Line 690 of lalr1.cc  */
#line 2487 "parser/nssis_new.yy"
    {
  (yyval._expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (1)].sval));
  USE((yysemantic_stack_[(3) - (3)].sval));
  }
    break;

  case 398:

/* Line 690 of lalr1.cc  */
#line 2493 "parser/nssis_new.yy"
    {
    int i = search_string_table((yysemantic_stack_[(3) - (3)].sval));
    variable *var;
    if(i>=0) {
      var = new variable((*string_table)[0], (*string_table)[i]);
      free((yysemantic_stack_[(3) - (3)].sval));
    } else {
      var = new variable((*string_table)[0], (yysemantic_stack_[(3) - (3)].sval)); 
      string_table->push_back((yysemantic_stack_[(3) - (3)].sval));
    }
    i = search_variable_table(var);
    if(i>=0) {
      (yyval._expression) = (*variable_table)[i];
      delete var;
    } else {
      (yyval._expression) = var;
      variable_table->push_back(var);
    }
  }
    break;

  case 399:

/* Line 690 of lalr1.cc  */
#line 2512 "parser/nssis_new.yy"
    {
  (yyval._expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (3)].sval));
  }
    break;

  case 400:

/* Line 690 of lalr1.cc  */
#line 2517 "parser/nssis_new.yy"
    {
  (yyval._expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (3)].sval));
  }
    break;

  case 401:

/* Line 690 of lalr1.cc  */
#line 2522 "parser/nssis_new.yy"
    {
  (yyval._expression) = new int_value((yysemantic_stack_[(1) - (1)].ival));
  }
    break;

  case 402:

/* Line 690 of lalr1.cc  */
#line 2526 "parser/nssis_new.yy"
    {
  (yyval._expression) = (yysemantic_stack_[(1) - (1)]._bool_value);
 }
    break;

  case 403:

/* Line 690 of lalr1.cc  */
#line 2529 "parser/nssis_new.yy"
    {
    int i = search_string_table((yysemantic_stack_[(1) - (1)].sval));
    if(i>=0) {
      (yyval._expression) = new enum_value((*string_table)[i]);
      free((yysemantic_stack_[(1) - (1)].sval));
    } else {
      (yyval._expression) = new enum_value((yysemantic_stack_[(1) - (1)].sval)); // can be enumerate value. Will be decided during global syntax checking
      string_table->push_back((yysemantic_stack_[(1) - (1)].sval));
    }
  }
    break;

  case 404:

/* Line 690 of lalr1.cc  */
#line 2539 "parser/nssis_new.yy"
    {
  (yyval._expression) = new int_value((yysemantic_stack_[(1) - (1)].ival));
  }
    break;

  case 405:

/* Line 690 of lalr1.cc  */
#line 2544 "parser/nssis_new.yy"
    {
  (yyval.ival) = 1;
 }
    break;

  case 406:

/* Line 690 of lalr1.cc  */
#line 2547 "parser/nssis_new.yy"
    {
  (yyval.ival) = 1;
 }
    break;

  case 407:

/* Line 690 of lalr1.cc  */
#line 2550 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 408:

/* Line 690 of lalr1.cc  */
#line 2554 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 409:

/* Line 690 of lalr1.cc  */
#line 2558 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
  }
    break;

  case 411:

/* Line 690 of lalr1.cc  */
#line 2563 "parser/nssis_new.yy"
    {
  driver.syntax_error = true;
  }
    break;

  case 413:

/* Line 690 of lalr1.cc  */
#line 2568 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(5) - (2)].sval)!=NULL && (yysemantic_stack_[(5) - (4)]._bool_expression)!=NULL) {
    if(is_evaluation->find(*(yysemantic_stack_[(5) - (2)].sval)) != is_evaluation->end() && options["quiet"] == 0)
      cout << "warning: atomic proposition " << *(yysemantic_stack_[(5) - (2)].sval) << " has already been defined." << endl;
    (*is_evaluation)[*(yysemantic_stack_[(5) - (2)].sval)] = (yysemantic_stack_[(5) - (4)]._bool_expression);
    free((yysemantic_stack_[(5) - (2)].sval));
  }
 }
    break;

  case 414:

/* Line 690 of lalr1.cc  */
#line 2576 "parser/nssis_new.yy"
    {
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (2)].sval));
  USE((yysemantic_stack_[(5) - (4)]._bool_expression));
 }
    break;

  case 415:

/* Line 690 of lalr1.cc  */
#line 2581 "parser/nssis_new.yy"
    {
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (2)].sval));
  USE((yysemantic_stack_[(5) - (4)]._bool_expression));
 }
    break;

  case 416:

/* Line 690 of lalr1.cc  */
#line 2586 "parser/nssis_new.yy"
    {
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (2)].sval));
  USE((yysemantic_stack_[(5) - (4)]._bool_expression));
 }
    break;

  case 417:

/* Line 690 of lalr1.cc  */
#line 2591 "parser/nssis_new.yy"
    {
  driver.syntax_error = true;
  }
    break;

  case 418:

/* Line 690 of lalr1.cc  */
#line 2595 "parser/nssis_new.yy"
    { 
  (yyval._bool_expression) = (yysemantic_stack_[(3) - (2)]._bool_expression); 
 }
    break;

  case 419:

/* Line 690 of lalr1.cc  */
#line 2598 "parser/nssis_new.yy"
    { 
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (2)]._bool_expression));
 }
    break;

  case 420:

/* Line 690 of lalr1.cc  */
#line 2603 "parser/nssis_new.yy"
    { 
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (2)]._bool_expression));
 }
    break;

  case 421:

/* Line 690 of lalr1.cc  */
#line 2608 "parser/nssis_new.yy"
    { 
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (2)]._bool_expression));
 }
    break;

  case 422:

/* Line 690 of lalr1.cc  */
#line 2613 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)]._bool_expression)!=NULL && (yysemantic_stack_[(3) - (3)]._bool_expression)!=NULL)
    (yyval._bool_expression) = new bool_expression(1, (yysemantic_stack_[(3) - (1)]._bool_expression), (yysemantic_stack_[(3) - (3)]._bool_expression));
  else
    (yyval._bool_expression) = NULL;
 }
    break;

  case 423:

/* Line 690 of lalr1.cc  */
#line 2619 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)]._bool_expression)!=NULL && (yysemantic_stack_[(3) - (3)]._bool_expression)!=NULL)
    (yyval._bool_expression) = new bool_expression(2, (yysemantic_stack_[(3) - (1)]._bool_expression), (yysemantic_stack_[(3) - (3)]._bool_expression));
  else
    (yyval._bool_expression) = NULL;
 }
    break;

  case 424:

/* Line 690 of lalr1.cc  */
#line 2625 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (1)]._bool_expression));USE((yysemantic_stack_[(3) - (3)]._bool_expression));
 }
    break;

  case 425:

/* Line 690 of lalr1.cc  */
#line 2630 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(2) - (2)]._bool_expression)!=NULL)
    (yyval._bool_expression) = new bool_expression(3, (yysemantic_stack_[(2) - (2)]._bool_expression));
  else
    (yyval._bool_expression) = NULL;
 }
    break;

  case 426:

/* Line 690 of lalr1.cc  */
#line 2636 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(2) - (2)]._bool_expression));
 }
    break;

  case 427:

/* Line 690 of lalr1.cc  */
#line 2641 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)]._expression)!=NULL && (yysemantic_stack_[(3) - (3)]._expression)!=NULL) {
    logic_expression *expr = new logic_expression((yysemantic_stack_[(3) - (2)]._unsigned_char), (yysemantic_stack_[(3) - (1)]._expression), (yysemantic_stack_[(3) - (3)]._expression));
    (yyval._bool_expression) = new bool_expression(0,  expr);
  } else
    (yyval._bool_expression) = NULL;
 }
    break;

  case 428:

/* Line 690 of lalr1.cc  */
#line 2648 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  }
    break;

  case 429:

/* Line 690 of lalr1.cc  */
#line 2656 "parser/nssis_new.yy"
    {
  (yyval.ival) = 1;
 }
    break;

  case 430:

/* Line 690 of lalr1.cc  */
#line 2659 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 431:

/* Line 690 of lalr1.cc  */
#line 2663 "parser/nssis_new.yy"
    {
  (yyval.ival) = 1;
 }
    break;

  case 432:

/* Line 690 of lalr1.cc  */
#line 2666 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 433:

/* Line 690 of lalr1.cc  */
#line 2670 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 434:

/* Line 690 of lalr1.cc  */
#line 2674 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 435:

/* Line 690 of lalr1.cc  */
#line 2678 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 436:

/* Line 690 of lalr1.cc  */
#line 2682 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 437:

/* Line 690 of lalr1.cc  */
#line 2686 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 438:

/* Line 690 of lalr1.cc  */
#line 2690 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
  }
    break;

  case 439:

/* Line 690 of lalr1.cc  */
#line 2694 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)].ival)==1 && (yysemantic_stack_[(3) - (3)].ival)==1)
    is_istates = (yysemantic_stack_[(3) - (2)]._bool_expression); 
 }
    break;

  case 440:

/* Line 690 of lalr1.cc  */
#line 2698 "parser/nssis_new.yy"
    {
  driver.syntax_error = true;
  }
    break;

  case 441:

/* Line 690 of lalr1.cc  */
#line 2702 "parser/nssis_new.yy"
    { 
  (yyval._bool_expression) = (yysemantic_stack_[(3) - (2)]._bool_expression); 
}
    break;

  case 442:

/* Line 690 of lalr1.cc  */
#line 2705 "parser/nssis_new.yy"
    { 
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (2)]._bool_expression));
 }
    break;

  case 443:

/* Line 690 of lalr1.cc  */
#line 2710 "parser/nssis_new.yy"
    { 
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (2)]._bool_expression));
 }
    break;

  case 444:

/* Line 690 of lalr1.cc  */
#line 2715 "parser/nssis_new.yy"
    { 
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (2)]._bool_expression))
 }
    break;

  case 445:

/* Line 690 of lalr1.cc  */
#line 2720 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)]._bool_expression)!=NULL && (yysemantic_stack_[(3) - (3)]._bool_expression)!=NULL)
    (yyval._bool_expression) = new bool_expression(1, (yysemantic_stack_[(3) - (1)]._bool_expression), (yysemantic_stack_[(3) - (3)]._bool_expression));
  else
    (yyval._bool_expression) = NULL;
 }
    break;

  case 446:

/* Line 690 of lalr1.cc  */
#line 2726 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)]._bool_expression)!=NULL && (yysemantic_stack_[(3) - (3)]._bool_expression)!=NULL)
    (yyval._bool_expression) = new bool_expression(2, (yysemantic_stack_[(3) - (1)]._bool_expression), (yysemantic_stack_[(3) - (3)]._bool_expression));
  else
    (yyval._bool_expression) = NULL;
 }
    break;

  case 447:

/* Line 690 of lalr1.cc  */
#line 2732 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (1)]._bool_expression));USE((yysemantic_stack_[(3) - (3)]._bool_expression));
 }
    break;

  case 448:

/* Line 690 of lalr1.cc  */
#line 2737 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(2) - (2)]._bool_expression)!=NULL)
    (yyval._bool_expression) = new bool_expression(3, (yysemantic_stack_[(2) - (2)]._bool_expression));
  else
    (yyval._bool_expression) = NULL;
 }
    break;

  case 449:

/* Line 690 of lalr1.cc  */
#line 2743 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(2) - (2)]._bool_expression));
 }
    break;

  case 450:

/* Line 690 of lalr1.cc  */
#line 2748 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(7) - (1)].sval)!=NULL && (yysemantic_stack_[(7) - (3)].sval)!=NULL && (yysemantic_stack_[(7) - (5)].sval)!=NULL && (yysemantic_stack_[(7) - (7)].sval)!=NULL) {
    int i = search_string_table((yysemantic_stack_[(7) - (1)].sval));
    int j = search_string_table((yysemantic_stack_[(7) - (3)].sval));
    variable *v;
    if(i>=0) {
      if(j>=0) {
	v = new variable((*string_table)[i], (*string_table)[j]);
	free((yysemantic_stack_[(7) - (3)].sval));
      } else {
	v = new variable((*string_table)[i], (yysemantic_stack_[(7) - (3)].sval));
	string_table->push_back((yysemantic_stack_[(7) - (3)].sval));
      }
      free((yysemantic_stack_[(7) - (1)].sval));
    } else {
      if(j>=0) {
	v = new variable((yysemantic_stack_[(7) - (1)].sval), (*string_table)[j]);
	free((yysemantic_stack_[(7) - (3)].sval));
      } else {
	v = new variable((yysemantic_stack_[(7) - (1)].sval), (yysemantic_stack_[(7) - (3)].sval));
	string_table->push_back((yysemantic_stack_[(7) - (3)].sval));
      }
      string_table->push_back((yysemantic_stack_[(7) - (1)].sval));
    }
    i = search_variable_table(v);
    if(i>=0) {
      delete v;
      v = (*variable_table)[i];
    } else {
      variable_table->push_back(v);
    }

    i = search_string_table((yysemantic_stack_[(7) - (5)].sval));
    j = search_string_table((yysemantic_stack_[(7) - (7)].sval));
    variable *v1;
    if(i>=0) {
      if(j>=0) {
	v1 = new variable((*string_table)[i], (*string_table)[j]);
	free((yysemantic_stack_[(7) - (7)].sval));
      } else {
	v1 = new variable((*string_table)[i], (yysemantic_stack_[(7) - (7)].sval));
	string_table->push_back((yysemantic_stack_[(7) - (7)].sval));
      }
      free((yysemantic_stack_[(7) - (5)].sval));
    } else {
      if(j>=0) {
	v1 = new variable((yysemantic_stack_[(7) - (5)].sval), (*string_table)[j]);
	free((yysemantic_stack_[(7) - (7)].sval));
      } else {
	v1 = new variable((yysemantic_stack_[(7) - (5)].sval), (yysemantic_stack_[(7) - (7)].sval));
	string_table->push_back((yysemantic_stack_[(7) - (7)].sval));
      }
      string_table->push_back((yysemantic_stack_[(7) - (5)].sval));
    }
    i = search_variable_table(v1);
    if(i>=0) {
      delete v1;
      v1 = (*variable_table)[i];
    } else {
      variable_table->push_back(v1);
    }

    i = search_logic_expression_table1(v, v1);
    if(i>=0) {
      (yyval._bool_expression) = (*logic_expression_table1)[i];
      free((yysemantic_stack_[(7) - (5)].sval));
    } else {
			logic_expression *e = new logic_expression(0, v, v1);
			bool_expression *bexpr = new bool_expression(0, e);
      (yyval._bool_expression) = bexpr;
      logic_expression_table1->push_back(bexpr);
    }    
  } else
    (yyval._bool_expression) = NULL;
 }
    break;

  case 451:

/* Line 690 of lalr1.cc  */
#line 2823 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(7) - (1)].sval)!=NULL && (yysemantic_stack_[(7) - (3)].sval)!=NULL && (yysemantic_stack_[(7) - (7)].sval)!=NULL) {
    int i = search_string_table((yysemantic_stack_[(7) - (1)].sval));
    int j = search_string_table((yysemantic_stack_[(7) - (3)].sval));
    variable *v;
    if(i>=0) {
      if(j>=0) {
	v = new variable((*string_table)[i], (*string_table)[j]);
	free((yysemantic_stack_[(7) - (3)].sval));
      } else {
	v = new variable((*string_table)[i], (yysemantic_stack_[(7) - (3)].sval));
	string_table->push_back((yysemantic_stack_[(7) - (3)].sval));
      }
      free((yysemantic_stack_[(7) - (1)].sval));
    } else {
      if(j>=0) {
	v = new variable((yysemantic_stack_[(7) - (1)].sval), (*string_table)[j]);
	free((yysemantic_stack_[(7) - (3)].sval));
      } else {
	v = new variable((yysemantic_stack_[(7) - (1)].sval), (yysemantic_stack_[(7) - (3)].sval));
	string_table->push_back((yysemantic_stack_[(7) - (3)].sval));
      }
      string_table->push_back((yysemantic_stack_[(7) - (1)].sval));
    }
    i = search_variable_table(v);
    if(i>=0) {
      delete v;
      v = (*variable_table)[i];
    } else {
      variable_table->push_back(v);
    }

    j = search_string_table((yysemantic_stack_[(7) - (7)].sval));
    variable *v1;
    if(j>=0) {
      v1 = new variable((*string_table)[0], (*string_table)[j]);
      free((yysemantic_stack_[(7) - (7)].sval));
    } else {
      v1 = new variable((*string_table)[0], (yysemantic_stack_[(7) - (7)].sval));
      string_table->push_back((yysemantic_stack_[(7) - (7)].sval));
    }
    
    i = search_variable_table(v1);
    if(i>=0) {
      delete v1;
      v1 = (*variable_table)[i];
    } else {
      variable_table->push_back(v1);
    }

    i = search_logic_expression_table1(v, v1);
    if(i>=0) {
      (yyval._bool_expression) = (*logic_expression_table1)[i];
    } else {
			logic_expression *e = new logic_expression(0, v, v1);
			bool_expression *bexpr = new bool_expression(0, e);
      (yyval._bool_expression) = bexpr;
      logic_expression_table1->push_back(bexpr);
    }    
  } else
    (yyval._bool_expression) = NULL;
 }
    break;

  case 452:

/* Line 690 of lalr1.cc  */
#line 2885 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(7) - (3)].sval)!=NULL && (yysemantic_stack_[(7) - (5)].sval)!=NULL && (yysemantic_stack_[(7) - (7)].sval)!=NULL) {
    int j = search_string_table((yysemantic_stack_[(7) - (3)].sval));
    variable *v;
    if(j>=0) {
      v = new variable((*string_table)[0], (*string_table)[j]);
      free((yysemantic_stack_[(7) - (3)].sval));
    } else {
      v = new variable((*string_table)[0], (yysemantic_stack_[(7) - (3)].sval));
      string_table->push_back((yysemantic_stack_[(7) - (3)].sval));
    }
    int i = search_variable_table(v);
    if(i>=0) {
      delete v;
      v = (*variable_table)[i];
    } else {
      variable_table->push_back(v);
    }

    i = search_string_table((yysemantic_stack_[(7) - (5)].sval));
    j = search_string_table((yysemantic_stack_[(7) - (7)].sval));
    variable *v1;
    if(i>=0) {
      if(j>=0) {
	v1 = new variable((*string_table)[i], (*string_table)[j]);
	free((yysemantic_stack_[(7) - (7)].sval));
      } else {
	v1 = new variable((*string_table)[i], (yysemantic_stack_[(7) - (7)].sval));
	string_table->push_back((yysemantic_stack_[(7) - (7)].sval));
      }
      free((yysemantic_stack_[(7) - (5)].sval));
    } else {
      if(j>=0) {
	v1 = new variable((yysemantic_stack_[(7) - (5)].sval), (*string_table)[j]);
	free((yysemantic_stack_[(7) - (7)].sval));
      } else {
	v1 = new variable((yysemantic_stack_[(7) - (5)].sval), (yysemantic_stack_[(7) - (7)].sval));
	string_table->push_back((yysemantic_stack_[(7) - (7)].sval));
      }
      string_table->push_back((yysemantic_stack_[(7) - (5)].sval));
    }
    i = search_variable_table(v1);
    if(i>=0) {
      delete v1;
      v1 = (*variable_table)[i];
    } else {
      variable_table->push_back(v1);
    }

    i = search_logic_expression_table1(v, v1);
    if(i>=0) {
      (yyval._bool_expression) = (*logic_expression_table1)[i];
      free((yysemantic_stack_[(7) - (5)].sval));
    } else {
			logic_expression *e = new logic_expression(0, v, v1);
			bool_expression *bexpr = new bool_expression(0, e);
      (yyval._bool_expression) = bexpr;
      logic_expression_table1->push_back(bexpr);
    }    
  } else
    (yyval._bool_expression) = NULL;
 }
    break;

  case 453:

/* Line 690 of lalr1.cc  */
#line 2947 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(5) - (1)].sval)!=NULL && (yysemantic_stack_[(5) - (3)].sval)!=NULL && (yysemantic_stack_[(5) - (5)]._expression)!=NULL) {
    int i = search_string_table((yysemantic_stack_[(5) - (1)].sval));
    int j = search_string_table((yysemantic_stack_[(5) - (3)].sval));
    variable *v;
    if(i>=0) {
      if(j>=0) {
	v = new variable((*string_table)[i], (*string_table)[j]);
	free((yysemantic_stack_[(5) - (3)].sval));
      } else {
	v = new variable((*string_table)[i], (yysemantic_stack_[(5) - (3)].sval));
	string_table->push_back((yysemantic_stack_[(5) - (3)].sval));
      }
      free((yysemantic_stack_[(5) - (1)].sval));
    } else {
      if(j>=0) {
	v = new variable((yysemantic_stack_[(5) - (1)].sval), (*string_table)[j]);
	free((yysemantic_stack_[(5) - (3)].sval));
      } else {
	v = new variable((yysemantic_stack_[(5) - (1)].sval), (yysemantic_stack_[(5) - (3)].sval));
	string_table->push_back((yysemantic_stack_[(5) - (3)].sval));
      }
      string_table->push_back((yysemantic_stack_[(5) - (1)].sval));
    }
    i = search_variable_table(v);
    if(i>=0) {
      delete v;
      v = (*variable_table)[i];
    } else {
      variable_table->push_back(v);
    }
    i = search_logic_expression_table1(v, (yysemantic_stack_[(5) - (5)]._expression));
    if(i>=0) {
      (yyval._bool_expression) = (*logic_expression_table1)[i];
      free((yysemantic_stack_[(5) - (5)]._expression));
    } else {
			logic_expression *e = new logic_expression(0, v, (yysemantic_stack_[(5) - (5)]._expression));
			bool_expression *bexpr = new bool_expression(0, e);
      (yyval._bool_expression) = bexpr;
      logic_expression_table1->push_back(bexpr);
    }    
  } else
    (yyval._bool_expression) = NULL;
 }
    break;

  case 454:

/* Line 690 of lalr1.cc  */
#line 2991 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (1)].sval));
  USE((yysemantic_stack_[(5) - (3)].sval));
  USE((yysemantic_stack_[(5) - (5)]._expression));
 }
    break;

  case 455:

/* Line 690 of lalr1.cc  */
#line 2998 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (1)].sval));
  USE((yysemantic_stack_[(5) - (3)].sval));
  USE((yysemantic_stack_[(5) - (5)]._expression));
 }
    break;

  case 456:

/* Line 690 of lalr1.cc  */
#line 3005 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (1)].sval));
  USE((yysemantic_stack_[(5) - (3)].sval));
  USE((yysemantic_stack_[(5) - (5)]._expression));
 }
    break;

  case 457:

/* Line 690 of lalr1.cc  */
#line 3012 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(7) - (3)].sval)!=NULL && (yysemantic_stack_[(7) - (7)].sval)!=NULL) {
    int j = search_string_table((yysemantic_stack_[(7) - (3)].sval));
    variable *v;
    if(j>=0) {
      v = new variable((*string_table)[0], (*string_table)[j]);
      free((yysemantic_stack_[(7) - (3)].sval));
    } else {
      v = new variable((*string_table)[0], (yysemantic_stack_[(7) - (3)].sval));
      string_table->push_back((yysemantic_stack_[(7) - (3)].sval));
    }
    int i = search_variable_table(v);
    if(i>=0) {
      delete v;
      v = (*variable_table)[i];
    } else {
      variable_table->push_back(v);
    }

    j = search_string_table((yysemantic_stack_[(7) - (7)].sval));
    variable *v1;
    if(j>=0) {
      v1 = new variable((*string_table)[0], (*string_table)[j]);
      free((yysemantic_stack_[(7) - (7)].sval));
    } else {
      v1 = new variable((*string_table)[0], (yysemantic_stack_[(7) - (7)].sval));
      string_table->push_back((yysemantic_stack_[(7) - (7)].sval));
    }
    i = search_variable_table(v1);
    if(i>=0) {
      delete v1;
      v1 = (*variable_table)[i];
    } else {
      variable_table->push_back(v1);
    }

    i = search_logic_expression_table1(v, v1);
    if(i>=0) {
      (yyval._bool_expression) = (*logic_expression_table1)[i];
    } else {
			logic_expression *e = new logic_expression(0, v, v1);
			bool_expression *bexpr = new bool_expression(0, e);
      (yyval._bool_expression) = bexpr;
      logic_expression_table1->push_back(bexpr);
    }    
  } else
    (yyval._bool_expression) = NULL;
 }
    break;

  case 458:

/* Line 690 of lalr1.cc  */
#line 3060 "parser/nssis_new.yy"
    {	
  if((yysemantic_stack_[(5) - (3)].sval)!=NULL && (yysemantic_stack_[(5) - (5)]._expression)!=NULL) {
    int j = search_string_table((yysemantic_stack_[(5) - (3)].sval));
    variable *v;
    if(j>=0) {
      v = new variable((*string_table)[0], (*string_table)[j]);
      free((yysemantic_stack_[(5) - (3)].sval));
    } else {
      v = new variable((*string_table)[0], (yysemantic_stack_[(5) - (3)].sval));
      string_table->push_back((yysemantic_stack_[(5) - (3)].sval));
    }
    j = search_variable_table(v);
    if(j>=0) {
      delete v;
      v = (*variable_table)[j];
    } else {
      variable_table->push_back(v);
    }
    j = search_logic_expression_table1(v, (yysemantic_stack_[(5) - (5)]._expression));
    if(j>=0) {
      (yyval._bool_expression) = (*logic_expression_table1)[j];
      free((yysemantic_stack_[(5) - (5)]._expression));
    } else {
			logic_expression *e = new logic_expression(0, v, (yysemantic_stack_[(5) - (5)]._expression));
			bool_expression *bexpr = new bool_expression(0, e);
      (yyval._bool_expression) = bexpr;
      logic_expression_table1->push_back(bexpr);
    }    
  } else
    (yyval._bool_expression) = NULL;
 }
    break;

  case 459:

/* Line 690 of lalr1.cc  */
#line 3091 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (3)].sval));
  USE((yysemantic_stack_[(5) - (5)]._expression));
 }
    break;

  case 460:

/* Line 690 of lalr1.cc  */
#line 3097 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (3)].sval));
  USE((yysemantic_stack_[(5) - (5)]._expression));
 }
    break;

  case 461:

/* Line 690 of lalr1.cc  */
#line 3103 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (3)].sval));
  USE((yysemantic_stack_[(5) - (5)]._expression));
 }
    break;

  case 462:

/* Line 690 of lalr1.cc  */
#line 3109 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(4) - (2)].sval));
  USE((yysemantic_stack_[(4) - (4)]._expression));
 }
    break;

  case 463:

/* Line 690 of lalr1.cc  */
#line 3115 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (3)].sval));
  USE((yysemantic_stack_[(5) - (5)]._expression));
 }
    break;

  case 464:

/* Line 690 of lalr1.cc  */
#line 3121 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(4) - (2)].sval));
  USE((yysemantic_stack_[(4) - (4)]._expression));
 }
    break;

  case 465:

/* Line 690 of lalr1.cc  */
#line 3127 "parser/nssis_new.yy"
    {
  (yyval._bool_expression) = NULL;
  driver.syntax_error = true;
  }
    break;

  case 466:

/* Line 690 of lalr1.cc  */
#line 3134 "parser/nssis_new.yy"
    {
  (yyval.ival) = 1;
 }
    break;

  case 467:

/* Line 690 of lalr1.cc  */
#line 3137 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 468:

/* Line 690 of lalr1.cc  */
#line 3141 "parser/nssis_new.yy"
    {
  (yyval.ival) = 1;
 }
    break;

  case 469:

/* Line 690 of lalr1.cc  */
#line 3144 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 470:

/* Line 690 of lalr1.cc  */
#line 3148 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 471:

/* Line 690 of lalr1.cc  */
#line 3152 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
  }
    break;

  case 474:

/* Line 690 of lalr1.cc  */
#line 3158 "parser/nssis_new.yy"
    {
  driver.syntax_error = true;
  }
    break;

  case 475:

/* Line 690 of lalr1.cc  */
#line 3162 "parser/nssis_new.yy"
    {
  (yyval.ival) = 1;
 }
    break;

  case 476:

/* Line 690 of lalr1.cc  */
#line 3165 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 477:

/* Line 690 of lalr1.cc  */
#line 3169 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 478:

/* Line 690 of lalr1.cc  */
#line 3173 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
  }
    break;

  case 479:

/* Line 690 of lalr1.cc  */
#line 3177 "parser/nssis_new.yy"
    {
  (yyval.ival) = 1;
 }
    break;

  case 480:

/* Line 690 of lalr1.cc  */
#line 3180 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 481:

/* Line 690 of lalr1.cc  */
#line 3184 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 482:

/* Line 690 of lalr1.cc  */
#line 3188 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
  }
    break;

  case 483:

/* Line 690 of lalr1.cc  */
#line 3192 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(4) - (1)].sval)!=NULL && (yysemantic_stack_[(4) - (2)].ival)==1 && (yysemantic_stack_[(4) - (3)].set_string)!=NULL && (yysemantic_stack_[(4) - (4)].ival)==1) {
    (*is_groups)[*(yysemantic_stack_[(4) - (1)].sval)] = *(yysemantic_stack_[(4) - (3)].set_string);
    free((yysemantic_stack_[(4) - (1)].sval));
  }
 }
    break;

  case 484:

/* Line 690 of lalr1.cc  */
#line 3198 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(5) - (2)].sval)!=NULL && (yysemantic_stack_[(5) - (3)].ival)==1 && (yysemantic_stack_[(5) - (4)].set_string)!=NULL && (yysemantic_stack_[(5) - (5)].ival)==1) {
    if(is_groups->find(*(yysemantic_stack_[(5) - (2)].sval)) != is_groups->end() && options["quiet"] == 0)
      cout << "warning: group " << *(yysemantic_stack_[(5) - (2)].sval) << " already exists." << endl; 
    (*is_groups)[*(yysemantic_stack_[(5) - (2)].sval)] = *(yysemantic_stack_[(5) - (4)].set_string);
    free((yysemantic_stack_[(5) - (2)].sval));
  }
 }
    break;

  case 485:

/* Line 690 of lalr1.cc  */
#line 3206 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)].sval)!=NULL && (yysemantic_stack_[(3) - (2)].ival)==1 && (yysemantic_stack_[(3) - (3)].ival)==1) {
    (*is_groups)[*(yysemantic_stack_[(3) - (1)].sval)] = set<string>();
    free((yysemantic_stack_[(3) - (1)].sval));
  }
 }
    break;

  case 486:

/* Line 690 of lalr1.cc  */
#line 3212 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(4) - (2)].sval)!=NULL && (yysemantic_stack_[(4) - (3)].ival)==1 && (yysemantic_stack_[(4) - (4)].ival)==1) {
    if(is_groups->find(*(yysemantic_stack_[(4) - (2)].sval)) != is_groups->end() && options["quiet"] == 0)
      cout << "warning: group " << *(yysemantic_stack_[(4) - (2)].sval) << " already exists." << endl;
    (*is_groups)[*(yysemantic_stack_[(4) - (2)].sval)] = set<string>();
    free((yysemantic_stack_[(4) - (2)].sval));
  }
 }
    break;

  case 487:

/* Line 690 of lalr1.cc  */
#line 3220 "parser/nssis_new.yy"
    {
  driver.syntax_error = true;
  }
    break;

  case 488:

/* Line 690 of lalr1.cc  */
#line 3224 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(1) - (1)].sval)!=NULL) {
    (yyval.set_string) = new set<string>;
    (yyval.set_string)->insert(*(yysemantic_stack_[(1) - (1)].sval));
  } else
    (yyval.set_string) = NULL;
 }
    break;

  case 489:

/* Line 690 of lalr1.cc  */
#line 3231 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)].set_string)!=NULL && (yysemantic_stack_[(3) - (3)].sval)!=NULL) {
    pair<set<string>::iterator, bool> ret = (yysemantic_stack_[(3) - (1)].set_string)->insert(*(yysemantic_stack_[(3) - (3)].sval));
    if(!ret.second && options["quiet"] == 0)
      cout << "warning: agent " << *(yysemantic_stack_[(3) - (3)].sval) << " in group definition is redundant." << endl;
    (yyval.set_string) = (yysemantic_stack_[(3) - (1)].set_string);
  } else
    (yyval.set_string) = NULL;
 }
    break;

  case 490:

/* Line 690 of lalr1.cc  */
#line 3240 "parser/nssis_new.yy"
    {
  (yyval.set_string) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (1)].set_string));USE((yysemantic_stack_[(3) - (3)].sval));
 }
    break;

  case 491:

/* Line 690 of lalr1.cc  */
#line 3245 "parser/nssis_new.yy"
    {
  (yyval.set_string) = NULL;
  driver.syntax_error = true;
  }
    break;

  case 492:

/* Line 690 of lalr1.cc  */
#line 3249 "parser/nssis_new.yy"
    {
  (yyval.sval) = (*string_table)[0];
 }
    break;

  case 493:

/* Line 690 of lalr1.cc  */
#line 3252 "parser/nssis_new.yy"
    {
    int i = search_string_table((yysemantic_stack_[(1) - (1)].sval));
    if(i>=0) {
      (yyval.sval) = (*string_table)[i];
      free((yysemantic_stack_[(1) - (1)].sval));
    } else {
      (yyval.sval) = (yysemantic_stack_[(1) - (1)].sval);
      string_table->push_back((yysemantic_stack_[(1) - (1)].sval));
    }
  }
    break;

  case 494:

/* Line 690 of lalr1.cc  */
#line 3262 "parser/nssis_new.yy"
    {
  (yyval.sval) = NULL;
  driver.syntax_error = true;
  }
    break;

  case 495:

/* Line 690 of lalr1.cc  */
#line 3269 "parser/nssis_new.yy"
    {
  (yyval.ival) = 1;
 }
    break;

  case 496:

/* Line 690 of lalr1.cc  */
#line 3272 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 497:

/* Line 690 of lalr1.cc  */
#line 3276 "parser/nssis_new.yy"
    {
  (yyval.ival) = 1;
 }
    break;

  case 498:

/* Line 690 of lalr1.cc  */
#line 3279 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 499:

/* Line 690 of lalr1.cc  */
#line 3283 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 500:

/* Line 690 of lalr1.cc  */
#line 3287 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
  }
    break;

  case 503:

/* Line 690 of lalr1.cc  */
#line 3294 "parser/nssis_new.yy"
    { 
  if((yysemantic_stack_[(2) - (1)]._fairness_expression)!=NULL)
    is_fairness->push_back((yysemantic_stack_[(2) - (1)]._fairness_expression));
 }
    break;

  case 504:

/* Line 690 of lalr1.cc  */
#line 3298 "parser/nssis_new.yy"
    {
  driver.syntax_error = true;
  USE((yysemantic_stack_[(2) - (1)]._fairness_expression));
 }
    break;

  case 505:

/* Line 690 of lalr1.cc  */
#line 3302 "parser/nssis_new.yy"
    { 
  if((yysemantic_stack_[(3) - (2)]._fairness_expression)!=NULL)
    is_fairness->push_back((yysemantic_stack_[(3) - (2)]._fairness_expression)); 
 }
    break;

  case 506:

/* Line 690 of lalr1.cc  */
#line 3306 "parser/nssis_new.yy"
    {
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (2)]._fairness_expression));
 }
    break;

  case 507:

/* Line 690 of lalr1.cc  */
#line 3310 "parser/nssis_new.yy"
    {
  driver.syntax_error = true;
  }
    break;

  case 508:

/* Line 690 of lalr1.cc  */
#line 3314 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(5) - (2)]._fairness_expression)!=NULL && (yysemantic_stack_[(5) - (4)]._fairness_expression)!=NULL)
    (yyval.dual_fairness_expression) = new pair<fairness_expression *, fairness_expression *>((yysemantic_stack_[(5) - (2)]._fairness_expression), (yysemantic_stack_[(5) - (4)]._fairness_expression));
  else
    (yyval.dual_fairness_expression) = NULL;
 }
    break;

  case 509:

/* Line 690 of lalr1.cc  */
#line 3320 "parser/nssis_new.yy"
    {
  (yyval.dual_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (2)]._fairness_expression));USE((yysemantic_stack_[(5) - (4)]._fairness_expression));
 }
    break;

  case 510:

/* Line 690 of lalr1.cc  */
#line 3325 "parser/nssis_new.yy"
    {
  (yyval.dual_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (2)]._fairness_expression));USE((yysemantic_stack_[(5) - (4)]._fairness_expression));
 }
    break;

  case 511:

/* Line 690 of lalr1.cc  */
#line 3330 "parser/nssis_new.yy"
    {
  (yyval.dual_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (2)]._fairness_expression));USE((yysemantic_stack_[(5) - (4)]._fairness_expression));
 }
    break;

  case 512:

/* Line 690 of lalr1.cc  */
#line 3335 "parser/nssis_new.yy"
    {
  (yyval.dual_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (2)]._fairness_expression));USE((yysemantic_stack_[(5) - (4)]._fairness_expression));
 }
    break;

  case 513:

/* Line 690 of lalr1.cc  */
#line 3340 "parser/nssis_new.yy"
    {
  (yyval.dual_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (2)]._fairness_expression));USE((yysemantic_stack_[(5) - (4)]._fairness_expression));
 }
    break;

  case 514:

/* Line 690 of lalr1.cc  */
#line 3345 "parser/nssis_new.yy"
    {
  (yyval.dual_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (2)]._fairness_expression));USE((yysemantic_stack_[(5) - (4)]._fairness_expression));
 }
    break;

  case 515:

/* Line 690 of lalr1.cc  */
#line 3350 "parser/nssis_new.yy"
    {
  (yyval.dual_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (2)]._fairness_expression));USE((yysemantic_stack_[(5) - (4)]._fairness_expression));
 }
    break;

  case 516:

/* Line 690 of lalr1.cc  */
#line 3355 "parser/nssis_new.yy"
    {
    if((yysemantic_stack_[(5) - (2)].sval)!=NULL && (yysemantic_stack_[(5) - (4)]._fairness_expression)!=NULL) {
      int i = search_string_table((yysemantic_stack_[(5) - (2)].sval));
      if(i>=0) {
	(yyval.ID_fairness_expression) = new pair<string *, fairness_expression *>((*string_table)[i], (yysemantic_stack_[(5) - (4)]._fairness_expression));
	free((yysemantic_stack_[(5) - (2)].sval));
      } else {
	(yyval.ID_fairness_expression) = new pair<string *, fairness_expression *>((yysemantic_stack_[(5) - (2)].sval), (yysemantic_stack_[(5) - (4)]._fairness_expression));
	string_table->push_back((yysemantic_stack_[(5) - (2)].sval));
      }
    } else
      (yyval.ID_fairness_expression) = NULL;
 }
    break;

  case 517:

/* Line 690 of lalr1.cc  */
#line 3368 "parser/nssis_new.yy"
    {
  (yyval.ID_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (2)].sval));
  USE((yysemantic_stack_[(5) - (4)]._fairness_expression));
 }
    break;

  case 518:

/* Line 690 of lalr1.cc  */
#line 3374 "parser/nssis_new.yy"
    {
  (yyval.ID_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (2)].sval));
  USE((yysemantic_stack_[(5) - (4)]._fairness_expression));
 }
    break;

  case 519:

/* Line 690 of lalr1.cc  */
#line 3380 "parser/nssis_new.yy"
    {
  (yyval.ID_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (2)].sval));
  USE((yysemantic_stack_[(5) - (4)]._fairness_expression));
 }
    break;

  case 520:

/* Line 690 of lalr1.cc  */
#line 3386 "parser/nssis_new.yy"
    {
  (yyval.ID_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (2)].sval));
  USE((yysemantic_stack_[(5) - (4)]._fairness_expression));
 }
    break;

  case 521:

/* Line 690 of lalr1.cc  */
#line 3392 "parser/nssis_new.yy"
    {
  (yyval.ID_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (2)].sval));
  USE((yysemantic_stack_[(5) - (4)]._fairness_expression));
 }
    break;

  case 522:

/* Line 690 of lalr1.cc  */
#line 3398 "parser/nssis_new.yy"
    {
  (yyval.ID_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (2)].sval));
  USE((yysemantic_stack_[(5) - (4)]._fairness_expression));
 }
    break;

  case 523:

/* Line 690 of lalr1.cc  */
#line 3404 "parser/nssis_new.yy"
    {
  (yyval.ID_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (2)].sval));
  USE((yysemantic_stack_[(5) - (4)]._fairness_expression));
 }
    break;

  case 524:

/* Line 690 of lalr1.cc  */
#line 3410 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(5) - (4)]._fairness_expression)!=NULL)
    (yyval.ID_fairness_expression) = new pair<string *, fairness_expression *>((*string_table)[0], (yysemantic_stack_[(5) - (4)]._fairness_expression));
  else
    (yyval.ID_fairness_expression) = NULL;
 }
    break;

  case 525:

/* Line 690 of lalr1.cc  */
#line 3416 "parser/nssis_new.yy"
    {
  (yyval.ID_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (4)]._fairness_expression));
 }
    break;

  case 526:

/* Line 690 of lalr1.cc  */
#line 3421 "parser/nssis_new.yy"
    {
  (yyval.ID_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (4)]._fairness_expression));
 }
    break;

  case 527:

/* Line 690 of lalr1.cc  */
#line 3426 "parser/nssis_new.yy"
    {
  (yyval.ID_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (4)]._fairness_expression));
 }
    break;

  case 528:

/* Line 690 of lalr1.cc  */
#line 3431 "parser/nssis_new.yy"
    {
  (yyval.ID_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (4)]._fairness_expression));
 }
    break;

  case 529:

/* Line 690 of lalr1.cc  */
#line 3436 "parser/nssis_new.yy"
    {
  (yyval.ID_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (4)]._fairness_expression));
 }
    break;

  case 530:

/* Line 690 of lalr1.cc  */
#line 3441 "parser/nssis_new.yy"
    {
  (yyval.ID_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (4)]._fairness_expression));
 }
    break;

  case 531:

/* Line 690 of lalr1.cc  */
#line 3446 "parser/nssis_new.yy"
    {
  (yyval.ID_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (4)]._fairness_expression));
 }
    break;

  case 532:

/* Line 690 of lalr1.cc  */
#line 3451 "parser/nssis_new.yy"
    {
    if((yysemantic_stack_[(5) - (2)].sval)!=NULL && (yysemantic_stack_[(5) - (4)]._fairness_expression)!=NULL) {
      int i = search_string_table((yysemantic_stack_[(5) - (2)].sval));
      if(i>=0) {
	(yyval.ID_fairness_expression) = new pair<string *, fairness_expression *>((*string_table)[i], (yysemantic_stack_[(5) - (4)]._fairness_expression));
	free((yysemantic_stack_[(5) - (2)].sval));
      } else {
	(yyval.ID_fairness_expression) = new pair<string *, fairness_expression *>((yysemantic_stack_[(5) - (2)].sval), (yysemantic_stack_[(5) - (4)]._fairness_expression));
	string_table->push_back((yysemantic_stack_[(5) - (2)].sval));
      }
    } else
      (yyval.ID_fairness_expression) = NULL;
 }
    break;

  case 533:

/* Line 690 of lalr1.cc  */
#line 3464 "parser/nssis_new.yy"
    {
  (yyval.ID_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (2)].sval));
  USE((yysemantic_stack_[(5) - (4)]._fairness_expression));
 }
    break;

  case 534:

/* Line 690 of lalr1.cc  */
#line 3470 "parser/nssis_new.yy"
    {
  (yyval.ID_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (2)].sval));
  USE((yysemantic_stack_[(5) - (4)]._fairness_expression));
 }
    break;

  case 535:

/* Line 690 of lalr1.cc  */
#line 3476 "parser/nssis_new.yy"
    {
  (yyval.ID_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (2)].sval));
  USE((yysemantic_stack_[(5) - (4)]._fairness_expression));
 }
    break;

  case 536:

/* Line 690 of lalr1.cc  */
#line 3482 "parser/nssis_new.yy"
    {
  (yyval.ID_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (2)].sval));
  USE((yysemantic_stack_[(5) - (4)]._fairness_expression));
 }
    break;

  case 537:

/* Line 690 of lalr1.cc  */
#line 3488 "parser/nssis_new.yy"
    {
  (yyval.ID_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (2)].sval));
  USE((yysemantic_stack_[(5) - (4)]._fairness_expression));
 }
    break;

  case 538:

/* Line 690 of lalr1.cc  */
#line 3494 "parser/nssis_new.yy"
    {
  (yyval.ID_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (2)].sval));
  USE((yysemantic_stack_[(5) - (4)]._fairness_expression));
 }
    break;

  case 539:

/* Line 690 of lalr1.cc  */
#line 3500 "parser/nssis_new.yy"
    {
  (yyval.ID_fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (2)].sval));
  USE((yysemantic_stack_[(5) - (4)]._fairness_expression));
 }
    break;

  case 540:

/* Line 690 of lalr1.cc  */
#line 3507 "parser/nssis_new.yy"
    { 
  (yyval._fairness_expression) = (yysemantic_stack_[(3) - (2)]._fairness_expression); 
 }
    break;

  case 541:

/* Line 690 of lalr1.cc  */
#line 3510 "parser/nssis_new.yy"
    { 
  (yyval._fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (2)]._fairness_expression));
 }
    break;

  case 542:

/* Line 690 of lalr1.cc  */
#line 3515 "parser/nssis_new.yy"
    { 
  (yyval._fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (2)]._fairness_expression));
 }
    break;

  case 543:

/* Line 690 of lalr1.cc  */
#line 3520 "parser/nssis_new.yy"
    { 
  (yyval._fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (2)]._fairness_expression));
 }
    break;

  case 544:

/* Line 690 of lalr1.cc  */
#line 3525 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)]._fairness_expression)!=NULL && (yysemantic_stack_[(3) - (3)]._fairness_expression)!=NULL)
    (yyval._fairness_expression) = new fairness_expression(1, (yysemantic_stack_[(3) - (1)]._fairness_expression), (yysemantic_stack_[(3) - (3)]._fairness_expression));
  else
    (yyval._fairness_expression) = NULL;
 }
    break;

  case 545:

/* Line 690 of lalr1.cc  */
#line 3531 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)]._fairness_expression)!=NULL && (yysemantic_stack_[(3) - (3)]._fairness_expression)!=NULL)
    (yyval._fairness_expression) = new fairness_expression(2, (yysemantic_stack_[(3) - (1)]._fairness_expression), (yysemantic_stack_[(3) - (3)]._fairness_expression));
  else
    (yyval._fairness_expression) = NULL;
 }
    break;

  case 546:

/* Line 690 of lalr1.cc  */
#line 3537 "parser/nssis_new.yy"
    {
  (yyval._fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (1)]._fairness_expression));USE((yysemantic_stack_[(3) - (3)]._fairness_expression));
 }
    break;

  case 547:

/* Line 690 of lalr1.cc  */
#line 3542 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(2) - (2)]._fairness_expression)!=NULL)
    (yyval._fairness_expression) = new fairness_expression(3, (yysemantic_stack_[(2) - (2)]._fairness_expression));
  else
    (yyval._fairness_expression) = NULL;
 }
    break;

  case 548:

/* Line 690 of lalr1.cc  */
#line 3548 "parser/nssis_new.yy"
    {
  (yyval._fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(2) - (2)]._fairness_expression));
 }
    break;

  case 549:

/* Line 690 of lalr1.cc  */
#line 3553 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)]._fairness_expression)!=NULL && (yysemantic_stack_[(3) - (3)]._fairness_expression)!=NULL)
    (yyval._fairness_expression) = new fairness_expression(4, (yysemantic_stack_[(3) - (1)]._fairness_expression), (yysemantic_stack_[(3) - (3)]._fairness_expression));
  else
    (yyval._fairness_expression) = NULL;
 }
    break;

  case 550:

/* Line 690 of lalr1.cc  */
#line 3559 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(2) - (2)]._fairness_expression)!=NULL)
    (yyval._fairness_expression) = new fairness_expression(10, (yysemantic_stack_[(2) - (2)]._fairness_expression));
  else
    (yyval._fairness_expression) = NULL;
 }
    break;

  case 551:

/* Line 690 of lalr1.cc  */
#line 3565 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(2) - (2)]._fairness_expression)!=NULL)
    (yyval._fairness_expression) = new fairness_expression(11, (yysemantic_stack_[(2) - (2)]._fairness_expression));
  else
    (yyval._fairness_expression) = NULL;
  }
    break;

  case 552:

/* Line 690 of lalr1.cc  */
#line 3571 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(2) - (2)]._fairness_expression)!=NULL)
    (yyval._fairness_expression) = new fairness_expression(12, (yysemantic_stack_[(2) - (2)]._fairness_expression));
  else
    (yyval._fairness_expression) = NULL;
 }
    break;

  case 553:

/* Line 690 of lalr1.cc  */
#line 3577 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(2) - (2)]._fairness_expression)!=NULL)
    (yyval._fairness_expression) = new fairness_expression(13, (yysemantic_stack_[(2) - (2)]._fairness_expression));
  else
    (yyval._fairness_expression) = NULL;
 }
    break;

  case 554:

/* Line 690 of lalr1.cc  */
#line 3583 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(2) - (2)]._fairness_expression)!=NULL)
    (yyval._fairness_expression) = new fairness_expression(14, (yysemantic_stack_[(2) - (2)]._fairness_expression));
  else
    (yyval._fairness_expression) = NULL;
 }
    break;

  case 555:

/* Line 690 of lalr1.cc  */
#line 3589 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(2) - (2)]._fairness_expression)!=NULL)
    (yyval._fairness_expression) = new fairness_expression(15, (yysemantic_stack_[(2) - (2)]._fairness_expression));
  else
    (yyval._fairness_expression) = NULL;
 }
    break;

  case 556:

/* Line 690 of lalr1.cc  */
#line 3595 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(2) - (2)].dual_fairness_expression)!=NULL) {
    (yyval._fairness_expression) = new fairness_expression(16, (yysemantic_stack_[(2) - (2)].dual_fairness_expression)->first, (yysemantic_stack_[(2) - (2)].dual_fairness_expression)->second);
    free((yysemantic_stack_[(2) - (2)].dual_fairness_expression));
  }
  else
    (yyval._fairness_expression) = NULL;
 }
    break;

  case 557:

/* Line 690 of lalr1.cc  */
#line 3603 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(2) - (2)].dual_fairness_expression)!=NULL) {
    (yyval._fairness_expression) = new fairness_expression(17, (yysemantic_stack_[(2) - (2)].dual_fairness_expression)->first, (yysemantic_stack_[(2) - (2)].dual_fairness_expression)->second);
    free((yysemantic_stack_[(2) - (2)].dual_fairness_expression));
  }
  else
    (yyval._fairness_expression) = NULL;
 }
    break;

  case 558:

/* Line 690 of lalr1.cc  */
#line 3611 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(2) - (2)].ID_fairness_expression)!=NULL) {
    atomic_proposition *ap = new atomic_proposition((yysemantic_stack_[(2) - (2)].ID_fairness_expression)->first);
    fairness_expression *a = new fairness_expression(ap);
    (yyval._fairness_expression) = new fairness_expression(30, a, (yysemantic_stack_[(2) - (2)].ID_fairness_expression)->second);
    free((yysemantic_stack_[(2) - (2)].ID_fairness_expression));
  } else
    (yyval._fairness_expression) = NULL;
 }
    break;

  case 559:

/* Line 690 of lalr1.cc  */
#line 3620 "parser/nssis_new.yy"
    {
  // Knowledge in a group (everybody knows)
  if((yysemantic_stack_[(2) - (2)].ID_fairness_expression)!=NULL) {
    atomic_proposition *ap = new atomic_proposition((yysemantic_stack_[(2) - (2)].ID_fairness_expression)->first);
    fairness_expression *a = new fairness_expression(ap);
    (yyval._fairness_expression) = new fairness_expression(31, a, (yysemantic_stack_[(2) - (2)].ID_fairness_expression)->second);
    free((yysemantic_stack_[(2) - (2)].ID_fairness_expression));
  } else
    (yyval._fairness_expression) = NULL;
 }
    break;

  case 560:

/* Line 690 of lalr1.cc  */
#line 3630 "parser/nssis_new.yy"
    {
  // Common knowledge in a group
  if((yysemantic_stack_[(2) - (2)].ID_fairness_expression)!=NULL) {
    atomic_proposition *ap = new atomic_proposition((yysemantic_stack_[(2) - (2)].ID_fairness_expression)->first);
    fairness_expression *a = new fairness_expression(ap);
    (yyval._fairness_expression) = new fairness_expression(32, a, (yysemantic_stack_[(2) - (2)].ID_fairness_expression)->second);
    free((yysemantic_stack_[(2) - (2)].ID_fairness_expression));
  } else
    (yyval._fairness_expression) = NULL;
 }
    break;

  case 561:

/* Line 690 of lalr1.cc  */
#line 3640 "parser/nssis_new.yy"
    {
  // deontic operator
  if((yysemantic_stack_[(2) - (2)].ID_fairness_expression)!=NULL) {
    atomic_proposition *ap = new atomic_proposition((yysemantic_stack_[(2) - (2)].ID_fairness_expression)->first);
    fairness_expression *a = new fairness_expression(ap);
    (yyval._fairness_expression) = new fairness_expression(40, a, (yysemantic_stack_[(2) - (2)].ID_fairness_expression)->second);
    free((yysemantic_stack_[(2) - (2)].ID_fairness_expression));
  } else
    (yyval._fairness_expression) = NULL;
 }
    break;

  case 562:

/* Line 690 of lalr1.cc  */
#line 3650 "parser/nssis_new.yy"
    {
  // Distributed knowledge in a group
  if((yysemantic_stack_[(2) - (2)].ID_fairness_expression)!=NULL) {
    atomic_proposition *ap = new atomic_proposition((yysemantic_stack_[(2) - (2)].ID_fairness_expression)->first);
    fairness_expression *a = new fairness_expression(ap);
    (yyval._fairness_expression) = new fairness_expression(42, a, (yysemantic_stack_[(2) - (2)].ID_fairness_expression)->second);
    free((yysemantic_stack_[(2) - (2)].ID_fairness_expression));
  } else
    (yyval._fairness_expression) = NULL;
 }
    break;

  case 563:

/* Line 690 of lalr1.cc  */
#line 3660 "parser/nssis_new.yy"
    { 
  (yyval._fairness_expression) = NULL;
  if((yysemantic_stack_[(2) - (2)].ID_fairness_expression) != NULL)
    free((yysemantic_stack_[(2) - (2)].ID_fairness_expression));
  driver.syntax_error = true;
 }
    break;

  case 564:

/* Line 690 of lalr1.cc  */
#line 3666 "parser/nssis_new.yy"
    { 
  (yyval._fairness_expression) = NULL;
  if((yysemantic_stack_[(2) - (2)].ID_fairness_expression) != NULL)
    free((yysemantic_stack_[(2) - (2)].ID_fairness_expression));
  driver.syntax_error = true;
 }
    break;

  case 565:

/* Line 690 of lalr1.cc  */
#line 3672 "parser/nssis_new.yy"
    {	
  if((yysemantic_stack_[(1) - (1)].sval)!=NULL) {
    int i = search_string_table((yysemantic_stack_[(1) - (1)].sval));
    atomic_proposition *ap;
    if(i>=0) {
      ap = new atomic_proposition((*string_table)[i]);
      free((yysemantic_stack_[(1) - (1)].sval));
    } else {
      ap = new atomic_proposition((yysemantic_stack_[(1) - (1)].sval));
      string_table->push_back((yysemantic_stack_[(1) - (1)].sval));
    }
    (yyval._fairness_expression) = new fairness_expression(ap);
  } else
    (yyval._fairness_expression) = NULL;
  }
    break;

  case 566:

/* Line 690 of lalr1.cc  */
#line 3687 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)].sval)!=NULL) {
    string *newname = new string(*(yysemantic_stack_[(3) - (1)].sval) + ".GreenStates");
    atomic_proposition *ap;
    int i = search_string_table(newname);
    if(i>=0) {
      ap = new atomic_proposition((*string_table)[i]);
      free(newname);
    } else {
      ap = new atomic_proposition(newname);
      string_table->push_back(newname);
    }
    free((yysemantic_stack_[(3) - (1)].sval));
    (yyval._fairness_expression) = new fairness_expression(ap);
  } else
    (yyval._fairness_expression) = NULL;
 }
    break;

  case 567:

/* Line 690 of lalr1.cc  */
#line 3704 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)].sval)!=NULL) {
    string *newname = new string(*(yysemantic_stack_[(3) - (1)].sval) + ".RedStates");
    atomic_proposition *ap;
    int i = search_string_table(newname);
    if(i>=0) {
      ap = new atomic_proposition((*string_table)[i]);
      free(newname);
    } else {
      ap = new atomic_proposition(newname);
      string_table->push_back(newname);
    }
    free((yysemantic_stack_[(3) - (1)].sval));
    (yyval._fairness_expression) = new fairness_expression(ap);
  } else
    (yyval._fairness_expression) = NULL;
 }
    break;

  case 568:

/* Line 690 of lalr1.cc  */
#line 3721 "parser/nssis_new.yy"
    {
    string *newname = new string("Environment.GreenStates");
    atomic_proposition *ap;
    int i = search_string_table(newname);
    if(i>=0) {
      ap = new atomic_proposition((*string_table)[i]);
      free(newname);
    } else {
      ap = new atomic_proposition(newname);
      string_table->push_back(newname);
    }
    (yyval._fairness_expression) = new fairness_expression(ap);
 }
    break;

  case 569:

/* Line 690 of lalr1.cc  */
#line 3734 "parser/nssis_new.yy"
    {
  string *newname = new string("Environment.RedStates");
  atomic_proposition *ap;
  int i = search_string_table(newname);
  if(i>=0) {
    ap = new atomic_proposition((*string_table)[i]);
    free(newname);
  } else {
    ap = new atomic_proposition(newname);
    string_table->push_back(newname);
  }
  (yyval._fairness_expression) = new fairness_expression(ap);
 }
    break;

  case 570:

/* Line 690 of lalr1.cc  */
#line 3747 "parser/nssis_new.yy"
    {
  (yyval._fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (1)].sval));
 }
    break;

  case 571:

/* Line 690 of lalr1.cc  */
#line 3752 "parser/nssis_new.yy"
    {
  (yyval._fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (1)].sval));
 }
    break;

  case 572:

/* Line 690 of lalr1.cc  */
#line 3757 "parser/nssis_new.yy"
    {
  (yyval._fairness_expression) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (1)].sval));
 }
    break;

  case 573:

/* Line 690 of lalr1.cc  */
#line 3762 "parser/nssis_new.yy"
    {
  (yyval._fairness_expression) = NULL;
  driver.syntax_error = true;
  }
    break;

  case 574:

/* Line 690 of lalr1.cc  */
#line 3769 "parser/nssis_new.yy"
    {
  (yyval.ival) = 1;
 }
    break;

  case 575:

/* Line 690 of lalr1.cc  */
#line 3772 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 576:

/* Line 690 of lalr1.cc  */
#line 3776 "parser/nssis_new.yy"
    {
  (yyval.ival) = 1;
 }
    break;

  case 577:

/* Line 690 of lalr1.cc  */
#line 3779 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 578:

/* Line 690 of lalr1.cc  */
#line 3783 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
 }
    break;

  case 579:

/* Line 690 of lalr1.cc  */
#line 3787 "parser/nssis_new.yy"
    {
  (yyval.ival) = 0;
  driver.syntax_error = true;
  }
    break;

  case 581:

/* Line 690 of lalr1.cc  */
#line 3793 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (2)]._modal_formula)!=NULL) {
    ((yysemantic_stack_[(3) - (1)].boolean_flag) ? is_perfect_recall_formulae : is_formulae)->push_back(*(yysemantic_stack_[(3) - (2)]._modal_formula));
  }
 }
    break;

  case 582:

/* Line 690 of lalr1.cc  */
#line 3798 "parser/nssis_new.yy"
    {
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (1)].boolean_flag));
  USE((yysemantic_stack_[(3) - (2)]._modal_formula));
 }
    break;

  case 583:

/* Line 690 of lalr1.cc  */
#line 3803 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(4) - (3)]._modal_formula)!=NULL) {
    ((yysemantic_stack_[(4) - (2)].boolean_flag) ? is_perfect_recall_formulae : is_formulae)->push_back(*(yysemantic_stack_[(4) - (3)]._modal_formula));
  }
 }
    break;

  case 584:

/* Line 690 of lalr1.cc  */
#line 3808 "parser/nssis_new.yy"
    {
  driver.syntax_error = true;
  USE((yysemantic_stack_[(4) - (2)].boolean_flag));
  USE((yysemantic_stack_[(4) - (3)]._modal_formula));
 }
    break;

  case 585:

/* Line 690 of lalr1.cc  */
#line 3813 "parser/nssis_new.yy"
    {
  driver.syntax_error = true;
  }
    break;

  case 586:

/* Line 690 of lalr1.cc  */
#line 3817 "parser/nssis_new.yy"
    {
    int i = search_string_table((yysemantic_stack_[(3) - (2)].sval));
    if(i>=0) {
      (yyval.sval) = (*string_table)[i];
      free((yysemantic_stack_[(3) - (2)].sval));
    } else {
      (yyval.sval) = (yysemantic_stack_[(3) - (2)].sval);
      string_table->push_back((yysemantic_stack_[(3) - (2)].sval));
    }
 }
    break;

  case 587:

/* Line 690 of lalr1.cc  */
#line 3827 "parser/nssis_new.yy"
    {
  (yyval.sval) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (2)].sval));
 }
    break;

  case 588:

/* Line 690 of lalr1.cc  */
#line 3832 "parser/nssis_new.yy"
    {
  (yyval.sval) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (2)].sval));
 }
    break;

  case 589:

/* Line 690 of lalr1.cc  */
#line 3837 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(5) - (2)]._modal_formula)!=NULL && (yysemantic_stack_[(5) - (4)]._modal_formula)!=NULL)
    (yyval.dual_modal_formula) = new pair<modal_formula *, modal_formula *>((yysemantic_stack_[(5) - (2)]._modal_formula), (yysemantic_stack_[(5) - (4)]._modal_formula));
  else
    (yyval.dual_modal_formula) = NULL;
 }
    break;

  case 590:

/* Line 690 of lalr1.cc  */
#line 3848 "parser/nssis_new.yy"
    {
  (yyval.dual_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (2)]._modal_formula));USE((yysemantic_stack_[(5) - (4)]._modal_formula));
 }
    break;

  case 591:

/* Line 690 of lalr1.cc  */
#line 3853 "parser/nssis_new.yy"
    {
  (yyval.dual_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (2)]._modal_formula));USE((yysemantic_stack_[(5) - (4)]._modal_formula));
 }
    break;

  case 592:

/* Line 690 of lalr1.cc  */
#line 3858 "parser/nssis_new.yy"
    {
  (yyval.dual_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (2)]._modal_formula));USE((yysemantic_stack_[(5) - (4)]._modal_formula));
 }
    break;

  case 593:

/* Line 690 of lalr1.cc  */
#line 3863 "parser/nssis_new.yy"
    {
  (yyval.dual_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (2)]._modal_formula));USE((yysemantic_stack_[(5) - (4)]._modal_formula));
 }
    break;

  case 594:

/* Line 690 of lalr1.cc  */
#line 3868 "parser/nssis_new.yy"
    {
  (yyval.dual_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (2)]._modal_formula));USE((yysemantic_stack_[(5) - (4)]._modal_formula));
 }
    break;

  case 595:

/* Line 690 of lalr1.cc  */
#line 3873 "parser/nssis_new.yy"
    {
  (yyval.dual_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (2)]._modal_formula));USE((yysemantic_stack_[(5) - (4)]._modal_formula));
 }
    break;

  case 596:

/* Line 690 of lalr1.cc  */
#line 3878 "parser/nssis_new.yy"
    {
    if((yysemantic_stack_[(5) - (2)].sval)!=NULL && (yysemantic_stack_[(5) - (4)]._modal_formula)!=NULL) {
      int i = search_string_table((yysemantic_stack_[(5) - (2)].sval));
      if(i>=0) {
	(yyval.ID_modal_formula) = new pair<string *, modal_formula *>((*string_table)[i], (yysemantic_stack_[(5) - (4)]._modal_formula));
	free((yysemantic_stack_[(5) - (2)].sval));
      } else {
	(yyval.ID_modal_formula) = new pair<string *, modal_formula *>((yysemantic_stack_[(5) - (2)].sval), (yysemantic_stack_[(5) - (4)]._modal_formula));
	string_table->push_back((yysemantic_stack_[(5) - (2)].sval));
      }
    } else
    (yyval.ID_modal_formula) = NULL;
 }
    break;

  case 597:

/* Line 690 of lalr1.cc  */
#line 3891 "parser/nssis_new.yy"
    {
  (yyval.ID_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (2)].sval));
  USE((yysemantic_stack_[(5) - (4)]._modal_formula));
 }
    break;

  case 598:

/* Line 690 of lalr1.cc  */
#line 3897 "parser/nssis_new.yy"
    {
  (yyval.ID_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (2)].sval));
  USE((yysemantic_stack_[(5) - (4)]._modal_formula));
 }
    break;

  case 599:

/* Line 690 of lalr1.cc  */
#line 3903 "parser/nssis_new.yy"
    {
  (yyval.ID_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (2)].sval));
  USE((yysemantic_stack_[(5) - (4)]._modal_formula));
 }
    break;

  case 600:

/* Line 690 of lalr1.cc  */
#line 3909 "parser/nssis_new.yy"
    {
  (yyval.ID_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (2)].sval));
  USE((yysemantic_stack_[(5) - (4)]._modal_formula));
 }
    break;

  case 601:

/* Line 690 of lalr1.cc  */
#line 3915 "parser/nssis_new.yy"
    {
  (yyval.ID_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (2)].sval));
  USE((yysemantic_stack_[(5) - (4)]._modal_formula));
 }
    break;

  case 602:

/* Line 690 of lalr1.cc  */
#line 3921 "parser/nssis_new.yy"
    {
  (yyval.ID_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (2)].sval));
  USE((yysemantic_stack_[(5) - (4)]._modal_formula));
 }
    break;

  case 603:

/* Line 690 of lalr1.cc  */
#line 3927 "parser/nssis_new.yy"
    {
  (yyval.ID_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (2)].sval));
  USE((yysemantic_stack_[(5) - (4)]._modal_formula));
 }
    break;

  case 604:

/* Line 690 of lalr1.cc  */
#line 3933 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(5) - (4)]._modal_formula)!=NULL)
    (yyval.ID_modal_formula) = new pair<string *, modal_formula *>((*string_table)[0], (yysemantic_stack_[(5) - (4)]._modal_formula));
  else
    (yyval.ID_modal_formula) = NULL;
 }
    break;

  case 605:

/* Line 690 of lalr1.cc  */
#line 3939 "parser/nssis_new.yy"
    {
  (yyval.ID_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (4)]._modal_formula));
 }
    break;

  case 606:

/* Line 690 of lalr1.cc  */
#line 3944 "parser/nssis_new.yy"
    {
  (yyval.ID_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (4)]._modal_formula));
 }
    break;

  case 607:

/* Line 690 of lalr1.cc  */
#line 3949 "parser/nssis_new.yy"
    {
  (yyval.ID_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (4)]._modal_formula));
 }
    break;

  case 608:

/* Line 690 of lalr1.cc  */
#line 3954 "parser/nssis_new.yy"
    {
  (yyval.ID_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (4)]._modal_formula));
 }
    break;

  case 609:

/* Line 690 of lalr1.cc  */
#line 3959 "parser/nssis_new.yy"
    {
  (yyval.ID_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (4)]._modal_formula));
 }
    break;

  case 610:

/* Line 690 of lalr1.cc  */
#line 3964 "parser/nssis_new.yy"
    {
  (yyval.ID_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (4)]._modal_formula));
 }
    break;

  case 611:

/* Line 690 of lalr1.cc  */
#line 3969 "parser/nssis_new.yy"
    {
  (yyval.ID_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (4)]._modal_formula));
 }
    break;

  case 612:

/* Line 690 of lalr1.cc  */
#line 3974 "parser/nssis_new.yy"
    {
    if((yysemantic_stack_[(5) - (2)].sval)!=NULL && (yysemantic_stack_[(5) - (4)]._modal_formula)!=NULL) {
      int i = search_string_table((yysemantic_stack_[(5) - (2)].sval));
      if(i>=0) {
	(yyval.ID_modal_formula) = new pair<string *, modal_formula *>((*string_table)[i], (yysemantic_stack_[(5) - (4)]._modal_formula));
	free((yysemantic_stack_[(5) - (2)].sval));
      } else {
	(yyval.ID_modal_formula) = new pair<string *, modal_formula *>((yysemantic_stack_[(5) - (2)].sval), (yysemantic_stack_[(5) - (4)]._modal_formula));
	string_table->push_back((yysemantic_stack_[(5) - (2)].sval));
      }
    } else
      (yyval.ID_modal_formula) = NULL;
 }
    break;

  case 613:

/* Line 690 of lalr1.cc  */
#line 3987 "parser/nssis_new.yy"
    {
  (yyval.ID_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (2)].sval));
  USE((yysemantic_stack_[(5) - (4)]._modal_formula));
 }
    break;

  case 614:

/* Line 690 of lalr1.cc  */
#line 3993 "parser/nssis_new.yy"
    {
  (yyval.ID_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (2)].sval));
  USE((yysemantic_stack_[(5) - (4)]._modal_formula));
 }
    break;

  case 615:

/* Line 690 of lalr1.cc  */
#line 3999 "parser/nssis_new.yy"
    {
  (yyval.ID_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (2)].sval));
  USE((yysemantic_stack_[(5) - (4)]._modal_formula));
 }
    break;

  case 616:

/* Line 690 of lalr1.cc  */
#line 4005 "parser/nssis_new.yy"
    {
  (yyval.ID_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (2)].sval));
  USE((yysemantic_stack_[(5) - (4)]._modal_formula));
 }
    break;

  case 617:

/* Line 690 of lalr1.cc  */
#line 4011 "parser/nssis_new.yy"
    {
  (yyval.ID_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (2)].sval));
  USE((yysemantic_stack_[(5) - (4)]._modal_formula));
 }
    break;

  case 618:

/* Line 690 of lalr1.cc  */
#line 4017 "parser/nssis_new.yy"
    {
  (yyval.ID_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (2)].sval));
  USE((yysemantic_stack_[(5) - (4)]._modal_formula));
 }
    break;

  case 619:

/* Line 690 of lalr1.cc  */
#line 4023 "parser/nssis_new.yy"
    {
  (yyval.ID_modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(5) - (2)].sval));
  USE((yysemantic_stack_[(5) - (4)]._modal_formula));
 }
    break;

  case 620:

/* Line 690 of lalr1.cc  */
#line 4030 "parser/nssis_new.yy"
    { 
  (yyval._modal_formula) = (yysemantic_stack_[(3) - (2)]._modal_formula); 
 }
    break;

  case 621:

/* Line 690 of lalr1.cc  */
#line 4033 "parser/nssis_new.yy"
    { 
  (yyval._modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (2)]._modal_formula));
 }
    break;

  case 622:

/* Line 690 of lalr1.cc  */
#line 4038 "parser/nssis_new.yy"
    { 
  (yyval._modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (2)]._modal_formula));
 }
    break;

  case 623:

/* Line 690 of lalr1.cc  */
#line 4043 "parser/nssis_new.yy"
    { 
  (yyval._modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (2)]._modal_formula));
 }
    break;

  case 624:

/* Line 690 of lalr1.cc  */
#line 4048 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)]._modal_formula)!=NULL && (yysemantic_stack_[(3) - (3)]._modal_formula)!=NULL)
    (yyval._modal_formula) = new modal_formula(1, (yysemantic_stack_[(3) - (1)]._modal_formula), (yysemantic_stack_[(3) - (3)]._modal_formula));
  else
    (yyval._modal_formula) = NULL;
 }
    break;

  case 625:

/* Line 690 of lalr1.cc  */
#line 4054 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)]._modal_formula)!=NULL && (yysemantic_stack_[(3) - (3)]._modal_formula)!=NULL)
    (yyval._modal_formula) = new modal_formula(2, (yysemantic_stack_[(3) - (1)]._modal_formula), (yysemantic_stack_[(3) - (3)]._modal_formula));
  else
    (yyval._modal_formula) = NULL;
 }
    break;

  case 626:

/* Line 690 of lalr1.cc  */
#line 4060 "parser/nssis_new.yy"
    {
  (yyval._modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (1)]._modal_formula));USE((yysemantic_stack_[(3) - (3)]._modal_formula));
 }
    break;

  case 627:

/* Line 690 of lalr1.cc  */
#line 4065 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(2) - (2)]._modal_formula)!=NULL)
    (yyval._modal_formula) = new modal_formula(3, (yysemantic_stack_[(2) - (2)]._modal_formula));
  else
    (yyval._modal_formula) = NULL;
 }
    break;

  case 628:

/* Line 690 of lalr1.cc  */
#line 4071 "parser/nssis_new.yy"
    {
  (yyval._modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(2) - (2)]._modal_formula));
 }
    break;

  case 629:

/* Line 690 of lalr1.cc  */
#line 4076 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)]._modal_formula)!=NULL && (yysemantic_stack_[(3) - (3)]._modal_formula)!=NULL)
    (yyval._modal_formula) = new modal_formula(4, (yysemantic_stack_[(3) - (1)]._modal_formula), (yysemantic_stack_[(3) - (3)]._modal_formula));
  else
    (yyval._modal_formula) = NULL;
 }
    break;

  case 630:

/* Line 690 of lalr1.cc  */
#line 4082 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(2) - (2)]._modal_formula)!=NULL)
    (yyval._modal_formula) = new modal_formula(10, (yysemantic_stack_[(2) - (2)]._modal_formula));
  else
    (yyval._modal_formula) = NULL;
 }
    break;

  case 631:

/* Line 690 of lalr1.cc  */
#line 4088 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(2) - (2)]._modal_formula)!=NULL)
    (yyval._modal_formula) = new modal_formula(11, (yysemantic_stack_[(2) - (2)]._modal_formula));
  else
    (yyval._modal_formula) = NULL;
  }
    break;

  case 632:

/* Line 690 of lalr1.cc  */
#line 4094 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(2) - (2)]._modal_formula)!=NULL)
    (yyval._modal_formula) = new modal_formula(12, (yysemantic_stack_[(2) - (2)]._modal_formula));
  else
    (yyval._modal_formula) = NULL;
 }
    break;

  case 633:

/* Line 690 of lalr1.cc  */
#line 4100 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(2) - (2)]._modal_formula)!=NULL)
    (yyval._modal_formula) = new modal_formula(13, (yysemantic_stack_[(2) - (2)]._modal_formula));
  else
    (yyval._modal_formula) = NULL;
 }
    break;

  case 634:

/* Line 690 of lalr1.cc  */
#line 4106 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(2) - (2)]._modal_formula)!=NULL)
    (yyval._modal_formula) = new modal_formula(14, (yysemantic_stack_[(2) - (2)]._modal_formula));
  else
    (yyval._modal_formula) = NULL;
 }
    break;

  case 635:

/* Line 690 of lalr1.cc  */
#line 4112 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(2) - (2)]._modal_formula)!=NULL)
    (yyval._modal_formula) = new modal_formula(15, (yysemantic_stack_[(2) - (2)]._modal_formula));
  else
    (yyval._modal_formula) = NULL;
 }
    break;

  case 636:

/* Line 690 of lalr1.cc  */
#line 4118 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(2) - (2)].dual_modal_formula)!=NULL) {
    (yyval._modal_formula) = new modal_formula(16, (yysemantic_stack_[(2) - (2)].dual_modal_formula)->first, (yysemantic_stack_[(2) - (2)].dual_modal_formula)->second);
    free((yysemantic_stack_[(2) - (2)].dual_modal_formula));
  }
  else
    (yyval._modal_formula) = NULL;
 }
    break;

  case 637:

/* Line 690 of lalr1.cc  */
#line 4126 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(2) - (2)].dual_modal_formula)!=NULL) {
    (yyval._modal_formula) = new modal_formula(17, (yysemantic_stack_[(2) - (2)].dual_modal_formula)->first, (yysemantic_stack_[(2) - (2)].dual_modal_formula)->second);
    free((yysemantic_stack_[(2) - (2)].dual_modal_formula));
  }
  else
    (yyval._modal_formula) = NULL;
 }
    break;

  case 638:

/* Line 690 of lalr1.cc  */
#line 4134 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(2) - (2)].ID_modal_formula)!=NULL) {
    atomic_proposition *ap = new atomic_proposition((yysemantic_stack_[(2) - (2)].ID_modal_formula)->first);
    modal_formula *a = new modal_formula(ap);
    (yyval._modal_formula) = new modal_formula(30, a, (yysemantic_stack_[(2) - (2)].ID_modal_formula)->second);
    free((yysemantic_stack_[(2) - (2)].ID_modal_formula));
  } else
    (yyval._modal_formula) = NULL;
 }
    break;

  case 639:

/* Line 690 of lalr1.cc  */
#line 4143 "parser/nssis_new.yy"
    {
  // Knowledge in a group (everybody knows)
  if((yysemantic_stack_[(2) - (2)].ID_modal_formula)!=NULL) {
    atomic_proposition *ap = new atomic_proposition((yysemantic_stack_[(2) - (2)].ID_modal_formula)->first);
    modal_formula *a = new modal_formula(ap);
    (yyval._modal_formula) = new modal_formula(31, a, (yysemantic_stack_[(2) - (2)].ID_modal_formula)->second);
    free((yysemantic_stack_[(2) - (2)].ID_modal_formula));
  } else
    (yyval._modal_formula) = NULL;
 }
    break;

  case 640:

/* Line 690 of lalr1.cc  */
#line 4153 "parser/nssis_new.yy"
    {
  // Common knowledge in a group
  if((yysemantic_stack_[(2) - (2)].ID_modal_formula)!=NULL) {
    atomic_proposition *ap = new atomic_proposition((yysemantic_stack_[(2) - (2)].ID_modal_formula)->first);
    modal_formula *a = new modal_formula(ap);
    (yyval._modal_formula) = new modal_formula(32, a, (yysemantic_stack_[(2) - (2)].ID_modal_formula)->second);
    free((yysemantic_stack_[(2) - (2)].ID_modal_formula));
  } else
    (yyval._modal_formula) = NULL;
 }
    break;

  case 641:

/* Line 690 of lalr1.cc  */
#line 4163 "parser/nssis_new.yy"
    {
  // deontic operator
  if((yysemantic_stack_[(2) - (2)].ID_modal_formula)!=NULL) {
    atomic_proposition *ap = new atomic_proposition((yysemantic_stack_[(2) - (2)].ID_modal_formula)->first);
    modal_formula *a = new modal_formula(ap);
    (yyval._modal_formula) = new modal_formula(40, a, (yysemantic_stack_[(2) - (2)].ID_modal_formula)->second);
    free((yysemantic_stack_[(2) - (2)].ID_modal_formula));
  } else
    (yyval._modal_formula) = NULL;
 }
    break;

  case 642:

/* Line 690 of lalr1.cc  */
#line 4173 "parser/nssis_new.yy"
    {
  // Distributed knowledge in a group
  if((yysemantic_stack_[(2) - (2)].ID_modal_formula)!=NULL) {
    atomic_proposition *ap = new atomic_proposition((yysemantic_stack_[(2) - (2)].ID_modal_formula)->first);
    modal_formula *a = new modal_formula(ap);
    (yyval._modal_formula) = new modal_formula(42, a, (yysemantic_stack_[(2) - (2)].ID_modal_formula)->second);
    free((yysemantic_stack_[(2) - (2)].ID_modal_formula));
  } else
    (yyval._modal_formula) = NULL;
 }
    break;

  case 643:

/* Line 690 of lalr1.cc  */
#line 4183 "parser/nssis_new.yy"
    { 
  (yyval._modal_formula) = NULL;
  driver.syntax_error = true;
 }
    break;

  case 644:

/* Line 690 of lalr1.cc  */
#line 4187 "parser/nssis_new.yy"
    { 
  (yyval._modal_formula) = NULL;
  driver.syntax_error = true;
 }
    break;

  case 645:

/* Line 690 of lalr1.cc  */
#line 4191 "parser/nssis_new.yy"
    {
  // ATL X operator
  if((yysemantic_stack_[(3) - (1)].sval)!=NULL && (yysemantic_stack_[(3) - (3)]._modal_formula)!=NULL) {
    atomic_proposition *ap = new atomic_proposition((yysemantic_stack_[(3) - (1)].sval));
    modal_formula *a = new modal_formula(ap);
    (yyval._modal_formula) = new modal_formula(45, a, (yysemantic_stack_[(3) - (3)]._modal_formula));
  } else
    (yyval._modal_formula) = NULL;
 }
    break;

  case 646:

/* Line 690 of lalr1.cc  */
#line 4200 "parser/nssis_new.yy"
    {
  // ATL F operator
  if((yysemantic_stack_[(3) - (1)].sval)!=NULL && (yysemantic_stack_[(3) - (3)]._modal_formula)!=NULL) {
    atomic_proposition *ap = new atomic_proposition((yysemantic_stack_[(3) - (1)].sval));
    modal_formula *a = new modal_formula(ap);
    (yyval._modal_formula) = new modal_formula(46, a, (yysemantic_stack_[(3) - (3)]._modal_formula));
  } else
    (yyval._modal_formula) = NULL;
 }
    break;

  case 647:

/* Line 690 of lalr1.cc  */
#line 4209 "parser/nssis_new.yy"
    {
  // ATL G operator
  if((yysemantic_stack_[(3) - (1)].sval)!=NULL && (yysemantic_stack_[(3) - (3)]._modal_formula)!=NULL) {
    atomic_proposition *ap = new atomic_proposition((yysemantic_stack_[(3) - (1)].sval));
    modal_formula *a = new modal_formula(ap);
    (yyval._modal_formula) = new modal_formula(47, a, (yysemantic_stack_[(3) - (3)]._modal_formula));
  } else
    (yyval._modal_formula) = NULL;
 }
    break;

  case 648:

/* Line 690 of lalr1.cc  */
#line 4218 "parser/nssis_new.yy"
    {
  (yyval._modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (3)]._modal_formula));
 }
    break;

  case 649:

/* Line 690 of lalr1.cc  */
#line 4223 "parser/nssis_new.yy"
    {
  // ATL U operator
  if((yysemantic_stack_[(2) - (1)].sval)!=NULL && (yysemantic_stack_[(2) - (2)].dual_modal_formula)!=NULL) {
    atomic_proposition *ap = new atomic_proposition((yysemantic_stack_[(2) - (1)].sval));
    modal_formula *a = new modal_formula(ap);
    (yyval._modal_formula) = new modal_formula(48, a, (yysemantic_stack_[(2) - (2)].dual_modal_formula)->first, (yysemantic_stack_[(2) - (2)].dual_modal_formula)->second);
    free((yysemantic_stack_[(2) - (2)].dual_modal_formula));
  } else {
    if((yysemantic_stack_[(2) - (2)].dual_modal_formula) != NULL)
       free((yysemantic_stack_[(2) - (2)].dual_modal_formula));
    if((yysemantic_stack_[(2) - (1)].sval) != NULL)
      free((yysemantic_stack_[(2) - (1)].sval));
    (yyval._modal_formula) = NULL;
  }
 }
    break;

  case 650:

/* Line 690 of lalr1.cc  */
#line 4238 "parser/nssis_new.yy"
    {
  // SL <<x>> operator
  if ((yysemantic_stack_[(6) - (3)].sval) != NULL && (yysemantic_stack_[(6) - (6)]._modal_formula) != NULL) {
    modal_formula *var = new modal_formula(new atomic_proposition((yysemantic_stack_[(6) - (3)].sval)));
    (yyval._modal_formula) = new modal_formula(50, var, (yysemantic_stack_[(6) - (6)]._modal_formula));
  } else {
    if ((yysemantic_stack_[(6) - (3)].sval) != NULL) {
      free((yysemantic_stack_[(6) - (3)].sval));
    }
    if ((yysemantic_stack_[(6) - (6)]._modal_formula) != NULL) {
      free((yysemantic_stack_[(6) - (6)]._modal_formula));
    }
    (yyval._modal_formula) = NULL;
  }
 }
    break;

  case 651:

/* Line 690 of lalr1.cc  */
#line 4253 "parser/nssis_new.yy"
    {
  // SL [[x]] operator
  if ((yysemantic_stack_[(6) - (3)].sval) != NULL && (yysemantic_stack_[(6) - (6)]._modal_formula) != NULL) {
    modal_formula *var = new modal_formula(new atomic_proposition((yysemantic_stack_[(6) - (3)].sval)));
    (yyval._modal_formula) = new modal_formula(51, var, (yysemantic_stack_[(6) - (6)]._modal_formula));
  } else {
    if ((yysemantic_stack_[(6) - (3)].sval) != NULL) {
      free((yysemantic_stack_[(6) - (3)].sval));
    }
    if ((yysemantic_stack_[(6) - (6)]._modal_formula) != NULL) {
      free((yysemantic_stack_[(6) - (6)]._modal_formula));
    }
    (yyval._modal_formula) = NULL;
  }
 }
    break;

  case 652:

/* Line 690 of lalr1.cc  */
#line 4268 "parser/nssis_new.yy"
    {
  // SL (a, x) operator
  if ((yysemantic_stack_[(6) - (2)].sval) != NULL && (yysemantic_stack_[(6) - (4)].sval) != NULL && (yysemantic_stack_[(6) - (6)]._modal_formula) != NULL) {
    modal_formula *agent = new modal_formula(new atomic_proposition((yysemantic_stack_[(6) - (2)].sval)));
    modal_formula *var = new modal_formula(new atomic_proposition((yysemantic_stack_[(6) - (4)].sval)));
    (yyval._modal_formula) = new modal_formula(52, agent, var, (yysemantic_stack_[(6) - (6)]._modal_formula));
  } else {
    if ((yysemantic_stack_[(6) - (2)].sval) != NULL) {
      free((yysemantic_stack_[(6) - (2)].sval));
    }
    if ((yysemantic_stack_[(6) - (4)].sval) != NULL) {
      free((yysemantic_stack_[(6) - (4)].sval));
    }
    if ((yysemantic_stack_[(6) - (6)]._modal_formula) != NULL) {
      free((yysemantic_stack_[(6) - (6)]._modal_formula));
    }
    (yyval._modal_formula) = NULL;
  }
 }
    break;

  case 653:

/* Line 690 of lalr1.cc  */
#line 4287 "parser/nssis_new.yy"
    {
  // SL (a, x) operator
  if ((yysemantic_stack_[(6) - (4)].sval) != NULL && (yysemantic_stack_[(6) - (6)]._modal_formula) != NULL) {
    modal_formula *agent = new modal_formula(
        new atomic_proposition(new string("Environment")));
    modal_formula *var = new modal_formula(new atomic_proposition((yysemantic_stack_[(6) - (4)].sval)));
    (yyval._modal_formula) = new modal_formula(52, agent, var, (yysemantic_stack_[(6) - (6)]._modal_formula));
  } else {
    if ((yysemantic_stack_[(6) - (4)].sval) != NULL) {
      free((yysemantic_stack_[(6) - (4)].sval));
    }
    if ((yysemantic_stack_[(6) - (6)]._modal_formula) != NULL) {
      free((yysemantic_stack_[(6) - (6)]._modal_formula));
    }
    (yyval._modal_formula) = NULL;
  }
 }
    break;

  case 654:

/* Line 690 of lalr1.cc  */
#line 4304 "parser/nssis_new.yy"
    {
  // LTL/SL X operator
  if((yysemantic_stack_[(2) - (2)]._modal_formula) != NULL) {
    (yyval._modal_formula) = new modal_formula(53, (yysemantic_stack_[(2) - (2)]._modal_formula));
  } else {
    (yyval._modal_formula) = NULL;
  }
 }
    break;

  case 655:

/* Line 690 of lalr1.cc  */
#line 4312 "parser/nssis_new.yy"
    {
  // LTL/SL F operator
  if((yysemantic_stack_[(2) - (2)]._modal_formula) != NULL) {
    (yyval._modal_formula) = new modal_formula(54, (yysemantic_stack_[(2) - (2)]._modal_formula));
  } else {
    (yyval._modal_formula) = NULL;
  }
 }
    break;

  case 656:

/* Line 690 of lalr1.cc  */
#line 4320 "parser/nssis_new.yy"
    {
  // LTL/SL G operator
  if((yysemantic_stack_[(2) - (2)]._modal_formula) != NULL) {
    (yyval._modal_formula) = new modal_formula(55, (yysemantic_stack_[(2) - (2)]._modal_formula));
  } else {
    (yyval._modal_formula) = NULL;
  }
 }
    break;

  case 657:

/* Line 690 of lalr1.cc  */
#line 4328 "parser/nssis_new.yy"
    {
  // LTL/SL U operator
  if((yysemantic_stack_[(3) - (1)]._modal_formula) != NULL && (yysemantic_stack_[(3) - (3)]._modal_formula) != NULL) {
    (yyval._modal_formula) = new modal_formula(56, (yysemantic_stack_[(3) - (1)]._modal_formula), (yysemantic_stack_[(3) - (3)]._modal_formula));
  } else {
    if ((yysemantic_stack_[(3) - (1)]._modal_formula) != NULL) {
      free((yysemantic_stack_[(3) - (1)]._modal_formula));
    }
    if ((yysemantic_stack_[(3) - (3)]._modal_formula) != NULL) {
      free((yysemantic_stack_[(3) - (3)]._modal_formula));
    }
    (yyval._modal_formula) = NULL;
  }
 }
    break;

  case 658:

/* Line 690 of lalr1.cc  */
#line 4342 "parser/nssis_new.yy"
    {	
  if((yysemantic_stack_[(1) - (1)].sval)!=NULL) {
    atomic_proposition *ap;
    int i = search_string_table((yysemantic_stack_[(1) - (1)].sval));
    if(i>=0) {
      ap = new atomic_proposition((*string_table)[i]);
      free((yysemantic_stack_[(1) - (1)].sval));
    } else {
      ap = new atomic_proposition((yysemantic_stack_[(1) - (1)].sval));
      string_table->push_back((yysemantic_stack_[(1) - (1)].sval));
    }
    (yyval._modal_formula) = new modal_formula(ap);
  } else
    (yyval._modal_formula) = NULL;
  }
    break;

  case 659:

/* Line 690 of lalr1.cc  */
#line 4357 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)].sval)!=NULL) {
    string *newname = new string(*(yysemantic_stack_[(3) - (1)].sval) + ".GreenStates");
    atomic_proposition *ap;
    int i = search_string_table(newname);
    if(i>=0) {
      ap = new atomic_proposition((*string_table)[i]);
      free(newname);
    } else {
      ap = new atomic_proposition(newname);
      string_table->push_back(newname);
    }
    free((yysemantic_stack_[(3) - (1)].sval));
    (yyval._modal_formula) = new modal_formula(ap);
  } else
    (yyval._modal_formula) = NULL;
 }
    break;

  case 660:

/* Line 690 of lalr1.cc  */
#line 4374 "parser/nssis_new.yy"
    {
  if((yysemantic_stack_[(3) - (1)].sval)!=NULL) {
    string *newname = new string(*(yysemantic_stack_[(3) - (1)].sval) + ".RedStates");
    atomic_proposition *ap;
    int i = search_string_table(newname);
    if(i>=0) {
      ap = new atomic_proposition((*string_table)[i]);
      free(newname);
    } else {
      ap = new atomic_proposition(newname);
      string_table->push_back(newname);
    }
    free((yysemantic_stack_[(3) - (1)].sval));
    (yyval._modal_formula) = new modal_formula(ap);
  } else
    (yyval._modal_formula) = NULL;
 }
    break;

  case 661:

/* Line 690 of lalr1.cc  */
#line 4391 "parser/nssis_new.yy"
    {
    string *newname = new string("Environment.GreenStates");
    atomic_proposition *ap;
    int i = search_string_table(newname);
    if(i>=0) {
      ap = new atomic_proposition((*string_table)[i]);
      free(newname);
    } else {
      ap = new atomic_proposition(newname);
      string_table->push_back(newname);
    }
    (yyval._modal_formula) = new modal_formula(ap);
 }
    break;

  case 662:

/* Line 690 of lalr1.cc  */
#line 4404 "parser/nssis_new.yy"
    {
  string *newname = new string("Environment.RedStates");
  atomic_proposition *ap;
  int i = search_string_table(newname);
  if(i>=0) {
    ap = new atomic_proposition((*string_table)[i]);
    free(newname);
  } else {
    ap = new atomic_proposition(newname);
    string_table->push_back(newname);
  }
  (yyval._modal_formula) = new modal_formula(ap);
 }
    break;

  case 663:

/* Line 690 of lalr1.cc  */
#line 4417 "parser/nssis_new.yy"
    {
  (yyval._modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (1)].sval));
 }
    break;

  case 664:

/* Line 690 of lalr1.cc  */
#line 4422 "parser/nssis_new.yy"
    {
  (yyval._modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (1)].sval));
 }
    break;

  case 665:

/* Line 690 of lalr1.cc  */
#line 4427 "parser/nssis_new.yy"
    {
  (yyval._modal_formula) = NULL;
  driver.syntax_error = true;
  USE((yysemantic_stack_[(3) - (1)].sval));
 }
    break;

  case 666:

/* Line 690 of lalr1.cc  */
#line 4432 "parser/nssis_new.yy"
    {
  (yyval._modal_formula) = NULL;
  driver.syntax_error = true;
  }
    break;

  case 667:

/* Line 690 of lalr1.cc  */
#line 4437 "parser/nssis_new.yy"
    {
  (yyval.boolean_flag) = false;
  }
    break;

  case 668:

/* Line 690 of lalr1.cc  */
#line 4440 "parser/nssis_new.yy"
    {
  (yyval.boolean_flag) = true;
  }
    break;



/* Line 690 of lalr1.cc  */
#line 8809 "parser/nssis.cc"
	default:
          break;
      }
    /* User semantic actions sometimes alter yychar, and that requires
       that yytoken be updated with the new translation.  We take the
       approach of translating immediately before every use of yytoken.
       One alternative is translating here after every semantic action,
       but that translation would be missed if the semantic action
       invokes YYABORT, YYACCEPT, or YYERROR immediately after altering
       yychar.  In the case of YYABORT or YYACCEPT, an incorrect
       destructor might then be invoked immediately.  In the case of
       YYERROR, subsequent parser actions might lead to an incorrect
       destructor call or verbose syntax error message before the
       lookahead is translated.  */
    YY_SYMBOL_PRINT ("-> $$ =", yyr1_[yyn], &yyval, &yyloc);

    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();

    yysemantic_stack_.push (yyval);
    yylocation_stack_.push (yyloc);

    /* Shift the result of the reduction.  */
    yyn = yyr1_[yyn];
    yystate = yypgoto_[yyn - yyntokens_] + yystate_stack_[0];
    if (0 <= yystate && yystate <= yylast_
	&& yycheck_[yystate] == yystate_stack_[0])
      yystate = yytable_[yystate];
    else
      yystate = yydefgoto_[yyn - yyntokens_];
    goto yynewstate;

  /*------------------------------------.
  | yyerrlab -- here on detecting error |
  `------------------------------------*/
  yyerrlab:
    /* Make sure we have latest lookahead translation.  See comments at
       user semantic actions for why this is necessary.  */
    yytoken = yytranslate_ (yychar);

    /* If not already recovering from an error, report this error.  */
    if (!yyerrstatus_)
      {
	++yynerrs_;
	if (yychar == yyempty_)
	  yytoken = yyempty_;
	error (yylloc, yysyntax_error_ (yystate, yytoken));
      }

    yyerror_range[1] = yylloc;
    if (yyerrstatus_ == 3)
      {
	/* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

	if (yychar <= yyeof_)
	  {
	  /* Return failure if at end of input.  */
	  if (yychar == yyeof_)
	    YYABORT;
	  }
	else
	  {
	    yydestruct_ ("Error: discarding", yytoken, &yylval, &yylloc);
	    yychar = yyempty_;
	  }
      }

    /* Else will try to reuse lookahead token after shifting the error
       token.  */
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;

    yyerror_range[1] = yylocation_stack_[yylen - 1];
    /* Do not reclaim the symbols of the rule which action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    yystate = yystate_stack_[0];
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;	/* Each real token shifted decrements this.  */

    for (;;)
      {
	yyn = yypact_[yystate];
	if (!yy_pact_value_is_default_ (yyn))
	{
	  yyn += yyterror_;
	  if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
	    {
	      yyn = yytable_[yyn];
	      if (0 < yyn)
		break;
	    }
	}

	/* Pop the current state because it cannot handle the error token.  */
	if (yystate_stack_.height () == 1)
	YYABORT;

	yyerror_range[1] = yylocation_stack_[0];
	yydestruct_ ("Error: popping",
		     yystos_[yystate],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);
	yypop_ ();
	yystate = yystate_stack_[0];
	YY_STACK_PRINT ();
      }

    yyerror_range[2] = yylloc;
    // Using YYLLOC is tempting, but would change the location of
    // the lookahead.  YYLOC is available though.
    YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yyloc);

    /* Shift the error token.  */
    YY_SYMBOL_PRINT ("Shifting", yystos_[yyn],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);

    yystate = yyn;
    goto yynewstate;

    /* Accept.  */
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    /* Abort.  */
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (yychar != yyempty_)
      {
        /* Make sure we have latest lookahead translation.  See comments
           at user semantic actions for why this is necessary.  */
        yytoken = yytranslate_ (yychar);
        yydestruct_ ("Cleanup: discarding lookahead", yytoken, &yylval,
                     &yylloc);
      }

    /* Do not reclaim the symbols of the rule which action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (yystate_stack_.height () != 1)
      {
	yydestruct_ ("Cleanup: popping",
		   yystos_[yystate_stack_[0]],
		   &yysemantic_stack_[0],
		   &yylocation_stack_[0]);
	yypop_ ();
      }

    return yyresult;
  }

  // Generate an error message.
  std::string
  mcmas_parser::yysyntax_error_ (int yystate, int yytoken)
  {
    std::string yyres;
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yytoken) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yychar.
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (yytoken != yyempty_)
      {
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            /* Stay within bounds of both yycheck and yytname.  */
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = 0;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
  const short int mcmas_parser::yypact_ninf_ = -969;
  const short int
  mcmas_parser::yypact_[] =
  {
        54,   336,   299,    35,   163,  1418,  -969,  2110,  1601,   600,
     150,  -969,  -969,  -969,  -969,   865,  -969,   706,  -969,  1271,
     296,   827,   833,   909,   256,  1245,   331,  1314,  1134,  1269,
     406,  1257,   302,  -969,   600,   671,  -969,  -969,   341,   321,
     578,   472,   485,  -969,   605,   392,   704,   717,  -969,  -969,
    -969,  -969,  -969,  -969,   486,   462,  -969,   414,  1657,  1314,
    1269,  1257,  -969,   457,  1943,  1269,  1257,  1682,   458,  3034,
    -969,  -969,   709,  3034,   449,  -969,  -969,  -969,  -969,  1413,
    1154,  6631,  6223,  -969,  1987,  6903,  -969,  -969,  -969,  -969,
    1527,  1257,   684,   510,  -969,  -969,   160,   586,  1086,  2813,
    1002,   321,  -969,   487,   759,  -969,   482,   943,  4600,  1014,
     331,  1408,   494,   459,  -969,  -969,  -969,  -969,  -969,  -969,
    -969,  -969,  -969,  -969,   756,  1153,  -969,   541,   506,  1269,
    1257,  1257,  1002,  1105,   907,  -969,  -969,  1257,  1002,  1842,
    -969,  -969,  2109,  6664,  3099,  -969,  -969,  -969,  1824,  7331,
    3162,  -969,  2618,  1905,  1010,  -969,   583,  -969,  2934,  3034,
    3034,  -969,   733,   733,   733,   733,   733,   733,  1010,  -969,
    -969,  -969,  -969,  -969,  -969,  1010,  1010,  1010,  1010,  1010,
    1002,  -969,  -969,  -969,   553,   796,  -969,  -969,  -969,  -969,
    1224,  1282,  1172,  -969,  2850,  -969,  1417,  1268,   841,  1216,
      78,  1461,   943,   871,   522,    90,  -969,  4786,   482,    66,
     482,   721,  1501,  1333,  -969,  -969,  -969,   513,   536,  4467,
     240,  4689,  -969,  -969,   917,  -969,  1042,   995,   457,  1467,
    2876,  1475,    25,  1353,  1351,   552,  -969,  -969,   712,  1097,
    1408,   294,   297,  -969,  -969,  1257,  1002,  1002,  1461,  -969,
    -969,  -969,  1002,  1461,  2602,  -969,  -969,  -969,  2643,  -969,
    2161,  -969,  2418,  -969,  3034,  1905,   554,   620,  3060,  4469,
    4939,  2224,   733,  6256,  6301,  6334,  -969,  -969,  -969,  6936,
    6973,  6993,  1530,  -969,  -969,  1461,  -969,  -969,  1968,  -969,
    1120,    97,  -969,  -969,  1101,    97,  1296,  -969,  -969,  1417,
    1229,  -969,  2996,    97,  -969,  -969,  -969,  -969,   320,  1242,
    1604,  -969,   536,   240,  -969,  -969,  -969,  -969,  1876,  1876,
    1184,   826,  4935,  2047,  1209,  1231,  5004,  1241,  1304,  4680,
     482,   482,  1474,  -969,   112,   205,  1024,  -969,   520,   998,
     240,  -969,  4440,   856,  6103,  1372,  6103,  6103,  6103,  6103,
    6103,  6103,  6103,   604,   604,  1121,  1124,  1124,  1121,  1124,
    5788,  -969,  5994,  1167,  -969,  -969,  -969,  -969,  4497,  5721,
    -969,  -969,  -969,  -969,  -969,  -969,  1152,  3010,   835,  3010,
     590,  -969,  -969,  -969,  1413,  1564,  2243,  7030,  -969,  -969,
    6709,  6379,  -969,  -969,  -969,  1589,  1353,  -969,   160,   859,
     880,  1350,  -969,  -969,  -969,   944,  1321,  -969,  1475,  1353,
     108,  -969,  -969,   901,  1111,   108,   237,  -969,  1139,  1002,
    1461,  1461,  -969,  1461,  -969,  1582,  1941,  -969,  -969,  -969,
    -969,  -969,  -969,   996,   996,  -969,   996,   815,  1410,    69,
    1427,  -969,  -969,  1630,  -969,  -969,  -969,   240,  -969,  -969,
    1716,  1876,   853,  1876,   918,  6535,  -969,  2340,  7217,  -969,
    -969,  7050,  6742,  -969,  -969,  -969,  1632,  1735,  1473,   669,
     791,   840,  -969,  1196,  -969,  1206,  1207,   482,  1279,  1338,
     390,  -969,  5094,  5184,  5274,  1465,   450,  -969,  -969,  -969,
    1550,  1189,   437,  1539,  1024,  -969,  -969,  4757,  6160,  -969,
    -969,  -969,  2162,  -969,  -969,  4784,  1383,  1040,  2419,  4564,
    4876,  6295,  6373,  6451,  6493,  6103,  6103,  -969,  -969,    42,
      80,  -969,  1495,  1518,  -969,  -969,  -969,  -969,  1166,   295,
    4847,  -969,  1331,  6020,  6103,  6103,  -969,  6103,  1553,   241,
    -969,  5721,  3079,  5748,  1602,    49,  1579,  5721,  5721,  5721,
    5721,  5721,  5721,  5721,  1225,  1225,  1236,  1349,  1349,  1236,
    1349,  5721,  5721,  5721,  5881,   579,  1079,  1359,  1559,  5029,
    3230,  -969,  6774,  2206,  3298,  7376,  1598,  1603,  5119,  1422,
     507,  -969,  -969,  2884,  3010,  3010,  -969,   507,   507,   507,
     507,   507,   507,  1013,  1013,  1013,  1013,  1013,  1013,  1350,
    -969,  1486,  2769,  -969,  1417,  1320,   841,  -969,  1523,  -969,
    -969,  1353,  1350,  -969,  1609,  -969,  1617,    52,    52,  -969,
    1176,    52,    52,  1461,  -969,  -969,  -969,   965,   563,  1618,
    -969,  -969,  -969,  -969,  -969,  -969,  -969,  1334,  1010,  3020,
      69,  -969,  1620,  3366,  -969,  7095,  5364,  3434,  7399,  2523,
    1626,  1627,  5454,  2002,   729,  -969,  1628,  1629,   729,   729,
     729,   729,   729,   729,  1266,  1266,  1266,  1266,  1266,  1266,
    2910,  1876,  1876,  -969,  2947,  -969,   791,  1552,  2314,  -969,
    -969,  -969,  -969,  -969,   791,   791,   791,    89,   791,   791,
     791,   411,  -969,  -969,  -969,  -969,  -969,  -969,  -969,  -969,
    1414,   603,  -969,  -969,  -969,  1201,  -969,   437,   654,  4396,
     981,  7780,  4910,  -969,  4937,  -969,  -969,  -969,  6103,   837,
     977,   303,   367,   391,   607,   622,   666,  -969,  -969,  -969,
    -969,  -969,  6077,  -969,  6703,  7450,  7453,  7456,  -969,  -969,
    -969,  2755,  3147,  5814,  7438,  -969,  -969,  7489,  1146,  2631,
    1259,  1640,  1643,   838,  1472,  7492,  7512,  7514,  7516,  7534,
    7536,  7558,  5721,  5721,  -969,  -969,   137,   176,  -969,  1644,
    1645,  -969,  -969,  -969,  -969,  7570,  7581,  7592,  1508,   890,
    5721,  5721,  5721,  5721,  -969,  4524,  5721,  5721,  -969,  5721,
    5721,  -969,  2494,  -969,  -969,  -969,  2507,  -969,  2321,  -969,
    2065,  -969,  -969,  -969,  3010,  1422,   723,   913,  5209,  5299,
    5389,  7127,  7160,  7197,  1760,  -969,  -969,  1779,  1013,  6412,
    6457,  6490,  -969,  -969,  -969,  1523,  1549,  1076,  -969,  -969,
    1417,  -969,  1459,    97,   364,   364,  1674,  1646,  -969,  1350,
    1523,  -969,  -969,  -969,  -969,  1609,  -969,  -969,  -969,  -969,
    -969,  -969,  -969,  -969,  -969,  -969,   720,  2128,  3020,  1393,
    3020,  4704,  1987,  1857,  -969,  -969,  -969,  -969,  2667,  -969,
    2452,  -969,  2355,  -969,  2691,  -969,  -969,  -969,  1876,  2002,
     930,   931,  -969,  -969,  7254,  7274,  7311,  1823,  -969,  -969,
    2258,  1266,  6807,  6839,  6871,  -969,  -969,  -969,  5479,  5544,
    5569,  -969,  -969,  -969,  -969,  1664,  1680,  -969,  -969,  -969,
    -969,  1684,  1685,  -969,  -969,  -969,  -969,   401,   490,  -969,
    -969,  1201,  6103,  6103,  5937,  6103,  6103,  6103,  5937,  6103,
    6103,  6103,  6103,  6103,  6103,  6103,  6103,  6103,  6103,  6103,
    6103,  6103,  4593,  -969,  1091,  7406,  1119,  3512,  -969,  3215,
    -969,  1654,  1662,  3283,  -969,  1725,  1726,  -969,  -969,  -969,
    -969,  5721,  1636,  2810,   693,   732,  1001,  1012,  1072,  1123,
    -969,  -969,  -969,  -969,  -969,  7594,  7614,  7617,  7639,  7646,
    7650,  7661,  7668,  7683,  2038,  2481,  -969,  -969,   996,   905,
     527,  1737,  -969,   988,  -969,  -969,  -969,  -969,  -969,  1523,
    -969,  1687,  6567,  3099,  5634,  3162,  2744,  1688,  1689,  5659,
     698,   396,  1010,  3020,  3020,  3020,  -969,  2564,  2692,  1690,
    1691,  1692,  1693,  -969,  -969,  -969,  -969,  1446,  2400,  2817,
    2821,  2897,  2929,  3072,  3144,  2089,  3584,  2225,  3652,  3720,
    3788,  3856,  3924,  3992,  4060,  4128,  4196,  5721,  5721,  4623,
    5721,  5721,  5841,  4623,  5907,  1761,  1762,  1759,  1758,  5721,
    5721,  5721,  5721,  5721,  5721,  5721,  5721,  5721,  5721,  5721,
    5721,  5721,  -969,  -969,  1335,   507,  2972,  2972,   527,  -969,
    -969,  2715,  -969,  2756,  -969,  -969,  -969,  1700,  1396,  -969,
     268,  1416,  2536,  5725,  5839,  6022,  -969,  -969,  -969,  -969,
    5000,  -969,  5027,  -969,  5090,  -969,  5117,  -969,  5180,  -969,
    5207,  -969,  5270,  -969,  5297,  -969,  5360,  -969,  5387,  -969,
    5450,  -969,  5477,  -969,  5090,  -969,  5117,  -969,  5270,  -969,
    5297,  -969,  5540,  -969,  5567,  -969,  5630,  -969,  5657,  -969,
    2303,  2863,  3006,  3066,  3580,  1614,  3648,  3716,  1614,  3784,
    5721,  5721,  5721,  5721,  7705,  7712,  3852,  3920,  3988,  4056,
    4124,  4192,  4260,  4328,  4875,  5926,  -969,   754,  1612,  2972,
     855,  1442,  2972,  6166,  2243,  1886,  1923,  -969,  -969,  1701,
    1702,  1706,  -969,  1707,  1714,  3351,  -969,  3419,  -969,  3487,
    -969,  3555,  -969,  3623,  -969,  3691,  -969,  3759,  -969,  3827,
    -969,  7727,  7728,  7730,  7734,  3895,  -969,  3963,  4031,  -969,
    4099,  -969,  3487,  -969,  3555,  -969,  3759,  -969,  3827,  -969,
    4167,  -969,  4235,  -969,  4303,  -969,  4371,  -969,  1715,  6599,
    3230,  6023,  3298,  2862,   777,    82,  1738,  1739,  6024,   802,
     567,   507,   742,  2972,  2972,  -969,  2800,  -969,  -969,  -969,
    -969,  -969,  -969,  -969,  2548,  -969,  2589,  -969,  1740,  1799,
    6105,   362,  1456,  -969,  -969,  2972,  1741,  1469,  -969,   377,
    1479,  2577,  6106,  6107,  6259,  -969,  1742,  1744,  -969,  1746,
    1751,  -969,  1752,  1754,  1756,  -969,  1763,  1764,  -969,  -969,
    -969,  -969,  -969,  -969,  -969,  -969,  -969
  };

  /* YYDEFACT[S] -- default reduction number in state S.  Performed when
     YYTABLE doesn't specify something else to do.  Zero means the
     default is an error.  */
  const unsigned short int
  mcmas_parser::yydefact_[] =
  {
         0,    18,     0,     0,     0,     0,     2,     0,     0,     0,
       0,   120,    16,    17,    15,     0,     1,    18,     3,    81,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   122,   123,     0,   133,   405,   121,     0,     0,
       0,     0,     0,   157,     0,    80,   158,     0,    34,    32,
      68,    66,    79,    78,    39,     0,    41,     0,    81,     0,
       0,     0,    45,     0,    81,     0,     0,     0,     0,     0,
     386,   387,     0,     0,     0,   384,    62,   385,    87,     0,
       0,     0,     0,   253,     0,     0,   264,   267,   257,   383,
     160,     0,   164,     0,   170,   166,     0,   177,     0,     0,
       0,     0,   417,     0,   430,   429,     0,     0,    69,     0,
       0,     0,     0,     0,     4,     5,   159,   154,   155,   156,
     153,    37,    38,    36,    39,     0,    40,     0,    80,     0,
       0,     0,     0,    57,     0,    74,    80,     0,     0,     0,
      83,    62,     0,     0,     0,   266,    84,    82,     0,     0,
       0,    63,     0,     0,     0,   265,    85,    86,     0,     0,
       0,    92,     0,     0,     0,     0,     0,     0,     0,   347,
     349,   351,   348,   350,   352,     0,     0,     0,     0,     0,
       0,   163,   162,   161,   164,     0,   165,   175,   176,   174,
       0,     0,     0,   185,     0,   191,     0,     0,   101,     0,
       0,     0,     0,   409,     0,     0,   410,     0,     0,     0,
       0,     0,     0,   496,   495,   466,   574,     0,     0,     0,
       0,     0,    14,   138,     0,    67,   139,     0,     0,    81,
       0,     0,     0,     0,   145,     0,   149,   147,     0,    69,
       0,     0,     0,    44,    43,     0,     0,     0,     0,    71,
      72,    70,     0,     0,     0,   225,   255,   269,     0,   224,
       0,   254,     0,   268,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   252,   250,   251,     0,
       0,     0,     0,   263,   262,     0,   172,   171,     0,   179,
       0,     0,   180,   178,   200,     0,     0,   182,   192,     0,
     181,   184,     0,     0,    99,   100,    98,   109,     0,    22,
       0,    30,     0,     0,    10,   407,   408,   406,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   439,   471,     0,     0,   473,     0,   496,
       0,    12,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   501,     0,     0,   575,    13,   585,   668,     0,     0,
     140,   135,   136,   137,   134,    76,     0,     0,     0,     0,
       0,   389,   393,    90,     0,     0,     0,     0,   278,   281,
       0,     0,   307,   388,   311,   160,     0,   173,     0,   177,
       0,     0,   144,   143,   142,   145,     0,   146,     0,     0,
      61,    48,    58,     0,     0,    47,     0,    46,     0,     0,
       0,     0,    28,     0,    26,     0,     0,    29,   198,   199,
     197,   214,   211,     0,     0,   183,     0,   105,     0,     0,
       0,   106,   108,     0,    20,    21,    19,     0,     8,     9,
       0,     0,     0,     0,     0,     0,   401,     0,     0,   292,
     295,     0,     0,   319,   394,   323,     0,     0,     0,     0,
       0,     0,   442,     0,   441,     0,     0,     0,     0,     0,
       0,   435,     0,     0,     0,   436,     0,   469,   470,   468,
     478,     0,     0,   471,     0,   472,    11,     0,     0,   498,
     563,   564,     0,   499,   497,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   556,   557,     0,
       0,   558,     0,     0,   559,   560,   561,   562,     0,     0,
       0,   502,     0,     0,     0,     0,   503,     0,   579,     0,
     580,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   280,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   279,    89,     0,     0,     0,    95,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     168,     0,     0,   194,     0,     0,   101,   217,     0,   151,
     150,     0,     0,    64,    56,    54,     0,     0,     0,    61,
       0,     0,     0,     0,    24,    27,    25,   204,     0,     0,
     210,   209,   205,   103,   104,   102,   115,     0,     0,     0,
       0,     7,     0,     0,   294,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   293,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   414,     0,   413,     0,    65,     0,   404,
     402,   464,   403,   462,     0,     0,     0,     0,     0,     0,
       0,     0,   437,   432,   433,   434,   431,   476,   477,   475,
     482,     0,   492,   493,   485,     0,   488,     0,     0,     0,
       0,     0,     0,   541,     0,   540,   569,   568,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   572,   571,   570,
     567,   566,     0,   505,     0,     0,     0,     0,   577,   578,
     576,     0,     0,     0,     0,   643,   644,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   636,   637,     0,     0,   638,     0,
       0,   639,   640,   641,   642,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   649,     0,     0,     0,   581,     0,
       0,   391,     0,   236,   283,   309,     0,   235,     0,   282,
       0,   308,   392,   390,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   277,   276,     0,     0,     0,
       0,     0,   306,   304,   305,     0,     0,     0,   187,   195,
       0,   189,     0,     0,     0,     0,   128,     0,   130,     0,
       0,    60,    59,    52,    50,    55,    53,    51,    49,    23,
     202,   213,   203,   201,   212,   112,     0,     0,     0,     0,
       0,     0,     0,     0,   113,   399,   297,   321,     0,   419,
       0,   296,     0,   320,     0,   418,   400,   398,     0,     0,
       0,     0,   397,   396,     0,     0,     0,     0,   291,   290,
       0,     0,     0,     0,     0,   318,   316,   317,     0,     0,
       0,   463,   461,   459,   460,     0,   403,   458,   456,   454,
     455,     0,   403,   453,   480,   481,   479,     0,     0,   483,
     486,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   583,     0,     0,     0,     0,   588,     0,
     621,     0,     0,     0,   620,     0,     0,   587,   586,   662,
     661,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     665,   664,   663,   660,   659,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   129,   188,     0,   105,
       0,     0,   216,     0,   218,   215,   126,   127,   125,     0,
     132,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   110,     0,     0,     0,
       0,     0,     0,   494,   490,   489,   484,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   207,   119,     0,     0,     0,     0,     0,   131,
     335,     0,   325,     0,   324,   336,   334,     0,     0,   345,
       0,     0,     0,     0,     0,     0,   457,   452,   451,   450,
       0,   528,     0,   525,     0,   520,     0,   517,     0,   526,
       0,   524,     0,   518,     0,   516,     0,   512,     0,   509,
       0,   510,     0,   508,     0,   520,     0,   517,     0,   518,
       0,   516,     0,   536,     0,   533,     0,   534,     0,   532,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   116,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   117,   342,     0,
       0,     0,   343,     0,     0,     0,   608,     0,   605,     0,
     600,     0,   597,     0,   606,     0,   604,     0,   598,     0,
     596,     0,     0,     0,     0,     0,   592,     0,     0,   590,
       0,   589,     0,   600,     0,   597,     0,   598,     0,   596,
       0,   616,     0,   613,     0,   614,     0,   612,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   220,     0,   219,   344,   339,
     340,   341,   338,   364,     0,   354,     0,   353,     0,     0,
     392,     0,     0,   365,   363,     0,     0,     0,   374,     0,
       0,     0,     0,     0,     0,   378,     0,     0,   379,     0,
       0,   371,     0,     0,     0,   372,     0,     0,   380,   376,
     377,   375,   373,   368,   369,   370,   367
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  mcmas_parser::yypgoto_[] =
  {
      -969,  -969,  -969,  1807,  -969,  -223,  -969,  -969,  1777,  -969,
      50,  -969,  1419,   -28,    83,  1608,  1812,  1727,   -94,   -60,
    1051,  1605,  -969,  -969,  -392,   775,   167,  -969,  -969,  -421,
    -968,  1836,  -969,  -791,   983,  -969,  1610,  -969,  -969,   -64,
     -84,   281,  -198,  1621,  -210,  -158,   259,  -365,  -969,  -969,
    -181,  -432,  1658,  1262,  -184,  -290,  -572,  1254,  -969,   643,
     -85,   -32,   -59,  1164,   -61,   -74,  1373,    13,  -308,  -514,
    1068,  -352,  -400,  -594,  1003,  -447,  -356,  -498,   924,  -436,
    -606,   928,  -610,  -385,  -741,  -969,    15,  -969,  -969,  -327,
    -969,  -969,  1844,  -969,   -97,  -969,  -969,  1775,    21,  -969,
    1541,  1678,  1391,  -651,  -969,  1181,   752,  -969,  1528,  -170,
    -969,  1535,  1178,  1190,    36,  -969,  -969,    63,  -969,  -969,
     155,   982,  1027,    -3,  1524
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  mcmas_parser::yydefgoto_[] =
  {
        -1,     4,     5,     6,     7,   311,     8,    24,    56,    25,
      57,   127,   413,   382,    26,   135,    27,   111,    28,    78,
      29,   231,    79,   384,   200,   441,   201,   308,   442,   443,
     993,     9,    10,   838,    11,   112,   237,   113,   238,    30,
      95,    31,   233,    96,    99,   193,   100,   401,   194,   602,
     291,   630,   195,   603,   196,   433,   608,   834,   994,   142,
     569,    81,    82,    83,    84,    85,    86,    87,   386,   387,
     388,   389,   457,   458,   459,   460,   390,   391,   392,   461,
     462,   463,  1093,   177,  1272,    88,   393,   394,   465,   681,
      38,   206,    39,   103,   898,   106,   333,   107,   482,   217,
     337,   218,   492,   704,   338,   705,   706,   219,   361,   220,
     362,   517,   500,   501,   734,   221,   540,   222,   368,   565,
     764,   745,   746,   979,   369
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If YYTABLE_NINF_, syntax error.  */
  const short int mcmas_parser::yytable_ninf_ = -668;
  const short int
  mcmas_parser::yytable_[] =
  {
        77,   590,   631,   644,   632,   434,   144,   655,   150,   607,
     299,   295,   186,   436,   645,   648,   303,   230,   637,   157,
     572,   575,  1074,   400,   571,   422,   397,   825,   581,   863,
     424,   599,   313,   396,   986,   143,   297,   149,   301,    77,
     840,    77,   409,    89,   612,    77,    77,   232,   340,  1000,
     643,   647,    15,   677,   919,     1,   920,     2,   892,   893,
     894,   721,   427,   752,   884,   885,   886,   324,   570,   574,
     636,    77,   661,   811,   812,   813,    63,   439,   144,   307,
     145,    72,    89,  1261,    89,  -107,  -107,   155,    89,    89,
     677,   318,   266,   267,   279,   819,   820,   821,   431,   723,
      94,   280,   281,   273,   274,   275,   319,   143,   905,   325,
    1177,    77,    70,    71,    89,  1262,   282,   722,    72,  -487,
       3,   143,   149,   110,   753,    77,    77,   212,    76,   144,
      77,    77,    77,   -65,    77,    77,    77,    77,    77,    77,
      77,   435,   447,   683,   440,   385,   230,    77,    77,    77,
      77,    77,   145,  -107,    89,   724,   964,   803,   143,   487,
     228,   184,    77,    16,   906,    76,    77,   232,    89,    89,
     383,    93,   432,    89,    89,    89,   232,    89,    89,    89,
      89,    89,    89,    89,   613,   590,   400,  -487,   279,   590,
      89,    89,    89,    89,    89,   966,   110,   624,   625,   400,
     626,   273,   185,   145,   266,    89,   488,   607,  1079,    89,
     611,   572,   965,   414,   418,   571,   604,   645,   648,   864,
     607,   466,   467,   572,   575,    40,    77,   144,   322,   323,
      77,   326,    77,   143,    77,   144,    77,    77,   619,   425,
     426,   364,   739,    77,    77,   572,   839,  1004,  1006,   571,
    1009,   967,   489,   880,   881,   363,   143,    54,   661,   570,
      77,   887,   661,    55,   143,   314,   892,   999,    77,    89,
    1026,   806,   807,    89,    77,    89,   884,    89,   145,    89,
      89,   341,   814,   365,   811,  1181,    89,    89,   216,   740,
     456,   456,   573,   570,   578,   410,   729,    46,   415,   248,
      13,   145,   819,    89,   922,   253,    61,   416,    66,   145,
      91,    89,   412,    47,   600,   605,   411,    89,    14,   417,
     132,   437,   104,    72,   582,   138,    72,   438,   439,   730,
     731,   -42,    62,   464,   464,  1175,  1176,    -6,   -42,    -6,
     130,   131,   102,  1182,   232,   923,   137,   285,  -412,   901,
     180,   483,   484,   646,   649,    12,   652,   902,   903,   904,
     907,   908,   909,   910,   913,   989,   566,   105,   934,   412,
      76,   438,   990,    76,  -123,   448,   449,  -124,   502,  1277,
     506,  -122,   508,   509,   510,   511,   512,   513,   514,   246,
     247,   692,   926,   -33,  1284,   440,   252,  1090,   532,   -33,
     849,   400,  1023,   496,  1094,  1095,   -42,    92,  -482,   935,
     245,  -124,   677,   420,   421,   124,  -412,    93,   830,   423,
     702,    55,   456,   456,   833,   456,   456,  1231,  1233,  1091,
     911,  1238,   644,   927,    70,    71,   693,  1278,   700,   991,
      72,   679,   679,   645,   828,   914,   831,   607,   701,   572,
     153,   695,  1285,   571,  1017,  1018,   702,   154,   133,   146,
     239,   984,   985,   122,   134,   464,   464,   -33,   464,   464,
     572,   572,    70,    71,   571,   571,   703,  1012,    72,   880,
      22,    94,   123,   207,   680,   680,   912,    76,   203,   125,
     208,  1023,   147,   -45,   204,   234,   696,   806,   808,   809,
     810,   209,  1273,  1274,   419,   235,   121,   -67,   805,   702,
     641,   182,   703,   -67,   334,   580,   114,   605,   570,   570,
     335,   493,   210,   316,    75,    76,   378,   335,  1073,   115,
      70,    71,   125,   502,   506,   990,    72,   339,   741,   747,
     750,   502,   243,   988,   755,   756,   757,   758,   759,   760,
     761,   719,   720,   403,   183,   168,  1072,   211,   775,   776,
     777,   -45,   205,   257,   852,   703,   502,   317,  1269,   236,
     735,   736,   214,   737,   899,   900,   380,   856,   862,   108,
     780,   -67,   381,    76,   216,   244,   623,   763,   336,   843,
     844,   579,  -186,   847,   848,   494,   404,   181,   580,    22,
    1270,    35,   991,    33,   915,   515,   116,   853,   936,   378,
      77,    77,   516,    70,    71,   117,   109,   140,  1012,    72,
    1012,   262,   175,   938,   176,   456,   456,   187,   286,   263,
     456,   456,   456,   456,   456,   456,   456,   456,   456,   456,
     456,   456,   456,   456,   456,    36,   456,   916,   679,   937,
     781,   782,   783,    89,    89,   922,   679,   679,   679,   679,
     679,   679,   679,   679,   939,   381,    76,   940,   464,   464,
     677,    80,   987,   464,   464,   464,   464,   464,   464,   464,
     464,   464,   464,   464,   464,   464,   464,   464,   175,   464,
     176,   680,    70,    71,  1047,  -173,   923,   507,    72,   680,
     680,   680,   680,   680,   680,   680,   680,   808,   941,   -31,
     765,   808,   148,   405,   118,  1087,   152,  -411,   119,   808,
     784,   168,   327,   235,   587,    12,  -173,   120,   181,  -114,
     879,  1088,   794,  1063,   271,  1048,  -114,   654,  -114,   747,
     750,   272,   197,  1168,   678,    76,  -124,   808,   452,  -222,
    1169,  -122,    70,    71,   406,   587,    70,    71,    72,   962,
     963,  1170,    72,  -118,   328,    70,    71,  1167,  1174,  1174,
    -118,    72,  -118,  1089,  1064,  1171,   121,   975,   976,   977,
     978,  -124,  1172,   980,   981,   151,   982,   983,   175,  1241,
     176,   588,   677,   589,  1258,  -440,  1003,  1005,   454,   862,
     -57,   268,   269,   270,   455,    76,  -440,  -440,    75,    76,
    1259,   380,   572,   575,    70,    71,   571,  1173,    76,  1266,
      72,   633,   588,  -111,   589,   143,   149,   469,    48,    77,
      77,  -115,    77,  -115,    50,  1267,   576,   197,   930,   957,
     456,   207,   456,   470,   456,  1241,   456,  1241,   208,  -444,
     456,   456,  1260,   958,   650,   534,  1234,   503,  -444,   209,
    1230,  1232,   456,   456,  1174,  -190,   682,    76,    49,   328,
     145,   287,    89,    89,    51,    89,   535,  1268,   577,  -444,
     210,   601,   304,   464,  -444,   464,   537,   464,   377,   464,
    -111,   972,   504,   464,   464,   931,   651,   268,  1235,   378,
     187,   268,   614,    70,    71,   464,   464,   268,   250,    72,
      52,   633,   615,  -223,   798,   211,   315,   192,   370,   653,
     379,  -119,   799,  -119,   973,   974,   654,   371,   251,    41,
      42,   658,   870,  1271,  1174,  1174,  1174,   452,  1174,   866,
     871,    70,    71,   616,   213,   268,  1174,    72,  1174,   380,
      53,  1092,   862,   862,   862,   381,    76,  1174,  1027,  1028,
    1029,  1030,  1031,  1032,  1033,  1034,  1035,  1036,  1037,  1038,
    1039,  1040,  1041,  1042,  1043,  1044,  1045,  1046,   932,   214,
    -223,   588,   926,   589,    77,    77,    77,    77,   402,  1076,
     215,   216,    37,   455,    76,   534,   373,   627,   659,   659,
     660,   660,  1051,   198,  1077,   374,  1078,   628,   199,   850,
    -575,   265,  -575,  1066,   817,   226,   535,    37,   154,   609,
     862,   818,   862,   927,   507,   490,   537,    89,    89,    89,
      89,   227,   378,    70,    71,   933,    70,    71,   629,    72,
     851,   491,    72,  1065,  1140,  1141,  1142,  1143,  1144,  1146,
    1147,  1149,   372,    77,  1067,    77,  1154,  1155,  1156,  1157,
    1158,  1159,  1146,  1160,  1161,  1162,  1163,  1164,  1165,  -575,
    -575,  -575,  -575,  1068,   716,   717,    60,   826,    65,    74,
     785,   289,  -181,  -208,   377,    75,    76,   188,   381,    76,
     -65,   -65,  1047,   -65,  -245,   378,    89,   786,    89,    70,
      71,   -77,   -65,   -65,   -65,    72,   -65,   -65,   -65,   -73,
     129,   428,   617,  -208,  1069,  -245,   379,   290,   787,   568,
    1051,   429,   519,   788,  1070,   522,   249,   189,   789,   520,
     430,   -77,   523,  1048,   754,    67,   618,   790,   225,   -73,
     621,    68,    69,   -65,   -65,   380,   -65,  1201,  1202,  1203,
    1204,   381,   141,   567,   241,   158,   -85,    70,    71,   -97,
     377,  1052,   754,    72,   622,  1071,   -65,   -65,   533,   -65,
    -245,   378,   159,   294,    73,    70,    71,   845,   -65,   -65,
     -65,    72,   -65,   -65,   -65,   534,   140,   846,   951,   754,
     698,  -245,   379,   160,   242,   568,  -245,   207,   161,   699,
     727,   728,   917,    74,   208,  -443,   535,   684,   686,    75,
      76,   536,   701,   290,  -443,   209,   537,   305,   616,   -65,
     -65,   380,   -65,   685,   687,   288,   762,   381,   141,   289,
    -181,  -193,    69,   763,   289,  -443,   210,   766,   -65,   -65,
    -443,   -65,  -234,   918,   767,   444,    58,    70,    71,    20,
     -65,   -65,   -65,    72,   -65,   -65,   -65,   306,    97,   468,
     953,  -193,    98,  -234,    73,   290,    22,   890,   954,   302,
      90,   211,   -35,    20,   891,   -75,  -167,   786,   -35,    23,
     688,    43,  -160,   292,   475,   452,   159,   293,    44,    70,
      71,   -65,   -65,    74,   -65,    72,   689,   288,   787,    75,
     141,   289,  -181,  -206,    69,   -75,   476,   160,   789,   290,
     -65,   -65,    45,   -65,  -234,    64,   478,   790,    20,    70,
      71,   832,   -65,   -65,   -65,    72,   -65,   -65,   -65,   276,
     277,   278,   732,  -206,  -467,  -234,    73,   290,   584,   690,
    -467,   455,    76,   855,  1166,  -575,   -35,  -575,    23,   534,
     769,   606,   640,  1078,   399,   691,   199,   770,    98,   585,
     567,   290,  -152,   -65,   -65,    74,   -65,   377,   -65,  -474,
     535,    75,   141,   -65,   -65,   733,   -65,  -245,   378,   479,
     537,  -474,    70,    71,   714,   -65,   -65,   -65,    72,   -65,
     -65,   -65,   715,  -152,  1007,   402,   610,  1179,  -245,   379,
    -245,   534,   568,  -245,  -575,  -575,  -575,  -575,  -467,   229,
    1008,   634,    20,  1180,   156,   507,   635,  1183,   300,    17,
      68,     2,   535,   805,   191,  -491,   -65,   -65,   380,   -65,
     580,   -65,   537,  1184,   381,   141,   -65,   -65,   -65,   -65,
     -65,   378,    23,  1236,   638,    70,    71,  1100,   -65,   -65,
     -65,    72,   -65,   -65,   -65,  1101,  -491,  1279,   914,  1237,
     567,   -65,   309,   -65,   534,   568,   -65,   377,   310,   428,
    1282,   -91,  -169,  1280,   676,   485,   395,    43,   378,    20,
    1286,   486,    70,    71,    44,   535,  1283,   826,    72,   -65,
     -65,   380,   -65,  -196,   377,   537,  1287,   381,   141,   379,
     -65,   -65,   329,   -65,  -245,   378,   959,   960,   136,    70,
      71,   694,   -65,   -65,   -65,    72,   -65,   -65,   -65,   330,
     822,   823,   824,  -196,   836,  -245,   379,   290,   380,   568,
     837,   168,  -167,   521,   381,    76,   526,    43,   768,  -233,
     331,   773,   970,   971,    44,   332,   524,   525,  -233,   527,
     567,   283,   284,   -65,   -65,   380,   -65,   377,   -65,   428,
     697,   381,   141,   -65,   -65,   583,   -65,  -245,   378,  -233,
     725,  -233,    70,    71,  -233,   -65,   -65,   -65,    72,   -65,
     -65,   -65,   584,   162,   771,   772,   487,   774,  -245,   379,
    -245,   256,   568,   726,  -169,   895,   896,   897,   175,    43,
     176,   738,    32,   585,    33,   445,    44,   446,   586,   992,
     995,   163,   164,  1168,   751,   778,   -65,   -65,   380,   -65,
    1169,   -65,   754,  -658,   381,   141,   -65,   -65,   613,  1228,
    -382,  1170,  -658,   670,   791,    70,    71,  1059,   -65,   -65,
     -65,    72,   -65,   -65,   -65,  1171,   639,   997,   640,   998,
     671,  -382,  1172,  -658,   786,   568,  -382,   779,   -69,   815,
     816,   -75,  -167,  -658,   -69,   888,   889,    43,  -160,  1024,
    1025,   672,  -658,   802,    44,   787,   673,   996,   803,   -65,
     -65,   380,   -65,   139,   841,   789,   -85,  1229,   141,   -94,
      69,   -75,   842,   854,  1060,   865,   -65,   -65,   128,   -65,
    -234,   876,   877,   882,   883,    70,    71,  1019,   -65,   -65,
     -65,    72,   -65,   -65,   -65,   955,   140,   450,   956,   968,
     969,  -234,    73,  1020,   451,   -65,  -234,  1021,  1022,  1055,
     -65,   -65,   -69,   -65,  -428,   452,   674,  1056,  1057,    70,
      71,  1058,   -65,   -65,   -65,    72,   -65,   -65,   -65,   -65,
     -65,    74,   -65,   671,  1075,  -428,   453,    75,   141,   642,
    -428,   587,  1080,  1085,  1086,  1096,  1097,  1098,  1099,  -244,
    1150,  1151,  1152,  1153,   672,  1178,  1248,  1249,  -244,   675,
     817,  1250,  1251,   -65,   -65,   454,   -65,   818,   -65,  1252,
    1253,   455,   141,   -65,   -65,   -65,   -65,   -65,   378,  -244,
    1276,  -244,    70,    71,  -244,   -65,   -65,   -65,    72,   -65,
     -65,   -65,    18,  1263,  1264,  1275,  1281,  1288,   -65,  1289,
     -65,  1290,   568,   -65,   658,   258,  1291,  1292,   588,  1293,
     589,  1294,  -427,   259,   126,   620,   375,    59,  1295,  1296,
     240,  -427,   159,   139,    34,   408,   -65,   -65,   407,   -65,
      69,   -65,   298,   398,   381,   141,   -65,   -65,  1013,   -65,
    -234,   835,  -427,   160,   829,    70,    71,  -427,   -65,   -65,
     -65,    72,   -65,   -65,   -65,  1014,   202,   450,   101,   495,
     312,  -234,    73,  -234,   451,   707,  -234,  1242,   921,   518,
     531,   659,   541,   660,     0,   452,  1015,     0,     0,    70,
      71,  1016,     0,     0,  1243,    72,   265,     0,     0,   -65,
     -65,    74,   -65,   154,   -65,     0,   453,    75,   141,   -65,
     -65,   -65,   -65,   -65,  1246,  1244,     0,     0,    70,    71,
    1245,   -65,   -65,   -65,    72,   -65,   -65,   -65,     0,     0,
       0,  1243,   260,     0,   -65,   454,   -65,   -88,  -167,   -65,
     261,   455,    76,    43,  -160,     0,     0,     0,     0,     0,
      44,     0,  1244,     0,     0,     0,     0,  1247,     0,   139,
     163,   164,   -65,   -65,    74,   -65,    69,   -65,   428,     0,
      75,   141,   -65,   -65,   136,   -65,  -234,     0,   168,     0,
       0,    70,    71,     0,   -65,   -65,   -65,    72,   -65,   -65,
     -65,   169,   170,   879,   171,     0,     0,  -234,    73,  -234,
     654,   -65,     0,   172,   173,   174,   -65,   -65,     0,   -65,
     -65,   452,     0,     0,     0,    70,    71,     0,   -65,   -65,
     -65,    72,   -65,   -65,   -65,   -65,   -65,    74,   -65,   593,
       0,   -65,     0,    75,   141,   642,   -65,   795,   473,     0,
       0,     0,     0,     0,     0,   175,   474,   176,     0,     0,
       0,     0,     0,     0,     0,   330,   817,   594,   595,   -65,
     -65,   454,   -65,   818,  -310,     0,     0,   455,   141,  -310,
    -310,  -310,  -310,  -310,   378,     0,   331,     0,    70,    71,
    1116,  -310,  -310,  -310,    72,  -310,  -310,  -310,  1117,     0,
       0,     0,     0,     0,  -310,     0,  -310,   534,     0,  -310,
     254,    19,     0,     0,    20,     0,     0,     0,   255,     0,
       0,     0,     0,     0,     0,     0,     0,   159,   535,   857,
      21,    22,  -310,  -310,     0,  -310,   858,   -65,   537,     0,
     381,    76,   -65,   -65,    23,  1001,  -346,  -546,   160,     0,
    -232,    70,    71,  -232,   -65,   -65,   -65,    72,   -65,   -65,
     -65,   859,   271,   712,     0,     0,     0,  -346,   860,   272,
    -256,   713,  -346,     0,     0,  -256,  -256,  -256,  -256,  -256,
     534,     0,     0,     0,    70,    71,     0,  -256,  -256,  -256,
      72,  -256,  -256,  -256,     0,   -65,   -65,    74,   -65,     0,
    -256,   535,  -256,  1002,   141,  -256,  -548,   796,     0,     0,
       0,   537,     0,     0,     0,   797,     0,     0,     0,     0,
    -548,     0,     0,     0,   584,   271,  1120,     0,  -256,  -256,
       0,  -256,   272,   -65,  1121,     0,    75,    76,   -65,   -65,
     -65,   -65,   -65,   534,   587,   585,     0,    70,    71,     0,
     -65,   -65,   -65,    72,   -65,   -65,   -65,   169,   170,   890,
     171,     0,     0,   -65,   535,   -65,   891,   -65,   -65,   172,
     173,   174,   -65,   -65,   537,   -65,   -65,   452,     0,     0,
       0,    70,    71,  -546,   -65,   -65,   -65,    72,   -65,   -65,
     -65,   -65,   -65,     0,   -65,     0,     0,   -65,     0,    75,
     141,   642,   -65,     0,  1185,     0,     0,     0,     0,     0,
       0,   588,  1186,   589,     0,   688,     0,     0,     0,     0,
       0,   786,   805,  -403,     0,   -65,   -65,     0,   -65,   580,
    -284,   689,  -403,   455,   141,  -284,  -284,  -284,  -284,  -284,
     378,   658,   787,     0,    70,    71,     0,  -284,  -284,  -284,
      72,     0,   789,  -403,   169,   170,   890,   171,  -403,     0,
    -284,   790,  -284,   891,  -322,  -284,   172,   173,   174,  -322,
    -322,     0,  -322,  -322,   452,     0,     0,     0,    70,    71,
       0,  -322,  -322,  -322,    72,  -322,  -322,  -322,  -284,  -284,
     380,  -284,     0,     0,  -322,     0,   381,    76,     0,  -322,
       0,  1102,     0,     0,     0,     0,     0,     0,   659,  1103,
     660,     0,     0,     0,     0,     0,     0,     0,   534,   265,
     718,     0,  -322,  -322,     0,  -322,   154,  -270,  -547,     0,
     455,    76,  -270,  -270,  -270,  -270,  -270,  -547,     0,   535,
       0,    70,    71,     0,  -270,  -270,  -270,    72,     0,   537,
       0,     0,     0,   879,     0,     0,     0,  -270,  -547,  -270,
     654,  -298,  -270,  -547,     0,     0,  -298,  -298,  -547,  -298,
    -298,   452,     0,     0,     0,    70,    71,  -547,  -298,  -298,
    -298,    72,   800,     0,     0,  -270,  -270,    74,  -270,     0,
     801,  -298,     0,    75,    76,   567,  -298,     0,     0,     0,
       0,     0,   377,  -238,     0,     0,     0,     0,   567,     0,
     594,   595,  -238,   378,     0,   377,  -237,    70,    71,  -298,
    -298,   454,  -298,    72,   874,  -237,   378,   455,    76,     0,
      70,    71,   875,  -238,   379,  -238,    72,   168,  -238,     0,
       0,   671,     0,     0,     0,  -333,  -237,   379,  -237,  1168,
       0,  -237,     0,     0,  -333,     0,  1169,  -356,     0,     0,
       0,     0,   672,   380,     0,   664,  -356,  1170,     0,   381,
      76,    70,    71,   867,     0,  -333,   380,    72,   587,     0,
    -333,  1171,   381,    76,     0,     0,  -362,  -356,  1172,     0,
    1168,     0,  -356,   665,   666,  -362,     0,  1169,  -355,     0,
       0,     0,     0,   139,   175,     0,   176,  -355,  1170,     0,
      69,  -227,    70,    71,     0,     0,  -362,   380,    72,   264,
    -227,  -362,  1171,  1173,    76,    70,    71,  -231,  -355,  1172,
       0,    72,   778,  -355,     0,     0,  -231,     0,     0,     0,
    -658,  -227,    73,  -227,   139,   588,  -227,   589,     0,  -658,
       0,    69,  -226,     0,     0,     0,     0,  -231,   380,  -231,
       0,  -226,  -231,     0,  1173,    76,    70,    71,   450,     0,
    -658,    74,    72,   952,   779,   451,  -421,    75,    76,     0,
    -658,     0,  -226,    73,  -226,  -421,   452,  -226,     0,  -658,
      70,    71,   450,   872,     0,     0,    72,     0,     0,   451,
    -420,   873,     0,     0,     0,     0,  -421,   453,     0,  -420,
     452,  -421,    74,     0,    70,    71,   857,     0,    75,    76,
      72,   665,   666,   858,  -327,     0,     0,     0,     0,     0,
    -420,   453,     0,  -327,     0,  -420,   454,     0,    70,    71,
       0,     0,   455,    76,    72,  1083,     0,     0,   859,     0,
       0,     0,     0,  1084,  -327,   860,   942,   857,     0,  -327,
     454,     0,  1014,     0,   858,  -326,   455,    76,     0,     0,
     827,     0,     0,   786,  -326,     0,   191,   377,     0,    70,
      71,     0,     0,  1015,    74,    72,     0,     0,   378,   859,
     861,    76,    70,    71,   787,  -326,   860,     0,    72,   943,
    -326,  1168,     0,     0,   789,     0,   192,  -221,  1169,   379,
       0,  1061,     0,   790,   190,     0,     0,     0,  1104,  1170,
     191,    69,  1106,    70,    71,    74,  1105,     0,   786,    72,
    1107,   861,    76,  1171,     0,   534,    70,    71,   380,   534,
    1172,     0,    72,     0,   381,    76,     0,     0,     0,   787,
     192,   296,     0,    73,     0,     0,   535,   191,    69,   789,
     535,     0,     0,  1256,  1187,     0,   537,     0,  1062,   380,
     537,  1257,  1188,    70,    71,  1173,    76,   376,     0,    72,
    1243,   786,    74,    68,   377,   567,     0,   192,    75,    76,
      73,   -96,   377,     0,     0,   378,     0,     0,  1108,    70,
      71,  1244,   787,   378,     0,    72,  1109,    70,    71,     0,
       0,   450,   789,    72,     0,   534,   379,  -416,   451,    74,
       0,   790,     0,     0,   379,    75,    76,     0,     0,   452,
    1110,     0,     0,    70,    71,   139,   535,     0,  1111,    72,
       0,   -93,    69,     0,     0,   380,   537,   534,   450,     0,
     453,   381,    76,   380,  -415,   451,     0,    70,    71,   381,
      76,     0,     0,    72,     0,     0,   452,     0,   535,     0,
      70,    71,     0,  1168,    73,     0,    72,     0,   537,   454,
    1169,     0,     0,     0,     0,   455,    76,   453,     0,     0,
       0,  1170,     0,     0,     0,    70,    71,   139,     0,     0,
       0,    72,     0,    74,    69,  1171,   428,  1189,     0,    75,
      76,   567,  1172,     0,     0,  1190,   454,     0,   377,    70,
      71,   857,   455,    76,   786,    72,     0,     0,   858,   378,
       0,     0,     0,    70,    71,   139,    73,     0,     0,    72,
       0,   380,    69,    70,    71,   787,     0,  1173,    76,    72,
     379,     0,     0,   859,     0,   789,     0,    70,    71,     0,
     860,   264,     0,    72,   790,    74,     0,  1191,     0,  -230,
       0,    75,    76,  1112,    73,  1192,     0,     0,   159,   380,
     742,  1113,     0,     0,   786,   381,    76,   743,  -666,    74,
     534,   544,     0,   545,     0,   861,    76,  -666,   546,   160,
     168,  -230,     0,    74,  -230,   787,     0,     0,   257,    75,
      76,   535,     0,   169,   170,   789,   171,     0,  -666,   547,
       0,   537,     0,  -666,   790,   172,   173,   174,  -666,   548,
     549,   550,   551,   552,   553,   554,   555,  -666,   556,   557,
     558,   559,   560,     0,     0,  1114,     0,     0,   742,     0,
     561,   562,   563,  1115,   744,   743,  -666,     0,     0,   544,
       0,   545,   534,   262,     0,  -666,   944,   175,     0,   176,
       0,   263,     0,     0,     0,     0,   169,   170,     0,   171,
       0,     0,     0,   535,     0,     0,  -666,   547,   172,   173,
     174,  -666,     0,   537,     0,     0,  -666,   548,   549,   550,
     551,   552,   553,   554,   555,  -666,   556,   557,   558,   559,
     560,     0,     0,     0,     0,     0,   542,     0,   561,   562,
     563,     0,   945,   543,  -623,     0,     0,   544,     0,   545,
     175,   587,   176,  -623,   546,     0,     0,     0,     0,   794,
       0,     0,     0,     0,   169,   170,     0,   171,     0,     0,
       0,     0,     0,     0,  -623,   547,   172,   173,   174,  -623,
       0,     0,     0,     0,  -623,   548,   549,   550,   551,   552,
     553,   554,   555,  -623,   556,   557,   558,   559,   560,     0,
       0,     0,     0,     0,   542,     0,   561,   562,   563,     0,
     564,   543,  -622,     0,     0,   544,     0,   545,   588,   798,
     589,  -622,   546,     0,     0,     0,     0,   799,     0,     0,
       0,     0,   169,   170,     0,   171,     0,     0,     0,     0,
       0,     0,  -622,   547,   172,   173,   174,  -622,     0,     0,
       0,     0,  -622,   548,   549,   550,   551,   552,   553,   554,
     555,  -622,   556,   557,   558,   559,   560,     0,     0,     0,
       0,     0,   542,     0,   561,   562,   563,     0,   564,   543,
    -611,     0,     0,   544,     0,   545,   588,   658,   589,  -611,
     546,     0,     0,     0,     0,   866,     0,     0,     0,     0,
     169,   170,     0,   171,     0,     0,     0,     0,     0,     0,
    -611,   547,   172,   173,   174,  -611,     0,     0,     0,     0,
    -611,   548,   549,   550,   551,   552,   553,   554,   555,  -611,
     556,   557,   558,   559,   560,     0,     0,     0,     0,     0,
     542,     0,   561,   562,   563,     0,   564,   543,  -609,     0,
       0,   544,     0,   545,   659,   870,   660,  -609,   546,     0,
       0,     0,     0,   871,     0,     0,     0,     0,   169,   170,
       0,   171,     0,     0,     0,     0,     0,     0,  -609,   547,
     172,   173,   174,  -609,     0,     0,     0,     0,  -609,   548,
     549,   550,   551,   552,   553,   554,   555,  -609,   556,   557,
     558,   559,   560,     0,     0,     0,     0,     0,   542,     0,
     561,   562,   563,     0,   564,   543,  -603,     0,     0,   544,
       0,   545,   659,     0,   660,  -603,   546,     0,     0,     0,
       0,     0,     0,  1053,     0,     0,     0,     0,     0,     0,
       0,  -658,     0,     0,     0,     0,  -603,   547,     0,     0,
    -658,  -603,     0,     0,     0,     0,  -603,   548,   549,   550,
     551,   552,   553,   554,   555,  -603,   556,   557,   558,   559,
     560,  -658,     0,     0,  1054,   779,   542,     0,   561,   562,
     563,  -658,   564,   543,  -601,     0,     0,   544,     0,   545,
    -658,     0,     0,  -601,   546,     0,     0,     0,     0,     0,
       0,  1193,     0,     0,     0,  1118,     0,     0,     0,  1194,
       0,     0,     0,  1119,  -601,   547,     0,     0,   786,  -601,
       0,     0,   534,     0,  -601,   548,   549,   550,   551,   552,
     553,   554,   555,  -601,   556,   557,   558,   559,   560,   787,
       0,     0,     0,   535,   542,     0,   561,   562,   563,   789,
     564,   543,  -610,   537,     0,   544,     0,   545,   790,     0,
       0,  -610,   546,     0,     0,     0,     0,     0,     0,  1195,
       0,     0,     0,  1122,     0,     0,     0,  1196,     0,     0,
       0,  1123,  -610,   547,     0,     0,   786,  -610,     0,     0,
     534,     0,  -610,   548,   549,   550,   551,   552,   553,   554,
     555,  -610,   556,   557,   558,   559,   560,   787,     0,     0,
       0,   535,   542,     0,   561,   562,   563,   789,   564,   543,
    -607,   537,     0,   544,     0,   545,   790,     0,     0,  -607,
     546,     0,     0,     0,     0,     0,     0,  1197,     0,     0,
       0,  1124,     0,     0,     0,  1198,     0,     0,     0,  1125,
    -607,   547,     0,     0,   786,  -607,     0,     0,   534,     0,
    -607,   548,   549,   550,   551,   552,   553,   554,   555,  -607,
     556,   557,   558,   559,   560,   787,     0,     0,     0,   535,
     542,     0,   561,   562,   563,   789,   564,   543,  -602,   537,
       0,   544,     0,   545,   790,     0,     0,  -602,   546,     0,
       0,     0,     0,     0,     0,  1199,     0,     0,     0,  1126,
       0,     0,     0,  1200,     0,     0,     0,  1127,  -602,   547,
       0,     0,   786,  -602,     0,     0,   534,     0,  -602,   548,
     549,   550,   551,   552,   553,   554,   555,  -602,   556,   557,
     558,   559,   560,   787,     0,     0,     0,   535,   542,     0,
     561,   562,   563,   789,   564,   543,  -599,   537,     0,   544,
       0,   545,   790,     0,     0,  -599,   546,     0,     0,     0,
       0,     0,     0,  1208,     0,     0,     0,  1128,     0,     0,
       0,  1209,     0,     0,     0,  1129,  -599,   547,     0,     0,
     786,  -599,     0,     0,   534,     0,  -599,   548,   549,   550,
     551,   552,   553,   554,   555,  -599,   556,   557,   558,   559,
     560,   787,     0,     0,     0,   535,   542,     0,   561,   562,
     563,   789,   564,   543,  -595,   537,     0,   544,     0,   545,
     790,     0,     0,  -595,   546,     0,     0,     0,     0,     0,
       0,  1210,     0,     0,     0,  1130,     0,     0,     0,  1211,
       0,     0,     0,  1131,  -595,   547,     0,     0,   786,  -595,
       0,     0,   534,     0,  -595,   548,   549,   550,   551,   552,
     553,   554,   555,  -595,   556,   557,   558,   559,   560,   787,
       0,     0,     0,   535,   542,     0,   561,   562,   563,   789,
     564,   543,  -593,   537,     0,   544,     0,   545,   790,     0,
       0,  -593,   546,     0,     0,     0,     0,     0,     0,  1212,
       0,     0,     0,  1132,     0,     0,     0,  1213,     0,     0,
       0,  1133,  -593,   547,     0,     0,   786,  -593,     0,     0,
     534,     0,  -593,   548,   549,   550,   551,   552,   553,   554,
     555,  -593,   556,   557,   558,   559,   560,   787,     0,     0,
       0,   535,   542,     0,   561,   562,   563,   789,   564,   543,
    -594,   537,     0,   544,     0,   545,   790,     0,     0,  -594,
     546,     0,     0,     0,     0,     0,     0,  1214,     0,     0,
       0,  1134,     0,     0,     0,  1215,     0,     0,     0,  1135,
    -594,   547,     0,     0,   786,  -594,     0,     0,   534,     0,
    -594,   548,   549,   550,   551,   552,   553,   554,   555,  -594,
     556,   557,   558,   559,   560,   787,     0,     0,     0,   535,
     542,     0,   561,   562,   563,   789,   564,   543,  -591,   537,
       0,   544,     0,   545,   790,     0,     0,  -591,   546,     0,
       0,     0,     0,     0,     0,  1216,     0,     0,     0,  1136,
       0,     0,     0,  1217,     0,     0,     0,  1137,  -591,   547,
       0,     0,   786,  -591,     0,     0,   534,     0,  -591,   548,
     549,   550,   551,   552,   553,   554,   555,  -591,   556,   557,
     558,   559,   560,   787,     0,     0,     0,   535,   542,     0,
     561,   562,   563,   789,   564,   543,  -619,   537,     0,   544,
       0,   545,   790,     0,     0,  -619,   546,     0,     0,     0,
       0,     0,     0,  1218,     0,     0,     0,  1138,     0,     0,
       0,  1219,     0,     0,     0,  1139,  -619,   547,     0,     0,
     786,  -619,     0,     0,   534,     0,  -619,   548,   549,   550,
     551,   552,   553,   554,   555,  -619,   556,   557,   558,   559,
     560,   787,     0,     0,     0,   535,   542,     0,   561,   562,
     563,   789,   564,   543,  -617,   537,     0,   544,     0,   545,
     790,     0,     0,  -617,   546,     0,     0,     0,     0,     0,
       0,  1220,     0,     0,     0,     0,     0,     0,     0,  1221,
       0,     0,     0,     0,  -617,   547,     0,     0,   786,  -617,
       0,     0,     0,     0,  -617,   548,   549,   550,   551,   552,
     553,   554,   555,  -617,   556,   557,   558,   559,   560,   787,
       0,     0,     0,     0,   542,     0,   561,   562,   563,   789,
     564,   543,  -618,     0,     0,   544,     0,   545,   790,     0,
       0,  -618,   546,     0,     0,     0,     0,     0,     0,  1222,
       0,     0,     0,     0,     0,     0,     0,  1223,     0,     0,
       0,     0,  -618,   547,     0,     0,   786,  -618,     0,     0,
       0,     0,  -618,   548,   549,   550,   551,   552,   553,   554,
     555,  -618,   556,   557,   558,   559,   560,   787,     0,     0,
       0,     0,   542,     0,   561,   562,   563,   789,   564,   543,
    -615,     0,     0,   544,     0,   545,   790,     0,     0,  -615,
     546,     0,     0,     0,     0,     0,     0,   924,     0,     0,
       0,     0,     0,     0,     0,  -565,     0,     0,     0,     0,
    -615,   547,     0,     0,  -565,  -615,     0,     0,     0,     0,
    -615,   548,   549,   550,   551,   552,   553,   554,   555,  -615,
     556,   557,   558,   559,   560,  -565,     0,     0,   925,   529,
    -565,   497,   561,   562,   563,  -565,   564,  -507,   498,     0,
       0,     0,     0,     0,  -565,     0,     0,     0,  -573,   345,
       0,     0,     0,     0,     0,     0,     0,     0,   342,     0,
     264,     0,     0,     0,   343,   344,   499,     0,  -228,  -573,
     346,     0,     0,     0,  -573,     0,   345,  -228,  -500,  -573,
     347,   348,   349,   350,   351,   352,   353,   354,   538,   355,
     356,   357,   358,   359,   539,  -667,     0,   346,  -228,  -667,
    -228,  -667,     0,  -228,     0,   360,  -667,   347,   348,   349,
     350,   351,   352,   353,   354,   542,   355,   356,   357,   358,
     359,  -582,   543,     0,     0,     0,   544,  -667,   545,     0,
       0,     0,   360,   546,     0,     0,     0,  -667,  -667,  -667,
    -667,  -667,  -667,  -667,  -667,     0,  -667,  -667,  -667,  -667,
    -667,     0,     0,     0,   547,   718,     0,     0,  -667,  -667,
    -667,   367,  -667,  -550,   548,   549,   550,   551,   552,   553,
     554,   555,  -550,   556,   557,   558,   559,   560,     0,     0,
       0,     0,     0,     0,   542,   561,   562,   563,  -582,   564,
    -584,   543,     0,  -550,   -77,   544,     0,   545,  -550,     0,
     223,  -141,   546,  -550,     0,     0,     0,   224,     0,     0,
       0,  -148,  -550,     0,   542,     0,     0,     0,     0,     0,
       0,   543,     0,   547,   -77,   544,     0,   545,     0,     0,
       0,   225,   546,   548,   549,   550,   551,   552,   553,   554,
     555,     0,   556,   557,   558,   559,   560,   970,   971,     0,
       0,     0,     0,   547,   561,   562,   563,  -584,   564,     0,
       0,     0,     0,   548,   549,   550,   551,   552,   553,   554,
     555,   207,   556,   557,   558,   559,   560,   480,   208,     0,
     366,     0,     0,     0,   561,   562,   563,  -667,   564,   209,
       0,  -667,     0,  -667,     0,  1010,     0,     0,  -667,     0,
       0,     0,     0,  -384,     0,     0,  -438,     0,  -384,  -384,
     210,  -384,     0,     0,     0,     0,   481,  -438,  -438,  -667,
    -384,  -384,  -384,  -384,  -384,  -384,  -384,     0,     0,  -667,
    -667,  -667,  -667,  -667,  -667,  -667,  -667,  1011,  -667,  -667,
    -667,  -667,  -667,     0,     0,   211,     0,     0,   497,     0,
    -667,  -667,  -667,   367,  -667,   498,  -573,     0,     0,     0,
       0,  -384,  -384,     0,  -384,  -573,   708,     0,     0,     0,
       0,     0,     0,     0,     0,   497,     0,   207,     0,     0,
       0,     0,   498,  -573,   208,  -465,  -573,   346,     0,     0,
       0,  -573,  -573,   345,  -465,   209,  -573,   347,   348,   349,
     350,   351,   352,   353,   354,  -573,   355,   356,   357,   358,
     359,     0,     0,  -573,   346,  -465,   210,     0,  -573,   320,
    -465,     0,   709,  -573,   347,   348,   349,   350,   351,   352,
     353,   354,  -573,   355,   356,   357,   358,   359,   497,     0,
       0,     0,     0,     0,     0,   498,     0,     0,     0,   360,
       0,   321,     0,     0,     0,  -573,   345,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1224,   718,     0,     0,
       0,     0,     0,   499,  1225,  -551,  -573,   346,     0,     0,
       0,  -573,     0,   786,  -551,  -500,  -573,   347,   348,   349,
     350,   351,   352,   353,   354,     0,   355,   356,   357,   358,
     359,   505,     0,     0,   787,  -551,     0,     0,   344,  -543,
    -551,     0,   360,     0,   789,  -551,     0,     0,  -543,   345,
       0,     0,     0,   790,  -551,     0,   471,     0,   505,     0,
     264,     0,     0,     0,   472,   344,  -542,     0,  -229,  -543,
     346,     0,     0,   330,  -543,  -542,   345,   159,     0,  -543,
     347,   348,   349,   350,   351,   352,   353,   354,  -543,   355,
     356,   357,   358,   359,   331,     0,  -542,   346,  -229,  -449,
    -229,  -542,     0,  -229,     0,   360,  -542,   347,   348,   349,
     350,   351,   352,   353,   354,  -542,   355,   356,   357,   358,
     359,   505,     0,     0,     0,   477,     0,     0,   344,  -531,
       0,     0,   360,  -448,     0,     0,     0,     0,  -531,   345,
       0,     0,  -448,     0,     0,     0,     0,     0,   505,     0,
     792,     0,     0,     0,     0,   344,  -529,     0,   793,  -531,
     346,     0,     0,  -448,  -531,  -529,   345,   584,  -448,  -531,
     347,   348,   349,   350,   351,   352,   353,   354,  -531,   355,
     356,   357,   358,   359,     0,     0,  -529,   346,   585,     0,
    -243,  -529,     0,  -243,     0,   360,  -529,   347,   348,   349,
     350,   351,   352,   353,   354,  -529,   355,   356,   357,   358,
     359,   505,     0,     0,     0,   477,     0,     0,   344,  -523,
       0,     0,   360,  -447,     0,     0,     0,     0,  -523,   345,
       0,     0,   330,     0,     0,     0,     0,     0,   505,     0,
     804,     0,     0,     0,     0,   344,  -521,     0,  -242,  -523,
     346,     0,     0,   331,  -523,  -521,   345,  -242,  -447,  -523,
     347,   348,   349,   350,   351,   352,   353,   354,  -523,   355,
     356,   357,   358,   359,     0,     0,  -521,   346,  -242,     0,
    -242,  -521,     0,  -242,     0,   360,  -521,   347,   348,   349,
     350,   351,   352,   353,   354,  -521,   355,   356,   357,   358,
     359,   505,     0,     0,     0,   477,     0,     0,   344,  -530,
       0,     0,   360,  -445,     0,     0,     0,     0,  -530,   345,
       0,     0,  -445,     0,     0,     0,     0,     0,   505,     0,
     804,     0,     0,     0,     0,   344,  -527,     0,  -241,  -530,
     346,     0,     0,  -445,  -530,  -527,   345,   584,  -445,  -530,
     347,   348,   349,   350,   351,   352,   353,   354,  -530,   355,
     356,   357,   358,   359,     0,     0,  -527,   346,   585,     0,
    -241,  -527,     0,  -241,     0,   360,  -527,   347,   348,   349,
     350,   351,   352,   353,   354,  -527,   355,   356,   357,   358,
     359,   505,     0,     0,     0,   477,     0,     0,   344,  -522,
       0,     0,   360,  -446,     0,     0,     0,     0,  -522,   345,
       0,     0,   330,     0,     0,     0,     0,     0,   505,     0,
     804,     0,     0,     0,     0,   344,  -519,     0,  -239,  -522,
     346,     0,     0,  -446,  -522,  -519,   345,  -239,  -446,  -522,
     347,   348,   349,   350,   351,   352,   353,   354,  -522,   355,
     356,   357,   358,   359,     0,     0,  -519,   346,  -239,     0,
    -239,  -519,     0,  -239,     0,   360,  -519,   347,   348,   349,
     350,   351,   352,   353,   354,  -519,   355,   356,   357,   358,
     359,   505,     0,     0,     0,   868,     0,     0,   344,  -515,
       0,     0,   360,   869,     0,     0,     0,     0,  -515,   345,
       0,     0,   671,     0,     0,     0,     0,     0,   505,     0,
     804,     0,     0,     0,     0,   344,  -513,     0,  -240,  -515,
     346,     0,     0,   672,  -515,  -513,   345,   584,  -426,  -515,
     347,   348,   349,   350,   351,   352,   353,   354,  -515,   355,
     356,   357,   358,   359,     0,     0,  -513,   346,  -240,     0,
    -240,  -513,     0,  -240,     0,   360,  -513,   347,   348,   349,
     350,   351,   352,   353,   354,  -513,   355,   356,   357,   358,
     359,   505,     0,     0,     0,   878,     0,     0,   344,  -514,
       0,     0,   360,  -425,     0,     0,     0,     0,  -514,   345,
       0,     0,  -425,     0,     0,     0,     0,     0,   505,     0,
     878,     0,     0,     0,     0,   344,  -511,     0,  -424,  -514,
     346,     0,     0,  -425,  -514,  -511,   345,   671,  -425,  -514,
     347,   348,   349,   350,   351,   352,   353,   354,  -514,   355,
     356,   357,   358,   359,     0,     0,  -511,   346,   672,     0,
       0,  -511,     0,  -424,     0,   360,  -511,   347,   348,   349,
     350,   351,   352,   353,   354,  -511,   355,   356,   357,   358,
     359,   505,     0,     0,     0,   878,     0,     0,   344,  -539,
       0,     0,   360,  -422,     0,     0,     0,     0,  -539,   345,
       0,     0,  -422,     0,     0,     0,     0,     0,   505,     0,
     878,     0,     0,     0,     0,   344,  -537,     0,  -423,  -539,
     346,     0,     0,  -422,  -539,  -537,   345,   671,  -422,  -539,
     347,   348,   349,   350,   351,   352,   353,   354,  -539,   355,
     356,   357,   358,   359,     0,     0,  -537,   346,  -423,     0,
       0,  -537,     0,  -423,     0,   360,  -537,   347,   348,   349,
     350,   351,   352,   353,   354,  -537,   355,   356,   357,   358,
     359,   505,     0,     0,     0,  1081,     0,     0,   344,  -538,
       0,     0,   360,  1082,     0,     0,     0,     0,  -538,   345,
       0,     0,  1014,     0,     0,     0,     0,     0,   505,     0,
    1013,     0,     0,     0,     0,   344,  -535,     0,  -331,  -538,
     346,     0,     0,  1015,  -538,  -535,   345,  -331,  -332,  -538,
     347,   348,   349,   350,   351,   352,   353,   354,  -538,   355,
     356,   357,   358,   359,     0,     0,  -535,   346,  -331,     0,
       0,  -535,     0,  -331,     0,   360,  -535,   347,   348,   349,
     350,   351,   352,   353,   354,  -535,   355,   356,   357,   358,
     359,     0,   542,     0,     0,     0,  1013,     0,     0,   543,
       0,     0,   360,   544,  -330,   545,     0,     0,     0,     0,
     546,     0,     0,  1014,     0,     0,     0,     0,     0,   542,
       0,     0,     0,     0,     0,     0,   543,     0,     0,     0,
     544,   547,   545,     0,  1015,     0,     0,   748,     0,  -330,
       0,   548,   549,   550,   551,   552,   553,   554,   555,     0,
     556,   557,   558,   559,   560,     0,     0,     0,   547,   528,
       0,     0,   561,   562,   563,     0,   564,  -565,   548,   549,
     550,   551,   552,   553,   554,   555,  -565,   556,   557,   558,
     559,   560,     0,     0,     0,   542,     0,     0,     0,   561,
     562,   563,   543,   749,     0,     0,   544,  -565,   545,     0,
       0,   529,  -565,   946,     0,     0,     0,  -565,     0,     0,
    1013,     0,   542,     0,     0,     0,  -565,     0,  -328,   543,
       0,     0,     0,   544,   547,   545,     0,  -328,     0,     0,
     546,     0,     0,     0,   548,   549,   550,   551,   552,   553,
     554,   555,     0,   556,   557,   558,   559,   560,  -328,     0,
       0,   547,   778,  -328,     0,   561,   562,   563,     0,   947,
    -658,   548,   549,   550,   551,   552,   553,   554,   555,  -658,
     556,   557,   558,   559,   560,     0,     0,     0,   542,     0,
       0,     0,   561,   562,   563,   543,  1145,     0,     0,   544,
    -658,   545,     0,     0,   779,  -658,   546,  1226,     0,     0,
    -658,     0,     0,     0,     0,  1227,     0,     0,   505,  -658,
       0,     0,     0,     0,   786,   344,     0,   547,     0,     0,
       0,     0,     0,     0,     0,     0,   345,   548,   549,   550,
     551,   552,   553,   554,   555,   787,   556,   557,   558,   559,
     560,   727,   728,     0,     0,   789,     0,   346,   561,   562,
     563,     0,  1148,     0,   790,     0,     0,   347,   348,   349,
     350,   351,   352,   353,   354,   530,   355,   356,   357,   358,
     359,   343,   344,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   360,   345,     0,     0,     0,     0,     0,     0,
       0,   505,     0,  1013,  1254,  1265,     0,  -504,   344,     0,
       0,  -329,  1255,  -360,   346,     0,     0,     0,     0,   345,
    1014,  1243,  -360,     0,   347,   348,   349,   350,   351,   352,
     353,   354,     0,   355,   356,   357,   358,   359,     0,     0,
     346,  -329,  1244,  -360,     0,     0,  -329,  -361,  -360,   360,
     347,   348,   349,   350,   351,   352,   353,   354,   505,   355,
     356,   357,   358,   359,  -506,   344,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   360,   345,     0,     0,     0,
       0,     0,     0,     0,   505,     0,  -381,  1265,  1265,     0,
       0,   344,     0,     0,  -381,  -359,  -357,   346,     0,     0,
       0,     0,   345,  -381,  1243,  -357,     0,   347,   348,   349,
     350,   351,   352,   353,   354,     0,   355,   356,   357,   358,
     359,     0,     0,   346,  -381,  1244,  -357,     0,     0,  -381,
    -359,  -357,   360,   347,   348,   349,   350,   351,   352,   353,
     354,   505,   355,   356,   357,   358,   359,  1239,   344,     0,
       0,     0,     0,     0,     0,  -389,     0,     0,   360,   710,
    -389,  -389,     0,  -389,     0,     0,     0,     0,     0,     0,
       0,     0,  -389,  -389,  -389,  -389,  -389,  -389,  -389,     0,
     346,     0,     0,     0,     0,     0,     0,     0,     0,  1240,
     347,   348,   349,   350,   351,   352,   353,   354,     0,   355,
     356,   357,   358,   359,   165,     0,     0,     0,     0,     0,
       0,     0,  -249,  -389,  -389,   711,  -389,  -249,  -249,  -249,
    -249,  -249,     0,     0,     0,     0,     0,     0,     0,  -249,
    -249,  -249,  -249,  -249,   166,   167,     0,   165,     0,     0,
    1265,     0,  -249,     0,  -249,  -248,     0,  -249,  -358,     0,
    -248,  -248,  -248,  -248,  -248,     0,     0,  1243,     0,     0,
       0,     0,  -248,  -248,  -248,  -248,  -248,   166,   167,     0,
    -249,  -249,     0,  -249,     0,  -248,   718,  -248,  -358,     0,
    -248,     0,   165,  -358,  -552,     0,     0,     0,     0,     0,
    -247,     0,     0,  -552,     0,  -247,  -247,  -247,  -247,  -247,
       0,     0,     0,  -248,  -248,     0,  -248,  -247,  -247,  -247,
    -247,  -247,   166,   167,  -552,   165,     0,     0,     0,  -552,
    -247,     0,  -247,  -246,  -552,  -247,     0,     0,  -246,  -246,
    -246,  -246,  -246,  -552,     0,     0,     0,     0,     0,     0,
    -246,  -246,  -246,  -246,  -246,   166,   167,     0,  -247,  -247,
       0,  -247,     0,  -246,   718,  -246,     0,     0,  -246,     0,
     596,     0,  -553,     0,     0,     0,     0,     0,  -303,     0,
       0,  -553,     0,  -303,  -303,  -303,  -303,  -303,     0,     0,
       0,  -246,  -246,     0,  -246,  -303,  -303,  -303,  -303,  -303,
     597,   598,  -553,   596,     0,     0,     0,  -553,  -303,     0,
    -303,  -302,  -553,  -303,     0,     0,  -302,  -302,  -302,  -302,
    -302,  -553,     0,     0,     0,     0,     0,     0,  -302,  -302,
    -302,  -302,  -302,   597,   598,     0,  -303,  -303,     0,  -303,
       0,  -302,   718,  -302,     0,     0,  -302,     0,   596,     0,
    -554,     0,     0,     0,     0,     0,  -301,     0,     0,  -554,
       0,  -301,  -301,  -301,  -301,  -301,     0,     0,     0,  -302,
    -302,     0,  -302,  -301,  -301,  -301,  -301,  -301,   597,   598,
    -554,   596,     0,     0,   718,  -554,  -301,     0,  -301,  -300,
    -554,  -301,  -555,     0,  -300,  -300,  -300,  -300,  -300,  -554,
       0,  -555,     0,     0,     0,     0,  -300,  -300,  -300,  -300,
    -300,   597,   598,     0,  -301,  -301,     0,  -301,     0,  -300,
       0,  -300,  -555,     0,  -300,     0,   656,  -555,     0,     0,
       0,     0,  -555,     0,  -395,     0,     0,     0,     0,  -395,
    -395,  -555,  -395,  -395,     0,     0,     0,  -300,  -300,     0,
    -300,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  1010,     0,
       0,     0,     0,     0,  -395,     0,  -337,     0,   657,  -395,
       0,  -384,  -384,     0,  -384,  -337,     0,     0,     0,     0,
       0,     0,     0,  -384,  -384,  -384,  -384,  -384,  -384,  -384,
    1239,     0,  -395,  -395,     0,  -395,  -337,     0,  -366,     0,
    1011,  -337,     0,  -389,  -389,     0,  -389,  -366,     0,     0,
       0,     0,     0,     0,     0,  -389,  -389,  -389,  -389,  -389,
    -389,  -389,   162,     0,  -384,  -384,     0,  -384,  -366,     0,
    -271,     0,  1240,  -366,     0,  -271,  -271,  -271,  -271,  -271,
       0,     0,     0,     0,     0,     0,     0,  -271,  -271,  -271,
     163,   164,     0,     0,     0,   162,  -389,  -389,     0,  -389,
    -271,     0,  -271,   256,     0,  -271,     0,     0,  -271,  -271,
    -271,  -271,  -271,     0,     0,     0,     0,     0,     0,     0,
    -271,  -271,  -271,   163,   164,     0,     0,     0,  -271,  -271,
       0,  -271,     0,  -271,   718,  -271,     0,     0,  -271,     0,
     593,     0,  -546,     0,     0,     0,     0,     0,  -285,     0,
       0,   534,     0,  -285,  -285,  -285,  -285,  -285,     0,     0,
       0,  -271,  -271,     0,  -271,  -285,  -285,  -285,   594,   595,
       0,     0,   535,   667,     0,     0,     0,  -546,  -285,     0,
    -285,  -315,   537,  -285,     0,     0,  -315,  -315,     0,  -315,
    -315,  -546,     0,     0,     0,     0,     0,     0,  -315,  -315,
    -315,  -315,  -315,   668,   669,   593,  -285,  -285,     0,  -285,
       0,  -315,     0,   795,     0,     0,  -315,     0,  -285,  -285,
    -285,  -285,  -285,     0,     0,     0,     0,     0,     0,     0,
    -285,  -285,  -285,   594,   595,     0,     0,     0,   667,  -315,
    -315,     0,  -315,  -285,     0,  -285,  -314,     0,  -285,     0,
       0,  -314,  -314,     0,  -314,  -314,     0,     0,     0,     0,
       0,     0,     0,  -314,  -314,  -314,  -314,  -314,   668,   669,
     667,  -285,  -285,     0,  -285,     0,  -314,     0,  -313,     0,
       0,  -314,     0,  -313,  -313,     0,  -313,  -313,     0,     0,
       0,     0,     0,     0,     0,  -313,  -313,  -313,  -313,  -313,
     668,   669,   667,     0,  -314,  -314,     0,  -314,  -313,     0,
    -312,     0,     0,  -313,     0,  -312,  -312,     0,  -312,  -312,
       0,     0,     0,     0,     0,     0,     0,  -312,  -312,  -312,
    -312,  -312,   668,   669,   178,     0,  -313,  -313,     0,  -313,
    -312,     0,  -261,     0,     0,  -312,     0,  -261,  -261,  -261,
    -261,  -261,     0,     0,     0,     0,     0,     0,     0,  -261,
    -261,  -261,     0,     0,     0,     0,     0,   178,  -312,  -312,
       0,  -312,  -261,     0,  -261,  -260,     0,  -261,     0,     0,
    -260,  -260,  -260,  -260,  -260,     0,     0,     0,     0,     0,
       0,     0,  -260,  -260,  -260,     0,     0,     0,     0,     0,
     179,  -261,     0,  -261,   178,  -260,     0,  -260,     0,     0,
    -260,     0,  -258,     0,     0,     0,     0,  -258,  -258,  -258,
    -258,  -258,     0,     0,   178,     0,     0,     0,     0,  -258,
    -258,  -258,  -259,   179,  -260,     0,  -260,  -259,  -259,  -259,
    -259,  -259,  -258,     0,  -258,     0,     0,  -258,     0,  -259,
    -259,  -259,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   591,  -259,     0,  -259,     0,     0,  -259,     0,  -275,
     179,  -258,     0,  -258,  -275,  -275,  -275,  -275,  -275,     0,
       0,   664,     0,     0,     0,     0,  -275,  -275,  -275,  -299,
     179,  -259,     0,  -259,  -299,  -299,     0,  -299,  -299,  -275,
       0,  -275,     0,     0,  -275,     0,  -299,  -299,  -299,   665,
     666,     0,     0,     0,     0,     0,     0,     0,     0,  -299,
       0,     0,     0,     0,  -299,     0,   664,   592,  -275,     0,
    -275,     0,     0,     0,   867,     0,     0,     0,     0,  -299,
    -299,     0,  -299,  -299,     0,     0,     0,  -299,  -299,     0,
    -299,  -299,  -299,  -299,   665,   666,     0,     0,   591,     0,
       0,     0,     0,     0,  -299,     0,  -274,     0,     0,  -299,
       0,  -274,  -274,  -274,  -274,  -274,     0,     0,     0,     0,
       0,     0,     0,  -274,  -274,  -274,     0,     0,     0,     0,
       0,   591,  -299,  -299,     0,  -299,  -274,     0,  -274,  -272,
       0,  -274,     0,     0,  -272,  -272,  -272,  -272,  -272,     0,
       0,     0,     0,     0,     0,     0,  -272,  -272,  -272,     0,
       0,     0,     0,     0,   592,  -274,     0,  -274,   591,  -272,
       0,  -272,     0,     0,  -272,     0,  -273,     0,     0,     0,
       0,  -273,  -273,  -273,  -273,  -273,     0,     0,   662,     0,
       0,     0,     0,  -273,  -273,  -273,  -289,   592,  -272,     0,
    -272,  -289,  -289,     0,  -289,  -289,  -273,     0,  -273,     0,
       0,  -273,     0,  -289,  -289,  -289,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   662,  -289,     0,     0,     0,
       0,  -289,     0,  -288,   592,  -273,     0,  -273,  -288,  -288,
       0,  -288,  -288,     0,     0,   662,     0,     0,     0,     0,
    -288,  -288,  -288,  -286,   663,  -289,     0,  -289,  -286,  -286,
       0,  -286,  -286,  -288,     0,     0,     0,     0,  -288,     0,
    -286,  -286,  -286,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   662,  -286,     0,     0,     0,     0,  -286,     0,
    -287,   663,  -288,     0,  -288,  -287,  -287,     0,  -287,  -287,
       0,     0,   260,     0,     0,     0,     0,  -287,  -287,  -287,
     261,   663,  -286,     0,  -286,  -271,  -271,     0,  -271,     0,
    -287,     0,     0,     0,     0,  -287,     0,  -271,  -271,  -271,
     163,   164,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   800,   663,  -287,
       0,  -287,     0,     0,     0,   801,     0,     0,     0,     0,
    -285,  -285,     0,  -285,     0,     0,     0,     0,  -271,  -271,
     872,  -271,  -285,  -285,  -285,   594,   595,  1049,   873,     0,
       0,     0,     0,  -299,  -299,  -658,  -299,     0,     0,     0,
       0,   948,     0,     0,  -658,  -299,  -299,  -299,   665,   666,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   778,
       0,     0,     0,  -285,  -285,  -658,  -285,  -658,  1050,   779,
    -658,   718,     0,   948,   718,  -658,  -658,   718,     0,  -544,
       0,     0,  -545,     0,  -658,  -549,  -299,  -299,  -544,  -299,
       0,   534,     0,     0,   534,     0,     0,  -658,     0,     0,
       0,   779,  -658,     0,     0,     0,     0,  -658,     0,  -544,
     949,     0,  -545,   961,  -544,   535,  -658,  -545,   950,  -544,
    -549,  -627,  -545,     0,     0,   537,     0,   786,  -544,     0,
    -627,  -545,     0,   961,  -549,   961,     0,   961,     0,     0,
       0,  -630,     0,  -631,     0,  -632,     0,     0,   787,     0,
    -630,  -627,  -631,  -628,  -632,   961,  -627,   961,   789,     0,
       0,  -627,     0,  -633,     0,  -634,     0,   790,     0,     0,
    -627,  -630,  -633,  -631,  -634,  -632,  -630,     0,  -631,   961,
    -632,  -630,     0,  -631,     0,  -632,     0,  -635,     0,     0,
    -630,   961,  -631,  -633,  -632,  -634,  -635,     0,  -633,  -654,
    -634,     0,   961,  -633,     0,  -634,     0,     0,  -654,     0,
    -655,     0,  -633,   961,  -634,  1059,     0,  -635,     0,  -655,
       0,  -656,  -635,  -648,     0,     0,     0,  -635,     0,  -654,
    -656,     0,   786,     0,  -654,   961,  -635,     0,   961,  -654,
    -655,     0,     0,  -645,     0,  -655,  -646,     0,  -654,     0,
    -655,  -656,  -645,   787,     0,  -646,  -656,     0,  -648,  -655,
     961,  -656,     0,   789,     0,     0,     0,   961,  -647,     0,
    -656,   961,  1060,  -645,     0,  -626,  -646,  -647,  -645,  -624,
       0,  -646,   961,  -645,   786,     0,  -646,     0,  -624,   961,
    -625,     0,  -645,     0,     0,  -646,     0,  -629,  -647,   786,
       0,     0,     0,  -647,   961,   787,   786,     0,  -647,  -624,
    -626,     0,  -657,     0,  -624,   789,     0,  -647,     0,  -624,
    -625,   786,     0,     0,   790,  -625,  1205,   787,  -624,     0,
    -625,     0,  -629,  1207,  1206,     0,     0,   789,     0,  -625,
       0,  -657,   787,   786,     0,     0,  -629,  -657,   961,   961,
     786,   961,   789,     0,     0,   961,  -653,  -652,     0,  -651,
       0,   790,     0,  -650,   787,  -653,  -652,     0,  -651,  -626,
       0,   787,  -650,     0,   789,     0,  -657,     0,     0,     0,
       0,   789,     0,   790,     0,     0,  -653,  -652,     0,  -651,
     790,  -653,  -652,  -650,  -651,     0,  -653,  -652,  -650,  -651,
       0,   928,     0,  -650,     0,  -653,  -652,     0,  -651,  -565,
       0,     0,  -650,     0,     0,     0,     0,     0,  -565,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -565,
       0,     0,   929,   529,     0,     0,     0,     0,     0,  -565
  };

  /* YYCHECK.  */
  const short int
  mcmas_parser::yycheck_[] =
  {
        28,   386,   434,   450,   436,   295,    67,   454,    69,   401,
     194,   192,    96,   303,   450,   451,   197,   111,   439,    79,
     376,   377,   990,   233,   376,   248,     1,   599,   380,   639,
     253,   396,   202,   231,   825,    67,   194,    69,   196,    67,
     612,    69,   240,    28,   409,    73,    74,   111,   218,   840,
     450,   451,    17,     1,   705,     1,   707,     3,   664,   665,
     666,    19,   285,    14,   658,   659,   660,     1,   376,   377,
       1,    99,   457,   587,   588,   589,    26,     8,   139,     1,
      67,    29,    67,     1,    69,     7,     8,    74,    73,    74,
       1,     1,   153,   154,   168,   593,   594,   595,     1,    19,
      75,   175,   176,   162,   163,   164,    16,   139,    19,    43,
    1078,   139,    23,    24,    99,    33,   177,    75,    29,     7,
      66,   153,   154,    40,    75,   153,   154,   106,    76,   190,
     158,   159,   160,    25,   162,   163,   164,   165,   166,   167,
     168,   299,   312,   470,    75,   230,   240,   175,   176,   177,
     178,   179,   139,    75,   139,    75,    19,    75,   190,    47,
     110,     1,   190,     0,    75,    76,   194,   231,   153,   154,
     230,    11,    75,   158,   159,   160,   240,   162,   163,   164,
     165,   166,   167,   168,    76,   570,   396,    75,   262,   574,
     175,   176,   177,   178,   179,    19,   113,   420,   421,   409,
     423,   260,    42,   190,   265,   190,     1,   599,   999,   194,
     408,   567,    75,   241,   242,   567,   400,   653,   654,   640,
     612,   318,   319,   579,   580,    75,   254,   288,   207,   208,
     258,   210,   260,   265,   262,   296,   264,   265,     1,   271,
     272,     1,     1,   271,   272,   601,   611,   857,   858,   601,
     860,    75,    47,   653,   654,   219,   288,     1,   643,   567,
     288,   661,   647,     7,   296,   202,   872,   839,   296,   254,
     921,   579,   580,   258,   302,   260,   870,   262,   265,   264,
     265,   218,   590,   220,   798,    17,   271,   272,    48,    48,
     318,   319,   377,   601,   379,     1,     1,     1,     1,   132,
       1,   288,   800,   288,     1,   138,    25,    10,    27,   296,
      29,   296,    75,    17,   398,   400,    22,   302,    19,    22,
      61,     1,     1,    29,   384,    66,    29,     7,     8,    34,
      35,    75,     1,   318,   319,  1076,  1077,     1,     7,     3,
      59,    60,     1,    75,   408,    42,    65,   180,     7,   676,
      91,   330,   331,   450,   451,    19,   453,   684,   685,   686,
     687,   688,   689,   690,   691,     1,   369,    46,     1,    75,
      76,     7,     8,    76,    75,   312,   313,    75,   342,    17,
     344,    45,   346,   347,   348,   349,   350,   351,   352,   130,
     131,     1,     1,     1,    17,    75,   137,     1,   362,     7,
     623,   611,     1,   340,  1014,  1015,    75,     1,     7,    42,
     129,    75,     1,   246,   247,     1,    75,    11,   602,   252,
      19,     7,   450,   451,   605,   453,   454,  1168,  1169,    33,
      19,  1172,   879,    42,    23,    24,    46,    75,     1,    75,
      29,   469,   470,   879,   602,    44,   604,   839,    11,   805,
       1,     1,    75,   805,   890,   891,    19,     8,     1,     1,
       1,   817,   818,     1,     7,   450,   451,    75,   453,   454,
     826,   827,    23,    24,   826,   827,    75,   862,    29,   879,
      21,    75,    20,     1,   469,   470,    75,    76,     1,    75,
       8,     1,    34,     7,     7,     1,    46,   805,   583,   584,
     585,    19,  1243,  1244,   245,    11,    20,     1,     1,    19,
     447,     1,    75,     7,     1,     8,    44,   602,   826,   827,
       7,     1,    40,     1,    75,    76,    19,     7,     1,    44,
      23,    24,    75,   497,   498,     8,    29,     1,   541,   542,
     543,   505,     1,   833,   547,   548,   549,   550,   551,   552,
     553,   515,   516,     1,    44,     1,   988,    75,   561,   562,
     563,    75,    75,     9,     1,    75,   530,    45,     1,    75,
     534,   535,    36,   537,   671,   672,    69,   638,   639,     1,
       1,    75,    75,    76,    48,    44,   419,     8,    75,   617,
     618,     1,     6,   621,   622,    75,    44,    44,     8,    21,
      33,     1,    75,     3,     1,     1,     1,    44,     1,    19,
     638,   639,     8,    23,    24,    10,    38,    34,  1003,    29,
    1005,     1,    68,     1,    70,   653,   654,    41,    75,     9,
     658,   659,   660,   661,   662,   663,   664,   665,   666,   667,
     668,   669,   670,   671,   672,    45,   674,    44,   676,    42,
      71,    72,    73,   638,   639,     1,   684,   685,   686,   687,
     688,   689,   690,   691,    42,    75,    76,     1,   653,   654,
       1,    28,   830,   658,   659,   660,   661,   662,   663,   664,
     665,   666,   667,   668,   669,   670,   671,   672,    68,   674,
      70,   676,    23,    24,     1,    11,    42,    43,    29,   684,
     685,   686,   687,   688,   689,   690,   691,   792,    42,     3,
     555,   796,    69,     1,    10,    17,    73,    46,     1,   804,
     565,     1,     1,    11,     1,    19,    42,    10,    44,     9,
       1,    33,     9,     1,     1,    42,    16,     8,    18,   742,
     743,     8,    99,     1,    75,    76,    75,   832,    19,     7,
       8,    45,    23,    24,    42,     1,    23,    24,    29,   762,
     763,    19,    29,     9,    43,    23,    24,  1075,  1076,  1077,
      16,    29,    18,    75,    42,    33,    20,   780,   781,   782,
     783,    75,    40,   786,   787,    76,   789,   790,    68,  1174,
      70,    68,     1,    70,    17,    36,   857,   858,    69,   860,
      44,   158,   159,   160,    75,    76,    47,    48,    75,    76,
      33,    69,  1168,  1169,    23,    24,  1168,    75,    76,    17,
      29,     6,    68,     8,    70,   857,   858,     1,     1,   857,
     858,    16,   860,    18,     1,    33,     1,   194,     1,     1,
     868,     1,   870,    17,   872,  1230,   874,  1232,     8,     9,
     878,   879,    75,    15,     1,    18,     1,     1,    18,    19,
    1168,  1169,   890,   891,  1172,     6,    75,    76,    41,    43,
     857,    75,   857,   858,    41,   860,    39,    75,    43,    39,
      40,     1,    41,   868,    44,   870,    49,   872,     8,   874,
      75,     1,    36,   878,   879,    58,    43,   254,    43,    19,
      41,   258,     1,    23,    24,   890,   891,   264,     1,    29,
       1,     6,    11,     8,     1,    75,    45,    37,     1,     1,
      40,    16,     9,    18,    34,    35,     8,    10,    21,    64,
      65,     1,     1,  1241,  1242,  1243,  1244,    19,  1246,     9,
       9,    23,    24,    42,     1,   302,  1254,    29,  1256,    69,
      41,  1012,  1013,  1014,  1015,    75,    76,  1265,   922,   923,
     924,   925,   926,   927,   928,   929,   930,   931,   932,   933,
     934,   935,   936,   937,   938,   939,   940,   941,     1,    36,
      75,    68,     1,    70,  1012,  1013,  1014,  1015,    44,     1,
      47,    48,     9,    75,    76,    18,     1,     1,    68,    68,
      70,    70,     1,     1,    16,    10,    18,    11,     6,    44,
      12,     1,    14,     1,     1,     1,    39,    34,     8,    75,
    1081,     8,  1083,    42,    43,     1,    49,  1012,  1013,  1014,
    1015,    17,    19,    23,    24,    58,    23,    24,    42,    29,
      75,    17,    29,    42,  1047,  1048,  1049,  1050,  1051,  1052,
    1053,  1054,    10,  1081,    42,  1083,  1059,  1060,  1061,  1062,
    1063,  1064,  1065,  1066,  1067,  1068,  1069,  1070,  1071,    71,
      72,    73,    74,     1,    34,    35,    25,     1,    27,    69,
       1,     5,     6,     7,     8,    75,    76,     1,    75,    76,
      14,    15,     1,    17,    18,    19,  1081,    18,  1083,    23,
      24,     4,    26,    27,    28,    29,    30,    31,    32,     4,
      59,    10,     1,    37,    42,    39,    40,    41,    39,    43,
       1,     1,     1,    44,     1,     1,    21,    41,    49,     8,
      10,    34,     8,    42,    43,     1,    25,    58,    41,    34,
       1,     7,     8,    67,    68,    69,    70,  1150,  1151,  1152,
    1153,    75,    76,     1,     1,     1,     4,    23,    24,     7,
       8,    42,    43,    29,    25,    42,    14,    15,     1,    17,
      18,    19,    18,     1,    40,    23,    24,     1,    26,    27,
      28,    29,    30,    31,    32,    18,    34,    11,    42,    43,
       1,    39,    40,    39,    41,    43,    44,     1,    44,    10,
      34,    35,     1,    69,     8,     9,    39,     1,     1,    75,
      76,    44,    11,    41,    18,    19,    49,     1,    42,    67,
      68,    69,    70,    17,    17,     1,     1,    75,    76,     5,
       6,     7,     8,     8,     5,    39,    40,     1,    14,    15,
      44,    17,    18,    42,     8,     3,     1,    23,    24,     4,
      26,    27,    28,    29,    30,    31,    32,    41,     1,    75,
       1,    37,     5,    39,    40,    41,    21,     1,     9,     1,
       1,    75,     1,     4,     8,     4,     5,    18,     7,    34,
       1,    10,    11,     1,    75,    19,    18,     5,    17,    23,
      24,    67,    68,    69,    70,    29,    17,     1,    39,    75,
      76,     5,     6,     7,     8,    34,    75,    39,    49,    41,
      14,    15,    41,    17,    18,     1,    75,    58,     4,    23,
      24,     1,    26,    27,    28,    29,    30,    31,    32,   165,
     166,   167,     1,    37,     1,    39,    40,    41,    18,     1,
       7,    75,    76,     9,     9,    12,    75,    14,    34,    18,
       1,     1,    18,    18,     1,    17,     6,     8,     5,    39,
       1,    41,    11,    67,    68,    69,    70,     8,     9,    36,
      39,    75,    76,    14,    15,    44,    17,    18,    19,    75,
      49,    48,    23,    24,     1,    26,    27,    28,    29,    30,
      31,    32,     9,    42,     1,    44,    75,     1,    39,    40,
      41,    18,    43,    44,    71,    72,    73,    74,    75,     1,
      17,     1,     4,    17,     1,    43,     6,     1,     1,     1,
       7,     3,    39,     1,     7,    11,    67,    68,    69,    70,
       8,     9,    49,    17,    75,    76,    14,    15,    16,    17,
      18,    19,    34,     1,    17,    23,    24,     1,    26,    27,
      28,    29,    30,    31,    32,     9,    42,     1,    44,    17,
       1,    39,     1,    41,    18,    43,    44,     8,     7,    10,
       1,     4,     5,    17,     1,     1,     1,    10,    19,     4,
       1,     7,    23,    24,    17,    39,    17,     1,    29,    67,
      68,    69,    70,     7,     8,    49,    17,    75,    76,    40,
      14,    15,     1,    17,    18,    19,    34,    35,    41,    23,
      24,    46,    26,    27,    28,    29,    30,    31,    32,    18,
     596,   597,   598,    37,     1,    39,    40,    41,    69,    43,
       7,     1,     5,   355,    75,    76,   358,    10,   556,     9,
      39,   559,    34,    35,    17,    44,   356,   357,    18,   359,
       1,   178,   179,    67,    68,    69,    70,     8,     9,    10,
      10,    75,    76,    14,    15,     1,    17,    18,    19,    39,
      75,    41,    23,    24,    44,    26,    27,    28,    29,    30,
      31,    32,    18,     1,   557,   558,    47,   560,    39,    40,
      41,     9,    43,    75,     5,   667,   668,   669,    68,    10,
      70,    48,     1,    39,     3,     1,    17,     3,    44,   834,
     835,    29,    30,     1,    12,     1,    67,    68,    69,    70,
       8,     9,    43,     9,    75,    76,    14,    15,    76,    17,
      18,    19,    18,     1,    75,    23,    24,     1,    26,    27,
      28,    29,    30,    31,    32,    33,    16,     1,    18,     3,
      18,    39,    40,    39,    18,    43,    44,    43,     1,   591,
     592,     4,     5,    49,     7,   662,   663,    10,    11,   917,
     918,    39,    58,    75,    17,    39,    44,     3,    75,    67,
      68,    69,    70,     1,    75,    49,     4,    75,    76,     7,
       8,    34,    75,    75,    58,    75,    14,    15,    41,    17,
      18,    75,    75,    75,    75,    23,    24,    43,    26,    27,
      28,    29,    30,    31,    32,    75,    34,     1,    75,    75,
      75,    39,    40,    43,     8,     9,    44,    43,    43,    75,
      14,    15,    75,    17,    18,    19,     1,    75,    13,    23,
      24,    15,    26,    27,    28,    29,    30,    31,    32,    67,
      68,    69,    70,    18,    17,    39,    40,    75,    76,    43,
      44,     1,    75,    75,    75,    75,    75,    75,    75,     9,
       9,     9,    13,    15,    39,    75,    75,    75,    18,    44,
       1,    75,    75,    67,    68,    69,    70,     8,     9,    75,
      75,    75,    76,    14,    15,    16,    17,    18,    19,    39,
       1,    41,    23,    24,    44,    26,    27,    28,    29,    30,
      31,    32,     5,    75,    75,    75,    75,    75,    39,    75,
      41,    75,    43,    44,     1,     1,    75,    75,    68,    75,
      70,    75,     9,     9,    57,   416,   228,    25,    75,    75,
     113,    18,    18,     1,     8,   240,    67,    68,   238,    70,
       8,     9,   194,   232,    75,    76,    14,    15,     1,    17,
      18,   607,    39,    39,   602,    23,    24,    44,    26,    27,
      28,    29,    30,    31,    32,    18,   101,     1,    34,   338,
     202,    39,    40,    41,     8,   494,    44,     1,   707,   354,
     362,    68,   368,    70,    -1,    19,    39,    -1,    -1,    23,
      24,    44,    -1,    -1,    18,    29,     1,    -1,    -1,    67,
      68,    69,    70,     8,     9,    -1,    40,    75,    76,    14,
      15,    16,    17,    18,     1,    39,    -1,    -1,    23,    24,
      44,    26,    27,    28,    29,    30,    31,    32,    -1,    -1,
      -1,    18,     1,    -1,    39,    69,    41,     4,     5,    44,
       9,    75,    76,    10,    11,    -1,    -1,    -1,    -1,    -1,
      17,    -1,    39,    -1,    -1,    -1,    -1,    44,    -1,     1,
      29,    30,    67,    68,    69,    70,     8,     9,    10,    -1,
      75,    76,    14,    15,    41,    17,    18,    -1,     1,    -1,
      -1,    23,    24,    -1,    26,    27,    28,    29,    30,    31,
      32,    14,    15,     1,    17,    -1,    -1,    39,    40,    41,
       8,     9,    -1,    26,    27,    28,    14,    15,    -1,    17,
      18,    19,    -1,    -1,    -1,    23,    24,    -1,    26,    27,
      28,    29,    30,    31,    32,    67,    68,    69,    70,     1,
      -1,    39,    -1,    75,    76,    43,    44,     9,     1,    -1,
      -1,    -1,    -1,    -1,    -1,    68,     9,    70,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    18,     1,    29,    30,    67,
      68,    69,    70,     8,     9,    -1,    -1,    75,    76,    14,
      15,    16,    17,    18,    19,    -1,    39,    -1,    23,    24,
       1,    26,    27,    28,    29,    30,    31,    32,     9,    -1,
      -1,    -1,    -1,    -1,    39,    -1,    41,    18,    -1,    44,
       1,     1,    -1,    -1,     4,    -1,    -1,    -1,     9,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    18,    39,     1,
      20,    21,    67,    68,    -1,    70,     8,     9,    49,    -1,
      75,    76,    14,    15,    34,    17,    18,    58,    39,    -1,
      41,    23,    24,    44,    26,    27,    28,    29,    30,    31,
      32,    33,     1,     1,    -1,    -1,    -1,    39,    40,     8,
       9,     9,    44,    -1,    -1,    14,    15,    16,    17,    18,
      18,    -1,    -1,    -1,    23,    24,    -1,    26,    27,    28,
      29,    30,    31,    32,    -1,    67,    68,    69,    70,    -1,
      39,    39,    41,    75,    76,    44,    44,     1,    -1,    -1,
      -1,    49,    -1,    -1,    -1,     9,    -1,    -1,    -1,    -1,
      58,    -1,    -1,    -1,    18,     1,     1,    -1,    67,    68,
      -1,    70,     8,     9,     9,    -1,    75,    76,    14,    15,
      16,    17,    18,    18,     1,    39,    -1,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    14,    15,     1,
      17,    -1,    -1,    39,    39,    41,     8,     9,    44,    26,
      27,    28,    14,    15,    49,    17,    18,    19,    -1,    -1,
      -1,    23,    24,    58,    26,    27,    28,    29,    30,    31,
      32,    67,    68,    -1,    70,    -1,    -1,    39,    -1,    75,
      76,    43,    44,    -1,     1,    -1,    -1,    -1,    -1,    -1,
      -1,    68,     9,    70,    -1,     1,    -1,    -1,    -1,    -1,
      -1,    18,     1,     9,    -1,    67,    68,    -1,    70,     8,
       9,    17,    18,    75,    76,    14,    15,    16,    17,    18,
      19,     1,    39,    -1,    23,    24,    -1,    26,    27,    28,
      29,    -1,    49,    39,    14,    15,     1,    17,    44,    -1,
      39,    58,    41,     8,     9,    44,    26,    27,    28,    14,
      15,    -1,    17,    18,    19,    -1,    -1,    -1,    23,    24,
      -1,    26,    27,    28,    29,    30,    31,    32,    67,    68,
      69,    70,    -1,    -1,    39,    -1,    75,    76,    -1,    44,
      -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,    68,     9,
      70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    18,     1,
       1,    -1,    67,    68,    -1,    70,     8,     9,     9,    -1,
      75,    76,    14,    15,    16,    17,    18,    18,    -1,    39,
      -1,    23,    24,    -1,    26,    27,    28,    29,    -1,    49,
      -1,    -1,    -1,     1,    -1,    -1,    -1,    39,    39,    41,
       8,     9,    44,    44,    -1,    -1,    14,    15,    49,    17,
      18,    19,    -1,    -1,    -1,    23,    24,    58,    26,    27,
      28,    29,     1,    -1,    -1,    67,    68,    69,    70,    -1,
       9,    39,    -1,    75,    76,     1,    44,    -1,    -1,    -1,
      -1,    -1,     8,     9,    -1,    -1,    -1,    -1,     1,    -1,
      29,    30,    18,    19,    -1,     8,     9,    23,    24,    67,
      68,    69,    70,    29,     1,    18,    19,    75,    76,    -1,
      23,    24,     9,    39,    40,    41,    29,     1,    44,    -1,
      -1,    18,    -1,    -1,    -1,     9,    39,    40,    41,     1,
      -1,    44,    -1,    -1,    18,    -1,     8,     9,    -1,    -1,
      -1,    -1,    39,    69,    -1,     1,    18,    19,    -1,    75,
      76,    23,    24,     9,    -1,    39,    69,    29,     1,    -1,
      44,    33,    75,    76,    -1,    -1,     9,    39,    40,    -1,
       1,    -1,    44,    29,    30,    18,    -1,     8,     9,    -1,
      -1,    -1,    -1,     1,    68,    -1,    70,    18,    19,    -1,
       8,     9,    23,    24,    -1,    -1,    39,    69,    29,     1,
      18,    44,    33,    75,    76,    23,    24,     9,    39,    40,
      -1,    29,     1,    44,    -1,    -1,    18,    -1,    -1,    -1,
       9,    39,    40,    41,     1,    68,    44,    70,    -1,    18,
      -1,     8,     9,    -1,    -1,    -1,    -1,    39,    69,    41,
      -1,    18,    44,    -1,    75,    76,    23,    24,     1,    -1,
      39,    69,    29,    42,    43,     8,     9,    75,    76,    -1,
      49,    -1,    39,    40,    41,    18,    19,    44,    -1,    58,
      23,    24,     1,     1,    -1,    -1,    29,    -1,    -1,     8,
       9,     9,    -1,    -1,    -1,    -1,    39,    40,    -1,    18,
      19,    44,    69,    -1,    23,    24,     1,    -1,    75,    76,
      29,    29,    30,     8,     9,    -1,    -1,    -1,    -1,    -1,
      39,    40,    -1,    18,    -1,    44,    69,    -1,    23,    24,
      -1,    -1,    75,    76,    29,     1,    -1,    -1,    33,    -1,
      -1,    -1,    -1,     9,    39,    40,     1,     1,    -1,    44,
      69,    -1,    18,    -1,     8,     9,    75,    76,    -1,    -1,
       1,    -1,    -1,    18,    18,    -1,     7,     8,    -1,    23,
      24,    -1,    -1,    39,    69,    29,    -1,    -1,    19,    33,
      75,    76,    23,    24,    39,    39,    40,    -1,    29,    44,
      44,     1,    -1,    -1,    49,    -1,    37,     7,     8,    40,
      -1,     1,    -1,    58,     1,    -1,    -1,    -1,     1,    19,
       7,     8,     1,    23,    24,    69,     9,    -1,    18,    29,
       9,    75,    76,    33,    -1,    18,    23,    24,    69,    18,
      40,    -1,    29,    -1,    75,    76,    -1,    -1,    -1,    39,
      37,     1,    -1,    40,    -1,    -1,    39,     7,     8,    49,
      39,    -1,    -1,     1,     1,    -1,    49,    -1,    58,    69,
      49,     9,     9,    23,    24,    75,    76,     1,    -1,    29,
      18,    18,    69,     7,     8,     1,    -1,    37,    75,    76,
      40,     7,     8,    -1,    -1,    19,    -1,    -1,     1,    23,
      24,    39,    39,    19,    -1,    29,     9,    23,    24,    -1,
      -1,     1,    49,    29,    -1,    18,    40,     7,     8,    69,
      -1,    58,    -1,    -1,    40,    75,    76,    -1,    -1,    19,
       1,    -1,    -1,    23,    24,     1,    39,    -1,     9,    29,
      -1,     7,     8,    -1,    -1,    69,    49,    18,     1,    -1,
      40,    75,    76,    69,     7,     8,    -1,    23,    24,    75,
      76,    -1,    -1,    29,    -1,    -1,    19,    -1,    39,    -1,
      23,    24,    -1,     1,    40,    -1,    29,    -1,    49,    69,
       8,    -1,    -1,    -1,    -1,    75,    76,    40,    -1,    -1,
      -1,    19,    -1,    -1,    -1,    23,    24,     1,    -1,    -1,
      -1,    29,    -1,    69,     8,    33,    10,     1,    -1,    75,
      76,     1,    40,    -1,    -1,     9,    69,    -1,     8,    23,
      24,     1,    75,    76,    18,    29,    -1,    -1,     8,    19,
      -1,    -1,    -1,    23,    24,     1,    40,    -1,    -1,    29,
      -1,    69,     8,    23,    24,    39,    -1,    75,    76,    29,
      40,    -1,    -1,    33,    -1,    49,    -1,    23,    24,    -1,
      40,     1,    -1,    29,    58,    69,    -1,     1,    -1,     9,
      -1,    75,    76,     1,    40,     9,    -1,    -1,    18,    69,
       1,     9,    -1,    -1,    18,    75,    76,     8,     9,    69,
      18,    12,    -1,    14,    -1,    75,    76,    18,    19,    39,
       1,    41,    -1,    69,    44,    39,    -1,    -1,     9,    75,
      76,    39,    -1,    14,    15,    49,    17,    -1,    39,    40,
      -1,    49,    -1,    44,    58,    26,    27,    28,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    -1,    -1,     1,    -1,    -1,     1,    -1,
      71,    72,    73,     9,    75,     8,     9,    -1,    -1,    12,
      -1,    14,    18,     1,    -1,    18,    19,    68,    -1,    70,
      -1,     9,    -1,    -1,    -1,    -1,    14,    15,    -1,    17,
      -1,    -1,    -1,    39,    -1,    -1,    39,    40,    26,    27,
      28,    44,    -1,    49,    -1,    -1,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    -1,    -1,    -1,    -1,    -1,     1,    -1,    71,    72,
      73,    -1,    75,     8,     9,    -1,    -1,    12,    -1,    14,
      68,     1,    70,    18,    19,    -1,    -1,    -1,    -1,     9,
      -1,    -1,    -1,    -1,    14,    15,    -1,    17,    -1,    -1,
      -1,    -1,    -1,    -1,    39,    40,    26,    27,    28,    44,
      -1,    -1,    -1,    -1,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    -1,
      -1,    -1,    -1,    -1,     1,    -1,    71,    72,    73,    -1,
      75,     8,     9,    -1,    -1,    12,    -1,    14,    68,     1,
      70,    18,    19,    -1,    -1,    -1,    -1,     9,    -1,    -1,
      -1,    -1,    14,    15,    -1,    17,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    40,    26,    27,    28,    44,    -1,    -1,
      -1,    -1,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    -1,    -1,    -1,
      -1,    -1,     1,    -1,    71,    72,    73,    -1,    75,     8,
       9,    -1,    -1,    12,    -1,    14,    68,     1,    70,    18,
      19,    -1,    -1,    -1,    -1,     9,    -1,    -1,    -1,    -1,
      14,    15,    -1,    17,    -1,    -1,    -1,    -1,    -1,    -1,
      39,    40,    26,    27,    28,    44,    -1,    -1,    -1,    -1,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    -1,    -1,    -1,    -1,    -1,
       1,    -1,    71,    72,    73,    -1,    75,     8,     9,    -1,
      -1,    12,    -1,    14,    68,     1,    70,    18,    19,    -1,
      -1,    -1,    -1,     9,    -1,    -1,    -1,    -1,    14,    15,
      -1,    17,    -1,    -1,    -1,    -1,    -1,    -1,    39,    40,
      26,    27,    28,    44,    -1,    -1,    -1,    -1,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    -1,    -1,    -1,    -1,    -1,     1,    -1,
      71,    72,    73,    -1,    75,     8,     9,    -1,    -1,    12,
      -1,    14,    68,    -1,    70,    18,    19,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     9,    -1,    -1,    -1,    -1,    39,    40,    -1,    -1,
      18,    44,    -1,    -1,    -1,    -1,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    39,    -1,    -1,    42,    43,     1,    -1,    71,    72,
      73,    49,    75,     8,     9,    -1,    -1,    12,    -1,    14,
      58,    -1,    -1,    18,    19,    -1,    -1,    -1,    -1,    -1,
      -1,     1,    -1,    -1,    -1,     1,    -1,    -1,    -1,     9,
      -1,    -1,    -1,     9,    39,    40,    -1,    -1,    18,    44,
      -1,    -1,    18,    -1,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    39,
      -1,    -1,    -1,    39,     1,    -1,    71,    72,    73,    49,
      75,     8,     9,    49,    -1,    12,    -1,    14,    58,    -1,
      -1,    18,    19,    -1,    -1,    -1,    -1,    -1,    -1,     1,
      -1,    -1,    -1,     1,    -1,    -1,    -1,     9,    -1,    -1,
      -1,     9,    39,    40,    -1,    -1,    18,    44,    -1,    -1,
      18,    -1,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    39,    -1,    -1,
      -1,    39,     1,    -1,    71,    72,    73,    49,    75,     8,
       9,    49,    -1,    12,    -1,    14,    58,    -1,    -1,    18,
      19,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,
      -1,     1,    -1,    -1,    -1,     9,    -1,    -1,    -1,     9,
      39,    40,    -1,    -1,    18,    44,    -1,    -1,    18,    -1,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    39,    -1,    -1,    -1,    39,
       1,    -1,    71,    72,    73,    49,    75,     8,     9,    49,
      -1,    12,    -1,    14,    58,    -1,    -1,    18,    19,    -1,
      -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,    -1,     1,
      -1,    -1,    -1,     9,    -1,    -1,    -1,     9,    39,    40,
      -1,    -1,    18,    44,    -1,    -1,    18,    -1,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    39,    -1,    -1,    -1,    39,     1,    -1,
      71,    72,    73,    49,    75,     8,     9,    49,    -1,    12,
      -1,    14,    58,    -1,    -1,    18,    19,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    -1,    -1,    -1,     1,    -1,    -1,
      -1,     9,    -1,    -1,    -1,     9,    39,    40,    -1,    -1,
      18,    44,    -1,    -1,    18,    -1,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    39,    -1,    -1,    -1,    39,     1,    -1,    71,    72,
      73,    49,    75,     8,     9,    49,    -1,    12,    -1,    14,
      58,    -1,    -1,    18,    19,    -1,    -1,    -1,    -1,    -1,
      -1,     1,    -1,    -1,    -1,     1,    -1,    -1,    -1,     9,
      -1,    -1,    -1,     9,    39,    40,    -1,    -1,    18,    44,
      -1,    -1,    18,    -1,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    39,
      -1,    -1,    -1,    39,     1,    -1,    71,    72,    73,    49,
      75,     8,     9,    49,    -1,    12,    -1,    14,    58,    -1,
      -1,    18,    19,    -1,    -1,    -1,    -1,    -1,    -1,     1,
      -1,    -1,    -1,     1,    -1,    -1,    -1,     9,    -1,    -1,
      -1,     9,    39,    40,    -1,    -1,    18,    44,    -1,    -1,
      18,    -1,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    39,    -1,    -1,
      -1,    39,     1,    -1,    71,    72,    73,    49,    75,     8,
       9,    49,    -1,    12,    -1,    14,    58,    -1,    -1,    18,
      19,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,
      -1,     1,    -1,    -1,    -1,     9,    -1,    -1,    -1,     9,
      39,    40,    -1,    -1,    18,    44,    -1,    -1,    18,    -1,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    39,    -1,    -1,    -1,    39,
       1,    -1,    71,    72,    73,    49,    75,     8,     9,    49,
      -1,    12,    -1,    14,    58,    -1,    -1,    18,    19,    -1,
      -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,    -1,     1,
      -1,    -1,    -1,     9,    -1,    -1,    -1,     9,    39,    40,
      -1,    -1,    18,    44,    -1,    -1,    18,    -1,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    39,    -1,    -1,    -1,    39,     1,    -1,
      71,    72,    73,    49,    75,     8,     9,    49,    -1,    12,
      -1,    14,    58,    -1,    -1,    18,    19,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    -1,    -1,    -1,     1,    -1,    -1,
      -1,     9,    -1,    -1,    -1,     9,    39,    40,    -1,    -1,
      18,    44,    -1,    -1,    18,    -1,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    39,    -1,    -1,    -1,    39,     1,    -1,    71,    72,
      73,    49,    75,     8,     9,    49,    -1,    12,    -1,    14,
      58,    -1,    -1,    18,    19,    -1,    -1,    -1,    -1,    -1,
      -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,
      -1,    -1,    -1,    -1,    39,    40,    -1,    -1,    18,    44,
      -1,    -1,    -1,    -1,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    39,
      -1,    -1,    -1,    -1,     1,    -1,    71,    72,    73,    49,
      75,     8,     9,    -1,    -1,    12,    -1,    14,    58,    -1,
      -1,    18,    19,    -1,    -1,    -1,    -1,    -1,    -1,     1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,    -1,    -1,
      -1,    -1,    39,    40,    -1,    -1,    18,    44,    -1,    -1,
      -1,    -1,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    39,    -1,    -1,
      -1,    -1,     1,    -1,    71,    72,    73,    49,    75,     8,
       9,    -1,    -1,    12,    -1,    14,    58,    -1,    -1,    18,
      19,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     9,    -1,    -1,    -1,    -1,
      39,    40,    -1,    -1,    18,    44,    -1,    -1,    -1,    -1,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    39,    -1,    -1,    42,    43,
      44,     1,    71,    72,    73,    49,    75,     7,     8,    -1,
      -1,    -1,    -1,    -1,    58,    -1,    -1,    -1,    18,    19,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,
       1,    -1,    -1,    -1,     7,     8,    36,    -1,     9,    39,
      40,    -1,    -1,    -1,    44,    -1,    19,    18,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,     1,    59,
      60,    61,    62,    63,     7,     8,    -1,    40,    39,    12,
      41,    14,    -1,    44,    -1,    75,    19,    50,    51,    52,
      53,    54,    55,    56,    57,     1,    59,    60,    61,    62,
      63,     7,     8,    -1,    -1,    -1,    12,    40,    14,    -1,
      -1,    -1,    75,    19,    -1,    -1,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    61,    62,
      63,    -1,    -1,    -1,    40,     1,    -1,    -1,    71,    72,
      73,    74,    75,     9,    50,    51,    52,    53,    54,    55,
      56,    57,    18,    59,    60,    61,    62,    63,    -1,    -1,
      -1,    -1,    -1,    -1,     1,    71,    72,    73,    74,    75,
       7,     8,    -1,    39,     4,    12,    -1,    14,    44,    -1,
      10,    11,    19,    49,    -1,    -1,    -1,    17,    -1,    -1,
      -1,    21,    58,    -1,     1,    -1,    -1,    -1,    -1,    -1,
      -1,     8,    -1,    40,    34,    12,    -1,    14,    -1,    -1,
      -1,    41,    19,    50,    51,    52,    53,    54,    55,    56,
      57,    -1,    59,    60,    61,    62,    63,    34,    35,    -1,
      -1,    -1,    -1,    40,    71,    72,    73,    74,    75,    -1,
      -1,    -1,    -1,    50,    51,    52,    53,    54,    55,    56,
      57,     1,    59,    60,    61,    62,    63,     7,     8,    -1,
       1,    -1,    -1,    -1,    71,    72,    73,     8,    75,    19,
      -1,    12,    -1,    14,    -1,     1,    -1,    -1,    19,    -1,
      -1,    -1,    -1,     9,    -1,    -1,    36,    -1,    14,    15,
      40,    17,    -1,    -1,    -1,    -1,    46,    47,    48,    40,
      26,    27,    28,    29,    30,    31,    32,    -1,    -1,    50,
      51,    52,    53,    54,    55,    56,    57,    43,    59,    60,
      61,    62,    63,    -1,    -1,    75,    -1,    -1,     1,    -1,
      71,    72,    73,    74,    75,     8,     9,    -1,    -1,    -1,
      -1,    67,    68,    -1,    70,    18,    19,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     1,    -1,     1,    -1,    -1,
      -1,    -1,     8,     9,     8,     9,    39,    40,    -1,    -1,
      -1,    44,    18,    19,    18,    19,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    -1,    -1,    39,    40,    39,    40,    -1,    44,    43,
      44,    -1,    75,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,     1,    -1,
      -1,    -1,    -1,    -1,    -1,     8,    -1,    -1,    -1,    75,
      -1,    75,    -1,    -1,    -1,    18,    19,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     1,     1,    -1,    -1,
      -1,    -1,    -1,    36,     9,     9,    39,    40,    -1,    -1,
      -1,    44,    -1,    18,    18,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    61,    62,
      63,     1,    -1,    -1,    39,    39,    -1,    -1,     8,     9,
      44,    -1,    75,    -1,    49,    49,    -1,    -1,    18,    19,
      -1,    -1,    -1,    58,    58,    -1,     1,    -1,     1,    -1,
       1,    -1,    -1,    -1,     9,     8,     9,    -1,     9,    39,
      40,    -1,    -1,    18,    44,    18,    19,    18,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    39,    -1,    39,    40,    39,    44,
      41,    44,    -1,    44,    -1,    75,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,     1,    -1,    -1,    -1,     1,    -1,    -1,     8,     9,
      -1,    -1,    75,     9,    -1,    -1,    -1,    -1,    18,    19,
      -1,    -1,    18,    -1,    -1,    -1,    -1,    -1,     1,    -1,
       1,    -1,    -1,    -1,    -1,     8,     9,    -1,     9,    39,
      40,    -1,    -1,    39,    44,    18,    19,    18,    44,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    -1,    -1,    39,    40,    39,    -1,
      41,    44,    -1,    44,    -1,    75,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,     1,    -1,    -1,    -1,     1,    -1,    -1,     8,     9,
      -1,    -1,    75,     9,    -1,    -1,    -1,    -1,    18,    19,
      -1,    -1,    18,    -1,    -1,    -1,    -1,    -1,     1,    -1,
       1,    -1,    -1,    -1,    -1,     8,     9,    -1,     9,    39,
      40,    -1,    -1,    39,    44,    18,    19,    18,    44,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    -1,    -1,    39,    40,    39,    -1,
      41,    44,    -1,    44,    -1,    75,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,     1,    -1,    -1,    -1,     1,    -1,    -1,     8,     9,
      -1,    -1,    75,     9,    -1,    -1,    -1,    -1,    18,    19,
      -1,    -1,    18,    -1,    -1,    -1,    -1,    -1,     1,    -1,
       1,    -1,    -1,    -1,    -1,     8,     9,    -1,     9,    39,
      40,    -1,    -1,    39,    44,    18,    19,    18,    44,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    -1,    -1,    39,    40,    39,    -1,
      41,    44,    -1,    44,    -1,    75,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,     1,    -1,    -1,    -1,     1,    -1,    -1,     8,     9,
      -1,    -1,    75,     9,    -1,    -1,    -1,    -1,    18,    19,
      -1,    -1,    18,    -1,    -1,    -1,    -1,    -1,     1,    -1,
       1,    -1,    -1,    -1,    -1,     8,     9,    -1,     9,    39,
      40,    -1,    -1,    39,    44,    18,    19,    18,    44,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    -1,    -1,    39,    40,    39,    -1,
      41,    44,    -1,    44,    -1,    75,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,     1,    -1,    -1,    -1,     1,    -1,    -1,     8,     9,
      -1,    -1,    75,     9,    -1,    -1,    -1,    -1,    18,    19,
      -1,    -1,    18,    -1,    -1,    -1,    -1,    -1,     1,    -1,
       1,    -1,    -1,    -1,    -1,     8,     9,    -1,     9,    39,
      40,    -1,    -1,    39,    44,    18,    19,    18,    44,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    -1,    -1,    39,    40,    39,    -1,
      41,    44,    -1,    44,    -1,    75,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,     1,    -1,    -1,    -1,     1,    -1,    -1,     8,     9,
      -1,    -1,    75,     9,    -1,    -1,    -1,    -1,    18,    19,
      -1,    -1,    18,    -1,    -1,    -1,    -1,    -1,     1,    -1,
       1,    -1,    -1,    -1,    -1,     8,     9,    -1,     9,    39,
      40,    -1,    -1,    39,    44,    18,    19,    18,    44,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    -1,    -1,    39,    40,    39,    -1,
      -1,    44,    -1,    44,    -1,    75,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,     1,    -1,    -1,    -1,     1,    -1,    -1,     8,     9,
      -1,    -1,    75,     9,    -1,    -1,    -1,    -1,    18,    19,
      -1,    -1,    18,    -1,    -1,    -1,    -1,    -1,     1,    -1,
       1,    -1,    -1,    -1,    -1,     8,     9,    -1,     9,    39,
      40,    -1,    -1,    39,    44,    18,    19,    18,    44,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    -1,    -1,    39,    40,    39,    -1,
      -1,    44,    -1,    44,    -1,    75,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,     1,    -1,    -1,    -1,     1,    -1,    -1,     8,     9,
      -1,    -1,    75,     9,    -1,    -1,    -1,    -1,    18,    19,
      -1,    -1,    18,    -1,    -1,    -1,    -1,    -1,     1,    -1,
       1,    -1,    -1,    -1,    -1,     8,     9,    -1,     9,    39,
      40,    -1,    -1,    39,    44,    18,    19,    18,    44,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    -1,    -1,    39,    40,    39,    -1,
      -1,    44,    -1,    44,    -1,    75,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    -1,     1,    -1,    -1,    -1,     1,    -1,    -1,     8,
      -1,    -1,    75,    12,     9,    14,    -1,    -1,    -1,    -1,
      19,    -1,    -1,    18,    -1,    -1,    -1,    -1,    -1,     1,
      -1,    -1,    -1,    -1,    -1,    -1,     8,    -1,    -1,    -1,
      12,    40,    14,    -1,    39,    -1,    -1,    19,    -1,    44,
      -1,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      59,    60,    61,    62,    63,    -1,    -1,    -1,    40,     1,
      -1,    -1,    71,    72,    73,    -1,    75,     9,    50,    51,
      52,    53,    54,    55,    56,    57,    18,    59,    60,    61,
      62,    63,    -1,    -1,    -1,     1,    -1,    -1,    -1,    71,
      72,    73,     8,    75,    -1,    -1,    12,    39,    14,    -1,
      -1,    43,    44,    19,    -1,    -1,    -1,    49,    -1,    -1,
       1,    -1,     1,    -1,    -1,    -1,    58,    -1,     9,     8,
      -1,    -1,    -1,    12,    40,    14,    -1,    18,    -1,    -1,
      19,    -1,    -1,    -1,    50,    51,    52,    53,    54,    55,
      56,    57,    -1,    59,    60,    61,    62,    63,    39,    -1,
      -1,    40,     1,    44,    -1,    71,    72,    73,    -1,    75,
       9,    50,    51,    52,    53,    54,    55,    56,    57,    18,
      59,    60,    61,    62,    63,    -1,    -1,    -1,     1,    -1,
      -1,    -1,    71,    72,    73,     8,    75,    -1,    -1,    12,
      39,    14,    -1,    -1,    43,    44,    19,     1,    -1,    -1,
      49,    -1,    -1,    -1,    -1,     9,    -1,    -1,     1,    58,
      -1,    -1,    -1,    -1,    18,     8,    -1,    40,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    19,    50,    51,    52,
      53,    54,    55,    56,    57,    39,    59,    60,    61,    62,
      63,    34,    35,    -1,    -1,    49,    -1,    40,    71,    72,
      73,    -1,    75,    -1,    58,    -1,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,     1,    59,    60,    61,    62,
      63,     7,     8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    75,    19,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     1,    -1,     1,     1,     1,    -1,     7,     8,    -1,
      -1,     9,     9,     9,    40,    -1,    -1,    -1,    -1,    19,
      18,    18,    18,    -1,    50,    51,    52,    53,    54,    55,
      56,    57,    -1,    59,    60,    61,    62,    63,    -1,    -1,
      40,    39,    39,    39,    -1,    -1,    44,    44,    44,    75,
      50,    51,    52,    53,    54,    55,    56,    57,     1,    59,
      60,    61,    62,    63,     7,     8,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    75,    19,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     1,    -1,     1,     1,     1,    -1,
      -1,     8,    -1,    -1,     9,     9,     9,    40,    -1,    -1,
      -1,    -1,    19,    18,    18,    18,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    61,    62,
      63,    -1,    -1,    40,    39,    39,    39,    -1,    -1,    44,
      44,    44,    75,    50,    51,    52,    53,    54,    55,    56,
      57,     1,    59,    60,    61,    62,    63,     1,     8,    -1,
      -1,    -1,    -1,    -1,    -1,     9,    -1,    -1,    75,    19,
      14,    15,    -1,    17,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    26,    27,    28,    29,    30,    31,    32,    -1,
      40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      50,    51,    52,    53,    54,    55,    56,    57,    -1,    59,
      60,    61,    62,    63,     1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     9,    67,    68,    75,    70,    14,    15,    16,
      17,    18,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,
      27,    28,    29,    30,    31,    32,    -1,     1,    -1,    -1,
       1,    -1,    39,    -1,    41,     9,    -1,    44,     9,    -1,
      14,    15,    16,    17,    18,    -1,    -1,    18,    -1,    -1,
      -1,    -1,    26,    27,    28,    29,    30,    31,    32,    -1,
      67,    68,    -1,    70,    -1,    39,     1,    41,    39,    -1,
      44,    -1,     1,    44,     9,    -1,    -1,    -1,    -1,    -1,
       9,    -1,    -1,    18,    -1,    14,    15,    16,    17,    18,
      -1,    -1,    -1,    67,    68,    -1,    70,    26,    27,    28,
      29,    30,    31,    32,    39,     1,    -1,    -1,    -1,    44,
      39,    -1,    41,     9,    49,    44,    -1,    -1,    14,    15,
      16,    17,    18,    58,    -1,    -1,    -1,    -1,    -1,    -1,
      26,    27,    28,    29,    30,    31,    32,    -1,    67,    68,
      -1,    70,    -1,    39,     1,    41,    -1,    -1,    44,    -1,
       1,    -1,     9,    -1,    -1,    -1,    -1,    -1,     9,    -1,
      -1,    18,    -1,    14,    15,    16,    17,    18,    -1,    -1,
      -1,    67,    68,    -1,    70,    26,    27,    28,    29,    30,
      31,    32,    39,     1,    -1,    -1,    -1,    44,    39,    -1,
      41,     9,    49,    44,    -1,    -1,    14,    15,    16,    17,
      18,    58,    -1,    -1,    -1,    -1,    -1,    -1,    26,    27,
      28,    29,    30,    31,    32,    -1,    67,    68,    -1,    70,
      -1,    39,     1,    41,    -1,    -1,    44,    -1,     1,    -1,
       9,    -1,    -1,    -1,    -1,    -1,     9,    -1,    -1,    18,
      -1,    14,    15,    16,    17,    18,    -1,    -1,    -1,    67,
      68,    -1,    70,    26,    27,    28,    29,    30,    31,    32,
      39,     1,    -1,    -1,     1,    44,    39,    -1,    41,     9,
      49,    44,     9,    -1,    14,    15,    16,    17,    18,    58,
      -1,    18,    -1,    -1,    -1,    -1,    26,    27,    28,    29,
      30,    31,    32,    -1,    67,    68,    -1,    70,    -1,    39,
      -1,    41,    39,    -1,    44,    -1,     1,    44,    -1,    -1,
      -1,    -1,    49,    -1,     9,    -1,    -1,    -1,    -1,    14,
      15,    58,    17,    18,    -1,    -1,    -1,    67,    68,    -1,
      70,    26,    27,    28,    29,    30,    31,    32,     1,    -1,
      -1,    -1,    -1,    -1,    39,    -1,     9,    -1,    43,    44,
      -1,    14,    15,    -1,    17,    18,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    26,    27,    28,    29,    30,    31,    32,
       1,    -1,    67,    68,    -1,    70,    39,    -1,     9,    -1,
      43,    44,    -1,    14,    15,    -1,    17,    18,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    26,    27,    28,    29,    30,
      31,    32,     1,    -1,    67,    68,    -1,    70,    39,    -1,
       9,    -1,    43,    44,    -1,    14,    15,    16,    17,    18,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,    27,    28,
      29,    30,    -1,    -1,    -1,     1,    67,    68,    -1,    70,
      39,    -1,    41,     9,    -1,    44,    -1,    -1,    14,    15,
      16,    17,    18,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      26,    27,    28,    29,    30,    -1,    -1,    -1,    67,    68,
      -1,    70,    -1,    39,     1,    41,    -1,    -1,    44,    -1,
       1,    -1,     9,    -1,    -1,    -1,    -1,    -1,     9,    -1,
      -1,    18,    -1,    14,    15,    16,    17,    18,    -1,    -1,
      -1,    67,    68,    -1,    70,    26,    27,    28,    29,    30,
      -1,    -1,    39,     1,    -1,    -1,    -1,    44,    39,    -1,
      41,     9,    49,    44,    -1,    -1,    14,    15,    -1,    17,
      18,    58,    -1,    -1,    -1,    -1,    -1,    -1,    26,    27,
      28,    29,    30,    31,    32,     1,    67,    68,    -1,    70,
      -1,    39,    -1,     9,    -1,    -1,    44,    -1,    14,    15,
      16,    17,    18,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      26,    27,    28,    29,    30,    -1,    -1,    -1,     1,    67,
      68,    -1,    70,    39,    -1,    41,     9,    -1,    44,    -1,
      -1,    14,    15,    -1,    17,    18,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    26,    27,    28,    29,    30,    31,    32,
       1,    67,    68,    -1,    70,    -1,    39,    -1,     9,    -1,
      -1,    44,    -1,    14,    15,    -1,    17,    18,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    26,    27,    28,    29,    30,
      31,    32,     1,    -1,    67,    68,    -1,    70,    39,    -1,
       9,    -1,    -1,    44,    -1,    14,    15,    -1,    17,    18,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,    27,    28,
      29,    30,    31,    32,     1,    -1,    67,    68,    -1,    70,
      39,    -1,     9,    -1,    -1,    44,    -1,    14,    15,    16,
      17,    18,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,
      27,    28,    -1,    -1,    -1,    -1,    -1,     1,    67,    68,
      -1,    70,    39,    -1,    41,     9,    -1,    44,    -1,    -1,
      14,    15,    16,    17,    18,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,
      67,    68,    -1,    70,     1,    39,    -1,    41,    -1,    -1,
      44,    -1,     9,    -1,    -1,    -1,    -1,    14,    15,    16,
      17,    18,    -1,    -1,     1,    -1,    -1,    -1,    -1,    26,
      27,    28,     9,    67,    68,    -1,    70,    14,    15,    16,
      17,    18,    39,    -1,    41,    -1,    -1,    44,    -1,    26,
      27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     1,    39,    -1,    41,    -1,    -1,    44,    -1,     9,
      67,    68,    -1,    70,    14,    15,    16,    17,    18,    -1,
      -1,     1,    -1,    -1,    -1,    -1,    26,    27,    28,     9,
      67,    68,    -1,    70,    14,    15,    -1,    17,    18,    39,
      -1,    41,    -1,    -1,    44,    -1,    26,    27,    28,    29,
      30,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    44,    -1,     1,    67,    68,    -1,
      70,    -1,    -1,    -1,     9,    -1,    -1,    -1,    -1,    14,
      15,    -1,    17,    18,    -1,    -1,    -1,    67,    68,    -1,
      70,    26,    27,    28,    29,    30,    -1,    -1,     1,    -1,
      -1,    -1,    -1,    -1,    39,    -1,     9,    -1,    -1,    44,
      -1,    14,    15,    16,    17,    18,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,
      -1,     1,    67,    68,    -1,    70,    39,    -1,    41,     9,
      -1,    44,    -1,    -1,    14,    15,    16,    17,    18,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    26,    27,    28,    -1,
      -1,    -1,    -1,    -1,    67,    68,    -1,    70,     1,    39,
      -1,    41,    -1,    -1,    44,    -1,     9,    -1,    -1,    -1,
      -1,    14,    15,    16,    17,    18,    -1,    -1,     1,    -1,
      -1,    -1,    -1,    26,    27,    28,     9,    67,    68,    -1,
      70,    14,    15,    -1,    17,    18,    39,    -1,    41,    -1,
      -1,    44,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     1,    39,    -1,    -1,    -1,
      -1,    44,    -1,     9,    67,    68,    -1,    70,    14,    15,
      -1,    17,    18,    -1,    -1,     1,    -1,    -1,    -1,    -1,
      26,    27,    28,     9,    67,    68,    -1,    70,    14,    15,
      -1,    17,    18,    39,    -1,    -1,    -1,    -1,    44,    -1,
      26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     1,    39,    -1,    -1,    -1,    -1,    44,    -1,
       9,    67,    68,    -1,    70,    14,    15,    -1,    17,    18,
      -1,    -1,     1,    -1,    -1,    -1,    -1,    26,    27,    28,
       9,    67,    68,    -1,    70,    14,    15,    -1,    17,    -1,
      39,    -1,    -1,    -1,    -1,    44,    -1,    26,    27,    28,
      29,    30,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    67,    68,
      -1,    70,    -1,    -1,    -1,     9,    -1,    -1,    -1,    -1,
      14,    15,    -1,    17,    -1,    -1,    -1,    -1,    67,    68,
       1,    70,    26,    27,    28,    29,    30,     1,     9,    -1,
      -1,    -1,    -1,    14,    15,     9,    17,    -1,    -1,    -1,
      -1,    15,    -1,    -1,    18,    26,    27,    28,    29,    30,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,
      -1,    -1,    -1,    67,    68,    39,    70,     9,    42,    43,
      44,     1,    -1,    15,     1,    49,    18,     1,    -1,     9,
      -1,    -1,     9,    -1,    58,     9,    67,    68,    18,    70,
      -1,    18,    -1,    -1,    18,    -1,    -1,    39,    -1,    -1,
      -1,    43,    44,    -1,    -1,    -1,    -1,    49,    -1,    39,
       1,    -1,    39,     1,    44,    39,    58,    44,     9,    49,
      44,     9,    49,    -1,    -1,    49,    -1,    18,    58,    -1,
      18,    58,    -1,     1,    58,     1,    -1,     1,    -1,    -1,
      -1,     9,    -1,     9,    -1,     9,    -1,    -1,    39,    -1,
      18,    39,    18,    44,    18,     1,    44,     1,    49,    -1,
      -1,    49,    -1,     9,    -1,     9,    -1,    58,    -1,    -1,
      58,    39,    18,    39,    18,    39,    44,    -1,    44,     1,
      44,    49,    -1,    49,    -1,    49,    -1,     9,    -1,    -1,
      58,     1,    58,    39,    58,    39,    18,    -1,    44,     9,
      44,    -1,     1,    49,    -1,    49,    -1,    -1,    18,    -1,
       9,    -1,    58,     1,    58,     1,    -1,    39,    -1,    18,
      -1,     9,    44,     9,    -1,    -1,    -1,    49,    -1,    39,
      18,    -1,    18,    -1,    44,     1,    58,    -1,     1,    49,
      39,    -1,    -1,     9,    -1,    44,     9,    -1,    58,    -1,
      49,    39,    18,    39,    -1,    18,    44,    -1,    44,    58,
       1,    49,    -1,    49,    -1,    -1,    -1,     1,     9,    -1,
      58,     1,    58,    39,    -1,     9,    39,    18,    44,     9,
      -1,    44,     1,    49,    18,    -1,    49,    -1,    18,     1,
       9,    -1,    58,    -1,    -1,    58,    -1,     9,    39,    18,
      -1,    -1,    -1,    44,     1,    39,    18,    -1,    49,    39,
      44,    -1,     9,    -1,    44,    49,    -1,    58,    -1,    49,
      39,    18,    -1,    -1,    58,    44,     1,    39,    58,    -1,
      49,    -1,    44,     1,     9,    -1,    -1,    49,    -1,    58,
      -1,     9,    39,    18,    -1,    -1,    58,    44,     1,     1,
      18,     1,    49,    -1,    -1,     1,     9,     9,    -1,     9,
      -1,    58,    -1,     9,    39,    18,    18,    -1,    18,    44,
      -1,    39,    18,    -1,    49,    -1,    44,    -1,    -1,    -1,
      -1,    49,    -1,    58,    -1,    -1,    39,    39,    -1,    39,
      58,    44,    44,    39,    44,    -1,    49,    49,    44,    49,
      -1,     1,    -1,    49,    -1,    58,    58,    -1,    58,     9,
      -1,    -1,    58,    -1,    -1,    -1,    -1,    -1,    18,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,
      -1,    -1,    42,    43,    -1,    -1,    -1,    -1,    -1,    49
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  mcmas_parser::yystos_[] =
  {
         0,     1,     3,    66,    79,    80,    81,    82,    84,   109,
     110,   112,    19,     1,    19,    17,     0,     1,    81,     1,
       4,    20,    21,    34,    85,    87,    92,    94,    96,    98,
     117,   119,     1,     3,   109,     1,    45,   112,   168,   170,
      75,    64,    65,    10,    17,    41,     1,    17,     1,    41,
       1,    41,     1,    41,     1,     7,    86,    88,     1,    94,
      98,   119,     1,    88,     1,    98,   119,     1,     7,     8,
      23,    24,    29,    40,    69,    75,    76,    91,    97,   100,
     137,   139,   140,   141,   142,   143,   144,   145,   163,   164,
       1,   119,     1,    11,    75,   118,   121,     1,     5,   122,
     124,   170,     1,   171,     1,    46,   173,   175,     1,    38,
      92,    95,   113,   115,    44,    44,     1,    10,    10,     1,
      10,    20,     1,    20,     1,    75,    86,    89,    41,    98,
     119,   119,   124,     1,     7,    93,    41,   119,   124,     1,
      34,    76,   137,   139,   142,   145,     1,    34,   137,   139,
     142,    76,   137,     1,     8,   145,     1,    97,     1,    18,
      39,    44,     1,    29,    30,     1,    31,    32,     1,    14,
      15,    17,    26,    27,    28,    68,    70,   161,     1,    67,
     124,    44,     1,    44,     1,    42,   118,    41,     1,    41,
       1,     7,    37,   123,   126,   130,   132,   137,     1,     6,
     102,   104,   175,     1,     7,    75,   169,     1,     8,    19,
      40,    75,   176,     1,    36,    47,    48,   177,   179,   185,
     187,   193,   195,    10,    17,    41,     1,    17,    88,     1,
      96,    99,   117,   120,     1,    11,    75,   114,   116,     1,
      95,     1,    41,     1,    44,   119,   124,   124,   104,    21,
       1,    21,   124,   104,     1,     9,     9,     9,     1,     9,
       1,     9,     1,     9,     1,     1,   142,   142,   137,   137,
     137,     1,     8,   140,   140,   140,   141,   141,   141,   143,
     143,   143,   142,   144,   144,   104,    75,    75,     1,     5,
      41,   128,     1,     5,     1,   128,     1,   123,   130,   132,
       1,   123,     1,   128,    41,     1,    41,     1,   105,     1,
       7,    83,   179,   187,   195,    45,     1,    45,     1,    16,
      43,    75,   176,   176,     1,    43,   176,     1,    43,     1,
      18,    39,    44,   174,     1,     7,    75,   178,   182,     1,
     187,   195,     1,     7,     8,    19,    40,    50,    51,    52,
      53,    54,    55,    56,    57,    59,    60,    61,    62,    63,
      75,   186,   188,   192,     1,   195,     1,    74,   196,   202,
       1,    10,    10,     1,    10,    93,     1,     8,    19,    40,
      69,    75,    91,    97,   101,   138,   146,   147,   148,   149,
     154,   155,   156,   164,   165,     1,   120,     1,   121,     1,
     122,   125,    44,     1,    44,     1,    42,   114,    99,   120,
       1,    22,    75,    90,    91,     1,    10,    22,    91,   124,
     104,   104,    83,   104,    83,   139,   139,    83,    10,     1,
      10,     1,    75,   133,   133,   123,   133,     1,     7,     8,
      75,   103,   106,   107,     3,     1,     3,   187,   195,   195,
       1,     8,    19,    40,    69,    75,    91,   150,   151,   152,
     153,   157,   158,   159,   164,   166,   172,   172,    75,     1,
      17,     1,     9,     1,     9,    75,    75,     1,    75,    75,
       7,    46,   176,   176,   176,     1,     7,    47,     1,    47,
       1,    17,   180,     1,    75,   178,   195,     1,     8,    36,
     190,   191,   192,     1,    36,     1,   192,    43,   192,   192,
     192,   192,   192,   192,   192,     1,     8,   189,   189,     1,
       8,   190,     1,     8,   191,   191,   190,   191,     1,    43,
       1,   186,   192,     1,    18,    39,    44,    49,     1,     7,
     194,   202,     1,     8,    12,    14,    19,    40,    50,    51,
      52,    53,    54,    55,    56,    57,    59,    60,    61,    62,
      63,    71,    72,    73,    75,   197,   201,     1,    43,   138,
     146,   149,   154,   138,   146,   154,     1,    43,   138,     1,
       8,   149,    97,     1,    18,    39,    44,     1,    68,    70,
     161,     1,    67,     1,    29,    30,     1,    31,    32,   125,
     118,     1,   127,   131,   132,   138,     1,   102,   134,    75,
      75,   120,   125,    76,     1,    11,    42,     1,    25,     1,
      90,     1,    25,   104,    83,    83,    83,     1,    11,    42,
     129,   129,   129,     6,     1,     6,     1,   107,    17,    16,
      18,   195,    43,   150,   153,   157,   172,   150,   157,   172,
       1,    43,   172,     1,     8,   153,     1,    43,     1,    68,
      70,   161,     1,    67,     1,    29,    30,     1,    31,    32,
       1,    18,    39,    44,     1,    44,     1,     1,    75,    91,
     164,   167,    75,   167,     1,    17,     1,    17,     1,    17,
       1,    17,     1,    46,    46,     1,    46,    10,     1,    10,
       1,    11,    19,    75,   181,   183,   184,   180,    19,    75,
      19,    75,     1,     9,     1,     9,    34,    35,     1,   192,
     192,    19,    75,    19,    75,    75,    75,    34,    35,     1,
      34,    35,     1,    44,   192,   192,   192,   192,    48,     1,
      48,   201,     1,     8,    75,   199,   200,   201,    19,    75,
     201,    12,    14,    75,    43,   201,   201,   201,   201,   201,
     201,   201,     1,     8,   198,   198,     1,     8,   199,     1,
       8,   200,   200,   199,   200,   201,   201,   201,     1,    43,
       1,    71,    72,    73,   198,     1,    18,    39,    44,    49,
      58,    75,     1,     9,     9,     9,     1,     9,     1,     9,
       1,     9,    75,    75,     1,     1,   146,   146,   138,   138,
     138,   147,   147,   147,   146,   148,   148,     1,     8,   155,
     155,   155,   156,   156,   156,   134,     1,     1,   123,   131,
     132,   123,     1,   128,   135,   135,     1,     7,   111,   125,
     134,    75,    75,    91,    91,     1,    11,    91,    91,    83,
      44,    75,     1,    44,    75,     9,   142,     1,     8,    33,
      40,    75,   142,   160,   107,    75,     9,     9,     1,     9,
       1,     9,     1,     9,     1,     9,    75,    75,     1,     1,
     150,   150,    75,    75,   151,   151,   151,   150,   152,   152,
       1,     8,   158,   158,   158,   159,   159,   159,   172,   172,
     172,   167,   167,   167,   167,    19,    75,   167,   167,   167,
     167,    19,    75,   167,    44,     1,    44,     1,    42,   181,
     181,   183,     1,    42,     1,    42,     1,    42,     1,    42,
       1,    58,     1,    58,     1,    42,     1,    42,     1,    42,
       1,    42,     1,    44,    19,    75,    19,    75,    15,     1,
       9,    42,    42,     1,     9,    75,    75,     1,    15,    34,
      35,     1,   201,   201,    19,    75,    19,    75,    75,    75,
      34,    35,     1,    34,    35,   201,   201,   201,   201,   201,
     201,   201,   201,   201,   154,   154,   111,   123,   133,     1,
       8,    75,   103,   108,   136,   103,     3,     1,     3,   134,
     111,    17,    75,   142,   160,   142,   160,     1,    17,   160,
       1,    43,   161,     1,    18,    39,    44,   157,   157,    43,
      43,    43,    43,     1,   184,   184,   181,   192,   192,   192,
     192,   192,   192,   192,   192,   192,   192,   192,   192,   192,
     192,   192,   192,   192,   192,   192,   192,     1,    42,     1,
      42,     1,    42,     1,    42,    75,    75,    13,    15,     1,
      58,     1,    58,     1,    42,    42,     1,    42,     1,    42,
       1,    42,   129,     1,   108,    17,     1,    16,    18,   111,
      75,     1,     9,     1,     9,    75,    75,    17,    33,    75,
       1,    33,   142,   160,   160,   160,    75,    75,    75,    75,
       1,     9,     1,     9,     1,     9,     1,     9,     1,     9,
       1,     9,     1,     9,     1,     9,     1,     9,     1,     9,
       1,     9,     1,     9,     1,     9,     1,     9,     1,     9,
       1,     9,     1,     9,     1,     9,     1,     9,     1,     9,
     201,   201,   201,   201,   201,    75,   201,   201,    75,   201,
       9,     9,    13,    15,   201,   201,   201,   201,   201,   201,
     201,   201,   201,   201,   201,   201,     9,   146,     1,     8,
      19,    33,    40,    75,   146,   162,   162,   108,    75,     1,
      17,    17,    75,     1,    17,     1,     9,     1,     9,     1,
       9,     1,     9,     1,     9,     1,     9,     1,     9,     1,
       9,   201,   201,   201,   201,     1,     9,     1,     1,     9,
       1,     9,     1,     9,     1,     9,     1,     9,     1,     9,
       1,     9,     1,     9,     1,     9,     1,     9,    17,    75,
     146,   162,   146,   162,     1,    43,     1,    17,   162,     1,
      43,   161,     1,    18,    39,    44,     1,    44,    75,    75,
      75,    75,    75,    75,     1,     9,     1,     9,    17,    33,
      75,     1,    33,    75,    75,     1,    17,    33,    75,     1,
      33,   146,   162,   162,   162,    75,     1,    17,    75,     1,
      17,    75,     1,    17,    17,    75,     1,    17,    75,    75,
      75,    75,    75,    75,    75,    75,    75
  };

#if YYDEBUG
  /* TOKEN_NUMBER_[YYLEX-NUM] -- Internal symbol number corresponding
     to YYLEX-NUM.  */
  const unsigned short int
  mcmas_parser::yytoken_number_[] =
  {
         0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  mcmas_parser::yyr1_[] =
  {
         0,    78,    79,    79,    80,    80,    80,    81,    81,    81,
      81,    81,    81,    81,    81,    82,    82,    82,    82,    83,
      83,    83,    83,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    85,    85,    85,    85,    86,    86,    86,    86,
      87,    87,    88,    88,    88,    88,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    90,    90,
      90,    90,    91,    91,    91,    91,    92,    92,    92,    92,
      93,    93,    93,    93,    94,    94,    95,    95,    96,    96,
      96,    96,    97,    97,    97,    97,    98,    98,    98,    99,
      99,    99,   100,   100,   100,   101,   101,   101,   102,   102,
     102,   102,   103,   103,   103,   103,   104,   105,   105,   105,
     106,   106,   107,   107,   107,   107,   108,   108,   108,   108,
     109,   109,   109,   110,   110,   111,   111,   111,   111,   112,
     112,   112,   112,   112,   113,   113,   113,   113,   113,   113,
     113,   113,   114,   114,   114,   114,   115,   115,   115,   116,
     116,   116,   116,   117,   117,   117,   117,   117,   117,   117,
     117,   118,   118,   118,   118,   119,   119,   119,   120,   120,
     121,   121,   121,   121,   122,   122,   122,   122,   123,   123,
     123,   123,   124,   124,   124,   124,   124,   125,   125,   125,
     125,   126,   126,   126,   127,   127,   127,   128,   128,   128,
     128,   129,   129,   129,   129,   130,   130,   131,   131,   132,
     132,   133,   133,   133,   133,   134,   134,   135,   135,   136,
     136,   136,   136,   136,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   139,   139,   139,   139,
     140,   140,   140,   140,   141,   141,   141,   141,   142,   142,
     142,   142,   143,   143,   143,   144,   144,   144,   145,   145,
     145,   145,   146,   146,   146,   146,   147,   147,   147,   148,
     148,   148,   149,   149,   149,   149,   150,   150,   150,   150,
     151,   151,   151,   152,   152,   152,   153,   153,   153,   153,
     154,   154,   154,   154,   155,   155,   155,   155,   156,   156,
     156,   156,   157,   157,   157,   157,   158,   158,   158,   158,
     159,   159,   159,   159,   160,   160,   160,   160,   160,   160,
     160,   160,   160,   160,   160,   160,   160,   160,   160,   160,
     160,   160,   160,   160,   160,   160,   160,   161,   161,   161,
     161,   161,   161,   162,   162,   162,   162,   162,   162,   162,
     162,   162,   162,   162,   162,   162,   162,   162,   162,   162,
     162,   162,   162,   162,   162,   162,   162,   162,   162,   162,
     162,   162,   162,   163,   163,   163,   164,   164,   165,   165,
     165,   165,   165,   165,   166,   166,   166,   166,   166,   166,
     166,   166,   167,   167,   167,   168,   169,   169,   169,   169,
     170,   170,   171,   171,   171,   171,   171,   171,   172,   172,
     172,   172,   172,   172,   172,   172,   172,   172,   172,   173,
     173,   174,   174,   174,   174,   174,   174,   174,   174,   175,
     175,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   176,   177,   177,   178,   178,
     178,   178,   179,   179,   179,   180,   180,   180,   180,   181,
     181,   181,   181,   182,   182,   182,   182,   182,   183,   183,
     183,   183,   184,   184,   184,   185,   185,   186,   186,   186,
     186,   187,   187,   188,   188,   188,   188,   188,   189,   189,
     189,   189,   189,   189,   189,   189,   190,   190,   190,   190,
     190,   190,   190,   190,   190,   190,   190,   190,   190,   190,
     190,   190,   191,   191,   191,   191,   191,   191,   191,   191,
     192,   192,   192,   192,   192,   192,   192,   192,   192,   192,
     192,   192,   192,   192,   192,   192,   192,   192,   192,   192,
     192,   192,   192,   192,   192,   192,   192,   192,   192,   192,
     192,   192,   192,   192,   193,   193,   194,   194,   194,   194,
     195,   196,   196,   196,   196,   196,   197,   197,   197,   198,
     198,   198,   198,   198,   198,   198,   199,   199,   199,   199,
     199,   199,   199,   199,   199,   199,   199,   199,   199,   199,
     199,   199,   200,   200,   200,   200,   200,   200,   200,   200,
     201,   201,   201,   201,   201,   201,   201,   201,   201,   201,
     201,   201,   201,   201,   201,   201,   201,   201,   201,   201,
     201,   201,   201,   201,   201,   201,   201,   201,   201,   201,
     201,   201,   201,   201,   201,   201,   201,   201,   201,   201,
     201,   201,   201,   201,   201,   201,   201,   202,   202
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  mcmas_parser::yyr2_[] =
  {
         0,     2,     1,     2,     4,     4,     1,     7,     6,     6,
       5,     6,     5,     5,     4,     2,     2,     2,     1,     2,
       2,     2,     1,     8,     7,     7,     6,     7,     6,     6,
       5,     1,     2,     2,     2,     1,     2,     2,     2,     1,
       3,     2,     0,     3,     3,     1,     3,     3,     3,     5,
       5,     5,     5,     5,     4,     5,     4,     1,     1,     3,
       3,     1,     1,     2,     2,     1,     2,     2,     2,     1,
       2,     2,     2,     1,     3,     1,     3,     1,     2,     2,
       2,     1,     2,     2,     2,     1,     3,     2,     1,     3,
       2,     1,     2,     2,     1,     2,     2,     1,     2,     2,
       2,     1,     2,     2,     2,     1,     3,     0,     2,     1,
       4,     1,     3,     3,     3,     1,     3,     3,     3,     1,
       1,     2,     1,     1,     1,     2,     2,     2,     1,     8,
       7,     9,     8,     1,     3,     3,     3,     3,     2,     2,
       3,     1,     2,     2,     2,     1,     3,     2,     1,     1,
       3,     3,     1,     3,     3,     3,     3,     2,     2,     3,
       1,     2,     2,     2,     1,     3,     2,     1,     3,     1,
       1,     3,     3,     1,     2,     2,     2,     1,     2,     2,
       2,     1,     3,     4,     3,     2,     1,     3,     4,     3,
       1,     1,     2,     1,     1,     2,     1,     2,     2,     2,
       1,     2,     2,     2,     1,     4,     1,     4,     1,     4,
       4,     1,     3,     3,     1,     3,     3,     0,     2,     4,
       4,     4,     4,     1,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     3,     1,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     3,     1,     3,     3,     3,     1,
       3,     3,     3,     1,     3,     3,     3,     1,     3,     3,
       3,     1,     3,     3,     1,     2,     2,     1,     3,     3,
       3,     1,     3,     3,     3,     1,     3,     3,     1,     2,
       2,     1,     3,     3,     3,     1,     3,     3,     3,     1,
       3,     3,     1,     2,     2,     1,     3,     3,     3,     1,
       3,     3,     3,     1,     3,     3,     3,     1,     3,     3,
       3,     1,     3,     3,     3,     1,     3,     3,     3,     1,
       3,     3,     3,     1,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     3,     3,     3,     3,     2,     5,     5,
       5,     5,     4,     4,     5,     3,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     3,     3,     3,     3,     2,     5,     5,     5,
       5,     4,     4,     5,     3,     5,     5,     5,     4,     4,
       5,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     1,     1,     1,     3,     3,     3,     3,
       3,     1,     1,     1,     1,     1,     2,     2,     2,     1,
       3,     1,     0,     5,     5,     5,     5,     1,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     3,     1,     1,
       1,     3,     3,     3,     3,     2,     2,     3,     1,     3,
       1,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       7,     7,     7,     5,     5,     5,     5,     7,     5,     5,
       5,     5,     4,     5,     4,     1,     1,     1,     2,     2,
       2,     1,     3,     2,     1,     2,     2,     2,     1,     2,
       2,     2,     1,     4,     5,     3,     4,     1,     1,     3,
       3,     1,     1,     1,     1,     1,     1,     2,     2,     2,
       1,     2,     3,     2,     2,     3,     3,     1,     5,     5,
       5,     5,     5,     5,     5,     5,     5,     5,     5,     5,
       5,     5,     5,     5,     5,     5,     5,     5,     5,     5,
       5,     5,     5,     5,     5,     5,     5,     5,     5,     5,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     3,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     1,     3,     3,     3,     3,
       3,     3,     3,     1,     1,     1,     2,     2,     2,     1,
       3,     3,     3,     4,     4,     1,     3,     3,     3,     5,
       5,     5,     5,     5,     5,     5,     5,     5,     5,     5,
       5,     5,     5,     5,     5,     5,     5,     5,     5,     5,
       5,     5,     5,     5,     5,     5,     5,     5,     5,     5,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     3,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     3,     3,     3,     3,     2,
       6,     6,     6,     6,     2,     2,     2,     3,     1,     3,
       3,     3,     3,     3,     3,     3,     1,     0,     1
  };

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const mcmas_parser::yytname_[] =
  {
    "\"end of file\"", "error", "$undefined", "AGENT", "ACTIONS",
  "PROTOCOL", "EVOLUTION", "END", "LB", "RB", "LCB", "RCB", "LSB", "RSB",
  "LT", "GT", "IF", "EQ", "AND", "ENVIRONMENT", "OBSVARS", "VARS",
  "BOOLEAN", "BTRUE", "BFALSE", "TO", "LE", "GE", "NEQ", "MINUS", "PLUS",
  "TIMES", "DIVIDE", "ACTION", "REDSTATES", "GREENSTATES", "FAIRNESS",
  "OTHER", "LOBSVARS", "OR", "NOT", "COLON", "COMMA", "DOT", "SEMICOLON",
  "EVALUATION", "INITSTATES", "GROUPS", "FORMULAE", "IMPLIES", "AG", "EG",
  "AX", "EX", "AF", "EF", "A", "E", "UNTIL", "K", "GK", "GCK", "O", "DK",
  "MULTIASSIGNMENT", "SINGLEASSIGNMENT", "SEMANTICS", "BITAND", "BITOR",
  "BITNOT", "BITXOR", "X", "F", "G", "PERFECTRECALL", "\"identifier\"",
  "\"number\"", "QUANTIFIER", "$accept", "eis", "semantics", "is",
  "envprefix", "envsuffix", "environment", "obsprefix", "obssuffix",
  "obsvardef", "varidlist", "onevardef", "enumlist", "integer",
  "varprefix", "varsuffix", "envardef", "vardef", "redprefix", "redsuffix",
  "enreddef", "reddef", "enrboolcond", "rboolcond", "evprefix", "evsuffix",
  "envevdef", "envevdeflist", "envevline", "boolresult", "boolresult1",
  "agents", "agprefix", "agsuffix", "agent", "lobsprefix", "lobssuffix",
  "lobsvarsdef", "lobsvaridlist", "actprefix", "actsuffix", "enactiondef",
  "actiondef", "actionidlist", "protprefix", "protsuffix", "enprotdef",
  "protdef", "enprotdeflist", "protdeflist", "plprefix", "plsuffix",
  "enprotline", "protline", "otherbranch", "enabledidlist", "evdef",
  "evdeflist", "evline", "enlboolcond", "lboolcond", "expr1", "term1",
  "element1", "expr4", "term4", "factor4", "element4", "expr5", "term5",
  "factor5", "element5", "expr6", "term6", "factor6", "element6", "expr2",
  "term2", "element2", "expr3", "term3", "element3", "eboolcond",
  "logicop", "gboolcond", "varvalue1", "boolvalue", "varvalue2",
  "varvalue3", "varvalue4", "evaprefix", "evasuffix", "evaluation",
  "evalist", "evaboolcond", "iniprefix", "inisuffix", "istates",
  "isboolcond", "groupprefix", "groupsuffix", "groups", "gplprefix",
  "gplsufffix", "groupdeflist", "namelist", "agentname", "fairprefix",
  "fairsuffix", "fairness", "fformlist", "untilprefixfair",
  "epistemicprefixfair", "gepistemicprefixfair", "fformula", "forprefix",
  "forsuffix", "formulae", "formlist", "atlprefix", "untilprefix",
  "epistemicprefix", "gepistemicprefix", "formula", "perfectrecalltag", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const mcmas_parser::rhs_number_type
  mcmas_parser::yyrhs_[] =
  {
        79,     0,    -1,    81,    -1,    80,    81,    -1,    66,    17,
      64,    44,    -1,    66,    17,    65,    44,    -1,     1,    -1,
      84,   109,   170,   175,   179,   187,   195,    -1,    84,   109,
     170,   175,   179,   195,    -1,    84,   109,   170,   175,   187,
     195,    -1,    84,   109,   170,   175,   195,    -1,   109,   170,
     175,   179,   187,   195,    -1,   109,   170,   175,   179,   195,
      -1,   109,   170,   175,   187,   195,    -1,   109,   170,   175,
     195,    -1,     3,    19,    -1,     1,    19,    -1,     3,     1,
      -1,     1,    -1,     7,     3,    -1,     1,     3,    -1,     7,
       1,    -1,     1,    -1,    82,    87,    94,    98,   119,   124,
     104,    83,    -1,    82,    87,    94,   119,   124,   104,    83,
      -1,    82,    94,    98,   119,   124,   104,    83,    -1,    82,
      94,   119,   124,   104,    83,    -1,    82,    87,    98,   119,
     124,   104,    83,    -1,    82,    87,   119,   124,   104,    83,
      -1,    82,    98,   119,   124,   104,    83,    -1,    82,   119,
     124,   104,    83,    -1,     1,    -1,    20,    41,    -1,     1,
      41,    -1,    20,     1,    -1,     1,    -1,     7,    20,    -1,
       1,    20,    -1,     7,     1,    -1,     1,    -1,    85,    88,
      86,    -1,    85,    86,    -1,    -1,    88,    89,    44,    -1,
      88,    89,     1,    -1,     1,    -1,    75,    41,    22,    -1,
      75,    41,     1,    -1,    75,     1,    22,    -1,    75,    41,
      91,    25,    91,    -1,    75,     1,    91,    25,    91,    -1,
      75,    41,    91,     1,    91,    -1,    75,     1,    91,     1,
      91,    -1,    75,    41,    10,    90,    11,    -1,    75,     1,
      90,    11,    -1,    75,    41,    10,    90,     1,    -1,    75,
       1,    90,     1,    -1,     1,    -1,    75,    -1,    90,    42,
      75,    -1,    90,     1,    75,    -1,     1,    -1,    76,    -1,
      29,    76,    -1,     1,    76,    -1,     1,    -1,    21,    41,
      -1,     1,    41,    -1,    21,     1,    -1,     1,    -1,     7,
      21,    -1,     1,    21,    -1,     7,     1,    -1,     1,    -1,
      92,    88,    93,    -1,     1,    -1,    92,    88,    93,    -1,
       1,    -1,    34,    41,    -1,    34,     1,    -1,     1,    41,
      -1,     1,    -1,     7,    34,    -1,     1,    34,    -1,     7,
       1,    -1,     1,    -1,    96,   100,    97,    -1,    96,    97,
      -1,     1,    -1,    96,   101,    97,    -1,    96,    97,    -1,
       1,    -1,   137,    44,    -1,   137,     1,    -1,     1,    -1,
     138,    44,    -1,   138,     1,    -1,     1,    -1,     6,    41,
      -1,     1,    41,    -1,     6,     1,    -1,     1,    -1,     7,
       6,    -1,     1,     6,    -1,     7,     1,    -1,     1,    -1,
     102,   105,   103,    -1,    -1,   105,   106,    -1,     1,    -1,
     107,    16,   160,    44,    -1,     1,    -1,     8,   107,     9,
      -1,   107,    18,   107,    -1,    75,    17,   142,    -1,     1,
      -1,     8,   108,     9,    -1,   108,    18,   108,    -1,    75,
      17,   146,    -1,     1,    -1,   112,    -1,   109,   112,    -1,
       1,    -1,     3,    -1,     1,    -1,     7,     3,    -1,     1,
       3,    -1,     7,     1,    -1,     1,    -1,   110,    75,    95,
      99,   120,   125,   134,   111,    -1,   110,    75,    95,   120,
     125,   134,   111,    -1,   110,    75,   115,    95,    99,   120,
     125,   134,   111,    -1,   110,    75,   115,    95,   120,   125,
     134,   111,    -1,     1,    -1,    38,    17,    10,    -1,     1,
      17,    10,    -1,    38,     1,    10,    -1,    38,    17,     1,
      -1,     1,    10,    -1,    38,     1,    -1,     1,    17,     1,
      -1,     1,    -1,    11,    44,    -1,    11,     1,    -1,     1,
      44,    -1,     1,    -1,   113,   116,   114,    -1,   113,   114,
      -1,     1,    -1,    75,    -1,   116,    42,    75,    -1,   116,
       1,    75,    -1,     1,    -1,     4,    17,    10,    -1,     1,
      17,    10,    -1,     4,     1,    10,    -1,     4,    17,     1,
      -1,     1,    10,    -1,     4,     1,    -1,     1,    17,     1,
      -1,     1,    -1,    11,    44,    -1,    11,     1,    -1,     1,
      44,    -1,     1,    -1,   117,   121,   118,    -1,   117,   118,
      -1,     1,    -1,   117,   121,   118,    -1,     1,    -1,    75,
      -1,   121,    42,    75,    -1,   121,     1,    75,    -1,     1,
      -1,     5,    41,    -1,     1,    41,    -1,     5,     1,    -1,
       1,    -1,     7,     5,    -1,     1,     5,    -1,     7,     1,
      -1,     1,    -1,   122,   126,   123,    -1,   122,   126,   132,
     123,    -1,   122,   132,   123,    -1,   122,   123,    -1,     1,
      -1,   122,   127,   123,    -1,   122,   127,   132,   123,    -1,
     122,   132,   123,    -1,     1,    -1,   130,    -1,   126,   130,
      -1,     1,    -1,   131,    -1,   127,   131,    -1,     1,    -1,
      41,    10,    -1,     1,    10,    -1,    41,     1,    -1,     1,
      -1,    11,    44,    -1,     1,    44,    -1,    11,     1,    -1,
       1,    -1,   137,   128,   133,   129,    -1,     1,    -1,   138,
     128,   133,   129,    -1,     1,    -1,    37,   128,   133,   129,
      -1,     1,   128,   133,   129,    -1,    75,    -1,   133,    42,
      75,    -1,   133,     1,    75,    -1,     1,    -1,   102,   135,
     103,    -1,     1,   135,   103,    -1,    -1,   135,   136,    -1,
     108,    16,   162,    44,    -1,   108,     1,   162,    44,    -1,
     108,    16,   162,     1,    -1,   108,     1,   162,     1,    -1,
       1,    -1,     8,   137,     9,    -1,     1,   137,     9,    -1,
       8,   137,     1,    -1,     1,   137,     1,    -1,   137,    18,
     137,    -1,   137,    39,   137,    -1,   137,     1,   137,    -1,
      40,   137,    -1,     1,   137,    -1,   142,   161,   142,    -1,
       1,    -1,     8,   138,     9,    -1,     1,   138,     9,    -1,
       8,   138,     1,    -1,     1,   138,     1,    -1,   138,    18,
     138,    -1,   138,    39,   138,    -1,   138,     1,   138,    -1,
      40,   138,    -1,     1,   138,    -1,   146,   161,   146,    -1,
       1,    -1,   139,    30,   140,    -1,   139,    29,   140,    -1,
     139,     1,   140,    -1,   140,    -1,   140,    31,   141,    -1,
     140,    32,   141,    -1,   140,     1,   141,    -1,   141,    -1,
       8,   139,     9,    -1,     1,   139,     9,    -1,     8,   139,
       1,    -1,   163,    -1,   142,    68,   143,    -1,   142,    70,
     143,    -1,   142,     1,   143,    -1,   143,    -1,   143,    67,
     144,    -1,   143,     1,   144,    -1,   144,    -1,    69,   145,
      -1,     1,   145,    -1,   145,    -1,     8,   142,     9,    -1,
       1,   142,     9,    -1,     8,   142,     1,    -1,   139,    -1,
     146,    68,   147,    -1,   146,    70,   147,    -1,   146,     1,
     147,    -1,   147,    -1,   147,    67,   148,    -1,   147,     1,
     148,    -1,   148,    -1,    69,   149,    -1,     1,   149,    -1,
     149,    -1,     8,   146,     9,    -1,     1,   146,     9,    -1,
       8,   146,     1,    -1,   154,    -1,   150,    68,   151,    -1,
     150,    70,   151,    -1,   150,     1,   151,    -1,   151,    -1,
     151,    67,   152,    -1,   151,     1,   152,    -1,   152,    -1,
      69,   153,    -1,     1,   153,    -1,   153,    -1,     8,   150,
       9,    -1,     1,   150,     9,    -1,     8,   150,     1,    -1,
     157,    -1,   154,    30,   155,    -1,   154,    29,   155,    -1,
     154,     1,   155,    -1,   155,    -1,   155,    31,   156,    -1,
     155,    32,   156,    -1,   155,     1,   156,    -1,   156,    -1,
       8,   154,     9,    -1,     1,   154,     9,    -1,     8,   154,
       1,    -1,   165,    -1,   157,    30,   158,    -1,   157,    29,
     158,    -1,   157,     1,   158,    -1,   158,    -1,   158,    31,
     159,    -1,   158,    32,   159,    -1,   158,     1,   159,    -1,
     159,    -1,     8,   157,     9,    -1,     1,   157,     9,    -1,
       8,   157,     1,    -1,   166,    -1,     8,   160,     9,    -1,
       1,   160,     9,    -1,     8,   160,     1,    -1,     1,   160,
       1,    -1,   160,    18,   160,    -1,   160,    39,   160,    -1,
     160,     1,   160,    -1,    40,   160,    -1,     1,   160,    -1,
     142,   161,   142,    -1,    33,    17,    75,    -1,     1,    17,
      75,    -1,    33,     1,    75,    -1,     1,    75,    -1,    75,
      43,    33,    17,    75,    -1,    75,     1,    33,    17,    75,
      -1,    75,    43,     1,    17,    75,    -1,    75,    43,    33,
       1,    75,    -1,    75,     1,    17,    75,    -1,    75,    43,
       1,    75,    -1,    75,     1,    33,     1,    75,    -1,    75,
       1,    75,    -1,     1,    -1,    14,    -1,    26,    -1,    15,
      -1,    27,    -1,    17,    -1,    28,    -1,     8,   162,     9,
      -1,     1,   162,     9,    -1,     8,   162,     1,    -1,     1,
     162,     1,    -1,   162,    18,   162,    -1,   162,    39,   162,
      -1,   162,     1,   162,    -1,    40,   162,    -1,     1,   162,
      -1,   146,   161,   146,    -1,    33,    17,    75,    -1,     1,
      17,    75,    -1,    33,     1,    75,    -1,     1,    75,    -1,
      75,    43,    33,    17,    75,    -1,    75,     1,    33,    17,
      75,    -1,    75,    43,     1,    17,    75,    -1,    75,    43,
      33,     1,    75,    -1,    75,     1,    17,    75,    -1,    75,
      43,     1,    75,    -1,    75,     1,    33,     1,    75,    -1,
      75,     1,    75,    -1,    19,    43,    33,    17,    75,    -1,
      19,    43,     1,    17,    75,    -1,    19,    43,    33,     1,
      75,    -1,    19,     1,    17,    75,    -1,    19,    43,     1,
      75,    -1,    19,     1,    33,     1,    75,    -1,    19,     1,
      75,    -1,     1,    -1,   164,    -1,    75,    -1,    91,    -1,
      23,    -1,    24,    -1,   164,    -1,    75,    -1,    19,    43,
      75,    -1,     1,    43,    75,    -1,    19,     1,    75,    -1,
      91,    -1,   164,    -1,    75,    -1,    75,    43,    75,    -1,
      75,     1,    75,    -1,    19,    43,    75,    -1,     1,    43,
      75,    -1,    19,     1,    75,    -1,    91,    -1,   164,    -1,
      75,    -1,    91,    -1,    45,    -1,     7,    45,    -1,     1,
      45,    -1,     7,     1,    -1,     1,    -1,   168,   171,   169,
      -1,     1,    -1,    -1,   171,    75,    16,   172,    44,    -1,
     171,    75,     1,   172,    44,    -1,   171,    75,    16,   172,
       1,    -1,   171,    75,     1,   172,     1,    -1,     1,    -1,
       8,   172,     9,    -1,     1,   172,     9,    -1,     8,   172,
       1,    -1,     1,   172,     1,    -1,   172,    18,   172,    -1,
     172,    39,   172,    -1,   172,     1,   172,    -1,    40,   172,
      -1,     1,   172,    -1,   150,   161,   150,    -1,     1,    -1,
      46,    -1,     1,    -1,    44,     7,    46,    -1,     1,     7,
      46,    -1,    44,     1,    46,    -1,    44,     7,     1,    -1,
       1,    46,    -1,    44,     1,    -1,     1,     7,     1,    -1,
       1,    -1,   173,   176,   174,    -1,     1,    -1,     8,   176,
       9,    -1,     1,   176,     9,    -1,     8,   176,     1,    -1,
       1,   176,     1,    -1,   176,    18,   176,    -1,   176,    39,
     176,    -1,   176,     1,   176,    -1,    40,   176,    -1,     1,
     176,    -1,    75,    43,    75,    17,    75,    43,    75,    -1,
      75,    43,    75,    17,    19,    43,    75,    -1,    19,    43,
      75,    17,    75,    43,    75,    -1,    75,    43,    75,    17,
     167,    -1,    75,     1,    75,    17,   167,    -1,    75,    43,
      75,     1,   167,    -1,    75,     1,    75,     1,   167,    -1,
      19,    43,    75,    17,    19,    43,    75,    -1,    19,    43,
      75,    17,   167,    -1,    19,     1,    75,    17,   167,    -1,
      19,    43,    75,     1,   167,    -1,    19,     1,    75,     1,
     167,    -1,     1,    75,    17,   167,    -1,     1,    43,    75,
       1,   167,    -1,     1,    75,     1,   167,    -1,     1,    -1,
      47,    -1,     1,    -1,     7,    47,    -1,     1,    47,    -1,
       7,     1,    -1,     1,    -1,   177,   182,   178,    -1,   177,
     178,    -1,     1,    -1,    17,    10,    -1,     1,    10,    -1,
      17,     1,    -1,     1,    -1,    11,    44,    -1,     1,    44,
      -1,    11,     1,    -1,     1,    -1,    75,   180,   183,   181,
      -1,   182,    75,   180,   183,   181,    -1,    75,   180,   181,
      -1,   182,    75,   180,   181,    -1,     1,    -1,   184,    -1,
     183,    42,   184,    -1,   183,     1,   184,    -1,     1,    -1,
      19,    -1,    75,    -1,     1,    -1,    36,    -1,     1,    -1,
       7,    36,    -1,     1,    36,    -1,     7,     1,    -1,     1,
      -1,   185,   186,    -1,   185,   188,   186,    -1,   192,    44,
      -1,   192,     1,    -1,   188,   192,    44,    -1,   188,   192,
       1,    -1,     1,    -1,     8,   192,    58,   192,     9,    -1,
       1,   192,    58,   192,     9,    -1,     8,   192,     1,   192,
       9,    -1,     8,   192,    58,   192,     1,    -1,     1,   192,
       1,   192,     9,    -1,     1,   192,    58,   192,     1,    -1,
       8,   192,     1,   192,     1,    -1,     1,   192,     1,   192,
       1,    -1,     8,    75,    42,   192,     9,    -1,     1,    75,
      42,   192,     9,    -1,     8,    75,     1,   192,     9,    -1,
       8,    75,    42,   192,     1,    -1,     1,    75,     1,   192,
       9,    -1,     1,    75,    42,   192,     1,    -1,     8,    75,
       1,   192,     1,    -1,     1,    75,     1,   192,     1,    -1,
       8,    19,    42,   192,     9,    -1,     1,    19,    42,   192,
       9,    -1,     8,    19,     1,   192,     9,    -1,     8,    19,
      42,   192,     1,    -1,     1,    19,     1,   192,     9,    -1,
       1,    19,    42,   192,     1,    -1,     8,    19,     1,   192,
       1,    -1,     1,    19,     1,   192,     1,    -1,     8,    75,
      42,   192,     9,    -1,     1,    75,    42,   192,     9,    -1,
       8,    75,     1,   192,     9,    -1,     8,    75,    42,   192,
       1,    -1,     1,    75,     1,   192,     9,    -1,     1,    75,
      42,   192,     1,    -1,     8,    75,     1,   192,     1,    -1,
       1,    75,     1,   192,     1,    -1,     8,   192,     9,    -1,
       1,   192,     9,    -1,     8,   192,     1,    -1,     1,   192,
       1,    -1,   192,    18,   192,    -1,   192,    39,   192,    -1,
     192,     1,   192,    -1,    40,   192,    -1,     1,   192,    -1,
     192,    49,   192,    -1,    50,   192,    -1,    51,   192,    -1,
      52,   192,    -1,    53,   192,    -1,    54,   192,    -1,    55,
     192,    -1,    56,   189,    -1,    57,   189,    -1,    59,   190,
      -1,    60,   191,    -1,    61,   191,    -1,    62,   190,    -1,
      63,   191,    -1,     1,   190,    -1,     1,   191,    -1,    75,
      -1,    75,    43,    35,    -1,    75,    43,    34,    -1,    19,
      43,    35,    -1,    19,    43,    34,    -1,    75,    43,     1,
      -1,    75,     1,    35,    -1,    75,     1,    34,    -1,     1,
      -1,    48,    -1,     1,    -1,     7,    48,    -1,     1,    48,
      -1,     7,     1,    -1,     1,    -1,   193,   196,   194,    -1,
     202,   201,    44,    -1,   202,   201,     1,    -1,   196,   202,
     201,    44,    -1,   196,   202,   201,     1,    -1,     1,    -1,
      14,    75,    15,    -1,    14,    75,     1,    -1,     1,    75,
      15,    -1,     8,   201,    58,   201,     9,    -1,     8,   201,
       1,   201,     9,    -1,     8,   201,    58,   201,     1,    -1,
       1,   201,     1,   201,     9,    -1,     1,   201,    58,   201,
       1,    -1,     8,   201,     1,   201,     1,    -1,     1,   201,
       1,   201,     1,    -1,     8,    75,    42,   201,     9,    -1,
       1,    75,    42,   201,     9,    -1,     8,    75,     1,   201,
       9,    -1,     8,    75,    42,   201,     1,    -1,     1,    75,
       1,   201,     9,    -1,     1,    75,    42,   201,     1,    -1,
       8,    75,     1,   201,     1,    -1,     1,    75,     1,   201,
       1,    -1,     8,    19,    42,   201,     9,    -1,     1,    19,
      42,   201,     9,    -1,     8,    19,     1,   201,     9,    -1,
       8,    19,    42,   201,     1,    -1,     1,    19,     1,   201,
       9,    -1,     1,    19,    42,   201,     1,    -1,     8,    19,
       1,   201,     1,    -1,     1,    19,     1,   201,     1,    -1,
       8,    75,    42,   201,     9,    -1,     1,    75,    42,   201,
       9,    -1,     8,    75,     1,   201,     9,    -1,     8,    75,
      42,   201,     1,    -1,     1,    75,     1,   201,     9,    -1,
       1,    75,    42,   201,     1,    -1,     8,    75,     1,   201,
       1,    -1,     1,    75,     1,   201,     1,    -1,     8,   201,
       9,    -1,     1,   201,     9,    -1,     8,   201,     1,    -1,
       1,   201,     1,    -1,   201,    18,   201,    -1,   201,    39,
     201,    -1,   201,     1,   201,    -1,    40,   201,    -1,     1,
     201,    -1,   201,    49,   201,    -1,    50,   201,    -1,    51,
     201,    -1,    52,   201,    -1,    53,   201,    -1,    54,   201,
      -1,    55,   201,    -1,    56,   198,    -1,    57,   198,    -1,
      59,   199,    -1,    60,   200,    -1,    61,   200,    -1,    62,
     199,    -1,    63,   200,    -1,     1,   199,    -1,     1,   200,
      -1,   197,    71,   201,    -1,   197,    72,   201,    -1,   197,
      73,   201,    -1,   197,     1,   201,    -1,   197,   198,    -1,
      14,    14,    75,    15,    15,   201,    -1,    12,    12,    75,
      13,    13,   201,    -1,     8,    75,    42,    75,     9,   201,
      -1,     8,    19,    42,    75,     9,   201,    -1,    71,   201,
      -1,    72,   201,    -1,    73,   201,    -1,   201,    58,   201,
      -1,    75,    -1,    75,    43,    35,    -1,    75,    43,    34,
      -1,    19,    43,    35,    -1,    19,    43,    34,    -1,    75,
      43,     1,    -1,    75,     1,    35,    -1,    75,     1,    34,
      -1,     1,    -1,    -1,    74,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  mcmas_parser::yyprhs_[] =
  {
         0,     0,     3,     5,     8,    13,    18,    20,    28,    35,
      42,    48,    55,    61,    67,    72,    75,    78,    81,    83,
      86,    89,    92,    94,   103,   111,   119,   126,   134,   141,
     148,   154,   156,   159,   162,   165,   167,   170,   173,   176,
     178,   182,   185,   186,   190,   194,   196,   200,   204,   208,
     214,   220,   226,   232,   238,   243,   249,   254,   256,   258,
     262,   266,   268,   270,   273,   276,   278,   281,   284,   287,
     289,   292,   295,   298,   300,   304,   306,   310,   312,   315,
     318,   321,   323,   326,   329,   332,   334,   338,   341,   343,
     347,   350,   352,   355,   358,   360,   363,   366,   368,   371,
     374,   377,   379,   382,   385,   388,   390,   394,   395,   398,
     400,   405,   407,   411,   415,   419,   421,   425,   429,   433,
     435,   437,   440,   442,   444,   446,   449,   452,   455,   457,
     466,   474,   484,   493,   495,   499,   503,   507,   511,   514,
     517,   521,   523,   526,   529,   532,   534,   538,   541,   543,
     545,   549,   553,   555,   559,   563,   567,   571,   574,   577,
     581,   583,   586,   589,   592,   594,   598,   601,   603,   607,
     609,   611,   615,   619,   621,   624,   627,   630,   632,   635,
     638,   641,   643,   647,   652,   656,   659,   661,   665,   670,
     674,   676,   678,   681,   683,   685,   688,   690,   693,   696,
     699,   701,   704,   707,   710,   712,   717,   719,   724,   726,
     731,   736,   738,   742,   746,   748,   752,   756,   757,   760,
     765,   770,   775,   780,   782,   786,   790,   794,   798,   802,
     806,   810,   813,   816,   820,   822,   826,   830,   834,   838,
     842,   846,   850,   853,   856,   860,   862,   866,   870,   874,
     876,   880,   884,   888,   890,   894,   898,   902,   904,   908,
     912,   916,   918,   922,   926,   928,   931,   934,   936,   940,
     944,   948,   950,   954,   958,   962,   964,   968,   972,   974,
     977,   980,   982,   986,   990,   994,   996,  1000,  1004,  1008,
    1010,  1014,  1018,  1020,  1023,  1026,  1028,  1032,  1036,  1040,
    1042,  1046,  1050,  1054,  1056,  1060,  1064,  1068,  1070,  1074,
    1078,  1082,  1084,  1088,  1092,  1096,  1098,  1102,  1106,  1110,
    1112,  1116,  1120,  1124,  1126,  1130,  1134,  1138,  1142,  1146,
    1150,  1154,  1157,  1160,  1164,  1168,  1172,  1176,  1179,  1185,
    1191,  1197,  1203,  1208,  1213,  1219,  1223,  1225,  1227,  1229,
    1231,  1233,  1235,  1237,  1241,  1245,  1249,  1253,  1257,  1261,
    1265,  1268,  1271,  1275,  1279,  1283,  1287,  1290,  1296,  1302,
    1308,  1314,  1319,  1324,  1330,  1334,  1340,  1346,  1352,  1357,
    1362,  1368,  1372,  1374,  1376,  1378,  1380,  1382,  1384,  1386,
    1388,  1392,  1396,  1400,  1402,  1404,  1406,  1410,  1414,  1418,
    1422,  1426,  1428,  1430,  1432,  1434,  1436,  1439,  1442,  1445,
    1447,  1451,  1453,  1454,  1460,  1466,  1472,  1478,  1480,  1484,
    1488,  1492,  1496,  1500,  1504,  1508,  1511,  1514,  1518,  1520,
    1522,  1524,  1528,  1532,  1536,  1540,  1543,  1546,  1550,  1552,
    1556,  1558,  1562,  1566,  1570,  1574,  1578,  1582,  1586,  1589,
    1592,  1600,  1608,  1616,  1622,  1628,  1634,  1640,  1648,  1654,
    1660,  1666,  1672,  1677,  1683,  1688,  1690,  1692,  1694,  1697,
    1700,  1703,  1705,  1709,  1712,  1714,  1717,  1720,  1723,  1725,
    1728,  1731,  1734,  1736,  1741,  1747,  1751,  1756,  1758,  1760,
    1764,  1768,  1770,  1772,  1774,  1776,  1778,  1780,  1783,  1786,
    1789,  1791,  1794,  1798,  1801,  1804,  1808,  1812,  1814,  1820,
    1826,  1832,  1838,  1844,  1850,  1856,  1862,  1868,  1874,  1880,
    1886,  1892,  1898,  1904,  1910,  1916,  1922,  1928,  1934,  1940,
    1946,  1952,  1958,  1964,  1970,  1976,  1982,  1988,  1994,  2000,
    2006,  2010,  2014,  2018,  2022,  2026,  2030,  2034,  2037,  2040,
    2044,  2047,  2050,  2053,  2056,  2059,  2062,  2065,  2068,  2071,
    2074,  2077,  2080,  2083,  2086,  2089,  2091,  2095,  2099,  2103,
    2107,  2111,  2115,  2119,  2121,  2123,  2125,  2128,  2131,  2134,
    2136,  2140,  2144,  2148,  2153,  2158,  2160,  2164,  2168,  2172,
    2178,  2184,  2190,  2196,  2202,  2208,  2214,  2220,  2226,  2232,
    2238,  2244,  2250,  2256,  2262,  2268,  2274,  2280,  2286,  2292,
    2298,  2304,  2310,  2316,  2322,  2328,  2334,  2340,  2346,  2352,
    2358,  2362,  2366,  2370,  2374,  2378,  2382,  2386,  2389,  2392,
    2396,  2399,  2402,  2405,  2408,  2411,  2414,  2417,  2420,  2423,
    2426,  2429,  2432,  2435,  2438,  2441,  2445,  2449,  2453,  2457,
    2460,  2467,  2474,  2481,  2488,  2491,  2494,  2497,  2501,  2503,
    2507,  2511,  2515,  2519,  2523,  2527,  2531,  2533,  2534
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  mcmas_parser::yyrline_[] =
  {
         0,   275,   275,   276,   279,   282,   285,   290,   291,   292,
     293,   294,   301,   308,   315,   325,   328,   332,   336,   340,
     343,   347,   351,   356,   363,   370,   377,   384,   391,   398,
     406,   414,   419,   422,   426,   430,   434,   437,   441,   445,
     449,   455,   463,   468,   481,   487,   492,   505,   510,   515,
     531,   536,   541,   546,   559,   565,   571,   577,   581,   589,
     600,   606,   610,   613,   616,   620,   626,   629,   633,   637,
     641,   644,   648,   652,   656,   662,   668,   674,   680,   683,
     687,   691,   695,   698,   702,   706,   711,   717,   720,   725,
     731,   734,   739,   742,   747,   752,   755,   760,   767,   770,
     774,   778,   782,   785,   789,   793,   797,   803,   806,   813,
     817,   823,   827,   830,   839,   855,   860,   863,   872,   888,
     893,   899,   909,   913,   916,   920,   923,   927,   931,   936,
     950,   964,   978,   992,   998,  1001,  1005,  1009,  1013,  1017,
    1021,  1025,  1029,  1032,  1036,  1040,  1044,  1050,  1053,  1057,
    1073,  1089,  1095,  1102,  1105,  1109,  1113,  1117,  1121,  1125,
    1129,  1133,  1136,  1140,  1144,  1148,  1154,  1160,  1166,  1172,
    1176,  1184,  1194,  1200,  1207,  1210,  1214,  1218,  1222,  1225,
    1229,  1233,  1238,  1244,  1252,  1260,  1266,  1272,  1278,  1286,
    1294,  1299,  1306,  1313,  1318,  1325,  1332,  1337,  1340,  1344,
    1348,  1352,  1355,  1359,  1363,  1367,  1373,  1378,  1384,  1389,
    1395,  1401,  1409,  1419,  1425,  1432,  1438,  1444,  1447,  1455,
    1461,  1467,  1473,  1479,  1484,  1487,  1492,  1497,  1502,  1508,
    1514,  1520,  1526,  1531,  1538,  1543,  1546,  1551,  1556,  1561,
    1567,  1573,  1579,  1585,  1590,  1597,  1602,  1608,  1614,  1619,
    1622,  1628,  1634,  1639,  1642,  1645,  1650,  1655,  1659,  1665,
    1671,  1676,  1679,  1685,  1690,  1693,  1699,  1704,  1707,  1710,
    1715,  1720,  1724,  1730,  1736,  1741,  1744,  1750,  1755,  1758,
    1764,  1769,  1772,  1775,  1780,  1785,  1789,  1795,  1801,  1806,
    1809,  1815,  1820,  1823,  1829,  1834,  1837,  1840,  1845,  1850,
    1854,  1860,  1866,  1871,  1874,  1880,  1886,  1891,  1894,  1897,
    1902,  1907,  1910,  1916,  1922,  1927,  1930,  1936,  1942,  1947,
    1950,  1953,  1958,  1963,  1969,  1972,  1977,  1982,  1987,  1993,
    1999,  2005,  2011,  2016,  2023,  2040,  2045,  2050,  2055,  2095,
    2101,  2107,  2113,  2119,  2125,  2131,  2137,  2142,  2145,  2148,
    2151,  2154,  2157,  2162,  2165,  2170,  2175,  2180,  2186,  2192,
    2198,  2204,  2209,  2216,  2233,  2238,  2243,  2248,  2279,  2285,
    2291,  2297,  2303,  2309,  2315,  2321,  2338,  2343,  2348,  2353,
    2358,  2363,  2368,  2374,  2377,  2387,  2390,  2393,  2397,  2400,
    2410,  2429,  2434,  2439,  2442,  2445,  2455,  2487,  2493,  2512,
    2517,  2522,  2526,  2529,  2539,  2544,  2547,  2550,  2554,  2558,
    2562,  2563,  2567,  2568,  2576,  2581,  2586,  2591,  2595,  2598,
    2603,  2608,  2613,  2619,  2625,  2630,  2636,  2641,  2648,  2656,
    2659,  2663,  2666,  2670,  2674,  2678,  2682,  2686,  2690,  2694,
    2698,  2702,  2705,  2710,  2715,  2720,  2726,  2732,  2737,  2743,
    2748,  2823,  2885,  2947,  2991,  2998,  3005,  3012,  3060,  3091,
    3097,  3103,  3109,  3115,  3121,  3127,  3134,  3137,  3141,  3144,
    3148,  3152,  3156,  3157,  3158,  3162,  3165,  3169,  3173,  3177,
    3180,  3184,  3188,  3192,  3198,  3206,  3212,  3220,  3224,  3231,
    3240,  3245,  3249,  3252,  3262,  3269,  3272,  3276,  3279,  3283,
    3287,  3291,  3292,  3294,  3298,  3302,  3306,  3310,  3314,  3320,
    3325,  3330,  3335,  3340,  3345,  3350,  3355,  3368,  3374,  3380,
    3386,  3392,  3398,  3404,  3410,  3416,  3421,  3426,  3431,  3436,
    3441,  3446,  3451,  3464,  3470,  3476,  3482,  3488,  3494,  3500,
    3507,  3510,  3515,  3520,  3525,  3531,  3537,  3542,  3548,  3553,
    3559,  3565,  3571,  3577,  3583,  3589,  3595,  3603,  3611,  3620,
    3630,  3640,  3650,  3660,  3666,  3672,  3687,  3704,  3721,  3734,
    3747,  3752,  3757,  3762,  3769,  3772,  3776,  3779,  3783,  3787,
    3791,  3793,  3798,  3803,  3808,  3813,  3817,  3827,  3832,  3837,
    3848,  3853,  3858,  3863,  3868,  3873,  3878,  3891,  3897,  3903,
    3909,  3915,  3921,  3927,  3933,  3939,  3944,  3949,  3954,  3959,
    3964,  3969,  3974,  3987,  3993,  3999,  4005,  4011,  4017,  4023,
    4030,  4033,  4038,  4043,  4048,  4054,  4060,  4065,  4071,  4076,
    4082,  4088,  4094,  4100,  4106,  4112,  4118,  4126,  4134,  4143,
    4153,  4163,  4173,  4183,  4187,  4191,  4200,  4209,  4218,  4223,
    4238,  4253,  4268,  4287,  4304,  4312,  4320,  4328,  4342,  4357,
    4374,  4391,  4404,  4417,  4422,  4427,  4432,  4437,  4440
  };

  // Print the state stack on the debug stream.
  void
  mcmas_parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (state_stack_type::const_iterator i = yystate_stack_.begin ();
	 i != yystate_stack_.end (); ++i)
      *yycdebug_ << ' ' << *i;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  mcmas_parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    /* Print the symbols being reduced, and their result.  */
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
	       << " (line " << yylno << "):" << std::endl;
    /* The symbols being reduced.  */
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
		       yyrhs_[yyprhs_[yyrule] + yyi],
		       &(yysemantic_stack_[(yynrhs) - (yyi + 1)]),
		       &(yylocation_stack_[(yynrhs) - (yyi + 1)]));
  }
#endif // YYDEBUG

  /* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
  mcmas_parser::token_number_type
  mcmas_parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
           0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int mcmas_parser::yyeof_ = 0;
  const int mcmas_parser::yylast_ = 7829;
  const int mcmas_parser::yynnts_ = 125;
  const int mcmas_parser::yyempty_ = -2;
  const int mcmas_parser::yyfinal_ = 16;
  const int mcmas_parser::yyterror_ = 1;
  const int mcmas_parser::yyerrcode_ = 256;
  const int mcmas_parser::yyntokens_ = 78;

  const unsigned int mcmas_parser::yyuser_token_number_max_ = 332;
  const mcmas_parser::token_number_type mcmas_parser::yyundef_token_ = 2;


} // yy

/* Line 1136 of lalr1.cc  */
#line 11821 "parser/nssis.cc"


/* Line 1138 of lalr1.cc  */
#line 4444 "parser/nssis_new.yy"

void
yy::mcmas_parser::error (const yy::mcmas_parser::location_type& l,
                          const std::string& m)
{
  driver.error (l, m);
}

