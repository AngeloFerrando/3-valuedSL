# Makefile for mcmas+
# --------------------------------------------------
ifneq (,$(findstring Linux, $(shell uname -s)))
	MCMASEXE = mcmas
	OSTYPE = linux
endif
ifneq (,$(findstring SunOS, $(shell uname -s)))
	MCMASEXE = mcmas
	OSTYPE = solaris
endif
ifneq (,$(findstring CYGWIN, $(shell uname -s)))
	MCMASEXE = mcmas.exe
	OSTYPE = cygwin
endif
ifneq (,$(findstring Darwin, $(shell uname -s)))
	#ifneq (,$(findstring 10.0.0, $(shell uname -r)))
	ifneq (,$(findstring 9, $(shell uname -r | sed 's/\([0-9]*\).*/\1/')))
		OSTYPE = macosx
	else
		OSTYPE = macosx64
	endif
endif

ifneq (,$(findstring x86_64, $(shell uname -m)))
	MCMASEXE = mcmas
	ARCH = x86_64
endif
ifneq (,$(findstring ia64, $(shell uname -m)))
	MCMASEXE = mcmas
	ARCH = ia64
endif

# Cudd Directory
CUDD	= cudd-2.5.0-exp/

# ---- COMPILERS ----
# C++ compiler
CPP     = g++
# C compiler
CC 	= gcc
# CC compilation flags
CCFLAGS	= -O3
# CPP compilation flags
CPPFLAGS = -O3 -W $(CPPARCH)
INCLUDE = -Iinclude -I$(CUDD)include #-I$(CUDD)obj
# ---- END COMPILERS ----

GCC_MAJOR := $(shell (echo|gcc -dM -E -|grep __GNUC__|cut -d' ' -f3))
GCC_MINOR := $(shell (echo|gcc -dM -E -|grep __GNUC_MINOR__|cut -d' ' -f3))
GCC_PATCHLEVEL := $(shell (echo|gcc -dM -E -|grep __GNUC_PATCHLEVEL__|cut -d' ' -f3))

ifeq ($(shell if [ $(GCC_MAJOR) -lt 4 ]; then echo T; else echo F; fi), T)
	CUDD_MAKEFILE = Makefile.linux64
	#echo GCC version too old
else
	ifeq ($(shell if [ $(GCC_MAJOR) -eq 4 ]; then echo T; else echo F; fi), T)
		ifeq ($(shell if [ $(GCC_MINOR) -lt 2 ]; then echo T; else echo F; fi), T)
			CUDD_MAKEFILE = Makefile.linux64
		else
			ifeq ($(shell if [ $(GCC_MINOR) -eq 2 ]; then echo T; else echo F; fi), T)
				ifeq ($(shell if [ $(GCC_PATCHLEVEL) -lt 4 ]; then echo T; else echo F; fi), T)
					CUDD_MAKEFILE = Makefile.linux64
				else
					CUDD_MAKEFILE = Makefile.linux64.gcc4.2.4
				endif
			else
				CUDD_MAKEFILE = Makefile.linux64.gcc4.2.4	
			endif
		endif
	else
		CUDD_MAKEFILE = Makefile.linux64.gcc4.2.4	
	endif
endif

