regres: fib gcd test jp-joytst flatjoy jp-reprodtst modtst jp-nestrec laztst joytut jp-church grmtst mtrtst reptst tutorial symtst plgtst lsptst

fib:
	./$@3 | diff -w - OUT/fib.out

gcd:
	./$@3 24 54 | diff -w - OUT/gcd.out

test:
	-./$@3 | diff -w - OUT/$@.out

jp-joytst:
	-./$@4 | diff -w - OUT/$@.out

flatjoy:
	./$@4 | diff -w - OUT/$@.out

jp-reprodtst:
	./$@3 | diff -w - OUT/$@.out

modtst:
	-./$@3 | diff -w - OUT/$@.out

jp-nestrec:
	./$@3 | diff -w - OUT/$@.out

laztst:
	./$@3 | diff -w - OUT/$@.out

joytut:
	-./$@2 <$@.inp | diff -w - OUT/$@.out

jp-church:
	./$@3 | diff -w - OUT/$@.out

grmtst:
	./$@4 | diff -w - OUT/$@.out

mtrtst:
	-./$@3 | diff -w - OUT/$@.out

reptst:
	./$@3 | diff -w - OUT/$@.out

tutorial:
	./$@3 | diff -w - OUT/$@.out

symtst:
	./$@3 | diff -w - OUT/$@.out

plgtst:
	./$@3 | diff -w - OUT/$@.out

lsptst:
	-./$@1 <$@.inp | diff -w - OUT/$@.out
