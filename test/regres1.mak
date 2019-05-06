regres: fib gcd test jp-reprodtst modtst jp-church reptst tutorial symtst plgtst grmtst # jp-joytst flatjoy jp-nestrec laztst joytut mtrtst lsptst

fib:
	./$@3 | diff -w - OUT/fib.out

gcd:
	./$@3 24 54 | diff -w - OUT/gcd.out

test:
	-./$@3 | diff -w - OUT/$@.out

jp-joytst:
	./$@3 | diff -w - OUT/$@.out

flatjoy:
	./$@3 | diff -w - OUT/$@.out

jp-reprodtst:
	./$@3 | diff -w - OUT/$@.out

modtst:
	-./$@3 | diff -w - OUT/$@.out

jp-nestrec:
	./$@3 | diff -w - OUT/$@.out

laztst:
	./$@3 | diff -w - OUT/$@.out

joytut:
	./$@2 <$@.inp | diff -w - OUT/$@.out

jp-church:
	./$@3 | diff -w - OUT/$@.out

grmtst:
	./$@3 | diff -w - OUT/$@.out

mtrtst:
	./$@3 | diff -w - OUT/$@.out

reptst:
	./$@3 | diff -w - OUT/$@.out

tutorial:
	./$@3 | diff -w - OUT/$@.out

symtst:
	./$@3 | diff -w - OUT/$@.out

plgtst:
	./$@3 | diff -w - OUT/$@.out

lsptst:
	./$@1 <$@.inp | diff -w - OUT/$@.out
