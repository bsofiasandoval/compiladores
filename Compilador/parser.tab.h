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
     PROGRAMA = 258,
     INICIO = 259,
     FIN = 260,
     VARS = 261,
     NULA = 262,
     ENTERO = 263,
     FLOTANTE = 264,
     SI = 265,
     SINO = 266,
     MIENTRAS = 267,
     HAZ = 268,
     ESCRIBE = 269,
     REGRESA = 270,
     ASIGNACION = 271,
     PUNTOYCOMA = 272,
     DOSPUNTOS = 273,
     COMA = 274,
     PARENIZQ = 275,
     PARENDER = 276,
     LLAVEIZQ = 277,
     LLAVEDER = 278,
     CORCHETEIZQ = 279,
     CORCHETEDER = 280,
     IGUAL = 281,
     DIFERENTE = 282,
     MENORQUE = 283,
     MAYORQUE = 284,
     MAS = 285,
     MENOS = 286,
     POR = 287,
     ENTRE = 288,
     CTE_ENT = 289,
     CTE_FLOT = 290,
     ID = 291,
     LETRERO = 292
   };
#endif
/* Tokens.  */
#define PROGRAMA 258
#define INICIO 259
#define FIN 260
#define VARS 261
#define NULA 262
#define ENTERO 263
#define FLOTANTE 264
#define SI 265
#define SINO 266
#define MIENTRAS 267
#define HAZ 268
#define ESCRIBE 269
#define REGRESA 270
#define ASIGNACION 271
#define PUNTOYCOMA 272
#define DOSPUNTOS 273
#define COMA 274
#define PARENIZQ 275
#define PARENDER 276
#define LLAVEIZQ 277
#define LLAVEDER 278
#define CORCHETEIZQ 279
#define CORCHETEDER 280
#define IGUAL 281
#define DIFERENTE 282
#define MENORQUE 283
#define MAYORQUE 284
#define MAS 285
#define MENOS 286
#define POR 287
#define ENTRE 288
#define CTE_ENT 289
#define CTE_FLOT 290
#define ID 291
#define LETRERO 292




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 51 "parser.y"
{
    int ival;
    float fval;
    char* sval;
}
/* Line 1529 of yacc.c.  */
#line 129 "parser.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

