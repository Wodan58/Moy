regres: gcd test1 modtst flatjoy jp-reprodtst laztst reptst jp-nestrec jp-church mtrtst symtst grmtst plgtst # lsptst joytut jp-joytst

gcd:
	-./$@ 24 54 | diff -w - OUT/gcd.out

test1:
	-./$@ | diff -w - OUT/$@.out

modtst:
	-./$@ | diff -w - OUT/$@.out

flatjoy:
	nm $@ | grep " _do" >$@.sym
	-./$@ | diff -w - OUT/$@.out

jp-reprodtst:
	nm $@ | grep " _do" >$@.sym
	-./$@ | diff -w - OUT/$@.out

jp-joytst:
	nm $@ | grep " _do" >$@.sym
	-./$@ | diff -w - OUT/$@.out

lsptst:
	-./$@ <$@.inp | diff -w - OUT/$@.out

laztst:
	nm $@ | grep " _do" >$@.sym
	-./$@ | diff -w - OUT/$@.out

joytut:
	-./$@ <$@.inp | diff -w - OUT/$@.out

reptst:
	nm $@ | grep " _do" >$@.sym
	-./$@ | diff -w - OUT/$@.out

jp-nestrec:
	-./$@ | diff -w - OUT/$@.out

jp-church:
	nm $@ | grep " _do" >$@.sym
	-./$@ | diff -w - OUT/$@.out

mtrtst:
	-./$@ | diff -w - OUT/$@.out

symtst:
	nm $@ | grep " _do" >$@.sym
	-./$@ | diff -w - OUT/$@.out

grmtst:
	-./$@ | diff -w - OUT/$@.out

plgtst:
	nm $@ | grep " _do" >$@.sym
	-./$@ | diff -w - OUT/$@.out
