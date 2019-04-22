regres: tutorial fib modtst gcd test jp-reprodtst flatjoy lsptst joytut laztst jp-nestrec jp-church reptst mtrtst symtst grmtst plgtst jp-joytst

tutorial:
	./$@3 | diff -w - OUT/tutorial.out

fib:
	./$@3 | diff -w - OUT/fib.out

modtst:
	-./$@3 | diff -w - OUT/$@.out

gcd:
	./$@3 24 54 | diff -w - OUT/gcd.out

test:
	-./$@3 | diff -w - OUT/$@.out

jp-reprodtst:
	./$@3 | diff -w - OUT/$@.out

jp-joytst:
	./$@3 | diff -w - OUT/$@.out

flatjoy:
	./$@3 | diff -w - OUT/$@.out

lsptst:
	./$@1 <$@.inp | diff -w - OUT/$@.out

joytut:
	./$@2 <$@.inp | diff -w - OUT/$@.out

laztst:
	./$@3 | diff -w - OUT/$@.out

jp-nestrec:
	./$@3 | diff -w - OUT/$@.out

jp-church:
	./$@3 | diff -w - OUT/$@.out

reptst:
	./$@3 | diff -w - OUT/$@.out

mtrtst:
	./$@3 | diff -w - OUT/$@.out

symtst:
	./$@3 | diff -w - OUT/$@.out

grmtst:
	./$@3 | diff -w - OUT/$@.out

plgtst:
	./$@3 | diff -w - OUT/$@.out
