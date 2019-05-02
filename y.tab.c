/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

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
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     OR = 258,
     AND = 259,
     LT = 260,
     GT = 261,
     EQ = 262,
     NE = 263,
     LE = 264,
     GE = 265,
     PLUS = 266,
     MINUS = 267,
     STAR = 268,
     DIV = 269,
     MOD = 270,
     NOT = 271,
     INTLIT = 272,
     REALLIT = 273,
     ID = 274,
     RESERVED = 275,
     LPAR = 276,
     RPAR = 277,
     SEMICOLON = 278,
     RSQ = 279,
     FOR = 280,
     CMDARGS = 281,
     BLANKID = 282,
     FUNC = 283,
     RBRACE = 284,
     LSQ = 285,
     ASSIGN = 286,
     IF = 287,
     RETURN = 288,
     LBRACE = 289,
     PARSEINT = 290,
     COMMA = 291,
     STRLIT = 292,
     ELSE = 293,
     PRINT = 294,
     FLOAT32 = 295,
     STRING = 296,
     BOOL = 297,
     INT = 298,
     PACKAGE = 299,
     VAR = 300,
     IFELSE = 301
   };
#endif
/* Tokens.  */
#define OR 258
#define AND 259
#define LT 260
#define GT 261
#define EQ 262
#define NE 263
#define LE 264
#define GE 265
#define PLUS 266
#define MINUS 267
#define STAR 268
#define DIV 269
#define MOD 270
#define NOT 271
#define INTLIT 272
#define REALLIT 273
#define ID 274
#define RESERVED 275
#define LPAR 276
#define RPAR 277
#define SEMICOLON 278
#define RSQ 279
#define FOR 280
#define CMDARGS 281
#define BLANKID 282
#define FUNC 283
#define RBRACE 284
#define LSQ 285
#define ASSIGN 286
#define IF 287
#define RETURN 288
#define LBRACE 289
#define PARSEINT 290
#define COMMA 291
#define STRLIT 292
#define ELSE 293
#define PRINT 294
#define FLOAT32 295
#define STRING 296
#define BOOL 297
#define INT 298
#define PACKAGE 299
#define VAR 300
#define IFELSE 301




