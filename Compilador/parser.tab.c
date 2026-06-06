/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include <iostream>
#include <string>
#include <vector>
#include "helpers/compilador/FuncDir.h"
#include "helpers/compilador/SemanticCube.h"
#include "helpers/compilador/QuadrupleBuilder.h"
#include "helpers/compilador/Memory.h"
#include "helpers/estructuras/Stack.h"
using namespace std;

void yyerror(const char* s) {
    cerr << "Error sintáctico: " << s << endl;
}
int yylex();

SemanticCube cube;
MemoryManager memory;

Table<string, FuncEntry> dirFunc;
string scopeActual = "global";
vector<string> idStack;

Stack<string> operators;
Stack<string> vars;
Stack<string> types;
Stack<int> jumps;
QuadrupleBuilder quadruples;
string callTarget = "";
int paramCount = 0;

VarInfo lookupVar(const string& name) {
    if (scopeActual != "global" &&
        dirFunc.get(scopeActual).varTable.vars.contains(name))
        return dirFunc.get(scopeActual).varTable.vars.get(name);
    if (dirFunc.get("global").varTable.vars.contains(name))
        return dirFunc.get("global").varTable.vars.get(name);
    throw runtime_error("Variable no declarada: " + name);
}

void registerParam(const string& name, const string& tipo) {
    int addr = memory.getAddress(scopeActual, tipo);
    dirFunc.get(scopeActual).varTable.vars.insert(name, VarInfo(tipo, addr));
    dirFunc.get(scopeActual).params.push_back(ParamInfo(tipo, addr));
}

void finalizeFunc() {
    quadruples.add("ENDFUNC", "_", "_", "_");
    FuncEntry& f = dirFunc.get(scopeActual);
    f.localIntCount   = memory.localIntCount();
    f.localFloatCount = memory.localFloatCount();
    f.tempIntCount    = memory.tempIntCount();
    f.tempFloatCount  = memory.tempFloatCount();
    memory.resetLocal();
    scopeActual = "global";
}

string popExpr() {
    string addr = vars.getTop(); vars.pop();
    types.pop();
    return addr;
}

void makeQuadruple() {
    string op = operators.getTop(); operators.pop();
    string varDer = vars.getTop(); vars.pop();
    string tipoDer = types.getTop(); types.pop();
    string varIzq = vars.getTop(); vars.pop();
    string tipoIzq = types.getTop(); types.pop();

   

    if(op == "="){
        quadruples.add(op, varDer, "_", varIzq);
    } 
    else {
        string tipoRes = cube.validate(tipoIzq, tipoDer, op);
        string tempAddr = to_string(memory.getTempAddress(tipoRes));
        quadruples.add(op, varIzq, varDer, tempAddr);
        vars.push(tempAddr);
        types.push(tipoRes);
    }
}


