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

  /* 파서에서 사용할 C 헤더 및 심볼 선언 */
  #include <stdio.h>    // fprintf 등 에러 출력용
  #include <stdlib.h>   // calloc/free 등 동적 메모리
  #include <string.h>
  #include "ast.h"      // AST 노드 타입/함수

  extern int yylex(void);     // Flex가 생성하는 렉서 함수
  extern int yylineno;        // Flex의 현재 소스 코드 라인 번호
  void yyerror(const char *s); // 에러 리포팅 함수 (아래에서 정의)

  Node *root = NULL;    // 전체 파싱 결과 AST 루트 저장용

#line 85 "parser.c"

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

#include "parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENT = 3,                      /* IDENT  */
  YYSYMBOL_INT_CONST = 4,                  /* INT_CONST  */
  YYSYMBOL_FLOAT_CONST = 5,                /* FLOAT_CONST  */
  YYSYMBOL_CHAR_CONST = 6,                 /* CHAR_CONST  */
  YYSYMBOL_STRING_LITERAL = 7,             /* STRING_LITERAL  */
  YYSYMBOL_INT = 8,                        /* INT  */
  YYSYMBOL_FLOAT = 9,                      /* FLOAT  */
  YYSYMBOL_CHAR = 10,                      /* CHAR  */
  YYSYMBOL_VOID = 11,                      /* VOID  */
  YYSYMBOL_IF = 12,                        /* IF  */
  YYSYMBOL_ELSE = 13,                      /* ELSE  */
  YYSYMBOL_WHILE = 14,                     /* WHILE  */
  YYSYMBOL_RETURN = 15,                    /* RETURN  */
  YYSYMBOL_FOR = 16,                       /* FOR  */
  YYSYMBOL_EQ = 17,                        /* EQ  */
  YYSYMBOL_NE = 18,                        /* NE  */
  YYSYMBOL_LE = 19,                        /* LE  */
  YYSYMBOL_GE = 20,                        /* GE  */
  YYSYMBOL_AND = 21,                       /* AND  */
  YYSYMBOL_OR = 22,                        /* OR  */
  YYSYMBOL_23_ = 23,                       /* '|'  */
  YYSYMBOL_24_ = 24,                       /* '^'  */
  YYSYMBOL_25_ = 25,                       /* '&'  */
  YYSYMBOL_26_ = 26,                       /* '<'  */
  YYSYMBOL_27_ = 27,                       /* '>'  */
  YYSYMBOL_28_ = 28,                       /* '+'  */
  YYSYMBOL_29_ = 29,                       /* '-'  */
  YYSYMBOL_30_ = 30,                       /* '*'  */
  YYSYMBOL_31_ = 31,                       /* '/'  */
  YYSYMBOL_32_ = 32,                       /* '%'  */
  YYSYMBOL_33_ = 33,                       /* '!'  */
  YYSYMBOL_34_ = 34,                       /* '~'  */
  YYSYMBOL_35_ = 35,                       /* '='  */
  YYSYMBOL_LOWER_THAN_ELSE = 36,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_37_ = 37,                       /* '('  */
  YYSYMBOL_38_ = 38,                       /* ')'  */
  YYSYMBOL_39_ = 39,                       /* ','  */
  YYSYMBOL_40_ = 40,                       /* ';'  */
  YYSYMBOL_41_ = 41,                       /* '{'  */
  YYSYMBOL_42_ = 42,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 43,                  /* $accept  */
  YYSYMBOL_translation_unit = 44,          /* translation_unit  */
  YYSYMBOL_external_decl = 45,             /* external_decl  */
  YYSYMBOL_function_definition = 46,       /* function_definition  */
  YYSYMBOL_param_list_opt = 47,            /* param_list_opt  */
  YYSYMBOL_param_list = 48,                /* param_list  */
  YYSYMBOL_param_decl = 49,                /* param_decl  */
  YYSYMBOL_declaration = 50,               /* declaration  */
  YYSYMBOL_init_declarator_list = 51,      /* init_declarator_list  */
  YYSYMBOL_init_declarator = 52,           /* init_declarator  */
  YYSYMBOL_type_spec = 53,                 /* type_spec  */
  YYSYMBOL_compound_stmt = 54,             /* compound_stmt  */
  YYSYMBOL_stmt_decl_list_opt = 55,        /* stmt_decl_list_opt  */
  YYSYMBOL_stmt_decl_list = 56,            /* stmt_decl_list  */
  YYSYMBOL_stmt_or_decl = 57,              /* stmt_or_decl  */
  YYSYMBOL_statement = 58,                 /* statement  */
  YYSYMBOL_expr = 59,                      /* expr  */
  YYSYMBOL_assignment = 60,                /* assignment  */
  YYSYMBOL_logical_or = 61,                /* logical_or  */
  YYSYMBOL_logical_and = 62,               /* logical_and  */
  YYSYMBOL_equality = 63,                  /* equality  */
  YYSYMBOL_relational = 64,                /* relational  */
  YYSYMBOL_additive = 65,                  /* additive  */
  YYSYMBOL_multiplicative = 66,            /* multiplicative  */
  YYSYMBOL_unary = 67,                     /* unary  */
  YYSYMBOL_postfix = 68,                   /* postfix  */
  YYSYMBOL_arg_list_opt = 69,              /* arg_list_opt  */
  YYSYMBOL_arg_list = 70,                  /* arg_list  */
  YYSYMBOL_primary = 71,                   /* primary  */
  YYSYMBOL_simple_decl = 72,               /* simple_decl  */
  YYSYMBOL_expr_opt = 73,                  /* expr_opt  */
  YYSYMBOL_for_init_opt = 74,              /* for_init_opt  */
  YYSYMBOL_for_cond_opt = 75,              /* for_cond_opt  */
  YYSYMBOL_for_step_opt = 76,              /* for_step_opt  */
  YYSYMBOL_for_stmt = 77                   /* for_stmt  */
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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   171

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  82
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  136

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   278


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
       2,     2,     2,    33,     2,     2,     2,    32,    25,     2,
      37,    38,    30,    28,    39,    29,     2,    31,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    40,
      26,    35,    27,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    24,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    41,    23,    42,    34,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    36
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    78,    78,    79,    97,    98,   107,   113,   114,   119,
     121,   133,   138,   144,   146,   162,   163,   168,   169,   170,
     171,   176,   181,   182,   187,   189,   201,   202,   207,   208,
     209,   210,   212,   214,   216,   217,   218,   223,   228,   229,
     234,   235,   240,   241,   246,   247,   248,   253,   254,   255,
     256,   257,   262,   263,   264,   269,   270,   271,   272,   277,
     278,   279,   280,   285,   286,   291,   292,   297,   298,   313,
     314,   315,   316,   317,   318,   323,   329,   330,   335,   336,
     340,   344,   349
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IDENT", "INT_CONST",
  "FLOAT_CONST", "CHAR_CONST", "STRING_LITERAL", "INT", "FLOAT", "CHAR",
  "VOID", "IF", "ELSE", "WHILE", "RETURN", "FOR", "EQ", "NE", "LE", "GE",
  "AND", "OR", "'|'", "'^'", "'&'", "'<'", "'>'", "'+'", "'-'", "'*'",
  "'/'", "'%'", "'!'", "'~'", "'='", "LOWER_THAN_ELSE", "'('", "')'",
  "','", "';'", "'{'", "'}'", "$accept", "translation_unit",
  "external_decl", "function_definition", "param_list_opt", "param_list",
  "param_decl", "declaration", "init_declarator_list", "init_declarator",
  "type_spec", "compound_stmt", "stmt_decl_list_opt", "stmt_decl_list",
  "stmt_or_decl", "statement", "expr", "assignment", "logical_or",
  "logical_and", "equality", "relational", "additive", "multiplicative",
  "unary", "postfix", "arg_list_opt", "arg_list", "primary", "simple_decl",
  "expr_opt", "for_init_opt", "for_cond_opt", "for_step_opt", "for_stmt", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-124)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -124,   134,  -124,  -124,  -124,  -124,  -124,  -124,  -124,  -124,
       6,    43,   -15,  -124,    98,   101,    25,  -124,    62,  -124,
    -124,  -124,  -124,   133,   133,   133,    98,  -124,   -16,    17,
      28,    50,    87,    41,  -124,  -124,  -124,    29,    68,  -124,
      61,    82,  -124,    98,    98,    84,  -124,  -124,  -124,    86,
    -124,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,    88,   101,  -124,  -124,  -124,    90,
      93,  -124,    17,    28,    50,    50,    87,    87,    87,    87,
      41,    41,  -124,  -124,  -124,     7,  -124,  -124,  -124,    98,
      96,   104,    26,   113,  -124,  -124,    25,  -124,    81,     7,
    -124,  -124,   111,  -124,  -124,    98,    98,  -124,   112,    85,
    -124,  -124,  -124,    92,   115,  -124,    25,  -124,  -124,  -124,
     114,    46,    46,   116,    98,   143,  -124,  -124,   117,    46,
      98,  -124,  -124,   120,    46,  -124
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,    17,    18,    19,    20,     3,     4,     5,
       0,    15,     0,    13,     0,     7,     0,    12,    69,    70,
      71,    72,    73,     0,     0,     0,     0,    16,    38,    40,
      42,    44,    47,    52,    55,    59,    63,     0,     8,     9,
       0,    15,    14,     0,    65,    69,    62,    61,    60,     0,
      37,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    11,    39,    67,     0,
      66,    74,    41,    43,    45,    46,    50,    51,    48,    49,
      53,    54,    56,    57,    58,    22,     6,    10,    64,     0,
       0,     0,     0,     0,    28,    27,     0,    36,     0,    23,
      24,    26,     0,    35,    68,     0,     0,    30,     0,    76,
      21,    25,    29,     0,     0,    31,     0,    77,    78,    79,
       0,     0,     0,    75,    76,    32,    34,    80,     0,     0,
      76,    33,    81,     0,     0,    82
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -124,  -124,  -124,  -124,  -124,  -124,    94,   124,    44,   147,
      -1,   100,  -124,  -124,    66,   -95,   -24,    -6,  -124,   118,
     119,     3,    91,    60,   -20,  -124,  -124,  -124,  -124,  -124,
    -123,  -124,  -124,  -124,  -124
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     7,     8,    37,    38,    39,    95,    12,    13,
      40,    97,    98,    99,   100,   101,   102,    50,    28,    29,
      30,    31,    32,    33,    34,    35,    69,    70,    36,   118,
     119,   120,   128,   133,   103
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      10,   127,    49,    46,    47,    48,    51,   132,    27,    11,
      18,    19,    20,    21,    22,     3,     4,     5,     6,    90,
      68,    91,    92,    93,    16,    17,   125,   126,    41,    18,
      19,    20,    21,    22,   131,    23,    24,    67,    52,   135,
      25,    82,    83,    84,    26,    53,    54,    94,    85,    18,
      19,    20,    21,    22,    23,    24,    74,    75,    90,    25,
      91,    92,    93,    26,    66,   104,   107,    64,   108,    55,
      56,    61,    62,    63,    23,    24,    57,    58,    14,    25,
      15,   113,   114,    26,    96,   117,    94,    85,    18,    19,
      20,    21,    22,     3,     4,     5,     6,    43,    96,    44,
     117,    18,    19,    20,    21,    22,   117,    65,   116,     3,
       4,     5,     6,    23,    24,    59,    60,    14,    25,    80,
      81,    44,    26,   110,    71,     9,    23,    24,    88,    85,
     121,    25,    89,   105,     2,    26,    45,    19,    20,    21,
      22,   106,     3,     4,     5,     6,    76,    77,    78,    79,
     109,   112,   115,   122,   124,    16,   129,   130,   134,    87,
     123,    23,    24,    42,    86,   111,    25,     0,     0,    72,
      26,    73
};

