regres: gcd test1 modtst flatjoy jp-reprodtst jp-joytst lsptst2 laztst tutinp2 reptst jp-nestrec jp-church mtrtst symtst grmtst plgtst

gcd:
	-./$@ 24 54 | diff -w - gcd.out

test1:
	-./$@ | diff -w - $@.out

modtst:
	-./$@ | diff -w - $@.out

flatjoy:
	nm $@ | grep " _do" >$@.sym
	-./$@ | diff -w - $@.out

jp-reprodtst:
	nm $@ | grep " _do" >$@.sym
	-./$@ | diff -w - $@.out

jp-joytst:
	nm $@ | grep " _do" >$@.sym
	-./$@ | diff -w - $@.out

lsptst2:
	-./$@ <$@.txt | diff -w - $@.out

laztst:
	nm $@ | grep " _do" >$@.sym
	-./$@ | diff -w - $@.out

tutinp2:
	-./$@ <$@.txt | diff -w - $@.out

reptst:
	nm $@ | grep " _do" >$@.sym
	-./$@ | diff -w - $@.out

jp-nestrec:
	-./$@ | diff -w - $@.out

jp-church:
	nm $@ | grep " _do" >$@.sym
	-./$@ | diff -w - $@.out

mtrtst:
	-./$@ | diff -w - $@.out

symtst:
	nm $@ | grep " _do" >$@.sym
	-./$@ | diff -w - $@.out

grmtst:
	-./$@ | diff -w - $@.out

plgtst:
	-./$@ | diff -w - $@.out
