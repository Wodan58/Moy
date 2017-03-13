#
#	Makefile for JOY library
#
cmake_minimum_required(VERSION 3.0)
find_package(FLEX)
FLEX_TARGET(MyScanner lexer.l lexer.c)
add_library(joy ${FLEX_MyScanner_OUTPUTS} error.c initmem.c initsym.c interp1.c
joy.c node.c print.c scan.c symbol.c utils.c binrec.c dup.c small.c pred.c
plus.c put.c stop.c mul.c compare2.c eql.c greater.c or.c and.c not.c swap.c
step.c cons.c dip.c i.c uncons.c pop.c nothing.c sametype.c index.c putch.c
get.c stack.c unstack.c body.c leql.c setautoput.c setundeferror.c argv.c
rest.c backup.c map.c strtol.c while.c rollup.c rem.c quit.c setecho.c minus.c
succ.c concat.c abs.c dupd.c swapd.c cleave.c unary2.c divide.c argc.c time.c
srand.c of.c first.c putchars.c integer.c ifte.c equal.c at.c list.c some.c
size.c geql.c times.c linrec.c null.c nullary.c less.c infra.c settracegc.c
popd.c id.c swons.c sin.c cos.c tan.c xor.c fold.c unswons.c rolldown.c log10.c
unary.c split.c enconcat.c cond.c in.c filter.c rollupd.c iflist.c intern.c
opcase.c has.c float.c string.c tailrec.c case.c leaf.c include.c abort.c x.c
rotate.c condlinrec.c false.c true.c maxint.c setsize.c symtabmax.c
symtabindex.c dump.c conts.c autoput.c undeferror.c undefs.c echo.c clock.c
rand.c memorymax.c stdin.c stdout.c stderr.c rolldownd.c rotated.c choice.c
div.c sign.c neg.c ord.c chr.c asin.c acos.c atan.c atan2.c ceil.c sinh.c
cosh.c tanh.c exp.c floor.c round.c frexp.c ldexp.c log.c modf.c pow.c sqrt.c
trunc.c localtime.c gmtime.c mktime.c strftime.c decode.c strtod.c format.c
formatf.c min.c max.c compare.c drop.c take.c name.c neql.c char.c logical.c
set.c user.c file.c ifchar.c iffile.c iffloat.c ifinteger.c iflogical.c ifset.c
ifstring.c app1.c app11.c app12.c gc.c system.c getenv.c memoryindex.c getch.c
all.c optable.c help1.c help2.c manual.c helpdetail.c makemanual.c manuallist.c
casting.c branch.c construct.c unary3.c unary4.c binary.c ternary.c genrec.c
primrec.c treestep.c treerec.c treegenrec.c fclose.c feof.c ferror.c fflush.c
fget.c fgetch.c fgets.c fopen.c fread.c fwrite.c fremove.c frename.c filetime.c
fput.c fputch.c fputchars.c fseek.c ftell.c)
