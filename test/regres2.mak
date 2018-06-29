regres: gcd test modtst flatjoy jp-reprodtst jp-joytst lsptst joytut laztst reptst jp-nestrec jp-church mtrtst symtst plgtst

# grmtst

gcd:
	-./$@2 24 54 | diff -w - OUT/gcd.out

test:
	-./$@2 | diff -w - OUT/$@.out

modtst:
	-./$@2 | diff -w - OUT/$@.out

flatjoy:
	-./$@2 | diff -w - OUT/$@.out

jp-reprodtst:
	-./$@2 | diff -w - OUT/$@.out

jp-joytst:
	-./$@2 | diff -w - OUT/$@.out

lsptst:
	-./$@2 $@.inp | diff -w - OUT/$@.out

laztst:
	-./$@2 | diff -w - OUT/$@.out

joytut:
	-./$@2 $@.inp | diff -w - OUT/$@.out

reptst:
	-./$@2 | diff -w - OUT/$@.out

jp-nestrec:
	-./$@2 | diff -w - OUT/$@.out

jp-church:
	-./$@2 | diff -w - OUT/$@.out

mtrtst:
	-./$@2 | diff -w - OUT/$@.out

symtst:
	-./$@2 | diff -w - OUT/$@.out

grmtst:
	-./$@2 | diff -w - OUT/$@.out

plgtst:
	-./$@2 | diff -w - OUT/$@.out
