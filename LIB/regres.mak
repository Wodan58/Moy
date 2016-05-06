regres: gcd24_54 modtst test tutinp jp-reprodtst mtrtst flatjoy jp-church reptst symtst jp-joytst plgtst lsptst laztst jp-nestrec grmtst

gcd24_54:
        ..\moy gcd 24 54 | diff -w - gcd_.out

modtst:
	-..\moy $@.joy | diff -w - $@_.out

test:
	..\moy $@.joy | diff -w - $@_.out

tutinp:
	..\moy $@.joy | diff -w - $@_.out

jp-reprodtst:
	..\moy $@.joy | diff -w - $@_.out

mtrtst:
	..\moy $@.joy | diff -w - $@_.out

flatjoy:
	..\moy $@.joy | diff -w - $@_.out

jp-church:
	..\moy $@.joy | diff -w - $@_.out

reptst:
	..\moy $@.joy | diff -w - $@_.out

symtst:
	..\moy $@.joy | diff -w - $@_.out

jp-joytst:
	..\moy $@.joy | diff -w - $@_.out

plgtst:
	..\moy $@.joy | diff -w - $@_.out

lsptst:
	..\moy $@.joy | diff -w - $@_.out

laztst:
	..\moy $@.joy | diff -w - $@_.out

jp-nestrec:
	..\moy $@.joy | diff -w - $@_.out

grmtst:
	..\moy $@.joy | diff -w - $@_.out
