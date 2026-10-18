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
#line 1 "minic.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "ast.h"
#include "semantic_analysis.h"
extern int yylex();
extern int yylex_destroy();
extern int yywrap();
void yyerror(const char *);
extern FILE *yyin;
astNode *root;

#line 86 "y.tab.c"

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

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    ID = 258,                      /* ID  */
    NUM = 259,                     /* NUM  */
    INT = 260,                     /* INT  */
    VOID = 261,                    /* VOID  */
    GT = 262,                      /* GT  */
    LT = 263,                      /* LT  */
    EQ = 264,                      /* EQ  */
    GE = 265,                      /* GE  */
    LE = 266,                      /* LE  */
    NEQ = 267,                     /* NEQ  */
    IF = 268,                      /* IF  */
    WHILE = 269,                   /* WHILE  */
    ELSE = 270,                    /* ELSE  */
    EXTERN = 271,                  /* EXTERN  */
    RETURN = 272,                  /* RETURN  */
    PRINT = 273,                   /* PRINT  */
    READ = 274                     /* READ  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define ID 258
#define NUM 259
#define INT 260
#define VOID 261
#define GT 262
#define LT 263
#define EQ 264
#define GE 265
#define LE 266
#define NEQ 267
#define IF 268
#define WHILE 269
#define ELSE 270
#define EXTERN 271
#define RETURN 272
#define PRINT 273
#define READ 274

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 19 "minic.y"

	int ival;
	char *idname;
	astNode *nptr;
	vector<astNode*> *svec;

#line 184 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_NUM = 4,                        /* NUM  */
  YYSYMBOL_INT = 5,                        /* INT  */
  YYSYMBOL_VOID = 6,                       /* VOID  */
  YYSYMBOL_GT = 7,                         /* GT  */
  YYSYMBOL_LT = 8,                         /* LT  */
  YYSYMBOL_EQ = 9,                         /* EQ  */
  YYSYMBOL_GE = 10,                        /* GE  */
  YYSYMBOL_LE = 11,                        /* LE  */
  YYSYMBOL_NEQ = 12,                       /* NEQ  */
  YYSYMBOL_IF = 13,                        /* IF  */
  YYSYMBOL_WHILE = 14,                     /* WHILE  */
  YYSYMBOL_ELSE = 15,                      /* ELSE  */
  YYSYMBOL_EXTERN = 16,                    /* EXTERN  */
  YYSYMBOL_RETURN = 17,                    /* RETURN  */
  YYSYMBOL_PRINT = 18,                     /* PRINT  */
  YYSYMBOL_READ = 19,                      /* READ  */
  YYSYMBOL_20_ = 20,                       /* '('  */
  YYSYMBOL_21_ = 21,                       /* ')'  */
  YYSYMBOL_22_ = 22,                       /* ';'  */
  YYSYMBOL_23_ = 23,                       /* '{'  */
  YYSYMBOL_24_ = 24,                       /* '}'  */
  YYSYMBOL_25_ = 25,                       /* '='  */
  YYSYMBOL_26_ = 26,                       /* '-'  */
  YYSYMBOL_27_ = 27,                       /* '+'  */
  YYSYMBOL_28_ = 28,                       /* '*'  */
  YYSYMBOL_29_ = 29,                       /* '/'  */
  YYSYMBOL_YYACCEPT = 30,                  /* $accept  */
  YYSYMBOL_program = 31,                   /* program  */
  YYSYMBOL_printextern = 32,               /* printextern  */
  YYSYMBOL_readextern = 33,                /* readextern  */
  YYSYMBOL_function = 34,                  /* function  */
  YYSYMBOL_whilestatement = 35,            /* whilestatement  */
  YYSYMBOL_ifstatement = 36,               /* ifstatement  */
  YYSYMBOL_condition = 37,                 /* condition  */
  YYSYMBOL_block = 38,                     /* block  */
  YYSYMBOL_statements = 39,                /* statements  */
  YYSYMBOL_statement = 40,                 /* statement  */
  YYSYMBOL_returnstatement = 41,           /* returnstatement  */
  YYSYMBOL_assignmentstatement = 42,       /* assignmentstatement  */
  YYSYMBOL_unaryexpression = 43,           /* unaryexpression  */
  YYSYMBOL_functionCall = 44,              /* functionCall  */
  YYSYMBOL_binaryexpression = 45,          /* binaryexpression  */
  YYSYMBOL_binaryexpressioncore = 46,      /* binaryexpressioncore  */
  YYSYMBOL_relationalexpression = 47,      /* relationalexpression  */
  YYSYMBOL_relitem = 48,                   /* relitem  */
  YYSYMBOL_declarations = 49,              /* declarations  */
  YYSYMBOL_declaration = 50,               /* declaration  */
  YYSYMBOL_term = 51                       /* term  */
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

