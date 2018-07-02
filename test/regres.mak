regres: gcd24_54 test modtst flatjoy jp-reprodtst jp-joytst lsptst joytut laztst reptst jp-nestrec jp-church mtrtst symtst grmtst plgtst

gcd24_54:
	-../moy gcd.joy 24 54 | diff -w - OUT/gcd.out

test:
	-../moy $@.joy | diff -w - OUT/$@.out

modtst:
	-../moy $@.joy | diff -w - OUT/$@.out

flatjoy:
	-../moy $@.joy | diff -w - OUT/$@.out

jp-reprodtst:
	-../moy $@.joy | diff -w - OUT/$@.out

jp-joytst:
	-../moy $@.joy | diff -w - OUT/$@.out

lsptst:
	-cat $@.joy $@.inp | ../moy | diff -w - OUT/$@.out

joytut:
	-cat $@.joy $@.inp | ../moy | diff -w - OUT/$@.out

laztst:
	-../moy $@.joy | diff -w - OUT/$@.out

reptst:
	-../moy $@.joy | diff -w - OUT/$@.out

jp-nestrec:
	-../moy $@.joy | diff -w - OUT/$@.out

jp-church:
	-../moy $@.joy | diff -w - OUT/$@.out

mtrtst:
	-../moy $@.joy | diff -w - OUT/$@.out

symtst:
	-../moy $@.joy | diff -w - OUT/$@.out

grmtst:
	-../moy $@.joy | diff -w - OUT/$@.out

plgtst:
	-../moy $@.joy | diff -w - OUT/$@.out