#line 157 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_PROGRAMA = 3,                   /* PROGRAMA  */
  YYSYMBOL_INICIO = 4,                     /* INICIO  */
  YYSYMBOL_FIN = 5,                        /* FIN  */
  YYSYMBOL_VARS = 6,                       /* VARS  */
  YYSYMBOL_NULA = 7,                       /* NULA  */
  YYSYMBOL_ENTERO = 8,                     /* ENTERO  */
  YYSYMBOL_FLOTANTE = 9,                   /* FLOTANTE  */
  YYSYMBOL_SI = 10,                        /* SI  */
  YYSYMBOL_SINO = 11,                      /* SINO  */
  YYSYMBOL_MIENTRAS = 12,                  /* MIENTRAS  */
  YYSYMBOL_HAZ = 13,                       /* HAZ  */
  YYSYMBOL_ESCRIBE = 14,                   /* ESCRIBE  */
  YYSYMBOL_REGRESA = 15,                   /* REGRESA  */
  YYSYMBOL_ASIGNACION = 16,                /* ASIGNACION  */
  YYSYMBOL_PUNTOYCOMA = 17,                /* PUNTOYCOMA  */
  YYSYMBOL_DOSPUNTOS = 18,                 /* DOSPUNTOS  */
  YYSYMBOL_COMA = 19,                      /* COMA  */
  YYSYMBOL_PARENIZQ = 20,                  /* PARENIZQ  */
  YYSYMBOL_PARENDER = 21,                  /* PARENDER  */
  YYSYMBOL_LLAVEIZQ = 22,                  /* LLAVEIZQ  */
  YYSYMBOL_LLAVEDER = 23,                  /* LLAVEDER  */
  YYSYMBOL_CORCHETEIZQ = 24,               /* CORCHETEIZQ  */
  YYSYMBOL_CORCHETEDER = 25,               /* CORCHETEDER  */
  YYSYMBOL_IGUAL = 26,                     /* IGUAL  */
  YYSYMBOL_DIFERENTE = 27,                 /* DIFERENTE  */
  YYSYMBOL_MENORQUE = 28,                  /* MENORQUE  */
  YYSYMBOL_MAYORQUE = 29,                  /* MAYORQUE  */
  YYSYMBOL_MAS = 30,                       /* MAS  */
  YYSYMBOL_MENOS = 31,                     /* MENOS  */
  YYSYMBOL_POR = 32,                       /* POR  */
  YYSYMBOL_ENTRE = 33,                     /* ENTRE  */
  YYSYMBOL_CTE_ENT = 34,                   /* CTE_ENT  */
  YYSYMBOL_CTE_FLOT = 35,                  /* CTE_FLOT  */
  YYSYMBOL_ID = 36,                        /* ID  */
  YYSYMBOL_LETRERO = 37,                   /* LETRERO  */
  YYSYMBOL_YYACCEPT = 38,                  /* $accept  */
  YYSYMBOL_programa = 39,                  /* programa  */
  YYSYMBOL_40_1 = 40,                      /* $@1  */
  YYSYMBOL_41_2 = 41,                      /* $@2  */
  YYSYMBOL_programa_p = 42,                /* programa_p  */
  YYSYMBOL_programa_pp = 43,               /* programa_pp  */
  YYSYMBOL_vars = 44,                      /* vars  */
  YYSYMBOL_vars_p = 45,                    /* vars_p  */
  YYSYMBOL_46_3 = 46,                      /* $@3  */
  YYSYMBOL_47_4 = 47,                      /* $@4  */
  YYSYMBOL_vars_pp = 48,                   /* vars_pp  */
  YYSYMBOL_49_5 = 49,                      /* $@5  */
  YYSYMBOL_tipo = 50,                      /* tipo  */
  YYSYMBOL_funcs = 51,                     /* funcs  */
  YYSYMBOL_52_6 = 52,                      /* $@6  */
  YYSYMBOL_53_7 = 53,                      /* $@7  */
  YYSYMBOL_54_8 = 54,                      /* $@8  */
  YYSYMBOL_55_9 = 55,                      /* $@9  */
  YYSYMBOL_funcs_p = 56,                   /* funcs_p  */
  YYSYMBOL_57_10 = 57,                     /* $@10  */
  YYSYMBOL_funcs_pp = 58,                  /* funcs_pp  */
  YYSYMBOL_funcs_ppp = 59,                 /* funcs_ppp  */
  YYSYMBOL_60_11 = 60,                     /* $@11  */
  YYSYMBOL_cuerpo = 61,                    /* cuerpo  */
  YYSYMBOL_cuerpo_p = 62,                  /* cuerpo_p  */
  YYSYMBOL_estatuto = 63,                  /* estatuto  */
  YYSYMBOL_estatuto_p = 64,                /* estatuto_p  */
  YYSYMBOL_asigna = 65,                    /* asigna  */
  YYSYMBOL_66_12 = 66,                     /* $@12  */
  YYSYMBOL_67_13 = 67,                     /* $@13  */
  YYSYMBOL_68_14 = 68,                     /* $@14  */
  YYSYMBOL_llamada = 69,                   /* llamada  */
  YYSYMBOL_70_15 = 70,                     /* $@15  */
  YYSYMBOL_llamada_p = 71,                 /* llamada_p  */
  YYSYMBOL_72_16 = 72,                     /* $@16  */
  YYSYMBOL_llamada_pp = 73,                /* llamada_pp  */
  YYSYMBOL_imprime = 74,                   /* imprime  */
  YYSYMBOL_imprime_p = 75,                 /* imprime_p  */
  YYSYMBOL_76_17 = 76,                     /* $@17  */
  YYSYMBOL_77_18 = 77,                     /* $@18  */
  YYSYMBOL_imprime_pp = 78,                /* imprime_pp  */
  YYSYMBOL_regresa = 79,                   /* regresa  */
  YYSYMBOL_condicion = 80,                 /* condicion  */
  YYSYMBOL_81_19 = 81,                     /* $@19  */
  YYSYMBOL_condicion_p = 82,               /* condicion_p  */
  YYSYMBOL_83_20 = 83,                     /* $@20  */
  YYSYMBOL_ciclo = 84,                     /* ciclo  */
  YYSYMBOL_85_21 = 85,                     /* $@21  */
  YYSYMBOL_86_22 = 86,                     /* $@22  */
  YYSYMBOL_87_23 = 87,                     /* $@23  */
  YYSYMBOL_expresion = 88,                 /* expresion  */
  YYSYMBOL_expresion_p = 89,               /* expresion_p  */
  YYSYMBOL_90_24 = 90,                     /* $@24  */
  YYSYMBOL_91_25 = 91,                     /* $@25  */
  YYSYMBOL_92_26 = 92,                     /* $@26  */
  YYSYMBOL_93_27 = 93,                     /* $@27  */
  YYSYMBOL_exp = 94,                       /* exp  */
  YYSYMBOL_exp_p = 95,                     /* exp_p  */
  YYSYMBOL_96_28 = 96,                     /* $@28  */
  YYSYMBOL_97_29 = 97,                     /* $@29  */
  YYSYMBOL_98_30 = 98,                     /* $@30  */
  YYSYMBOL_99_31 = 99,                     /* $@31  */
  YYSYMBOL_termino = 100,                  /* termino  */
  YYSYMBOL_termino_p = 101,                /* termino_p  */
  YYSYMBOL_102_32 = 102,                   /* $@32  */
  YYSYMBOL_103_33 = 103,                   /* $@33  */
  YYSYMBOL_104_34 = 104,                   /* $@34  */
  YYSYMBOL_105_35 = 105,                   /* $@35  */
  YYSYMBOL_factor = 106,                   /* factor  */
  YYSYMBOL_factor_p = 107,                 /* factor_p  */
  YYSYMBOL_cte = 108                       /* cte  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   172

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  71
/* YYNRULES -- Number of rules.  */
#define YYNRULES  107
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  190

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   292


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      35,    36,    37
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   112,   112,   119,   111,   134,   135,   139,   140,   144,
     149,   153,   148,   167,   172,   171,   176,   180,   181,   186,
     197,   185,   202,   216,   201,   223,   222,   227,   231,   232,
     237,   236,   241,   245,   249,   250,   254,   255,   256,   257,
     258,   259,   263,   264,   269,   276,   276,   268,   282,   281,
     304,   303,   320,   324,   325,   329,   334,   333,   339,   338,
     347,   348,   352,   360,   359,   369,   368,   381,   389,   393,
     398,   388,   408,   412,   412,   413,   413,   414,   414,   415,
     415,   416,   420,   424,   424,   424,   425,   425,   425,   426,
     430,   434,   434,   434,   435,   435,   435,   436,   440,   441,
     454,   462,   463,   464,   468,   469,   473,   480
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "PROGRAMA", "INICIO",
  "FIN", "VARS", "NULA", "ENTERO", "FLOTANTE", "SI", "SINO", "MIENTRAS",
  "HAZ", "ESCRIBE", "REGRESA", "ASIGNACION", "PUNTOYCOMA", "DOSPUNTOS",
  "COMA", "PARENIZQ", "PARENDER", "LLAVEIZQ", "LLAVEDER", "CORCHETEIZQ",
  "CORCHETEDER", "IGUAL", "DIFERENTE", "MENORQUE", "MAYORQUE", "MAS",
  "MENOS", "POR", "ENTRE", "CTE_ENT", "CTE_FLOT", "ID", "LETRERO",
  "$accept", "programa", "$@1", "$@2", "programa_p", "programa_pp", "vars",
  "vars_p", "$@3", "$@4", "vars_pp", "$@5", "tipo", "funcs", "$@6", "$@7",
  "$@8", "$@9", "funcs_p", "$@10", "funcs_pp", "funcs_ppp", "$@11",
  "cuerpo", "cuerpo_p", "estatuto", "estatuto_p", "asigna", "$@12", "$@13",
  "$@14", "llamada", "$@15", "llamada_p", "$@16", "llamada_pp", "imprime",
  "imprime_p", "$@17", "$@18", "imprime_pp", "regresa", "condicion",
  "$@19", "condicion_p", "$@20", "ciclo", "$@21", "$@22", "$@23",
  "expresion", "expresion_p", "$@24", "$@25", "$@26", "$@27", "exp",
  "exp_p", "$@28", "$@29", "$@30", "$@31", "termino", "termino_p", "$@32",
  "$@33", "$@34", "$@35", "factor", "factor_p", "cte", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-121)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-49)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       4,   -27,    14,     5,  -121,  -121,    18,    -3,    10,  -121,
    -121,  -121,    12,  -121,  -121,    40,    23,    10,    56,  -121,
    -121,  -121,  -121,    41,    58,    59,    60,    61,  -121,     3,
      42,    -4,    75,    42,    56,    66,    67,    63,    68,  -121,
      69,    -4,    70,    64,    -4,  -121,    74,  -121,  -121,  -121,
    -121,    65,  -121,  -121,     3,  -121,    15,    72,     6,    -4,
      71,    77,    78,  -121,  -121,  -121,  -121,    -3,  -121,    73,
      15,    -6,    -6,  -121,  -121,    70,  -121,    76,    29,     8,
      20,  -121,    15,  -121,    79,  -121,  -121,  -121,  -121,    15,
      80,  -121,    84,    18,    83,  -121,  -121,  -121,  -121,  -121,
    -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,
    -121,    85,    86,    82,    86,    15,    87,  -121,    18,    81,
    -121,  -121,    60,  -121,    60,    15,    15,    15,    15,    15,
      15,    15,    15,  -121,     6,  -121,  -121,  -121,  -121,  -121,
      88,    60,    91,    89,    99,  -121,  -121,  -121,  -121,  -121,
    -121,  -121,  -121,    98,  -121,    96,    15,  -121,   101,     3,
      97,  -121,   102,     8,     8,    20,    20,    60,  -121,  -121,
      15,    95,  -121,  -121,    60,  -121,  -121,  -121,  -121,  -121,
    -121,   103,   104,    84,  -121,   105,  -121,  -121,  -121,  -121
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     2,     6,    13,     8,     5,
      10,     9,     0,    17,    18,     0,     0,     8,    16,    19,
       3,    22,     7,     0,     0,     0,     0,     0,    14,     0,
      27,    35,     0,    27,    16,     0,     0,     0,     0,    68,
       0,    43,    44,     0,    35,    36,     0,    40,    37,    38,
       4,     0,    15,    11,     0,    20,     0,     0,     0,    43,
       0,     0,     0,    33,    34,    39,    23,    13,    25,     0,
       0,     0,     0,   106,   107,   100,    99,     0,    81,    89,
      97,   101,     0,    58,     0,    56,    42,    41,    45,    52,
       0,    12,    32,    29,     0,   104,   102,   105,   103,    63,
      79,    77,    75,    73,    72,    83,    86,    82,    91,    94,
      90,     0,    61,     0,    61,     0,     0,    50,    29,     0,
      26,    28,     0,    98,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    69,     0,    59,    55,    57,    46,    49,
      54,     0,     0,     0,    67,    80,    78,    76,    74,    84,
      87,    92,    95,     0,    60,     0,    52,    51,     0,     0,
       0,    65,     0,    89,    89,    97,    97,     0,    47,    53,
       0,     0,    30,    21,     0,    64,    85,    88,    93,    96,
      70,     0,     0,    32,    66,     0,    62,    24,    31,    71
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -121,  -121,  -121,  -121,  -121,   106,   118,    27,  -121,  -121,
      92,  -121,   -29,  -121,  -121,  -121,  -121,  -121,    94,  -121,
       7,   -54,  -121,  -120,    90,   -36,    93,  -121,  -121,  -121,
    -121,   -28,  -121,   -25,  -121,  -121,  -121,    -2,  -121,  -121,
      19,  -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,
     -55,  -121,  -121,  -121,  -121,  -121,   -64,   -98,  -121,  -121,
    -121,  -121,   -62,   -96,  -121,  -121,  -121,  -121,   -60,   100,
       2
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     6,    26,     8,    15,   121,    11,    18,    67,
      24,    34,    16,    17,    25,    69,    27,    90,    37,    92,
     122,   120,   183,    32,    43,    44,    60,    45,    61,   115,
     155,    76,    62,   116,   140,   157,    47,    84,   114,   112,
     135,   171,    48,   124,   162,   174,    49,    57,   153,   185,
      85,   104,   128,   127,   126,   125,    78,   107,   129,   163,
     130,   164,    79,   110,   131,   165,   132,   166,    80,    96,
      81
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      35,    77,   143,    46,   144,    59,    38,     1,    39,     3,
      40,    13,    14,    46,     4,    94,    46,    12,    13,    14,
      41,   158,     5,    59,     7,    68,    70,   111,    73,    74,
      95,    46,    42,    10,   117,    70,    71,    72,   105,   106,
      73,    74,    75,    83,    20,    71,    72,   180,    19,    73,
      74,    75,   108,   109,   184,   100,   101,   102,   103,    21,
     138,   145,   146,   147,   148,   176,   177,   149,   150,   178,
     179,   151,   152,    97,    97,    23,    29,    28,    36,    30,
      50,    33,    31,    53,    55,    54,    66,    63,    56,    58,
     -48,    65,    82,    88,    91,    93,    87,    99,    89,   136,
     113,   117,   118,   119,   123,   134,   133,   156,   139,   159,
     161,   167,   160,   168,   173,   181,   170,   142,   182,   175,
     186,   187,   189,    22,     9,   141,    52,    51,     0,   188,
     172,   169,   154,   137,    64,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    86,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    98
};

