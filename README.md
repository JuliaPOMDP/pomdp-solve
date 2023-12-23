# POMDP Solve

This repository is a fork of the original POMDP Solve code by Anthony R. Cassandra. The original code can be found at the [POMDP.org](http://www.pomdp.org/code/index.html) website.

From the pomdp-solve website:

> The 'pomdp-solve' program (written in C) solves problems that are formulated as partially observable Markov decision processes, a.k.a. POMDPs. It uses the basic dynamic programming approach for all algorithms, solving one stage at a time working backwards in time. It does finite horizon problems with or without discounting. It will stop solving if the answer is within a tolerable range of the infinite horizon answer, and there are a couple of different stopping conditions (requires a discount factor less than 1.0). Alternatively you can solve a finite horizon problem for some fixed horizon length. The code actually implements a number of POMDP solution algorithms:

> - Enumeration (Sondik '71, Monahan '82, White '91)
> - Two Pass (Sondik '71)
> - Linear Support (Cheng '88) †
> - Witness (Littman '97, Cassandra '98)
> - Incremental Pruning (Zhang and Lui '96, Cassandra, Littman and Zhang '97)
> - Finite Grid -and instance of point-based value iteration (PBVI) (Cassandra '04)
>
> † Requires the commercial CPLEX linear programming solver software.


The code was forked from the v5.4 version. Changes to the code are documented in the [Changelog](#changelog) section below.

## Repo Organization

- `/src`:  The main source directory for the pomdp-solve program.
- `/src/mdp`: This directory contains the code for a library of low-level POMDP manipulation routines, including parsing files and the internal representation used by the program.  Only look at the stuff in this directory if you want to muck around with the file format and/or the internal representation.
- `/src/lp_solve`: This directory contains the code for a public domain linear programming solver. It is included it in this distribution because some minor changes were needed to integrate it with the pomdp-solve code. If the commerical program CPLEX does not exist, this is what is used to solve the linear programs required.


## Documenation
Please reference the [pomdp-solve website](https://www.pomdp.org/code/index.html) for documentation. 

- Binary Downloads and Installation: https://www.pomdp.org/code/index.html
- Command Line Options: https://www.pomdp.org/code/cmd-line.html
- POMDP File Format: https://www.pomdp.org/code/pomdp-file-spec.html
- Value Function File Format: https://www.pomdp.org/code/alpha-file-spec.html
- Policy Graph File Format: https://www.pomdp.org/code/pg-file-spec.html

## Copywrite and Disclaimer

> Copyright 1994-1997, Brown University; 
> Copyright 1998-2023, Anthony R. Cassandra; 
> All Rights Reserved

> Permission to use, copy, modify, and distribute this software and its documentation for any purpose other than its incorporation into a commercial product is hereby granted without fee, provided that the above copyright notice appear in all copies and that both that copyright notice and this permission notice appear in supporting documentation.


## Changelog

### _2023-12-23_

     * configure.ac: Numerous changes to address compiler warnings
	 * src/global.c: Changed strupr to my_strupr for Windows compatibility
     * src/globah.c: Modified getPid to work on POSIX and Windows
     * src/random.c: Modified random number generator to work on non POSIX systems (windows)
     * src/signal-handler.c: Modified signal handler to work on non POSIX systems (windows) and fixed a bug where gInterrupt was not being set after timeout
	 * src/signal-handler.h: Adjusted gInterrupt to be volatile
     * src/timing.c: Modified timing functions to work on non POSIX systems (windows)
     * src/xalloc.c and src/xalloc.h: Added declaration and defined rpl_malloc and rpl_realloc. These were not defined and caused errors for systems that could not use malloc.
     * src/mdp/mdp.c: Removed declaration of IP and IR as they are declared in parser.c and have an extern declaration in mdp.h
	 * src/Makefile.am: Compiler warning fixes. INCLUDES -> AM_CPPFLAGS, CFLAGS -> AM_CFLAGS, LDFLAGS -> AM_LDFLAGS
	 * src/lp-solve/read.h: Added declaration for yyerror, yylex, and yyparse as implicit declaration was causing errors with more modern compilers
	 * src/fg-params.c: Fixed a compiler warning where an or statement wasn't necessary
	 * src/laspack/Makefile.am: Compiler warning fixes. INCLUDES -> AM_CPPFLAGS, CFLAGS -> AM_CFLAGS, YFLAGS -> AM_YFLAGS
	 * src/mdp/Makefile.am: Compiler warning fixes. CFLAGS -> AM_CFLAGS, YFLAGS -> AM_YFLAGS
	 * src/mdp/parse_err.c and parsr_err.h: Implicit declaration of ERR_enter was addressed
	 * src/testing/Makefile.am: Compiler warning fixes. INCLUDES -> AM_CPPFLAGS, CFLAGS -> AM_CFLAGS, LDFLAGS -> AM_LDFLAGS
     * ChangeLog: Added entries for the changes made here. Most changes are for cross-platform compatibility

### _2015-05-18_ 

     * mdp/scanner.l: Added support for scientific notation
     * mdp/Makefile.am: Added faster immediate reward handling
     * mdp/imm-reward.c: Added faster immediate reward handling
     * mdp/decision-tree.h: Added faster immediate reward handling
     * mdp/decision-tree.c: Added faster immediate reward handling

### _2015-05-17_

     * src/mdp/mdp.c: Fixed missing return value compiler error
     * src/index-list.c: Fixed missing return value compiler error
     * (many) Fixed numerous compiler warnings

### _2003-05-13_  

	* ChangeLog: adding per GNU build addition
	* configure.ac: adding per GNU build addition
	* Makefile.am: adding per GNU build addition
	* AUTHORS: adding per GNU build addition
	* NEWS: adding per GNU build addition
	* THANKS: adding per GNU build addition
	* src/Makefile.am: adding per GNU build addition
	* mdp/Makefile.am: adding per GNU build addition
	* lp-solve/Makefile.am: adding per GNU build addition
	* config/: adding per GNU build addition
	* config/bootstrap: adding per GNU build addition
	
	* src/: Added XML headers to all 'src' dir source files

	* src/mdp/scanner.l: Using parser.h instead of parser.tab.h
	* src/lp-solve/lex.l: Added includes and extern defs

### _2004-03-08_

	* src/finite-grid.c: fixed major logic bug in main function call
	* src/utils.c: added to support map-belief executable
	* src/map-belief-main.c: added to support map-belief executable
	* src/: refactored some of the belief and alpha file writing things

### _2004-03-16_ 

	* src/pg.[ch]: adding for explicit policy graph data structure
	* src/pg-isomorphism-main.c: adding utility program to check isomorphisms
	* src/params.c: added '-v' and '-version' flags

### _2004-04-18_ 

	* added the sort-alpha-list utility program
	* src/pomdp-solve.c: sorting alpha list before saving for -save_all
	* added the compare-alpha-lists utility program
	* src/utils.c: added more alpha vector stats to the map-belief utility
	* added the purge-alpha-list utility program
	* src/finite-grid.c: added alpha list purge to finite grid method

### _2004-04-19_

	* src/pomdp-solve.c: fixed context bug for 'exact' stopping criteria

### _2004-06-16_

	* src/pomdp-tools-main.c: added for consolidation of misc tools programs
	* src/associative-array.c: added for better option handling
	* src/associative-array.h: added for better option handling
	* src/command-line.c: added for better option handling
	* src/command-line.h: added for better option handling
	* src/config-file.c: added for better option handling
	* src/config-file.h: added for better option handling
	* src/pomdp-tools-options.c: added for better option handling
	* src/pomdp-tools-options.h: added for better option handling
	* src/program-options.c: added for better option handling
	* src/program-options.h: added for better option handling
	* src/compare-alpha-main.c: removed due to consolidation
	* src/map-belief-main.c: removed due to consolidation
	* src/pg-isomorphism-main.c: removed due to consolidation
	* src/pomdp-tools-main.c: removed due to consolidation
	* src/purge-alpha-main.c: removed due to consolidation
	* src/sort-alpha-main.c: removed due to consolidation

### _2004-06-17_ 

	* src/Makefile.am: Added object files to 'tools' binary list
	* src/main.c: altered main to deal with new option scheme
	* src/params.c: removed functionality that new option scheme handles
	* src/params.h: removed functionality that new option scheme handles
	* src/pomdp-solve.c: removed usage routine, new option scheme handles this
	* src/pomdp-tools-main.c: updated for more unique names
	* src/pomdp-tools-options.c: updated for more unique names
	* src/pomdp-tools-options.h: updated for more unique names
	* src/program-options.c: updated for more unique names
	* src/program-options.h: updated for more unique names

### _2004-07-01_

	* src/pomdp-tools-main.c: Added belief update loop tool
	* src/utils.c: Added belief update loop tool

### _2004-09-03_

	* examples/: Added example .POMDP and .prob files
	* examples/: Added example .POMDP and .prob files
	* src/common.c: Added shouldTerminateEarly() stub procedure
	* src/inc-prune.c: Added shouldTerminateEarly() call
	* src/two-pass.c: Added two shouldTerminateEarly() calls
	* src/witness.c: Added shouldTerminateEarly() call
	* src/scripts/generate-options/: Added script for auto-code generation

### _2004-10-01_

	* src/mcgs.c: Merged this into main pomdp-solve executable
	* src/finite-grid.c: Fixed bug in looping for initial belief list
	* src/finite-grid.c: Made default belief list size 10,000 (old=50,000)
	* src/finite-graid.c: Added option 'initial' for finite grid types

### _2004-10-05_

	* src/pg-eval.[ch]: Added for pomdp-tool use (future)
	* src/laspack-utils.[ch]: Added for laspack support (future)
	* src/laspack: added library source code for future use

### _2004-10-06_

	* src/mdp/scanner.l: Added '\r' as no-op character
	* src/command-line.h: Increased MAX_CMD_LINE_STRING_LEN to 1024

### _2004-10-08_

	* src/alpha.c: Redid isBetterValue to use GreaterThan macro 
	* src/global.h: Redid isBetterValue to use GreaterThan macro 
	* src/pomdp-solve.c: Added sorting before 'exact'  stopping criteria
	* src/pomdp.c: Redid isBetterValue to use GreaterThan macro 
	* src/pomdp.h: Removed spurious isBetterValue() function 
	* src/utils.c: Redid isBetterValue to use GreaterThan macro 
	* src/pomdp-solve-options.[ch]: Added new defaults

### _2004-10-09_

	* configure.ac: Added debug and dmalloc support 
	* src/Makefile.am: Added debug and dmalloc support 
	* src/mdp/Makefile.am: Added debug and dmalloc support 
	* src/lp-solve/Makefile.am: Added debug and dmalloc support 
	* src/xalloc.[ch]: Redid to support dmalloc

### _2004-10-31_

	* pg.[ch]: Merged policy-graph.[ch] into here
	* policy-graph.[ch]: Removed due to merge with pg.[ch]
	* pg.[ch]: Refactored so only one read and one write pg routine
	* pg-eval-main.c: changes to support being hooked up to pomdp-tools
	* pomdp-tools-main.c: Hooked up pg_eval tool
	* pomdp-tools-main.c: Added support for pg_relink tool
	* utils.[ch]: Added routines to support pg_relink tool
	* pomdp-tools-options.xml: Added 'pg_relink option
	* pomdp-solve-options.xml: Added 'save_penultimate' flag
	* params.[ch]: Added penultimate_filename to struct
	
### _2005-01-18_

	* util.c: Added tracking action in alpha compare

### _2005-01-25_

	* common.c: Added things to support belief-based alpah compare
	* pomdp-solve.c: Added case of finite grid stopping criteria
	* finite-grid.[ch]: Added special sopping critera function
	* utils.c: 

### _2005-02-01_

	* src/pomdp-fg-main.c: Beginnings of separate finite grid binary
	* src/index-list.[ch]: Maintains a list of integers
	* testing/Makefile.am: Unit test automake file
	* testing/main-test.c: Unit test driver program
	* testing/index-list-test.[ch]: Unit test for index-list.c
