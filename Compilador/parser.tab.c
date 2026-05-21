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
#include "FuncDir.h"
#include "SemanticCube.h"
#include "QuadrupleBuilder.h"
#include "Stack.h"
using namespace std;

void yyerror(const char* s) {
    cerr << "Error sintáctico: " << s << endl;
}
int yylex();

SemanticCube cube;

Stack<string> operators;
Stack<string> vars;
Stack<string> types;
QuadrupleBuilder quadruples;

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
        string tempNum = quadruples.newTemp(); // numero de temporal "t1, t2, etc."
        quadruples.add(op,varIzq, varDer, tempNum);
        vars.push(tempNum);
        types.push(tipoRes);
    }
}


#line 116 "parser.tab.c"

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
  YYSYMBOL_ASIGNACION = 15,                /* ASIGNACION  */
  YYSYMBOL_PUNTOYCOMA = 16,                /* PUNTOYCOMA  */
  YYSYMBOL_DOSPUNTOS = 17,                 /* DOSPUNTOS  */
  YYSYMBOL_COMA = 18,                      /* COMA  */
  YYSYMBOL_PARENIZQ = 19,                  /* PARENIZQ  */
  YYSYMBOL_PARENDER = 20,                  /* PARENDER  */
  YYSYMBOL_LLAVEIZQ = 21,                  /* LLAVEIZQ  */
  YYSYMBOL_LLAVEDER = 22,                  /* LLAVEDER  */
  YYSYMBOL_CORCHETEIZQ = 23,               /* CORCHETEIZQ  */
  YYSYMBOL_CORCHETEDER = 24,               /* CORCHETEDER  */
  YYSYMBOL_IGUAL = 25,                     /* IGUAL  */
  YYSYMBOL_DIFERENTE = 26,                 /* DIFERENTE  */
  YYSYMBOL_MENORQUE = 27,                  /* MENORQUE  */
  YYSYMBOL_MAYORQUE = 28,                  /* MAYORQUE  */
  YYSYMBOL_MAS = 29,                       /* MAS  */
  YYSYMBOL_MENOS = 30,                     /* MENOS  */
  YYSYMBOL_POR = 31,                       /* POR  */
  YYSYMBOL_ENTRE = 32,                     /* ENTRE  */
  YYSYMBOL_CTE_ENT = 33,                   /* CTE_ENT  */
  YYSYMBOL_CTE_FLOT = 34,                  /* CTE_FLOT  */
  YYSYMBOL_ID = 35,                        /* ID  */
  YYSYMBOL_LETRERO = 36,                   /* LETRERO  */
  YYSYMBOL_YYACCEPT = 37,                  /* $accept  */
  YYSYMBOL_programa = 38,                  /* programa  */
  YYSYMBOL_39_1 = 39,                      /* $@1  */
  YYSYMBOL_programa_p = 40,                /* programa_p  */
  YYSYMBOL_programa_pp = 41,               /* programa_pp  */
  YYSYMBOL_vars = 42,                      /* vars  */
  YYSYMBOL_vars_p = 43,                    /* vars_p  */
  YYSYMBOL_44_2 = 44,                      /* $@2  */
  YYSYMBOL_45_3 = 45,                      /* $@3  */
  YYSYMBOL_vars_pp = 46,                   /* vars_pp  */
  YYSYMBOL_47_4 = 47,                      /* $@4  */
  YYSYMBOL_tipo = 48,                      /* tipo  */
  YYSYMBOL_funcs = 49,                     /* funcs  */
  YYSYMBOL_50_5 = 50,                      /* $@5  */
  YYSYMBOL_51_6 = 51,                      /* $@6  */
  YYSYMBOL_funcs_p = 52,                   /* funcs_p  */
  YYSYMBOL_funcs_pp = 53,                  /* funcs_pp  */
  YYSYMBOL_funcs_ppp = 54,                 /* funcs_ppp  */
  YYSYMBOL_cuerpo = 55,                    /* cuerpo  */
  YYSYMBOL_cuerpo_p = 56,                  /* cuerpo_p  */
  YYSYMBOL_estatuto = 57,                  /* estatuto  */
  YYSYMBOL_estatuto_p = 58,                /* estatuto_p  */
  YYSYMBOL_asigna = 59,                    /* asigna  */
  YYSYMBOL_60_7 = 60,                      /* $@7  */
  YYSYMBOL_61_8 = 61,                      /* $@8  */
  YYSYMBOL_62_9 = 62,                      /* $@9  */
  YYSYMBOL_llamada = 63,                   /* llamada  */
  YYSYMBOL_llamada_p = 64,                 /* llamada_p  */
  YYSYMBOL_llamada_pp = 65,                /* llamada_pp  */
  YYSYMBOL_imprime = 66,                   /* imprime  */
  YYSYMBOL_imprime_p = 67,                 /* imprime_p  */
  YYSYMBOL_68_10 = 68,                     /* $@10  */
  YYSYMBOL_69_11 = 69,                     /* $@11  */
  YYSYMBOL_imprime_pp = 70,                /* imprime_pp  */
  YYSYMBOL_condicion = 71,                 /* condicion  */
  YYSYMBOL_condicion_p = 72,               /* condicion_p  */
  YYSYMBOL_ciclo = 73,                     /* ciclo  */
  YYSYMBOL_expresion = 74,                 /* expresion  */
  YYSYMBOL_expresion_p = 75,               /* expresion_p  */
  YYSYMBOL_76_12 = 76,                     /* $@12  */
  YYSYMBOL_77_13 = 77,                     /* $@13  */
  YYSYMBOL_78_14 = 78,                     /* $@14  */
  YYSYMBOL_79_15 = 79,                     /* $@15  */
  YYSYMBOL_exp = 80,                       /* exp  */
  YYSYMBOL_exp_p = 81,                     /* exp_p  */
  YYSYMBOL_82_16 = 82,                     /* $@16  */
  YYSYMBOL_83_17 = 83,                     /* $@17  */
  YYSYMBOL_84_18 = 84,                     /* $@18  */
  YYSYMBOL_85_19 = 85,                     /* $@19  */
  YYSYMBOL_termino = 86,                   /* termino  */
  YYSYMBOL_termino_p = 87,                 /* termino_p  */
  YYSYMBOL_88_20 = 88,                     /* $@20  */
  YYSYMBOL_89_21 = 89,                     /* $@21  */
  YYSYMBOL_90_22 = 90,                     /* $@22  */
  YYSYMBOL_91_23 = 91,                     /* $@23  */
  YYSYMBOL_factor = 92,                    /* factor  */
  YYSYMBOL_factor_p = 93,                  /* factor_p  */
  YYSYMBOL_cte = 94                        /* cte  */
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
#define YYLAST   153

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  58
/* YYNRULES -- Number of rules.  */
#define YYNRULES  93
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  174

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   291


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
      35,    36
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    71,    71,    70,    80,    81,    85,    86,    90,    95,
      99,    94,   113,   118,   117,   122,   126,   127,   132,   131,
     145,   144,   159,   160,   164,   165,   169,   170,   174,   178,
     179,   183,   184,   185,   186,   187,   188,   192,   193,   198,
     203,   203,   197,   208,   212,   213,   217,   221,   226,   225,
     233,   232,   240,   241,   245,   249,   250,   254,   258,   262,
     262,   263,   263,   264,   264,   265,   265,   266,   270,   274,
     274,   274,   275,   275,   275,   276,   280,   284,   284,   284,
     285,   285,   285,   286,   290,   291,   292,   298,   299,   300,
     304,   305,   309,   314
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
  "HAZ", "ESCRIBE", "ASIGNACION", "PUNTOYCOMA", "DOSPUNTOS", "COMA",
  "PARENIZQ", "PARENDER", "LLAVEIZQ", "LLAVEDER", "CORCHETEIZQ",
  "CORCHETEDER", "IGUAL", "DIFERENTE", "MENORQUE", "MAYORQUE", "MAS",
  "MENOS", "POR", "ENTRE", "CTE_ENT", "CTE_FLOT", "ID", "LETRERO",
  "$accept", "programa", "$@1", "programa_p", "programa_pp", "vars",
  "vars_p", "$@2", "$@3", "vars_pp", "$@4", "tipo", "funcs", "$@5", "$@6",
  "funcs_p", "funcs_pp", "funcs_ppp", "cuerpo", "cuerpo_p", "estatuto",
  "estatuto_p", "asigna", "$@7", "$@8", "$@9", "llamada", "llamada_p",
  "llamada_pp", "imprime", "imprime_p", "$@10", "$@11", "imprime_pp",
  "condicion", "condicion_p", "ciclo", "expresion", "expresion_p", "$@12",
  "$@13", "$@14", "$@15", "exp", "exp_p", "$@16", "$@17", "$@18", "$@19",
  "termino", "termino_p", "$@20", "$@21", "$@22", "$@23", "factor",
  "factor_p", "cte", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-104)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       1,   -27,    10,    -4,  -104,  -104,    21,   -20,    22,  -104,
    -104,  -104,     0,  -104,  -104,    34,    29,    22,    27,  -104,
      56,  -104,  -104,    43,    62,    61,    -1,    76,    63,  -104,
      15,    48,    65,    66,    67,    -1,    68,    69,    -1,  -104,
      72,  -104,  -104,  -104,  -104,    48,    27,    73,    75,    70,
      25,    25,     7,    -1,    71,    25,    78,  -104,  -104,  -104,
      74,  -104,  -104,    15,    77,    25,    33,    33,  -104,  -104,
      68,  -104,    79,    -7,    18,    30,  -104,    80,  -104,    81,
    -104,  -104,  -104,    82,    85,  -104,    83,   -20,    87,    21,
      86,  -104,  -104,  -104,  -104,    56,  -104,  -104,  -104,  -104,
    -104,  -104,  -104,  -104,  -104,  -104,  -104,    84,    89,    92,
      89,  -104,    25,  -104,    25,    21,  -104,    88,  -104,  -104,
      56,  -104,    98,    25,    25,    25,    25,    25,    25,    25,
      25,    56,     7,  -104,  -104,  -104,  -104,  -104,    56,    93,
      90,    56,    95,  -104,  -104,  -104,  -104,  -104,  -104,  -104,
    -104,    97,  -104,    99,    94,    15,   101,  -104,  -104,    18,
      18,    30,    30,  -104,  -104,   102,    87,  -104,  -104,  -104,
    -104,  -104,  -104,  -104
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     2,     5,    12,     7,     4,
       9,     8,     0,    16,    17,     0,     0,     7,    15,    18,
       0,    20,     6,     0,     0,     0,    30,     0,     0,    13,
       0,    23,     0,     0,     0,    38,    39,     0,    30,    31,
       0,    35,    32,    33,     3,    23,    15,     0,     0,     0,
       0,     0,     0,    38,     0,    45,     0,    28,    29,    34,
       0,    14,    10,     0,     0,     0,     0,     0,    92,    93,
      86,    85,     0,    67,    75,    83,    87,     0,    50,     0,
      48,    37,    36,     0,     0,    40,     0,    12,    27,    25,
       0,    90,    88,    91,    89,     0,    65,    63,    61,    59,
      58,    69,    72,    68,    77,    80,    76,     0,    53,     0,
      53,    43,    45,    44,     0,    25,    11,     0,    22,    24,
       0,    84,    56,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    51,    47,    49,    46,    41,     0,     0,
       0,     0,     0,    66,    64,    62,    60,    70,    73,    78,
      81,     0,    52,     0,     0,     0,     0,    55,    54,    75,
      75,    83,    83,    57,    42,     0,    27,    19,    71,    74,
      79,    82,    21,    26
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -104,  -104,  -104,  -104,   103,   108,    32,  -104,  -104,    50,
    -104,   -30,  -104,  -104,  -104,    91,     6,   -44,   -92,    96,
     -28,   100,  -104,  -104,  -104,  -104,   -21,    12,  -104,  -104,
      -6,  -104,  -104,    17,  -104,  -104,  -104,   -49,  -104,  -104,
    -104,  -104,  -104,   -73,  -103,  -104,  -104,  -104,  -104,   -58,
     -90,  -104,  -104,  -104,  -104,   -56,    64,     9
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     6,     8,    15,   119,    11,    18,    87,    24,
      46,    16,    17,    25,    28,    49,   120,   118,    27,    37,
      38,    54,    39,    56,   114,   153,    71,    83,   113,    41,
      79,   110,   108,   133,    42,   142,    43,    80,   100,   126,
     125,   124,   123,    73,   103,   127,   159,   128,   160,    74,
     106,   129,   161,   130,   162,    75,    92,    76
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      47,    72,    77,   122,     1,    40,    84,    53,     3,    32,
       4,    33,     5,    34,    40,    10,    90,    40,    96,    97,
      98,    99,    35,    13,    14,    53,    65,     7,   140,    12,
      13,    14,    40,    88,    36,    19,    66,    67,    20,   151,
      68,    69,    70,    78,    65,    23,   154,   101,   102,   157,
     143,   144,   145,   146,    66,    67,   168,   169,    68,    69,
      70,   104,   105,    84,    21,   137,    68,    69,    91,   147,
     148,   170,   171,   149,   150,    93,    93,    26,    29,    30,
      31,    44,    45,    48,    50,    51,    52,    55,    59,    62,
      64,    57,    63,    85,    86,    82,    61,   131,    89,    95,
     107,   109,   111,   112,   115,   117,   121,   132,   134,   141,
     155,   158,   156,   163,     9,   164,   165,   167,   172,   116,
      22,   138,   173,   139,   136,   166,   152,   135,     0,     0,
       0,    94,     0,     0,    58,     0,    60,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    81
};