static const yytype_int16 yycheck[] =
{
      29,    56,   122,    31,   124,    41,    10,     3,    12,    36,
      14,     8,     9,    41,     0,    70,    44,     7,     8,     9,
      24,   141,    17,    59,     6,    54,    20,    82,    34,    35,
      36,    59,    36,    36,    89,    20,    30,    31,    30,    31,
      34,    35,    36,    37,     4,    30,    31,   167,    36,    34,
      35,    36,    32,    33,   174,    26,    27,    28,    29,    36,
     115,   125,   126,   127,   128,   163,   164,   129,   130,   165,
     166,   131,   132,    71,    72,    19,    18,    36,    36,    20,
       5,    20,    22,    17,    21,    18,    21,    23,    20,    20,
      20,    17,    20,    16,    67,    22,    25,    21,    20,    17,
      21,   156,    22,    19,    21,    19,    21,    19,    21,    18,
      11,    13,    23,    17,    17,   170,    15,    36,    23,    17,
      17,    17,    17,    17,     6,   118,    34,    33,    -1,   183,
     159,   156,   134,   114,    44,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    72
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    39,    36,     0,    17,    40,     6,    42,    44,
      36,    45,     7,     8,     9,    43,    50,    51,    46,    36,
       4,    36,    43,    19,    48,    52,    41,    54,    36,    18,
      20,    22,    61,    20,    49,    50,    36,    56,    10,    12,
      14,    24,    36,    62,    63,    65,    69,    74,    80,    84,
       5,    56,    48,    17,    18,    21,    20,    85,    20,    63,
      64,    66,    70,    23,    62,    17,    21,    47,    50,    53,
      20,    30,    31,    34,    35,    36,    69,    88,    94,   100,
     106,   108,    20,    37,    75,    88,    64,    25,    16,    20,
      55,    45,    57,    22,    88,    36,   107,   108,   107,    21,
      26,    27,    28,    29,    89,    30,    31,    95,    32,    33,
     101,    88,    77,    21,    76,    67,    71,    88,    22,    19,
      59,    44,    58,    21,    81,    93,    92,    91,    90,    96,
      98,   102,   104,    21,    19,    78,    17,    78,    88,    21,
      72,    58,    36,    61,    61,    94,    94,    94,    94,   100,
     100,   106,   106,    86,    75,    68,    19,    73,    61,    18,
      23,    11,    82,    97,    99,   103,   105,    13,    17,    71,
      15,    79,    50,    17,    83,    17,    95,    95,   101,   101,
      61,    88,    23,    60,    61,    87,    17,    17,    59,    17
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    38,    40,    41,    39,    42,    42,    43,    43,    44,
      46,    47,    45,    45,    49,    48,    48,    50,    50,    52,
      53,    51,    54,    55,    51,    57,    56,    56,    58,    58,
      60,    59,    59,    61,    62,    62,    63,    63,    63,    63,
      63,    63,    64,    64,    66,    67,    68,    65,    70,    69,
      72,    71,    71,    73,    73,    74,    76,    75,    77,    75,
      78,    78,    79,    81,    80,    83,    82,    82,    85,    86,
      87,    84,    88,    90,    89,    91,    89,    92,    89,    93,
      89,    89,    94,    96,    97,    95,    98,    99,    95,    95,
     100,   102,   103,   101,   104,   105,   101,   101,   106,   106,
     106,   106,   106,   106,   107,   107,   108,   108
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     0,    10,     1,     0,     2,     0,     2,
       0,     0,     8,     0,     0,     4,     0,     1,     1,     0,
       0,    12,     0,     0,    13,     0,     5,     0,     1,     0,
       0,     6,     0,     3,     2,     0,     1,     1,     1,     2,
       1,     3,     2,     0,     0,     0,     0,     7,     0,     5,
       0,     3,     0,     2,     0,     5,     0,     3,     0,     3,
       2,     0,     3,     0,     8,     0,     3,     0,     0,     0,
       0,    10,     2,     0,     3,     0,     3,     0,     3,     0,
       3,     0,     2,     0,     0,     5,     0,     0,     5,     0,
       2,     0,     0,     5,     0,     0,     5,     0,     3,     1,
       1,     1,     2,     2,     1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* $@1: %empty  */
#line 112 "parser.y"
    {
        dirFunc.insert("global", FuncEntry("nula"));
        scopeActual = "global";
        jumps.push(quadruples.nextQuad());
        quadruples.add("GOTO", "_", "_", "_");
    }
#line 1393 "parser.tab.c"
    break;

  case 3: /* $@2: %empty  */
#line 119 "parser.y"
    {
        quadruples.fillQuad(jumps.getTop(), to_string(quadruples.nextQuad()));
        jumps.pop();
    }
#line 1402 "parser.tab.c"
    break;

  case 4: /* programa: PROGRAMA ID PUNTOYCOMA $@1 programa_p programa_pp INICIO $@2 cuerpo FIN  */
#line 124 "parser.y"
    {
        FuncEntry& g = dirFunc.get("global");
        g.tempIntCount   = memory.tempIntCount();
        g.tempFloatCount = memory.tempFloatCount();
        quadruples.add("END", "_", "_", "_");
        // cout << "Programa válido!" << endl;
    }
#line 1414 "parser.tab.c"
    break;

  case 10: /* $@3: %empty  */
#line 149 "parser.y"
    {
        idStack.push_back((yyvsp[0].sval));
    }
#line 1422 "parser.tab.c"
    break;

  case 11: /* $@4: %empty  */
#line 153 "parser.y"
    {
        string tipVar = (yyvsp[-1].sval);
        for (auto& id : idStack) {
            try {
                int addr = memory.getAddress(scopeActual, tipVar);
                dirFunc.get(scopeActual).varTable.vars.insert(id, VarInfo(tipVar, addr));
            } catch (runtime_error&) {
                yyerror("Variable doblemente declarada");
                YYABORT;
            }
        }
        idStack.clear();
    }
#line 1440 "parser.tab.c"
    break;

  case 14: /* $@5: %empty  */
#line 172 "parser.y"
    {
        idStack.push_back((yyvsp[0].sval));
    }
#line 1448 "parser.tab.c"
    break;

  case 17: /* tipo: ENTERO  */
#line 180 "parser.y"
             { (yyval.sval) = strdup("entero"); }
#line 1454 "parser.tab.c"
    break;

  case 18: /* tipo: FLOTANTE  */
#line 181 "parser.y"
               { (yyval.sval) = strdup("flotante"); }
#line 1460 "parser.tab.c"
    break;

  case 19: /* $@6: %empty  */
#line 186 "parser.y"
    {
        string funcName = (yyvsp[0].sval);
        try {
            dirFunc.insert(funcName, FuncEntry("nula"));
        } catch (runtime_error&) {
            yyerror("Función doblemente declarada");
            YYABORT;
        }
        scopeActual = funcName;
    }
#line 1475 "parser.tab.c"
    break;

  case 20: /* $@7: %empty  */
#line 197 "parser.y"
    { dirFunc.get(scopeActual).startQuad = quadruples.nextQuad(); }
#line 1481 "parser.tab.c"
    break;

  case 21: /* funcs: NULA ID $@6 PARENIZQ funcs_p PARENDER $@7 LLAVEIZQ funcs_pp cuerpo LLAVEDER PUNTOYCOMA  */
#line 199 "parser.y"
    { finalizeFunc(); }
#line 1487 "parser.tab.c"
    break;

  case 22: /* $@8: %empty  */
#line 202 "parser.y"
    {
        string tipoReturn = (yyvsp[-1].sval);
        string funcName = (yyvsp[0].sval);
        try {
            dirFunc.insert(funcName, FuncEntry(tipoReturn));
        } catch (runtime_error&) {
            yyerror("Función doblemente declarada");
            YYABORT;
        }
        int retAddr = memory.getAddress("global", tipoReturn);
        dirFunc.get(funcName).returnAddress = retAddr;
        scopeActual = funcName;
    }
#line 1505 "parser.tab.c"
    break;

  case 23: /* $@9: %empty  */
#line 216 "parser.y"
    { dirFunc.get(scopeActual).startQuad = quadruples.nextQuad(); }
#line 1511 "parser.tab.c"
    break;

  case 24: /* funcs: tipo ID $@8 PARENIZQ funcs_p PARENDER $@9 LLAVEIZQ funcs_pp cuerpo regresa LLAVEDER PUNTOYCOMA  */
#line 218 "parser.y"
    { finalizeFunc(); }
#line 1517 "parser.tab.c"
    break;

  case 25: /* $@10: %empty  */
#line 223 "parser.y"
    {
        registerParam((yyvsp[-2].sval), (yyvsp[0].sval));
    }
#line 1525 "parser.tab.c"
    break;

  case 30: /* $@11: %empty  */
#line 237 "parser.y"
    {
        registerParam((yyvsp[-2].sval), (yyvsp[0].sval));
    }
#line 1533 "parser.tab.c"
    break;

  case 44: /* $@12: %empty  */
#line 269 "parser.y"
    {   
        VarInfo info;
        try { info = lookupVar((yyvsp[0].sval)); }
        catch (runtime_error& e) { yyerror(e.what()); YYABORT; }
        vars.push(to_string(info.address));
        types.push(info.tipo);
    }
#line 1545 "parser.tab.c"
    break;

  case 45: /* $@13: %empty  */
#line 276 "parser.y"
               { operators.push("=");}
#line 1551 "parser.tab.c"
    break;

  case 46: /* $@14: %empty  */
#line 276 "parser.y"
                                                 { makeQuadruple(); }
#line 1557 "parser.tab.c"
    break;

  case 48: /* $@15: %empty  */
#line 282 "parser.y"
    {
        if (!dirFunc.contains((yyvsp[0].sval))) {
            yyerror(("Función no declarada: " + string((yyvsp[0].sval))).c_str());
            YYABORT;
        }
        callTarget = (yyvsp[0].sval);
        paramCount = 0;
        quadruples.add("ERA", "_", "_", (yyvsp[0].sval));
    }
#line 1571 "parser.tab.c"
    break;

  case 49: /* llamada: ID $@15 PARENIZQ llamada_p PARENDER  */
#line 292 "parser.y"
    {
        int expected = dirFunc.get(callTarget).params.size();
        if (paramCount != expected) {
            yyerror("Número incorrecto de parámetros");
            YYABORT;
        }
        quadruples.add("GOSUB", "_", "_", to_string(dirFunc.get(callTarget).startQuad));
    }
#line 1584 "parser.tab.c"
    break;

  case 50: /* $@16: %empty  */
#line 304 "parser.y"
    {
        auto& params = dirFunc.get(callTarget).params;
        if (paramCount >= (int)params.size()) {
            yyerror("Demasiados parámetros");
            YYABORT;
        }
        string argVal  = vars.getTop();  vars.pop();
        string argTipo = types.getTop(); types.pop();
        if (argTipo != params[paramCount].tipo) {
            yyerror(("Tipo incorrecto en parámetro " + to_string(paramCount + 1)).c_str());
            YYABORT;
        }
        quadruples.add("PARAM", argVal, "_", to_string(params[paramCount].address));
        paramCount++;
    }
#line 1604 "parser.tab.c"
    break;

  case 56: /* $@17: %empty  */
#line 334 "parser.y"
    {
        quadruples.add("PRINT", popExpr(), "_", "_");
    }
#line 1612 "parser.tab.c"
    break;

  case 58: /* $@18: %empty  */
#line 339 "parser.y"
    {
        int addr = memory.getConstAddress("string", (yyvsp[0].sval));
        quadruples.add("PRINT", to_string(addr), "_", "_");
    }
#line 1621 "parser.tab.c"
    break;

  case 62: /* regresa: REGRESA expresion PUNTOYCOMA  */
#line 353 "parser.y"
    {
        quadruples.add("RETURN", popExpr(), "_", scopeActual);
    }
#line 1629 "parser.tab.c"
    break;

  case 63: /* $@19: %empty  */
#line 360 "parser.y"
    {
        jumps.push(quadruples.nextQuad());
        quadruples.add("GOTOF", popExpr(), "_", "_");
    }
#line 1638 "parser.tab.c"
    break;

  case 65: /* $@20: %empty  */
#line 369 "parser.y"
    {
        int falseJump = jumps.getTop(); jumps.pop();
        jumps.push(quadruples.nextQuad());
        quadruples.add("GOTO", "_", "_", "_");
        quadruples.fillQuad(falseJump, to_string(quadruples.nextQuad()));
    }
#line 1649 "parser.tab.c"
    break;

  case 66: /* condicion_p: SINO $@20 cuerpo  */
#line 376 "parser.y"
    {
        int endJump = jumps.getTop(); jumps.pop();
        quadruples.fillQuad(endJump, to_string(quadruples.nextQuad()));
    }
#line 1658 "parser.tab.c"
    break;

  case 67: /* condicion_p: %empty  */
#line 381 "parser.y"
    {
        int falseJump = jumps.getTop(); jumps.pop();
        quadruples.fillQuad(falseJump, to_string(quadruples.nextQuad()));
    }
#line 1667 "parser.tab.c"
    break;

  case 68: /* $@21: %empty  */
#line 389 "parser.y"
    {
        jumps.push(quadruples.nextQuad());
    }
#line 1675 "parser.tab.c"
    break;

  case 69: /* $@22: %empty  */
#line 393 "parser.y"
    {
        jumps.push(quadruples.nextQuad());
        quadruples.add("GOTOF", popExpr(), "_", "_");
    }
#line 1684 "parser.tab.c"
    break;

  case 70: /* $@23: %empty  */
#line 398 "parser.y"
    {
        int falseJump = jumps.getTop(); jumps.pop();
        int loopStart = jumps.getTop(); jumps.pop();
        quadruples.add("GOTO", "_", "_", to_string(loopStart));
        quadruples.fillQuad(falseJump, to_string(quadruples.nextQuad()));
    }
#line 1695 "parser.tab.c"
    break;

  case 73: /* $@24: %empty  */
#line 412 "parser.y"
             { operators.push(">");}
#line 1701 "parser.tab.c"
    break;

  case 74: /* expresion_p: MAYORQUE $@24 exp  */
#line 412 "parser.y"
                                         { makeQuadruple();}
#line 1707 "parser.tab.c"
    break;

  case 75: /* $@25: %empty  */
#line 413 "parser.y"
               { operators.push("<");}
#line 1713 "parser.tab.c"
    break;

  case 76: /* expresion_p: MENORQUE $@25 exp  */
#line 413 "parser.y"
                                           { makeQuadruple();}
#line 1719 "parser.tab.c"
    break;

  case 77: /* $@26: %empty  */
#line 414 "parser.y"
                { operators.push("!=");}
#line 1725 "parser.tab.c"
    break;

  case 78: /* expresion_p: DIFERENTE $@26 exp  */
#line 414 "parser.y"
                                              { makeQuadruple();}
#line 1731 "parser.tab.c"
    break;

  case 79: /* $@27: %empty  */
#line 415 "parser.y"
            { operators.push("==");}
#line 1737 "parser.tab.c"
    break;

  case 80: /* expresion_p: IGUAL $@27 exp  */
#line 415 "parser.y"
                                         { makeQuadruple();}
#line 1743 "parser.tab.c"
    break;

  case 83: /* $@28: %empty  */
#line 424 "parser.y"
        { operators.push("+");}
#line 1749 "parser.tab.c"
    break;

  case 84: /* $@29: %empty  */
#line 424 "parser.y"
                                        { makeQuadruple();}
#line 1755 "parser.tab.c"
    break;

  case 86: /* $@30: %empty  */
#line 425 "parser.y"
             { operators.push("-");}
#line 1761 "parser.tab.c"
    break;

  case 87: /* $@31: %empty  */
#line 425 "parser.y"
                                              { makeQuadruple();}
#line 1767 "parser.tab.c"
    break;

  case 91: /* $@32: %empty  */
#line 434 "parser.y"
         { operators.push("*");}
#line 1773 "parser.tab.c"
    break;

  case 92: /* $@33: %empty  */
#line 434 "parser.y"
                                         { makeQuadruple();}
#line 1779 "parser.tab.c"
    break;

  case 94: /* $@34: %empty  */
#line 435 "parser.y"
             { operators.push("/");}
#line 1785 "parser.tab.c"
    break;

  case 95: /* $@35: %empty  */
#line 435 "parser.y"
                                            { makeQuadruple();}
#line 1791 "parser.tab.c"
    break;

  case 99: /* factor: llamada  */
#line 442 "parser.y"
    {
        string tipoReturn = dirFunc.get(callTarget).tipo;
        if(tipoReturn == "nula"){
            yyerror("No se puede usar una funcion void en una expresion");
            YYABORT;
        }
        int returnAddr = dirFunc.get(callTarget).returnAddress;
        int tempAddr = memory.getTempAddress(tipoReturn);
        quadruples.add("=", to_string(returnAddr), "_", to_string(tempAddr));
        vars.push(to_string(tempAddr));
        types.push(tipoReturn);
    }
#line 1808 "parser.tab.c"
    break;

  case 100: /* factor: ID  */
#line 455 "parser.y"
    {
        VarInfo info;
        try { info = lookupVar((yyvsp[0].sval)); }
        catch (runtime_error& e) { yyerror(e.what()); YYABORT; }
        vars.push(to_string(info.address));
        types.push(info.tipo);
    }
#line 1820 "parser.tab.c"
    break;

  case 106: /* cte: CTE_ENT  */
#line 474 "parser.y"
    {
        int valor = (yyvsp[0].ival);
        int addr = memory.getConstAddress("entero", to_string(valor));
        vars.push(to_string(addr));
        types.push("entero");
    }
#line 1831 "parser.tab.c"
    break;

  case 107: /* cte: CTE_FLOT  */
#line 481 "parser.y"
    {
        float valor = (yyvsp[0].fval);
        int addr = memory.getConstAddress("flotante", to_string(valor));
        vars.push(to_string(addr));
        types.push("flotante");
    }
#line 1842 "parser.tab.c"
    break;


#line 1846 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 489 "parser.y"