#if 1

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
#endif /* 1 */

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
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   160

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  30
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  57
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  133

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   274


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
      20,    21,    28,    27,     2,    26,     2,    29,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    22,
       2,    25,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    23,     2,    24,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int8 yyrline[] =
{
       0,    39,    39,    40,    42,    44,    46,    48,    50,    51,
      52,    53,    54,    55,    57,    59,    64,    65,    67,    68,
      69,    70,    71,    73,    74,    75,    76,    78,    79,    80,
      81,    83,    85,    86,    87,    88,    90,    91,    93,    94,
      95,    96,    98,    99,   100,   101,   102,   103,   105,   106,
     108,   109,   113,   115,   117,   118,   119,   120
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  static const char *const yy_sname[] =
  {
  "end of file", "error", "invalid token", "ID", "NUM", "INT", "VOID",
  "GT", "LT", "EQ", "GE", "LE", "NEQ", "IF", "WHILE", "ELSE", "EXTERN",
  "RETURN", "PRINT", "READ", "'('", "')'", "';'", "'{'", "'}'", "'='",
  "'-'", "'+'", "'*'", "'/'", "$accept", "program", "printextern",
  "readextern", "function", "whilestatement", "ifstatement", "condition",
  "block", "statements", "statement", "returnstatement",
  "assignmentstatement", "unaryexpression", "functionCall",
  "binaryexpression", "binaryexpressioncore", "relationalexpression",
  "relitem", "declarations", "declaration", "term", YY_NULLPTR
  };
  return yy_sname[yysymbol];
}
#endif

#define YYPACT_NINF (-53)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      -7,    13,    24,    -3,    10,    -8,    14,   -53,    33,    37,
      39,    37,    32,    34,    65,   -53,   -53,    48,    77,    75,
      63,    76,    91,   -53,    90,   110,   -53,    93,    92,   111,
     -53,   114,    70,   -53,    96,   -13,    99,    99,    11,   100,
     101,   -53,   -53,    22,   -53,   -53,   -53,   102,   -53,   -53,
       2,    11,    47,    30,    92,   103,   -53,    52,    54,   104,
     105,   106,   -53,    64,    54,   108,   -53,   -53,   -53,   -53,
      56,   -53,   109,   112,   113,   115,    72,   -53,   117,    69,
      82,   107,   116,   -53,   118,   119,   120,    82,   -53,   -53,
     -53,   -53,   -53,    54,    54,    54,    54,   121,   -53,   118,
     119,   -53,   -53,   -53,   -53,   -53,   -53,    47,    47,    47,
      47,    47,    47,    30,    30,   -53,   -53,   -53,   -53,   -53,
     -53,   -53,   -53,   -53,   -53,   -53,   -53,   -53,   -53,   -53,
     -53,   -53,   -53
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     1,     0,     0,
       0,     0,     0,     0,     0,     2,     3,     0,     0,     0,
       0,     0,     0,     5,     0,     0,     4,     0,     0,    52,
       6,     0,     0,    51,     0,     0,     0,     0,     0,     0,
       0,    20,    19,     0,    17,    21,    18,     0,    50,    53,
       0,     0,     0,     0,     0,    54,    56,     0,     0,     0,
       0,     0,    37,     0,     0,     0,    15,    16,    22,    54,
       0,    32,     0,     0,     0,     0,     0,    49,     0,     0,
      48,     8,    11,     7,    54,    56,     0,     0,    31,    25,
      26,    24,    23,     0,     0,     0,     0,     0,    35,     0,
       0,    33,    30,    29,    28,    27,    14,     0,     0,     0,
       0,     0,     0,     0,     0,    55,    57,    36,    39,    38,
      40,    41,    34,    42,    43,    44,    45,    46,    47,     9,
      10,    12,    13
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -53,   -53,   128,   122,   125,   -53,   -53,   123,   -52,   -53,
     -43,   -53,   -53,    94,   -35,   -34,    86,   -53,    -5,   -53,
     124,   -30
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     3,     4,    15,    41,    42,    53,    30,    43,
      44,    45,    46,    59,    47,    77,    62,    78,    79,    32,
      33,    80
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      67,    81,    83,    60,    61,    69,    56,    50,    63,     1,
      82,    12,    51,     8,    55,    56,    74,    75,     5,     6,
      72,    76,    70,    71,     7,    35,    10,    87,    88,    39,
      40,    57,    13,    35,    97,    36,    37,    58,     5,    38,
      39,    40,    14,    36,    37,     6,    66,    38,    39,    40,
      69,    56,    17,    29,    18,    84,    85,    69,    56,    99,
     100,   129,   131,   118,   119,   120,   121,    57,    19,    20,
     130,   132,    70,    35,    70,    31,   107,   108,   109,   110,
     111,   112,    21,    36,    37,    23,    92,    38,    39,    40,
      93,    94,    95,    96,   105,    22,    25,    24,    93,    94,
      95,    96,   123,   124,   125,   126,   127,   128,    93,    94,
      95,    96,    26,    27,    28,    29,    31,    34,    49,    52,
      64,    65,   113,    50,    68,     9,    89,    90,    91,    98,
     101,   114,    11,     0,   102,   103,    16,   104,   106,   115,
     116,   117,   122,    86,     0,    73,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    48,     0,     0,     0,
      54
};

