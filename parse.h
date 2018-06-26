/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef YY_YY_PARSE_H_INCLUDED
# define YY_YY_PARSE_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    Symbol = 250,
    SYMBOL_ = 1,
    USR_ = 2,
    ANON_FUNCT_ = 3,
    BOOLEAN_ = 4,
    CHAR_ = 5,
    INTEGER_ = 6,
    SET_ = 7,
    STRING_ = 8,
    LIST_ = 9,
    FLOAT_ = 10,
    FILE_ = 11,
    DO_NOTHING = 12,
    DO_FALSE = 13,
    DO_TRUE = 14,
    DO_MAXINT = 15,
    DO_SETSIZE = 16,
    DO_STACK = 17,
    DO_SYMTABMAX = 18,
    DO_SYMTABINDEX = 19,
    DO_DUMP = 20,
    DO_CONTS = 21,
    DO_AUTOPUT = 22,
    DO_UNDEFERROR = 23,
    DO_UNDEFS = 24,
    DO_ECHO = 25,
    DO_CLOCK = 26,
    DO_TIME = 27,
    DO_RAND = 28,
    DO_MEMORYMAX = 29,
    DO_STDIN = 30,
    DO_STDOUT = 31,
    DO_STDERR = 32,
    DO_ID = 33,
    DO_DUP = 34,
    DO_OVER = 35,
    DO_PICK = 36,
    DO_SWAP = 37,
    DO_ROLLUP = 38,
    DO_ROLLDOWN = 39,
    DO_ROTATE = 40,
    DO_POPD = 41,
    DO_MUL = 42,
    DO_PLUS = 43,
    DO_DUPD = 44,
    DO_MINUS = 45,
    DO_STOP = 46,
    DO_DIVIDE = 47,
    DO_SWAPD = 48,
    DO_ROLLUPD = 49,
    DO_ROLLDOWND = 50,
    DO_ROTATED = 51,
    DO_POP = 52,
    DO_CHOICE = 53,
    DO_OR = 54,
    DO_XOR = 55,
    DO_AND = 56,
    DO_NOT = 57,
    DO_REM = 58,
    SEMI = 59,
    DO_LESS = 60,
    DO_EQL = 61,
    DO_GREATER = 62,
    DO_DIV = 63,
    DO_SIGN = 64,
    DO_NEG = 65,
    DO_ORD = 66,
    DO_CHR = 67,
    DO_ABS = 68,
    DO_ACOS = 69,
    DO_ASIN = 70,
    DO_ATAN = 71,
    DO_ATAN2 = 72,
    DO_CEIL = 73,
    DO_COS = 74,
    DO_COSH = 75,
    DO_EXP = 76,
    DO_FLOOR = 77,
    DO_ROUND = 78,
    DO_FREXP = 79,
    DO_LDEXP = 80,
    DO_LOG = 81,
    DO_LOG10 = 82,
    DO_MODF = 83,
    DO_POW = 84,
    DO_SIN = 85,
    DO_SINH = 86,
    DO_SQRT = 87,
    DO_TAN = 88,
    DO_TANH = 89,
    DO_TRUNC = 90,
    LBRACK = 91,
    DO_LOCALTIME = 92,
    RBRACK = 93,
    DO_GMTIME = 94,
    DO_MKTIME = 95,
    DO_STRFTIME = 96,
    DO_STRTOL = 97,
    DO_STRTOD = 98,
    DO_FORMAT = 99,
    DO_FORMATF = 100,
    DO_SRAND = 101,
    DO_PRED = 102,
    DO_SUCC = 103,
    DO_MAX = 104,
    DO_MIN = 105,
    DO_FCLOSE = 106,
    DO_FEOF = 107,
    DO_FERROR = 108,
    DO_FFLUSH = 109,
    DO_FGET = 110,
    DO_FGETCH = 111,
    DO_FGETS = 112,
    DO_FOPEN = 113,
    DO_FREAD = 114,
    DO_FWRITE = 115,
    DO_FREMOVE = 116,
    DO_FRENAME = 117,
    DO_FILETIME = 118,
    DO_FPUT = 119,
    DO_FPUTCH = 120,
    DO_FPUTCHARS = 121,
    DO_FPUTSTRING = 122,
    LBRACE = 123,
    DO_FSEEK = 124,
    RBRACE = 125,
    DO_FTELL = 126,
    DO_UNSTACK = 127,
    DO_CONS = 128,
    DO_SWONS = 129,
    DO_FIRST = 130,
    DO_REST = 131,
    DO_COMPARE = 132,
    DO_INDEX = 133,
    DO_AT = 134,
    DO_OF = 135,
    DO_SIZE = 136,
    DO_CASTING = 137,
    DO_OPCASE = 138,
    DO_CASE = 139,
    DO_UNCONS = 140,
    DO_UNSWONS = 141,
    DO_DROP = 142,
    DO_TAKE = 143,
    DO_CONCAT = 144,
    DO_ENCONCAT = 145,
    DO_NAME = 146,
    DO_INTERN = 147,
    DO_BODY = 148,
    DO_NULL = 149,
    DO_SMALL = 150,
    DO_GEQL = 151,
    DO_LEQL = 152,
    DO_NEQL = 153,
    DO_EQUAL = 154,
    DO_HAS = 155,
    DO_IN = 156,
    DO_SAMETYPE = 157,
    DO_INTEGER = 158,
    DO_CHAR = 159,
    DO_LOGICAL = 160,
    DO_SET = 161,
    DO_STRING = 162,
    DO_LIST = 163,
    DO_LEAF = 164,
    DO_USER = 165,
    DO_FLOAT = 166,
    DO_FILE = 167,
    DO_I = 168,
    DO_X = 169,
    DO_DIP = 170,
    DO_APP1 = 171,
    DO_APP11 = 172,
    DO_APP12 = 173,
    DO_CONSTRUCT = 174,
    DO_NULLARY = 175,
    DO_UNARY = 176,
    DO_UNARY2 = 177,
    DO_UNARY3 = 178,
    DO_UNARY4 = 179,
    DO_APP2 = 180,
    DO_APP3 = 181,
    DO_APP4 = 182,
    DO_BINARY = 183,
    DO_TERNARY = 184,
    DO_CLEAVE = 185,
    DO_BRANCH = 186,
    DO_IFTE = 187,
    DO_IFINTEGER = 188,
    DO_IFCHAR = 189,
    DO_IFLOGICAL = 190,
    DO_IFSET = 191,
    DO_IFSTRING = 192,
    DO_IFLIST = 193,
    DO_IFFLOAT = 194,
    DO_IFFILE = 195,
    DO_COND = 196,
    DO_WHILE = 197,
    DO_LINREC = 198,
    DO_TAILREC = 199,
    DO_BINREC = 200,
    DO_GENREC = 201,
    DO_CONDNESTREC = 202,
    DO_CONDLINREC = 203,
    DO_STEP = 204,
    DO_FOLD = 205,
    DO_MAP = 206,
    DO_TIMES = 207,
    DO_INFRA = 208,
    DO_PRIMREC = 209,
    DO_FILTER = 210,
    DO_SPLIT = 211,
    DO_SOME = 212,
    DO_ALL = 213,
    DO_TREESTEP = 214,
    DO_TREEREC = 215,
    DO_TREEGENREC = 216,
    DO_HELP = 217,
    DO_HELP1 = 218,
    DO_HELPDETAIL = 219,
    DO_MANUAL = 220,
    DO_HTML_MANUAL = 221,
    DO_LATEX_MANUAL = 222,
    DO_MANUAL_LIST = 223,
    DO_SETTRACEGC = 224,
    DO_SETAUTOPUT = 225,
    DO_SETUNDEFERROR = 226,
    DO_SETECHO = 227,
    DO_GC = 228,
    DO_SYSTEM = 229,
    DO_GETENV = 230,
    DO_ARGV = 231,
    DO_ARGC = 232,
    DO_MEMORYINDEX = 233,
    DO_GET = 234,
    DO_GETCH = 235,
    DO_PUT = 236,
    DO_PUTCH = 237,
    DO_PUTCHARS = 238,
    DO_INCLUDE = 239,
    DO_ABORT = 240,
    DO_QUIT = 241,
    MODULE = 251,
    JPRIVATE = 252,
    JPUBLIC = 253,
    JEQUAL = 254,
    END = 255
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 268 "parse.y" /* yacc.c:1909  */

    long_t num;
    ulong_t set;
    char *str;
    real_t dbl;
    FILE *fil;
    struct Node *lis;
    struct Entry *ent;
    void (*proc)(void);
    char ch;
    int bool;
    void *ptr;
    unsigned flag;

#line 319 "parse.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSE_H_INCLUDED  */
