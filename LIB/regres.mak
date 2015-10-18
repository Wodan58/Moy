regres: gcd24_54 modtst test joytut jp-reprodtst mtrtst flatjoy jp-church reptst symtst jp-joytst plgtst lsptst laztst jp-nestrec grmtst zextra
	rm -f joy.out

gcd24_54:
	../moy gcd 24 54 | diff -w - gcd.out

joytut:
	../moy $@.inp | diff -w - $@.out

lsptst:
	../moy $@.joy | diff -w - $@.out

jp-joytst:
	../moy $@.joy | diff -w - $@.out

laztst:
	../moy $@.joy | diff -w - $@.out

grmtst:
	../moy $@.joy | diff -w - $@.out

modtst:
	../moy $@.joy | diff -w - $@.out

mtrtst:
	../moy $@.joy | diff -w - $@.out

plgtst:
	../moy $@.joy | diff -w - $@.out

symtst:
	../moy $@.joy | diff -w - $@.out

test:
	../moy $@.joy | diff -w - $@.out

reptst:
	../moy $@.joy | diff -w - $@.out

jp-nestrec:
	../moy $@.joy | diff -w - $@.out

jp-reprodtst:
	../moy $@.joy | diff -w - $@.out

flatjoy:
	../moy $@.joy | diff -w - $@.out

jp-church:
	../moy $@.joy | diff -w - $@.out

zextra:
	-../moy $@.joy | diff -w - $@.out