static const yytype_int8 yycheck[] =
{
      43,    53,    54,    38,    38,     3,     4,    20,    38,    16,
      53,    19,    25,    16,     3,     4,    51,    51,     5,     6,
      50,    51,    20,    21,     0,     3,    16,    57,    58,    18,
      19,    20,    18,     3,    64,    13,    14,    26,     5,    17,
      18,    19,     5,    13,    14,     6,    24,    17,    18,    19,
       3,     4,    20,    23,    20,     3,     4,     3,     4,     3,
       4,   113,   114,    93,    94,    95,    96,    20,     3,    21,
     113,   114,    20,     3,    20,     5,     7,     8,     9,    10,
      11,    12,     5,    13,    14,    22,    22,    17,    18,    19,
      26,    27,    28,    29,    22,    20,     5,    21,    26,    27,
      28,    29,   107,   108,   109,   110,   111,   112,    26,    27,
      28,    29,    22,     3,    21,    23,     5,     3,    22,    20,
      20,    20,    15,    20,    22,     3,    22,    22,    22,    21,
      21,    15,     4,    -1,    22,    22,    11,    22,    21,    21,
      21,    21,    21,    57,    -1,    51,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    32,    -1,    -1,    -1,
      37
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    16,    31,    32,    33,     5,     6,     0,    16,    33,
      16,    32,    19,    18,     5,    34,    34,    20,    20,     3,
      21,     5,    20,    22,    21,     5,    22,     3,    21,    23,
      38,     5,    49,    50,     3,     3,    13,    14,    17,    18,
      19,    35,    36,    39,    40,    41,    42,    44,    50,    22,
      20,    25,    20,    37,    37,     3,     4,    20,    26,    43,
      44,    45,    46,    51,    20,    20,    24,    40,    22,     3,
      20,    21,    51,    43,    44,    45,    51,    45,    47,    48,
      51,    38,    40,    38,     3,     4,    46,    51,    51,    22,
      22,    22,    22,    26,    27,    28,    29,    51,    21,     3,
       4,    21,    22,    22,    22,    22,    21,     7,     8,     9,
      10,    11,    12,    15,    15,    21,    21,    21,    51,    51,
      51,    51,    21,    48,    48,    48,    48,    48,    48,    38,
      40,    38,    40
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    30,    31,    31,    32,    33,    34,    35,    36,    36,
      36,    36,    36,    36,    37,    38,    39,    39,    40,    40,
      40,    40,    40,    41,    41,    41,    41,    42,    42,    42,
      42,    43,    44,    44,    44,    44,    45,    45,    46,    46,
      46,    46,    47,    47,    47,    47,    47,    47,    48,    48,
      49,    49,    49,    50,    51,    51,    51,    51
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     3,     7,     6,     7,     3,     3,     5,
       5,     3,     5,     5,     3,     4,     2,     1,     1,     1,
       1,     1,     2,     3,     3,     3,     3,     4,     4,     4,
       4,     2,     3,     4,     4,     3,     3,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     1,
       2,     1,     0,     3,     1,     3,     1,     3
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif



static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yystrlen (yysymbol_name (yyarg[yyi]));
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp = yystpcpy (yyp, yysymbol_name (yyarg[yyi++]));
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


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

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

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
  case 2: /* program: printextern readextern function  */
#line 39 "minic.y"
                                                                                        {(yyval.nptr) = createProg((yyvsp[-2].nptr), (yyvsp[-1].nptr), (yyvsp[0].nptr)); root = (yyval.nptr);}
#line 1517 "y.tab.c"
    break;

  case 3: /* program: readextern printextern function  */
#line 40 "minic.y"
                                                                                                                {(yyval.nptr) = createProg((yyvsp[-2].nptr), (yyvsp[-1].nptr), (yyvsp[0].nptr)); root = (yyval.nptr);}
#line 1523 "y.tab.c"
    break;

  case 4: /* printextern: EXTERN VOID PRINT '(' INT ')' ';'  */
#line 42 "minic.y"
                                                                {(yyval.nptr) = createExtern(strdup("print"));printf("Matched: extern print ;\n");}
#line 1529 "y.tab.c"
    break;

  case 5: /* readextern: EXTERN INT READ '(' ')' ';'  */
#line 44 "minic.y"
                                                                                        {(yyval.nptr) = createExtern(strdup("read"));}
#line 1535 "y.tab.c"
    break;

  case 6: /* function: INT ID '(' INT ID ')' block  */
#line 46 "minic.y"
                                                                                        {(yyval.nptr) = createFunc((yyvsp[-5].idname), createDecl((yyvsp[-2].idname)), (yyvsp[0].nptr));}
#line 1541 "y.tab.c"
    break;

  case 7: /* whilestatement: WHILE condition block  */
#line 48 "minic.y"
                                                                                        {(yyval.nptr) = createWhile((yyvsp[-1].nptr), (yyvsp[0].nptr));}
#line 1547 "y.tab.c"
    break;

  case 8: /* ifstatement: IF condition block  */
#line 50 "minic.y"
                                                                                                                {(yyval.nptr) = createIf((yyvsp[-1].nptr), (yyvsp[0].nptr));}
#line 1553 "y.tab.c"
    break;

  case 9: /* ifstatement: IF condition block ELSE block  */
#line 51 "minic.y"
                                                                                                                {(yyval.nptr) = createIf((yyvsp[-3].nptr), (yyvsp[-2].nptr), (yyvsp[0].nptr));}
#line 1559 "y.tab.c"
    break;

  case 10: /* ifstatement: IF condition block ELSE statement  */
#line 52 "minic.y"
                                                                                                        {(yyval.nptr) = createIf((yyvsp[-3].nptr), (yyvsp[-2].nptr), (yyvsp[0].nptr));}
#line 1565 "y.tab.c"
    break;

  case 11: /* ifstatement: IF condition statement  */
#line 53 "minic.y"
                                                                                                                                        {(yyval.nptr) = createIf((yyvsp[-1].nptr), (yyvsp[0].nptr));}
#line 1571 "y.tab.c"
    break;

  case 12: /* ifstatement: IF condition statement ELSE block  */
#line 54 "minic.y"
                                                                                                        {(yyval.nptr) = createIf((yyvsp[-3].nptr), (yyvsp[-2].nptr), (yyvsp[0].nptr));}
#line 1577 "y.tab.c"
    break;

  case 13: /* ifstatement: IF condition statement ELSE statement  */
#line 55 "minic.y"
                                                                                        {(yyval.nptr) = createIf((yyvsp[-3].nptr), (yyvsp[-2].nptr), (yyvsp[0].nptr));}
#line 1583 "y.tab.c"
    break;

  case 14: /* condition: '(' relationalexpression ')'  */
#line 57 "minic.y"
                                                                                        {(yyval.nptr) = (yyvsp[-1].nptr);}
#line 1589 "y.tab.c"
    break;

  case 15: /* block: '{' declarations statements '}'  */
#line 59 "minic.y"
                                                                                        {
																											(yyvsp[-2].svec)->insert((yyvsp[-2].svec)->end(), (yyvsp[-1].svec)->begin(), (yyvsp[-1].svec)->end());
																											delete (yyvsp[-1].svec);
																											(yyval.nptr) = createBlock((yyvsp[-2].svec));
																										}
#line 1599 "y.tab.c"
    break;

  case 16: /* statements: statements statement  */
#line 64 "minic.y"
                                                                                                        {(yyval.svec) = (yyvsp[-1].svec); (yyval.svec)->push_back((yyvsp[0].nptr));}
#line 1605 "y.tab.c"
    break;

  case 17: /* statements: statement  */
#line 65 "minic.y"
                                                                                                                                                                {(yyval.svec) = new vector<astNode*>(); (yyval.svec)->push_back((yyvsp[0].nptr));}
#line 1611 "y.tab.c"
    break;

  case 18: /* statement: assignmentstatement  */
#line 67 "minic.y"
                                                                                                                {(yyval.nptr) = (yyvsp[0].nptr);}
#line 1617 "y.tab.c"
    break;

  case 19: /* statement: ifstatement  */
#line 68 "minic.y"
                                                                                                                                                                        {(yyval.nptr) = (yyvsp[0].nptr);}
#line 1623 "y.tab.c"
    break;

  case 20: /* statement: whilestatement  */
#line 69 "minic.y"
                                                                                                                                                                {(yyval.nptr) = (yyvsp[0].nptr);}
#line 1629 "y.tab.c"
    break;

  case 21: /* statement: returnstatement  */
#line 70 "minic.y"
                                                                                                                                                                {(yyval.nptr) = (yyvsp[0].nptr);}
#line 1635 "y.tab.c"
    break;

  case 22: /* statement: functionCall ';'  */
#line 71 "minic.y"
                                                                                                                                                        {(yyval.nptr) = (yyvsp[-1].nptr);}
#line 1641 "y.tab.c"
    break;

  case 23: /* returnstatement: RETURN term ';'  */
#line 73 "minic.y"
                                                                                                                {(yyval.nptr) = createRet((yyvsp[-1].nptr));}
#line 1647 "y.tab.c"
    break;

  case 24: /* returnstatement: RETURN binaryexpression ';'  */
#line 74 "minic.y"
                                                                                                                        {(yyval.nptr) = createRet((yyvsp[-1].nptr));}
#line 1653 "y.tab.c"
    break;

  case 25: /* returnstatement: RETURN unaryexpression ';'  */
#line 75 "minic.y"
                                                                                                                        {(yyval.nptr) = createRet((yyvsp[-1].nptr));}
#line 1659 "y.tab.c"
    break;

  case 26: /* returnstatement: RETURN functionCall ';'  */
#line 76 "minic.y"
                                                                                                                                        {(yyval.nptr) = createRet((yyvsp[-1].nptr));}
#line 1665 "y.tab.c"
    break;

  case 27: /* assignmentstatement: ID '=' term ';'  */
#line 78 "minic.y"
                                                                                                {(yyval.nptr) = createAsgn(createVar((yyvsp[-3].idname)), (yyvsp[-1].nptr)); free((yyvsp[-3].idname));}
#line 1671 "y.tab.c"
    break;

  case 28: /* assignmentstatement: ID '=' binaryexpression ';'  */
#line 79 "minic.y"
                                                                                                                        {(yyval.nptr) = createAsgn(createVar((yyvsp[-3].idname)), (yyvsp[-1].nptr)); free((yyvsp[-3].idname));}
#line 1677 "y.tab.c"
    break;

  case 29: /* assignmentstatement: ID '=' functionCall ';'  */
#line 80 "minic.y"
                                                                                                                                        {(yyval.nptr) = createAsgn(createVar((yyvsp[-3].idname)), (yyvsp[-1].nptr)); free((yyvsp[-3].idname));}
#line 1683 "y.tab.c"
    break;

  case 30: /* assignmentstatement: ID '=' unaryexpression ';'  */
#line 81 "minic.y"
                                                                                                                        {(yyval.nptr) = createAsgn(createVar((yyvsp[-3].idname)), (yyvsp[-1].nptr)); free((yyvsp[-3].idname));}
#line 1689 "y.tab.c"
    break;

  case 31: /* unaryexpression: '-' term  */
#line 83 "minic.y"
                                                                                                                                {(yyval.nptr) = createUExpr((yyvsp[0].nptr), uminus);}
#line 1695 "y.tab.c"
    break;

  case 32: /* functionCall: ID '(' ')'  */
#line 85 "minic.y"
                                                                                                                                {(yyval.nptr) = createCall((yyvsp[-2].idname)); free((yyvsp[-2].idname));}
#line 1701 "y.tab.c"
    break;

  case 33: /* functionCall: ID '(' term ')'  */
#line 86 "minic.y"
                                                                                                                                                        {(yyval.nptr) = createCall((yyvsp[-3].idname)); free((yyvsp[-3].idname));}
#line 1707 "y.tab.c"
    break;

  case 34: /* functionCall: PRINT '(' term ')'  */
#line 87 "minic.y"
                                                                                                                                                {(yyval.nptr) = createCall(strdup("print")); }
#line 1713 "y.tab.c"
    break;

  case 35: /* functionCall: READ '(' ')'  */
#line 88 "minic.y"
                                                                                                                                                                {(yyval.nptr) = createCall(strdup("read"));}
#line 1719 "y.tab.c"
    break;

  case 36: /* binaryexpression: '(' binaryexpressioncore ')'  */
#line 90 "minic.y"
                                                                {(yyval.nptr) = (yyvsp[-1].nptr);}
#line 1725 "y.tab.c"
    break;

  case 37: /* binaryexpression: binaryexpressioncore  */
#line 91 "minic.y"
                                                                                                                                        {(yyval.nptr) = (yyvsp[0].nptr);}
#line 1731 "y.tab.c"
    break;

  case 38: /* binaryexpressioncore: term '+' term  */
#line 93 "minic.y"
                                                                                                {(yyval.nptr) = createBExpr((yyvsp[-2].nptr), (yyvsp[0].nptr), add);}
#line 1737 "y.tab.c"
    break;

  case 39: /* binaryexpressioncore: term '-' term  */
#line 94 "minic.y"
                                                                                                                                                                {(yyval.nptr) = createBExpr((yyvsp[-2].nptr), (yyvsp[0].nptr), sub);}
#line 1743 "y.tab.c"
    break;

  case 40: /* binaryexpressioncore: term '*' term  */
#line 95 "minic.y"
                                                                                                                                                                {(yyval.nptr) = createBExpr((yyvsp[-2].nptr), (yyvsp[0].nptr), mul);}
#line 1749 "y.tab.c"
    break;

  case 41: /* binaryexpressioncore: term '/' term  */
#line 96 "minic.y"
                                                                                                                                                                {(yyval.nptr) = createBExpr((yyvsp[-2].nptr), (yyvsp[0].nptr), divide);}
#line 1755 "y.tab.c"
    break;

  case 42: /* relationalexpression: relitem GT relitem  */
#line 98 "minic.y"
                                                                                {(yyval.nptr) = createRExpr((yyvsp[-2].nptr), (yyvsp[0].nptr), gt);}
#line 1761 "y.tab.c"
    break;

  case 43: /* relationalexpression: relitem LT relitem  */
#line 99 "minic.y"
                                                                                                                                        {(yyval.nptr) = createRExpr((yyvsp[-2].nptr), (yyvsp[0].nptr), lt);}
#line 1767 "y.tab.c"
    break;

  case 44: /* relationalexpression: relitem EQ relitem  */
#line 100 "minic.y"
                                                                                                                                        {(yyval.nptr) = createRExpr((yyvsp[-2].nptr), (yyvsp[0].nptr), eq);}
#line 1773 "y.tab.c"
    break;

  case 45: /* relationalexpression: relitem GE relitem  */
#line 101 "minic.y"
                                                                                                                                        {(yyval.nptr) = createRExpr((yyvsp[-2].nptr), (yyvsp[0].nptr), ge);}
#line 1779 "y.tab.c"
    break;

  case 46: /* relationalexpression: relitem LE relitem  */
#line 102 "minic.y"
                                                                                                                                        {(yyval.nptr) = createRExpr((yyvsp[-2].nptr), (yyvsp[0].nptr), le);}
#line 1785 "y.tab.c"
    break;

  case 47: /* relationalexpression: relitem NEQ relitem  */
#line 103 "minic.y"
                                                                                                                                        {(yyval.nptr) = createRExpr((yyvsp[-2].nptr), (yyvsp[0].nptr), neq);}
#line 1791 "y.tab.c"
    break;

  case 48: /* relitem: term  */
#line 105 "minic.y"
                                                                                                                                                                {(yyval.nptr) = (yyvsp[0].nptr);}
#line 1797 "y.tab.c"
    break;

  case 49: /* relitem: binaryexpression  */
#line 106 "minic.y"
                                                                                                                                                        {(yyval.nptr) = (yyvsp[0].nptr);}
#line 1803 "y.tab.c"
    break;

  case 50: /* declarations: declarations declaration  */
#line 108 "minic.y"
                                                                                        {(yyval.svec) = (yyvsp[-1].svec); (yyval.svec)->push_back((yyvsp[0].nptr));}
#line 1809 "y.tab.c"
    break;

  case 51: /* declarations: declaration  */
#line 109 "minic.y"
                                                                                                                                                                {
																											(yyval.svec) = new std::vector<astNode*>();
																											(yyval.svec)->push_back((yyvsp[0].nptr));
																										}
#line 1818 "y.tab.c"
    break;

  case 52: /* declarations: %empty  */
#line 113 "minic.y"
                                                                                                                                                                                                        {(yyval.svec) = new vector<astNode*>();}
#line 1824 "y.tab.c"
    break;

  case 53: /* declaration: INT ID ';'  */
#line 115 "minic.y"
                                                                                                                                        {(yyval.nptr) = createDecl((yyvsp[-1].idname)); free((yyvsp[-1].idname));}
#line 1830 "y.tab.c"
    break;

  case 54: /* term: ID  */
#line 117 "minic.y"
                                                                                                                                                                                {(yyval.nptr) = createVar((yyvsp[0].idname)); free((yyvsp[0].idname));}
#line 1836 "y.tab.c"
    break;

  case 55: /* term: '(' ID ')'  */
#line 118 "minic.y"
                                                                                                                                                                        {(yyval.nptr) = createVar((yyvsp[-1].idname)); free((yyvsp[-1].idname));}
#line 1842 "y.tab.c"
    break;

  case 56: /* term: NUM  */
#line 119 "minic.y"
                                                                                                                                                                                        {(yyval.nptr) = createCnst((yyvsp[0].ival));}
#line 1848 "y.tab.c"
    break;

  case 57: /* term: '(' NUM ')'  */
#line 120 "minic.y"
                                                                                                                                                                {(yyval.nptr) = createCnst((yyvsp[-1].ival));}
#line 1854 "y.tab.c"
    break;


#line 1858 "y.tab.c"

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
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
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
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 122 "minic.y"

int main(int argc, char** argv){
	if (argc == 2){
  	yyin = fopen(argv[1], "r");
	}
	yyparse(); // Will set the root
	printNode(root);
	int sem_flag = semantic_analysis(root);
	printf("\n%d\n", sem_flag);

 	// Convert to LLVM IR
	// Code optimizer
	// Assembly code generator


	// Cleanup	
	freeNode(root);

	if (yyin != stdin)
		fclose(yyin);
	
	yylex_destroy();

	
	return 0;
}

void yyerror(const char *){
	fprintf(stderr, "Syntax error\n");
}
