
/*  A Bison parser, made from small.y
    by GNU Bison version 1.28  */

#define YYBISON 1  /* Identify Bison output.  */

#define	BEG	257
#define	END	258
#define	IF	259
#define	ELSE	260
#define	THEN	261
#define	WHILE	262
#define	DO	263
#define	REPEAT	264
#define	UNTIL	265
#define	READ	266
#define	WRITE	267
#define	FUNCTION	268
#define	ODD	269
#define	XOR	270
#define	BC	271
#define	GE	272
#define	LE	273
#define	GT	274
#define	LT	275
#define	EQ	276
#define	NE	277
#define	VAR	278
#define	CONST	279
#define	CALL	280
#define	RETURN	281
#define	IDENT	282
#define	NUMBER	283

#line 1 "small.y"

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define idTableMax 100
#define idLenMax 10
#define globalStackMax 2048
#define stackMax 2048
#define codeMax 200

enum object
{
    variable,
    constant,
    function,
};

struct tablestruct
{
    char name[idLenMax];
    enum object kind;
    int level;
    int adr;
    int size;
};

struct tablestruct localtable[idTableMax], globaltable[idTableMax];

enum fct {
    lit,     opr,     lod, 
    sto,     cal,     ini, 
    jmp,     jpc,     
};

struct instruction
{
	enum fct f;   /* 虚拟机代码指令 */
	int l;        /* 引用层与声明层的层次差 */
	int a;        /* 根据f的不同而不同 */
};
struct instruction code[codeMax];

int localtablePoint;
int globaltablePoint;
int level;
int codePoint;
int listswitch;
int startPoint;
int globalStackPoint;
int localStackPoint;

int returnReg;
int paramReg[10];
int paramPoint;

FILE* fin;      /* 输入源文件 */
FILE* ftable;	  /* 输出符号表 */
FILE* fcode;    /* 输出虚拟机代码 */
FILE* foutput;  /* 输出出错示意（如有错） */
FILE* fresult;  /* 输出执行结果 */
char fname[10];
int err;
extern int line;

int yyerror(char *s);
void init();
struct tablestruct* enter(char *name, enum object kind, int size);
struct tablestruct* position(char *name);
void gen(enum fct x, int y, int z);
void listall();
void listtable();
int main(void);


#line 78 "small.y"
typedef union
{
    char ident[10];
    int number;
} YYSTYPE;
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		128
#define	YYFLAG		-32768
#define	YYNTBASE	39

#define YYTRANSLATE(x) ((unsigned)(x) <= 283 ? yytranslate[x] : 71)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,    30,     2,     2,    37,
    38,    33,    31,    36,    32,     2,    34,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,    35,     2,
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
     2,     2,     2,     2,     2,     1,     3,     4,     5,     6,
     7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
    17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
    27,    28,    29
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     1,     4,     8,    12,    14,    16,    18,    19,    23,
    25,    28,    33,    34,    35,    46,    50,    52,    54,    56,
    58,    60,    62,    64,    66,    68,    70,    72,    75,    76,
    83,    84,    91,    97,   101,   104,   107,   113,   114,   117,
   118,   122,   124,   126,   127,   136,   142,   145,   147,   151,
   155,   159,   163,   167,   171,   173,   177,   181,   185,   189,
   193,   197,   200,   202,   204,   208,   210,   212
};

