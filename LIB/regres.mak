regres: gcd24_54 test1 modtst flatjoy jp-reprodtst jp-joytst lsptst tutinp laztst reptst jp-nestrec jp-church mtrtst symtst grmtst plgtst

gcd24_54:
	-../moy gcd.joy 24 54 | diff -w - gcd.out

test1:
	-../moy $@.joy | diff -w - $@.out

modtst:
	-../moy $@.joy 2>&1 | diff -w - $@.out

flatjoy:
	-../moy $@.joy | diff -w - $@.out

jp-reprodtst:
	-../moy $@.joy | diff -w - $@.out

jp-joytst:
	-../moy $@.joy | diff -w - $@.out

lsptst:
	-../moy $@.joy | diff -w - $@.out

tutinp:
	-../moy $@.joy | diff -w - $@.out

laztst:
	-../moy $@.joy | diff -w - $@.out

reptst:
	-../moy $@.joy | diff -w - $@.out

jp-nestrec:
	-../moy $@.joy | diff -w - $@.out

jp-church:
	-../moy $@.joy | diff -w - $@.out

mtrtst:
	-../moy $@.joy | diff -w - $@.out

symtst:
	-../moy $@.joy | diff -w - $@.out

grmtst:
	-../moy $@.joy | diff -w - $@.out

plgtst:
	-../moy $@.joy | diff -w - $@.out
