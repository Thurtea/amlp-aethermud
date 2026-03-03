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
#line 3 "grammar.y"


extern char *outp;
#include "std.h"
#include "compiler.h"
#include "lex.h"
#include "scratchpad.h"

#include "lpc_incl.h"
#include "simul_efun.h"
#include "generate.h"
#include "master.h"

/* gross. Necessary? - Beek */
#ifdef WIN32
#define MSDOS
#endif
#define YYSTACK_USE_ALLOCA 0
#line 20 "grammar.y.pre"
/*
 * This is the grammar definition of LPC, and its parse tree generator.
 */

/* down to one global :) 
   bits:
      SWITCH_CONTEXT     - we're inside a switch
      LOOP_CONTEXT       - we're inside a loop
      SWITCH_STRINGS     - a string case has been found
      SWITCH_NUMBERS     - a non-zero numeric case has been found
      SWITCH_RANGES      - a range has been found
      SWITCH_DEFAULT     - a default has been found
 */
int context;
int num_refs;
int func_present;
/*
 * bison & yacc don't prototype this in y.tab.h
 */
int yyparse (void);


#line 113 "grammar.tab.c"

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
# define YYDEBUG 0
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
    L_STRING = 258,                /* L_STRING  */
    L_NUMBER = 259,                /* L_NUMBER  */
    L_REAL = 260,                  /* L_REAL  */
    L_BASIC_TYPE = 261,            /* L_BASIC_TYPE  */
    L_TYPE_MODIFIER = 262,         /* L_TYPE_MODIFIER  */
    L_DEFINED_NAME = 263,          /* L_DEFINED_NAME  */
    L_IDENTIFIER = 264,            /* L_IDENTIFIER  */
    L_EFUN = 265,                  /* L_EFUN  */
    L_INC = 266,                   /* L_INC  */
    L_DEC = 267,                   /* L_DEC  */
    L_ASSIGN = 268,                /* L_ASSIGN  */
    L_LAND = 269,                  /* L_LAND  */
    L_LOR = 270,                   /* L_LOR  */
    L_LSH = 271,                   /* L_LSH  */
    L_RSH = 272,                   /* L_RSH  */
    L_ORDER = 273,                 /* L_ORDER  */
    L_NOT = 274,                   /* L_NOT  */
    L_IF = 275,                    /* L_IF  */
    L_ELSE = 276,                  /* L_ELSE  */
    L_SWITCH = 277,                /* L_SWITCH  */
    L_CASE = 278,                  /* L_CASE  */
    L_DEFAULT = 279,               /* L_DEFAULT  */
    L_RANGE = 280,                 /* L_RANGE  */
    L_DOT_DOT_DOT = 281,           /* L_DOT_DOT_DOT  */
    L_WHILE = 282,                 /* L_WHILE  */
    L_DO = 283,                    /* L_DO  */
    L_FOR = 284,                   /* L_FOR  */
    L_FOREACH = 285,               /* L_FOREACH  */
    L_IN = 286,                    /* L_IN  */
    L_BREAK = 287,                 /* L_BREAK  */
    L_CONTINUE = 288,              /* L_CONTINUE  */
    L_RETURN = 289,                /* L_RETURN  */
    L_ARROW = 290,                 /* L_ARROW  */
    L_INHERIT = 291,               /* L_INHERIT  */
    L_COLON_COLON = 292,           /* L_COLON_COLON  */
    L_ARRAY_OPEN = 293,            /* L_ARRAY_OPEN  */
    L_MAPPING_OPEN = 294,          /* L_MAPPING_OPEN  */
    L_FUNCTION_OPEN = 295,         /* L_FUNCTION_OPEN  */
    L_NEW_FUNCTION_OPEN = 296,     /* L_NEW_FUNCTION_OPEN  */
    L_SSCANF = 297,                /* L_SSCANF  */
    L_CATCH = 298,                 /* L_CATCH  */
    L_ARRAY = 299,                 /* L_ARRAY  */
    L_REF = 300,                   /* L_REF  */
    L_PARSE_COMMAND = 301,         /* L_PARSE_COMMAND  */
    L_TIME_EXPRESSION = 302,       /* L_TIME_EXPRESSION  */
    L_CLASS = 303,                 /* L_CLASS  */
    L_NEW = 304,                   /* L_NEW  */
    L_PARAMETER = 305,             /* L_PARAMETER  */
    LOWER_THAN_ELSE = 306,         /* LOWER_THAN_ELSE  */
    L_EQ = 307,                    /* L_EQ  */
    L_NE = 308                     /* L_NE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define L_STRING 258
#define L_NUMBER 259
#define L_REAL 260
#define L_BASIC_TYPE 261
#define L_TYPE_MODIFIER 262
#define L_DEFINED_NAME 263
#define L_IDENTIFIER 264
#define L_EFUN 265
#define L_INC 266
#define L_DEC 267
#define L_ASSIGN 268
#define L_LAND 269
#define L_LOR 270
#define L_LSH 271
#define L_RSH 272
#define L_ORDER 273
#define L_NOT 274
#define L_IF 275
#define L_ELSE 276
#define L_SWITCH 277
#define L_CASE 278
#define L_DEFAULT 279
#define L_RANGE 280
#define L_DOT_DOT_DOT 281
#define L_WHILE 282
#define L_DO 283
#define L_FOR 284
#define L_FOREACH 285
#define L_IN 286
#define L_BREAK 287
#define L_CONTINUE 288
#define L_RETURN 289
#define L_ARROW 290
#define L_INHERIT 291
#define L_COLON_COLON 292
#define L_ARRAY_OPEN 293
#define L_MAPPING_OPEN 294
#define L_FUNCTION_OPEN 295
#define L_NEW_FUNCTION_OPEN 296
#define L_SSCANF 297
#define L_CATCH 298
#define L_ARRAY 299
#define L_REF 300
#define L_PARSE_COMMAND 301
#define L_TIME_EXPRESSION 302
#define L_CLASS 303
#define L_NEW 304
#define L_PARAMETER 305
#define LOWER_THAN_ELSE 306
#define L_EQ 307
#define L_NE 308

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 124 "grammar.y"

    POINTER_INT pointer_int;
    long number;
    float real;
    char *string;
    struct { short num_arg; char flags; } argument;
    ident_hash_elem_t *ihe;
    parse_node_t *node;
    function_context_t *contextp;
    struct {
	parse_node_t *node;
        char num;
    } decl; /* 5 */
    struct {
	char num_local;
	char max_num_locals; 
	short context; 
	short save_current_type; 
	short save_exact_types;
    } func_block; /* 8 */

#line 294 "grammar.tab.c"

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
  YYSYMBOL_L_STRING = 3,                   /* L_STRING  */
  YYSYMBOL_L_NUMBER = 4,                   /* L_NUMBER  */
  YYSYMBOL_L_REAL = 5,                     /* L_REAL  */
  YYSYMBOL_L_BASIC_TYPE = 6,               /* L_BASIC_TYPE  */
  YYSYMBOL_L_TYPE_MODIFIER = 7,            /* L_TYPE_MODIFIER  */
  YYSYMBOL_L_DEFINED_NAME = 8,             /* L_DEFINED_NAME  */
  YYSYMBOL_L_IDENTIFIER = 9,               /* L_IDENTIFIER  */
  YYSYMBOL_L_EFUN = 10,                    /* L_EFUN  */
  YYSYMBOL_L_INC = 11,                     /* L_INC  */
  YYSYMBOL_L_DEC = 12,                     /* L_DEC  */
  YYSYMBOL_L_ASSIGN = 13,                  /* L_ASSIGN  */
  YYSYMBOL_L_LAND = 14,                    /* L_LAND  */
  YYSYMBOL_L_LOR = 15,                     /* L_LOR  */
  YYSYMBOL_L_LSH = 16,                     /* L_LSH  */
  YYSYMBOL_L_RSH = 17,                     /* L_RSH  */
  YYSYMBOL_L_ORDER = 18,                   /* L_ORDER  */
  YYSYMBOL_L_NOT = 19,                     /* L_NOT  */
  YYSYMBOL_L_IF = 20,                      /* L_IF  */
  YYSYMBOL_L_ELSE = 21,                    /* L_ELSE  */
  YYSYMBOL_L_SWITCH = 22,                  /* L_SWITCH  */
  YYSYMBOL_L_CASE = 23,                    /* L_CASE  */
  YYSYMBOL_L_DEFAULT = 24,                 /* L_DEFAULT  */
  YYSYMBOL_L_RANGE = 25,                   /* L_RANGE  */
  YYSYMBOL_L_DOT_DOT_DOT = 26,             /* L_DOT_DOT_DOT  */
  YYSYMBOL_L_WHILE = 27,                   /* L_WHILE  */
  YYSYMBOL_L_DO = 28,                      /* L_DO  */
  YYSYMBOL_L_FOR = 29,                     /* L_FOR  */
  YYSYMBOL_L_FOREACH = 30,                 /* L_FOREACH  */
  YYSYMBOL_L_IN = 31,                      /* L_IN  */
  YYSYMBOL_L_BREAK = 32,                   /* L_BREAK  */
  YYSYMBOL_L_CONTINUE = 33,                /* L_CONTINUE  */
  YYSYMBOL_L_RETURN = 34,                  /* L_RETURN  */
  YYSYMBOL_L_ARROW = 35,                   /* L_ARROW  */
  YYSYMBOL_L_INHERIT = 36,                 /* L_INHERIT  */
  YYSYMBOL_L_COLON_COLON = 37,             /* L_COLON_COLON  */
  YYSYMBOL_L_ARRAY_OPEN = 38,              /* L_ARRAY_OPEN  */
  YYSYMBOL_L_MAPPING_OPEN = 39,            /* L_MAPPING_OPEN  */
  YYSYMBOL_L_FUNCTION_OPEN = 40,           /* L_FUNCTION_OPEN  */
  YYSYMBOL_L_NEW_FUNCTION_OPEN = 41,       /* L_NEW_FUNCTION_OPEN  */
  YYSYMBOL_L_SSCANF = 42,                  /* L_SSCANF  */
  YYSYMBOL_L_CATCH = 43,                   /* L_CATCH  */
  YYSYMBOL_L_ARRAY = 44,                   /* L_ARRAY  */
  YYSYMBOL_L_REF = 45,                     /* L_REF  */
  YYSYMBOL_L_PARSE_COMMAND = 46,           /* L_PARSE_COMMAND  */
  YYSYMBOL_L_TIME_EXPRESSION = 47,         /* L_TIME_EXPRESSION  */
  YYSYMBOL_L_CLASS = 48,                   /* L_CLASS  */
  YYSYMBOL_L_NEW = 49,                     /* L_NEW  */
  YYSYMBOL_L_PARAMETER = 50,               /* L_PARAMETER  */
  YYSYMBOL_LOWER_THAN_ELSE = 51,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_52_ = 52,                       /* '?'  */
  YYSYMBOL_53_ = 53,                       /* '|'  */
  YYSYMBOL_54_ = 54,                       /* '^'  */
  YYSYMBOL_55_ = 55,                       /* '&'  */
  YYSYMBOL_L_EQ = 56,                      /* L_EQ  */
  YYSYMBOL_L_NE = 57,                      /* L_NE  */
  YYSYMBOL_58_ = 58,                       /* '<'  */
  YYSYMBOL_59_ = 59,                       /* '+'  */
  YYSYMBOL_60_ = 60,                       /* '-'  */
  YYSYMBOL_61_ = 61,                       /* '*'  */
  YYSYMBOL_62_ = 62,                       /* '%'  */
  YYSYMBOL_63_ = 63,                       /* '/'  */
  YYSYMBOL_64_ = 64,                       /* '~'  */
  YYSYMBOL_65_ = 65,                       /* ';'  */
  YYSYMBOL_66_ = 66,                       /* '('  */
  YYSYMBOL_67_ = 67,                       /* ')'  */
  YYSYMBOL_68_ = 68,                       /* ':'  */
  YYSYMBOL_69_ = 69,                       /* ','  */
  YYSYMBOL_70_ = 70,                       /* '{'  */
  YYSYMBOL_71_ = 71,                       /* '}'  */
  YYSYMBOL_72_ = 72,                       /* '$'  */
  YYSYMBOL_73_ = 73,                       /* '['  */
  YYSYMBOL_74_ = 74,                       /* ']'  */
  YYSYMBOL_YYACCEPT = 75,                  /* $accept  */
  YYSYMBOL_all = 76,                       /* all  */
  YYSYMBOL_program = 77,                   /* program  */
  YYSYMBOL_possible_semi_colon = 78,       /* possible_semi_colon  */
  YYSYMBOL_inheritance = 79,               /* inheritance  */
  YYSYMBOL_real = 80,                      /* real  */
  YYSYMBOL_number = 81,                    /* number  */
  YYSYMBOL_optional_star = 82,             /* optional_star  */
  YYSYMBOL_block_or_semi = 83,             /* block_or_semi  */
  YYSYMBOL_identifier = 84,                /* identifier  */
  YYSYMBOL_def = 85,                       /* def  */
  YYSYMBOL_86_1 = 86,                      /* $@1  */
  YYSYMBOL_87_2 = 87,                      /* @2  */
  YYSYMBOL_modifier_change = 88,           /* modifier_change  */
  YYSYMBOL_member_name = 89,               /* member_name  */
  YYSYMBOL_member_name_list = 90,          /* member_name_list  */
  YYSYMBOL_member_list = 91,               /* member_list  */
  YYSYMBOL_92_3 = 92,                      /* $@3  */
  YYSYMBOL_type_decl = 93,                 /* type_decl  */
  YYSYMBOL_94_4 = 94,                      /* @4  */
  YYSYMBOL_new_local_name = 95,            /* new_local_name  */
  YYSYMBOL_atomic_type = 96,               /* atomic_type  */
  YYSYMBOL_opt_atomic_type = 97,           /* opt_atomic_type  */
  YYSYMBOL_basic_type = 98,                /* basic_type  */
  YYSYMBOL_arg_type = 99,                  /* arg_type  */
  YYSYMBOL_new_arg = 100,                  /* new_arg  */
  YYSYMBOL_argument = 101,                 /* argument  */
  YYSYMBOL_argument_list = 102,            /* argument_list  */
  YYSYMBOL_type_modifier_list = 103,       /* type_modifier_list  */
  YYSYMBOL_type = 104,                     /* type  */
  YYSYMBOL_cast = 105,                     /* cast  */
  YYSYMBOL_opt_basic_type = 106,           /* opt_basic_type  */
  YYSYMBOL_name_list = 107,                /* name_list  */
  YYSYMBOL_new_name = 108,                 /* new_name  */
  YYSYMBOL_block = 109,                    /* block  */
  YYSYMBOL_decl_block = 110,               /* decl_block  */
  YYSYMBOL_local_declarations = 111,       /* local_declarations  */
  YYSYMBOL_112_5 = 112,                    /* $@5  */
  YYSYMBOL_new_local_def = 113,            /* new_local_def  */
  YYSYMBOL_single_new_local_def = 114,     /* single_new_local_def  */
  YYSYMBOL_single_new_local_def_with_init = 115, /* single_new_local_def_with_init  */
  YYSYMBOL_local_name_list = 116,          /* local_name_list  */
  YYSYMBOL_statements = 117,               /* statements  */
  YYSYMBOL_statement = 118,                /* statement  */
  YYSYMBOL_while = 119,                    /* while  */
  YYSYMBOL_120_6 = 120,                    /* $@6  */
  YYSYMBOL_do = 121,                       /* do  */
  YYSYMBOL_122_7 = 122,                    /* $@7  */
  YYSYMBOL_for = 123,                      /* for  */
  YYSYMBOL_124_8 = 124,                    /* $@8  */
  YYSYMBOL_foreach_var = 125,              /* foreach_var  */
  YYSYMBOL_foreach_vars = 126,             /* foreach_vars  */
  YYSYMBOL_foreach = 127,                  /* foreach  */
  YYSYMBOL_128_9 = 128,                    /* $@9  */
  YYSYMBOL_for_expr = 129,                 /* for_expr  */
  YYSYMBOL_first_for_expr = 130,           /* first_for_expr  */
  YYSYMBOL_switch = 131,                   /* switch  */
  YYSYMBOL_132_10 = 132,                   /* $@10  */
  YYSYMBOL_switch_block = 133,             /* switch_block  */
  YYSYMBOL_case = 134,                     /* case  */
  YYSYMBOL_case_label = 135,               /* case_label  */
  YYSYMBOL_constant = 136,                 /* constant  */
  YYSYMBOL_comma_expr = 137,               /* comma_expr  */
  YYSYMBOL_ref = 138,                      /* ref  */
  YYSYMBOL_expr0 = 139,                    /* expr0  */
  YYSYMBOL_return = 140,                   /* return  */
  YYSYMBOL_expr_list = 141,                /* expr_list  */
  YYSYMBOL_expr_list_node = 142,           /* expr_list_node  */
  YYSYMBOL_expr_list2 = 143,               /* expr_list2  */
  YYSYMBOL_expr_list3 = 144,               /* expr_list3  */
  YYSYMBOL_expr_list4 = 145,               /* expr_list4  */
  YYSYMBOL_assoc_pair = 146,               /* assoc_pair  */
  YYSYMBOL_lvalue = 147,                   /* lvalue  */
  YYSYMBOL_l_new_function_open = 148,      /* l_new_function_open  */
  YYSYMBOL_expr4 = 149,                    /* expr4  */
  YYSYMBOL_150_11 = 150,                   /* @11  */
  YYSYMBOL_151_12 = 151,                   /* @12  */
  YYSYMBOL_expr_or_block = 152,            /* expr_or_block  */
  YYSYMBOL_catch = 153,                    /* catch  */
  YYSYMBOL_154_13 = 154,                   /* @13  */
  YYSYMBOL_sscanf = 155,                   /* sscanf  */
  YYSYMBOL_parse_command = 156,            /* parse_command  */
  YYSYMBOL_time_expression = 157,          /* time_expression  */
  YYSYMBOL_158_14 = 158,                   /* @14  */
  YYSYMBOL_lvalue_list = 159,              /* lvalue_list  */
  YYSYMBOL_string = 160,                   /* string  */
  YYSYMBOL_string_con1 = 161,              /* string_con1  */
  YYSYMBOL_string_con2 = 162,              /* string_con2  */
  YYSYMBOL_class_init = 163,               /* class_init  */
  YYSYMBOL_opt_class_init = 164,           /* opt_class_init  */
  YYSYMBOL_function_call = 165,            /* function_call  */
  YYSYMBOL_166_15 = 166,                   /* @15  */
  YYSYMBOL_167_16 = 167,                   /* @16  */
  YYSYMBOL_168_17 = 168,                   /* @17  */
  YYSYMBOL_169_18 = 169,                   /* @18  */
  YYSYMBOL_170_19 = 170,                   /* @19  */
  YYSYMBOL_171_20 = 171,                   /* @20  */
  YYSYMBOL_efun_override = 172,            /* efun_override  */
  YYSYMBOL_function_name = 173,            /* function_name  */
  YYSYMBOL_cond = 174,                     /* cond  */
  YYSYMBOL_optional_else_part = 175        /* optional_else_part  */
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
typedef yytype_int16 yy_state_t;

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1834

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  75
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  101
/* YYNRULES -- Number of rules.  */
#define YYNRULES  257
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  485

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   308


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
       2,     2,     2,     2,     2,     2,    72,    62,    55,     2,
      66,    67,    61,    59,    69,    60,     2,    63,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    68,    65,
      58,     2,     2,    52,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    73,     2,    74,    54,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    70,    53,    71,    64,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    56,    57
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   213,   213,   221,   227,   233,   235,   245,   329,   337,
     346,   350,   358,   366,   371,   379,   384,   389,   415,   388,
     473,   480,   481,   482,   485,   503,   517,   518,   521,   524,
     523,   533,   532,   613,   614,   632,   633,   650,   666,   668,
     675,   676,   684,   685,   693,   700,   709,   723,   728,   729,
     748,   760,   775,   779,   789,   798,   806,   808,   815,   816,
     820,   846,   902,   912,   912,   912,   916,   922,   921,   943,
     955,   990,  1002,  1035,  1041,  1053,  1057,  1064,  1072,  1085,
    1086,  1087,  1088,  1089,  1090,  1096,  1101,  1124,  1138,  1137,
    1153,  1152,  1168,  1167,  1193,  1215,  1226,  1244,  1250,  1262,
    1261,  1283,  1287,  1291,  1297,  1307,  1306,  1347,  1354,  1362,
    1370,  1378,  1393,  1408,  1422,  1439,  1454,  1471,  1476,  1481,
    1486,  1491,  1496,  1505,  1510,  1515,  1520,  1525,  1530,  1535,
    1540,  1545,  1550,  1555,  1560,  1565,  1573,  1578,  1586,  1590,
    1619,  1645,  1651,  1676,  1683,  1690,  1716,  1721,  1745,  1768,
    1783,  1828,  1866,  1871,  1876,  2047,  2142,  2223,  2228,  2324,
    2346,  2368,  2391,  2401,  2413,  2438,  2461,  2483,  2484,  2485,
    2486,  2487,  2488,  2492,  2499,  2521,  2525,  2530,  2538,  2543,
    2551,  2558,  2572,  2577,  2582,  2590,  2601,  2620,  2628,  2744,
    2745,  2754,  2755,  2798,  2815,  2821,  2820,  2852,  2877,  2885,
    2890,  2898,  2906,  2911,  2916,  2962,  3017,  3018,  3023,  3025,
    3024,  3081,  3119,  3214,  3237,  3246,  3258,  3263,  3272,  3271,
    3287,  3297,  3309,  3308,  3324,  3330,  3345,  3354,  3355,  3360,
    3368,  3369,  3376,  3388,  3392,  3403,  3402,  3418,  3417,  3450,
    3486,  3506,  3505,  3575,  3574,  3648,  3647,  3701,  3700,  3732,
    3758,  3774,  3775,  3790,  3806,  3822,  3857,  3862
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
  "\"end of file\"", "error", "\"invalid token\"", "L_STRING", "L_NUMBER",
  "L_REAL", "L_BASIC_TYPE", "L_TYPE_MODIFIER", "L_DEFINED_NAME",
  "L_IDENTIFIER", "L_EFUN", "L_INC", "L_DEC", "L_ASSIGN", "L_LAND",
  "L_LOR", "L_LSH", "L_RSH", "L_ORDER", "L_NOT", "L_IF", "L_ELSE",
  "L_SWITCH", "L_CASE", "L_DEFAULT", "L_RANGE", "L_DOT_DOT_DOT", "L_WHILE",
  "L_DO", "L_FOR", "L_FOREACH", "L_IN", "L_BREAK", "L_CONTINUE",
  "L_RETURN", "L_ARROW", "L_INHERIT", "L_COLON_COLON", "L_ARRAY_OPEN",
  "L_MAPPING_OPEN", "L_FUNCTION_OPEN", "L_NEW_FUNCTION_OPEN", "L_SSCANF",
  "L_CATCH", "L_ARRAY", "L_REF", "L_PARSE_COMMAND", "L_TIME_EXPRESSION",
  "L_CLASS", "L_NEW", "L_PARAMETER", "LOWER_THAN_ELSE", "'?'", "'|'",
  "'^'", "'&'", "L_EQ", "L_NE", "'<'", "'+'", "'-'", "'*'", "'%'", "'/'",
  "'~'", "';'", "'('", "')'", "':'", "','", "'{'", "'}'", "'$'", "'['",
  "']'", "$accept", "all", "program", "possible_semi_colon", "inheritance",
  "real", "number", "optional_star", "block_or_semi", "identifier", "def",
  "$@1", "@2", "modifier_change", "member_name", "member_name_list",
  "member_list", "$@3", "type_decl", "@4", "new_local_name", "atomic_type",
  "opt_atomic_type", "basic_type", "arg_type", "new_arg", "argument",
  "argument_list", "type_modifier_list", "type", "cast", "opt_basic_type",
  "name_list", "new_name", "block", "decl_block", "local_declarations",
  "$@5", "new_local_def", "single_new_local_def",
  "single_new_local_def_with_init", "local_name_list", "statements",
  "statement", "while", "$@6", "do", "$@7", "for", "$@8", "foreach_var",
  "foreach_vars", "foreach", "$@9", "for_expr", "first_for_expr", "switch",
  "$@10", "switch_block", "case", "case_label", "constant", "comma_expr",
  "ref", "expr0", "return", "expr_list", "expr_list_node", "expr_list2",
  "expr_list3", "expr_list4", "assoc_pair", "lvalue",
  "l_new_function_open", "expr4", "@11", "@12", "expr_or_block", "catch",
  "@13", "sscanf", "parse_command", "time_expression", "@14",
  "lvalue_list", "string", "string_con1", "string_con2", "class_init",
  "opt_class_init", "function_call", "@15", "@16", "@17", "@18", "@19",
  "@20", "efun_override", "function_name", "cond", "optional_else_part", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-386)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-252)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -386,    47,   161,  -386,   123,  -386,     8,  -386,  -386,   134,
      82,  -386,  -386,  -386,  -386,    19,   290,  -386,   115,   137,
    -386,  -386,  -386,   334,   102,   135,  -386,    19,    91,   211,
     163,   180,   190,  -386,  -386,  -386,     4,  -386,    82,    -1,
      19,  -386,  -386,  -386,  1623,   229,   334,  -386,  -386,  -386,
    -386,   260,  -386,  -386,   253,   -17,    -9,   265,   279,   279,
    1623,   334,  1131,   489,  1623,  -386,   255,  -386,  -386,   261,
    -386,   280,  -386,  1623,  1623,   919,   297,  -386,  -386,   328,
    1623,   279,  1099,   267,   281,    42,  -386,  -386,  -386,  -386,
    -386,   211,  -386,   305,   322,   143,   376,    21,  1623,   334,
     324,  -386,   156,  1203,  -386,     5,  -386,  -386,  -386,  1030,
     320,  -386,   323,   529,   319,   325,  -386,   289,  1099,   305,
    1623,   114,  1623,   114,   347,  -386,  -386,     9,   351,  1623,
      82,     7,  -386,   334,  -386,  -386,  1623,  1623,  1623,  1623,
    1623,  1623,  1623,  1623,  1623,  1623,  1623,  1623,  1623,  1623,
    1623,  1623,  1623,  -386,  -386,  1623,   329,  1623,   334,  1273,
    -386,  -386,  -386,  -386,  -386,   352,    82,  -386,   331,    25,
    -386,  -386,  1099,  -386,   143,  1343,  -386,  -386,  -386,   332,
    1059,  1623,   337,   561,   339,  1623,  1660,  1623,  -386,  -386,
    -386,  1682,  -386,   353,  1343,  -386,  -386,    66,   340,  -386,
    1623,  -386,  1170,   456,   162,   162,   157,   887,  1309,   318,
    1518,   462,   462,   157,   246,   246,  -386,  -386,  -386,  1099,
    -386,   315,   342,  1623,    57,  1343,  1343,  -386,   378,  -386,
    -386,    36,    82,   343,   344,  -386,  -386,  1099,  -386,  -386,
    -386,  1099,  1623,   173,   633,  1623,  -386,  -386,   345,   348,
    -386,   207,  1623,   357,  1623,  -386,   138,   189,  -386,   364,
     365,  -386,    49,  -386,   334,   346,   354,   363,  -386,  1710,
    -386,    23,   368,   369,   371,  -386,   383,   384,   386,   388,
    1413,  -386,  -386,  -386,  -386,   390,   777,  -386,  -386,  -386,
    -386,  -386,   183,  -386,  -386,  1732,   214,   217,  -386,  -386,
    -386,  1099,  -386,  1343,   417,  -386,  1623,  -386,   172,  -386,
    -386,  -386,  -386,  -386,  -386,  -386,    82,  -386,  -386,   279,
     398,  -386,  1623,  1623,  1623,   849,   989,   248,  -386,  -386,
    -386,   193,    82,  -386,  -386,  -386,  1623,  -386,   334,  -386,
    1343,   401,  1623,  -386,   197,   201,  -386,  -386,   400,  -386,
     224,   236,   286,   444,    82,   463,  -386,  -386,   419,   413,
    -386,  -386,  -386,   416,   455,  -386,   378,   418,   423,  1710,
     428,  -386,   435,  -386,   203,  -386,  -386,  -386,   849,  -386,
    -386,   437,   378,  1623,  1483,   248,  1623,   491,    82,  -386,
     438,  1623,  -386,  -386,   485,   467,   849,  1623,  -386,  1099,
     442,  -386,   957,  1623,  -386,  -386,  1099,   849,  -386,  -386,
    -386,   287,  1553,  -386,  1099,  -386,   148,   468,   473,   849,
     240,   474,   705,  -386,  -386,  -386,  -386,   537,    68,   544,
     546,    68,    54,  1240,   492,  -386,   705,   481,   705,   849,
    -386,   486,  -386,  -386,   385,    61,  -386,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,  -386,  -386,  -386,  -386,  -386,  -386,  -386,   488,   119,
     278,   278,   307,  1379,  1448,  1588,  1176,  1176,   307,   270,
     270,  -386,  -386,  -386,  -386
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       4,     0,    52,     1,    52,    21,     5,    23,    22,    57,
      10,    53,     6,     3,    35,     0,     0,    24,    40,     0,
      56,    54,    11,     0,     0,    58,   230,     0,     0,   227,
      36,    37,     0,    41,    15,    16,    60,    20,    10,     0,
       0,     7,   231,    31,     0,     0,     0,    59,   228,   229,
      28,     0,     9,     8,   209,   192,   193,     0,     0,     0,
       0,     0,     0,     0,     0,   189,     0,   218,   138,     0,
     222,     0,   194,     0,     0,     0,     0,   172,   171,     0,
       0,     0,    61,     0,     0,   167,   208,   168,   169,   170,
     206,   226,   191,     0,     0,    39,    60,    39,     0,     0,
       0,   241,     0,     0,   160,   188,   161,   162,   252,   178,
       0,   180,   176,     0,     0,   183,   185,     0,   136,   190,
       0,     0,     0,     0,   237,   164,   163,    35,     0,     0,
      10,     0,   195,     0,   159,   139,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   165,   166,     0,     0,     0,     0,     0,
     235,   243,    34,    33,    46,    42,    10,    50,     0,    48,
      32,    29,   141,   253,    39,     0,   250,   249,   179,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    66,   216,
     219,     0,   223,     0,     0,    36,    37,     0,     0,   207,
       0,   254,   144,   143,   152,   153,   150,     0,   145,   146,
     147,   148,   149,   151,   154,   155,   156,   157,   158,   140,
     211,     0,   197,     0,     0,     0,     0,    43,    44,    18,
      49,    39,    10,     0,     0,   215,   181,   187,   214,   186,
     213,   137,     0,     0,     0,     0,   233,   233,     0,     0,
      55,     0,     0,     0,     0,   245,     0,     0,   205,     0,
       0,    45,     0,    51,     0,    26,     0,     0,   242,   224,
     217,     0,     0,     0,     0,    90,     0,     0,     0,     0,
       0,    85,    67,    63,    84,     0,     0,    80,    81,    64,
      65,    82,     0,    83,    79,     0,     0,     0,   238,   247,
     196,   142,   212,     0,     0,   204,     0,   202,     0,   236,
     244,    14,    13,    19,    12,    25,    10,    30,   210,     0,
       0,    77,     0,     0,     0,     0,     0,    39,    86,    87,
     173,     0,    10,    62,    76,    78,     0,   239,     0,   240,
       0,     0,     0,   203,     0,     0,   198,    27,   224,   220,
       0,     0,     0,     0,    10,     0,   104,   103,     0,   102,
      94,    96,    95,    97,     0,   174,     0,    73,     0,   224,
       0,   234,     0,   246,     0,   199,   201,   225,     0,   105,
      88,     0,     0,     0,     0,    39,     0,    69,    10,    68,
       0,     0,   248,   200,   256,     0,     0,     0,    71,    72,
       0,    98,     0,     0,    74,   221,   232,     0,   255,    66,
      89,     0,     0,    99,    70,   257,    39,     0,     0,     0,
       0,     0,     0,    91,    92,   100,   132,     0,     0,     0,
       0,     0,     0,   115,   116,   114,     0,     0,     0,     0,
     134,     0,   133,   135,     0,     0,   110,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   108,   106,   107,    93,   113,   131,   112,     0,     0,
     124,   125,   122,   117,   118,   119,   120,   121,   123,   126,
     127,   128,   129,   130,   111
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -386,  -386,  -386,  -386,  -386,  -386,  -386,    -6,  -386,   -13,
    -386,  -386,  -386,  -386,  -386,   241,  -386,  -386,  -386,  -386,
    -213,  -386,  -386,    -7,  -289,   327,   394,  -386,   555,  -386,
    -386,  -386,   522,  -386,  -105,  -386,   165,  -386,  -386,   249,
    -386,   188,   291,  -230,  -386,  -386,  -386,  -386,  -386,  -386,
     194,  -386,  -386,  -386,  -345,  -386,  -386,  -386,  -123,   177,
    -385,  1365,   -12,   429,   -39,  -386,  -164,  -161,   421,  -386,
    -386,   412,   -52,  -386,   -50,  -386,  -386,   482,  -386,  -386,
    -386,  -386,  -386,  -386,  -211,  -386,   -14,   -15,  -386,   349,
    -386,  -386,  -386,  -386,  -386,  -386,  -386,   545,  -386,  -386,
    -386
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,     2,    13,     5,    77,    78,   264,   313,    79,
       6,    45,   262,     7,   265,   266,    97,   232,     8,    50,
     164,    18,    19,   165,   166,   167,   168,   169,     9,    10,
      80,    21,    24,    25,   283,   284,   244,   332,   367,   362,
     356,   368,   285,   436,   287,   396,   288,   325,   289,   439,
     363,   364,   290,   419,   357,   358,   291,   395,   437,   438,
     432,   433,   292,    81,   118,   293,   110,   111,   112,   114,
     115,   116,    83,    84,    85,   200,   100,   190,    86,   121,
      87,    88,    89,   123,   320,    90,   434,    91,   371,   296,
      92,   225,   194,   175,   226,   303,   340,    93,    94,   294,
     408
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      29,    28,    20,    32,    23,    82,   104,   106,   105,   105,
      36,   234,    29,    39,   286,   261,   189,    44,   189,   236,
     -15,   107,    26,   109,   113,    29,    49,    14,   -16,   135,
     248,   105,    46,    96,   125,   126,    98,   354,   354,   400,
     158,   134,    14,   441,   162,   163,    99,     3,   108,   101,
     311,   230,   117,  -188,  -188,  -188,   286,  -251,    40,   172,
     468,   259,   260,   131,    26,   426,    48,   418,   130,   128,
     -17,    26,   426,    12,   199,  -209,   185,   158,   159,   445,
     427,   186,   257,   191,   128,    27,   173,   427,   321,   177,
     171,   131,   170,   236,   231,   353,   354,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   312,   159,   219,   197,   109,   188,
     201,   429,   446,   426,   198,   430,   185,   431,   429,   467,
       4,   258,   430,   249,   431,   185,   109,   377,   427,   341,
      14,   109,   237,    22,   113,   222,   241,   224,   394,    14,
      40,   162,   163,   387,    14,   109,    41,   314,   390,   -38,
     228,    -2,   318,   304,    34,    35,   410,    37,     4,   398,
      15,   420,   421,   138,   139,   243,   372,   415,   -39,   429,
     187,    33,    16,   430,   188,   469,   109,   109,   251,   425,
      51,   128,    26,    52,    53,    54,   128,    55,    56,    57,
      58,    59,    17,   269,    38,   176,   295,   185,    60,   464,
     -47,   256,   305,   301,    42,   109,   148,   149,   150,   151,
     152,   148,   149,   150,   151,   152,    61,    62,    63,    64,
      65,    66,    67,   -15,    68,    69,    70,   282,    71,    72,
     270,   185,   185,    26,   426,   308,   346,   306,   335,    73,
     -16,   315,   185,    74,    14,    75,   360,   361,   365,   427,
      43,    76,   185,   307,   109,   428,   185,   348,   331,   105,
     185,   375,   185,    98,   300,   376,   185,   393,   153,   154,
     155,   337,    26,   338,   339,    54,   338,    55,    56,    57,
      99,   378,   344,   185,   345,    95,   128,   369,    30,    31,
     429,   109,   102,   379,   430,   185,   431,   150,   151,   152,
     350,   351,   352,   461,   359,   463,    61,    62,    63,    64,
      65,   120,    67,   447,   448,   370,   366,   122,    71,    72,
     374,   458,   459,   460,   138,   139,   140,   456,   457,   458,
     459,   460,    34,    35,   399,   103,   124,   402,   382,   156,
     157,    76,   406,   380,   417,   185,   185,   184,   185,   195,
     196,   246,   247,   132,   414,   133,   456,   457,   458,   459,
     460,   160,   359,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   366,   253,   254,   411,   162,   163,   161,    44,
     174,   179,   180,   182,   183,   193,   220,    68,   229,   235,
     359,   447,   448,   449,   238,    29,   240,   250,   255,   282,
     267,   268,   298,    29,   299,   316,    29,    39,    51,   317,
      26,    52,    53,    54,   302,    55,    56,    57,    58,    59,
      29,   309,   310,   188,   322,   323,    60,   324,   450,   451,
     452,   453,   454,   455,   456,   457,   458,   459,   460,   326,
     327,   328,   466,   329,    61,    62,    63,    64,    65,    66,
      67,   333,    68,    69,    70,   349,    71,    72,   373,   319,
     136,   381,   138,   139,   140,   342,   383,    73,   138,   139,
     140,    74,   185,    75,   384,   385,   386,   388,   389,    76,
      51,   343,    26,    52,    53,    54,   391,    55,    56,    57,
      58,    59,   392,   397,   403,   405,   407,   412,    60,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     147,   148,   149,   150,   151,   152,    61,    62,    63,    64,
      65,    66,    67,   423,    68,    69,    70,   409,    71,    72,
     424,   440,   435,   136,   137,   138,   139,   140,   442,    73,
     443,    40,   462,    74,   465,    75,   484,   347,   263,    11,
      47,    76,    51,  -182,    26,    52,    53,    54,   233,    55,
      56,    57,    58,    59,   416,   355,   404,   334,   221,   401,
      60,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   422,   227,   239,   297,   181,    61,    62,
      63,    64,    65,    66,    67,   192,    68,    69,    70,   119,
      71,    72,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    73,     0,     0,     0,    74,     0,    75,     0,     0,
       0,     0,     0,    76,   271,  -184,    26,    52,    53,   127,
       0,    55,    56,    57,    58,    59,     0,     0,     0,     0,
       0,     0,    60,   272,     0,   273,     0,     0,     0,     0,
     274,   275,   276,   277,     0,   278,   279,   280,     0,     0,
      61,    62,    63,    64,    65,    66,    67,   -39,    68,    69,
      70,   128,    71,    72,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    73,     0,     0,     0,    74,   281,    75,
       0,     0,     0,   188,   -75,    76,    51,     0,    26,    52,
      53,    54,     0,    55,    56,    57,    58,    59,     0,     0,
       0,     0,     0,     0,    60,   272,     0,   273,   420,   421,
       0,     0,   274,   275,   276,   277,     0,   278,   279,   280,
       0,     0,    61,    62,    63,    64,    65,    66,    67,     0,
      68,    69,    70,     0,    71,    72,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    73,     0,     0,     0,    74,
     281,    75,     0,     0,     0,   188,  -109,    76,   271,     0,
      26,    52,    53,    54,     0,    55,    56,    57,    58,    59,
       0,     0,     0,     0,     0,     0,    60,   272,     0,   273,
       0,     0,     0,     0,   274,   275,   276,   277,     0,   278,
     279,   280,     0,     0,    61,    62,    63,    64,    65,    66,
      67,     0,    68,    69,    70,     0,    71,    72,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    73,     0,     0,
       0,    74,   281,    75,     0,     0,     0,   188,   -75,    76,
      51,     0,    26,    52,    53,    54,     0,    55,    56,    57,
      58,    59,     0,     0,     0,     0,     0,     0,    60,   272,
       0,   273,     0,     0,     0,     0,   274,   275,   276,   277,
       0,   278,   279,   280,     0,     0,    61,    62,    63,    64,
      65,    66,    67,     0,    68,    69,    70,     0,    71,    72,
       0,   136,   137,   138,   139,   140,     0,     0,     0,    73,
       0,     0,     0,    74,   281,    75,     0,     0,     0,   188,
      51,    76,    26,    52,    53,   127,     0,    55,    56,    57,
      58,    59,     0,     0,     0,     0,     0,     0,    60,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,     0,     0,     0,     0,   252,    61,    62,    63,    64,
      65,    66,    67,   -39,    68,    69,    70,   128,    71,    72,
       0,   136,   137,   138,   139,   140,     0,     0,     0,    73,
     129,     0,     0,    74,     0,    75,     0,     0,     0,     0,
      51,    76,    26,    52,    53,   127,     0,    55,    56,    57,
      58,    59,     0,     0,     0,     0,     0,     0,    60,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,     0,     0,     0,   413,     0,    61,    62,    63,    64,
      65,    66,    67,   -39,    68,    69,    70,   128,    71,    72,
       0,     0,     0,     0,   136,   137,   138,   139,   140,    73,
       0,     0,     0,    74,  -101,    75,   178,     0,     0,     0,
      51,    76,    26,    52,    53,    54,     0,    55,    56,    57,
      58,    59,     0,     0,     0,     0,     0,     0,    60,     0,
       0,     0,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,     0,     0,    61,    62,    63,    64,
      65,    66,    67,     0,    68,    69,    70,     0,    71,    72,
       0,     0,     0,   136,   137,   138,   139,   140,     0,    73,
       0,     0,     0,    74,     0,    75,  -177,     0,     0,     0,
    -177,    76,    51,     0,    26,    52,    53,    54,     0,    55,
      56,    57,    58,    59,     0,     0,     0,     0,     0,     0,
      60,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,     0,     0,     0,     0,     0,    61,    62,
      63,    64,    65,    66,    67,     0,    68,    69,    70,     0,
      71,    72,     0,     0,     0,     0,   138,   139,   140,     0,
       0,    73,   447,   448,   449,    74,     0,    75,     0,     0,
       0,     0,  -175,    76,    51,     0,    26,    52,    53,    54,
       0,    55,    56,    57,    58,    59,     0,     0,     0,     0,
       0,     0,    60,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   455,   456,   457,   458,   459,   460,
      61,    62,    63,    64,    65,    66,    67,     0,    68,    69,
      70,     0,    71,    72,     0,     0,   447,   448,   449,     0,
       0,     0,     0,    73,   129,     0,     0,    74,     0,    75,
       0,     0,     0,     0,    51,    76,    26,    52,    53,    54,
       0,    55,    56,    57,    58,    59,     0,     0,     0,     0,
       0,     0,    60,   450,   451,   452,   453,   454,   455,   456,
     457,   458,   459,   460,     0,     0,     0,     0,     0,     0,
      61,    62,    63,    64,    65,    66,    67,     0,    68,    69,
      70,     0,    71,    72,     0,   138,   139,   140,     0,     0,
       0,   223,     0,    73,     0,     0,     0,    74,     0,    75,
       0,     0,     0,     0,    51,    76,    26,    52,    53,    54,
       0,    55,    56,    57,    58,    59,     0,     0,     0,     0,
       0,     0,    60,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,     0,     0,     0,     0,     0,     0,     0,
      61,    62,    63,    64,    65,    66,    67,     0,    68,    69,
      70,     0,    71,    72,     0,   447,   448,   449,     0,     0,
       0,     0,     0,    73,     0,     0,     0,    74,     0,    75,
    -175,     0,     0,     0,    51,    76,    26,    52,    53,    54,
       0,    55,    56,    57,    58,    59,     0,     0,     0,     0,
       0,     0,    60,   451,   452,   453,   454,   455,   456,   457,
     458,   459,   460,     0,     0,     0,     0,     0,     0,     0,
      61,    62,    63,    64,    65,    66,    67,     0,    68,    69,
      70,     0,    71,    72,   447,   448,   449,     0,     0,     0,
       0,     0,     0,    73,     0,     0,     0,    74,   330,    75,
       0,     0,     0,     0,    51,    76,    26,    52,    53,    54,
       0,    55,    56,    57,    58,    59,     0,     0,     0,     0,
       0,     0,    60,   452,   453,   454,   455,   456,   457,   458,
     459,   460,     0,     0,     0,     0,     0,     0,     0,     0,
      61,    62,    63,    64,    65,    66,    67,     0,    68,    69,
      70,     0,    71,    72,   138,   139,   140,     0,     0,     0,
       0,     0,     0,    73,     0,     0,     0,    74,  -101,    75,
       0,     0,     0,     0,    51,    76,    26,    52,    53,    54,
       0,    55,    56,    57,    58,    59,     0,     0,     0,     0,
       0,     0,    60,     0,   145,   146,   147,   148,   149,   150,
     151,   152,     0,     0,     0,     0,     0,     0,     0,     0,
      61,    62,    63,    64,    65,    66,    67,     0,    68,    69,
      70,     0,    71,    72,   447,   448,   449,     0,     0,     0,
       0,     0,     0,    73,     0,     0,     0,    74,     0,    75,
    -101,     0,     0,     0,    51,    76,    26,    52,    53,    54,
       0,    55,    56,    57,    58,    59,     0,     0,     0,     0,
       0,     0,    60,     0,   453,   454,   455,   456,   457,   458,
     459,   460,     0,     0,     0,     0,     0,     0,     0,     0,
      61,    62,    63,    64,    65,    66,    67,     0,    68,    69,
      70,     0,    71,    72,   136,   137,   138,   139,   140,     0,
       0,     0,     0,    73,     0,     0,     0,    74,     0,    75,
       0,     0,     0,     0,     0,    76,   136,   137,   138,   139,
     140,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   136,   137,   138,   139,   140,   242,
       0,     0,     0,     0,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   136,   137,   138,   139,
     140,   245,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,     0,     0,     0,     0,     0,   319,
       0,     0,     0,     0,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   444,     0,     0,     0,
       0,   336,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   470,   471,   472,   473,   474,   475,   476,   477,
     478,   479,   480,   481,   482,   483,     0,     0,     0,     0,
       0,     0,     0,     0,   444
};

