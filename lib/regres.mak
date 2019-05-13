regres: fib gcd test flatjoy jp-reprodtst jp-nestrec laztst jp-church grmtst mtrtst reptst tut symtst plgtst jp-joytst modtst tutinp lsptst

fib:
	../moy $@.joy 2>&1 | diff -w - OUT/$@.out

gcd:
	../moy $@.joy 24 54 2>&1 | diff -w - OUT/$@.out

test:
	../moy $@.joy 2>&1 | diff -w - OUT/$@.out

flatjoy:
	../moy $@.joy 2>&1 | diff -w - OUT/$@.out

jp-reprodtst:
	../moy $@.joy 2>&1 | diff -w - OUT/$@.out

jp-nestrec:
	../moy $@.joy 2>&1 | diff -w - OUT/$@.out

laztst:
	../moy $@.joy 2>&1 | diff -w - OUT/$@.out

jp-church:
	../moy $@.joy 2>&1 | diff -w - OUT/$@.out

grmtst:
	../moy $@.joy 2>&1 | diff -w - OUT/$@.out

mtrtst:
	../moy $@.joy 2>&1 | diff -w - OUT/$@.out

reptst:
	../moy $@.joy 2>&1 | diff -w - OUT/$@.out

tut:
	../moy $@.joy 2>&1 | diff -w - OUT/$@.out

symtst:
	../moy $@.joy 2>&1 | diff -w - OUT/$@.out

plgtst:
	../moy $@.joy 2>&1 | diff -w - OUT/$@.out

jp-joytst:
	-../moy $@.joy 2>&1 | diff -w - OUT/$@.out

modtst:
	-../moy $@.joy 2>&1 | diff -w - OUT/$@.out

tutinp:
	-cat $@.joy $@.inp | ../moy 2>&1 | diff -w - OUT/$@.out

lsptst:
	-cat $@.joy $@.inp | ../moy 2>&1 | diff -w - OUT/$@.out
