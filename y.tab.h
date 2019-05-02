/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

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
/* Line 1529 of yacc.c.  */
#line 149 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