static const yytype_int16 yycheck[] =
{
      15,    15,     9,    16,    10,    44,    58,    59,    58,    59,
      23,   175,    27,    27,   244,   228,   121,    13,   123,   180,
      37,    60,     3,    62,    63,    40,    40,     6,    37,    81,
     194,    81,    38,    46,    73,    74,    13,   326,   327,   384,
      35,    80,     6,   428,     8,     9,    37,     0,    61,    66,
       1,    26,    64,    11,    12,    13,   286,    66,    59,    98,
     445,   225,   226,    75,     3,     4,    67,   412,    75,    48,
      66,     3,     4,    65,    67,    66,    69,    35,    73,    25,
      19,   120,    25,   122,    48,    66,    99,    19,    65,   102,
      97,   103,    71,   254,    69,   325,   385,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,    65,    73,   155,   129,   157,    70,
     133,    60,    68,     4,   130,    64,    69,    66,    60,    68,
       7,    74,    64,    67,    66,    69,   175,   348,    19,   303,
       6,   180,   181,    61,   183,   158,   185,   159,   378,     6,
      59,     8,     9,   366,     6,   194,    65,   262,   369,    44,
     166,     0,   267,    25,     8,     9,   396,    65,     7,   382,
      36,    23,    24,    16,    17,   187,   340,   407,    44,    60,
      66,    44,    48,    64,    70,    66,   225,   226,   200,   419,
       1,    48,     3,     4,     5,     6,    48,     8,     9,    10,
      11,    12,    68,   242,    69,    49,   245,    69,    19,   439,
      67,   223,    74,   252,     3,   254,    59,    60,    61,    62,
      63,    59,    60,    61,    62,    63,    37,    38,    39,    40,
      41,    42,    43,    70,    45,    46,    47,   244,    49,    50,
      67,    69,    69,     3,     4,   257,    74,    58,    65,    60,
      70,   264,    69,    64,     6,    66,     8,     9,    65,    19,
      70,    72,    69,    74,   303,    25,    69,   319,   280,   319,
      69,    74,    69,    13,    67,    74,    69,    74,    11,    12,
      13,    67,     3,    69,    67,     6,    69,     8,     9,    10,
      37,    67,   304,    69,   306,    66,    48,   336,     8,     9,
      60,   340,    37,    67,    64,    69,    66,    61,    62,    63,
     322,   323,   324,   436,   326,   438,    37,    38,    39,    40,
      41,    66,    43,    16,    17,   338,   332,    66,    49,    50,
     342,    61,    62,    63,    16,    17,    18,    59,    60,    61,
      62,    63,     8,     9,   383,    66,    66,   386,   354,    68,
      69,    72,   391,    67,    67,    69,    69,    68,    69,     8,
       9,     8,     9,    66,   403,    37,    59,    60,    61,    62,
      63,    66,   384,    55,    56,    57,    58,    59,    60,    61,
      62,    63,   388,    68,    69,   397,     8,     9,    66,    13,
      66,    71,    69,    74,    69,    48,    67,    45,    67,    67,
     412,    16,    17,    18,    67,   420,    67,    67,    66,   416,
      67,    67,    67,   428,    66,    69,   431,   431,     1,    65,
       3,     4,     5,     6,    67,     8,     9,    10,    11,    12,
     445,    67,    67,    70,    66,    66,    19,    66,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    66,
      66,    65,    67,    65,    37,    38,    39,    40,    41,    42,
      43,    71,    45,    46,    47,    67,    49,    50,    67,    69,
      14,    27,    16,    17,    18,    58,    13,    60,    16,    17,
      18,    64,    69,    66,    65,    69,    31,    69,    65,    72,
       1,    74,     3,     4,     5,     6,    68,     8,     9,    10,
      11,    12,    67,    66,    13,    67,    21,    65,    19,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      58,    59,    60,    61,    62,    63,    37,    38,    39,    40,
      41,    42,    43,    65,    45,    46,    47,    70,    49,    50,
      67,     4,    68,    14,    15,    16,    17,    18,     4,    60,
       4,    59,    71,    64,    68,    66,    68,   316,   231,     4,
      38,    72,     1,    74,     3,     4,     5,     6,   174,     8,
       9,    10,    11,    12,   409,   326,   388,   286,   157,   385,
      19,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,   416,   165,   183,   247,    68,    37,    38,
      39,    40,    41,    42,    43,   123,    45,    46,    47,    64,
      49,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    60,    -1,    -1,    -1,    64,    -1,    66,    -1,    -1,
      -1,    -1,    -1,    72,     1,    74,     3,     4,     5,     6,
      -1,     8,     9,    10,    11,    12,    -1,    -1,    -1,    -1,
      -1,    -1,    19,    20,    -1,    22,    -1,    -1,    -1,    -1,
      27,    28,    29,    30,    -1,    32,    33,    34,    -1,    -1,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    60,    -1,    -1,    -1,    64,    65,    66,
      -1,    -1,    -1,    70,    71,    72,     1,    -1,     3,     4,
       5,     6,    -1,     8,     9,    10,    11,    12,    -1,    -1,
      -1,    -1,    -1,    -1,    19,    20,    -1,    22,    23,    24,
      -1,    -1,    27,    28,    29,    30,    -1,    32,    33,    34,
      -1,    -1,    37,    38,    39,    40,    41,    42,    43,    -1,
      45,    46,    47,    -1,    49,    50,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,    -1,    64,
      65,    66,    -1,    -1,    -1,    70,    71,    72,     1,    -1,
       3,     4,     5,     6,    -1,     8,     9,    10,    11,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    19,    20,    -1,    22,
      -1,    -1,    -1,    -1,    27,    28,    29,    30,    -1,    32,
      33,    34,    -1,    -1,    37,    38,    39,    40,    41,    42,
      43,    -1,    45,    46,    47,    -1,    49,    50,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,
      -1,    64,    65,    66,    -1,    -1,    -1,    70,    71,    72,
       1,    -1,     3,     4,     5,     6,    -1,     8,     9,    10,
      11,    12,    -1,    -1,    -1,    -1,    -1,    -1,    19,    20,
      -1,    22,    -1,    -1,    -1,    -1,    27,    28,    29,    30,
      -1,    32,    33,    34,    -1,    -1,    37,    38,    39,    40,
      41,    42,    43,    -1,    45,    46,    47,    -1,    49,    50,
      -1,    14,    15,    16,    17,    18,    -1,    -1,    -1,    60,
      -1,    -1,    -1,    64,    65,    66,    -1,    -1,    -1,    70,
       1,    72,     3,     4,     5,     6,    -1,     8,     9,    10,
      11,    12,    -1,    -1,    -1,    -1,    -1,    -1,    19,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    -1,    -1,    -1,    -1,    68,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      -1,    14,    15,    16,    17,    18,    -1,    -1,    -1,    60,
      61,    -1,    -1,    64,    -1,    66,    -1,    -1,    -1,    -1,
       1,    72,     3,     4,     5,     6,    -1,     8,     9,    10,
      11,    12,    -1,    -1,    -1,    -1,    -1,    -1,    19,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    -1,    -1,    -1,    67,    -1,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      -1,    -1,    -1,    -1,    14,    15,    16,    17,    18,    60,
      -1,    -1,    -1,    64,    65,    66,    26,    -1,    -1,    -1,
       1,    72,     3,     4,     5,     6,    -1,     8,     9,    10,
      11,    12,    -1,    -1,    -1,    -1,    -1,    -1,    19,    -1,
      -1,    -1,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    -1,    -1,    37,    38,    39,    40,
      41,    42,    43,    -1,    45,    46,    47,    -1,    49,    50,
      -1,    -1,    -1,    14,    15,    16,    17,    18,    -1,    60,
      -1,    -1,    -1,    64,    -1,    66,    67,    -1,    -1,    -1,
      71,    72,     1,    -1,     3,     4,     5,     6,    -1,     8,
       9,    10,    11,    12,    -1,    -1,    -1,    -1,    -1,    -1,
      19,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    -1,    -1,    -1,    -1,    -1,    37,    38,
      39,    40,    41,    42,    43,    -1,    45,    46,    47,    -1,
      49,    50,    -1,    -1,    -1,    -1,    16,    17,    18,    -1,
      -1,    60,    16,    17,    18,    64,    -1,    66,    -1,    -1,
      -1,    -1,    71,    72,     1,    -1,     3,     4,     5,     6,
      -1,     8,     9,    10,    11,    12,    -1,    -1,    -1,    -1,
      -1,    -1,    19,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    58,    59,    60,    61,    62,    63,
      37,    38,    39,    40,    41,    42,    43,    -1,    45,    46,
      47,    -1,    49,    50,    -1,    -1,    16,    17,    18,    -1,
      -1,    -1,    -1,    60,    61,    -1,    -1,    64,    -1,    66,
      -1,    -1,    -1,    -1,     1,    72,     3,     4,     5,     6,
      -1,     8,     9,    10,    11,    12,    -1,    -1,    -1,    -1,
      -1,    -1,    19,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,
      37,    38,    39,    40,    41,    42,    43,    -1,    45,    46,
      47,    -1,    49,    50,    -1,    16,    17,    18,    -1,    -1,
      -1,    58,    -1,    60,    -1,    -1,    -1,    64,    -1,    66,
      -1,    -1,    -1,    -1,     1,    72,     3,     4,     5,     6,
      -1,     8,     9,    10,    11,    12,    -1,    -1,    -1,    -1,
      -1,    -1,    19,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      37,    38,    39,    40,    41,    42,    43,    -1,    45,    46,
      47,    -1,    49,    50,    -1,    16,    17,    18,    -1,    -1,
      -1,    -1,    -1,    60,    -1,    -1,    -1,    64,    -1,    66,
      67,    -1,    -1,    -1,     1,    72,     3,     4,     5,     6,
      -1,     8,     9,    10,    11,    12,    -1,    -1,    -1,    -1,
      -1,    -1,    19,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      37,    38,    39,    40,    41,    42,    43,    -1,    45,    46,
      47,    -1,    49,    50,    16,    17,    18,    -1,    -1,    -1,
      -1,    -1,    -1,    60,    -1,    -1,    -1,    64,    65,    66,
      -1,    -1,    -1,    -1,     1,    72,     3,     4,     5,     6,
      -1,     8,     9,    10,    11,    12,    -1,    -1,    -1,    -1,
      -1,    -1,    19,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      37,    38,    39,    40,    41,    42,    43,    -1,    45,    46,
      47,    -1,    49,    50,    16,    17,    18,    -1,    -1,    -1,
      -1,    -1,    -1,    60,    -1,    -1,    -1,    64,    65,    66,
      -1,    -1,    -1,    -1,     1,    72,     3,     4,     5,     6,
      -1,     8,     9,    10,    11,    12,    -1,    -1,    -1,    -1,
      -1,    -1,    19,    -1,    56,    57,    58,    59,    60,    61,
      62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      37,    38,    39,    40,    41,    42,    43,    -1,    45,    46,
      47,    -1,    49,    50,    16,    17,    18,    -1,    -1,    -1,
      -1,    -1,    -1,    60,    -1,    -1,    -1,    64,    -1,    66,
      67,    -1,    -1,    -1,     1,    72,     3,     4,     5,     6,
      -1,     8,     9,    10,    11,    12,    -1,    -1,    -1,    -1,
      -1,    -1,    19,    -1,    56,    57,    58,    59,    60,    61,
      62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      37,    38,    39,    40,    41,    42,    43,    -1,    45,    46,
      47,    -1,    49,    50,    14,    15,    16,    17,    18,    -1,
      -1,    -1,    -1,    60,    -1,    -1,    -1,    64,    -1,    66,
      -1,    -1,    -1,    -1,    -1,    72,    14,    15,    16,    17,
      18,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    14,    15,    16,    17,    18,    69,
      -1,    -1,    -1,    -1,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    14,    15,    16,    17,
      18,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    -1,    -1,    -1,    -1,    -1,    69,
      -1,    -1,    -1,    -1,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,   431,    -1,    -1,    -1,
      -1,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   447,   448,   449,   450,   451,   452,   453,   454,
     455,   456,   457,   458,   459,   460,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   469
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    76,    77,     0,     7,    79,    85,    88,    93,   103,
     104,   103,    65,    78,     6,    36,    48,    68,    96,    97,
      98,   106,    61,    82,   107,   108,     3,    66,   161,   162,
       8,     9,    84,    44,     8,     9,    84,    65,    69,   161,
      59,    65,     3,    70,    13,    86,    82,   107,    67,   161,
      94,     1,     4,     5,     6,     8,     9,    10,    11,    12,
      19,    37,    38,    39,    40,    41,    42,    43,    45,    46,
      47,    49,    50,    60,    64,    66,    72,    80,    81,    84,
     105,   138,   139,   147,   148,   149,   153,   155,   156,   157,
     160,   162,   165,   172,   173,    66,    84,    91,    13,    37,
     151,    66,    37,    66,   147,   149,   147,   139,    84,   139,
     141,   142,   143,   139,   144,   145,   146,   137,   139,   172,
      66,   154,    66,   158,    66,   139,   139,     6,    48,    61,
      98,   137,    66,    37,   139,   147,    14,    15,    16,    17,
      18,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    11,    12,    13,    68,    69,    35,    73,
      66,    66,     8,     9,    95,    98,    99,   100,   101,   102,
      71,    98,   139,    84,    66,   168,    49,    84,    26,    71,
      69,    68,    74,    69,    68,    69,   139,    66,    70,   109,
     152,   139,   152,    48,   167,     8,     9,   137,    82,    67,
     150,    84,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
      67,   143,    84,    58,   137,   166,   169,   138,    82,    67,
      26,    69,    92,   101,   141,    67,   142,   139,    67,   146,
      67,   139,    69,   137,   111,    69,     8,     9,   141,    67,
      67,   137,    68,    68,    69,    66,   137,    25,    74,   141,
     141,    95,    87,   100,    82,    89,    90,    67,    67,   139,
      67,     1,    20,    22,    27,    28,    29,    30,    32,    33,
      34,    65,    98,   109,   110,   117,   118,   119,   121,   123,
     127,   131,   137,   140,   174,   139,   164,   164,    67,    66,
      67,   139,    67,   170,    25,    74,    58,    74,   137,    67,
      67,     1,    65,    83,   109,    84,    69,    65,   109,    69,
     159,    65,    66,    66,    66,   122,    66,    66,    65,    65,
      65,   137,   112,    71,   117,    65,    69,    67,    69,    67,
     171,   141,    58,    74,   137,   137,    74,    90,   147,    67,
     137,   137,   137,   118,    99,   114,   115,   129,   130,   137,
       8,     9,   114,   125,   126,    65,    82,   113,   116,   139,
      84,   163,   141,    67,   137,    74,    74,   159,    67,    67,
      67,    27,    82,    13,    65,    69,    31,    95,    69,    65,
     159,    68,    67,    74,   118,   132,   120,    66,    95,   139,
     129,   125,   139,    13,   116,    67,   139,    21,   175,    70,
     118,   137,    65,    67,   139,   118,   111,    67,   129,   128,
      23,    24,   134,    65,    67,   118,     4,    19,    25,    60,
      64,    66,   135,   136,   161,    68,   118,   133,   134,   124,
       4,   135,     4,     4,   136,    25,    68,    16,    17,    18,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,   133,    71,   133,   118,    68,    67,    68,   135,    66,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,    68
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    75,    76,    77,    77,    78,    78,    79,    80,    81,
      82,    82,    83,    83,    83,    84,    84,    86,    87,    85,
      85,    85,    85,    85,    88,    89,    90,    90,    91,    92,
      91,    94,    93,    95,    95,    96,    96,    96,    97,    97,
      98,    98,    99,    99,   100,   100,   100,   101,   101,   101,
     102,   102,   103,   103,   104,   105,   106,   106,   107,   107,
     108,   108,   109,   110,   110,   110,   111,   112,   111,   113,
     113,   114,   115,   116,   116,   117,   117,   117,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   120,   119,
     122,   121,   124,   123,   125,   125,   125,   126,   126,   128,
     127,   129,   129,   130,   130,   132,   131,   133,   133,   133,
     134,   134,   134,   134,   134,   135,   135,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   137,   137,   138,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   140,   140,   141,   141,   141,   142,   142,
     143,   143,   144,   144,   144,   145,   145,   146,   147,   148,
     148,   149,   149,   149,   149,   150,   149,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   151,
     149,   149,   149,   149,   149,   149,   152,   152,   154,   153,
     155,   156,   158,   157,   159,   159,   160,   161,   161,   161,
     162,   162,   163,   164,   164,   166,   165,   167,   165,   165,
     165,   168,   165,   169,   165,   170,   165,   171,   165,   172,
     172,   173,   173,   173,   173,   174,   175,   175
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     3,     0,     0,     1,     4,     1,     1,
       0,     1,     1,     1,     1,     1,     1,     0,     0,     9,
       3,     1,     1,     1,     2,     2,     1,     3,     0,     0,
       5,     0,     7,     1,     1,     1,     2,     2,     1,     0,
       1,     2,     1,     2,     2,     3,     1,     0,     1,     2,
       1,     3,     0,     2,     2,     4,     1,     0,     1,     3,
       2,     4,     4,     1,     1,     1,     0,     0,     5,     2,
       4,     3,     3,     1,     3,     0,     2,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     0,     6,
       0,     8,     0,    10,     1,     1,     1,     1,     3,     0,
       8,     0,     1,     1,     1,     0,    10,     2,     2,     0,
       3,     5,     4,     4,     2,     1,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     1,     2,     2,     2,     1,     3,     1,     2,
       3,     3,     5,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     2,     2,     2,     2,     2,     2,     1,     1,     1,
       1,     1,     1,     2,     3,     0,     1,     2,     1,     2,
       1,     3,     0,     1,     2,     1,     3,     3,     1,     1,
       2,     1,     1,     1,     1,     0,     5,     3,     6,     7,
       8,     7,     5,     6,     5,     4,     1,     3,     1,     0,
       6,     3,     5,     4,     4,     4,     1,     3,     0,     3,
       7,     9,     0,     3,     0,     3,     1,     1,     3,     3,
       1,     2,     3,     0,     3,     0,     5,     0,     5,     6,
       6,     0,     5,     0,     5,     0,     7,     0,     8,     3,
       3,     1,     2,     3,     3,     6,     0,     2
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
  case 2: /* all: program  */
#line 214 "grammar.y"
        {
#line 230 "grammar.y.pre"
	    comp_trees[TREE_MAIN] = (yyval.node);
	}
#line 2076 "grammar.tab.c"
    break;

  case 3: /* program: program def possible_semi_colon  */
#line 222 "grammar.y"
        {
#line 237 "grammar.y.pre"
	    CREATE_TWO_VALUES((yyval.node), 0, (yyvsp[-2].node), (yyvsp[-1].node));
	}
#line 2085 "grammar.tab.c"
    break;

  case 4: /* program: %empty  */
#line 227 "grammar.y"
        {
#line 241 "grammar.y.pre"
	    (yyval.node) = 0;
	}
#line 2094 "grammar.tab.c"
    break;

  case 6: /* possible_semi_colon: ';'  */
#line 236 "grammar.y"
            {
#line 249 "grammar.y.pre"

		yywarn("Extra ';'. Ignored.");
	    }
#line 2104 "grammar.tab.c"
    break;

  case 7: /* inheritance: type_modifier_list L_INHERIT string_con1 ';'  */
#line 246 "grammar.y"
            {
#line 258 "grammar.y.pre"
		object_t *ob;
		inherit_t inherit;
		int initializer;
		
		(yyvsp[-3].number) |= global_modifiers;

		
		if (!((yyvsp[-3].number) & DECL_ACCESS)) (yyvsp[-3].number) |= DECL_PUBLIC;
#ifndef ALLOW_INHERIT_AFTER_FUNCTION
		if (func_present)
		    yyerror("Illegal to inherit after defining functions.");
#endif
		if (var_defined)
		    yyerror("Illegal to inherit after defining global variables.");
#ifndef ALLOW_INHERIT_AFTER_FUNCTION
		if (func_present || var_defined){
#else
		if (var_defined){
#endif
		  inherit_file = 0;
		  YYACCEPT;
		}
#ifdef NEVER
		} //stupid bison
#endif
		ob = find_object2((yyvsp[-1].string));
		if (ob == 0) {
		    inherit_file = alloc_cstring((yyvsp[-1].string), "inherit");
		    /* Return back to load_object() */
		    YYACCEPT;
		}
		scratch_free((yyvsp[-1].string));
		inherit.prog = ob->prog;

		if (mem_block[A_INHERITS].current_size){
		    inherit_t *prev_inherit = INHERIT(NUM_INHERITS - 1);
		    
		    inherit.function_index_offset 
			= prev_inherit->function_index_offset
			+ prev_inherit->prog->num_functions_defined
			+ prev_inherit->prog->last_inherited;
		    if (prev_inherit->prog->num_functions_defined &&
			prev_inherit->prog->function_table[prev_inherit->prog->num_functions_defined - 1].funcname[0] == APPLY___INIT_SPECIAL_CHAR)
			inherit.function_index_offset--;
		} else inherit.function_index_offset = 0;
		
		inherit.variable_index_offset =
		    mem_block[A_VAR_TEMP].current_size /
		    sizeof (variable_t);
		inherit.type_mod = (yyvsp[-3].number);
		add_to_mem_block(A_INHERITS, (char *)&inherit, sizeof inherit);

		/* The following has to come before copy_vars - Sym */
		copy_structures(ob->prog);
		copy_variables(ob->prog, (yyvsp[-3].number));
		initializer = copy_functions(ob->prog, (yyvsp[-3].number));
		if (initializer >= 0) {
		    parse_node_t *node, *newnode;
		    /* initializer is an index into the object we're
		       inheriting's function table; this finds the
		       appropriate entry in our table and generates
		       a call to it */
		    node = new_node_no_line();
		    node->kind = NODE_CALL_2;
		    node->r.expr = 0;
		    node->v.number = F_CALL_INHERITED;
		    node->l.number = initializer | ((NUM_INHERITS - 1) << 16);
		    node->type = TYPE_ANY;
		    
		    /* The following illustrates a distinction between */
		    /* macros and funcs...newnode is needed here - Sym */
		    newnode = comp_trees[TREE_INIT];
		    CREATE_TWO_VALUES(comp_trees[TREE_INIT],0, newnode, node);
		    comp_trees[TREE_INIT] = pop_value(comp_trees[TREE_INIT]);
		    
		} 
		(yyval.node) = 0;
	    }
#line 2189 "grammar.tab.c"
    break;

  case 8: /* real: L_REAL  */
#line 330 "grammar.y"
            {
#line 357 "grammar.y.pre"
		CREATE_REAL((yyval.node), (yyvsp[0].real));
	    }
#line 2198 "grammar.tab.c"
    break;

  case 9: /* number: L_NUMBER  */
#line 338 "grammar.y"
            {
#line 364 "grammar.y.pre"
		CREATE_NUMBER((yyval.node), (yyvsp[0].number));
	    }
#line 2207 "grammar.tab.c"
    break;

  case 10: /* optional_star: %empty  */
#line 346 "grammar.y"
            {
#line 371 "grammar.y.pre"
		(yyval.number) = 0;
	    }
#line 2216 "grammar.tab.c"
    break;

  case 11: /* optional_star: '*'  */
#line 351 "grammar.y"
{
#line 375 "grammar.y.pre"
		(yyval.number) = TYPE_MOD_ARRAY;
	    }
#line 2225 "grammar.tab.c"
    break;

  case 12: /* block_or_semi: block  */
#line 359 "grammar.y"
            {
#line 382 "grammar.y.pre"
		(yyval.node) = (yyvsp[0].decl).node;
		if (!(yyval.node)) {
		    CREATE_RETURN((yyval.node), 0);
		}
            }
#line 2237 "grammar.tab.c"
    break;

  case 13: /* block_or_semi: ';'  */
#line 367 "grammar.y"
            {
#line 389 "grammar.y.pre"
		(yyval.node) = 0;
	    }
#line 2246 "grammar.tab.c"
    break;

  case 14: /* block_or_semi: error  */
#line 372 "grammar.y"
            {
#line 393 "grammar.y.pre"
		(yyval.node) = 0;
	    }
#line 2255 "grammar.tab.c"
    break;

  case 15: /* identifier: L_DEFINED_NAME  */
#line 380 "grammar.y"
            {
#line 400 "grammar.y.pre"
		(yyval.string) = scratch_copy((yyvsp[0].ihe)->name);
	    }
#line 2264 "grammar.tab.c"
    break;

  case 17: /* $@1: %empty  */
#line 389 "grammar.y"
            {
#line 408 "grammar.y.pre"
		int flags;
                func_present = 1;
		flags = ((yyvsp[-2].number) >> 16);
		
		flags |= global_modifiers;


		if (!(flags & DECL_ACCESS)) flags |= DECL_PUBLIC;
                (yyvsp[-2].number) = (flags << 16) | ((yyvsp[-2].number) & 0xffff);
		/* Handle type checking here so we know whether to typecheck
		   'argument' */
		if ((yyvsp[-2].number) & 0xffff) {
		    exact_types = ((yyvsp[-2].number)& 0xffff) | (yyvsp[-1].number);
		} else {
		    if (pragmas & PRAGMA_STRICT_TYPES) {
			if (strcmp((yyvsp[0].string), "create") != 0)
			    yyerror("\"#pragma strict_types\" requires type of function");
			else
			    exact_types = TYPE_VOID; /* default for create() */
		    } else
			exact_types = 0;
		}
	    }
#line 2294 "grammar.tab.c"
    break;

  case 18: /* @2: %empty  */
#line 415 "grammar.y"
            {
#line 459 "grammar.y.pre"
		char *p = (yyvsp[-4].string);
		(yyvsp[-4].string) = make_shared_string((yyvsp[-4].string));
		scratch_free(p);

		/* If we had nested functions, we would need to check */
		/* here if we have enough space for locals */
		
		/*
		 * Define a prototype. If it is a real function, then the
		 * prototype will be replaced below.
		 */

		(yyval.number) = FUNC_PROTOTYPE;
		if ((yyvsp[-1].argument).flags & ARG_IS_VARARGS) {
		    (yyval.number) |= (FUNC_TRUE_VARARGS | FUNC_VARARGS);
		}
		(yyval.number) |= ((yyvsp[-6].number) >> 16);

		define_new_function((yyvsp[-4].string), (yyvsp[-1].argument).num_arg, 0, (yyval.number), ((yyvsp[-6].number) & 0xffff)| (yyvsp[-5].number));
		/* This is safe since it is guaranteed to be in the
		   function table, so it can't be dangling */
		free_string((yyvsp[-4].string)); 
		context = 0;
	    }
#line 2325 "grammar.tab.c"
    break;

  case 19: /* def: type optional_star identifier $@1 '(' argument ')' @2 block_or_semi  */
#line 442 "grammar.y"
            {
#line 485 "grammar.y.pre"
		/* Either a prototype or a block */
		if ((yyvsp[0].node)) {
		    int fun;

		    (yyvsp[-1].number) &= ~FUNC_PROTOTYPE;
		    if ((yyvsp[0].node)->kind != NODE_RETURN &&
			((yyvsp[0].node)->kind != NODE_TWO_VALUES
			 || (yyvsp[0].node)->r.expr->kind != NODE_RETURN)) {
			parse_node_t *replacement;
			CREATE_STATEMENTS(replacement, (yyvsp[0].node), 0);
			CREATE_RETURN(replacement->r.expr, 0);
			(yyvsp[0].node) = replacement;
		    }

		    fun = define_new_function((yyvsp[-6].string), (yyvsp[-3].argument).num_arg, 
					      max_num_locals - (yyvsp[-3].argument).num_arg,
					      (yyvsp[-1].number), ((yyvsp[-8].number) & 0xffff) | (yyvsp[-7].number));
		    if (fun != -1) {
			(yyval.node) = new_node_no_line();
			(yyval.node)->kind = NODE_FUNCTION;
			(yyval.node)->v.number = fun;
			(yyval.node)->l.number = max_num_locals;
			(yyval.node)->r.expr = (yyvsp[0].node);
		    } else 
			(yyval.node) = 0;
		} else
		    (yyval.node) = 0;
		free_all_local_names(!!(yyvsp[0].node));
	    }
#line 2361 "grammar.tab.c"
    break;

  case 20: /* def: type name_list ';'  */
#line 474 "grammar.y"
            {
#line 516 "grammar.y.pre"
		if (!((yyvsp[-2].number) & ~(DECL_MODS)) && (pragmas & PRAGMA_STRICT_TYPES))
		    yyerror("Missing type for global variable declaration");
		(yyval.node) = 0;
	    }
#line 2372 "grammar.tab.c"
    break;

  case 24: /* modifier_change: type_modifier_list ':'  */
#line 486 "grammar.y"
            {
#line 527 "grammar.y.pre"
		if (!(yyvsp[-1].number)) 
		    yyerror("modifier list may not be empty.");
		
		if ((yyvsp[-1].number) & FUNC_VARARGS) {
		    yyerror("Illegal modifier 'varargs' in global modifier list.");
		    (yyvsp[-1].number) &= ~FUNC_VARARGS;
		}

		if (!((yyvsp[-1].number) & DECL_ACCESS)) (yyvsp[-1].number) |= DECL_PUBLIC;
		global_modifiers = (yyvsp[-1].number);
		(yyval.node) = 0;
	    }
#line 2391 "grammar.tab.c"
    break;

  case 25: /* member_name: optional_star identifier  */
#line 504 "grammar.y"
            {
#line 544 "grammar.y.pre"
		/* At this point, the current_type here is only a basic_type */
		/* and cannot be unused yet - Sym */
		
		if (current_type == TYPE_VOID)
		    yyerror("Illegal to declare class member of type void.");
		add_local_name((yyvsp[0].string), current_type | (yyvsp[-1].number));
		scratch_free((yyvsp[0].string));
	    }
#line 2406 "grammar.tab.c"
    break;

  case 29: /* $@3: %empty  */
#line 524 "grammar.y"
          {
#line 563 "grammar.y.pre"
	      current_type = (yyvsp[0].number);
	  }
#line 2415 "grammar.tab.c"
    break;

  case 31: /* @4: %empty  */
#line 533 "grammar.y"
            {
#line 571 "grammar.y.pre"
		ident_hash_elem_t *ihe;

		ihe = find_or_add_ident(
			   PROG_STRING((yyval.number) = store_prog_string((yyvsp[-1].string))),
			   FOA_GLOBAL_SCOPE);
		if (ihe->dn.class_num == -1) {
		    ihe->sem_value++;
		    ihe->dn.class_num = mem_block[A_CLASS_DEF].current_size / sizeof(class_def_t);
		    if (ihe->dn.class_num > CLASS_NUM_MASK){
			char buf[256];
			char *p;

			p = buf;
			sprintf(p, "Too many classes, max is %d.\n", CLASS_NUM_MASK + 1);
			yyerror(buf);
		    }

		    scratch_free((yyvsp[-1].string));
		    (yyvsp[-2].ihe) = 0;
		}
		else {
		    (yyvsp[-2].ihe) = ihe;
		}
	    }
#line 2446 "grammar.tab.c"
    break;

  case 32: /* type_decl: type_modifier_list L_CLASS identifier '{' @4 member_list '}'  */
#line 560 "grammar.y"
            {
#line 597 "grammar.y.pre"
		class_def_t *sd;
		class_member_entry_t *sme;
		int i, raise_error = 0;
		
		/* check for a redefinition */
		if ((yyvsp[-5].ihe) != 0) {
		    sd = CLASS((yyvsp[-5].ihe)->dn.class_num);
		    if (sd->size != current_number_of_locals)
			raise_error = 1;
		    else {
			i = sd->size;
			sme = (class_member_entry_t *)mem_block[A_CLASS_MEMBER].block + sd->index;
			while (i--) {
			    /* check for matching names and types */
			    if (strcmp(PROG_STRING(sme[i].membername), locals_ptr[i].ihe->name) != 0 ||
				sme[i].type != (type_of_locals_ptr[i] & ~LOCAL_MODS)) {
				raise_error = 1;
				break;
			    }
			}
		    }
		}

		if (raise_error) {
		    char buf[512];
		    char *end = EndOf(buf);
		    char *p;

		    p = strput(buf, end, "Illegal to redefine class ");
		    p = strput(p, end, PROG_STRING((yyval.number)));
		    yyerror(buf);
		} else {
		    sd = (class_def_t *)allocate_in_mem_block(A_CLASS_DEF, sizeof(class_def_t));
		    i = sd->size = current_number_of_locals;
		    sd->index = mem_block[A_CLASS_MEMBER].current_size / sizeof(class_member_entry_t);
		    sd->classname = (yyvsp[-2].number);

		    sme = (class_member_entry_t *)allocate_in_mem_block(A_CLASS_MEMBER, sizeof(class_member_entry_t) * current_number_of_locals);

		    while (i--) {
			sme[i].membername = store_prog_string(locals_ptr[i].ihe->name);
			sme[i].type = type_of_locals_ptr[i] & ~LOCAL_MODS;
		    }
		}

		free_all_local_names(0);
		(yyval.node) = 0;
	    }
#line 2501 "grammar.tab.c"
    break;

  case 34: /* new_local_name: L_DEFINED_NAME  */
#line 615 "grammar.y"
            {
#line 651 "grammar.y.pre"
		if ((yyvsp[0].ihe)->dn.local_num != -1) {
		    char buff[256];
		    char *end = EndOf(buff);
		    char *p;
		    
		    p = strput(buff, end, "Illegal to redeclare local name '");
		    p = strput(p, end, (yyvsp[0].ihe)->name);
		    p = strput(p, end, "'");
		    yyerror(buff);
		}
		(yyval.string) = scratch_copy((yyvsp[0].ihe)->name);
	    }
#line 2520 "grammar.tab.c"
    break;

  case 36: /* atomic_type: L_CLASS L_DEFINED_NAME  */
#line 634 "grammar.y"
            {
#line 669 "grammar.y.pre"
		if ((yyvsp[0].ihe)->dn.class_num == -1) {
		    char buf[256];
		    char *end = EndOf(buf);
		    char *p;
		    
		    p = strput(buf, end, "Undefined class '");
		    p = strput(p, end, (yyvsp[0].ihe)->name);
		    p = strput(p, end, "'");
		    yyerror(buf);
		    (yyval.number) = TYPE_ANY;
		} else {
		    (yyval.number) = (yyvsp[0].ihe)->dn.class_num | TYPE_MOD_CLASS;
		}
	    }
#line 2541 "grammar.tab.c"
    break;

  case 37: /* atomic_type: L_CLASS L_IDENTIFIER  */
#line 651 "grammar.y"
            {
#line 685 "grammar.y.pre"
		char buf[256];
		char *end = EndOf(buf);
		char *p;

		p = strput(buf, end, "Undefined class '");
		p = strput(p, end, (yyvsp[0].string));
		p = strput(p, end, "'");
		yyerror(buf);
		(yyval.number) = TYPE_ANY;
	    }
#line 2558 "grammar.tab.c"
    break;

  case 39: /* opt_atomic_type: %empty  */
#line 668 "grammar.y"
            {
#line 702 "grammar.y.pre"
		(yyval.number) = TYPE_ANY;
	    }
#line 2567 "grammar.tab.c"
    break;

  case 41: /* basic_type: opt_atomic_type L_ARRAY  */
#line 677 "grammar.y"
            {
#line 712 "grammar.y.pre"
		(yyval.number) = (yyvsp[-1].number) | TYPE_MOD_ARRAY;
	    }
#line 2576 "grammar.tab.c"
    break;

  case 43: /* arg_type: basic_type ref  */
#line 686 "grammar.y"
            {
#line 722 "grammar.y.pre"
		(yyval.number) = (yyvsp[-1].number) | LOCAL_MOD_REF;
	    }
#line 2585 "grammar.tab.c"
    break;

  case 44: /* new_arg: arg_type optional_star  */
#line 694 "grammar.y"
            {
#line 730 "grammar.y.pre"
                (yyval.number) = (yyvsp[-1].number) | (yyvsp[0].number);
		if ((yyvsp[-1].number) != TYPE_VOID)
		    add_local_name("", (yyvsp[-1].number) | (yyvsp[0].number));
            }
#line 2596 "grammar.tab.c"
    break;

  case 45: /* new_arg: arg_type optional_star new_local_name  */
#line 701 "grammar.y"
            {
#line 736 "grammar.y.pre"
		if ((yyvsp[-2].number) == TYPE_VOID)
		    yyerror("Illegal to declare argument of type void.");
                add_local_name((yyvsp[0].string), (yyvsp[-2].number) | (yyvsp[-1].number));
		scratch_free((yyvsp[0].string));
                (yyval.number) = (yyvsp[-2].number) | (yyvsp[-1].number);
	    }
#line 2609 "grammar.tab.c"
    break;

  case 46: /* new_arg: new_local_name  */
#line 710 "grammar.y"
            {
#line 744 "grammar.y.pre"
		if (exact_types) {
		    yyerror("Missing type for argument");
		}
		add_local_name((yyvsp[0].string), TYPE_ANY);
		scratch_free((yyvsp[0].string));
		(yyval.number) = TYPE_ANY;
            }
#line 2623 "grammar.tab.c"
    break;

  case 47: /* argument: %empty  */
#line 723 "grammar.y"
            {
#line 756 "grammar.y.pre"
		(yyval.argument).num_arg = 0;
                (yyval.argument).flags = 0;
	    }
#line 2633 "grammar.tab.c"
    break;

  case 49: /* argument: argument_list L_DOT_DOT_DOT  */
#line 730 "grammar.y"
            {
#line 762 "grammar.y.pre"
		int x = type_of_locals_ptr[max_num_locals-1];
		int lt = x & ~LOCAL_MODS;
		
		(yyval.argument) = (yyvsp[-1].argument);
		(yyval.argument).flags |= ARG_IS_VARARGS;

		if (x & LOCAL_MOD_REF) {
		    yyerror("Variable to hold remainder of args may not be a reference");
		    x &= ~LOCAL_MOD_REF;
		}
		if (lt != TYPE_ANY && !(lt & TYPE_MOD_ARRAY))
		    yywarn("Variable to hold remainder of arguments should be an array.");
	    }
#line 2653 "grammar.tab.c"
    break;

  case 50: /* argument_list: new_arg  */
#line 749 "grammar.y"
            {
#line 780 "grammar.y.pre"
		if (((yyvsp[0].number) & TYPE_MASK) == TYPE_VOID && !((yyvsp[0].number) & TYPE_MOD_CLASS)) {
		    if ((yyvsp[0].number) & ~TYPE_MASK)
			yyerror("Illegal to declare argument of type void.");
		    (yyval.argument).num_arg = 0;
		} else {
		    (yyval.argument).num_arg = 1;
		}
                (yyval.argument).flags = 0;
	    }
#line 2669 "grammar.tab.c"
    break;

  case 51: /* argument_list: argument_list ',' new_arg  */
#line 761 "grammar.y"
            {
#line 791 "grammar.y.pre"
		if (!(yyval.argument).num_arg)    /* first arg was void w/no name */
		    yyerror("argument of type void must be the only argument.");
		if (((yyvsp[0].number) & TYPE_MASK) == TYPE_VOID && !((yyvsp[0].number) & TYPE_MOD_CLASS))
		    yyerror("Illegal to declare argument of type void.");

                (yyval.argument) = (yyvsp[-2].argument);
		(yyval.argument).num_arg++;
	    }
#line 2684 "grammar.tab.c"
    break;

  case 52: /* type_modifier_list: %empty  */
#line 775 "grammar.y"
            {
#line 804 "grammar.y.pre"
		(yyval.number) = 0;
	    }
#line 2693 "grammar.tab.c"
    break;

  case 53: /* type_modifier_list: L_TYPE_MODIFIER type_modifier_list  */
#line 780 "grammar.y"
            {
#line 808 "grammar.y.pre"
		
		(yyval.number) = (yyvsp[-1].number) | (yyvsp[0].number);
		
	    }
#line 2704 "grammar.tab.c"
    break;

  case 54: /* type: type_modifier_list opt_basic_type  */
#line 790 "grammar.y"
            {
#line 834 "grammar.y.pre"
		(yyval.number) = ((yyvsp[-1].number) << 16) | (yyvsp[0].number);
		current_type = (yyval.number);
	    }
#line 2714 "grammar.tab.c"
    break;

  case 55: /* cast: '(' basic_type optional_star ')'  */
#line 799 "grammar.y"
            {
#line 842 "grammar.y.pre"
		(yyval.number) = (yyvsp[-2].number) | (yyvsp[-1].number);
	    }
#line 2723 "grammar.tab.c"
    break;

  case 57: /* opt_basic_type: %empty  */
#line 808 "grammar.y"
            {
#line 850 "grammar.y.pre"
		(yyval.number) = TYPE_UNKNOWN;
	    }
#line 2732 "grammar.tab.c"
    break;

  case 60: /* new_name: optional_star identifier  */
#line 821 "grammar.y"
            {
#line 862 "grammar.y.pre"
		if (current_type & (FUNC_VARARGS << 16)){
		    yyerror("Illegal to declare varargs variable.");
		    current_type &= ~(FUNC_VARARGS << 16);
		}
		/* Now it is ok to merge the two
		 * remember that class_num and varargs was the reason for above
		 * Do the merging once only per row of decls
		 */

		if (current_type & 0xffff0000){
		    current_type = (current_type >> 16) | (current_type & 0xffff);
		}

		current_type |= global_modifiers;

		if (!(current_type & DECL_ACCESS)) current_type |= DECL_PUBLIC;

		if ((current_type & ~DECL_MODS) == TYPE_VOID)
		    yyerror("Illegal to declare global variable of type void.");

		define_new_variable((yyvsp[0].string), current_type | (yyvsp[-1].number));
		scratch_free((yyvsp[0].string));
	    }
#line 2762 "grammar.tab.c"
    break;

  case 61: /* new_name: optional_star identifier L_ASSIGN expr0  */
#line 847 "grammar.y"
            {
#line 887 "grammar.y.pre"
		parse_node_t *expr, *newnode;
		int type;

		if (current_type & (FUNC_VARARGS << 16)){
		    yyerror("Illegal to declare varargs variable.");
		    current_type &= ~(FUNC_VARARGS << 16);
		}
		
		if (current_type & 0xffff0000){
		    current_type = (current_type >> 16) | (current_type & 0xffff);
		}

		current_type |= global_modifiers;

		if (!(current_type & DECL_ACCESS)) current_type |= DECL_PUBLIC;

		if ((current_type & ~DECL_MODS) == TYPE_VOID)
		    yyerror("Illegal to declare global variable of type void.");

		if ((yyvsp[-1].number) != F_ASSIGN)
		    yyerror("Only '=' is legal in initializers.");

		/* ignore current_type == 0, which gets a missing type error
		   later anyway */
		if (current_type) {
		    type = (current_type | (yyvsp[-3].number)) & ~DECL_MODS;
		    if ((current_type & ~DECL_MODS) == TYPE_VOID)
			yyerror("Illegal to declare global variable of type void.");
		    if (!compatible_types(type, (yyvsp[0].node)->type)) {
			char buff[256];
			char *end = EndOf(buff);
			char *p;
			
			p = strput(buff, end, "Type mismatch ");
			p = get_two_types(p, end, type, (yyvsp[0].node)->type);
			p = strput(p, end, " when initializing ");
			p = strput(p, end, (yyvsp[-2].string));
			yyerror(buff);
		    }
		} else type = 0;
		(yyvsp[0].node) = do_promotions((yyvsp[0].node), type);

		CREATE_BINARY_OP(expr, F_VOID_ASSIGN, 0, (yyvsp[0].node), 0);
		CREATE_OPCODE_1(expr->r.expr, F_GLOBAL_LVALUE, 0,
				define_new_variable((yyvsp[-2].string), current_type | (yyvsp[-3].number)));
		newnode = comp_trees[TREE_INIT];
		CREATE_TWO_VALUES(comp_trees[TREE_INIT], 0,
				  newnode, expr);
		scratch_free((yyvsp[-2].string));
	    }
#line 2819 "grammar.tab.c"
    break;

  case 62: /* block: '{' local_declarations statements '}'  */
#line 903 "grammar.y"
            {
#line 942 "grammar.y.pre"
		if ((yyvsp[-2].decl).node && (yyvsp[-1].node)) {
		    CREATE_STATEMENTS((yyval.decl).node, (yyvsp[-2].decl).node, (yyvsp[-1].node));
		} else (yyval.decl).node = ((yyvsp[-2].decl).node ? (yyvsp[-2].decl).node : (yyvsp[-1].node));
                (yyval.decl).num = (yyvsp[-2].decl).num;
            }
#line 2831 "grammar.tab.c"
    break;

  case 66: /* local_declarations: %empty  */
#line 916 "grammar.y"
            {
#line 954 "grammar.y.pre"
                (yyval.decl).node = 0;
                (yyval.decl).num = 0;
            }
#line 2841 "grammar.tab.c"
    break;

  case 67: /* $@5: %empty  */
#line 922 "grammar.y"
            {
#line 959 "grammar.y.pre"
		if ((yyvsp[0].number) == TYPE_VOID)
		    yyerror("Illegal to declare local variable of type void.");
                /* can't do this in basic_type b/c local_name_list contains
                 * expr0 which contains cast which contains basic_type
                 */
                current_type = (yyvsp[0].number);
            }
#line 2855 "grammar.tab.c"
    break;

  case 68: /* local_declarations: local_declarations basic_type $@5 local_name_list ';'  */
#line 932 "grammar.y"
            {
#line 968 "grammar.y.pre"
                if ((yyvsp[-4].decl).node && (yyvsp[-1].decl).node) {
		    CREATE_STATEMENTS((yyval.decl).node, (yyvsp[-4].decl).node, (yyvsp[-1].decl).node);
                } else (yyval.decl).node = ((yyvsp[-4].decl).node ? (yyvsp[-4].decl).node : (yyvsp[-1].decl).node);
                (yyval.decl).num = (yyvsp[-4].decl).num + (yyvsp[-1].decl).num;
            }
#line 2867 "grammar.tab.c"
    break;

  case 69: /* new_local_def: optional_star new_local_name  */
#line 944 "grammar.y"
            {
#line 979 "grammar.y.pre"
		if (current_type & LOCAL_MOD_REF) {
		    yyerror("Illegal to declare local variable as reference");
		    current_type &= ~LOCAL_MOD_REF;
		}
		add_local_name((yyvsp[0].string), current_type | (yyvsp[-1].number) | LOCAL_MOD_UNUSED);

		scratch_free((yyvsp[0].string));
		(yyval.node) = 0;
	    }
#line 2883 "grammar.tab.c"
    break;

  case 70: /* new_local_def: optional_star new_local_name L_ASSIGN expr0  */
#line 956 "grammar.y"
            {
#line 990 "grammar.y.pre"
		int type = (current_type | (yyvsp[-3].number)) & ~DECL_MODS;

		if (current_type & LOCAL_MOD_REF) {
		    yyerror("Illegal to declare local variable as reference");
		    current_type &= ~LOCAL_MOD_REF;
		    type &= ~LOCAL_MOD_REF;
		}

		if ((yyvsp[-1].number) != F_ASSIGN)
		    yyerror("Only '=' is allowed in initializers.");
		if (!compatible_types((yyvsp[0].node)->type, type)) {
		    char buff[256];
		    char *end = EndOf(buff);
		    char *p;
		    
		    p = strput(buff, end, "Type mismatch ");
		    p = get_two_types(p, end, type, (yyvsp[0].node)->type);
		    p = strput(p, end, " when initializing ");
		    p = strput(p, end, (yyvsp[-2].string));

		    yyerror(buff);
		}
		
		(yyvsp[0].node) = do_promotions((yyvsp[0].node), type);

		CREATE_UNARY_OP_1((yyval.node), F_VOID_ASSIGN_LOCAL, 0, (yyvsp[0].node),
				  add_local_name((yyvsp[-2].string), current_type | (yyvsp[-3].number) | LOCAL_MOD_UNUSED));
		scratch_free((yyvsp[-2].string));
	    }
#line 2919 "grammar.tab.c"
    break;

  case 71: /* single_new_local_def: arg_type optional_star new_local_name  */
#line 991 "grammar.y"
            {
#line 1024 "grammar.y.pre"
		if ((yyvsp[-2].number) == TYPE_VOID)
		    yyerror("Illegal to declare local variable of type void.");

		(yyval.number) = add_local_name((yyvsp[0].string), (yyvsp[-2].number) | (yyvsp[-1].number));
		scratch_free((yyvsp[0].string));
	    }
#line 2932 "grammar.tab.c"
    break;

  case 72: /* single_new_local_def_with_init: single_new_local_def L_ASSIGN expr0  */
#line 1003 "grammar.y"
            {
#line 1035 "grammar.y.pre"
                int type = type_of_locals_ptr[(yyvsp[-2].number)];

		if (type & LOCAL_MOD_REF) {
		    yyerror("Illegal to declare local variable as reference");
		    type_of_locals_ptr[(yyvsp[-2].number)] &= ~LOCAL_MOD_REF;
		}
		type &= ~LOCAL_MODS;

		if ((yyvsp[-1].number) != F_ASSIGN)
		    yyerror("Only '=' is allowed in initializers.");
		if (!compatible_types((yyvsp[0].node)->type, type)) {
		    char buff[256];
		    char *end = EndOf(buff);
		    char *p;
		    
		    p = strput(buff, end, "Type mismatch ");
		    p = get_two_types(p, end, type, (yyvsp[0].node)->type);
		    p = strput(p, end, " when initializing.");
		    yyerror(buff);
		}

		(yyvsp[0].node) = do_promotions((yyvsp[0].node), type);

		/* this is an expression */
		CREATE_BINARY_OP((yyval.node), F_ASSIGN, 0, (yyvsp[0].node), 0);
                CREATE_OPCODE_1((yyval.node)->r.expr, F_LOCAL_LVALUE, 0, (yyvsp[-2].number));
	    }
#line 2966 "grammar.tab.c"
    break;

  case 73: /* local_name_list: new_local_def  */
#line 1036 "grammar.y"
            {
#line 1067 "grammar.y.pre"
                (yyval.decl).node = (yyvsp[0].node);
                (yyval.decl).num = 1;
            }
#line 2976 "grammar.tab.c"
    break;

  case 74: /* local_name_list: new_local_def ',' local_name_list  */
#line 1042 "grammar.y"
            {
#line 1072 "grammar.y.pre"
                if ((yyvsp[-2].node) && (yyvsp[0].decl).node) {
		    CREATE_STATEMENTS((yyval.decl).node, (yyvsp[-2].node), (yyvsp[0].decl).node);
                } else (yyval.decl).node = ((yyvsp[-2].node) ? (yyvsp[-2].node) : (yyvsp[0].decl).node);
                (yyval.decl).num = 1 + (yyvsp[0].decl).num;
            }
#line 2988 "grammar.tab.c"
    break;

  case 75: /* statements: %empty  */
#line 1053 "grammar.y"
            {
#line 1082 "grammar.y.pre"
		(yyval.node) = 0;
	    }
#line 2997 "grammar.tab.c"
    break;

  case 76: /* statements: statement statements  */
#line 1058 "grammar.y"
            {
#line 1086 "grammar.y.pre"
		if ((yyvsp[-1].node) && (yyvsp[0].node)) {
		    CREATE_STATEMENTS((yyval.node), (yyvsp[-1].node), (yyvsp[0].node));
		} else (yyval.node) = ((yyvsp[-1].node) ? (yyvsp[-1].node) : (yyvsp[0].node));
            }
#line 3008 "grammar.tab.c"
    break;

  case 77: /* statements: error ';'  */
#line 1065 "grammar.y"
            {
#line 1092 "grammar.y.pre"
		(yyval.node) = 0;
            }
#line 3017 "grammar.tab.c"
    break;

  case 78: /* statement: comma_expr ';'  */
#line 1073 "grammar.y"
            {
#line 1099 "grammar.y.pre"
		(yyval.node) = pop_value((yyvsp[-1].node));
#ifdef DEBUG
		{
		    parse_node_t *replacement;
		    CREATE_STATEMENTS(replacement, (yyval.node), 0);
		    CREATE_OPCODE(replacement->r.expr, F_BREAK_POINT, 0);
		    (yyval.node) = replacement;
		}
#endif
	    }
#line 3034 "grammar.tab.c"
    break;

  case 84: /* statement: decl_block  */
#line 1091 "grammar.y"
           {
#line 1116 "grammar.y.pre"
                (yyval.node) = (yyvsp[0].decl).node;
                pop_n_locals((yyvsp[0].decl).num);
            }
#line 3044 "grammar.tab.c"
    break;

  case 85: /* statement: ';'  */
#line 1097 "grammar.y"
            {
#line 1121 "grammar.y.pre"
		(yyval.node) = 0;
	    }
#line 3053 "grammar.tab.c"
    break;

  case 86: /* statement: L_BREAK ';'  */
#line 1102 "grammar.y"
            {
#line 1125 "grammar.y.pre"
		if (context & SPECIAL_CONTEXT) {
		    yyerror("Cannot break out of catch { } or time_expression { }");
		    (yyval.node) = 0;
		} else
		if (context & SWITCH_CONTEXT) {
		    CREATE_CONTROL_JUMP((yyval.node), CJ_BREAK_SWITCH);
		} else
		if (context & LOOP_CONTEXT) {
		    CREATE_CONTROL_JUMP((yyval.node), CJ_BREAK);
		    if (context & LOOP_FOREACH) {
			parse_node_t *replace;
			CREATE_STATEMENTS(replace, 0, (yyval.node));
			CREATE_OPCODE(replace->l.expr, F_EXIT_FOREACH, 0);
			(yyval.node) = replace;
		    }
		} else {
		    yyerror("break statement outside loop");
		    (yyval.node) = 0;
		}
	    }
#line 3080 "grammar.tab.c"
    break;

  case 87: /* statement: L_CONTINUE ';'  */
#line 1125 "grammar.y"
            {
#line 1147 "grammar.y.pre"
		if (context & SPECIAL_CONTEXT)
		    yyerror("Cannot continue out of catch { } or time_expression { }");
		else
		if (!(context & LOOP_CONTEXT))
		    yyerror("continue statement outside loop");
		CREATE_CONTROL_JUMP((yyval.node), CJ_CONTINUE);
	    }
#line 3094 "grammar.tab.c"
    break;

  case 88: /* $@6: %empty  */
#line 1138 "grammar.y"
            {
#line 1159 "grammar.y.pre"
		(yyvsp[-3].number) = context;
		context = LOOP_CONTEXT;
	    }
#line 3104 "grammar.tab.c"
    break;

  case 89: /* while: L_WHILE '(' comma_expr ')' $@6 statement  */
#line 1144 "grammar.y"
            {
#line 1164 "grammar.y.pre"
		CREATE_LOOP((yyval.node), 1, (yyvsp[0].node), 0, optimize_loop_test((yyvsp[-3].node)));
		context = (yyvsp[-5].number);
	    }
#line 3114 "grammar.tab.c"
    break;

  case 90: /* $@7: %empty  */
#line 1153 "grammar.y"
            {
#line 1172 "grammar.y.pre"
		(yyvsp[0].number) = context;
		context = LOOP_CONTEXT;
	    }
#line 3124 "grammar.tab.c"
    break;

  case 91: /* do: L_DO $@7 statement L_WHILE '(' comma_expr ')' ';'  */
#line 1159 "grammar.y"
            {
#line 1177 "grammar.y.pre"
		CREATE_LOOP((yyval.node), 0, (yyvsp[-5].node), 0, optimize_loop_test((yyvsp[-2].node)));
		context = (yyvsp[-7].number);
	    }
#line 3134 "grammar.tab.c"
    break;

  case 92: /* $@8: %empty  */
#line 1168 "grammar.y"
            {
#line 1185 "grammar.y.pre"
		(yyvsp[-5].decl).node = pop_value((yyvsp[-5].decl).node);
		(yyvsp[-7].number) = context;
		context = LOOP_CONTEXT;
	    }
#line 3145 "grammar.tab.c"
    break;

  case 93: /* for: L_FOR '(' first_for_expr ';' for_expr ';' for_expr ')' $@8 statement  */
#line 1175 "grammar.y"
            {
#line 1191 "grammar.y.pre"
		(yyval.decl).num = (yyvsp[-7].decl).num; /* number of declarations (0/1) */
		
		(yyvsp[-3].node) = pop_value((yyvsp[-3].node));
		if ((yyvsp[-3].node) && IS_NODE((yyvsp[-3].node), NODE_UNARY_OP, F_INC)
		    && IS_NODE((yyvsp[-3].node)->r.expr, NODE_OPCODE_1, F_LOCAL_LVALUE)) {
		    long lvar = (yyvsp[-3].node)->r.expr->l.number;
		    CREATE_OPCODE_1((yyvsp[-3].node), F_LOOP_INCR, 0, lvar);
		}

		CREATE_STATEMENTS((yyval.decl).node, (yyvsp[-7].decl).node, 0);
		CREATE_LOOP((yyval.decl).node->r.expr, 1, (yyvsp[0].node), (yyvsp[-3].node), optimize_loop_test((yyvsp[-5].node)));

		context = (yyvsp[-9].number);
	      }
#line 3166 "grammar.tab.c"
    break;

  case 94: /* foreach_var: L_DEFINED_NAME  */
#line 1194 "grammar.y"
            {
#line 1209 "grammar.y.pre"
		if ((yyvsp[0].ihe)->dn.local_num != -1) {
		    CREATE_OPCODE_1((yyval.decl).node, F_LOCAL_LVALUE, 0, (yyvsp[0].ihe)->dn.local_num);
		    type_of_locals_ptr[(yyvsp[0].ihe)->dn.local_num] &= ~LOCAL_MOD_UNUSED;
		} else
		if ((yyvsp[0].ihe)->dn.global_num != -1) {
		    CREATE_OPCODE_1((yyval.decl).node, F_GLOBAL_LVALUE, 0, (yyvsp[0].ihe)->dn.global_num);
		} else {
		    char buf[256];
		    char *end = EndOf(buf);
		    char *p;

		    p = strput(buf, end, "'");
		    p = strput(p, end, (yyvsp[0].ihe)->name);
		    p = strput(p, end, "' is not a local or a global variable.");
		    yyerror(buf);
		    CREATE_OPCODE_1((yyval.decl).node, F_GLOBAL_LVALUE, 0, 0);
		}
		(yyval.decl).num = 0;
	    }
#line 3192 "grammar.tab.c"
    break;

  case 95: /* foreach_var: single_new_local_def  */
#line 1216 "grammar.y"
            {
#line 1230 "grammar.y.pre"
		if (type_of_locals_ptr[(yyvsp[0].number)] & LOCAL_MOD_REF) {
		    CREATE_OPCODE_1((yyval.decl).node, F_REF_LVALUE, 0, (yyvsp[0].number));
		} else {
		    CREATE_OPCODE_1((yyval.decl).node, F_LOCAL_LVALUE, 0, (yyvsp[0].number));
		    type_of_locals_ptr[(yyvsp[0].number)] &= ~LOCAL_MOD_UNUSED;
		}
		(yyval.decl).num = 1;
            }
#line 3207 "grammar.tab.c"
    break;

  case 96: /* foreach_var: L_IDENTIFIER  */
#line 1227 "grammar.y"
            {
#line 1240 "grammar.y.pre"
		char buf[256];
		char *end = EndOf(buf);
		char *p;
		
		p = strput(buf, end, "'");
		p = strput(p, end, (yyvsp[0].string));
		p = strput(p, end, "' is not a local or a global variable.");
		yyerror(buf);
		CREATE_OPCODE_1((yyval.decl).node, F_GLOBAL_LVALUE, 0, 0);
		scratch_free((yyvsp[0].string));
		(yyval.decl).num = 0;
	    }
#line 3226 "grammar.tab.c"
    break;

  case 97: /* foreach_vars: foreach_var  */
#line 1245 "grammar.y"
            {
#line 1257 "grammar.y.pre"
		CREATE_FOREACH((yyval.decl).node, (yyvsp[0].decl).node, 0);
		(yyval.decl).num = (yyvsp[0].decl).num;
            }
#line 3236 "grammar.tab.c"
    break;

  case 98: /* foreach_vars: foreach_var ',' foreach_var  */
#line 1251 "grammar.y"
            {
#line 1262 "grammar.y.pre"
		CREATE_FOREACH((yyval.decl).node, (yyvsp[-2].decl).node, (yyvsp[0].decl).node);
		(yyval.decl).num = (yyvsp[-2].decl).num + (yyvsp[0].decl).num;
		if ((yyvsp[-2].decl).node->v.number == F_REF_LVALUE)
		    yyerror("Mapping key may not be a reference in foreach()");
            }
#line 3248 "grammar.tab.c"
    break;

  case 99: /* $@9: %empty  */
#line 1262 "grammar.y"
            {
#line 1272 "grammar.y.pre"
		(yyvsp[-3].decl).node->v.expr = (yyvsp[-1].node);
		(yyvsp[-5].number) = context;
		context = LOOP_CONTEXT | LOOP_FOREACH;
            }
#line 3259 "grammar.tab.c"
    break;

  case 100: /* foreach: L_FOREACH '(' foreach_vars L_IN expr0 ')' $@9 statement  */
#line 1269 "grammar.y"
            {
#line 1278 "grammar.y.pre"
		(yyval.decl).num = (yyvsp[-5].decl).num;

		CREATE_STATEMENTS((yyval.decl).node, (yyvsp[-5].decl).node, 0);
		CREATE_LOOP((yyval.decl).node->r.expr, 2, (yyvsp[0].node), 0, 0);
		CREATE_OPCODE((yyval.decl).node->r.expr->r.expr, F_NEXT_FOREACH, 0);
		
		context = (yyvsp[-7].number);
	    }
#line 3274 "grammar.tab.c"
    break;

  case 101: /* for_expr: %empty  */
#line 1283 "grammar.y"
            {
#line 1291 "grammar.y.pre"
		(yyval.node) = 0;
	    }
#line 3283 "grammar.tab.c"
    break;

  case 103: /* first_for_expr: for_expr  */
#line 1292 "grammar.y"
            {
#line 1299 "grammar.y.pre"
	 	(yyval.decl).node = (yyvsp[0].node);
		(yyval.decl).num = 0;
	    }
#line 3293 "grammar.tab.c"
    break;

  case 104: /* first_for_expr: single_new_local_def_with_init  */
#line 1298 "grammar.y"
            {
#line 1304 "grammar.y.pre"
		(yyval.decl).node = (yyvsp[0].node);
		(yyval.decl).num = 1;
	    }
#line 3303 "grammar.tab.c"
    break;

  case 105: /* $@10: %empty  */
#line 1307 "grammar.y"
            {
#line 1312 "grammar.y.pre"
                (yyvsp[-3].number) = context;
                context &= LOOP_CONTEXT;
                context |= SWITCH_CONTEXT;
                (yyvsp[-2].number) = mem_block[A_CASES].current_size;
            }
#line 3315 "grammar.tab.c"
    break;

  case 106: /* switch: L_SWITCH '(' comma_expr ')' $@10 '{' local_declarations case switch_block '}'  */
#line 1315 "grammar.y"
            {
#line 1319 "grammar.y.pre"
                parse_node_t *node1, *node2;

                if ((yyvsp[-1].node)) {
		    CREATE_STATEMENTS(node1, (yyvsp[-2].node), (yyvsp[-1].node));
                } else node1 = (yyvsp[-2].node);

                if (context & SWITCH_STRINGS) {
                    NODE_NO_LINE(node2, NODE_SWITCH_STRINGS);
                } else if (context & SWITCH_RANGES) {
		    NODE_NO_LINE(node2, NODE_SWITCH_RANGES);
		} else if ((context & SWITCH_NUMBERS) ||
			   (context & SWITCH_NOT_EMPTY)) {
                    NODE_NO_LINE(node2, NODE_SWITCH_NUMBERS);
                } else {
		    // to prevent crashing during the remaining parsing bits
		    NODE_NO_LINE(node2, NODE_SWITCH_NUMBERS);

		    yyerror("need case statements in switch/case, not just default:"); //just a default case present
		}

                node2->l.expr = (yyvsp[-7].node);
                node2->r.expr = node1;
                prepare_cases(node2, (yyvsp[-8].number));
                context = (yyvsp[-9].number);
		(yyval.node) = node2;
		pop_n_locals((yyvsp[-3].decl).num);
            }
#line 3349 "grammar.tab.c"
    break;

  case 107: /* switch_block: case switch_block  */
#line 1348 "grammar.y"
          {
#line 1351 "grammar.y.pre"
               if ((yyvsp[0].node)){
		   CREATE_STATEMENTS((yyval.node), (yyvsp[-1].node), (yyvsp[0].node));
               } else (yyval.node) = (yyvsp[-1].node);
           }
#line 3360 "grammar.tab.c"
    break;

  case 108: /* switch_block: statement switch_block  */
#line 1355 "grammar.y"
           {
#line 1357 "grammar.y.pre"
               if ((yyvsp[0].node)){
		   CREATE_STATEMENTS((yyval.node), (yyvsp[-1].node), (yyvsp[0].node));
               } else (yyval.node) = (yyvsp[-1].node);
           }
#line 3371 "grammar.tab.c"
    break;

  case 109: /* switch_block: %empty  */
#line 1362 "grammar.y"
           {
#line 1363 "grammar.y.pre"
               (yyval.node) = 0;
           }
#line 3380 "grammar.tab.c"
    break;

  case 110: /* case: L_CASE case_label ':'  */
#line 1371 "grammar.y"
            {
#line 1371 "grammar.y.pre"
                (yyval.node) = (yyvsp[-1].node);
                (yyval.node)->v.expr = 0;

                add_to_mem_block(A_CASES, (char *)&((yyvsp[-1].node)), sizeof((yyvsp[-1].node)));
            }
#line 3392 "grammar.tab.c"
    break;

  case 111: /* case: L_CASE case_label L_RANGE case_label ':'  */
#line 1379 "grammar.y"
            {
#line 1378 "grammar.y.pre"
                if ( (yyvsp[-3].node)->kind != NODE_CASE_NUMBER
                    || (yyvsp[-1].node)->kind != NODE_CASE_NUMBER )
                    yyerror("String case labels not allowed as range bounds");
                if ((yyvsp[-3].node)->r.number > (yyvsp[-1].node)->r.number) break;

		context |= SWITCH_RANGES;

                (yyval.node) = (yyvsp[-3].node);
                (yyval.node)->v.expr = (yyvsp[-1].node);

                add_to_mem_block(A_CASES, (char *)&((yyvsp[-3].node)), sizeof((yyvsp[-3].node)));
            }
#line 3411 "grammar.tab.c"
    break;

  case 112: /* case: L_CASE case_label L_RANGE ':'  */
#line 1394 "grammar.y"
            {
#line 1392 "grammar.y.pre"
	        if ( (yyvsp[-2].node)->kind != NODE_CASE_NUMBER )
                    yyerror("String case labels not allowed as range bounds");

		context |= SWITCH_RANGES;

                (yyval.node) = (yyvsp[-2].node);
                (yyval.node)->v.expr = new_node();
		(yyval.node)->v.expr->kind = NODE_CASE_NUMBER;
		(yyval.node)->v.expr->r.number = ((unsigned long)-1)/2; //maxint

                add_to_mem_block(A_CASES, (char *)&((yyvsp[-2].node)), sizeof((yyvsp[-2].node)));
            }
#line 3430 "grammar.tab.c"
    break;

  case 113: /* case: L_CASE L_RANGE case_label ':'  */
#line 1409 "grammar.y"
            {
#line 1406 "grammar.y.pre"
	      if ( (yyvsp[-1].node)->kind != NODE_CASE_NUMBER )
                    yyerror("String case labels not allowed as range bounds");

		context |= SWITCH_RANGES;
		(yyval.node) = new_node();
		(yyval.node)->kind = NODE_CASE_NUMBER;
                (yyval.node)->r.number = (long) 1+ ((unsigned long)-1)/2; //maxint +1 wraps to min_int, on all computers i know, just not in the C standard iirc 
                (yyval.node)->v.expr = (yyvsp[-1].node);

                add_to_mem_block(A_CASES, (char *)&((yyval.node)), sizeof((yyval.node)));
            }
#line 3448 "grammar.tab.c"
    break;

  case 114: /* case: L_DEFAULT ':'  */
#line 1423 "grammar.y"
            {
#line 1419 "grammar.y.pre"
                if (context & SWITCH_DEFAULT) {
                    yyerror("Duplicate default");
                    (yyval.node) = 0;
                    break;
                }
		(yyval.node) = new_node();
		(yyval.node)->kind = NODE_DEFAULT;
                (yyval.node)->v.expr = 0;
                add_to_mem_block(A_CASES, (char *)&((yyval.node)), sizeof((yyval.node)));
                context |= SWITCH_DEFAULT;
            }
#line 3466 "grammar.tab.c"
    break;

  case 115: /* case_label: constant  */
#line 1440 "grammar.y"
            {
#line 1435 "grammar.y.pre"
                if ((context & SWITCH_STRINGS) && (yyvsp[0].pointer_int))
                    yyerror("Mixed case label list not allowed");

                if ((yyvsp[0].pointer_int))
		  context |= SWITCH_NUMBERS;
		else
		  context |= SWITCH_NOT_EMPTY;

		(yyval.node) = new_node();
		(yyval.node)->kind = NODE_CASE_NUMBER;
                (yyval.node)->r.expr = (parse_node_t *)(yyvsp[0].pointer_int);
            }
#line 3485 "grammar.tab.c"
    break;

  case 116: /* case_label: string_con1  */
#line 1455 "grammar.y"
            {
#line 1449 "grammar.y.pre"
		int str;
		
		str = store_prog_string((yyvsp[0].string));
                scratch_free((yyvsp[0].string));
                if (context & SWITCH_NUMBERS)
                    yyerror("Mixed case label list not allowed");
                context |= SWITCH_STRINGS;
		(yyval.node) = new_node();
		(yyval.node)->kind = NODE_CASE_STRING;
                (yyval.node)->r.number = str;
            }
#line 3503 "grammar.tab.c"
    break;

  case 117: /* constant: constant '|' constant  */
#line 1472 "grammar.y"
            {
#line 1465 "grammar.y.pre"
                (yyval.pointer_int) = (yyvsp[-2].pointer_int) | (yyvsp[0].pointer_int);
            }
#line 3512 "grammar.tab.c"
    break;

  case 118: /* constant: constant '^' constant  */
#line 1477 "grammar.y"
            {
#line 1469 "grammar.y.pre"
                (yyval.pointer_int) = (yyvsp[-2].pointer_int) ^ (yyvsp[0].pointer_int);
            }
#line 3521 "grammar.tab.c"
    break;

  case 119: /* constant: constant '&' constant  */
#line 1482 "grammar.y"
            {
#line 1473 "grammar.y.pre"
                (yyval.pointer_int) = (yyvsp[-2].pointer_int) & (yyvsp[0].pointer_int);
            }
#line 3530 "grammar.tab.c"
    break;

  case 120: /* constant: constant L_EQ constant  */
#line 1487 "grammar.y"
            {
#line 1477 "grammar.y.pre"
                (yyval.pointer_int) = (yyvsp[-2].pointer_int) == (yyvsp[0].pointer_int);
            }
#line 3539 "grammar.tab.c"
    break;

  case 121: /* constant: constant L_NE constant  */
#line 1492 "grammar.y"
            {
#line 1481 "grammar.y.pre"
                (yyval.pointer_int) = (yyvsp[-2].pointer_int) != (yyvsp[0].pointer_int);
            }
#line 3548 "grammar.tab.c"
    break;

  case 122: /* constant: constant L_ORDER constant  */
#line 1497 "grammar.y"
            {
#line 1485 "grammar.y.pre"
                switch((yyvsp[-1].number)){
                    case F_GE: (yyval.pointer_int) = (yyvsp[-2].pointer_int) >= (yyvsp[0].pointer_int); break;
                    case F_LE: (yyval.pointer_int) = (yyvsp[-2].pointer_int) <= (yyvsp[0].pointer_int); break;
                    case F_GT: (yyval.pointer_int) = (yyvsp[-2].pointer_int) >  (yyvsp[0].pointer_int); break;
                }
            }
#line 3561 "grammar.tab.c"
    break;

  case 123: /* constant: constant '<' constant  */
#line 1506 "grammar.y"
            {
#line 1493 "grammar.y.pre"
                (yyval.pointer_int) = (yyvsp[-2].pointer_int) < (yyvsp[0].pointer_int);
            }
#line 3570 "grammar.tab.c"
    break;

  case 124: /* constant: constant L_LSH constant  */
#line 1511 "grammar.y"
            {
#line 1497 "grammar.y.pre"
                (yyval.pointer_int) = (yyvsp[-2].pointer_int) << (yyvsp[0].pointer_int);
            }
#line 3579 "grammar.tab.c"
    break;

  case 125: /* constant: constant L_RSH constant  */
#line 1516 "grammar.y"
            {
#line 1501 "grammar.y.pre"
                (yyval.pointer_int) = (yyvsp[-2].pointer_int) >> (yyvsp[0].pointer_int);
            }
#line 3588 "grammar.tab.c"
    break;

  case 126: /* constant: constant '+' constant  */
#line 1521 "grammar.y"
            {
#line 1505 "grammar.y.pre"
                (yyval.pointer_int) = (yyvsp[-2].pointer_int) + (yyvsp[0].pointer_int);
            }
#line 3597 "grammar.tab.c"
    break;

  case 127: /* constant: constant '-' constant  */
#line 1526 "grammar.y"
            {
#line 1509 "grammar.y.pre"
                (yyval.pointer_int) = (yyvsp[-2].pointer_int) - (yyvsp[0].pointer_int);
            }
#line 3606 "grammar.tab.c"
    break;

  case 128: /* constant: constant '*' constant  */
#line 1531 "grammar.y"
            {
#line 1513 "grammar.y.pre"
                (yyval.pointer_int) = (yyvsp[-2].pointer_int) * (yyvsp[0].pointer_int);
            }
#line 3615 "grammar.tab.c"
    break;

  case 129: /* constant: constant '%' constant  */
#line 1536 "grammar.y"
            {
#line 1517 "grammar.y.pre"
                if ((yyvsp[0].pointer_int)) (yyval.pointer_int) = (yyvsp[-2].pointer_int) % (yyvsp[0].pointer_int); else yyerror("Modulo by zero");
            }
#line 3624 "grammar.tab.c"
    break;

  case 130: /* constant: constant '/' constant  */
#line 1541 "grammar.y"
            {
#line 1521 "grammar.y.pre"
                if ((yyvsp[0].pointer_int)) (yyval.pointer_int) = (yyvsp[-2].pointer_int) / (yyvsp[0].pointer_int); else yyerror("Division by zero");
            }
#line 3633 "grammar.tab.c"
    break;

  case 131: /* constant: '(' constant ')'  */
#line 1546 "grammar.y"
            {
#line 1525 "grammar.y.pre"
                (yyval.pointer_int) = (yyvsp[-1].pointer_int);
            }
#line 3642 "grammar.tab.c"
    break;

  case 132: /* constant: L_NUMBER  */
#line 1551 "grammar.y"
            {
#line 1529 "grammar.y.pre"
		(yyval.pointer_int) = (yyvsp[0].number);
	    }
#line 3651 "grammar.tab.c"
    break;

  case 133: /* constant: '-' L_NUMBER  */
#line 1556 "grammar.y"
            {
#line 1533 "grammar.y.pre"
                (yyval.pointer_int) = -(yyvsp[0].number);
            }
#line 3660 "grammar.tab.c"
    break;

  case 134: /* constant: L_NOT L_NUMBER  */
#line 1561 "grammar.y"
            {
#line 1537 "grammar.y.pre"
                (yyval.pointer_int) = !(yyvsp[0].number);
            }
#line 3669 "grammar.tab.c"
    break;

  case 135: /* constant: '~' L_NUMBER  */
#line 1566 "grammar.y"
            {
#line 1541 "grammar.y.pre"
                (yyval.pointer_int) = ~(yyvsp[0].number);
            }
#line 3678 "grammar.tab.c"
    break;

  case 136: /* comma_expr: expr0  */
#line 1574 "grammar.y"
            {
#line 1548 "grammar.y.pre"
		(yyval.node) = (yyvsp[0].node);
	    }
#line 3687 "grammar.tab.c"
    break;

  case 137: /* comma_expr: comma_expr ',' expr0  */
#line 1579 "grammar.y"
            {
#line 1552 "grammar.y.pre"
		CREATE_TWO_VALUES((yyval.node), (yyvsp[0].node)->type, pop_value((yyvsp[-2].node)), (yyvsp[0].node));
	    }
#line 3696 "grammar.tab.c"
    break;

  case 139: /* expr0: ref lvalue  */
#line 1591 "grammar.y"
            {
#line 1569 "grammar.y.pre"
		int op;

		if (!(context & ARG_LIST))
		    yyerror("ref illegal outside function argument list");
		else
		    num_refs++;
		
		switch ((yyvsp[0].node)->kind) {
		case NODE_PARAMETER_LVALUE:
		    op = F_LOCAL_LVALUE;
		    break;
		case NODE_TERNARY_OP:
		case NODE_OPCODE_1:
		case NODE_UNARY_OP_1:
		case NODE_BINARY_OP:
		    op = (yyvsp[0].node)->v.number;
		    if (op > F_RINDEX_LVALUE) 
			yyerror("Illegal to make reference to range");
		    break;
		default:
		    op=0; //0 is harmless, i hope
		    yyerror("unknown lvalue kind");
		}
		CREATE_UNARY_OP_1((yyval.node), F_MAKE_REF, TYPE_ANY, (yyvsp[0].node), op);
	    }
#line 3728 "grammar.tab.c"
    break;

  case 140: /* expr0: lvalue L_ASSIGN expr0  */
#line 1620 "grammar.y"
            {
#line 1598 "grammar.y.pre"
	        parse_node_t *l = (yyvsp[-2].node), *r = (yyvsp[0].node);
		/* set this up here so we can change it below */
		/* assignments are backwards; rhs is evaluated before
		   lhs, so put the RIGHT hand side on the LEFT hand
		   side of the tree node. */
		CREATE_BINARY_OP((yyval.node), (yyvsp[-1].number), r->type, r, l);

		if (exact_types && !compatible_types(r->type, l->type) &&
		    !((yyvsp[-1].number) == F_ADD_EQ
		      && l->type == TYPE_STRING && 
		      (COMP_TYPE(r->type, TYPE_NUMBER))||r->type == TYPE_OBJECT)) {
		    char buf[256];
		    char *end = EndOf(buf);
		    char *p;
		    p = strput(buf, end, "Bad assignment ");
		    p = get_two_types(p, end, l->type, r->type);
		    p = strput(p, end, ".");
		    yyerror(buf);
		}
		
		if ((yyvsp[-1].number) == F_ASSIGN)
		    (yyval.node)->l.expr = do_promotions(r, l->type);
	    }
#line 3758 "grammar.tab.c"
    break;

  case 141: /* expr0: error L_ASSIGN expr0  */
#line 1646 "grammar.y"
            {
#line 1623 "grammar.y.pre"
		yyerror("Illegal LHS");
		CREATE_ERROR((yyval.node));
	    }
#line 3768 "grammar.tab.c"
    break;

  case 142: /* expr0: expr0 '?' expr0 ':' expr0  */
#line 1652 "grammar.y"
            {
#line 1628 "grammar.y.pre"
		parse_node_t *p1 = (yyvsp[-2].node), *p2 = (yyvsp[0].node);

		if (exact_types && !compatible_types2(p1->type, p2->type)) {
		    char buf[256];
		    char *end = EndOf(buf);
		    char *p;
		    
		    p = strput(buf, end, "Types in ?: do not match ");
		    p = get_two_types(p, end, p1->type, p2->type);
		    p = strput(p, end, ".");
		    yywarn(buf);
		}

		/* optimize if last expression did F_NOT */
		if (IS_NODE((yyvsp[-4].node), NODE_UNARY_OP, F_NOT)) {
		    /* !a ? b : c  --> a ? c : b */
		    CREATE_IF((yyval.node), (yyvsp[-4].node)->r.expr, p2, p1);
		} else {
		    CREATE_IF((yyval.node), (yyvsp[-4].node), p1, p2);
		}
		(yyval.node)->type = ((p1->type == p2->type) ? p1->type : TYPE_ANY);
	    }
#line 3797 "grammar.tab.c"
    break;

  case 143: /* expr0: expr0 L_LOR expr0  */
#line 1677 "grammar.y"
            {
#line 1652 "grammar.y.pre"
		CREATE_LAND_LOR((yyval.node), F_LOR, (yyvsp[-2].node), (yyvsp[0].node));
		if (IS_NODE((yyvsp[-2].node), NODE_LAND_LOR, F_LOR))
		    (yyvsp[-2].node)->kind = NODE_BRANCH_LINK;
	    }
#line 3808 "grammar.tab.c"
    break;

  case 144: /* expr0: expr0 L_LAND expr0  */
#line 1684 "grammar.y"
            {
#line 1658 "grammar.y.pre"
		CREATE_LAND_LOR((yyval.node), F_LAND, (yyvsp[-2].node), (yyvsp[0].node));
		if (IS_NODE((yyvsp[-2].node), NODE_LAND_LOR, F_LAND))
		    (yyvsp[-2].node)->kind = NODE_BRANCH_LINK;
	    }
#line 3819 "grammar.tab.c"
    break;

  case 145: /* expr0: expr0 '|' expr0  */
#line 1691 "grammar.y"
            {
#line 1664 "grammar.y.pre"
		int t1 = (yyvsp[-2].node)->type, t3 = (yyvsp[0].node)->type;
		
		if (is_boolean((yyvsp[-2].node)) && is_boolean((yyvsp[0].node)))
		    yywarn("bitwise operation on boolean values.");
		if ((t1 & TYPE_MOD_ARRAY) || (t3 & TYPE_MOD_ARRAY)) {
		    if (t1 != t3) {
			if ((t1 != TYPE_ANY) && (t3 != TYPE_ANY) &&
			    !(t1 & t3 & TYPE_MOD_ARRAY)) {
			    char buf[256];
			    char *end = EndOf(buf);
			    char *p;

			    p = strput(buf, end, "Incompatible types for | ");
			    p = get_two_types(p, end, t1, t3);
			    p = strput(p, end, ".");
			    yyerror(buf);
			}
			t1 = TYPE_ANY | TYPE_MOD_ARRAY;
		    }
		    CREATE_BINARY_OP((yyval.node), F_OR, t1, (yyvsp[-2].node), (yyvsp[0].node));
		}
		else (yyval.node) = binary_int_op((yyvsp[-2].node), (yyvsp[0].node), F_OR, "|");		
	    }
#line 3849 "grammar.tab.c"
    break;

  case 146: /* expr0: expr0 '^' expr0  */
#line 1717 "grammar.y"
            {
#line 1689 "grammar.y.pre"
		(yyval.node) = binary_int_op((yyvsp[-2].node), (yyvsp[0].node), F_XOR, "^");
	    }
#line 3858 "grammar.tab.c"
    break;

  case 147: /* expr0: expr0 '&' expr0  */
#line 1722 "grammar.y"
            {
#line 1693 "grammar.y.pre"
		int t1 = (yyvsp[-2].node)->type, t3 = (yyvsp[0].node)->type;
		if (is_boolean((yyvsp[-2].node)) && is_boolean((yyvsp[0].node)))
		    yywarn("bitwise operation on boolean values.");
		if ((t1 & TYPE_MOD_ARRAY) || (t3 & TYPE_MOD_ARRAY)) {
		    if (t1 != t3) {
			if ((t1 != TYPE_ANY) && (t3 != TYPE_ANY) &&
			    !(t1 & t3 & TYPE_MOD_ARRAY)) {
			    char buf[256];
			    char *end = EndOf(buf);
			    char *p;
			    
			    p = strput(buf, end, "Incompatible types for & ");
			    p = get_two_types(p, end, t1, t3);
			    p = strput(p, end, ".");
			    yyerror(buf);
			}
			t1 = TYPE_ANY | TYPE_MOD_ARRAY;
		    } 
		    CREATE_BINARY_OP((yyval.node), F_AND, t1, (yyvsp[-2].node), (yyvsp[0].node));
		} else (yyval.node) = binary_int_op((yyvsp[-2].node), (yyvsp[0].node), F_AND, "&");
	    }
#line 3886 "grammar.tab.c"
    break;

  case 148: /* expr0: expr0 L_EQ expr0  */
#line 1746 "grammar.y"
            {
#line 1716 "grammar.y.pre"
		if (exact_types && !compatible_types2((yyvsp[-2].node)->type, (yyvsp[0].node)->type)){
		    char buf[256];
		    char *end = EndOf(buf);
		    char *p;
		    
		    p = strput(buf, end, "== always false because of incompatible types ");
		    p = get_two_types(p, end, (yyvsp[-2].node)->type, (yyvsp[0].node)->type);
		    p = strput(p, end, ".");
		    yyerror(buf);
		}
		/* x == 0 -> !x */
		if (IS_NODE((yyvsp[-2].node), NODE_NUMBER, 0)) {
		    CREATE_UNARY_OP((yyval.node), F_NOT, TYPE_NUMBER, (yyvsp[0].node));
		} else
		if (IS_NODE((yyvsp[0].node), NODE_NUMBER, 0)) {
		    CREATE_UNARY_OP((yyval.node), F_NOT, TYPE_NUMBER, (yyvsp[-2].node));
		} else {
		    CREATE_BINARY_OP((yyval.node), F_EQ, TYPE_NUMBER, (yyvsp[-2].node), (yyvsp[0].node));
		}
	    }
#line 3913 "grammar.tab.c"
    break;

  case 149: /* expr0: expr0 L_NE expr0  */
#line 1769 "grammar.y"
            {
#line 1738 "grammar.y.pre"
		if (exact_types && !compatible_types2((yyvsp[-2].node)->type, (yyvsp[0].node)->type)){
		    char buf[256];
		    char *end = EndOf(buf);
		    char *p;

		    p = strput(buf, end, "!= always true because of incompatible types ");
		    p = get_two_types(p, end, (yyvsp[-2].node)->type, (yyvsp[0].node)->type);
		    p = strput(p, end, ".");
		    yyerror(buf);
		}
                CREATE_BINARY_OP((yyval.node), F_NE, TYPE_NUMBER, (yyvsp[-2].node), (yyvsp[0].node));
	    }
#line 3932 "grammar.tab.c"
    break;

  case 150: /* expr0: expr0 L_ORDER expr0  */
#line 1784 "grammar.y"
            {
#line 1752 "grammar.y.pre"
		if (exact_types) {
		    int t1 = (yyvsp[-2].node)->type;
		    int t3 = (yyvsp[0].node)->type;

		    if (!COMP_TYPE(t1, TYPE_NUMBER) 
			&& !COMP_TYPE(t1, TYPE_STRING)) {
			char buf[256];
			char *end = EndOf(buf);
			char *p;
			
			p = strput(buf, end, "Bad left argument to '");
			p = strput(p, end, query_instr_name((yyvsp[-1].number)));
			p = strput(p, end, "' : \"");
			p = get_type_name(p, end, t1);
			p = strput(p, end, "\"");
			yyerror(buf);
		    } else if (!COMP_TYPE(t3, TYPE_NUMBER) 
			       && !COMP_TYPE(t3, TYPE_STRING)) {
                        char buf[256];
			char *end = EndOf(buf);
			char *p;
			
                        p = strput(buf, end, "Bad right argument to '");
                        p = strput(p, end, query_instr_name((yyvsp[-1].number)));
                        p = strput(p, end, "' : \"");
                        p = get_type_name(p, end, t3);
			p = strput(p, end, "\"");
			yyerror(buf);
		    } else if (!compatible_types2(t1,t3)) {
			char buf[256];
			char *end = EndOf(buf);
			char *p;
			
			p = strput(buf, end, "Arguments to ");
			p = strput(p, end, query_instr_name((yyvsp[-1].number)));
			p = strput(p, end, " do not have compatible types : ");
			p = get_two_types(p, end, t1, t3);
			yyerror(buf);
		    }
		}
                CREATE_BINARY_OP((yyval.node), (yyvsp[-1].number), TYPE_NUMBER, (yyvsp[-2].node), (yyvsp[0].node));
	    }
#line 3981 "grammar.tab.c"
    break;

  case 151: /* expr0: expr0 '<' expr0  */
#line 1829 "grammar.y"
            {
#line 1796 "grammar.y.pre"
                if (exact_types) {
                    int t1 = (yyvsp[-2].node)->type, t3 = (yyvsp[0].node)->type;

                    if (!COMP_TYPE(t1, TYPE_NUMBER) 
			&& !COMP_TYPE(t1, TYPE_STRING)) {
                        char buf[256];
			char *end = EndOf(buf);
			char *p;
			
			p = strput(buf, end, "Bad left argument to '<' : \"");
                        p = get_type_name(p, end, t1);
			p = strput(p, end, "\"");
                        yyerror(buf);
                    } else if (!COMP_TYPE(t3, TYPE_NUMBER)
			       && !COMP_TYPE(t3, TYPE_STRING)) {
                        char buf[200];
			char *end = EndOf(buf);
			char *p;
			
                        p = strput(buf, end, "Bad right argument to '<' : \"");
                        p = get_type_name(p, end, t3);
                        p = strput(p, end, "\"");
                        yyerror(buf);
                    } else if (!compatible_types2(t1,t3)) {
                        char buf[256];
			char *end = EndOf(buf);
			char *p;
			
			p = strput(buf, end, "Arguments to < do not have compatible types : ");
			p = get_two_types(p, end, t1, t3);
                        yyerror(buf);
                    }
                }
                CREATE_BINARY_OP((yyval.node), F_LT, TYPE_NUMBER, (yyvsp[-2].node), (yyvsp[0].node));
            }
#line 4023 "grammar.tab.c"
    break;

  case 152: /* expr0: expr0 L_LSH expr0  */
#line 1867 "grammar.y"
            {
#line 1833 "grammar.y.pre"
		(yyval.node) = binary_int_op((yyvsp[-2].node), (yyvsp[0].node), F_LSH, "<<");
	    }
#line 4032 "grammar.tab.c"
    break;

  case 153: /* expr0: expr0 L_RSH expr0  */
#line 1872 "grammar.y"
            {
#line 1837 "grammar.y.pre"
		(yyval.node) = binary_int_op((yyvsp[-2].node), (yyvsp[0].node), F_RSH, ">>");
	    }
#line 4041 "grammar.tab.c"
    break;

  case 154: /* expr0: expr0 '+' expr0  */
#line 1877 "grammar.y"
            {
#line 1841 "grammar.y.pre"
		int result_type;

		if (exact_types) {
		    int t1 = (yyvsp[-2].node)->type, t3 = (yyvsp[0].node)->type;

		    if (t1 == t3){
#ifdef CAST_CALL_OTHERS
			if (t1 == TYPE_UNKNOWN){
			    yyerror("Bad arguments to '+' (unknown vs unknown)");
			    result_type = TYPE_ANY;
			} else
#endif
			    result_type = t1;
		    }
		    else if (t1 == TYPE_ANY) {
			if (t3 == TYPE_FUNCTION) {
			    yyerror("Bad right argument to '+' (function)");
			    result_type = TYPE_ANY;
			} else result_type = t3;
		    } else if (t3 == TYPE_ANY) {
			if (t1 == TYPE_FUNCTION) {
			    yyerror("Bad left argument to '+' (function)");
			    result_type = TYPE_ANY;
			} else result_type = t1;
		    } else {
			switch(t1) {
			case TYPE_OBJECT:
			  if(t3 == TYPE_STRING){
			    result_type = TYPE_STRING;
			  } else goto add_error;
			  break;
			case TYPE_STRING:
			  {
			    if (t3 == TYPE_REAL || t3 == TYPE_NUMBER || t3 == TYPE_OBJECT){
			      result_type = TYPE_STRING;
			    } else goto add_error;
			    break;
			  }
			case TYPE_NUMBER:
			  {
			    if (t3 == TYPE_REAL || t3 == TYPE_STRING)
			      result_type = t3;
			    else goto add_error;
			    break;
			  }
			case TYPE_REAL:
			  {
			    if (t3 == TYPE_NUMBER) result_type = TYPE_REAL;
			    else if (t3 == TYPE_STRING) result_type = TYPE_STRING;
			    else goto add_error;
			    break;
			  }
			default:
			  {
			    if (t1 & t3 & TYPE_MOD_ARRAY) {
			      result_type = TYPE_ANY|TYPE_MOD_ARRAY;
			      break;
			    }
			  add_error:
			    {
			      char buf[256];
			      char *end = EndOf(buf);
			      char *p;
			      
			      p = strput(buf, end, "Invalid argument types to '+' ");
			      p = get_two_types(p, end, t1, t3);
			      yyerror(buf);
			      result_type = TYPE_ANY;
			    }
			  }
			}
		    }
		} else 
		    result_type = TYPE_ANY;

		/* TODO: perhaps we should do (string)+(number) and
		 * (number)+(string) constant folding as well.
		 *
		 * codefor string x = "foo" + 1;
		 *
		 * 0000: push string 13, number 1
		 * 0004: +
		 * 0005: (void)assign_local LV0
		 */
		switch ((yyvsp[-2].node)->kind) {
		case NODE_NUMBER:
		    /* 0 + X */
		    if ((yyvsp[-2].node)->v.number == 0 &&
			((yyvsp[0].node)->type == TYPE_NUMBER || (yyvsp[0].node)->type == TYPE_REAL)) {
			(yyval.node) = (yyvsp[0].node);
			break;
		    }
		    if ((yyvsp[0].node)->kind == NODE_NUMBER) {
			(yyval.node) = (yyvsp[-2].node);
			(yyvsp[-2].node)->v.number += (yyvsp[0].node)->v.number;
			break;
		    }
		    if ((yyvsp[0].node)->kind == NODE_REAL) {
			(yyval.node) = (yyvsp[0].node);
			(yyvsp[0].node)->v.real += (yyvsp[-2].node)->v.number;
			break;
		    }
		    /* swapping the nodes may help later constant folding */
		    if ((yyvsp[0].node)->type != TYPE_STRING && (yyvsp[0].node)->type != TYPE_ANY)
			CREATE_BINARY_OP((yyval.node), F_ADD, result_type, (yyvsp[0].node), (yyvsp[-2].node));
		    else
			CREATE_BINARY_OP((yyval.node), F_ADD, result_type, (yyvsp[-2].node), (yyvsp[0].node));
		    break;
		case NODE_REAL:
		    if ((yyvsp[0].node)->kind == NODE_NUMBER) {
			(yyval.node) = (yyvsp[-2].node);
			(yyvsp[-2].node)->v.real += (yyvsp[0].node)->v.number;
			break;
		    }
		    if ((yyvsp[0].node)->kind == NODE_REAL) {
			(yyval.node) = (yyvsp[-2].node);
			(yyvsp[-2].node)->v.real += (yyvsp[0].node)->v.real;
			break;
		    }
		    /* swapping the nodes may help later constant folding */
		    if ((yyvsp[0].node)->type != TYPE_STRING && (yyvsp[0].node)->type != TYPE_ANY)
			CREATE_BINARY_OP((yyval.node), F_ADD, result_type, (yyvsp[0].node), (yyvsp[-2].node));
		    else
			CREATE_BINARY_OP((yyval.node), F_ADD, result_type, (yyvsp[-2].node), (yyvsp[0].node));
		    break;
		case NODE_STRING:
		    if ((yyvsp[0].node)->kind == NODE_STRING) {
			/* Combine strings */
			long n1, n2;
			const char *s1, *s2;
			char *news;
			int l;

			n1 = (yyvsp[-2].node)->v.number;
			n2 = (yyvsp[0].node)->v.number;
			s1 = PROG_STRING(n1);
			s2 = PROG_STRING(n2);
			news = (char *)DXALLOC( (l = strlen(s1))+strlen(s2)+1, TAG_COMPILER, "combine string" );
			strcpy(news, s1);
			strcat(news + l, s2);
			/* free old strings (ordering may help shrink table) */
			if (n1 > n2) {
			    free_prog_string(n1); free_prog_string(n2);
			} else {
			    free_prog_string(n2); free_prog_string(n1);
			}
			(yyval.node) = (yyvsp[-2].node);
			(yyval.node)->v.number = store_prog_string(news);
			FREE(news);
			break;
		    }
		    /* Yes, this can actually happen for absurd code like:
		     * (int)"foo" + 0
		     * for which I guess we ought to generate (int)"foo"
		     * in order to be consistent.  Then shoot the coder.
		     */
		    /* FALLTHROUGH */
		default:
		    /* X + 0 */
		    if (IS_NODE((yyvsp[0].node), NODE_NUMBER, 0) &&
			((yyvsp[-2].node)->type == TYPE_NUMBER || (yyvsp[-2].node)->type == TYPE_REAL)) {
			(yyval.node) = (yyvsp[-2].node);
			break;
		    }
		    CREATE_BINARY_OP((yyval.node), F_ADD, result_type, (yyvsp[-2].node), (yyvsp[0].node));
		    break;
		}
	    }
#line 4216 "grammar.tab.c"
    break;

  case 155: /* expr0: expr0 '-' expr0  */
#line 2048 "grammar.y"
            {
#line 2011 "grammar.y.pre"
		int result_type;

		if (exact_types) {
		    int t1 = (yyvsp[-2].node)->type, t3 = (yyvsp[0].node)->type;

		    if (t1 == t3){
			switch(t1){
			    case TYPE_ANY:
			    case TYPE_NUMBER:
			    case TYPE_REAL:
			        result_type = t1;
				break;
			    default:
				if (!(t1 & TYPE_MOD_ARRAY)){
				    type_error("Bad argument number 1 to '-'", t1);
				    result_type = TYPE_ANY;
				} else result_type = t1;
			}
		    } else if (t1 == TYPE_ANY){
			switch(t3){
			    case TYPE_REAL:
			    case TYPE_NUMBER:
			        result_type = t3;
				break;
			    default:
				if (!(t3 & TYPE_MOD_ARRAY)){
				    type_error("Bad argument number 2 to '-'", t3);
				    result_type = TYPE_ANY;
				} else result_type = t3;
			}
		    } else if (t3 == TYPE_ANY){
			switch(t1){
			    case TYPE_REAL:
			    case TYPE_NUMBER:
			        result_type = t1;
				break;
			    default:
				if (!(t1 & TYPE_MOD_ARRAY)){
				    type_error("Bad argument number 1 to '-'", t1);
				    result_type = TYPE_ANY;
				} else result_type = t1;
			}
		    } else if ((t1 == TYPE_REAL && t3 == TYPE_NUMBER) ||
			       (t3 == TYPE_REAL && t1 == TYPE_NUMBER)){
			result_type = TYPE_REAL;
		    } else if (t1 & t3 & TYPE_MOD_ARRAY){
			result_type = TYPE_MOD_ARRAY|TYPE_ANY;
		    } else {
			char buf[256];
			char *end = EndOf(buf);
			char *p;
			
			p = strput(buf, end, "Invalid types to '-' ");
			p = get_two_types(p, end, t1, t3);
			yyerror(buf);
			result_type = TYPE_ANY;
		    }
		} else result_type = TYPE_ANY;
		
		switch ((yyvsp[-2].node)->kind) {
		case NODE_NUMBER:
		    if ((yyvsp[-2].node)->v.number == 0) {
			CREATE_UNARY_OP((yyval.node), F_NEGATE, (yyvsp[0].node)->type, (yyvsp[0].node));
		    } else if ((yyvsp[0].node)->kind == NODE_NUMBER) {
			(yyval.node) = (yyvsp[-2].node);
			(yyvsp[-2].node)->v.number -= (yyvsp[0].node)->v.number;
		    } else if ((yyvsp[0].node)->kind == NODE_REAL) {
			(yyval.node) = (yyvsp[0].node);
			(yyvsp[0].node)->v.real = (yyvsp[-2].node)->v.number - (yyvsp[0].node)->v.real;
		    } else {
			CREATE_BINARY_OP((yyval.node), F_SUBTRACT, result_type, (yyvsp[-2].node), (yyvsp[0].node));
		    }
		    break;
		case NODE_REAL:
		    if ((yyvsp[0].node)->kind == NODE_NUMBER) {
			(yyval.node) = (yyvsp[-2].node);
			(yyvsp[-2].node)->v.real -= (yyvsp[0].node)->v.number;
		    } else if ((yyvsp[0].node)->kind == NODE_REAL) {
			(yyval.node) = (yyvsp[-2].node);
			(yyvsp[-2].node)->v.real -= (yyvsp[0].node)->v.real;
		    } else {
			CREATE_BINARY_OP((yyval.node), F_SUBTRACT, result_type, (yyvsp[-2].node), (yyvsp[0].node));
		    }
		    break;
		default:
		    /* optimize X-0 */
		    if (IS_NODE((yyvsp[0].node), NODE_NUMBER, 0)) {
			(yyval.node) = (yyvsp[-2].node);
		    } 
		    CREATE_BINARY_OP((yyval.node), F_SUBTRACT, result_type, (yyvsp[-2].node), (yyvsp[0].node));
		}
	    }
#line 4315 "grammar.tab.c"
    break;

  case 156: /* expr0: expr0 '*' expr0  */
#line 2143 "grammar.y"
            {
#line 2105 "grammar.y.pre"
		int result_type;

		if (exact_types){
		    int t1 = (yyvsp[-2].node)->type, t3 = (yyvsp[0].node)->type;

		    if (t1 == t3){
			switch(t1){
			    case TYPE_MAPPING:
			    case TYPE_ANY:
			    case TYPE_NUMBER:
			    case TYPE_REAL:
			        result_type = t1;
				break;
			default:
				type_error("Bad argument number 1 to '*'", t1);
				result_type = TYPE_ANY;
			}
		    } else if (t1 == TYPE_ANY || t3 == TYPE_ANY){
			int t = (t1 == TYPE_ANY) ? t3 : t1;
			switch(t){
			    case TYPE_NUMBER:
			    case TYPE_REAL:
			    case TYPE_MAPPING:
			        result_type = t;
				break;
			    default:
				type_error((t1 == TYPE_ANY) ?
					   "Bad argument number 2 to '*'" :
					   "Bad argument number 1 to '*'",
					   t);
				result_type = TYPE_ANY;
			}
		    } else if ((t1 == TYPE_NUMBER && t3 == TYPE_REAL) ||
			       (t1 == TYPE_REAL && t3 == TYPE_NUMBER)){
			result_type = TYPE_REAL;
		    } else {
			char buf[256];
			char *end = EndOf(buf);
			char *p;
			
			p = strput(buf, end, "Invalid types to '*' ");
			p = get_two_types(p, end, t1, t3);
			yyerror(buf);
			result_type = TYPE_ANY;
		    }
		} else result_type = TYPE_ANY;

		switch ((yyvsp[-2].node)->kind) {
		case NODE_NUMBER:
		    if ((yyvsp[0].node)->kind == NODE_NUMBER) {
			(yyval.node) = (yyvsp[-2].node);
			(yyval.node)->v.number *= (yyvsp[0].node)->v.number;
			break;
		    }
		    if ((yyvsp[0].node)->kind == NODE_REAL) {
			(yyval.node) = (yyvsp[0].node);
			(yyvsp[0].node)->v.real *= (yyvsp[-2].node)->v.number;
			break;
		    }
		    CREATE_BINARY_OP((yyval.node), F_MULTIPLY, result_type, (yyvsp[0].node), (yyvsp[-2].node));
		    break;
		case NODE_REAL:
		    if ((yyvsp[0].node)->kind == NODE_NUMBER) {
			(yyval.node) = (yyvsp[-2].node);
			(yyvsp[-2].node)->v.real *= (yyvsp[0].node)->v.number;
			break;
		    }
		    if ((yyvsp[0].node)->kind == NODE_REAL) {
			(yyval.node) = (yyvsp[-2].node);
			(yyvsp[-2].node)->v.real *= (yyvsp[0].node)->v.real;
			break;
		    }
		    CREATE_BINARY_OP((yyval.node), F_MULTIPLY, result_type, (yyvsp[0].node), (yyvsp[-2].node));
		    break;
		default:
		    CREATE_BINARY_OP((yyval.node), F_MULTIPLY, result_type, (yyvsp[-2].node), (yyvsp[0].node));
		}
	    }
#line 4400 "grammar.tab.c"
    break;

  case 157: /* expr0: expr0 '%' expr0  */
#line 2224 "grammar.y"
            {
#line 2185 "grammar.y.pre"
		(yyval.node) = binary_int_op((yyvsp[-2].node), (yyvsp[0].node), F_MOD, "%");
	    }
#line 4409 "grammar.tab.c"
    break;

  case 158: /* expr0: expr0 '/' expr0  */
#line 2229 "grammar.y"
            {
#line 2189 "grammar.y.pre"
		int result_type;

		if (exact_types){
		    int t1 = (yyvsp[-2].node)->type, t3 = (yyvsp[0].node)->type;

		    if (t1 == t3){
			switch(t1){
			    case TYPE_NUMBER:
			    case TYPE_REAL:
			case TYPE_ANY:
			        result_type = t1;
				break;
			    default:
				type_error("Bad argument 1 to '/'", t1);
				result_type = TYPE_ANY;
			}
		    } else if (t1 == TYPE_ANY || t3 == TYPE_ANY){
			int t = (t1 == TYPE_ANY) ? t3 : t1;
			if (t == TYPE_REAL || t == TYPE_NUMBER)
			    result_type = t; 
			else {
			    type_error(t1 == TYPE_ANY ?
				       "Bad argument 2 to '/'" :
				       "Bad argument 1 to '/'", t);
			    result_type = TYPE_ANY;
			}
		    } else if ((t1 == TYPE_NUMBER && t3 == TYPE_REAL) ||
			       (t1 == TYPE_REAL && t3 == TYPE_NUMBER)) {
			result_type = TYPE_REAL;
		    } else {
			char buf[256];
			char *end = EndOf(buf);
			char *p;
			
			p = strput(buf, end, "Invalid types to '/' ");
			p = get_two_types(p, end, t1, t3);
			yyerror(buf);
			result_type = TYPE_ANY;
		    }
		} else result_type = TYPE_ANY;		    

		/* constant expressions */
		switch ((yyvsp[-2].node)->kind) {
		case NODE_NUMBER:
		    if ((yyvsp[0].node)->kind == NODE_NUMBER) {
			if ((yyvsp[0].node)->v.number == 0) {
			    yyerror("Divide by zero in constant");
			    (yyval.node) = (yyvsp[-2].node);
			    break;
			}
			(yyval.node) = (yyvsp[-2].node);
			(yyvsp[-2].node)->v.number /= (yyvsp[0].node)->v.number;
			break;
		    }
		    if ((yyvsp[0].node)->kind == NODE_REAL) {
			if ((yyvsp[0].node)->v.real == 0.0) {
			    yyerror("Divide by zero in constant");
			    (yyval.node) = (yyvsp[-2].node);
			    break;
			}
			(yyval.node) = (yyvsp[0].node);
			(yyvsp[0].node)->v.real = ((yyvsp[-2].node)->v.number / (yyvsp[0].node)->v.real);
			break;
		    }
		    CREATE_BINARY_OP((yyval.node), F_DIVIDE, result_type, (yyvsp[-2].node), (yyvsp[0].node));
		    break;
		case NODE_REAL:
		    if ((yyvsp[0].node)->kind == NODE_NUMBER) {
			if ((yyvsp[0].node)->v.number == 0) {
			    yyerror("Divide by zero in constant");
			    (yyval.node) = (yyvsp[-2].node);
			    break;
			}
			(yyval.node) = (yyvsp[-2].node);
			(yyvsp[-2].node)->v.real /= (yyvsp[0].node)->v.number;
			break;
		    }
		    if ((yyvsp[0].node)->kind == NODE_REAL) {
			if ((yyvsp[0].node)->v.real == 0.0) {
			    yyerror("Divide by zero in constant");
			    (yyval.node) = (yyvsp[-2].node);
			    break;
			}
			(yyval.node) = (yyvsp[-2].node);
			(yyvsp[-2].node)->v.real /= (yyvsp[0].node)->v.real;
			break;
		    }
		    CREATE_BINARY_OP((yyval.node), F_DIVIDE, result_type, (yyvsp[-2].node), (yyvsp[0].node));
		    break;
		default:
		    CREATE_BINARY_OP((yyval.node), F_DIVIDE, result_type, (yyvsp[-2].node), (yyvsp[0].node));
		}
	    }
#line 4509 "grammar.tab.c"
    break;

  case 159: /* expr0: cast expr0  */
#line 2325 "grammar.y"
            {
#line 2284 "grammar.y.pre"
		(yyval.node) = (yyvsp[0].node);
		(yyval.node)->type = (yyvsp[-1].number);

		if (exact_types &&
		    (yyvsp[0].node)->type != (yyvsp[-1].number) &&
		    (yyvsp[0].node)->type != TYPE_ANY && 
		    (yyvsp[0].node)->type != TYPE_UNKNOWN &&
		    (yyvsp[-1].number) != TYPE_VOID) {
		    char buf[256];
		    char *end = EndOf(buf);
		    char *p;
		    
		    p = strput(buf, end, "Cannot cast ");
		    p = get_type_name(p, end, (yyvsp[0].node)->type);
		    p = strput(p, end, "to ");
		    p = get_type_name(p, end, (yyvsp[-1].number));
		    yyerror(buf);
		}
	    }
#line 4535 "grammar.tab.c"
    break;

  case 160: /* expr0: L_INC lvalue  */
#line 2347 "grammar.y"
            {
#line 2305 "grammar.y.pre"
		CREATE_UNARY_OP((yyval.node), F_PRE_INC, 0, (yyvsp[0].node));
                if (exact_types){
                    switch((yyvsp[0].node)->type){
                        case TYPE_NUMBER:
                        case TYPE_ANY:
                        case TYPE_REAL:
                        {
                            (yyval.node)->type = (yyvsp[0].node)->type;
                            break;
                        }

                        default:
                        {
                            (yyval.node)->type = TYPE_ANY;
                            type_error("Bad argument 1 to ++x", (yyvsp[0].node)->type);
                        }
                    }
                } else (yyval.node)->type = TYPE_ANY;
	    }
#line 4561 "grammar.tab.c"
    break;

  case 161: /* expr0: L_DEC lvalue  */
#line 2369 "grammar.y"
            {
#line 2326 "grammar.y.pre"
		CREATE_UNARY_OP((yyval.node), F_PRE_DEC, 0, (yyvsp[0].node));
                if (exact_types){
                    switch((yyvsp[0].node)->type){
                        case TYPE_NUMBER:
                        case TYPE_ANY:
                        case TYPE_REAL:
                        {
                            (yyval.node)->type = (yyvsp[0].node)->type;
                            break;
                        }

                        default:
                        {
                            (yyval.node)->type = TYPE_ANY;
                            type_error("Bad argument 1 to --x", (yyvsp[0].node)->type);
                        }
                    }
                } else (yyval.node)->type = TYPE_ANY;

	    }
#line 4588 "grammar.tab.c"
    break;

  case 162: /* expr0: L_NOT expr0  */
#line 2392 "grammar.y"
            {
#line 2348 "grammar.y.pre"
		if ((yyvsp[0].node)->kind == NODE_NUMBER) {
		    (yyval.node) = (yyvsp[0].node);
		    (yyval.node)->v.number = !((yyval.node)->v.number);
		} else {
		    CREATE_UNARY_OP((yyval.node), F_NOT, TYPE_NUMBER, (yyvsp[0].node));
		}
	    }
#line 4602 "grammar.tab.c"
    break;

  case 163: /* expr0: '~' expr0  */
#line 2402 "grammar.y"
            {
#line 2357 "grammar.y.pre"
		if (exact_types && !IS_TYPE((yyvsp[0].node)->type, TYPE_NUMBER))
		    type_error("Bad argument to ~", (yyvsp[0].node)->type);
		if ((yyvsp[0].node)->kind == NODE_NUMBER) {
		    (yyval.node) = (yyvsp[0].node);
		    (yyval.node)->v.number = ~(yyval.node)->v.number;
		} else {
		    CREATE_UNARY_OP((yyval.node), F_COMPL, TYPE_NUMBER, (yyvsp[0].node));
		}
	    }
#line 4618 "grammar.tab.c"
    break;

  case 164: /* expr0: '-' expr0  */
#line 2414 "grammar.y"
            {
#line 2368 "grammar.y.pre"
		int result_type;
                if (exact_types){
		    int t = (yyvsp[0].node)->type;
		    if (!COMP_TYPE(t, TYPE_NUMBER)){
			type_error("Bad argument to unary '-'", t);
			result_type = TYPE_ANY;
		    } else result_type = t;
		} else result_type = TYPE_ANY;

		switch ((yyvsp[0].node)->kind) {
		case NODE_NUMBER:
		    (yyval.node) = (yyvsp[0].node);
		    (yyval.node)->v.number = -(yyval.node)->v.number;
		    break;
		case NODE_REAL:
		    (yyval.node) = (yyvsp[0].node);
		    (yyval.node)->v.real = -(yyval.node)->v.real;
		    break;
		default:
		    CREATE_UNARY_OP((yyval.node), F_NEGATE, result_type, (yyvsp[0].node));
		}
	    }
#line 4647 "grammar.tab.c"
    break;

  case 165: /* expr0: lvalue L_INC  */
#line 2439 "grammar.y"
            {
#line 2392 "grammar.y.pre"
		CREATE_UNARY_OP((yyval.node), F_POST_INC, 0, (yyvsp[-1].node));
		(yyval.node)->v.number = F_POST_INC;
                if (exact_types){
                    switch((yyvsp[-1].node)->type){
                        case TYPE_NUMBER:
		    case TYPE_ANY:
                        case TYPE_REAL:
                        {
                            (yyval.node)->type = (yyvsp[-1].node)->type;
                            break;
                        }

                        default:
                        {
                            (yyval.node)->type = TYPE_ANY;
                            type_error("Bad argument 1 to x++", (yyvsp[-1].node)->type);
                        }
                    }
                } else (yyval.node)->type = TYPE_ANY;
	    }
#line 4674 "grammar.tab.c"
    break;

  case 166: /* expr0: lvalue L_DEC  */
#line 2462 "grammar.y"
            {
#line 2414 "grammar.y.pre"
		CREATE_UNARY_OP((yyval.node), F_POST_DEC, 0, (yyvsp[-1].node));
                if (exact_types){
                    switch((yyvsp[-1].node)->type){
		    case TYPE_NUMBER:
		    case TYPE_ANY:
		    case TYPE_REAL:
		    {
			(yyval.node)->type = (yyvsp[-1].node)->type;
			break;
		    }

		    default:
		    {
			(yyval.node)->type = TYPE_ANY;
			type_error("Bad argument 1 to x--", (yyvsp[-1].node)->type);
		    }
                    }
                } else (yyval.node)->type = TYPE_ANY;
	    }
#line 4700 "grammar.tab.c"
    break;

  case 173: /* return: L_RETURN ';'  */
#line 2493 "grammar.y"
            {
#line 2444 "grammar.y.pre"
		if (exact_types && !IS_TYPE(exact_types, TYPE_VOID))
		    yywarn("Non-void functions must return a value.");
		CREATE_RETURN((yyval.node), 0);
	    }
#line 4711 "grammar.tab.c"
    break;

  case 174: /* return: L_RETURN comma_expr ';'  */
#line 2500 "grammar.y"
            {
#line 2450 "grammar.y.pre"
		if (exact_types && !compatible_types((yyvsp[-1].node)->type, exact_types)) {
		    char buf[256];
		    char *end = EndOf(buf);
		    char *p;
		    
		    p = strput(buf, end, "Type of returned value doesn't match function return type ");
		    p = get_two_types(p, end, (yyvsp[-1].node)->type, exact_types);
		    yyerror(buf);
		}
		if (IS_NODE((yyvsp[-1].node), NODE_NUMBER, 0)) {
		    CREATE_RETURN((yyval.node), 0);
		} else {
		    CREATE_RETURN((yyval.node), (yyvsp[-1].node));
		}
	    }
#line 4733 "grammar.tab.c"
    break;

  case 175: /* expr_list: %empty  */
#line 2521 "grammar.y"
            {
#line 2470 "grammar.y.pre"
		CREATE_EXPR_LIST((yyval.node), 0);
	    }
#line 4742 "grammar.tab.c"
    break;

  case 176: /* expr_list: expr_list2  */
#line 2526 "grammar.y"
            {
#line 2474 "grammar.y.pre"
		CREATE_EXPR_LIST((yyval.node), (yyvsp[0].node));
	    }
#line 4751 "grammar.tab.c"
    break;

  case 177: /* expr_list: expr_list2 ','  */
#line 2531 "grammar.y"
            {
#line 2478 "grammar.y.pre"
		CREATE_EXPR_LIST((yyval.node), (yyvsp[-1].node));
	    }
#line 4760 "grammar.tab.c"
    break;

  case 178: /* expr_list_node: expr0  */
#line 2539 "grammar.y"
            {
#line 2485 "grammar.y.pre"
		CREATE_EXPR_NODE((yyval.node), (yyvsp[0].node), 0);
	    }
#line 4769 "grammar.tab.c"
    break;

  case 179: /* expr_list_node: expr0 L_DOT_DOT_DOT  */
#line 2544 "grammar.y"
            {
#line 2489 "grammar.y.pre"
		CREATE_EXPR_NODE((yyval.node), (yyvsp[-1].node), 1);
	    }
#line 4778 "grammar.tab.c"
    break;

  case 180: /* expr_list2: expr_list_node  */
#line 2552 "grammar.y"
            {
#line 2496 "grammar.y.pre"
		(yyvsp[0].node)->kind = 1;

		(yyval.node) = (yyvsp[0].node);
	    }
#line 4789 "grammar.tab.c"
    break;

  case 181: /* expr_list2: expr_list2 ',' expr_list_node  */
#line 2559 "grammar.y"
            {
#line 2502 "grammar.y.pre"
		(yyvsp[0].node)->kind = 0;

		(yyval.node) = (yyvsp[-2].node);
		(yyval.node)->kind++;
		(yyval.node)->l.expr->r.expr = (yyvsp[0].node);
		(yyval.node)->l.expr = (yyvsp[0].node);
	    }
#line 4803 "grammar.tab.c"
    break;

  case 182: /* expr_list3: %empty  */
#line 2572 "grammar.y"
            {
#line 2514 "grammar.y.pre"
		/* this is a dummy node */
		CREATE_EXPR_LIST((yyval.node), 0);
	    }
#line 4813 "grammar.tab.c"
    break;

  case 183: /* expr_list3: expr_list4  */
#line 2578 "grammar.y"
            {
#line 2519 "grammar.y.pre"
		CREATE_EXPR_LIST((yyval.node), (yyvsp[0].node));
	    }
#line 4822 "grammar.tab.c"
    break;

  case 184: /* expr_list3: expr_list4 ','  */
#line 2583 "grammar.y"
            {
#line 2523 "grammar.y.pre"
		CREATE_EXPR_LIST((yyval.node), (yyvsp[-1].node));
	    }
#line 4831 "grammar.tab.c"
    break;

  case 185: /* expr_list4: assoc_pair  */
#line 2591 "grammar.y"
            {
#line 2530 "grammar.y.pre"
		(yyval.node) = new_node_no_line();
		(yyval.node)->kind = 2;
		(yyval.node)->v.expr = (yyvsp[0].node);
		(yyval.node)->r.expr = 0;
		(yyval.node)->type = 0;
		/* we keep track of the end of the chain in the left nodes */
		(yyval.node)->l.expr = (yyval.node);
            }
#line 4846 "grammar.tab.c"
    break;

  case 186: /* expr_list4: expr_list4 ',' assoc_pair  */
#line 2602 "grammar.y"
            {
#line 2540 "grammar.y.pre"
		parse_node_t *expr;

		expr = new_node_no_line();
		expr->kind = 0;
		expr->v.expr = (yyvsp[0].node);
		expr->r.expr = 0;
		expr->type = 0;
		
		(yyvsp[-2].node)->l.expr->r.expr = expr;
		(yyvsp[-2].node)->l.expr = expr;
		(yyvsp[-2].node)->kind += 2;
		(yyval.node) = (yyvsp[-2].node);
	    }
#line 4866 "grammar.tab.c"
    break;

  case 187: /* assoc_pair: expr0 ':' expr0  */
#line 2621 "grammar.y"
            {
#line 2558 "grammar.y.pre"
		CREATE_TWO_VALUES((yyval.node), 0, (yyvsp[-2].node), (yyvsp[0].node));
            }
#line 4875 "grammar.tab.c"
    break;

  case 188: /* lvalue: expr4  */
#line 2629 "grammar.y"
            {
#line 2565 "grammar.y.pre"
#define LV_ILLEGAL 1
#define LV_RANGE 2
#define LV_INDEX 4
                /* Restrictive lvalues, but I think they make more sense :) */
                (yyval.node) = (yyvsp[0].node);
		if((yyval.node)->kind == NODE_BINARY_OP && (yyval.node)->v.number == F_TYPE_CHECK) 
		    (yyval.node) = (yyval.node)->l.expr;
                switch((yyval.node)->kind) {
		default:
		    yyerror("Illegal lvalue");
		    break;
		case NODE_PARAMETER:
		    (yyval.node)->kind = NODE_PARAMETER_LVALUE;
		    break;
		case NODE_TERNARY_OP:
		    (yyval.node)->v.number = (yyval.node)->r.expr->v.number;
		case NODE_OPCODE_1:
		case NODE_UNARY_OP_1:
		case NODE_BINARY_OP:
		    if ((yyval.node)->v.number >= F_LOCAL && (yyval.node)->v.number <= F_MEMBER)
			(yyval.node)->v.number++; /* make it an lvalue */
		    else if ((yyval.node)->v.number >= F_INDEX 
			     && (yyval.node)->v.number <= F_RE_RANGE) {
                        parse_node_t *node = (yyval.node);
                        int flag = 0;
                        do {
                            switch(node->kind) {
			    case NODE_PARAMETER:
				node->kind = NODE_PARAMETER_LVALUE;
				flag |= LV_ILLEGAL;
				break;
			    case NODE_TERNARY_OP:
				node->v.number = node->r.expr->v.number;
			    case NODE_OPCODE_1:
			    case NODE_UNARY_OP_1:
			    case NODE_BINARY_OP:
			        if(node->kind == NODE_BINARY_OP && 
				   node->v.number == F_TYPE_CHECK) {
				    node = node->l.expr;
				    continue;
				}

				if (node->v.number >= F_LOCAL 
				    && node->v.number <= F_MEMBER) {
				    node->v.number++;
				    flag |= LV_ILLEGAL;
				    break;
				} else if (node->v.number == F_INDEX ||
					 node->v.number == F_RINDEX) {
				    node->v.number++;
				    flag |= LV_INDEX;
				    break;
				} else if (node->v.number >= F_ADD_EQ
					   && node->v.number <= F_ASSIGN) {
				    if (!(flag & LV_INDEX)) {
					yyerror("Illegal lvalue, a possible lvalue is (x <assign> y)[a]");
				    }
				    if (node->r.expr->kind == NODE_BINARY_OP||
					node->r.expr->kind == NODE_TERNARY_OP){
					if (node->r.expr->v.number >= F_NN_RANGE_LVALUE && node->r.expr->v.number <= F_NR_RANGE_LVALUE)
					    yyerror("Illegal to have (x[a..b] <assign> y) to be the beginning of an lvalue");
				    }
				    flag = LV_ILLEGAL;
				    break;
				} else if (node->v.number >= F_NN_RANGE
					 && node->v.number <= F_RE_RANGE) {
				    if (flag & LV_RANGE) {
					yyerror("Can't do range lvalue of range lvalue.");
					flag |= LV_ILLEGAL;
					break;
				    }
                                    if (flag & LV_INDEX){
					yyerror("Can't do indexed lvalue of range lvalue.");
					flag |= LV_ILLEGAL;
					break;
				    }
				    if (node->v.number == F_NE_RANGE) {
					/* x[foo..] -> x[foo..<1] */
					parse_node_t *rchild = node->r.expr;
					node->kind = NODE_TERNARY_OP;
					CREATE_BINARY_OP(node->r.expr,
							 F_NR_RANGE_LVALUE,
							 0, 0, rchild);
					CREATE_NUMBER(node->r.expr->l.expr, 1);
				    } else if (node->v.number == F_RE_RANGE) {
					/* x[<foo..] -> x[<foo..<1] */
					parse_node_t *rchild = node->r.expr;
					node->kind = NODE_TERNARY_OP;
					CREATE_BINARY_OP(node->r.expr,
							 F_RR_RANGE_LVALUE,
							 0, 0, rchild);
					CREATE_NUMBER(node->r.expr->l.expr, 1);
				    } else
					node->r.expr->v.number++;
				    flag |= LV_RANGE;
				    node = node->r.expr->r.expr;
				    continue;
				}
			    default:
				yyerror("Illegal lvalue");
				flag = LV_ILLEGAL;
				break;
			    }   
                            if ((flag & LV_ILLEGAL) || !(node = node->r.expr)) break;
                        } while (1);
                        break;
		    } else 
			yyerror("Illegal lvalue");
		    break;
                }
            }
#line 4993 "grammar.tab.c"
    break;

  case 190: /* l_new_function_open: L_FUNCTION_OPEN efun_override  */
#line 2746 "grammar.y"
            {
#line 2681 "grammar.y.pre"
		(yyval.number) = ((yyvsp[0].number) << 8) | FP_EFUN;
	    }
#line 5002 "grammar.tab.c"
    break;

  case 192: /* expr4: L_DEFINED_NAME  */
#line 2756 "grammar.y"
            {
#line 2713 "grammar.y.pre"
              int i;
              if ((i = (yyvsp[0].ihe)->dn.local_num) != -1) {
		  type_of_locals_ptr[i] &= ~LOCAL_MOD_UNUSED;
		  if (type_of_locals_ptr[i] & LOCAL_MOD_REF)
		      CREATE_OPCODE_1((yyval.node), F_REF, type_of_locals_ptr[i] & ~LOCAL_MOD_REF,i & 0xff);
		  else
		      CREATE_OPCODE_1((yyval.node), F_LOCAL, type_of_locals_ptr[i], i & 0xff);
		  if (current_function_context)
		      current_function_context->num_locals++;
              } else
		  if ((i = (yyvsp[0].ihe)->dn.global_num) != -1) {
		      if (current_function_context)
			  current_function_context->bindable = FP_NOT_BINDABLE;
                          CREATE_OPCODE_1((yyval.node), F_GLOBAL,
				      VAR_TEMP(i)->type & ~DECL_MODS, i);
		      if (VAR_TEMP(i)->type & DECL_HIDDEN) {
			  char buf[256];
			  char *end = EndOf(buf);
			  char *p;

			  p = strput(buf, end, "Illegal to use private variable '");
			  p = strput(p, end, (yyvsp[0].ihe)->name);
			  p = strput(p, end, "'");
			  yyerror(buf);
		      }
		  } else {
		      char buf[256];
		      char *end = EndOf(buf);
		      char *p;
		      
		      p = strput(buf, end, "Undefined variable '");
		      p = strput(p, end, (yyvsp[0].ihe)->name);
		      p = strput(p, end, "'");
		      if (current_number_of_locals < CFG_MAX_LOCAL_VARIABLES) {
			  add_local_name((yyvsp[0].ihe)->name, TYPE_ANY);
		      }
		      CREATE_ERROR((yyval.node));
		      yyerror(buf);
		  }
	    }
#line 5049 "grammar.tab.c"
    break;

  case 193: /* expr4: L_IDENTIFIER  */
#line 2799 "grammar.y"
            {
#line 2755 "grammar.y.pre"
		char buf[256];
		char *end = EndOf(buf);
		char *p;
		
		p = strput(buf, end, "Undefined variable '");
		p = strput(p, end, (yyvsp[0].string));
		p = strput(p, end, "'");
                if (current_number_of_locals < CFG_MAX_LOCAL_VARIABLES) {
                    add_local_name((yyvsp[0].string), TYPE_ANY);
                }
                CREATE_ERROR((yyval.node));
                yyerror(buf);
                scratch_free((yyvsp[0].string));
            }
#line 5070 "grammar.tab.c"
    break;

  case 194: /* expr4: L_PARAMETER  */
#line 2816 "grammar.y"
            {
#line 2771 "grammar.y.pre"
		CREATE_PARAMETER((yyval.node), TYPE_ANY, (yyvsp[0].number));
            }
#line 5079 "grammar.tab.c"
    break;

  case 195: /* @11: %empty  */
#line 2821 "grammar.y"
            {
#line 2775 "grammar.y.pre"
		(yyval.contextp) = current_function_context;
		/* already flagged as an error */
		if (current_function_context)
		    current_function_context = current_function_context->parent;
            }
#line 5091 "grammar.tab.c"
    break;

  case 196: /* expr4: '$' '(' @11 comma_expr ')'  */
#line 2829 "grammar.y"
            {
#line 2782 "grammar.y.pre"
		parse_node_t *node;

		current_function_context = (yyvsp[-2].contextp);

		if (!current_function_context || current_function_context->num_parameters == -2) {
		    /* This was illegal, and error'ed when the '$' token
		     * was returned.
		     */
		    CREATE_ERROR((yyval.node));
		} else {
		    CREATE_OPCODE_1((yyval.node), F_LOCAL, (yyvsp[-1].node)->type,
				    current_function_context->values_list->kind++);

		    node = new_node_no_line();
		    node->type = 0;
		    current_function_context->values_list->l.expr->r.expr = node;
		    current_function_context->values_list->l.expr = node;
		    node->r.expr = 0;
		    node->v.expr = (yyvsp[-1].node);
		}
	    }
#line 5119 "grammar.tab.c"
    break;

  case 197: /* expr4: expr4 L_ARROW identifier  */
#line 2853 "grammar.y"
            {
#line 2805 "grammar.y.pre"
		if ((yyvsp[-2].node)->type == TYPE_ANY) {
		    int cmi;
		    unsigned char tp;
		    
		    if ((cmi = lookup_any_class_member((yyvsp[0].string), &tp)) != -1) {
			CREATE_UNARY_OP_1((yyval.node), F_MEMBER, tp, (yyvsp[-2].node), 0);
			(yyval.node)->l.number = cmi;
		    } else {
			CREATE_ERROR((yyval.node));
		    }
		} else if (!IS_CLASS((yyvsp[-2].node)->type)) {
		    yyerror("Left argument of -> is not a class");
		    CREATE_ERROR((yyval.node));
		} else {
		    CREATE_UNARY_OP_1((yyval.node), F_MEMBER, 0, (yyvsp[-2].node), 0);
		    (yyval.node)->l.number = lookup_class_member(CLASS_IDX((yyvsp[-2].node)->type),
						       (yyvsp[0].string),
						       &((yyval.node)->type));
		}
		    
		scratch_free((yyvsp[0].string));
            }
#line 5148 "grammar.tab.c"
    break;

  case 198: /* expr4: expr4 '[' comma_expr L_RANGE comma_expr ']'  */
#line 2878 "grammar.y"
            {
#line 2829 "grammar.y.pre"
                if ((yyvsp[-5].node)->type != TYPE_MAPPING && 
		    (yyvsp[-1].node)->kind == NODE_NUMBER && (yyvsp[-1].node)->v.number < 0)
		    yywarn("A negative constant as the second element of arr[x..y] no longer means indexing from the end.  Use arr[x..<y]");
                (yyval.node) = make_range_node(F_NN_RANGE, (yyvsp[-5].node), (yyvsp[-3].node), (yyvsp[-1].node));
            }
#line 5160 "grammar.tab.c"
    break;

  case 199: /* expr4: expr4 '[' '<' comma_expr L_RANGE comma_expr ']'  */
#line 2886 "grammar.y"
            {
#line 2840 "grammar.y.pre"
                (yyval.node) = make_range_node(F_RN_RANGE, (yyvsp[-6].node), (yyvsp[-3].node), (yyvsp[-1].node));
            }
#line 5169 "grammar.tab.c"
    break;

  case 200: /* expr4: expr4 '[' '<' comma_expr L_RANGE '<' comma_expr ']'  */
#line 2891 "grammar.y"
            {
#line 2844 "grammar.y.pre"
		if ((yyvsp[-1].node)->kind == NODE_NUMBER && (yyvsp[-1].node)->v.number <= 1)
		    (yyval.node) = make_range_node(F_RE_RANGE, (yyvsp[-7].node), (yyvsp[-4].node), 0);
		else
		    (yyval.node) = make_range_node(F_RR_RANGE, (yyvsp[-7].node), (yyvsp[-4].node), (yyvsp[-1].node));
            }
#line 5181 "grammar.tab.c"
    break;

  case 201: /* expr4: expr4 '[' comma_expr L_RANGE '<' comma_expr ']'  */
#line 2899 "grammar.y"
            {
#line 2851 "grammar.y.pre"
		if ((yyvsp[-1].node)->kind == NODE_NUMBER && (yyvsp[-1].node)->v.number <= 1)
		    (yyval.node) = make_range_node(F_NE_RANGE, (yyvsp[-6].node), (yyvsp[-4].node), 0);
		else
		    (yyval.node) = make_range_node(F_NR_RANGE, (yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-1].node));
            }
