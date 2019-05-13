regres: fib gcd test jp-joytst flatjoy jp-reprodtst modtst jp-nestrec laztst joytut jp-church grmtst mtrtst reptst tutorial symtst plgtst lsptst

fib:
	./$@3 | diff -w - OUT/fib.out

gcd:
	./$@3 24 54 | diff -w - OUT/gcd.out

test:
	-./$@3 | diff -w - OUT/$@.out

# builtin opcase is not supported
jp-joytst:
	-./$@1 | diff -w - OUT/$@.out

# predicate list is not supported
flatjoy:
	./$@1 | diff -w - OUT/$@.out

jp-reprodtst:
	./$@3 | diff -w - OUT/$@.out

modtst:
	-./$@3 | diff -w - OUT/$@.out

jp-nestrec:
	./$@3 | diff -w - OUT/$@.out

laztst:
	./$@3 | diff -w - OUT/$@.out

# predicates list, integer are not supported
joytut:
	./$@1 <$@.inp | diff -w - OUT/$@.out

jp-church:
	./$@3 | diff -w - OUT/$@.out

grmtst:
	./$@3 | diff -w - OUT/$@.out

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

# predicates list, integer, float, string are not supported
lsptst:
	./$@1 <$@.inp | diff -w - OUT/$@.out