static const short yyrhs[] = {    -1,
    40,    41,     0,    41,    35,    44,     0,    41,    35,    45,
     0,    44,     0,    45,     0,    43,     0,     0,    43,    36,
    44,     0,    44,     0,    24,    69,     0,    25,    69,    17,
    29,     0,     0,     0,    14,    69,    46,    37,    42,    38,
    47,     3,    48,     4,     0,    48,    35,    49,     0,    49,
     0,    50,     0,    54,     0,    55,     0,    56,     0,    57,
     0,    44,     0,    58,     0,    63,     0,    65,     0,    66,
     0,    52,     4,     0,     0,    52,    70,    51,     6,    48,
     4,     0,     0,     5,    67,    70,    53,     7,    48,     0,
    10,    70,    48,    11,    67,     0,    69,    17,    67,     0,
    12,    69,     0,    13,    67,     0,    26,    69,    37,    59,
    38,     0,     0,    60,    61,     0,     0,    61,    36,    62,
     0,    62,     0,    67,     0,     0,     8,    70,    67,    70,
    64,     9,    48,     4,     0,     9,    70,    48,     8,    67,
     0,    27,    67,     0,    27,     0,    68,    20,    68,     0,
    68,    21,    68,     0,    68,    18,    68,     0,    68,    19,
    68,     0,    68,    22,    68,     0,    68,    23,    68,     0,
    68,     0,    68,    31,    68,     0,    68,    32,    68,     0,
    68,    33,    68,     0,    68,    34,    68,     0,    68,    30,
    68,     0,    68,    16,    68,     0,    15,    68,     0,    29,
     0,    69,     0,    37,    67,    38,     0,    58,     0,    28,
     0,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   100,   105,   113,   114,   115,   116,   119,   120,   123,   124,
   127,   144,   154,   168,   177,   185,   186,   189,   190,   191,
   192,   193,   194,   195,   196,   197,   198,   201,   205,   210,
   216,   220,   226,   232,   241,   251,   257,   266,   271,   274,
   277,   281,   287,   294,   298,   305,   312,   317,   323,   327,
   331,   335,   339,   343,   347,   350,   354,   358,   362,   366,
   370,   374,   378,   382,   388,   389,   395,   401
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","BEG","END",
"IF","ELSE","THEN","WHILE","DO","REPEAT","UNTIL","READ","WRITE","FUNCTION","ODD",
"XOR","BC","GE","LE","GT","LT","EQ","NE","VAR","CONST","CALL","RETURN","IDENT",
"NUMBER","'%'","'+'","'-'","'*'","'/'","';'","','","'('","')'","program","@1",
"block","init_sequence","init_list","init_stmt","function_stmt","@2","@3","stmt_sequence",
"statement","if_stmt","@4","if_stmt1","@5","repeat_stmt","assign_stmt","read_stmt",
"write_stmt","call_stmt","param_sequence","@6","param_list","param_stmt","while_stmt",
"@7","dowhile_stmt","return_stmt","exp","simple_exp","identifier","get_code_addr", NULL
};
#endif

static const short yyr1[] = {     0,
    40,    39,    41,    41,    41,    41,    42,    42,    43,    43,
    44,    44,    46,    47,    45,    48,    48,    49,    49,    49,
    49,    49,    49,    49,    49,    49,    49,    50,    51,    50,
    53,    52,    54,    55,    56,    57,    58,    60,    59,    59,
    61,    61,    62,    64,    63,    65,    66,    66,    67,    67,
    67,    67,    67,    67,    67,    68,    68,    68,    68,    68,
    68,    68,    68,    68,    68,    68,    69,    70
};

static const short yyr2[] = {     0,
     0,     2,     3,     3,     1,     1,     1,     0,     3,     1,
     2,     4,     0,     0,    10,     3,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     2,     0,     6,
     0,     6,     5,     3,     2,     2,     5,     0,     2,     0,
     3,     1,     1,     0,     8,     5,     2,     1,     3,     3,
     3,     3,     3,     3,     1,     3,     3,     3,     3,     3,
     3,     2,     1,     1,     3,     1,     1,     0
};

static const short yydefact[] = {     1,
     0,     0,     0,     0,     2,     5,     6,    67,    13,    11,
     0,     0,     0,     0,     3,     4,     8,    12,     0,     7,
    10,    14,     0,     0,     9,     0,     0,    68,    68,    68,
     0,     0,     0,    48,    23,     0,    17,    18,    68,    19,
    20,    21,    22,    24,    25,    26,    27,     0,     0,    63,
     0,    66,    68,    55,    64,     0,     0,     0,    35,    36,
     0,    47,    15,     0,    28,    29,     0,    62,     0,    31,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,    68,     0,     0,    38,    16,     0,    34,    65,
     0,    61,    51,    52,    49,    50,    53,    54,    60,    56,
    57,    58,    59,    44,     0,     0,     0,     0,     0,     0,
     0,    46,    33,    37,    39,    42,    43,     0,    32,     0,
     0,    30,     0,    41,    45,     0,     0,     0
};

static const short yydefgoto[] = {   126,
     1,     5,    19,    20,    35,     7,    13,    24,    36,    37,
    38,    88,    39,    91,    40,    41,    42,    43,    52,   107,
   108,   115,   116,    45,   111,    46,    47,   117,    54,    55,
    56
};