#line 5193 "grammar.tab.c"
    break;

  case 202: /* expr4: expr4 '[' comma_expr L_RANGE ']'  */
#line 2907 "grammar.y"
            {
#line 2858 "grammar.y.pre"
                (yyval.node) = make_range_node(F_NE_RANGE, (yyvsp[-4].node), (yyvsp[-2].node), 0);
            }
#line 5202 "grammar.tab.c"
    break;

  case 203: /* expr4: expr4 '[' '<' comma_expr L_RANGE ']'  */
#line 2912 "grammar.y"
            {
#line 2862 "grammar.y.pre"
                (yyval.node) = make_range_node(F_RE_RANGE, (yyvsp[-5].node), (yyvsp[-2].node), 0);
            }
#line 5211 "grammar.tab.c"
    break;

  case 204: /* expr4: expr4 '[' '<' comma_expr ']'  */
#line 2917 "grammar.y"
            {
#line 2866 "grammar.y.pre"
                if (IS_NODE((yyvsp[-4].node), NODE_CALL, F_AGGREGATE)
		    && (yyvsp[-1].node)->kind == NODE_NUMBER) {
                    int i = (yyvsp[-1].node)->v.number;
                    if (i < 1 || i > (yyvsp[-4].node)->l.number)
                        yyerror("Illegal index to array constant.");
                    else {
                        parse_node_t *node = (yyvsp[-4].node)->r.expr;
                        i = (yyvsp[-4].node)->l.number - i;
                        while (i--)
                            node = node->r.expr;
                        (yyval.node) = node->v.expr;
                        break;
                    }
                }
		CREATE_BINARY_OP((yyval.node), F_RINDEX, 0, (yyvsp[-1].node), (yyvsp[-4].node));
                if (exact_types) {
		    switch((yyvsp[-4].node)->type) {
		    case TYPE_MAPPING:
			yyerror("Illegal index for mapping.");
		    case TYPE_ANY:
			(yyval.node)->type = TYPE_ANY;
			break;
		    case TYPE_STRING:
		    case TYPE_BUFFER:
			(yyval.node)->type = TYPE_NUMBER;
			if (!IS_TYPE((yyvsp[-1].node)->type,TYPE_NUMBER))
			    type_error("Bad type of index", (yyvsp[-1].node)->type);
			break;
			
		    default:
			if ((yyvsp[-4].node)->type & TYPE_MOD_ARRAY) {
			    (yyval.node)->type = (yyvsp[-4].node)->type & ~TYPE_MOD_ARRAY;
			    if ((yyval.node)->type != TYPE_ANY)
			        (yyval.node) = add_type_check((yyval.node), (yyval.node)->type); 
			    if (!IS_TYPE((yyvsp[-1].node)->type,TYPE_NUMBER))
				type_error("Bad type of index", (yyvsp[-1].node)->type);
			} else {
			    type_error("Value indexed has a bad type ", (yyvsp[-4].node)->type);
			    (yyval.node)->type = TYPE_ANY;
			}
		    }
		} else (yyval.node)->type = TYPE_ANY;
            }
