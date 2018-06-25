regres: gcd test modtst flatjoy jp-reprodtst laztst reptst jp-nestrec jp-church mtrtst symtst grmtst plgtst joytut lsptst jp-joytst

gcd:
	-./$@1 24 54 | diff -w - OUT/gcd.out

test:
	-./$@1 | diff -w - OUT/$@.out

modtst:
	-./$@1 | diff -w - OUT/$@.out

flatjoy:
	nm $@1 | grep " _do" >$@1.sym
	-./$@1 | diff -w - OUT/$@.out

jp-reprodtst:
	nm $@1 | grep " _do" >$@1.sym
	-./$@1 | diff -w - OUT/$@.out

jp-joytst:
	nm $@1 | grep " _do" >$@1.sym
	-./$@1 | diff -w - OUT/$@.out

lsptst:
	nm $@1 | grep " _do" >$@1.sym
	-./$@1 <$@.inp | diff -w - OUT/$@.out

laztst:
	nm $@1 | grep " _do" >$@1.sym
	-./$@1 | diff -w - OUT/$@.out

joytut:
	nm $@1 | grep " _do" >$@1.sym
	-./$@1 <$@.inp | diff -w - OUT/$@.out

reptst:
	nm $@1 | grep " _do" >$@1.sym
	-./$@1 | diff -w - OUT/$@.out

jp-nestrec:
	-./$@1 | diff -w - OUT/$@.out

jp-church:
	nm $@1 | grep " _do" >$@1.sym
	-./$@1 | diff -w - OUT/$@.out

mtrtst:
	-./$@1 | diff -w - OUT/$@.out

symtst:
	nm $@1 | grep " _do" >$@1.sym
	-./$@1 | diff -w - OUT/$@.out

grmtst:
	-./$@1 | diff -w - OUT/$@.out

plgtst:
	nm $@1 | grep " _do" >$@1.sym
	-./$@1 | diff -w - OUT/$@.out