/* Copy the first part of user declarations.  */
#line 1 "gocompiler.y"

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "tabelas.h"
    #define YYDEBUG 1
    extern int yydebug;
    extern int numcolunas;
    extern int yylineno;
    extern int flagString;
    extern char s[500];
    extern char* yytext;
    int yylex(void);
    void yyerror (char *st);
    int flagLex=0;
    int flagArvore=0;
    int flagErro=0;
    int flagSemantica=0;
    
    int imprimeTralha(nodeDefault *raiz,int depth);
    int limpaTralha(nodeDefault *raiz);
    nodeDefault * criaNoPai(nodeType tipo, char *str);
    nodeDefault * adicionaFilho(nodeDefault * pai,nodeType tipo, char *str);
    nodeDefault * adicionaIrmao(nodeDefault * atual,nodeType tipo, char *str);
    int imprimeTralha(nodeDefault *raiz,int depth);
    nodeDefault * adicionaIrmao2(nodeDefault * atual,nodeDefault *novo);
    nodeDefault * adicionaFilho2(nodeDefault * pai,nodeDefault *novo);
    nodeDefault * adicionaIrmaoInicio(nodeDefault * atual,nodeDefault *novo);
    nodeDefault * juntarCenas(nodeDefault * alvo,char* string);
    char * juntaStrings(char *tipo,char *valor, char *parenteses);
    int contaIrmao(nodeDefault * alvo);
    int criaTabelas(nodeDefault *raiz);
    int anota(nodeDefault *raiz);
    void checkaTerminais(nodeDefault *no,int local,int flag);
    int recursiva(nodeDefault *no,int local);
    void teste1(nodeDefault *raiz);
    char* percorreTabela(char* str,int local);
    /* Inicializa tabela de símbolos global */
    elemento_tabelag *tg = NULL;



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 42 "gocompiler.y"
{
    char cval;
    int intval;
    char *string;
    double d;
    struct node *ponteiro;
}
/* Line 193 of yacc.c.  */
#line 238 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 251 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   349

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  18
/* YYNRULES -- Number of rules.  */
#define YYNRULES  70
/* YYNRULES -- Number of states.  */
#define YYNSTATES  150

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   301

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
      45,    46
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     8,    12,    16,    17,    20,    26,    30,
      34,    35,    37,    39,    41,    43,    49,    56,    64,    71,
      75,    80,    81,    85,    88,    92,    96,    97,   102,   107,
     109,   111,   113,   115,   118,   124,   129,   133,   139,   149,
     153,   157,   158,   170,   179,   184,   188,   194,   198,   199,
     203,   205,   207,   209,   213,   217,   221,   225,   229,   233,
     237,   241,   245,   249,   253,   257,   261,   264,   267,   270,
     272
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      48,     0,    -1,    44,    19,    23,    49,    -1,    49,    50,
      23,    -1,    49,    54,    23,    -1,    -1,    45,    51,    -1,
      45,    21,    51,    23,    22,    -1,    19,    52,    53,    -1,
      52,    36,    19,    -1,    -1,    43,    -1,    42,    -1,    41,
      -1,    40,    -1,    28,    19,    21,    22,    57,    -1,    28,
      19,    21,    55,    22,    57,    -1,    28,    19,    21,    55,
      22,    53,    57,    -1,    28,    19,    21,    22,    53,    57,
      -1,    19,    53,    56,    -1,    56,    36,    19,    53,    -1,
      -1,    34,    58,    29,    -1,    58,    23,    -1,    58,    50,
      23,    -1,    58,    59,    23,    -1,    -1,    39,    21,    64,
      22,    -1,    39,    21,    37,    22,    -1,     1,    -1,    62,
      -1,    61,    -1,    33,    -1,    33,    64,    -1,    25,    64,
      34,    60,    29,    -1,    25,    34,    60,    29,    -1,    19,
      31,    64,    -1,    32,    64,    34,    60,    29,    -1,    32,
      64,    34,    60,    29,    38,    34,    60,    29,    -1,    34,
      60,    29,    -1,    60,    59,    23,    -1,    -1,    19,    36,
      27,    31,    35,    21,    26,    30,    64,    24,    22,    -1,
      19,    36,    27,    31,    35,    21,     1,    22,    -1,    19,
      21,     1,    22,    -1,    19,    21,    22,    -1,    19,    21,
      64,    63,    22,    -1,    63,    36,    64,    -1,    -1,    64,
       3,    64,    -1,    19,    -1,    18,    -1,    17,    -1,    64,
       4,    64,    -1,    64,    11,    64,    -1,    64,     5,    64,
      -1,    64,    12,    64,    -1,    64,     6,    64,    -1,    64,
      15,    64,    -1,    64,    14,    64,    -1,    64,    10,    64,
      -1,    64,    13,    64,    -1,    64,     7,    64,    -1,    64,
       8,    64,    -1,    64,     9,    64,    -1,    21,    64,    22,
      -1,    12,    64,    -1,    11,    64,    -1,    16,    64,    -1,
      62,    -1,    21,     1,    22,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   125,   125,   158,   168,   180,   183,   186,   191,   206,
     215,   218,   219,   220,   221,   224,   237,   250,   267,   286,
     312,   331,   334,   346,   354,   363,   372,   375,   376,   377,
     378,   379,   380,   381,   382,   401,   416,   421,   440,   487,
     504,   512,   515,   520,   523,   524,   525,   543,   544,   547,
     548,   549,   550,   551,   552,   553,   554,   555,   556,   557,
     558,   559,   560,   561,   562,   563,   564,   565,   566,   567,
     568
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "OR", "AND", "LT", "GT", "EQ", "NE",
  "LE", "GE", "PLUS", "MINUS", "STAR", "DIV", "MOD", "NOT", "INTLIT",
  "REALLIT", "ID", "RESERVED", "LPAR", "RPAR", "SEMICOLON", "RSQ", "FOR",
  "CMDARGS", "BLANKID", "FUNC", "RBRACE", "LSQ", "ASSIGN", "IF", "RETURN",
  "LBRACE", "PARSEINT", "COMMA", "STRLIT", "ELSE", "PRINT", "FLOAT32",
  "STRING", "BOOL", "INT", "PACKAGE", "VAR", "IFELSE", "$accept",
  "Program", "Declarations", "VarDeclaration", "VarSpec", "teste", "Type",
  "FuncDeclaration", "Parameters", "AuxParameters", "FuncBody",
  "VarsAndStatements", "Statement", "AuxStatement1", "ParseArgs",
  "FuncInvocation", "AuxFuncInvocation", "Expr", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    47,    48,    49,    49,    49,    50,    50,    51,    52,
      52,    53,    53,    53,    53,    54,    54,    54,    54,    55,
      56,    56,    57,    58,    58,    58,    58,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    59,
      60,    60,    61,    61,    62,    62,    62,    63,    63,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     4,     3,     3,     0,     2,     5,     3,     3,
       0,     1,     1,     1,     1,     5,     6,     7,     6,     3,
       4,     0,     3,     2,     3,     3,     0,     4,     4,     1,
       1,     1,     1,     2,     5,     4,     3,     5,     9,     3,
       3,     0,    11,     8,     4,     3,     5,     3,     0,     3,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     2,     1,
       3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     5,     2,     0,     0,     0,
       0,     0,    10,     0,     6,     3,     4,     0,     0,     0,
       0,     0,     0,     0,    14,    13,    12,    11,     8,     0,
      21,    26,     0,    15,     0,     9,     7,    19,     0,    18,
       0,    16,     0,    29,     0,    23,     0,    22,     0,    32,
      41,     0,     0,     0,    31,    30,    17,     0,     0,     0,
       0,     0,     0,     0,    52,    51,    50,     0,    41,    69,
       0,     0,    33,     0,     0,    24,    25,    20,     0,    45,
      48,    36,     0,    67,    66,    68,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    41,    41,    39,     0,     0,     0,    44,     0,
       0,    70,    65,    35,    49,    53,    55,    57,    62,    63,
      64,    60,    54,    56,    61,    59,    58,     0,     0,    40,
      28,    27,    46,     0,     0,    34,    37,    47,     0,     0,
       0,     0,    41,    43,     0,     0,     0,    38,     0,    42
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     6,     9,    14,    18,    28,    10,    22,    37,
      33,    38,   105,    73,    54,    69,   109,    70
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -67
static const yytype_int16 yypact[] =
{
     -30,     0,    20,     6,   -67,   -67,   -27,     9,    51,    28,
      29,    45,   -67,    50,   -67,   -67,   -67,   -11,   119,    52,
       1,     5,    56,    55,   -67,   -67,   -67,   -67,   -67,    57,
     -67,   -67,    49,   -67,     5,   -67,   -67,    58,    48,   -67,
      49,   -67,    65,   -67,   -15,   -67,   193,   -67,   204,   204,
     -67,    70,    72,    75,   -67,   -67,   -67,     1,   240,   204,
      61,   204,   204,   204,   -67,   -67,    83,   252,   -67,   -67,
     161,   174,   311,    67,   180,   -67,   -67,   -67,    88,   -67,
     311,   311,    74,   -67,   -67,   -67,    89,   271,    84,   204,
     204,   204,   204,   204,   204,   204,   204,   204,   204,   204,
     204,   204,   -67,   -67,   -67,    92,    90,   291,   -67,   -12,
      86,   -67,   -67,   -67,   323,   334,   231,   231,   231,   231,
     231,   231,    19,    19,   -67,   -67,   -67,   101,   113,   -67,
     -67,   -67,   -67,   204,    98,   -67,    91,   311,     4,    93,
     100,    94,   -67,   -67,   204,   124,   225,   -67,   106,   -67
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -67,   -67,   -67,    99,   118,   -67,   -17,   -67,   -67,   -67,
     -25,   -67,   103,   -66,   -67,   -38,   -67,   -36
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      55,     7,    88,    30,    32,   140,    58,    39,    20,    41,
     132,    21,    71,    72,     1,    56,    59,    40,     8,     3,
       4,    60,    80,    81,   133,    83,    84,    85,    11,     5,
     141,    87,    99,   100,   101,    55,   127,   128,   107,    31,
      77,    24,    25,    26,    27,    24,    25,    26,    27,    43,
      55,    15,    16,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,    17,    44,    43,    12,
      12,    45,    13,    46,    35,    29,   145,    47,    34,    36,
      48,    49,    50,    31,    57,    43,    44,    51,    82,    55,
      55,    74,    46,     8,    42,    75,   104,   137,    76,    48,
      49,    50,    43,    44,    58,   110,    51,    55,   146,    46,
     108,   111,   130,   113,    43,   129,    48,    49,    50,   138,
      44,   134,   143,    51,   144,    43,    46,   142,   149,   139,
     135,    19,    44,    48,    49,    50,     0,    52,    46,     0,
      51,    53,   136,    44,     0,    48,    49,    50,     0,    46,
       0,     0,    51,   147,     0,    23,    48,    49,    50,    24,
      25,    26,    27,    51,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
       0,    61,    62,     0,     0,   102,    63,    64,    65,    66,
       0,    67,     0,     0,    61,    62,     0,     0,   103,    63,
      64,    65,    66,     0,    67,    61,    62,   106,     0,     0,
      63,    64,    65,    66,     0,    67,     0,    68,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,    78,    97,    98,    99,   100,   101,     0,     0,   148,
       0,    61,    62,    86,     0,     0,    63,    64,    65,    66,
       0,    67,    79,    61,    62,     0,     0,     0,    63,    64,
      65,    66,     0,    67,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,     0,     0,     0,
       0,     0,     0,   112,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,     0,     0,     0,
       0,     0,     0,   131,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101
};