#line 5261 "grammar.tab.c"
    break;

  case 205: /* expr4: expr4 '[' comma_expr ']'  */
#line 2963 "grammar.y"
            {
#line 2911 "grammar.y.pre"
		/* Something stupid like ({ 1, 2, 3 })[1]; we take the
		 * time to optimize this because people who don't understand
		 * the preprocessor often write things like:
		 *
		 * #define MY_ARRAY ({ "foo", "bar", "bazz" })
		 * ...
		 * ... MY_ARRAY[1] ...
		 *
		 * which of course expands to the above.
		 */
                if (IS_NODE((yyvsp[-3].node), NODE_CALL, F_AGGREGATE) && (yyvsp[-1].node)->kind == NODE_NUMBER) {
                    int i = (yyvsp[-1].node)->v.number;
                    if (i < 0 || i >= (yyvsp[-3].node)->l.number)
                        yyerror("Illegal index to array constant.");
                    else {
                        parse_node_t *node = (yyvsp[-3].node)->r.expr;
                        while (i--)
                            node = node->r.expr;
                        (yyval.node) = node->v.expr;
                        break;
                    }
                }
                if ((yyvsp[-1].node)->kind == NODE_NUMBER && (yyvsp[-1].node)->v.number < 0)
		    yywarn("A negative constant in arr[x] no longer means indexing from the end.  Use arr[<x]");
                CREATE_BINARY_OP((yyval.node), F_INDEX, 0, (yyvsp[-1].node), (yyvsp[-3].node));
                if (exact_types) {
		    switch((yyvsp[-3].node)->type) {
		    case TYPE_MAPPING:
		    case TYPE_ANY:
			(yyval.node)->type = TYPE_ANY;
			break;
		    case TYPE_STRING:
		    case TYPE_BUFFER:
			(yyval.node)->type = TYPE_NUMBER;
			if (!IS_TYPE((yyvsp[-1].node)->type,TYPE_NUMBER))
			    type_error("Bad type of index", (yyvsp[-1].node)->type);
			break;
			
		    default:
			if ((yyvsp[-3].node)->type & TYPE_MOD_ARRAY) {
			    (yyval.node)->type = (yyvsp[-3].node)->type & ~TYPE_MOD_ARRAY;
			    if((yyval.node)->type != TYPE_ANY)
			        (yyval.node) = add_type_check((yyval.node), (yyval.node)->type);
			    if (!IS_TYPE((yyvsp[-1].node)->type,TYPE_NUMBER))
				type_error("Bad type of index", (yyvsp[-1].node)->type);
			} else {
			    type_error("Value indexed has a bad type ", (yyvsp[-3].node)->type);
			    (yyval.node)->type = TYPE_ANY;
			}
                    }
                } else (yyval.node)->type = TYPE_ANY;
            }
