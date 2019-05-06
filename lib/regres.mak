regres: fib gcd24_54 test jp-joytst flatjoy jp-church grmtst mtrtst reptst tut symtst plgtst lsptst # jp-reprodtst modtst jp-nestrec laztst tutinp

fib:
	../moy fib.joy

gcd24_54:
	../moy gcd.joy 24 54

test:
	../moy $@.joy

jp-joytst:
	../moy $@.joy

flatjoy:
	../moy $@.joy

jp-reprodtst:
	../moy $@.joy

modtst:
	../moy $@.joy

jp-nestrec:
	../moy $@.joy

laztst:
	../moy $@.joy

tutinp:
	cat $@.joy $@.inp | ../moy

jp-church:
	../moy $@.joy

grmtst:
	../moy $@.joy

mtrtst:
	../moy $@.joy

reptst:
	../moy $@.joy

tut:
	-../moy $@.joy

symtst:
	../moy $@.joy

plgtst:
	../moy $@.joy

lsptst:
	-cat $@.joy $@.inp | ../moy