static const yytype_int16 yycheck[] =
{
       1,   124,    26,    23,    24,    25,    22,   130,    14,     3,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      44,    14,    15,    16,    39,    40,   121,   122,     3,     3,
       4,     5,     6,     7,   129,    28,    29,    43,    21,   134,
      33,    61,    62,    63,    37,    17,    18,    40,    41,     3,
       4,     5,     6,     7,    28,    29,    53,    54,    12,    33,
      14,    15,    16,    37,     3,    89,    40,    38,    92,    19,
      20,    30,    31,    32,    28,    29,    26,    27,    35,    33,
      37,   105,   106,    37,    85,   109,    40,    41,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    35,    99,    37,
     124,     3,     4,     5,     6,     7,   130,    39,   109,     8,
       9,    10,    11,    28,    29,    28,    29,    35,    33,    59,
      60,    37,    37,    42,    38,     1,    28,    29,    38,    41,
      38,    33,    39,    37,     0,    37,     3,     4,     5,     6,
       7,    37,     8,     9,    10,    11,    55,    56,    57,    58,
      37,    40,    40,    38,    40,    39,    13,    40,    38,    65,
     116,    28,    29,    16,    64,    99,    33,    -1,    -1,    51,
      37,    52
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    44,     0,     8,     9,    10,    11,    45,    46,    50,
      53,     3,    51,    52,    35,    37,    39,    40,     3,     4,
       5,     6,     7,    28,    29,    33,    37,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    71,    47,    48,    49,
      53,     3,    52,    35,    37,     3,    67,    67,    67,    59,
      60,    22,    21,    17,    18,    19,    20,    26,    27,    28,
      29,    30,    31,    32,    38,    39,     3,    60,    59,    69,
      70,    38,    62,    63,    64,    64,    65,    65,    65,    65,
      66,    66,    67,    67,    67,    41,    54,    49,    38,    39,
      12,    14,    15,    16,    40,    50,    53,    54,    55,    56,
      57,    58,    59,    77,    59,    37,    37,    40,    59,    37,
      42,    57,    40,    59,    59,    40,    53,    59,    72,    73,
      74,    38,    38,    51,    40,    58,    58,    73,    75,    13,
      40,    58,    73,    76,    38,    58
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    43,    44,    44,    45,    45,    46,    47,    47,    48,
      48,    49,    50,    51,    51,    52,    52,    53,    53,    53,
      53,    54,    55,    55,    56,    56,    57,    57,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    59,    60,    60,
      61,    61,    62,    62,    63,    63,    63,    64,    64,    64,
      64,    64,    65,    65,    65,    66,    66,    66,    66,    67,
      67,    67,    67,    68,    68,    69,    69,    70,    70,    71,
      71,    71,    71,    71,    71,    72,    73,    73,    74,    74,
      75,    76,    77
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     6,     0,     1,     1,
       3,     2,     3,     1,     3,     1,     3,     1,     1,     1,
       1,     3,     0,     1,     1,     2,     1,     1,     1,     2,
       2,     3,     5,     7,     5,     1,     1,     1,     1,     3,
       1,     3,     1,     3,     1,     3,     3,     1,     3,     3,
       3,     3,     1,     3,     3,     1,     3,     3,     3,     1,
       2,     2,     2,     1,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     3,     2,     0,     1,     1,     1,
       1,     1,     9
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

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
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
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
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
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
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
  case 2: /* translation_unit: %empty  */
#line 78 "parser.y"
                                       { yyval = node(NK_TRANSLATION_UNIT, yylineno, NULL, 0); root = yyval; }
#line 1521 "parser.c"
    break;

  case 3: /* translation_unit: translation_unit external_decl  */
#line 79 "parser.y"
                                       {
        /* 누적된 노드 리스트 뒤에 새 external_decl 자식 추가 */
        Node **arr = (Node**)calloc(yyvsp[-1]->nchild+1, sizeof(Node*));
        for(int i=0;i<yyvsp[-1]->nchild;i++) arr[i]=yyvsp[-1]->child[i];
        arr[yyvsp[-1]->nchild]=yyvsp[0];

        /* nodev: 이미 구성된 배열을 자식으로 하는 새 노드 생성 */
        yyval = nodev(NK_TRANSLATION_UNIT, yylineno, NULL, yyvsp[-1]->nchild+1, arr);

        /* 이전 wrapper 노드의 child 배열/자원 정리(중첩 래핑 방지) */
        free(yyvsp[-1]->child); yyvsp[-1]->child=NULL; yyvsp[-1]->nchild=0; free(yyvsp[-1]);

        root = yyval;  /* 최신 루트를 전역에 갱신 */
    }
#line 1540 "parser.c"
    break;

  case 6: /* function_definition: type_spec IDENT '(' param_list_opt ')' compound_stmt  */
#line 108 "parser.y"
    { yyval = node(NK_FUNC_DEF, yylineno, yyvsp[-4]->op, 3, yyvsp[-5], yyvsp[-2], yyvsp[0]); free_ast(yyvsp[-4]); }
#line 1546 "parser.c"
    break;

  case 7: /* param_list_opt: %empty  */
#line 113 "parser.y"
                      { yyval = node(NK_PARAM_LIST, yylineno, NULL, 0); }
#line 1552 "parser.c"
    break;

  case 9: /* param_list: param_decl  */
#line 120 "parser.y"
    { yyval = node(NK_PARAM_LIST, yylineno, NULL, 1, yyvsp[0]); }
#line 1558 "parser.c"
    break;

  case 10: /* param_list: param_list ',' param_decl  */
#line 122 "parser.y"
    {
      Node **arr = (Node**)calloc(yyvsp[-2]->nchild+1, sizeof(Node*));
      for(int i=0;i<yyvsp[-2]->nchild;i++) arr[i]=yyvsp[-2]->child[i];
      arr[yyvsp[-2]->nchild] = yyvsp[0];
      yyval = nodev(NK_PARAM_LIST, yylineno, NULL, yyvsp[-2]->nchild+1, arr);
      free(yyvsp[-2]->child); yyvsp[-2]->child=NULL; yyvsp[-2]->nchild=0; free(yyvsp[-2]);
    }
#line 1570 "parser.c"
    break;

  case 11: /* param_decl: type_spec IDENT  */
#line 133 "parser.y"
                    { yyval = node(NK_PARAM, yylineno, yyvsp[0]->op, 1, yyvsp[-1]); free_ast(yyvsp[0]); }
#line 1576 "parser.c"
    break;

  case 12: /* declaration: type_spec init_declarator_list ';'  */
#line 139 "parser.y"
    { yyval = node(NK_DECL, yylineno, NULL, 2, yyvsp[-2], yyvsp[-1]); }
#line 1582 "parser.c"
    break;

  case 13: /* init_declarator_list: init_declarator  */
#line 145 "parser.y"
    { yyval = node(NK_INIT_DECL_LIST, yylineno, NULL, 1, yyvsp[0]); }
#line 1588 "parser.c"
    break;

  case 14: /* init_declarator_list: init_declarator_list ',' init_declarator  */
#line 147 "parser.y"
    {
      Node **arr = (Node**)calloc(yyvsp[-2]->nchild+1, sizeof(Node*));
      for(int i=0;i<yyvsp[-2]->nchild;i++) arr[i]=yyvsp[-2]->child[i];
      arr[yyvsp[-2]->nchild] = yyvsp[0];
      yyval = nodev(NK_INIT_DECL_LIST, yylineno, NULL, yyvsp[-2]->nchild+1, arr);
      free(yyvsp[-2]->child); yyvsp[-2]->child=NULL; yyvsp[-2]->nchild=0; free(yyvsp[-2]);
    }
#line 1600 "parser.c"
    break;

  case 15: /* init_declarator: IDENT  */
#line 162 "parser.y"
                         { yyval = node(NK_INIT_DECL, yylineno, yyvsp[0]->op, 1, NULL); free_ast(yyvsp[0]); }
#line 1606 "parser.c"
    break;

  case 16: /* init_declarator: IDENT '=' assignment  */
#line 163 "parser.y"
                         { yyval = node(NK_INIT_DECL, yylineno, yyvsp[-2]->op, 1, yyvsp[0]);   free_ast(yyvsp[-2]); }
#line 1612 "parser.c"
    break;

  case 17: /* type_spec: INT  */
#line 168 "parser.y"
          { yyval = node(NK_TYPE, yylineno, "int", 0); }
#line 1618 "parser.c"
    break;

  case 18: /* type_spec: FLOAT  */
#line 169 "parser.y"
          { yyval = node(NK_TYPE, yylineno, "float", 0); }
#line 1624 "parser.c"
    break;

  case 19: /* type_spec: CHAR  */
#line 170 "parser.y"
          { yyval = node(NK_TYPE, yylineno, "char", 0); }
#line 1630 "parser.c"
    break;

  case 20: /* type_spec: VOID  */
#line 171 "parser.y"
          { yyval = node(NK_TYPE, yylineno, "void", 0); }
#line 1636 "parser.c"
    break;

  case 21: /* compound_stmt: '{' stmt_decl_list_opt '}'  */
#line 176 "parser.y"
                               { yyval = node(NK_COMPOUND, yylineno, NULL, 1, yyvsp[-1]); }
#line 1642 "parser.c"
    break;

  case 22: /* stmt_decl_list_opt: %empty  */
#line 181 "parser.y"
                                  { yyval = node(NK_STMT_LIST, yylineno, NULL, 0); }
#line 1648 "parser.c"
    break;

  case 24: /* stmt_decl_list: stmt_or_decl  */
#line 188 "parser.y"
    { yyval = node(NK_STMT_LIST, yylineno, NULL, 1, yyvsp[0]); }
#line 1654 "parser.c"
    break;

  case 25: /* stmt_decl_list: stmt_decl_list stmt_or_decl  */
#line 190 "parser.y"
    {
      Node **arr = (Node**)calloc(yyvsp[-1]->nchild+1, sizeof(Node*));
      for(int i=0;i<yyvsp[-1]->nchild;i++) arr[i]=yyvsp[-1]->child[i];
      arr[yyvsp[-1]->nchild] = yyvsp[0];
      yyval = nodev(NK_STMT_LIST, yylineno, NULL, yyvsp[-1]->nchild+1, arr);
      free(yyvsp[-1]->child); yyvsp[-1]->child=NULL; yyvsp[-1]->nchild=0; free(yyvsp[-1]);
    }
#line 1666 "parser.c"
    break;

  case 28: /* statement: ';'  */
#line 207 "parser.y"
                                { yyval = node(NK_EXPR_STMT, yylineno, NULL, 0); }
#line 1672 "parser.c"
    break;

  case 29: /* statement: expr ';'  */
#line 208 "parser.y"
                                { yyval = node(NK_EXPR_STMT, yylineno, NULL, 1, yyvsp[-1]); }
#line 1678 "parser.c"
    break;

  case 30: /* statement: RETURN ';'  */
#line 209 "parser.y"
                                { yyval = node(NK_RETURN,    yylineno, NULL, 0); }
#line 1684 "parser.c"
    break;

  case 31: /* statement: RETURN expr ';'  */
#line 210 "parser.y"
                                { yyval = node(NK_RETURN,    yylineno, NULL, 1, yyvsp[-1]); }
#line 1690 "parser.c"
    break;

  case 32: /* statement: IF '(' expr ')' statement  */
#line 212 "parser.y"
                                                    { yyval = node(NK_IF, yylineno, NULL, 2, yyvsp[-2], yyvsp[0]); }
#line 1696 "parser.c"
    break;

  case 33: /* statement: IF '(' expr ')' statement ELSE statement  */
#line 215 "parser.y"
                                { yyval = node(NK_IF, yylineno, "else", 3, yyvsp[-4], yyvsp[-2], yyvsp[0]); }
#line 1702 "parser.c"
    break;

  case 34: /* statement: WHILE '(' expr ')' statement  */
#line 216 "parser.y"
                                { yyval = node(NK_WHILE, yylineno, NULL, 2, yyvsp[-2], yyvsp[0]); }
#line 1708 "parser.c"
    break;

  case 39: /* assignment: IDENT '=' assignment  */
#line 229 "parser.y"
                         { yyval = node(NK_ASSIGN, yylineno, yyvsp[-2]->op, 1, yyvsp[0]); free_ast(yyvsp[-2]); }
#line 1714 "parser.c"
    break;

  case 41: /* logical_or: logical_or OR logical_and  */
#line 235 "parser.y"
                                  { yyval = node(NK_BINOP, yylineno, "||", 2, yyvsp[-2], yyvsp[0]); }
#line 1720 "parser.c"
    break;

  case 43: /* logical_and: logical_and AND equality  */
#line 241 "parser.y"
                                  { yyval = node(NK_BINOP, yylineno, "&&", 2, yyvsp[-2], yyvsp[0]); }
#line 1726 "parser.c"
    break;

  case 45: /* equality: equality EQ relational  */
#line 247 "parser.y"
                                  { yyval = node(NK_BINOP, yylineno, "==", 2, yyvsp[-2], yyvsp[0]); }
#line 1732 "parser.c"
    break;

  case 46: /* equality: equality NE relational  */
#line 248 "parser.y"
                                  { yyval = node(NK_BINOP, yylineno, "!=", 2, yyvsp[-2], yyvsp[0]); }
#line 1738 "parser.c"
    break;

  case 48: /* relational: relational '<' additive  */
#line 254 "parser.y"
                                  { yyval = node(NK_BINOP, yylineno, "<",  2, yyvsp[-2], yyvsp[0]); }
#line 1744 "parser.c"
    break;

  case 49: /* relational: relational '>' additive  */
#line 255 "parser.y"
                                  { yyval = node(NK_BINOP, yylineno, ">",  2, yyvsp[-2], yyvsp[0]); }
#line 1750 "parser.c"
    break;

  case 50: /* relational: relational LE additive  */
#line 256 "parser.y"
                                  { yyval = node(NK_BINOP, yylineno, "<=", 2, yyvsp[-2], yyvsp[0]); }
#line 1756 "parser.c"
    break;

  case 51: /* relational: relational GE additive  */
#line 257 "parser.y"
                                  { yyval = node(NK_BINOP, yylineno, ">=", 2, yyvsp[-2], yyvsp[0]); }
#line 1762 "parser.c"
    break;

  case 53: /* additive: additive '+' multiplicative  */
#line 263 "parser.y"
                                  { yyval = node(NK_BINOP, yylineno, "+", 2, yyvsp[-2], yyvsp[0]); }
#line 1768 "parser.c"
    break;

  case 54: /* additive: additive '-' multiplicative  */
#line 264 "parser.y"
                                  { yyval = node(NK_BINOP, yylineno, "-", 2, yyvsp[-2], yyvsp[0]); }
#line 1774 "parser.c"
    break;

  case 56: /* multiplicative: multiplicative '*' unary  */
#line 270 "parser.y"
                                  { yyval = node(NK_BINOP, yylineno, "*", 2, yyvsp[-2], yyvsp[0]); }
#line 1780 "parser.c"
    break;

  case 57: /* multiplicative: multiplicative '/' unary  */
#line 271 "parser.y"
                                  { yyval = node(NK_BINOP, yylineno, "/", 2, yyvsp[-2], yyvsp[0]); }
#line 1786 "parser.c"
    break;

  case 58: /* multiplicative: multiplicative '%' unary  */
#line 272 "parser.y"
                                  { yyval = node(NK_BINOP, yylineno, "%", 2, yyvsp[-2], yyvsp[0]); }
#line 1792 "parser.c"
    break;

  case 60: /* unary: '!' unary  */
#line 278 "parser.y"
                                  { yyval = node(NK_UNOP, yylineno, "!",   1, yyvsp[0]); }
#line 1798 "parser.c"
    break;

  case 61: /* unary: '-' unary  */
#line 279 "parser.y"
                                  { yyval = node(NK_UNOP, yylineno, "neg", 1, yyvsp[0]); }
#line 1804 "parser.c"
    break;

  case 62: /* unary: '+' unary  */
#line 280 "parser.y"
                                  { yyval = yyvsp[0]; }
#line 1810 "parser.c"
    break;

  case 64: /* postfix: IDENT '(' arg_list_opt ')'  */
#line 286 "parser.y"
                                  { yyval = node(NK_CALL, yylineno, yyvsp[-3]->op, 1, yyvsp[-1]); free_ast(yyvsp[-3]); }
#line 1816 "parser.c"
    break;

  case 65: /* arg_list_opt: %empty  */
#line 291 "parser.y"
                                  { yyval = node(NK_ARG_LIST, yylineno, NULL, 0); }
#line 1822 "parser.c"
    break;

  case 67: /* arg_list: expr  */
#line 297 "parser.y"
                                  { yyval = node(NK_ARG_LIST, yylineno, NULL, 1, yyvsp[0]); }
#line 1828 "parser.c"
    break;

  case 68: /* arg_list: arg_list ',' expr  */
#line 299 "parser.y"
    {
      Node **arr = (Node**)calloc(yyvsp[-2]->nchild+1, sizeof(Node*));
      for(int i=0;i<yyvsp[-2]->nchild;i++) arr[i]=yyvsp[-2]->child[i];
      arr[yyvsp[-2]->nchild] = yyvsp[0];
      yyval = nodev(NK_ARG_LIST, yylineno, NULL, yyvsp[-2]->nchild+1, arr);
      free(yyvsp[-2]->child); yyvsp[-2]->child=NULL; yyvsp[-2]->nchild=0; free(yyvsp[-2]);
    }
#line 1840 "parser.c"
    break;

  case 69: /* primary: IDENT  */
#line 313 "parser.y"
                  { yyval = yyvsp[0]; }
#line 1846 "parser.c"
    break;

  case 70: /* primary: INT_CONST  */
#line 314 "parser.y"
                  { yyval = yyvsp[0]; }
#line 1852 "parser.c"
    break;

  case 71: /* primary: FLOAT_CONST  */
#line 315 "parser.y"
                  { yyval = yyvsp[0]; }
#line 1858 "parser.c"
    break;

  case 72: /* primary: CHAR_CONST  */
#line 316 "parser.y"
                  { yyval = yyvsp[0]; }
#line 1864 "parser.c"
    break;

  case 73: /* primary: STRING_LITERAL  */
#line 317 "parser.y"
                  { yyval = yyvsp[0]; }
#line 1870 "parser.c"
    break;

  case 74: /* primary: '(' expr ')'  */
#line 318 "parser.y"
                  { yyval = yyvsp[-1]; }
#line 1876 "parser.c"
    break;

  case 75: /* simple_decl: type_spec init_declarator_list  */
#line 324 "parser.y"
    { yyval = node(NK_DECL, yylineno, NULL, 2, yyvsp[-1], yyvsp[0]); }
#line 1882 "parser.c"
    break;

  case 76: /* expr_opt: %empty  */
#line 329 "parser.y"
                { yyval = NULL; }
#line 1888 "parser.c"
    break;

  case 77: /* expr_opt: expr  */
#line 330 "parser.y"
                { yyval = yyvsp[0]; }
#line 1894 "parser.c"
    break;

  case 82: /* for_stmt: FOR '(' for_init_opt ';' for_cond_opt ';' for_step_opt ')' statement  */
#line 350 "parser.y"
    { yyval = node(NK_FOR, yylineno, NULL, 4, yyvsp[-6], yyvsp[-4], yyvsp[-2], yyvsp[0]); }
#line 1900 "parser.c"
    break;


#line 1904 "parser.c"

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

#line 353 "parser.y"
  /* ===================== 문법 규칙(Grammar) 영역 끝 ===================== */

/* Bison이 구문 오류를 발견했을 때 호출하는 함수 */
void yyerror(const char *s){
  fprintf(stderr, "Parse error at line %d: %s\n", yylineno, s);
}