static const short yypact[] = {-32768,
    -3,    -5,    -5,    -5,    -8,-32768,-32768,-32768,-32768,-32768,
    15,    -3,   -11,    11,-32768,-32768,    -9,-32768,     7,    10,
-32768,-32768,    -9,    44,-32768,   101,    67,-32768,-32768,-32768,
    -5,    67,    -5,    67,-32768,     3,-32768,-32768,    46,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,    34,    67,-32768,
    67,-32768,-32768,   114,-32768,    67,   101,   101,-32768,-32768,
    17,-32768,-32768,   101,-32768,-32768,    67,-32768,    14,-32768,
    67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
    67,    67,-32768,     9,    -7,    21,-32768,    54,-32768,-32768,
    62,-32768,    68,    68,    68,    68,    68,    68,    33,    87,
    87,    45,    45,-32768,    67,    67,    47,    67,   101,   101,
    74,-32768,-32768,-32768,    52,-32768,-32768,     4,    55,   101,
    67,-32768,     8,-32768,-32768,    89,    94,-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,-32768,-32768,    13,    93,-32768,-32768,   -52,    48,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   -23,-32768,
-32768,-32768,    -6,-32768,-32768,-32768,-32768,   -14,    -1,    -2,
   -20
};


#define	YYLAST		148


static const short yytable[] = {     9,
    10,    11,    44,   106,    84,    85,    63,   122,    57,    58,
     2,   125,    53,     6,     3,     4,   105,    60,    66,    62,
     3,     4,     8,    48,    15,    17,    12,    64,    59,    21,
    61,    14,    70,    44,    44,    25,    69,    64,    64,    18,
    44,    83,    64,    64,    22,    23,    26,    68,    71,    65,
    67,    90,    89,    86,    48,    48,   118,   119,   -40,   109,
    71,    48,   104,    79,    80,    81,    82,   123,   110,    92,
    93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
   103,    49,   120,    71,   114,    44,    44,   121,   127,    64,
   112,   113,    33,   128,     8,    50,    44,    78,    79,    80,
    81,    82,    71,    51,    16,    27,    48,    48,    28,    29,
    30,    87,    31,    32,   124,     0,     0,    48,     0,    81,
    82,     0,     0,     0,     3,     4,    33,    34,     8,    71,
     0,    72,    73,    74,    75,    76,    77,     0,     0,     0,
     0,     0,     0,    78,    79,    80,    81,    82
};