#line 5320 "grammar.tab.c"
    break;

  case 207: /* expr4: '(' comma_expr ')'  */
#line 3019 "grammar.y"
            {
#line 2968 "grammar.y.pre"
		(yyval.node) = (yyvsp[-1].node);
	    }
#line 5329 "grammar.tab.c"
    break;

  case 209: /* @12: %empty  */
#line 3025 "grammar.y"
            {
#line 2976 "grammar.y.pre"
	        if ((yyvsp[0].number) != TYPE_FUNCTION) yyerror("Reserved type name unexpected.");
		(yyval.func_block).num_local = current_number_of_locals;
		(yyval.func_block).max_num_locals = max_num_locals;
		(yyval.func_block).context = context;
		(yyval.func_block).save_current_type = current_type;
		(yyval.func_block).save_exact_types = exact_types;
	        if (type_of_locals_ptr + max_num_locals + CFG_MAX_LOCAL_VARIABLES >= &type_of_locals[type_of_locals_size])
		    reallocate_locals();
		deactivate_current_locals();
		locals_ptr += current_number_of_locals;
		type_of_locals_ptr += max_num_locals;
		max_num_locals = current_number_of_locals = 0;
		push_function_context();
		current_function_context->num_parameters = -1;
		exact_types = TYPE_ANY;
		context = 0;
            }