static const yytype_int16 yycheck[] =
{
      38,    28,    68,    20,    21,     1,    21,    32,    19,    34,
      22,    22,    48,    49,    44,    40,    31,    34,    45,    19,
       0,    36,    58,    59,    36,    61,    62,    63,    19,    23,
      26,    67,    13,    14,    15,    73,   102,   103,    74,    34,
      57,    40,    41,    42,    43,    40,    41,    42,    43,     1,
      88,    23,    23,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,    21,    19,     1,    19,
      19,    23,    21,    25,    19,    23,   142,    29,    22,    22,
      32,    33,    34,    34,    19,     1,    19,    39,    27,   127,
     128,    21,    25,    45,    36,    23,    29,   133,    23,    32,
      33,    34,     1,    19,    21,    31,    39,   145,   144,    25,
      22,    22,    22,    29,     1,    23,    32,    33,    34,    21,
      19,    35,    22,    39,    30,     1,    25,    34,    22,    38,
      29,    13,    19,    32,    33,    34,    -1,    38,    25,    -1,
      39,    38,    29,    19,    -1,    32,    33,    34,    -1,    25,
      -1,    -1,    39,    29,    -1,    36,    32,    33,    34,    40,
      41,    42,    43,    39,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      -1,    11,    12,    -1,    -1,    34,    16,    17,    18,    19,
      -1,    21,    -1,    -1,    11,    12,    -1,    -1,    34,    16,
      17,    18,    19,    -1,    21,    11,    12,    37,    -1,    -1,
      16,    17,    18,    19,    -1,    21,    -1,    34,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,     1,    11,    12,    13,    14,    15,    -1,    -1,    24,
      -1,    11,    12,     1,    -1,    -1,    16,    17,    18,    19,
      -1,    21,    22,    11,    12,    -1,    -1,    -1,    16,    17,
      18,    19,    -1,    21,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    -1,    -1,    -1,
      -1,    -1,    -1,    22,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    -1,    -1,    -1,
      -1,    -1,    -1,    22,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    44,    48,    19,     0,    23,    49,    28,    45,    50,
      54,    19,    19,    21,    51,    23,    23,    21,    52,    51,
      19,    22,    55,    36,    40,    41,    42,    43,    53,    23,
      53,    34,    53,    57,    22,    19,    22,    56,    58,    57,
      53,    57,    36,     1,    19,    23,    25,    29,    32,    33,
      34,    39,    50,    59,    61,    62,    57,    19,    21,    31,
      36,    11,    12,    16,    17,    18,    19,    21,    34,    62,
      64,    64,    64,    60,    21,    23,    23,    53,     1,    22,
      64,    64,    27,    64,    64,    64,     1,    64,    60,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    34,    34,    29,    59,    37,    64,    22,    63,
      31,    22,    22,    29,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    60,    60,    23,
      22,    22,    22,    36,    35,    29,    29,    64,    21,    38,
       1,    26,    34,    22,    30,    60,    64,    29,    24,    22
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 125 "gocompiler.y"
    {
    if((yyvsp[(4) - (4)].ponteiro)!=NULL){
        (yyval.ponteiro)=criaNoPai(Raiz,"Program");
        adicionaFilho2((yyval.ponteiro),(yyvsp[(4) - (4)].ponteiro));
    if(flagErro!=1&&flagArvore!=0){
    
        imprimeTralha((yyval.ponteiro),0);


    }
        
    }
    else{
        (yyval.ponteiro)=criaNoPai(Raiz,"Program");
    if(flagErro!=1&&flagArvore!=0){
    
        imprimeTralha((yyval.ponteiro),0);

    }
        
    }
    criaTabelas((yyval.ponteiro));
    //anota
    if(flagSemantica==1){
        imprime_tabelaGlobal();
        imprimeTralha((yyval.ponteiro),0);
        //teste1($$);

    }
    
}
    break;

  case 3:
#line 158 "gocompiler.y"
    {
        if((yyvsp[(1) - (3)].ponteiro)!=NULL){
            (yyval.ponteiro)=(yyvsp[(1) - (3)].ponteiro);
            adicionaIrmao2((yyval.ponteiro),(yyvsp[(2) - (3)].ponteiro));
        }
        else{
            (yyval.ponteiro)=(yyvsp[(2) - (3)].ponteiro);
        }

        }
    break;

  case 4:
#line 168 "gocompiler.y"
    {

        if((yyvsp[(1) - (3)].ponteiro)!=NULL){
            (yyval.ponteiro)=(yyvsp[(1) - (3)].ponteiro);
            adicionaIrmao2((yyval.ponteiro),(yyvsp[(2) - (3)].ponteiro));
        }
        else{
            (yyval.ponteiro)=(yyvsp[(2) - (3)].ponteiro);
        }


}
    break;

  case 5:
#line 180 "gocompiler.y"
    {(yyval.ponteiro)=NULL;}
    break;

  case 6:
#line 183 "gocompiler.y"
    {
        (yyval.ponteiro)=(yyvsp[(2) - (2)].ponteiro);
}
    break;

  case 7:
#line 186 "gocompiler.y"
    {
        (yyval.ponteiro)=(yyvsp[(3) - (5)].ponteiro);
    }
    break;

  case 8:
#line 191 "gocompiler.y"
    { 
    if((yyvsp[(2) - (3)].ponteiro)!=NULL){
        (yyval.ponteiro)=adicionaIrmaoInicio((yyvsp[(2) - (3)].ponteiro),criaNoPai(Terminal,juntaStrings("Id(",(yyvsp[(1) - (3)].string),")")));
        (yyval.ponteiro)=juntarCenas((yyval.ponteiro),(yyvsp[(3) - (3)].ponteiro)->string);
        

    }
    else{
        (yyval.ponteiro)=criaNoPai(DecVariaveis,"VarDecl");
        adicionaFilho2((yyval.ponteiro),(yyvsp[(3) - (3)].ponteiro));
       adicionaIrmao2((yyval.ponteiro)->filho,criaNoPai(Terminal,juntaStrings("Id(",(yyvsp[(1) - (3)].string),")")));
    }
    }
    break;

  case 9:
#line 206 "gocompiler.y"
    {
    if((yyvsp[(1) - (3)].ponteiro)!=NULL){
        (yyval.ponteiro)=(yyvsp[(1) - (3)].ponteiro);
        adicionaIrmao2((yyval.ponteiro),criaNoPai(Terminal,juntaStrings("Id(",(yyvsp[(3) - (3)].string),")")));
    }
    else{
          (yyval.ponteiro)=criaNoPai(Terminal,juntaStrings("Id(",(yyvsp[(3) - (3)].string),")"));
    }
}
    break;

  case 10:
#line 215 "gocompiler.y"
    {(yyval.ponteiro)=NULL;}
    break;

  case 11:
#line 218 "gocompiler.y"
    {(yyval.ponteiro)=criaNoPai(Terminal,"Int");}
    break;

  case 12:
#line 219 "gocompiler.y"
    {(yyval.ponteiro)=criaNoPai(Terminal,"Bool");}
    break;

  case 13:
#line 220 "gocompiler.y"
    {(yyval.ponteiro)=criaNoPai(Terminal,"String");}
    break;

  case 14:
#line 221 "gocompiler.y"
    {(yyval.ponteiro)=criaNoPai(Terminal,"Float32");}
    break;

  case 15:
#line 224 "gocompiler.y"
    {
    nodeDefault *aux,*aux2,*aux3; 
    (yyval.ponteiro)=criaNoPai(DecFuncoes,"FuncDecl");
    aux=criaNoPai(DecFuncoes,"FuncHeader");
    adicionaFilho2((yyval.ponteiro),aux);
     aux2=criaNoPai(Terminal,juntaStrings("Id(",(yyvsp[(2) - (5)].string),")"));
    adicionaFilho2(aux,aux2);
    aux3=criaNoPai(DecFuncoes,"FuncParams");
    adicionaIrmao2(aux->filho,aux3);
    adicionaIrmao2((yyval.ponteiro)->filho,(yyvsp[(5) - (5)].ponteiro));

    //elemento_tabelag* newel=insert_el($2, none);
}
    break;

  case 16:
#line 237 "gocompiler.y"
    {
        nodeDefault *aux,*aux2; 
        (yyval.ponteiro)=criaNoPai(DecFuncoes,"FuncDecl");
        aux=criaNoPai(DecFuncoes,"FuncHeader");
        adicionaFilho2((yyval.ponteiro),aux);
        aux2=criaNoPai(Terminal,juntaStrings("Id(",(yyvsp[(2) - (6)].string),")"));
        adicionaFilho2(aux,aux2);
        adicionaIrmao2(aux->filho,(yyvsp[(4) - (6)].ponteiro));
        adicionaIrmao2((yyval.ponteiro)->filho,(yyvsp[(6) - (6)].ponteiro));

        //elemento_tabelag* newel=insert_el($2, none);
        //insertTipos($2, $4);
    }
    break;

  case 17:
#line 250 "gocompiler.y"
    {
        nodeDefault *aux,*aux2; 
        (yyval.ponteiro)=criaNoPai(DecFuncoes,"FuncDecl");
        aux=criaNoPai(DecFuncoes,"FuncHeader");
        adicionaFilho2((yyval.ponteiro),aux);
        aux2=criaNoPai(Terminal,juntaStrings("Id(",(yyvsp[(2) - (7)].string),")"));
        adicionaFilho2(aux,aux2);
        adicionaIrmao2(aux->filho,(yyvsp[(6) - (7)].ponteiro));
        adicionaIrmao2(aux->filho,(yyvsp[(4) - (7)].ponteiro));
        adicionaIrmao2((yyval.ponteiro)->filho,(yyvsp[(7) - (7)].ponteiro));

        //elemento_tabelag* newel=insert_elNode($2, $6);

        //insertTipos($2, $4);

        
    }
    break;

  case 18:
#line 267 "gocompiler.y"
    {
        nodeDefault *aux,*aux2; 
        (yyval.ponteiro)=criaNoPai(DecFuncoes,"FuncDecl");
        aux=criaNoPai(DecFuncoes,"FuncHeader");
        adicionaFilho2((yyval.ponteiro),aux);
        aux2=criaNoPai(Terminal,juntaStrings("Id(",(yyvsp[(2) - (6)].string),")"));
        adicionaFilho2(aux,aux2);
    
        adicionaIrmao2(aux->filho,(yyvsp[(5) - (6)].ponteiro));//dar double checkkkkk
    
        adicionaIrmao2((yyval.ponteiro)->filho,(yyvsp[(6) - (6)].ponteiro));
    adicionaIrmao2(aux->filho,criaNoPai(DecFuncoes,"FuncParams"));
        //elemento_tabelag* newel=insert_elNode($2, $6);

        //insertTipos($2, $4);

        
    }
    break;

  case 19:
#line 286 "gocompiler.y"
    {
    if ((yyvsp[(3) - (3)].ponteiro)!=NULL){
        nodeDefault *aux1,*aux2;
        aux1=criaNoPai(Terminal,juntaStrings("Id(",(yyvsp[(1) - (3)].string),")"));
        aux2=criaNoPai(DecFuncoes,"ParamDecl");
        adicionaFilho2(aux2,(yyvsp[(2) - (3)].ponteiro));
        adicionaIrmao2(aux2->filho,aux1);
        adicionaIrmaoInicio((yyvsp[(3) - (3)].ponteiro),aux2);
        (yyval.ponteiro)=criaNoPai(DecFuncoes,"FuncParams");
        adicionaFilho2((yyval.ponteiro),aux2);



    }
    else{
        nodeDefault *aux1,*aux2;
         aux1=criaNoPai(Terminal,juntaStrings("Id(",(yyvsp[(1) - (3)].string),")"));
        aux2=criaNoPai(DecFuncoes,"ParamDecl");
        adicionaFilho2(aux2,(yyvsp[(2) - (3)].ponteiro));
        adicionaIrmao2(aux2->filho,aux1);
        (yyval.ponteiro)=criaNoPai(DecFuncoes,"FuncParams");
        adicionaFilho2((yyval.ponteiro),aux2);
    }
    }
    break;

  case 20:
#line 312 "gocompiler.y"
    {
    if((yyvsp[(1) - (4)].ponteiro)!=NULL){
        (yyval.ponteiro)=(yyvsp[(1) - (4)].ponteiro);
        nodeDefault *aux1,*aux2;
        aux1=criaNoPai(Terminal,juntaStrings("Id(",(yyvsp[(3) - (4)].string),")"));
        aux2=criaNoPai(DecFuncoes,"ParamDecl");
        adicionaFilho2(aux2,(yyvsp[(4) - (4)].ponteiro));
        adicionaIrmao2(aux2->filho,aux1);
        adicionaIrmao2((yyval.ponteiro),aux2);
    }
    else{
        nodeDefault *aux1,*aux2;
        aux1=criaNoPai(Terminal,juntaStrings("Id(",(yyvsp[(3) - (4)].string),")"));
        aux2=criaNoPai(DecFuncoes,"ParamDecl");
        adicionaFilho2(aux2,(yyvsp[(4) - (4)].ponteiro));
        adicionaIrmao2(aux2->filho,aux1);
        (yyval.ponteiro)=aux2;
    }
}
    break;

  case 21:
#line 331 "gocompiler.y"
    {(yyval.ponteiro)=NULL;}
    break;

  case 22:
#line 334 "gocompiler.y"
    {
    if((yyvsp[(2) - (3)].ponteiro)!=NULL){

        (yyval.ponteiro)=criaNoPai(DecFuncoes,"FuncBody");
        adicionaFilho2((yyval.ponteiro),(yyvsp[(2) - (3)].ponteiro));
    }
    else{
        (yyval.ponteiro)=criaNoPai(DecFuncoes,"FuncBody");
    }
}
    break;

  case 23:
#line 346 "gocompiler.y"
    {
    if ((yyvsp[(1) - (2)].ponteiro)!=NULL){
        (yyval.ponteiro)=(yyvsp[(1) - (2)].ponteiro);
    } 
    else{
        (yyval.ponteiro)=NULL;
    }
}
    break;

  case 24:
#line 354 "gocompiler.y"
    {
        if((yyvsp[(1) - (3)].ponteiro)!=NULL){
            (yyval.ponteiro)=(yyvsp[(1) - (3)].ponteiro);
            adicionaIrmao2((yyvsp[(1) - (3)].ponteiro),(yyvsp[(2) - (3)].ponteiro));
        }
        else{
            (yyval.ponteiro)=(yyvsp[(2) - (3)].ponteiro);
        }
    }
    break;

  case 25:
#line 363 "gocompiler.y"
    {
        if((yyvsp[(1) - (3)].ponteiro)!=NULL){
            (yyval.ponteiro)=(yyvsp[(1) - (3)].ponteiro);
            adicionaIrmao2((yyvsp[(1) - (3)].ponteiro),(yyvsp[(2) - (3)].ponteiro));
        }
        else{
            (yyval.ponteiro)=(yyvsp[(2) - (3)].ponteiro);
        }
    }
    break;

  case 26:
#line 372 "gocompiler.y"
    {(yyval.ponteiro)=NULL;}
    break;

  case 27:
#line 375 "gocompiler.y"
    {(yyval.ponteiro)=criaNoPai(Statements,"Print");adicionaFilho2((yyval.ponteiro),(yyvsp[(3) - (4)].ponteiro));}
    break;

  case 28:
#line 376 "gocompiler.y"
    {(yyval.ponteiro)=criaNoPai(Statements,"Print");adicionaFilho2((yyval.ponteiro),criaNoPai(Terminal,juntaStrings("StrLit(\"",(yyvsp[(3) - (4)].string),"\")")));}
    break;

  case 29:
#line 377 "gocompiler.y"
    {(yyval.ponteiro)=NULL;}
    break;

  case 30:
#line 378 "gocompiler.y"
    {(yyval.ponteiro)=(yyvsp[(1) - (1)].ponteiro);}
    break;

  case 31:
#line 379 "gocompiler.y"
    {(yyval.ponteiro)=(yyvsp[(1) - (1)].ponteiro);}
    break;

  case 32:
#line 380 "gocompiler.y"
    {(yyval.ponteiro)=criaNoPai(Statements,"Return");}
    break;

  case 33:
#line 381 "gocompiler.y"
    {(yyval.ponteiro)=criaNoPai(Statements,"Return");adicionaFilho2((yyval.ponteiro),(yyvsp[(2) - (2)].ponteiro));}
    break;

  case 34:
#line 382 "gocompiler.y"
    {

        if((yyvsp[(4) - (5)].ponteiro)!=NULL){
            nodeDefault *aux;
            (yyval.ponteiro)=criaNoPai(Statements,"For");
            adicionaFilho2((yyval.ponteiro),(yyvsp[(2) - (5)].ponteiro));
            aux=criaNoPai(Statements,"Block");
            adicionaFilho2(aux,(yyvsp[(4) - (5)].ponteiro));
            adicionaIrmao2((yyval.ponteiro)->filho,aux);
        }
        else{
            nodeDefault *aux;
            (yyval.ponteiro)=criaNoPai(Statements,"For");
            adicionaFilho2((yyval.ponteiro),(yyvsp[(2) - (5)].ponteiro));
            aux=criaNoPai(Statements,"Block");
            adicionaIrmao2((yyval.ponteiro)->filho,aux);
        }

    }
    break;

  case 35:
#line 401 "gocompiler.y"
    {
        if((yyvsp[(3) - (4)].ponteiro)!=NULL){
            nodeDefault *aux;
            (yyval.ponteiro)=criaNoPai(Statements,"For");
            aux=criaNoPai(Statements,"Block");
            adicionaFilho2(aux,(yyvsp[(3) - (4)].ponteiro));
            adicionaFilho2((yyval.ponteiro),aux);
        }
        else{
            nodeDefault *aux;
            (yyval.ponteiro)=criaNoPai(Statements,"For");
            aux=criaNoPai(Statements,"Block");
            adicionaFilho2((yyval.ponteiro),aux);  
        }
    }
    break;

  case 36:
#line 416 "gocompiler.y"
    {
            (yyval.ponteiro)=criaNoPai(Operadores,"Assign");
            adicionaFilho2((yyval.ponteiro),criaNoPai(Terminal,juntaStrings("Id(",(yyvsp[(1) - (3)].string),")")));
            adicionaIrmao2((yyval.ponteiro)->filho,(yyvsp[(3) - (3)].ponteiro));
}
    break;

  case 37:
#line 421 "gocompiler.y"
    {
        if((yyvsp[(4) - (5)].ponteiro)!=NULL){
            nodeDefault *aux;
            (yyval.ponteiro)=criaNoPai(Statements,"If");
            adicionaFilho2((yyval.ponteiro),(yyvsp[(2) - (5)].ponteiro));
            aux=criaNoPai(Statements,"Block");
            adicionaFilho2(aux,(yyvsp[(4) - (5)].ponteiro));
            adicionaIrmao2((yyval.ponteiro)->filho,aux);
            adicionaIrmao2((yyval.ponteiro)->filho,criaNoPai(Statements,"Block"));
        }
        else{
            nodeDefault *aux;
            (yyval.ponteiro)=criaNoPai(Statements,"If");
            adicionaFilho2((yyval.ponteiro),(yyvsp[(2) - (5)].ponteiro));
            aux=criaNoPai(Statements,"Block");
            adicionaIrmao2((yyval.ponteiro)->filho,aux);
            adicionaIrmao2((yyval.ponteiro)->filho,criaNoPai(Statements,"Block"));
        }
    }
    break;

  case 38:
#line 440 "gocompiler.y"
    {
        //NENHUM NULL
        if((yyvsp[(4) - (9)].ponteiro)!=NULL && (yyvsp[(8) - (9)].ponteiro)!=NULL){
            nodeDefault *aux,*aux2;
            (yyval.ponteiro)=criaNoPai(Statements,"If");
            adicionaFilho2((yyval.ponteiro),(yyvsp[(2) - (9)].ponteiro));
            aux=criaNoPai(Statements,"Block");
            adicionaFilho2(aux,(yyvsp[(4) - (9)].ponteiro));
            adicionaIrmao2((yyval.ponteiro)->filho,aux);
            aux2=criaNoPai(Statements,"Block");
            adicionaIrmao2((yyval.ponteiro)->filho,aux2);
            adicionaFilho2(aux2,(yyvsp[(8) - (9)].ponteiro));
        }
        // $4 NULL E $8 NÃO NULL
        if((yyvsp[(4) - (9)].ponteiro)==NULL && (yyvsp[(8) - (9)].ponteiro)!=NULL){
            nodeDefault *aux,*aux2;
            (yyval.ponteiro)=criaNoPai(Statements,"If");
            adicionaFilho2((yyval.ponteiro),(yyvsp[(2) - (9)].ponteiro));
            aux=criaNoPai(Statements,"Block");
            adicionaIrmao2((yyval.ponteiro)->filho,aux);
            aux2=criaNoPai(Statements,"Block");
            adicionaIrmao2((yyval.ponteiro)->filho,aux2);
            adicionaFilho2(aux2,(yyvsp[(8) - (9)].ponteiro));
        }
        // $4 NÃO NULL E $8 NULL
        if((yyvsp[(4) - (9)].ponteiro)!=NULL && (yyvsp[(8) - (9)].ponteiro)==NULL){
            nodeDefault *aux,*aux2;
            (yyval.ponteiro)=criaNoPai(Statements,"If");
            adicionaFilho2((yyval.ponteiro),(yyvsp[(2) - (9)].ponteiro));
            aux=criaNoPai(Statements,"Block");
            adicionaFilho2(aux,(yyvsp[(4) - (9)].ponteiro));
            adicionaIrmao2((yyval.ponteiro)->filho,aux);
            aux2=criaNoPai(Statements,"Block");
            adicionaIrmao2((yyval.ponteiro)->filho,aux2);
        }
        // $4 NULL E $8 NULL
        if((yyvsp[(4) - (9)].ponteiro)==NULL && (yyvsp[(8) - (9)].ponteiro)==NULL){
            nodeDefault *aux,*aux2;
            (yyval.ponteiro)=criaNoPai(Statements,"If");
            adicionaFilho2((yyval.ponteiro),(yyvsp[(2) - (9)].ponteiro));
            aux=criaNoPai(Statements,"Block");
            adicionaIrmao2((yyval.ponteiro)->filho,aux);
            aux2=criaNoPai(Statements,"Block");
            adicionaIrmao2((yyval.ponteiro)->filho,aux2);
        }

    }
    break;

  case 39:
#line 487 "gocompiler.y"
    { /* Dúvida */
        if((yyvsp[(2) - (3)].ponteiro)!=NULL){
            if(contaIrmao((yyvsp[(2) - (3)].ponteiro))>1){ // Se for maior ou igual a 2 cria Block
                (yyval.ponteiro)=criaNoPai(Statements,"Block");
                adicionaFilho2((yyval.ponteiro),(yyvsp[(2) - (3)].ponteiro));

            }
            else{ // Caso contrário não cria, mas não é preciso adicionar também?
                (yyval.ponteiro)=(yyvsp[(2) - (3)].ponteiro);
            }
        }
        else{
            (yyval.ponteiro)=NULL;
        }
    }
    break;

  case 40:
#line 504 "gocompiler.y"
    {
    if((yyvsp[(1) - (3)].ponteiro)!=NULL){
        (yyval.ponteiro)=adicionaIrmao2((yyvsp[(1) - (3)].ponteiro),(yyvsp[(2) - (3)].ponteiro));// vai receber o irmao à esquerda do novo
    }
    else{
        (yyval.ponteiro)=(yyvsp[(2) - (3)].ponteiro);
    }
}
    break;

  case 41:
#line 512 "gocompiler.y"
    {(yyval.ponteiro)=NULL;}
    break;

  case 42:
#line 515 "gocompiler.y"
    {
    (yyval.ponteiro)=criaNoPai(Statements,"ParseArgs");
    adicionaFilho2((yyval.ponteiro),criaNoPai(Terminal,juntaStrings("Id(",(yyvsp[(1) - (11)].string),")")));
    adicionaIrmao2((yyval.ponteiro)->filho,(yyvsp[(9) - (11)].ponteiro));
}
    break;

  case 43:
#line 520 "gocompiler.y"
    {(yyval.ponteiro)=NULL;}
    break;

  case 44:
#line 523 "gocompiler.y"
    {(yyval.ponteiro)=NULL;}
    break;

  case 45:
#line 524 "gocompiler.y"
    {(yyval.ponteiro)=criaNoPai(Statements,"Call");adicionaFilho2((yyval.ponteiro),criaNoPai(Terminal,juntaStrings("Id(",(yyvsp[(1) - (3)].string),")")));}
    break;

  case 46:
#line 525 "gocompiler.y"
    {
        if((yyvsp[(4) - (5)].ponteiro)!=NULL){
            (yyval.ponteiro)=criaNoPai(Statements,"Call");
            adicionaFilho2((yyval.ponteiro),criaNoPai(Terminal,juntaStrings("Id(",(yyvsp[(1) - (5)].string),")")));
        adicionaIrmao2((yyvsp[(3) - (5)].ponteiro),(yyvsp[(4) - (5)].ponteiro));
            adicionaIrmao2((yyval.ponteiro)->filho,(yyvsp[(3) - (5)].ponteiro));
    }
    else{
        nodeDefault *aux;
        aux=criaNoPai(Terminal,juntaStrings("Id(",(yyvsp[(1) - (5)].string),")"));
        (yyval.ponteiro)=criaNoPai(Statements,"Call");
        adicionaIrmao2(aux,(yyvsp[(3) - (5)].ponteiro));
        adicionaFilho2((yyval.ponteiro),aux);
    }
    }
    break;

  case 47:
#line 543 "gocompiler.y"
    {if((yyvsp[(1) - (3)].ponteiro)!=NULL){(yyval.ponteiro)=(yyvsp[(1) - (3)].ponteiro);adicionaIrmao2((yyvsp[(1) - (3)].ponteiro),(yyvsp[(3) - (3)].ponteiro));}else{(yyval.ponteiro)=(yyvsp[(3) - (3)].ponteiro);}}
    break;

  case 48:
#line 544 "gocompiler.y"
    {(yyval.ponteiro)=NULL;}
    break;

  case 49:
#line 547 "gocompiler.y"
    {(yyval.ponteiro)=criaNoPai(Operadores,"Or");adicionaFilho2((yyval.ponteiro),(yyvsp[(1) - (3)].ponteiro));adicionaIrmao2((yyval.ponteiro)->filho,(yyvsp[(3) - (3)].ponteiro));}
    break;

  case 50:
#line 548 "gocompiler.y"
    {(yyval.ponteiro)=criaNoPai(Terminal,juntaStrings("Id(",(yyvsp[(1) - (1)].string),")"));}
    break;

  case 51:
#line 549 "gocompiler.y"
    {(yyval.ponteiro)=criaNoPai(Terminal,juntaStrings("RealLit(",(yyvsp[(1) - (1)].string),")"));}
    break;

  case 52:
#line 550 "gocompiler.y"
    {(yyval.ponteiro)=criaNoPai(Terminal,juntaStrings("IntLit(",(yyvsp[(1) - (1)].string),")"));}
    break;

  case 53:
#line 551 "gocompiler.y"
    {(yyval.ponteiro)=criaNoPai(Operadores,"And");adicionaFilho2((yyval.ponteiro),(yyvsp[(1) - (3)].ponteiro));adicionaIrmao2((yyval.ponteiro)->filho,(yyvsp[(3) - (3)].ponteiro));}
    break;

  case 54:
#line 552 "gocompiler.y"
    {(yyval.ponteiro)=criaNoPai(Operadores,"Add");adicionaFilho2((yyval.ponteiro),(yyvsp[(1) - (3)].ponteiro));adicionaIrmao2((yyval.ponteiro)->filho,(yyvsp[(3) - (3)].ponteiro));}
    break;

  case 55:
#line 553 "gocompiler.y"
    {(yyval.ponteiro)=criaNoPai(Operadores,"Lt");adicionaFilho2((yyval.ponteiro),(yyvsp[(1) - (3)].ponteiro));adicionaIrmao2((yyval.ponteiro)->filho,(yyvsp[(3) - (3)].ponteiro));}
    break;

  case 56:
#line 554 "gocompiler.y"
    {(yyval.ponteiro)=criaNoPai(Operadores,"Sub");adicionaFilho2((yyval.ponteiro),(yyvsp[(1) - (3)].ponteiro));adicionaIrmao2((yyval.ponteiro)->filho,(yyvsp[(3) - (3)].ponteiro));}
    break;

  case 57:
#line 555 "gocompiler.y"
    {(yyval.ponteiro)=criaNoPai(Operadores,"Gt");adicionaFilho2((yyval.ponteiro),(yyvsp[(1) - (3)].ponteiro));adicionaIrmao2((yyval.ponteiro)->filho,(yyvsp[(3) - (3)].ponteiro));}
    break;

  case 58:
#line 556 "gocompiler.y"
    {(yyval.ponteiro)=criaNoPai(Operadores,"Mod");adicionaFilho2((yyval.ponteiro),(yyvsp[(1) - (3)].ponteiro));adicionaIrmao2((yyval.ponteiro)->filho,(yyvsp[(3) - (3)].ponteiro));}
    break;

  case 59:
#line 557 "gocompiler.y"
    {(yyval.ponteiro)=criaNoPai(Operadores,"Div");adicionaFilho2((yyval.ponteiro),(yyvsp[(1) - (3)].ponteiro));adicionaIrmao2((yyval.ponteiro)->filho,(yyvsp[(3) - (3)].ponteiro));}
    break;

  case 60:
#line 558 "gocompiler.y"
    {(yyval.ponteiro)=criaNoPai(Operadores,"Ge");adicionaFilho2((yyval.ponteiro),(yyvsp[(1) - (3)].ponteiro));adicionaIrmao2((yyval.ponteiro)->filho,(yyvsp[(3) - (3)].ponteiro));}
    break;

  case 61:
#line 559 "gocompiler.y"
    {(yyval.ponteiro)=criaNoPai(Operadores,"Mul");adicionaFilho2((yyval.ponteiro),(yyvsp[(1) - (3)].ponteiro));adicionaIrmao2((yyval.ponteiro)->filho,(yyvsp[(3) - (3)].ponteiro));}
    break;

  case 62:
#line 560 "gocompiler.y"
    {(yyval.ponteiro)=criaNoPai(Operadores,"Eq");adicionaFilho2((yyval.ponteiro),(yyvsp[(1) - (3)].ponteiro));adicionaIrmao2((yyval.ponteiro)->filho,(yyvsp[(3) - (3)].ponteiro));}
    break;

  case 63:
#line 561 "gocompiler.y"
    {(yyval.ponteiro)=criaNoPai(Operadores,"Ne");adicionaFilho2((yyval.ponteiro),(yyvsp[(1) - (3)].ponteiro));adicionaIrmao2((yyval.ponteiro)->filho,(yyvsp[(3) - (3)].ponteiro));}
    break;

  case 64:
#line 562 "gocompiler.y"
    {(yyval.ponteiro)=criaNoPai(Operadores,"Le");adicionaFilho2((yyval.ponteiro),(yyvsp[(1) - (3)].ponteiro));adicionaIrmao2((yyval.ponteiro)->filho,(yyvsp[(3) - (3)].ponteiro));}
    break;

  case 65:
#line 563 "gocompiler.y"
    {(yyval.ponteiro)=(yyvsp[(2) - (3)].ponteiro);}
    break;

  case 66:
#line 564 "gocompiler.y"
    {(yyval.ponteiro)=criaNoPai(Operadores,"Minus");adicionaFilho2((yyval.ponteiro),(yyvsp[(2) - (2)].ponteiro));}
    break;

  case 67:
#line 565 "gocompiler.y"
    {(yyval.ponteiro)=criaNoPai(Operadores,"Plus");adicionaFilho2((yyval.ponteiro),(yyvsp[(2) - (2)].ponteiro));}
    break;

  case 68:
#line 566 "gocompiler.y"
    {(yyval.ponteiro)=criaNoPai(Operadores,"Not");adicionaFilho2((yyval.ponteiro),(yyvsp[(2) - (2)].ponteiro));}
    break;

  case 69:
#line 567 "gocompiler.y"
    {(yyval.ponteiro)=(yyvsp[(1) - (1)].ponteiro);}
    break;

  case 70:
#line 568 "gocompiler.y"
    {(yyval.ponteiro)=NULL;}
    break;


/* Line 1267 of yacc.c.  */
#line 2302 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 573 "gocompiler.y"




void yyerror (char *st) {
    flagErro=1;
    if(flagString==0){

        printf ("Line %d, column %d: %s: %s\n", yylineno, numcolunas-(int)strlen(yytext), st, yytext);

    }
    else{

        printf ("Line %d, column %d: %s: \"%s\"\n", yylineno, numcolunas-(int)strlen(s)-2, st, s);
        flagString=0;
    }

}

char * juntaStrings(char *tipo,char *valor, char *parenteses){
    char *aux;
    aux = (char*)malloc(sizeof(char)*300);
    strcpy(aux,tipo);
    strcat(aux,valor);
    strcat(aux, parenteses);
    
    return aux;
}
nodeDefault * criaNoPai(nodeType tipo, char *str){
    nodeDefault *ponteiro;
    if ((ponteiro=malloc(sizeof(nodeDefault)))== NULL)
        printf("Estoirou!\n");
    ponteiro->filho=NULL;
    ponteiro->irmao=NULL;
    ponteiro->string=str;
    ponteiro->tipo=tipo;
    return ponteiro;
}
nodeDefault * adicionaFilho(nodeDefault * pai,nodeType tipo, char *str){
    nodeDefault *novo;
    novo=criaNoPai(tipo, str);
    pai->filho=novo;
    return novo;
}

nodeDefault * adicionaIrmao(nodeDefault * atual,nodeType tipo, char *str){
    //Temos de adicionar no mais à direita
    nodeDefault *novo;
    nodeDefault *iterador;
    iterador=atual;
    while(iterador->irmao!=NULL){
        iterador=iterador->irmao;
    }
    novo=criaNoPai(tipo, str);
    iterador->irmao=novo;
    return novo;
}


int imprimeTralha(nodeDefault *raiz,int depth){
    nodeDefault *iterador;
    int i;
    for(i=0;i<depth;i++){
        printf("..");
    }
    printf("%s\n",raiz->string);
    if(raiz->filho!=NULL){
    imprimeTralha(raiz->filho,depth+1);
        iterador=raiz->filho->irmao;
        while(iterador!=NULL){
            imprimeTralha(iterador,depth+1);
            iterador=iterador->irmao;
        }
    }
   
    return 0;

}
nodeDefault * adicionaIrmao2(nodeDefault * atual,nodeDefault *novo){
    nodeDefault *iterador;
    iterador=atual;
    while(iterador->irmao!=NULL){
        iterador=iterador->irmao;
    }
    iterador->irmao=novo;


    return atual;
}
nodeDefault * adicionaFilho2(nodeDefault * pai,nodeDefault *novo){
    pai->filho=novo;
    return novo;
}

nodeDefault * adicionaIrmaoInicio(nodeDefault * atual,nodeDefault *novo){
    //Temos de adicionar no inicio
    novo->irmao=atual;
    return novo;
}
nodeDefault * juntarCenas(nodeDefault * alvo,char* string){
    //Temos de adicionar no inicios
    nodeDefault *final,*iterador,*aux;
    iterador=alvo;
    final=criaNoPai(DecVariaveis,"VarDecl");
    adicionaFilho2(final,criaNoPai(Terminal,string));
    adicionaIrmao2(final->filho,criaNoPai(Terminal,alvo->string));
    iterador=iterador->irmao;
    while(iterador!=NULL){
        aux=criaNoPai(DecVariaveis,"VarDecl");
        adicionaFilho2(aux,criaNoPai(Terminal,string));
        adicionaIrmao2(aux->filho,criaNoPai(Terminal,iterador->string));

        adicionaIrmao2(final,aux);
        iterador=iterador->irmao;

    }
    

    return final;
}


 int contaIrmao(nodeDefault * alvo){
    nodeDefault * iterador;
    int sum=1;
    iterador=alvo;
    while(iterador->irmao!=NULL){
        sum++;
        iterador=iterador->irmao;
    
    }
    return sum;

    }


int criaTabelas(nodeDefault *raiz){
    nodeDefault *iterador;
    elemento_tabelag * aux;
    iterador=raiz->filho;
    while(iterador!=NULL){
    if(strcmp(iterador->string,"FuncDecl")==0){
        aux=insertFuncaoT(iterador);
        criaLocal(iterador,aux);
        //imprime_tabelaLocal(aux->local);
        }
    if(strcmp(iterador->string,"VarDecl")==0){
            insertVarD(iterador);
        }


    iterador=iterador->irmao;
    }
/*
    //printf("%s\n",raiz->string);
    if(raiz->filho!=NULL){

        if(strcmp(raiz->filho->string,"FuncDecl")==0){
            insertFuncaoT(raiz->filho);
        }
    if(strcmp(raiz->filho->string,"VarDecl")==0){
        printf("heheheheh\n");
            insertVarD(raiz->filho);
        }
        criaTabelas(raiz->filho);
        iterador=raiz->filho->irmao;
        while(iterador!=NULL){
            if(strcmp(iterador->string,"FuncDecl")==0){
                insertFuncaoT(iterador);
            }
        if(strcmp(iterador->string,"VarDecl")==0){
        printf("heheheheh2\n");
                insertVarD(iterador);
             }
            criaTabelas(iterador);
            iterador=iterador->irmao;
        }
    //varDecl
    }*/
   
    return 0;

}
/*
int criaTabelas(nodeDefault *raiz){
    nodeDefault *iterador;


    //printf("%s\n",raiz->string);
    if(raiz->filho!=NULL){

        if(strcmp(raiz->filho->string,"FuncDecl")==0){
            insertFuncaoT(raiz->filho);
        }
    if(strcmp(raiz->filho->string,"VarDecl")==0){
        printf("heheheheh\n");
            insertVarD(raiz->filho);
        }
        criaTabelas(raiz->filho);
        iterador=raiz->filho->irmao;
        while(iterador!=NULL){
            if(strcmp(iterador->string,"FuncDecl")==0){
                insertFuncaoT(iterador);
            }
        if(strcmp(iterador->string,"VarDecl")==0){
        printf("heheheheh2\n");
                insertVarD(iterador);
             }
            criaTabelas(iterador);
            iterador=iterador->irmao;
        }
    //varDecl
    }
   
    return 0;

}*/
/*
int anota(nodeDefault *raiz){

    if(no==expressoes){
        if(no nao for equal)
        recursiva();
    }


}
 recursiva(){
    no->filho;
    if(eu sou x&& meiu irmao for x){
        return; 
    }
    se o meu irmao nao tiver tipo recursiva
    se eu nao tiver tipo ir ver
    while(no!=NULL) {
        if(){
        }
        no=no->irmao;
    }

}*/
//so o body e que iporta ir a cada body de cada funcao

void teste1(nodeDefault *raiz){
    nodeDefault *aux;
    int x=0;
    aux=raiz->filho;
    while(aux!=NULL){
        recursiva(aux->filho->irmao,x);
        aux=aux->irmao;
        x++;
    }
    
    }
int recursiva(nodeDefault *no,int local){
    //teoria so no body e que importa
    nodeDefault *aux;
    int flag=0;
    if(strcmp(no->string,"Call")==0){
        flag=1;
    }
    aux=no->filho;
    if(aux==NULL){
        return 0;   
    }
    if(strcmp(aux->string,"VarDecl")==0){
        aux=aux->irmao;
    }
    
    while(aux!=NULL){
        //acho que precisamos de um array para saber erros e tal do genero string*int
        checkaTerminais(aux,local,flag);
        recursiva(aux,local);
        aux=aux->irmao;
        flag=0;
    }
    if(strcmp(no->string,"Eq")==0){
        //percorrer filho ja com o tipo e depois meter o tipo
        printf("percorrer filho ja com o tipo e depois meter o tipo\n");
    }
    if(strcmp(no->string,"Or")==0){
        //percorrer filho ja com o tipo e depois meter o tipo
        printf("percorrer filho ja com o tipo e depois meter o tipo\n");
    }
    if(strcmp(no->string,"And")==0){
        //percorrer filho ja com o tipo e depois meter o tipo
        printf("percorrer filho ja com o tipo e depois meter o tipo\n");
    }
    if(strcmp(no->string,"Ne")==0){
        //percorrer filho ja com o tipo e depois meter o tipo
        printf("percorrer filho ja com o tipo e depois meter o tipo\n");
    }
    if(strcmp(no->string,"Lt")==0){
        //percorrer filho ja com o tipo e depois meter o tipo
        printf("percorrer filho ja com o tipo e depois meter o tipo\n");
    }
    /*if do mal para saber se e multi divi etccccc acho que seria aqui Or(2) And(2) Eq(2) Ne(2) Lt(2) Gt(2) Le(2) Ge(2) Add(2) Sub(2) Mul(2) Div(2) Mod(2)
Not(1) Minus(1) Plus(1) Assign(2) Call(>=1) parseArgs call*/
    if(strcmp(no->string,"Gt")==0){
        //percorrer filho ja com o tipo e depois meter o tipo
        printf("percorrer filho ja com o tipo e depois meter o tipo\n");
    }
    if(strcmp(no->string,"Le")==0){
        //percorrer filho ja com o tipo e depois meter o tipo
        printf("percorrer filho ja com o tipo e depois meter o tipo\n");
    }
    if(strcmp(no->string,"Ge")==0){
        //percorrer filho ja com o tipo e depois meter o tipo
        printf("percorrer filho ja com o tipo e depois meter o tipo\n");
    }
    if(strcmp(no->string,"Add")==0){
        //percorrer filho ja com o tipo e depois meter o tipo
        printf("percorrer filho ja com o tipo e depois meter o tipo\n");
    }
    if(strcmp(no->string,"Sub")==0){
        //percorrer filho ja com o tipo e depois meter o tipo
        printf("percorrer filho ja com o tipo e depois meter o tipo\n");
    }
    if(strcmp(no->string,"Mul")==0){
        //percorrer filho ja com o tipo e depois meter o tipo
        printf("percorrer filho ja com o tipo e depois meter o tipo\n");
    }
    if(strcmp(no->string,"Div")==0){
        //percorrer filho ja com o tipo e depois meter o tipo
        printf("percorrer filho ja com o tipo e depois meter o tipo\n");
    }
    if(strcmp(no->string,"Mod")==0){
        //percorrer filho ja com o tipo e depois meter o tipo
        printf("percorrer filho ja com o tipo e depois meter o tipo\n");
    }
    if(strcmp(no->string,"Not")==0){
        //percorrer filho ja com o tipo e depois meter o tipo
        printf("percorrer filho ja com o tipo e depois meter o tipo\n");
    }
    if(strcmp(no->string,"Minus")==0){
        //percorrer filho ja com o tipo e depois meter o tipo
        printf("percorrer filho ja com o tipo e depois meter o tipo\n");
    }
    if(strcmp(no->string,"Plus")==0){
        //percorrer filho ja com o tipo e depois meter o tipo
        printf("percorrer filho ja com o tipo e depois meter o tipo\n");
    }
    if(strcmp(no->string,"Assign")==0){
        //percorrer filho ja com o tipo e depois meter o tipo
        printf("percorrer filho ja com o tipo e depois meter o tipo\n");
    }
    if(strcmp(no->string,"Call")==0){
        //percorrer filho ja com o tipo e depois meter o tipo
        printf("percorrer filho ja com o tipo e depois meter o tipo\n");
    }
    if(strcmp(no->string,"ParseArgs")==0){
        //percorrer filho ja com o tipo e depois meter o tipo
        printf("percorrer filho ja com o tipo e depois meter o tipo\n");
    }
    //secalahr aqui em baixo duno
    return 0;

    }
void checkaTerminais(nodeDefault *no,int local,int flag){
    char* aux;
    aux=no->string;
    if(strncmp("Id",aux,strlen("Id"))==0){
        printf("id-->%s\n",aux);
        if(flag==1){
            //temos funcao percorrer tabelas da maneira x   
            printf("encotramos um id depois de um call\n"); 
        }
        else{
            printf("encotramos um id normal\n");
            //temos uma variavel percorrer da outra maneira
        }
        percorreTabela(aux,local);
        //quando temos o id temos de ir sempre as tabelas acho eu
        //temos de ir ver as tabelas e adicionar a lista de tipos
    }
    if(strncmp("IntLit",aux,strlen("IntLit"))==0){
        printf("intlit\n");
        //temos de adicionar ao no o tipo int
    }
    if(strncmp("RealLit",aux,strlen("RealLit"))==0){
        printf("realit\n");
        //temos de adicionar ao no o tipo float32
    }
    if(strncmp("StrLit",aux,strlen("StrLit"))==0){
        printf("strlit\n");
        //temos de adicionar ao no o tipo string
    }

    }

char* percorreTabela(char* str,int local){
    elemento_tabelag * aux;
    elemento_tabelal * aux2;
    int i;
    char* auxS;
    aux=tg;
    auxS=(char*)malloc(sizeof(char)*100);
    auxS=tiraId(str);
    //printf("tabela Global\n");
    while(aux){
        //printf("-%s\n",aux->name);
        if(strcmp(aux->name,auxS)==0){
            printf("encontramos Global\n"); 
            return estupido(aux->tipo);
        }
        aux=aux->next;  
        
    }
    //na ta na global ver local
    aux=tg;
    for(i=0;i<local;i++){
        aux=aux->next;  
    }
    aux2=aux->local;
    //printf("tabela local\n");
    while(aux2){    
        //printf("--%s\n",aux2->name);
        if(strcmp(aux2->name,auxS)==0){
            printf("encontramos local\n");
            return estupido(aux2->tipo);
        }
        aux2=aux2->next;    
    }
    return "";
    //nao encontramos nada
}
/*
int imprimeASTanotada(nodeDefault *raiz,int flag,int depth){
    nodeDefault *iterador;
    int i;
    for(i=0;i<depth;i++){
        printf("..");
    }
    printf("%s",raiz->string);
    // Quer dizer que tem notas, logo tem de as imprimir
    if(raiz->tipos!=NULL){
        imprimeTiposAST(raiz->tipos,flag);
    }
    printf("\n");
    if(raiz->filho!=NULL){
    imprimeASTanotada(raiz->filho,depth+1);
        iterador=raiz->filho->irmao;
        while(iterador!=NULL){
            imprimeASTanotada(iterador,depth+1);
            iterador=iterador->irmao;
        }
    }
   
    return 0;

}
*/

int main(int argc, char **argv) {
    /*
    yydebug=1;
    */
    if(argc>1){
        if (strcmp(argv[1],"-l")==0){
    flagArvore=0;
            flagLex=1;
        while(yylex()){
    
        }
        }
    else{
    if (strcmp(argv[1],"-t")==0){
            flagArvore=1;
     flagLex=0;
        yyparse();
        }
    if (strcmp(argv[1],"-s")==0){
         flagArvore=0;
            flagLex=0;
            flagSemantica=1;
        yyparse();
        }
    }   
        
    }
    else{
        yyparse();
        flagArvore=0;
        //imprime_tabelaGlobal();
    }
    return 0;
}