static const yytype_int16 yycheck[] =
{
      30,    50,    51,    95,     3,    26,    55,    35,    35,    10,
       0,    12,    16,    14,    35,    35,    65,    38,    25,    26,
      27,    28,    23,     8,     9,    53,    19,     6,   120,     7,
       8,     9,    53,    63,    35,    35,    29,    30,     4,   131,
      33,    34,    35,    36,    19,    18,   138,    29,    30,   141,
     123,   124,   125,   126,    29,    30,   159,   160,    33,    34,
      35,    31,    32,   112,    35,   114,    33,    34,    35,   127,
     128,   161,   162,   129,   130,    66,    67,    21,    35,    17,
      19,     5,    19,    35,    19,    19,    19,    19,    16,    16,
      20,    22,    17,    15,    20,    24,    46,    13,    21,    20,
      20,    20,    20,    18,    21,    18,    20,    18,    16,    11,
      17,    16,    22,    16,     6,    16,    22,    16,    16,    87,
      17,   115,   166,    35,   112,   155,   132,   110,    -1,    -1,
      -1,    67,    -1,    -1,    38,    -1,    45,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    53
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    38,    35,     0,    16,    39,     6,    40,    42,
      35,    43,     7,     8,     9,    41,    48,    49,    44,    35,
       4,    35,    41,    18,    46,    50,    21,    55,    51,    35,
      17,    19,    10,    12,    14,    23,    35,    56,    57,    59,
      63,    66,    71,    73,     5,    19,    47,    48,    35,    52,
      19,    19,    19,    57,    58,    19,    60,    22,    56,    16,
      52,    46,    16,    17,    20,    19,    29,    30,    33,    34,
      35,    63,    74,    80,    86,    92,    94,    74,    36,    67,
      74,    58,    24,    64,    74,    15,    20,    45,    48,    21,
      74,    35,    93,    94,    93,    20,    25,    26,    27,    28,
      75,    29,    30,    81,    31,    32,    87,    20,    69,    20,
      68,    20,    18,    65,    61,    21,    43,    18,    54,    42,
      53,    20,    55,    79,    78,    77,    76,    82,    84,    88,
      90,    13,    18,    70,    16,    70,    64,    74,    53,    35,
      55,    11,    72,    80,    80,    80,    80,    86,    86,    92,
      92,    55,    67,    62,    55,    17,    22,    55,    16,    83,
      85,    89,    91,    16,    16,    22,    48,    16,    81,    81,
      87,    87,    16,    54
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    37,    39,    38,    40,    40,    41,    41,    42,    44,
      45,    43,    43,    47,    46,    46,    48,    48,    50,    49,
      51,    49,    52,    52,    53,    53,    54,    54,    55,    56,
      56,    57,    57,    57,    57,    57,    57,    58,    58,    60,
      61,    62,    59,    63,    64,    64,    65,    66,    68,    67,
      69,    67,    70,    70,    71,    72,    72,    73,    74,    76,
      75,    77,    75,    78,    75,    79,    75,    75,    80,    82,
      83,    81,    84,    85,    81,    81,    86,    88,    89,    87,
      90,    91,    87,    87,    92,    92,    92,    92,    92,    92,
      93,    93,    94,    94
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     9,     1,     0,     2,     0,     2,     0,
       0,     8,     0,     0,     4,     0,     1,     1,     0,    11,
       0,    11,     4,     0,     1,     0,     5,     0,     3,     2,
       0,     1,     1,     1,     2,     1,     3,     2,     0,     0,
       0,     0,     7,     4,     2,     0,     2,     5,     0,     3,
       0,     3,     2,     0,     7,     2,     0,     7,     2,     0,
       3,     0,     3,     0,     3,     0,     3,     0,     2,     0,
       0,     5,     0,     0,     5,     0,     2,     0,     0,     5,
       0,     0,     5,     0,     3,     1,     1,     1,     2,     2,
       1,     1,     1,     1
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
#line 71 "parser.y"
    {
        dirFunc.insert("global", FuncEntry("nula"));
        scopeActual = "global";
    }
#line 1321 "parser.tab.c"
    break;

  case 3: /* programa: PROGRAMA ID PUNTOYCOMA $@1 programa_p programa_pp INICIO cuerpo FIN  */
#line 76 "parser.y"
    { cout << "Programa válido!" << endl; }
#line 1327 "parser.tab.c"
    break;

  case 9: /* $@2: %empty  */
#line 95 "parser.y"
    {
        idStack.push_back((yyvsp[0].sval));
    }
#line 1335 "parser.tab.c"
    break;

  case 10: /* $@3: %empty  */
#line 99 "parser.y"
    {
        cerr << "Insertando variables con tipo: " << (yyvsp[-1].sval) << endl;
        for (auto& id : idStack) {
            cerr << "  Insertando: " << id << endl;
            try {
                dirFunc.get(scopeActual).varTable.vars.insert(id, (yyvsp[-1].sval));
            } catch (runtime_error&) {
                yyerror("Variable doblemente declarada");
                YYABORT;
            }
        }
        idStack.clear();
    }
#line 1353 "parser.tab.c"
    break;

  case 13: /* $@4: %empty  */
#line 118 "parser.y"
    {
        idStack.push_back((yyvsp[0].sval));
    }
#line 1361 "parser.tab.c"
    break;

  case 16: /* tipo: ENTERO  */
#line 126 "parser.y"
             { (yyval.sval) = strdup("entero"); }
#line 1367 "parser.tab.c"
    break;

  case 17: /* tipo: FLOTANTE  */
#line 127 "parser.y"
               { (yyval.sval) = strdup("flotante"); }
#line 1373 "parser.tab.c"
    break;

  case 18: /* $@5: %empty  */
#line 132 "parser.y"
    {
        try {
            dirFunc.insert((yyvsp[0].sval), FuncEntry("nula"));
        } catch (runtime_error&) {
            yyerror("Función doblemente declarada");
            YYABORT;
        }
        scopeActual = (yyvsp[0].sval);
    }
#line 1387 "parser.tab.c"
    break;

  case 19: /* funcs: NULA ID $@5 PARENIZQ funcs_p PARENDER LLAVEIZQ funcs_pp cuerpo LLAVEDER PUNTOYCOMA  */
#line 142 "parser.y"
    { scopeActual = "global"; }
#line 1393 "parser.tab.c"
    break;

  case 20: /* $@6: %empty  */
#line 145 "parser.y"
    {
        try {
            dirFunc.insert((yyvsp[0].sval), FuncEntry((yyvsp[-1].sval)));
        } catch (runtime_error&) {
            yyerror("Función doblemente declarada");
            YYABORT;
        }
        scopeActual = (yyvsp[0].sval);
    }
#line 1407 "parser.tab.c"
    break;

  case 21: /* funcs: tipo ID $@6 PARENIZQ funcs_p PARENDER LLAVEIZQ funcs_pp cuerpo LLAVEDER PUNTOYCOMA  */
#line 155 "parser.y"
    { scopeActual = "global"; }
#line 1413 "parser.tab.c"
    break;

  case 39: /* $@7: %empty  */
#line 198 "parser.y"
    {
        vars.push((yyvsp[0].sval));
        string t = dirFunc.get(scopeActual).varTable.vars.get((yyvsp[0].sval));
        types.push(t);
    }
#line 1423 "parser.tab.c"
    break;

  case 40: /* $@8: %empty  */
#line 203 "parser.y"
               { operators.push("=");}
#line 1429 "parser.tab.c"
    break;

  case 41: /* $@9: %empty  */
#line 203 "parser.y"
                                                 { makeQuadruple(); }
#line 1435 "parser.tab.c"
    break;

  case 48: /* $@10: %empty  */
#line 226 "parser.y"
    {
        string var = vars.getTop(); vars.pop();
        types.pop();
        quadruples.add("PRINT", var, "_", "_");
    }
#line 1445 "parser.tab.c"
    break;

  case 50: /* $@11: %empty  */
#line 233 "parser.y"
    {
        quadruples.add("PRINT", (yyvsp[0].sval), "_","_");
    }
#line 1453 "parser.tab.c"
    break;

  case 59: /* $@12: %empty  */
#line 262 "parser.y"
             { operators.push(">");}
#line 1459 "parser.tab.c"
    break;

  case 60: /* expresion_p: MAYORQUE $@12 exp  */
#line 262 "parser.y"
                                         { makeQuadruple();}
#line 1465 "parser.tab.c"
    break;

  case 61: /* $@13: %empty  */
#line 263 "parser.y"
               { operators.push("<");}
#line 1471 "parser.tab.c"
    break;

  case 62: /* expresion_p: MENORQUE $@13 exp  */
#line 263 "parser.y"
                                           { makeQuadruple();}
#line 1477 "parser.tab.c"
    break;

  case 63: /* $@14: %empty  */
#line 264 "parser.y"
                { operators.push("!=");}
#line 1483 "parser.tab.c"
    break;

  case 64: /* expresion_p: DIFERENTE $@14 exp  */
#line 264 "parser.y"
                                              { makeQuadruple();}
#line 1489 "parser.tab.c"
    break;

  case 65: /* $@15: %empty  */
#line 265 "parser.y"
            { operators.push("==");}
#line 1495 "parser.tab.c"
    break;

  case 66: /* expresion_p: IGUAL $@15 exp  */
#line 265 "parser.y"
                                         { makeQuadruple();}
#line 1501 "parser.tab.c"
    break;

  case 69: /* $@16: %empty  */
#line 274 "parser.y"
        { operators.push("+");}
#line 1507 "parser.tab.c"
    break;

  case 70: /* $@17: %empty  */
#line 274 "parser.y"
                                        { makeQuadruple();}
#line 1513 "parser.tab.c"
    break;

  case 72: /* $@18: %empty  */
#line 275 "parser.y"
             { operators.push("-");}
#line 1519 "parser.tab.c"
    break;

  case 73: /* $@19: %empty  */
#line 275 "parser.y"
                                              { makeQuadruple();}
#line 1525 "parser.tab.c"
    break;

  case 77: /* $@20: %empty  */
#line 284 "parser.y"
         { operators.push("*");}
#line 1531 "parser.tab.c"
    break;

  case 78: /* $@21: %empty  */
#line 284 "parser.y"
                                         { makeQuadruple();}
#line 1537 "parser.tab.c"
    break;

  case 80: /* $@22: %empty  */
#line 285 "parser.y"
             { operators.push("/");}
#line 1543 "parser.tab.c"
    break;

  case 81: /* $@23: %empty  */
#line 285 "parser.y"
                                            { makeQuadruple();}
#line 1549 "parser.tab.c"
    break;

  case 86: /* factor: ID  */
#line 293 "parser.y"
    {
        vars.push((yyvsp[0].sval));
        string type = dirFunc.get(scopeActual).varTable.vars.get((yyvsp[0].sval));
        types.push(type);
    }
#line 1559 "parser.tab.c"
    break;

  case 92: /* cte: CTE_ENT  */
#line 310 "parser.y"
    {
        vars.push(to_string((yyvsp[0].ival)));
        types.push("entero");
    }
#line 1568 "parser.tab.c"
    break;

  case 93: /* cte: CTE_FLOT  */
#line 315 "parser.y"
    {
        vars.push(to_string((yyvsp[0].fval)));
        types.push("flotante");
    }
#line 1577 "parser.tab.c"
    break;


#line 1581 "parser.tab.c"

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

#line 321 "parser.y"


int main() {
    cout << "Ingresa tu programa:" << endl;
    yyparse();
    quadruples.print();
    return 0;
}