#line 5353 "grammar.tab.c"
    break;

  case 210: /* expr4: L_BASIC_TYPE @12 '(' argument ')' block  */
#line 3045 "grammar.y"
            {
#line 2995 "grammar.y.pre"
		if ((yyvsp[-2].argument).flags & ARG_IS_VARARGS) {
		    yyerror("Anonymous varargs functions aren't implemented");
		}
		if (!(yyvsp[0].decl).node) {
		    CREATE_RETURN((yyvsp[0].decl).node, 0);
		} else if ((yyvsp[0].decl).node->kind != NODE_RETURN &&
			   ((yyvsp[0].decl).node->kind != NODE_TWO_VALUES || (yyvsp[0].decl).node->r.expr->kind != NODE_RETURN)) {
		    parse_node_t *replacement;
		    CREATE_STATEMENTS(replacement, (yyvsp[0].decl).node, 0);
		    CREATE_RETURN(replacement->r.expr, 0);
		    (yyvsp[0].decl).node = replacement;
		}
		
		(yyval.node) = new_node();
		(yyval.node)->kind = NODE_ANON_FUNC;
		(yyval.node)->type = TYPE_FUNCTION;
		(yyval.node)->l.number = (max_num_locals - (yyvsp[-2].argument).num_arg);
		(yyval.node)->r.expr = (yyvsp[0].decl).node;
		(yyval.node)->v.number = (yyvsp[-2].argument).num_arg;
		if (current_function_context->bindable)
		    (yyval.node)->v.number |= 0x10000;
		free_all_local_names(1);
		
		current_number_of_locals = (yyvsp[-4].func_block).num_local;
		max_num_locals = (yyvsp[-4].func_block).max_num_locals;
		context = (yyvsp[-4].func_block).context;
		current_type = (yyvsp[-4].func_block).save_current_type;
		exact_types = (yyvsp[-4].func_block).save_exact_types;
		pop_function_context();
		
		locals_ptr -= current_number_of_locals;
		type_of_locals_ptr -= max_num_locals;
		reactivate_current_locals();
	    }