ifeq ($(OSTYPE),linux)
	ifeq ($(ARCH),ia64)
		CUDD_MAKEFILE = Makefile.linux64
	else
		ifeq ($(ARCH),x86_64)
			ifeq ($(shell if [ $(GCC_MAJOR) -lt 4 ]; then echo T; else echo F; fi), T)
				CUDD_MAKEFILE = Makefile.linux64
			else
				ifeq ($(shell if [ $(GCC_MAJOR) -eq 4 ]; then echo T; else echo F; fi), T)
					ifeq ($(shell if [ $(GCC_MINOR) -lt 2 ]; then echo T; else echo F; fi), T)
						CUDD_MAKEFILE = Makefile.linux64
					else
						ifeq ($(shell if [ $(GCC_MINOR) -eq 2 ]; then echo T; else echo F; fi), T)
							ifeq ($(shell if [ $(GCC_PATCHLEVEL) -lt 4 ]; then echo T; else echo F; fi), T)
								CUDD_MAKEFILE = Makefile.linux64
							else
								CUDD_MAKEFILE = Makefile.linux64.gcc4.2.4
							endif
						else
							CUDD_MAKEFILE = Makefile.linux64.gcc4.2.4	
						endif
					endif
				else
					CUDD_MAKEFILE = Makefile.linux64.gcc4.2.4	
				endif
			endif

		else
      ifeq ($(shell if [ $(GCC_MAJOR) -lt 4 ]; then echo T; else echo F; fi), T)
				CUDD_MAKEFILE = Makefile.linux
			else
				ifeq ($(shell if [ $(GCC_MAJOR) -eq 4 ]; then echo T; else echo F; fi), T)
					ifeq ($(shell if [ $(GCC_MINOR) -lt 2 ]; then echo T; else echo F; fi), T)
						CUDD_MAKEFILE = Makefile.linux
					else
						ifeq ($(shell if [ $(GCC_MINOR) -eq 2 ]; then echo T; else echo F; fi), T)
							ifeq ($(shell if [ $(GCC_PATCHLEVEL) -lt 4 ]; then echo T; else echo F; fi), T)
								CUDD_MAKEFILE = Makefile.linux
							else
								CUDD_MAKEFILE = Makefile.linux.gcc4.2.4
							endif
						else
							CUDD_MAKEFILE = Makefile.linux.gcc4.2.4	
						endif
					endif
				else
					CUDD_MAKEFILE = Makefile.linux.gcc4.2.4	
				endif
			endif
		endif
	endif
endif
# Solaris
ifeq ($(OSTYPE),solaris)
	CUDD_MAKEFILE = Makefile.solaris
endif
# Cygwin
ifeq ($(OSTYPE),cygwin)
	CUDD_MAKEFILE = Makefile.cygwin
endif
# Darwin
ifeq ($(OSTYPE),macosx)
	CUDD_MAKEFILE = Makefile.macosx
endif

ifeq ($(OSTYPE),macosx64)
	CUDD_MAKEFILE = Makefile.macosx64
endif



GRAMMAR		= parser/nssis
LEXFILE 	= parser/nssis
DRIVER		= parser/mcmas-driver
SYNTAXCHECK	= parser/syntaxcheck
UTILITIES	= utilities/utilities
STRATEGY_LOGIC = utilities/strategy_logic
READ_OPTIONS = utilities/read_options
SIMULATION	= utilities/simulation
BDDORDER	= utilities/bddorder
COMPUTEREACH	= utilities/computereach
ARITHMETIC_EXPRESSION	= utilities/arithmetic_expression
ASSIGNMENT = utilities/assignment
ATOMIC_PROPOSITION = utilities/atomic_proposition
BASIC_AGENT = utilities/basic_agent
BASICTYPE = utilities/basictype
BIT_EXPRESSION = utilities/bit_expression
BOOL_EXPRESSION = utilities/bool_expression
BOOL_VALUE = utilities/bool_value
ENUMERATE = utilities/enumerate
ENUM_VALUE = utilities/enum_value
EVOLUTION_LINE = utilities/evolution_line
EXPRESSION = utilities/expression
FAIRNESS_EXPRESSION = utilities/fairness_expression
INT_VALUE = utilities/int_value
LACTION = utilities/laction
LOGIC_EXPRESSION = utilities/logic_expression
MODAL_FORMULA = utilities/modal_formula
OBJECT = utilities/object
PROTOCOL_LINE = utilities/protocol_line
RANGEDINT = utilities/rangedint
STRATEGY = utilities/strategy
TRANSITION = utilities/transition
VARIABLE = utilities/variable
BENCHMARK = utilities/benchmark
MAIN		= main
LEX		= flex
YACC		= bison
############################################################################
# Find which version of Bison is used
BISON_VERSION := $(shell (echo|$(YACC) --version|grep bison|cut -d' ' -f4))
ifeq ($(BISON_VERSION), 2.3)
	BISONSUFFIX =
else
	BISONSUFFIX = _new
endif
############################################################################

CUDDLIBS = $(CUDD)obj/cuddObj.o $(CUDD)obj/libobj.a $(CUDD)cudd/libcudd.a $(CUDD)mtr/libmtr.a $(CUDD)st/libst.a $(CUDD)util/libutil.a $(CUDD)epd/libepd.a

PTHREADLIB = -lpthread
RTLIB = -lrt

# Uncomment and run "touch main.cc && make" to enable benchmarks
#BENCHMARK_FLAGS = -DBENCHMARK

# Force i386 architecture
#MCMASEXE = mcmas32
#CPPARCH = -m32
#CUDD_MAKEFILE = Makefile.linux

