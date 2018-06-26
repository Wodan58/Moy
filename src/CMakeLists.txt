#
#	Makefile for JOY library
#
cmake_minimum_required(VERSION 3.0)
add_library(joy __dump.c __html_manual.c __latex_manual.c __manual_list.c
__memoryindex.c __memorymax.c __settracegc.c __symtabindex.c __symtabmax.c
_help.c abort.c abs.c acos.c all.c and.c app1.c app11.c app12.c app2.c app3.c
app4.c argc.c argv.c asin.c at.c atan.c atan2.c autoput.c binary.c binrec.c
body.c branch.c case.c casting.c ceil.c char.c choice.c chr.c cleave.c clock.c
compare.c concat.c cond.c condlinrec.c condnestrec.c cons.c construct.c conts.c
cos.c cosh.c dip.c div.c divide.c drop.c dup.c dupd.c echo.c enconcat.c eql.c
equal.c exp.c false.c fclose.c feof.c ferror.c fflush.c fget.c fgetch.c fgets.c
file.c filetime.c filter.c first.c float.c floor.c fold.c fopen.c format.c
formatf.c fput.c fputch.c fputchars.c fread.c fremove.c frename.c frexp.c
fseek.c ftell.c fwrite.c gc.c genrec.c geql.c get.c getch.c getenv.c gmtime.c
greater.c has.c help.c helpdetail.c i.c id.c ifchar.c iffile.c iffloat.c
ifinteger.c iflist.c iflogical.c ifset.c ifstring.c ifte.c in.c include.c
index.c infra.c integer.c intern.c ldexp.c leaf.c leql.c less.c linrec.c list.c
localtime.c log.c log10.c logical.c manual.c map.c max.c maxint.c min.c minus.c
mktime.c modf.c mul.c name.c neg.c neql.c not.c nothing.c null.c nullary.c of.c
opcase.c or.c ord.c over.c pick.c plus.c pop.c popd.c pow.c pred.c primrec.c
put.c putch.c putchars.c quit.c rand.c rem.c rest.c rolldown.c rolldownd.c
rollup.c rollupd.c rotate.c rotated.c round.c sametype.c set.c setautoput.c
setecho.c setsize.c setundeferror.c sign.c sin.c sinh.c size.c small.c some.c
split.c sqrt.c srand.c stack.c stderr.c stdin.c stdout.c step.c stop.c
strftime.c string.c strtod.c strtol.c succ.c swap.c swapd.c swons.c system.c
tailrec.c take.c tan.c tanh.c ternary.c time.c times.c treegenrec.c treerec.c
treestep.c true.c trunc.c unary.c unary2.c unary3.c unary4.c uncons.c
undeferror.c undefs.c unstack.c unswons.c user.c while.c x.c xor.c)