#line 5394 "grammar.tab.c"
    break;

  case 211: /* expr4: l_new_function_open ':' ')'  */
#line 3082 "grammar.y"
            {
#line 3035 "grammar.y.pre"
#ifdef WOMBLES
	        if(*(outp-2) != ':')
		  yyerror("End of functional not found");
#endif
		(yyval.node) = new_node();
		(yyval.node)->kind = NODE_FUNCTION_CONSTRUCTOR;
		(yyval.node)->type = TYPE_FUNCTION;
		(yyval.node)->r.expr = 0;
		switch ((yyvsp[-2].number) & 0xff) {
		case FP_L_VAR:
		    yyerror("Illegal to use local variable in a functional.");
		    CREATE_NUMBER((yyval.node)->l.expr, 0);
		    (yyval.node)->l.expr->r.expr = 0;
		    (yyval.node)->l.expr->l.expr = 0;
		    (yyval.node)->v.number = FP_FUNCTIONAL;
		    break;
		case FP_G_VAR:
		    CREATE_OPCODE_1((yyval.node)->l.expr, F_GLOBAL, 0, (yyvsp[-2].number) >> 8);
		    (yyval.node)->v.number = FP_FUNCTIONAL | FP_NOT_BINDABLE;
		    if (VAR_TEMP((yyval.node)->l.expr->l.number)->type & DECL_HIDDEN) {
			char buf[256];
			char *end = EndOf(buf);
			char *p;
			
			p = strput(buf, end, "Illegal to use private variable '");
			p = strput(p, end, VAR_TEMP((yyval.node)->l.expr->l.number)->name);
			p = strput(p, end, "'");
			yyerror(buf);
		    }
		    break;
		default:
		    (yyval.node)->v.number = (yyvsp[-2].number);
		    break;
		}
	    }
#line 5436 "grammar.tab.c"
    break;

  case 212: /* expr4: l_new_function_open ',' expr_list2 ':' ')'  */
#line 3120 "grammar.y"
            {
#line 3072 "grammar.y.pre"
#ifdef WOMBLES
	        if(*(outp-2) != ':')
		  yyerror("End of functional not found");
#endif
		(yyval.node) = new_node();
		(yyval.node)->kind = NODE_FUNCTION_CONSTRUCTOR;
		(yyval.node)->type = TYPE_FUNCTION;
		(yyval.node)->v.number = (yyvsp[-4].number);
		(yyval.node)->r.expr = (yyvsp[-2].node);
		
		switch ((yyvsp[-4].number) & 0xff) {
		case FP_EFUN: {
		    int *argp;
		    int f = (yyvsp[-4].number) >>8;
		    int num = (yyvsp[-2].node)->kind;
		    int max_arg = predefs[f].max_args;
		    if(f!=-1){
		      if (num > max_arg && max_arg != -1) {
			parse_node_t *pn = (yyvsp[-2].node);
			
			while (pn) {
			    if (pn->type & 1) break;
			    pn = pn->r.expr;
			}
			
			if (!pn) {
			    char bff[256];
			    char *end = EndOf(bff);
			    char *p;
			    
			    p = strput(bff, end, "Too many arguments to ");
			    p = strput(p, end, predefs[f].word);
			    yyerror(bff);
			}
		      } else if (max_arg != -1 && exact_types) {
			/*
			 * Now check all types of arguments to efuns.
			 */
			int i, argn, tmp;
			parse_node_t *enode = (yyvsp[-2].node);
			argp = &efun_arg_types[predefs[f].arg_index];
			
			for (argn = 0; argn < num; argn++) {
			    if (enode->type & 1) break;
			    
			    tmp = enode->v.expr->type;
			    for (i=0; !compatible_types(tmp, argp[i])
				 && argp[i] != 0; i++)
				;
			    if (argp[i] == 0) {
				char buf[256];
				char *end = EndOf(buf);
				char *p;

				p = strput(buf, end, "Bad argument ");
				p = strput_int(p, end, argn+1);
				p = strput(p, end, " to efun ");
				p = strput(p, end, predefs[f].word);
				p = strput(p, end, "()");
				yyerror(buf);
			    } else {
				/* this little section necessary b/c in the
				   case float | int we dont want to do
				   promoting. */
				if (tmp == TYPE_NUMBER && argp[i] == TYPE_REAL) {
				    for (i++; argp[i] && argp[i] != TYPE_NUMBER; i++)
					;
				    if (!argp[i])
					enode->v.expr = promote_to_float(enode->v.expr);
				}
				if (tmp == TYPE_REAL && argp[i] == TYPE_NUMBER) {
				    for (i++; argp[i] && argp[i] != TYPE_REAL; i++)
					;
				    if (!argp[i])
					enode->v.expr = promote_to_int(enode->v.expr);
				}
			    }
			    while (argp[i] != 0)
				i++;
			    argp += i + 1;
			    enode = enode->r.expr;
			}
		      }
		    }
		    break;
		}
		case FP_L_VAR:
		case FP_G_VAR:
		    yyerror("Can't give parameters to functional.");
		    break;
		}
	    }
#line 5535 "grammar.tab.c"
    break;

  case 213: /* expr4: L_FUNCTION_OPEN comma_expr ':' ')'  */
#line 3215 "grammar.y"
             {
#line 3166 "grammar.y.pre"
#ifdef WOMBLES
	         if(*(outp-2) != ':')
		   yyerror("End of functional not found");
#endif
		 if (current_function_context->num_locals)
		     yyerror("Illegal to use local variable in functional.");
		 if (current_function_context->values_list->r.expr)
		     current_function_context->values_list->r.expr->kind = current_function_context->values_list->kind;
		 
		 (yyval.node) = new_node();
		 (yyval.node)->kind = NODE_FUNCTION_CONSTRUCTOR;
		 (yyval.node)->type = TYPE_FUNCTION;
		 (yyval.node)->l.expr = (yyvsp[-2].node);
		 if ((yyvsp[-2].node)->kind == NODE_STRING)
		     yywarn("Function pointer returning string constant is NOT a function call");
		 (yyval.node)->r.expr = current_function_context->values_list->r.expr;
		 (yyval.node)->v.number = FP_FUNCTIONAL + current_function_context->bindable
		     + (current_function_context->num_parameters << 8);
		 pop_function_context();
             }