# Force x86_64 architecture
#MCMASEXE = mcmas64
#CPPARCH = -m64
#CUDD_MAKEFILE = Makefile.linux64



default: all

all: cuddlibrary $(MCMASEXE)

cuddlibrary: 
	cd $(CUDD) && /bin/cp $(CUDD_MAKEFILE) Makefile && $(MAKE)



OBJECTS = parser/lex.yy.o $(GRAMMAR).o $(READ_OPTIONS).o $(DRIVER).o $(SYNTAXCHECK).o $(UTILITIES).o $(STRATEGY_LOGIC).o $(SIMULATION).o $(BDDORDER).o $(COMPUTEREACH).o $(ARITHMETIC_EXPRESSION).o $(ASSIGNMENT).o $(ATOMIC_PROPOSITION).o $(BASIC_AGENT).o $(BASICTYPE).o $(BIT_EXPRESSION).o $(BOOL_EXPRESSION).o $(BOOL_VALUE).o $(ENUMERATE).o $(ENUM_VALUE).o $(EVOLUTION_LINE).o $(EXPRESSION).o $(FAIRNESS_EXPRESSION).o $(INT_VALUE).o $(LACTION).o $(LOGIC_EXPRESSION).o $(MODAL_FORMULA).o $(OBJECT).o $(PROTOCOL_LINE).o $(RANGEDINT).o $(STRATEGY).o $(TRANSITION).o $(VARIABLE).o

$(MCMASEXE) : $(OBJECTS) $(MAIN).cc $(CUDDLIBS) $(BENCHMARK).o
	$(CPP) $(CPPFLAGS) $(BENCHMARK_FLAGS) $(INCLUDE) $(CUDDLIBS) $(PTHREADLIB) $(OBJECTS) $(BENCHMARK).o -o $(MCMASEXE) $(MAIN).cc $(RTLIB)

parser/lex.yy.o: $(LEXFILE).ll $(GRAMMAR)$(BISONSUFFIX).yy
	$(LEX) -oparser/lex.yy.c $(LEXFILE).ll

	$(YACC) --defines=$(GRAMMAR).hh $(GRAMMAR)$(BISONSUFFIX).yy -o $(GRAMMAR).cc
	$(CPP) $(CPPFLAGS) $(INCLUDE)  -c parser/lex.yy.c -o parser/lex.yy.o

$(GRAMMAR).o: include/utilities.hh include/types.hh $(LEXFILE).ll $(GRAMMAR)$(BISONSUFFIX).yy
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c $(GRAMMAR).cc -o $(GRAMMAR).o

$(SYNTAXCHECK).o: include/utilities.hh include/types.hh $(SYNTAXCHECK).cc
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c $(SYNTAXCHECK).cc -o $(SYNTAXCHECK).o

$(UTILITIES).o: include/utilities.hh $(UTILITIES).cc
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c $(UTILITIES).cc -o $(UTILITIES).o

$(STRATEGY_LOGIC).o: include/utilities.hh include/strategy_logic.hh $(STRATEGY_LOGIC).cc
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c $(STRATEGY_LOGIC).cc -o $(STRATEGY_LOGIC).o

$(READ_OPTIONS).o: include/utilities.hh $(READ_OPTIONS).cc
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c $(READ_OPTIONS).cc -o $(READ_OPTIONS).o

$(SIMULATION).o: include/utilities.hh include/types.hh $(SIMULATION).cc
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c $(SIMULATION).cc -o $(SIMULATION).o

$(BDDORDER).o: include/utilities.hh include/types.hh $(BDDORDER).cc
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c $(BDDORDER).cc -o $(BDDORDER).o

$(COMPUTEREACH).o: include/utilities.hh include/types.hh $(COMPUTEREACH).cc
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c $(COMPUTEREACH).cc -o $(COMPUTEREACH).o

$(ARITHMETIC_EXPRESSION).o: include/utilities.hh include/types.hh $(ARITHMETIC_EXPRESSION).cc
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c $(ARITHMETIC_EXPRESSION).cc -o $(ARITHMETIC_EXPRESSION).o

$(ASSIGNMENT).o: include/utilities.hh include/types.hh $(ASSIGNMENT).cc
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c $(ASSIGNMENT).cc -o $(ASSIGNMENT).o

$(ATOMIC_PROPOSITION).o: include/utilities.hh include/types.hh $(ATOMIC_PROPOSITION).cc
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c $(ATOMIC_PROPOSITION).cc -o $(ATOMIC_PROPOSITION).o

