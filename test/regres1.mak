regres: gcd test modtst flatjoy jp-reprodtst jp-joytst lsptst joytut laztst reptst jp-nestrec jp-church mtrtst symtst grmtst plgtst

gcd:
	-./$@1 24 54 | diff -w - OUT/gcd.out

test:
	-./$@1 | diff -w - OUT/$@.out

modtst:
	-./$@1 | diff -w - OUT/$@.out

flatjoy:
	-./$@1 | diff -w - OUT/$@.out

jp-reprodtst:
	-./$@1 | diff -w - OUT/$@.out

jp-joytst:
	-./$@1 | diff -w - OUT/$@.out

lsptst:
	-./$@1 $@.inp | diff -w - OUT/$@.out

laztst:
	-./$@1 | diff -w - OUT/$@.out

joytut:
	-./$@1 $@.inp | diff -w - OUT/$@.out

reptst:
	-./$@1 | diff -w - OUT/$@.out

jp-nestrec:
	-./$@1 | diff -w - OUT/$@.out

jp-church:
	-./$@1 | diff -w - OUT/$@.out

mtrtst:
	-./$@1 | diff -w - OUT/$@.out

symtst:
	-./$@1 | diff -w - OUT/$@.out

grmtst:
	-./$@1 | diff -w - OUT/$@.out

plgtst:
	-./$@1 | diff -w - OUT/$@.out
