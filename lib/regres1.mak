regres: fib gcd test jp-joytst flatjoy jp-reprodtst modtst jp-nestrec laztst tutinp jp-church grmtst mtrtst reptst tutorial symtst plgtst lsptst

fib:
	./$@1 | diff -w - OUT1/fib.out

gcd:
	./$@1 24 54 | diff -w - OUT1/gcd.out

test:
	./$@1 | diff -w - OUT1/$@.out

jp-joytst:
	./$@1 | diff -Bw - OUT1/$@.out

flatjoy:
	./$@1 | diff -Bw - OUT1/$@.out

jp-reprodtst:
	./$@1 | diff -Bw - OUT1/$@.out

modtst:
	./$@1 | diff -Bw - OUT1/$@.out

jp-nestrec:
	./$@1 | diff -Bw - OUT1/$@.out

laztst:
	./$@1 | diff -Bw - OUT1/$@.out

tutinp:
	./$@1 $@.inp | diff -Bw - OUT1/$@.out

jp-church:
	./$@1 | diff -Bw - OUT1/$@.out

grmtst:
	./$@1 | diff -Bw - OUT1/$@.out

mtrtst:
	./$@1 | diff -Bw - OUT1/$@.out

reptst:
	./$@1 | diff -Bw - OUT1/$@.out

tutorial:
	./$@1 | diff -w - OUT1/$@.out

symtst:
	./$@1 | diff -Bw - OUT1/$@.out

plgtst:
	./$@1 | diff -Bw - OUT1/$@.out

lsptst:
	./$@1 $@.inp | diff -Bw - OUT1/$@.out