static const short yycheck[] = {     2,
     3,     4,    26,    11,    57,    58,     4,     4,    29,    30,
    14,     4,    27,     1,    24,    25,     8,    32,    39,    34,
    24,    25,    28,    26,    12,    37,    35,    35,    31,    17,
    33,    17,    53,    57,    58,    23,    51,    35,    35,    29,
    64,    56,    35,    35,    38,    36,     3,    49,    16,     4,
    17,    38,    67,    37,    57,    58,   109,   110,    38,     6,
    16,    64,    83,    31,    32,    33,    34,   120,     7,    71,
    72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
    82,    15,     9,    16,    38,   109,   110,    36,     0,    35,
   105,   106,    26,     0,    28,    29,   120,    30,    31,    32,
    33,    34,    16,    37,    12,     5,   109,   110,     8,     9,
    10,    64,    12,    13,   121,    -1,    -1,   120,    -1,    33,
    34,    -1,    -1,    -1,    24,    25,    26,    27,    28,    16,
    -1,    18,    19,    20,    21,    22,    23,    -1,    -1,    -1,
    -1,    -1,    -1,    30,    31,    32,    33,    34
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "bison.simple"

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
 #pragma alloca
#else /* not MSDOS, __TURBOC__, or _AIX */
#ifdef __hpux
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca ();
#endif /* not __cplusplus */
#endif /* __hpux */
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#endif /* alloca not defined.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
int yyparse (void);
#endif

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(FROM,TO,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (from, to, count)
     char *from;
     char *to;
     int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *from, char *to, int count)
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 192 "bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#else
#define YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#endif

int
yyparse(YYPARSE_PARAM)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) alloca (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss1, (char *)yyss, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) alloca (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs1, (char *)yyvs, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls1, (char *)yyls, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 1:
#line 101 "small.y"
{
           gen(jmp, 0, 0);
       ;
    break;}
case 2:
#line 105 "small.y"
{
           if(startPoint == 0) yyerror("Cannot find main");
           code[0].a = codePoint;
           gen(cal, 0, startPoint);
           gen(jmp, 0, 0);
       ;
    break;}
case 11:
#line 128 "small.y"
{
             struct tablestruct* pos = position(yyvsp[0].ident);
             if(pos && pos -> level == level) yyerror("Redeclaration");
             pos = enter(yyvsp[0].ident, variable, 1);

             if(level == 0)
             {
                 pos -> adr = globalStackPoint++;
             }
             else
             {
                 pos -> adr = localStackPoint++;
                 gen(ini, 0, 1);
             }

         ;
    break;}
case 12:
#line 145 "small.y"
{
             struct tablestruct* pos = position(yyvsp[-2].ident);
             if(pos && pos -> level == level) yyerror("Redeclaration");
             pos = enter(yyvsp[-2].ident, constant, 1);
             pos -> adr = localStackPoint++;
             gen(ini, 0, 1);
         ;
    break;}
case 13:
#line 155 "small.y"
{
                 struct tablestruct* pos = position(yyvsp[0].ident);
                 if(pos && pos -> level == level) yyerror("Redeclaration");
                 pos = enter(yyvsp[0].ident, function, 0);
                 pos -> adr = codePoint;
                 if(strcmp("main", pos->name) == 0)
                 {
                     startPoint = codePoint;
                 }
                 gen(ini, 0, 2);
                 level++;
                 localStackPoint = 2;
             ;
    break;}
case 14:
#line 169 "small.y"
{
                 struct tablestruct* pos = position(yyvsp[-4].ident);
                 pos -> size = localtablePoint;
                 
                 //listall();
                // listtable();
                 
             ;
    break;}
case 15:
#line 178 "small.y"
{
                 level--;
                 localtablePoint = 0;
                 gen(opr, 0, 0);
             ;
    break;}
case 28:
#line 202 "small.y"
{
           code[yyvsp[-1].number].a = codePoint;
       ;
    break;}
case 29:
#line 206 "small.y"
{
           gen(jmp, 0, 0);
           code[yyvsp[-1].number].a = codePoint;
       ;
    break;}
case 30:
#line 211 "small.y"
{
           code[yyvsp[-4].number].a = codePoint;
       ;
    break;}
case 31:
#line 217 "small.y"
{
            gen(jpc, 0, 0);
        ;
    break;}
case 32:
#line 221 "small.y"
{
            yyval.number = yyvsp[-3].number;
        ;
    break;}
case 33:
#line 227 "small.y"
{
               gen(jpc, 0, yyvsp[-3].number);
           ;
    break;}
case 34:
#line 233 "small.y"
{
               struct tablestruct* pos = position(yyvsp[-2].ident);
               if(pos == NULL) yyerror("Undifined variable");
               if(pos && pos -> kind != variable) yyerror("Identifier with wrong kind");
               gen(sto, pos->level, pos->adr);
           ;
    break;}
case 35:
#line 242 "small.y"
{
             struct tablestruct* pos = position(yyvsp[0].ident);
             if(pos == NULL) yyerror("Undifined variable");
             if(pos && pos -> kind != variable) yyerror("Identifier with wrong kind");
             gen(opr, 0, 16);
             gen(sto, pos->level, pos->adr);
         ;
    break;}
case 36:
#line 252 "small.y"
{
              gen(opr, 0, 14);
          ;
    break;}
case 37:
#line 258 "small.y"
{
             struct tablestruct* pos = position(yyvsp[-3].ident);
             if(pos == NULL || pos && pos -> kind != function) yyerror("Undifined function");
             if(pos -> size != yyvsp[-1].number) yyerror("Param with wrong number");
             gen(cal, yyvsp[-1].number, pos->adr);
         ;
    break;}
case 38:
#line 267 "small.y"
{
                  paramPoint = 0;
              ;
    break;}
case 39:
#line 271 "small.y"
{
                  yyval.number = yyvsp[0].number;
              ;
    break;}
case 41:
#line 278 "small.y"
{
              yyval.number = yyvsp[-2].number + 1;
          ;
    break;}
case 42:
#line 282 "small.y"
{
              yyval.number = 1;
          ;
    break;}
case 43:
#line 288 "small.y"
{
              gen(opr, paramPoint++, 19);
          ;
    break;}
case 44:
#line 295 "small.y"
{
              gen(jpc, 0, 0);
          ;
    break;}
case 45:
#line 299 "small.y"
{
              gen(jmp, 0, yyvsp[-6].number);
              code[yyvsp[-4].number].a = codePoint;
          ;
    break;}
case 46:
#line 306 "small.y"
{
                gen(jpc, 0, codePoint+1);
                gen(jmp, 0, yyvsp[-3].number);
            ;
    break;}
case 47:
#line 313 "small.y"
{
               gen(opr, 0, 17);
               gen(opr, 0, 0);
           ;
    break;}
case 48:
#line 318 "small.y"
{
               gen(opr, 0, 0);
           ;
    break;}
case 49:
#line 324 "small.y"
{
       gen(opr, 0, 12);
   ;
    break;}
case 50:
#line 328 "small.y"
{
       gen(opr, 0, 10);
   ;
    break;}
case 51:
#line 332 "small.y"
{
       gen(opr, 0, 11);
   ;
    break;}
case 52:
#line 336 "small.y"
{
       gen(opr, 0, 13);
   ;
    break;}
case 53:
#line 340 "small.y"
{
       gen(opr, 0, 8);
   ;
    break;}
case 54:
#line 344 "small.y"
{
       gen(opr, 0, 9);
   ;
    break;}
case 56:
#line 351 "small.y"
{
              gen(opr, 0, 2);
          ;
    break;}
case 57:
#line 355 "small.y"
{
              gen(opr, 0, 3);
          ;
    break;}
case 58:
#line 359 "small.y"
{
              gen(opr, 0, 4);
          ;
    break;}
case 59:
#line 363 "small.y"
{
              gen(opr, 0, 5);
          ;
    break;}
case 60:
#line 367 "small.y"
{
              gen(opr, 0, 21);
          ;
    break;}
case 61:
#line 371 "small.y"
{
              gen(opr, 0, 22);
          ;
    break;}
case 62:
#line 375 "small.y"
{
              gen(opr, 0, 23);
          ;
    break;}
case 63:
#line 379 "small.y"
{
              gen(lit, 0, yyvsp[0].number);
          ;
    break;}
case 64:
#line 383 "small.y"
{
              struct tablestruct* pos = position(yyvsp[0].ident);
              if(pos == NULL || pos && pos -> kind == function) yyerror("Undifined variable");
              gen(lod, pos -> level, pos -> adr);
          ;
    break;}
case 66:
#line 390 "small.y"
{
              gen(opr, 0, 18);
          ;
    break;}
case 67:
#line 396 "small.y"
{
              strcpy(yyval.ident, yyvsp[0].ident);
          ;
    break;}
case 68:
#line 402 "small.y"
{
                yyval.number = codePoint;
              ;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 487 "bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}
#line 407 "small.y"

int yyerror(char *s)
{
	err = err + 1;
    printf("%s in line %d\n", s, line);
	fprintf(foutput, "%s in line %d\n", s, line);
	return 0;
}

/* 初始化 */
void init()
{
	localtablePoint = 0;
    globaltablePoint = 0;
    level = 0;
    codePoint = 0;
    err = 0;
    startPoint = 0;
    globalStackPoint = 0;
    localStackPoint = 0;
    returnReg = 0;
    paramPoint = 0;
}

struct tablestruct* enter(char *name, enum object kind, int size)
{
    if(level == 0)
    {
        strcpy(globaltable[globaltablePoint].name, name);
        globaltable[globaltablePoint].kind = kind;
        globaltable[globaltablePoint].level = level;
        globaltable[globaltablePoint].size = size;
        globaltablePoint++;
        return &globaltable[globaltablePoint-1];
    }
    else
    {
        strcpy(localtable[localtablePoint].name, name);
        localtable[localtablePoint].kind = kind;
        localtable[localtablePoint].level = level;
        localtable[localtablePoint].size = size;
        localtablePoint++;
        return &localtable[localtablePoint-1];
    }
}

struct tablestruct* position(char *name)
{
    int i = 0;
	if(level != 0)
    {
        i = localtablePoint - 1;
        while(i >= 0)
        {
            if(strcmp(name, localtable[i].name) == 0) return &localtable[i];
            i--;
        }
    }
    i = globaltablePoint - 1;
    while(i >= 0)
    {
        if(strcmp(name, globaltable[i].name) == 0) return &globaltable[i];
        i--;
    }
    return NULL;
}

void gen(enum fct x, int y, int z)
{
	if (codePoint >= codeMax)
	{
		printf("Program is too long!\n");	/* 生成的虚拟机代码程序过长 */
		exit(1);
	}
	if ( z >= stackMax)
	{
		printf("Displacement address is too big!\n");	/* 地址偏移越界 */
		exit(1);
	}
	code[codePoint].f = x;
	code[codePoint].l = y;
	code[codePoint].a = z;
	codePoint++;
}

void listall()
{
	int i;
	char name[][5]=
	{
		{"lit"},{"opr"},{"lod"},{"sto"},{"cal"},{"int"},{"jmp"},{"jpc"},
	};
    if (listswitch)
	{
		for (i = 0; i < codePoint; i++)
		{
			printf("%d %s %d %d\n", i, name[code[i].f], code[i].l, code[i].a);
			fprintf(fcode,"%d %s %d %d\n", i, name[code[i].f], code[i].l, code[i].a);
			
		}
    }
}

void listtable()
{
    int i = 0;
    printf("-----------global table-----------\n");
    while(i < globaltablePoint)
    {
        printf("name = %s, level = %d, adr = %d, size = %d\n", globaltable[i].name, globaltable[i].level, globaltable[i].adr, globaltable[i].size);
        i++;
    }
    printf("-----------local table-----------\n");
    i  = 0;
    while(i < localtablePoint)
    {
        printf("name = %s, level = %d, adr = %d, size= %d\n", localtable[i].name, localtable[i].level, localtable[i].adr, localtable[i].size);
        i++;
    }

}

void interpret()
{
	int p = 0; /* 指令指针 */
	int b = 0; /* 指令基址 */
	int t = 0; /* 栈顶指针 */
	struct instruction i;	/* 存放当前指令 */
	int s[stackMax];	/* 栈 */
    int globals[globalStackMax];

	printf("Start small\n");
	fprintf(fresult,"Start small\n");
	s[0] = 0; /* s[0]不用 */
	do {
	    i = code[p];	/* 读当前指令 */
        // printf("------line %d----------\n", p);
		p = p + 1;
		switch (i.f)
		{
			case lit:	/* 将常量a的值取到栈顶 */
				t = t + 1;
				s[t] = i.a;				
				break;
			case opr:	/* 数学、逻辑运算 */
				switch (i.a)
				{
					case 0:  /* 函数调用结束后返回 */
						t = b - 1;
						p = s[t + 2];
						b = s[t + 1];
						break;
					case 1: /* 栈顶元素取反 */
						s[t] = - s[t];
						break;
					case 2: /* 次栈顶项加上栈顶项，退两个栈元素，相加值进栈 */
						t = t - 1;
						s[t] = s[t] + s[t + 1];
						break;
					case 3:/* 次栈顶项减去栈顶项 */
						t = t - 1;
						s[t] = s[t] - s[t + 1];
						break;
					case 4:/* 次栈顶项乘以栈顶项 */
						t = t - 1;
						s[t] = s[t] * s[t + 1];
						break;
					case 5:/* 次栈顶项除以栈顶项 */
						t = t - 1;
						s[t] = s[t] / s[t + 1];
						break;
					case 6:/* 栈顶元素的奇偶判断 */
						s[t] = s[t] % 2;
						break;
					case 8:/* 次栈顶项与栈顶项是否相等 */
						t = t - 1;
						s[t] = (s[t] == s[t + 1]);
						break;
					case 9:/* 次栈顶项与栈顶项是否不等 */
						t = t - 1;
						s[t] = (s[t] != s[t + 1]);
						break;
					case 10:/* 次栈顶项是否小于栈顶项 */
						t = t - 1;
						s[t] = (s[t] < s[t + 1]);
						break;
					case 11:/* 次栈顶项是否大于等于栈顶项 */
						t = t - 1;
						s[t] = (s[t] >= s[t + 1]);
						break;
					case 12:/* 次栈顶项是否大于栈顶项 */
						t = t - 1;
						s[t] = (s[t] > s[t + 1]);
						break;
					case 13: /* 次栈顶项是否小于等于栈顶项 */
						t = t - 1;
						s[t] = (s[t] <= s[t + 1]);
						break;
					case 14:/* 栈顶值输出 */
						printf("%d\n", s[t]);
						fprintf(fresult, "%d", s[t]);
						t = t - 1;
						break;
					case 15:/* 输出换行符 */
						printf("\n");
						fprintf(fresult,"\n");
						break;
					case 16:/* 读入一个输入置于栈顶 */
						t = t + 1;
						printf("?");
						fprintf(fresult, "?");
						scanf("%d", &(s[t]));
						fprintf(fresult, "%d\n", s[t]);						
						break;
                    case 17:
                        returnReg = s[t];
                        t--;
                        break;
                    case 18:
                        t++;
                        s[t] = returnReg;
                        break;
                    case 19:
                        paramReg[i.l] = s[t];
                        t--;
                        break;
                    case 21:
                        t = t - 1;
						s[t] = s[t] % s[t + 1];
                        break;
                    case 22:
                        t = t - 1;
						s[t] = s[t] ^ s[t + 1];
                        break;
                    case 23:
                        s[t] = s[t] % 2 == 1 ? 1 : 0;
						break;
				}
				break;
			case lod:	/* 取相对当前过程的数据基地址为a的内存的值到栈顶 */
				t = t + 1;
				s[t] = i.l == 0 ? globals[i.a] : s[b + i.a];
				break;
			case sto:	/* 栈顶的值存到相对当前过程的数据基地址为a的内存 */
                if(i.l == 0)
                {
                    globals[i.a] = s[t];
                }
                else
                {
                    s[b + i.a] = s[t];
                }
				t = t - 1;
				break;
			case cal:	/* 调用子过程 */
				s[t + 1] = b;	/* 将本过程基地址入栈，即建立动态链 */
				s[t + 2] = p;	/* 将当前指令指针入栈，即保存返回地址 */
				b = t + 1;	/* 改变基地址指针值为新过程的基地址 */
				p = i.a;	/* 跳转 */
                int count = 0;
                for(; count < i.l; count++)
                {
                    s[t+3+count] = paramReg[count];
                }
				break;
			case ini:	/* 在数据栈中为被调用的过程开辟a个单元的数据区 */
				t = t + i.a;	
				break;
			case jmp:	/* 直接跳转 */
				p = i.a;
				break;
			case jpc:	/* 条件跳转 */
				if (s[t] == 0) 
					p = i.a;
				t = t - 1;
				break;
		}
        
        // int count = 0;
        // for(; count <= t; count++)
        // {
        //     printf("%d %d\n", count, s[count]);
        // }
	} while (p != 0);
	printf("End small\n");
	fprintf(fresult,"End small\n");
}


int main(void)
{
	printf("Input pl/0 file?   ");
	scanf("%s", fname);		/* 输入文件名 */

	if ((fin = fopen(fname, "r")) == NULL)
	{
		printf("Can't open the input file!\n");
		exit(1);
	}	
	if ((foutput = fopen("foutput.txt", "w")) == NULL)
  {
		printf("Can't open the output file!\n");
		exit(1);
	}
	if ((ftable = fopen("ftable.txt", "w")) == NULL)
	{
		printf("Can't open ftable.txt file!\n");
		exit(1);
	}
	
	printf("List object codes?(Y/N)");	/* 是否输出虚拟机代码 */
	scanf("%s", fname);
	listswitch = (fname[0]=='y' || fname[0]=='Y');
	
	redirectInput(fin);		
	init();
    yyparse();
	if(err == 0)
	{
		printf("\n===Parsing success!===\n");
		fprintf(foutput, "\n===Parsing success!===\n");
		if ((fcode = fopen("fcode.txt", "w")) == NULL)
		{
			printf("Can't open fcode.txt file!\n");
			exit(1);
		}		

		if ((fresult = fopen("fresult.txt", "w")) == NULL)
		{
			printf("Can't open fresult.txt file!\n");
			exit(1);
		}
		
		listall();  /* 输出所有代码 */
		fclose(fcode);
		
		interpret();	/* 调用解释执行程序 */        	
		fclose(fresult);
	}
  else
	{
		printf("%d errors in PL/0 program\n", err);
		fprintf(foutput, "%d errors in PL/0 program\n", err);
		
	}
	
	fclose(ftable);
    fclose(foutput);
	fclose(fin);
	return 0;
}