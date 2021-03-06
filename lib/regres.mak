#
#   module  : regres.mak
#   version : 1.8
#   date    : 01/24/21
#
regres: fib gcd test flatjoy jp-reprodtst jp-nestrec laztst jp-church grmtst mtrtst reptst tutorial symtst plgtst jp-joytst modtst tutinp lsptst

fib:
	../joy $@.joy 2>&1 | diff -w - OUT/$@.out

gcd:
	../joy $@.joy 24 54 2>&1 | diff -w - OUT/$@.out

test:
	../joy $@.joy 2>&1 | diff -w - OUT/$@.out

flatjoy:
	../joy $@.joy 2>&1 | diff -Bw - OUT/$@.out

jp-reprodtst:
	../joy $@.joy 2>&1 | diff -Bw - OUT/$@.out

jp-nestrec:
	../joy $@.joy 2>&1 | diff -Bw - OUT/$@.out

laztst:
	../joy $@.joy 2>&1 | diff -Bw - OUT/$@.out

jp-church:
	../joy $@.joy 2>&1 | diff -Bw - OUT/$@.out

grmtst:
	../joy $@.joy 2>&1 | diff -Bw - OUT/$@.out

mtrtst:
	../joy $@.joy 2>&1 | diff -Bw - OUT/$@.out

reptst:
	../joy $@.joy 2>&1 | diff -Bw - OUT/$@.out

tutorial:
	../joy $@.joy 2>&1 | diff -w - OUT/$@.out

symtst:
	../joy $@.joy 2>&1 | diff -Bw - OUT/$@.out

plgtst:
	../joy $@.joy 2>&1 | diff -Bw - OUT/$@.out

jp-joytst:
	../joy $@.joy 2>&1 | diff -Bw - OUT/$@.out

modtst:
	../joy $@.joy 2>&1 | diff -Bw - OUT/$@.out

tutinp:
	cat $@.joy $@.inp | ../joy -s 2>&1 | diff -Bw - OUT/$@.out

lsptst:
	cat $@.joy $@.inp | ../joy -s 2>&1 | diff -Bw - OUT/$@.out