$(BASIC_AGENT).o: include/utilities.hh include/types.hh $(BASIC_AGENT).cc
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c $(BASIC_AGENT).cc -o $(BASIC_AGENT).o

$(BASICTYPE).o: include/utilities.hh include/types.hh $(BASICTYPE).cc
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c $(BASICTYPE).cc -o $(BASICTYPE).o

$(BIT_EXPRESSION).o: include/utilities.hh include/types.hh $(BIT_EXPRESSION).cc
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c $(BIT_EXPRESSION).cc -o $(BIT_EXPRESSION).o

$(BOOL_EXPRESSION).o: include/utilities.hh include/types.hh $(BOOL_EXPRESSION).cc
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c $(BOOL_EXPRESSION).cc -o $(BOOL_EXPRESSION).o

$(BOOL_VALUE).o: include/utilities.hh include/types.hh $(BOOL_VALUE).cc
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c $(BOOL_VALUE).cc -o $(BOOL_VALUE).o

$(ENUMERATE).o: include/utilities.hh include/types.hh $(ENUMERATE).cc
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c $(ENUMERATE).cc -o $(ENUMERATE).o

$(ENUM_VALUE).o: include/utilities.hh include/types.hh $(ENUM_VALUE).cc
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c $(ENUM_VALUE).cc -o $(ENUM_VALUE).o

$(EVOLUTION_LINE).o: include/utilities.hh include/types.hh $(EVOLUTION_LINE).cc
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c $(EVOLUTION_LINE).cc -o $(EVOLUTION_LINE).o

$(EXPRESSION).o: include/utilities.hh include/types.hh $(EXPRESSION).cc
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c $(EXPRESSION).cc -o $(EXPRESSION).o

$(FAIRNESS_EXPRESSION).o: include/utilities.hh include/types.hh $(FAIRNESS_EXPRESSION).cc
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c $(FAIRNESS_EXPRESSION).cc -o $(FAIRNESS_EXPRESSION).o

$(INT_VALUE).o: include/utilities.hh include/types.hh $(INT_VALUE).cc
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c $(INT_VALUE).cc -o $(INT_VALUE).o

$(LACTION).o: include/utilities.hh include/types.hh $(LACTION).cc
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c $(LACTION).cc -o $(LACTION).o

$(LOGIC_EXPRESSION).o: include/utilities.hh include/types.hh $(LOGIC_EXPRESSION).cc
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c $(LOGIC_EXPRESSION).cc -o $(LOGIC_EXPRESSION).o

$(MODAL_FORMULA).o: include/utilities.hh include/types.hh $(MODAL_FORMULA).cc
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c $(MODAL_FORMULA).cc -o $(MODAL_FORMULA).o

$(OBJECT).o: include/utilities.hh include/types.hh $(OBJECT).cc
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c $(OBJECT).cc -o $(OBJECT).o

$(PROTOCOL_LINE).o: include/utilities.hh include/types.hh $(PROTOCOL_LINE).cc
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c $(PROTOCOL_LINE).cc -o $(PROTOCOL_LINE).o

$(RANGEDINT).o: include/utilities.hh include/types.hh $(RANGEDINT).cc
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c $(RANGEDINT).cc -o $(RANGEDINT).o

$(TRANSITION).o: include/utilities.hh include/types.hh $(TRANSITION).cc
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c $(TRANSITION).cc -o $(TRANSITION).o

$(STRATEGY).o: include/utilities.hh include/types.hh $(STRATEGY).cc
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c $(STRATEGY).cc -o $(STRATEGY).o

$(VARIABLE).o: include/utilities.hh include/types.hh $(VARIABLE).cc
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c $(VARIABLE).cc -o $(VARIABLE).o

$(DRIVER).o: $(DRIVER).cc 
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c $(DRIVER).cc -o $(DRIVER).o 

$(BENCHMARK).o: include/types.hh include/benchmark.hh $(BENCHMARK).cc
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c $(BENCHMARK).cc -o $(BENCHMARK).o

.PHONY : clean
clean: cleancudd cleanmcmas

cleancudd:
	cd $(CUDD) && $(MAKE) clean

cleanmcmas:
	rm $(MCMASEXE) $(OBJECTS) parser/lex.yy.c parser/location.hh parser/position.hh parser/stack.hh $(GRAMMAR).hh $(GRAMMAR).cc 