#line 5562 "grammar.tab.c"
    break;

  case 214: /* expr4: L_MAPPING_OPEN expr_list3 ']' ')'  */
#line 3238 "grammar.y"
            {
#line 3188 "grammar.y.pre"
#ifdef WOMBLES
	        if(*(outp-2) != ']')
		  yyerror("End of mapping not found");
#endif
		CREATE_CALL((yyval.node), F_AGGREGATE_ASSOC, TYPE_MAPPING, (yyvsp[-2].node));
	    }
#line 5575 "grammar.tab.c"
    break;

  case 215: /* expr4: L_ARRAY_OPEN expr_list '}' ')'  */
#line 3247 "grammar.y"
            {
#line 3196 "grammar.y.pre"
#ifdef WOMBLES
	        if(*(outp-2) != '}')
		  yyerror("End of array not found");
#endif  
		CREATE_CALL((yyval.node), F_AGGREGATE, TYPE_ANY | TYPE_MOD_ARRAY, (yyvsp[-2].node));
	    }
#line 5588 "grammar.tab.c"
    break;

  case 216: /* expr_or_block: block  */
#line 3259 "grammar.y"
            {
#line 3207 "grammar.y.pre"
		(yyval.node) = (yyvsp[0].decl).node;
	    }
#line 5597 "grammar.tab.c"
    break;

  case 217: /* expr_or_block: '(' comma_expr ')'  */
#line 3264 "grammar.y"
            {
#line 3211 "grammar.y.pre"
		(yyval.node) = insert_pop_value((yyvsp[-1].node));
	    }
#line 5606 "grammar.tab.c"
    break;

  case 218: /* @13: %empty  */
#line 3272 "grammar.y"
            {
#line 3218 "grammar.y.pre"
		(yyval.number) = context;
		context = SPECIAL_CONTEXT;
	    }
#line 5616 "grammar.tab.c"
    break;

  case 219: /* catch: L_CATCH @13 expr_or_block  */
#line 3278 "grammar.y"
            {
#line 3223 "grammar.y.pre"
		CREATE_CATCH((yyval.node), (yyvsp[0].node));
		context = (yyvsp[-1].number);
	    }
#line 5626 "grammar.tab.c"
    break;

  case 220: /* sscanf: L_SSCANF '(' expr0 ',' expr0 lvalue_list ')'  */
#line 3288 "grammar.y"
            {
#line 3247 "grammar.y.pre"
		int p = (yyvsp[-1].node)->v.number;
		CREATE_LVALUE_EFUN((yyval.node), TYPE_NUMBER, (yyvsp[-1].node));
		CREATE_BINARY_OP_1((yyval.node)->l.expr, F_SSCANF, 0, (yyvsp[-4].node), (yyvsp[-2].node), p);
	    }
#line 5637 "grammar.tab.c"
    break;

  case 221: /* parse_command: L_PARSE_COMMAND '(' expr0 ',' expr0 ',' expr0 lvalue_list ')'  */
#line 3298 "grammar.y"
            {
#line 3256 "grammar.y.pre"
		int p = (yyvsp[-1].node)->v.number;
		CREATE_LVALUE_EFUN((yyval.node), TYPE_NUMBER, (yyvsp[-1].node));
		CREATE_TERNARY_OP_1((yyval.node)->l.expr, F_PARSE_COMMAND, 0, 
				    (yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-2].node), p);
	    }
#line 5649 "grammar.tab.c"
    break;

  case 222: /* @14: %empty  */
#line 3309 "grammar.y"
            {
#line 3266 "grammar.y.pre"
		(yyval.number) = context;
		context = SPECIAL_CONTEXT;
	    }
#line 5659 "grammar.tab.c"
    break;

  case 223: /* time_expression: L_TIME_EXPRESSION @14 expr_or_block  */
#line 3315 "grammar.y"
            {
#line 3271 "grammar.y.pre"
		CREATE_TIME_EXPRESSION((yyval.node), (yyvsp[0].node));
		context = (yyvsp[-1].number);
	    }
#line 5669 "grammar.tab.c"
    break;

  case 224: /* lvalue_list: %empty  */
#line 3324 "grammar.y"
            {
#line 3279 "grammar.y.pre"
	        (yyval.node) = new_node_no_line();
		(yyval.node)->r.expr = 0;
	        (yyval.node)->v.number = 0;
	    }
#line 5680 "grammar.tab.c"
    break;

  case 225: /* lvalue_list: ',' lvalue lvalue_list  */
#line 3331 "grammar.y"
            {
#line 3285 "grammar.y.pre"
		parse_node_t *insert;
		
		(yyval.node) = (yyvsp[0].node);
		insert = new_node_no_line();
		insert->r.expr = (yyvsp[0].node)->r.expr;
		insert->l.expr = (yyvsp[-1].node);
		(yyvsp[0].node)->r.expr = insert;
		(yyval.node)->v.number++;
	    }
#line 5696 "grammar.tab.c"
    break;

  case 226: /* string: string_con2  */
#line 3346 "grammar.y"
            {
#line 3299 "grammar.y.pre"
		CREATE_STRING((yyval.node), (yyvsp[0].string));
		scratch_free((yyvsp[0].string));
	    }
#line 5706 "grammar.tab.c"
    break;

  case 228: /* string_con1: '(' string_con1 ')'  */
#line 3356 "grammar.y"
            {
#line 3308 "grammar.y.pre"
		(yyval.string) = (yyvsp[-1].string);
	    }
#line 5715 "grammar.tab.c"
    break;

  case 229: /* string_con1: string_con1 '+' string_con1  */
#line 3361 "grammar.y"
            {
#line 3312 "grammar.y.pre"
		(yyval.string) = scratch_join((yyvsp[-2].string), (yyvsp[0].string));
	    }
#line 5724 "grammar.tab.c"
    break;

  case 231: /* string_con2: string_con2 L_STRING  */
#line 3370 "grammar.y"
            {
#line 3320 "grammar.y.pre"
		(yyval.string) = scratch_join((yyvsp[-1].string), (yyvsp[0].string));
	    }
#line 5733 "grammar.tab.c"
    break;

  case 232: /* class_init: identifier ':' expr0  */
#line 3377 "grammar.y"
    {
#line 3326 "grammar.y.pre"
	(yyval.node) = new_node();
	(yyval.node)->l.expr = (parse_node_t *)(yyvsp[-2].string);
	(yyval.node)->v.expr = (yyvsp[0].node);
	(yyval.node)->r.expr = 0;
    }
#line 5745 "grammar.tab.c"
    break;

  case 233: /* opt_class_init: %empty  */
#line 3388 "grammar.y"
    {
#line 3336 "grammar.y.pre"
	(yyval.node) = 0;
    }
#line 5754 "grammar.tab.c"
    break;

  case 234: /* opt_class_init: opt_class_init ',' class_init  */
#line 3393 "grammar.y"
    {
#line 3340 "grammar.y.pre"
	(yyval.node) = (yyvsp[0].node);
	(yyval.node)->r.expr = (yyvsp[-2].node);
    }
#line 5764 "grammar.tab.c"
    break;

  case 235: /* @15: %empty  */
#line 3403 "grammar.y"
            {
#line 3349 "grammar.y.pre"
		(yyval.number) = context;
		(yyvsp[0].number) = num_refs;
		context |= ARG_LIST; 
	    }
#line 5775 "grammar.tab.c"
    break;

  case 236: /* function_call: efun_override '(' @15 expr_list ')'  */
#line 3410 "grammar.y"
            {
#line 3355 "grammar.y.pre"
		context = (yyvsp[-2].number);
		(yyval.node) = validate_efun_call((yyvsp[-4].number),(yyvsp[-1].node));
		(yyval.node) = check_refs(num_refs - (yyvsp[-3].number), (yyvsp[-1].node), (yyval.node));
		num_refs = (yyvsp[-3].number);
	    }
#line 5787 "grammar.tab.c"
    break;

  case 237: /* @16: %empty  */
#line 3418 "grammar.y"
            {
#line 3362 "grammar.y.pre"
		(yyval.number) = context;
		(yyvsp[0].number) = num_refs;
		context |= ARG_LIST;
	    }
#line 5798 "grammar.tab.c"
    break;

  case 238: /* function_call: L_NEW '(' @16 expr_list ')'  */
#line 3425 "grammar.y"
            {
#line 3368 "grammar.y.pre"
		ident_hash_elem_t *ihe;
		int f;

		context = (yyvsp[-2].number);
		ihe = lookup_ident("clone_object");

		if ((f = ihe->dn.simul_num) != -1) {
		    (yyval.node) = (yyvsp[-1].node);
		    (yyval.node)->kind = NODE_CALL_1;
		    (yyval.node)->v.number = F_SIMUL_EFUN;
		    (yyval.node)->l.number = f;
		    (yyval.node)->type = (SIMUL(f)->type) & ~DECL_MODS;
		} else {
		    (yyval.node) = validate_efun_call(lookup_predef("clone_object"), (yyvsp[-1].node));
#ifdef CAST_CALL_OTHERS
		    (yyval.node)->type = TYPE_UNKNOWN;
#else
		    (yyval.node)->type = TYPE_ANY;
#endif		  
		}
		(yyval.node) = check_refs(num_refs - (yyvsp[-3].number), (yyvsp[-1].node), (yyval.node));
		num_refs = (yyvsp[-3].number);
            }
#line 5828 "grammar.tab.c"
    break;

  case 239: /* function_call: L_NEW '(' L_CLASS L_DEFINED_NAME opt_class_init ')'  */
#line 3451 "grammar.y"
            {
#line 3393 "grammar.y.pre"
		parse_node_t *node;
		
		if ((yyvsp[-2].ihe)->dn.class_num == -1) {
		    char buf[256];
		    char *end = EndOf(buf);
		    char *p;
		    
		    p = strput(buf, end, "Undefined class '");
		    p = strput(p, end, (yyvsp[-2].ihe)->name);
		    p = strput(p, end, "'");
		    yyerror(buf);
		    CREATE_ERROR((yyval.node));
		    node = (yyvsp[-1].node);
		    while (node) {
			scratch_free((char *)node->l.expr);
			node = node->r.expr;
		    }
		} else {
		    int type = (yyvsp[-2].ihe)->dn.class_num | TYPE_MOD_CLASS;
		    
		    if ((node = (yyvsp[-1].node))) {
			CREATE_TWO_VALUES((yyval.node), type, 0, 0);
			(yyval.node)->l.expr = reorder_class_values((yyvsp[-2].ihe)->dn.class_num,
							node);
			CREATE_OPCODE_1((yyval.node)->r.expr, F_NEW_CLASS,
					type, (yyvsp[-2].ihe)->dn.class_num);
			
		    } else {
			CREATE_OPCODE_1((yyval.node), F_NEW_EMPTY_CLASS,
					type, (yyvsp[-2].ihe)->dn.class_num);
		    }
		}
            }
#line 5868 "grammar.tab.c"
    break;

  case 240: /* function_call: L_NEW '(' L_CLASS L_IDENTIFIER opt_class_init ')'  */
#line 3487 "grammar.y"
            {
#line 3428 "grammar.y.pre"
		parse_node_t *node;
		char buf[256];
		char *end = EndOf(buf);
		char *p;

		p = strput(buf, end, "Undefined class '");
		p = strput(p, end, (yyvsp[-2].string));
		p = strput(p, end, "'");
		yyerror(buf);
		CREATE_ERROR((yyval.node));
		node = (yyvsp[-1].node);
		while (node) {
		    scratch_free((char *)node->l.expr);
		    node = node->r.expr;
		}
	    }
#line 5891 "grammar.tab.c"
    break;

  case 241: /* @17: %empty  */
#line 3506 "grammar.y"
            {
#line 3446 "grammar.y.pre"
		(yyval.number) = context;
		(yyvsp[0].number) = num_refs;
		context |= ARG_LIST;
	    }
#line 5902 "grammar.tab.c"
    break;

  case 242: /* function_call: L_DEFINED_NAME '(' @17 expr_list ')'  */
#line 3513 "grammar.y"
            {
#line 3452 "grammar.y.pre"
		int f;
		
		context = (yyvsp[-2].number);
		(yyval.node) = (yyvsp[-1].node);
		if ((f = (yyvsp[-4].ihe)->dn.function_num) != -1) {
		    if (current_function_context)
			current_function_context->bindable = FP_NOT_BINDABLE;
		    
		    (yyval.node)->kind = NODE_CALL_1;
		    (yyval.node)->v.number = F_CALL_FUNCTION_BY_ADDRESS;
		    (yyval.node)->l.number = f;
		    (yyval.node)->type = validate_function_call(f, (yyvsp[-1].node)->r.expr);
		} else if ((f=(yyvsp[-4].ihe)->dn.simul_num) != -1) {
		    (yyval.node)->kind = NODE_CALL_1;
		    (yyval.node)->v.number = F_SIMUL_EFUN;
		    (yyval.node)->l.number = f;
		    (yyval.node)->type = (SIMUL(f)->type) & ~DECL_MODS;
		} else if ((f=(yyvsp[-4].ihe)->dn.efun_num) != -1) {
		    (yyval.node) = validate_efun_call(f, (yyvsp[-1].node));
		} else {
		    /* This here is a really nasty case that only occurs with
		     * exact_types off.  The user has done something gross like:
		     *
		     * func() { int f; f(); } // if f was prototyped we wouldn't
		     * f() { }                // need this case
		     *
		     * Don't complain, just grok it.
		     */
		    
		    if (current_function_context)
			current_function_context->bindable = FP_NOT_BINDABLE;
		    
		    f = define_new_function((yyvsp[-4].ihe)->name, 0, 0, 
					    DECL_PUBLIC|FUNC_UNDEFINED, TYPE_ANY);
		    (yyval.node)->kind = NODE_CALL_1;
		    (yyval.node)->v.number = F_CALL_FUNCTION_BY_ADDRESS;
		    (yyval.node)->l.number = f;
		    (yyval.node)->type = TYPE_ANY; /* just a guess */
		    if (exact_types) {
			char buf[256];
			char *end = EndOf(buf);
			char *p;
			const char *n = (yyvsp[-4].ihe)->name;
			if (*n == ':') n++;
			/* prevent some errors; by making it look like an
			 * inherited function we prevent redeclaration errors
			 * if it shows up later
			 */
			
			FUNCTION_FLAGS(f) &= ~FUNC_UNDEFINED;
			FUNCTION_FLAGS(f) |= (FUNC_INHERITED | FUNC_VARARGS);
			p = strput(buf, end, "Undefined function ");
			p = strput(p, end, n);
			yyerror(buf);
		    }
		}
		(yyval.node) = check_refs(num_refs - (yyvsp[-3].number), (yyvsp[-1].node), (yyval.node));
		num_refs = (yyvsp[-3].number);
	    }
#line 5968 "grammar.tab.c"
    break;

  case 243: /* @18: %empty  */
#line 3575 "grammar.y"
            {
#line 3513 "grammar.y.pre"
		(yyval.number) = context;
		(yyvsp[0].number) = num_refs;
		context |= ARG_LIST;
	    }
#line 5979 "grammar.tab.c"
    break;

  case 244: /* function_call: function_name '(' @18 expr_list ')'  */
#line 3582 "grammar.y"
            {
#line 3519 "grammar.y.pre"
	      char *name = (yyvsp[-4].string);

	      context = (yyvsp[-2].number);
	      (yyval.node) = (yyvsp[-1].node);
	      
	      if (current_function_context)
		  current_function_context->bindable = FP_NOT_BINDABLE;

	      if (*name == ':') {
		  int f;
		  
		  if ((f = arrange_call_inherited(name + 1, (yyval.node))) != -1)
		      /* Can't do this; f may not be the correct function
			 entry.  It might be overloaded.
			 
		      validate_function_call(f, $$->r.expr)
		      */
		      ;
	      } else {
		  int f;
		  ident_hash_elem_t *ihe;
		  
		  f = (ihe = lookup_ident(name)) ? ihe->dn.function_num : -1;
		  (yyval.node)->kind = NODE_CALL_1;
		  (yyval.node)->v.number = F_CALL_FUNCTION_BY_ADDRESS;
		  if (f!=-1) {
		      /* The only way this can happen is if function_name
		       * below made the function name.  The lexer would
		       * return L_DEFINED_NAME instead.
		       */
		      (yyval.node)->type = validate_function_call(f, (yyvsp[-1].node)->r.expr);
		  } else {
		      f = define_new_function(name, 0, 0, 
					      DECL_PUBLIC|FUNC_UNDEFINED, TYPE_ANY);
		  }
		  (yyval.node)->l.number = f;
		  /*
		   * Check if this function has been defined.
		   * But, don't complain yet about functions defined
		   * by inheritance.
		   */
		  if (exact_types && (FUNCTION_FLAGS(f) & FUNC_UNDEFINED)) {
		      char buf[256];
		      char *end = EndOf(buf);
		      char *p;
		      char *n = (yyvsp[-4].string);
		      if (*n == ':') n++;
		      /* prevent some errors */
		      FUNCTION_FLAGS(f) &= ~FUNC_UNDEFINED;
		      FUNCTION_FLAGS(f) |= (FUNC_INHERITED | FUNC_VARARGS);
		      p = strput(buf, end, "Undefined function ");
		      p = strput(p, end, n);
		      yyerror(buf);
		  }
		  if (!(FUNCTION_FLAGS(f) & FUNC_UNDEFINED))
		      (yyval.node)->type = FUNCTION_DEF(f)->type;
		  else
		      (yyval.node)->type = TYPE_ANY;  /* Just a guess */
	      }
	      (yyval.node) = check_refs(num_refs - (yyvsp[-3].number), (yyvsp[-1].node), (yyval.node));
	      num_refs = (yyvsp[-3].number);
	      scratch_free(name);
	  }
#line 6049 "grammar.tab.c"
    break;

  case 245: /* @19: %empty  */
#line 3648 "grammar.y"
            {
#line 3584 "grammar.y.pre"
		(yyval.number) = context;
		(yyvsp[0].number) = num_refs;
		context |= ARG_LIST;
	    }
#line 6060 "grammar.tab.c"
    break;

  case 246: /* function_call: expr4 L_ARROW identifier '(' @19 expr_list ')'  */
#line 3655 "grammar.y"
            {
#line 3590 "grammar.y.pre"
		ident_hash_elem_t *ihe;
		int f;
		parse_node_t *pn1, *pn2;
		
		(yyvsp[-1].node)->v.number += 2;

		pn1 = new_node_no_line();
		pn1->type = 0;
		pn1->v.expr = (yyvsp[-6].node);
		pn1->kind = (yyvsp[-1].node)->v.number;
		
		pn2 = new_node_no_line();
		pn2->type = 0;
		CREATE_STRING(pn2->v.expr, (yyvsp[-4].string));
		scratch_free((yyvsp[-4].string));
		
		/* insert the two nodes */
		pn2->r.expr = (yyvsp[-1].node)->r.expr;
		pn1->r.expr = pn2;
		(yyvsp[-1].node)->r.expr = pn1;
		
		if (!(yyvsp[-1].node)->l.expr) (yyvsp[-1].node)->l.expr = pn2;
		    
		context = (yyvsp[-2].number);
		ihe = lookup_ident("call_other");

		if ((f = ihe->dn.simul_num) != -1) {
		    (yyval.node) = (yyvsp[-1].node);
		    (yyval.node)->kind = NODE_CALL_1;
		    (yyval.node)->v.number = F_SIMUL_EFUN;
		    (yyval.node)->l.number = f;
		    (yyval.node)->type = (SIMUL(f)->type) & ~DECL_MODS;
		} else {
		    (yyval.node) = validate_efun_call(arrow_efun, (yyvsp[-1].node));
#ifdef CAST_CALL_OTHERS
		    (yyval.node)->type = TYPE_UNKNOWN;
#else
		    (yyval.node)->type = TYPE_ANY;
#endif		  
		}
		(yyval.node) = check_refs(num_refs - (yyvsp[-3].number), (yyvsp[-1].node), (yyval.node));
		num_refs = (yyvsp[-3].number);
	    }
#line 6110 "grammar.tab.c"
    break;

  case 247: /* @20: %empty  */
#line 3701 "grammar.y"
            {
#line 3635 "grammar.y.pre"
		(yyval.number) = context;
		(yyvsp[0].number) = num_refs;
		context |= ARG_LIST;
	    }
#line 6121 "grammar.tab.c"
    break;

  case 248: /* function_call: '(' '*' comma_expr ')' '(' @20 expr_list ')'  */
#line 3708 "grammar.y"
            {
#line 3641 "grammar.y.pre"
	        parse_node_t *expr;

		context = (yyvsp[-2].number);
		(yyval.node) = (yyvsp[-1].node);
		(yyval.node)->kind = NODE_EFUN;
		(yyval.node)->l.number = (yyval.node)->v.number + 1;
		(yyval.node)->v.number = predefs[evaluate_efun].token;
#ifdef CAST_CALL_OTHERS
		(yyval.node)->type = TYPE_UNKNOWN;
#else
		(yyval.node)->type = TYPE_ANY;
#endif
		expr = new_node_no_line();
		expr->type = 0;
		expr->v.expr = (yyvsp[-5].node);
		expr->r.expr = (yyval.node)->r.expr;
		(yyval.node)->r.expr = expr;
		(yyval.node) = check_refs(num_refs - (yyvsp[-3].number), (yyvsp[-1].node), (yyval.node));
		num_refs = (yyvsp[-3].number);
	    }
#line 6148 "grammar.tab.c"
    break;

  case 249: /* efun_override: L_EFUN L_COLON_COLON identifier  */
#line 3732 "grammar.y"
                                               {
#line 3664 "grammar.y.pre"
	svalue_t *res;
	ident_hash_elem_t *ihe;

	(yyval.number) = (ihe = lookup_ident((yyvsp[0].string))) ? ihe->dn.efun_num : -1;
	if ((yyval.number) == -1) {
	    char buf[256];
	    char *end = EndOf(buf);
	    char *p;
	    
	    p = strput(buf, end, "Unknown efun: ");
	    p = strput(p, end, (yyvsp[0].string));
	    yyerror(buf);
	} else {
	    push_malloced_string(the_file_name(current_file));
	    share_and_push_string((yyvsp[0].string));
	    push_malloced_string(add_slash(main_file_name()));
	    res = safe_apply_master_ob(APPLY_VALID_OVERRIDE, 3);
	    if (!MASTER_APPROVED(res)) {
		yyerror("Invalid simulated efunction override");
		(yyval.number) = -1;
	    }
	}
	scratch_free((yyvsp[0].string));
      }
#line 6179 "grammar.tab.c"
    break;

  case 250: /* efun_override: L_EFUN L_COLON_COLON L_NEW  */
#line 3758 "grammar.y"
                                 {
#line 3689 "grammar.y.pre"
	svalue_t *res;
	
	push_malloced_string(the_file_name(current_file));
	push_constant_string("new");
	push_malloced_string(add_slash(main_file_name()));
	res = safe_apply_master_ob(APPLY_VALID_OVERRIDE, 3);
	if (!MASTER_APPROVED(res)) {
	    yyerror("Invalid simulated efunction override");
	    (yyval.number) = -1;
	} else (yyval.number) = new_efun;
      }
#line 6197 "grammar.tab.c"
    break;

  case 252: /* function_name: L_COLON_COLON identifier  */
#line 3776 "grammar.y"
            {
#line 3706 "grammar.y.pre"
		int l = strlen((yyvsp[0].string)) + 1;
		char *p;
		/* here we be a bit cute.  we put a : on the front so we
		 * don't have to strchr for it.  Here we do:
		 * "name" -> ":::name"
		 */
		(yyval.string) = scratch_realloc((yyvsp[0].string), l + 3);
		p = (yyval.string) + l;
		while (p--,l--)
		    *(p+3) = *p;
		strncpy((yyval.string), ":::", 3);
	    }
#line 6216 "grammar.tab.c"
    break;

  case 253: /* function_name: L_BASIC_TYPE L_COLON_COLON identifier  */
#line 3791 "grammar.y"
            {
#line 3720 "grammar.y.pre"
		int z, l = strlen((yyvsp[0].string)) + 1;
		char *p;
		/* <type> and "name" -> ":type::name" */
		z = strlen(compiler_type_names[(yyvsp[-2].number)]) + 3; /* length of :type:: */
		(yyval.string) = scratch_realloc((yyvsp[0].string), l + z);
		p = (yyval.string) + l;
		while (p--,l--)
		    *(p+z) = *p;
		(yyval.string)[0] = ':';
		strncpy((yyval.string) + 1, compiler_type_names[(yyvsp[-2].number)], z - 3);
		(yyval.string)[z-2] = ':';
		(yyval.string)[z-1] = ':';
	    }
#line 6236 "grammar.tab.c"
    break;

  case 254: /* function_name: identifier L_COLON_COLON identifier  */
#line 3807 "grammar.y"
            {
#line 3735 "grammar.y.pre"
		int l = strlen((yyvsp[-2].string));
		/* "ob" and "name" -> ":ob::name" */
		(yyval.string) = scratch_alloc(l + strlen((yyvsp[0].string)) + 4);
		*((yyval.string)) = ':';
		strcpy((yyval.string) + 1, (yyvsp[-2].string));
		strcpy((yyval.string) + l + 1, "::");
		strcpy((yyval.string) + l + 3, (yyvsp[0].string));
		scratch_free((yyvsp[-2].string));
		scratch_free((yyvsp[0].string));
	    }
#line 6253 "grammar.tab.c"
    break;

  case 255: /* cond: L_IF '(' comma_expr ')' statement optional_else_part  */
#line 3823 "grammar.y"
            {
#line 3750 "grammar.y.pre"
		/* x != 0 -> x */
		if (IS_NODE((yyvsp[-3].node), NODE_BINARY_OP, F_NE)) {
		    if (IS_NODE((yyvsp[-3].node)->r.expr, NODE_NUMBER, 0))
			(yyvsp[-3].node) = (yyvsp[-3].node)->l.expr;
		    else if (IS_NODE((yyvsp[-3].node)->l.expr, NODE_NUMBER, 0))
			     (yyvsp[-3].node) = (yyvsp[-3].node)->r.expr;
		}

		/* TODO: should optimize if (0), if (1) here.  
		 * Also generalize this.
		 */

		if ((yyvsp[-1].node) == 0) {
		    if ((yyvsp[0].node) == 0) {
			/* if (x) ; -> x; */
			(yyval.node) = pop_value((yyvsp[-3].node));
			break;
		    } else {
			/* if (x) {} else y; -> if (!x) y; */
			parse_node_t *repl;
			
			CREATE_UNARY_OP(repl, F_NOT, TYPE_NUMBER, (yyvsp[-3].node));
			(yyvsp[-3].node) = repl;
			(yyvsp[-1].node) = (yyvsp[0].node);
			(yyvsp[0].node) = 0;
		    }
		}
		CREATE_IF((yyval.node), (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[0].node));
	    }
#line 6289 "grammar.tab.c"
    break;

  case 256: /* optional_else_part: %empty  */
#line 3858 "grammar.y"
            {
#line 3784 "grammar.y.pre"
		(yyval.node) = 0;
	    }
#line 6298 "grammar.tab.c"
    break;

  case 257: /* optional_else_part: L_ELSE statement  */
#line 3863 "grammar.y"
            {
#line 3788 "grammar.y.pre"
		(yyval.node) = (yyvsp[0].node);
            }
#line 6307 "grammar.tab.c"
    break;


#line 6311 "grammar.tab.c"

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

#line 3868 "grammar.y"



#line 3793 "grammar.y.pre"
