regres: gcd test modtst flatjoy jp-reprodtst laztst reptst jp-nestrec jp-church mtrtst symtst grmtst plgtst # lsptst joytut jp-joytst

gcd:
	-./$@2 24 54 | diff -w - OUT/gcd.out

test:
	-./$@2 | diff -w - OUT/$@.out

modtst:
	-./$@2 | diff -w - OUT/$@.out

flatjoy:
	nm $@2 | grep " _do" >$@2.sym
	-./$@2 | diff -w - OUT/$@.out

jp-reprodtst:
	nm $@2 | grep " _do" >$@2.sym
	-./$@2 | diff -w - OUT/$@.out

jp-joytst:
	nm $@2 | grep " _do" >$@2.sym
	-./$@2 | diff -w - OUT/$@.out

lsptst:
	-./$@2 <$@.inp | diff -w - OUT/$@.out

laztst:
	nm $@2 | grep " _do" >$@2.sym
	-./$@2 | diff -w - OUT/$@.out

joytut:
	-./$@2 <$@.inp | diff -w - OUT/$@.out

reptst:
	nm $@2 | grep " _do" >$@2.sym
	-./$@2 | diff -w - OUT/$@.out

jp-nestrec:
	-./$@2 | diff -w - OUT/$@.out

jp-church:
	nm $@2 | grep " _do" >$@2.sym
	-./$@2 | diff -w - OUT/$@.out

mtrtst:
	-./$@2 | diff -w - OUT/$@.out

symtst:
	nm $@2 | grep " _do" >$@2.sym
	-./$@2 | diff -w - OUT/$@.out

grmtst:
	-./$@2 | diff -w - OUT/$@.out

plgtst:
	nm $@2 | grep " _do" >$@2.sym
	-./$@2 | diff -w - OUT/$@.out
