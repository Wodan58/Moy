regres: gcd24_54 modtst test1 tutinp jp-reprodtst mtrtst flatjoy jp-church reptst symtst jp-joytst plgtst lsptst laztst jp-nestrec grmtst

gcd24_54:
	../moy gcd 24 54 | diff -w - gcd.out

modtst:
	-../moy $@.joy | diff -w - $@.out

test1:
	../moy $@.joy | diff -w - $@.out

tutinp:
	../moy $@.joy | diff -w - $@.out

jp-reprodtst:
	../moy $@.joy | diff -w - $@.out

mtrtst:
	../moy $@.joy | diff -w - $@.out

flatjoy:
	../moy $@.joy | diff -w - $@.out

jp-church:
	../moy $@.joy | diff -w - $@.out

reptst:
	../moy $@.joy | diff -w - $@.out

symtst:
	../moy $@.joy | diff -w - $@.out

jp-joytst:
	../moy $@.joy | diff -w - $@.out

plgtst:
	../moy $@.joy | diff -w - $@.out

lsptst:
	../moy $@.joy | diff -w - $@.out

laztst:
	../moy $@.joy | diff -w - $@.out

jp-nestrec:
	../moy $@.joy | diff -w - $@.out

grmtst:
	../moy $@.joy | diff -w - $@.out
