/*
    module  : runtime.c
    version : 1.1
    date    : 03/12/17
*/
#define NCHECK
#include "runtime.h"

/* fibonacci */
#include "binrec.c"
#include "dup.c"
#include "small.c"
#include "pred.c"
#include "plus.c"
#include "put.c"
#include "stop.c"
/* tutorial */
#include "mul.c"
#include "compare2.c"
#include "eql.c"
#include "greater.c"
#include "or.c"
#include "and.c"
#include "not.c"
#include "swap.c"
#include "step.c"
#include "cons.c"
#include "dip.c"
#include "i.c"
#include "uncons.c"
#include "pop.c"
#include "nothing.c"
#include "sametype.c"
#include "index.c"
#include "putch.c"
#include "get.c"
#include "stack.c"
#include "unstack.c"
#include "body.c"
#include "leql.c"
/* gcd */
#include "setautoput.c"
#include "setundeferror.c"
#include "argv.c"
#include "rest.c"
#include "backup.c"
#include "map.c"
#include "strtol.c"
#include "while.c"
#include "rollup.c"
#include "rem.c"
#include "quit.c"
/* modtst */
#include "setecho.c"
#include "minus.c"
#include "succ.c"
#include "concat.c"
/* test1 */
#include "abs.c"
#include "dupd.c"
#include "swapd.c"
#include "cleave.c"
#include "unary2.c"
#include "divide.c"
#include "argc.c"
/* tutinp */
#include "time.c"
#include "srand.c"
#include "of.c"
#include "first.c"
#include "putchars.c"
#include "integer.c"
#include "ifte.c"
#include "equal.c"
#include "at.c"
#include "list.c"
#include "some.c"
#include "size.c"
#include "geql.c"
/* jp-reprodtst */
#include "times.c"
#include "linrec.c"
#include "null.c"
#include "nullary.c"
#include "less.c"
#include "infra.c"
/* mtrtst */
#include "settracegc.c"
#include "popd.c"
#include "id.c"
#include "swons.c"
#include "sin.c"
#include "cos.c"
#include "tan.c"
#include "xor.c"
#include "fold.c"
#include "unswons.c"
/* flatjoy */
/* jp-church */
#include "rolldown.c"
/* reptst */
#include "log10.c"
#include "unary.c"
#include "split.c"
#include "enconcat.c"
/* symtst */
#include "cond.c"
#include "in.c"
#include "filter.c"
#include "rollupd.c"
#include "iflist.c"
#include "intern.c"
/* jp-joytst */
#include "opcase.c"
/* plgtst */
#include "has.c"
/* lsptst */
#include "float.c"
#include "string.c"
#include "tailrec.c"
#include "case.c"
#include "leaf.c"
#include "include.c"
#include "abort.c"
/* laztst */
/* jp-nestrec */
#include "x.c"
#include "condlinrec.c"
#include "rotate.c"
/* grmtst */
/* rest */
#include "false.c"
#include "true.c"
#include "maxint.c"
#include "setsize.c"
#include "symtabmax.c"
#include "symtabindex.c"
#include "dump.c"
#include "conts.c"
#include "autoput.c"
#include "undeferror.c"
#include "undefs.c"
#include "echo.c"
#include "clock.c"
#include "rand.c"
#include "memorymax.c"
#include "stdin.c"
#include "stdout.c"
#include "stderr.c"
#include "rolldownd.c"
#include "rotated.c"
#include "choice.c"
#include "div.c"
#include "sign.c"
#include "neg.c"
#include "ord.c"
#include "chr.c"
#include "asin.c"
#include "acos.c"
#include "atan.c"
#include "atan2.c"
#include "ceil.c"
#include "sinh.c"
#include "cosh.c"
#include "tanh.c"
#include "exp.c"
#include "floor.c"
#include "round.c"
#include "frexp.c"
#include "ldexp.c"
#include "log.c"
#include "modf.c"
#include "pow.c"
#include "sqrt.c"
#include "trunc.c"
#include "localtime.c"
#include "gmtime.c"
#include "mktime.c"
#include "strftime.c"
#include "decode.c"
#include "strtod.c"
#include "format.c"
#include "formatf.c"
#include "min.c"
#include "max.c"
#include "compare.c"
#include "drop.c"
#include "take.c"
#include "name.c"
#include "neql.c"
#include "char.c"
#include "logical.c"
#include "set.c"
#include "user.c"
#include "file.c"
#include "ifchar.c"
#include "iffile.c"
#include "iffloat.c"
#include "ifinteger.c"
#include "iflogical.c"
#include "ifset.c"
#include "ifstring.c"
#include "app1.c"
#include "app11.c"
#include "app12.c"
#include "gc.c"
#include "system.c"
#include "getenv.c"
#include "memoryindex.c"
#include "getch.c"
#include "all.c"
#include "help1.c"
#include "help2.c"
#include "manual.c"
#include "optable.c"
#include "helpdetail.c"
#include "makemanual.c"
#include "manuallist.c"
#include "casting.c"
#include "branch.c"
#include "construct.c"
#include "unary3.c"
#include "unary4.c"
#include "binary.c"
#include "ternary.c"
#include "genrec.c"
#include "primrec.c"
#include "treestep.c"
#include "treerec.c"
#include "treegenrec.c"
#include "fclose.c"
#include "feof.c"
#include "ferror.c"
#include "fflush.c"
#include "fget.c"
#include "fgetch.c"
#include "fgets.c"
#include "fopen.c"
#include "fread.c"
#include "fwrite.c"
#include "fremove.c"
#include "frename.c"
#include "filetime.c"
#include "fput.c"
#include "fputch.c"
#include "fputchars.c"
#include "fseek.c"
#include "ftell.c"