.POSIX:
.SUFFIXES:
.PRECIOUS: lexr.c

CC = gcc
CFLAGS = -O3 -Wall -Wextra -Werror
OBJECTS = arty.o comp.o dtim.o eval.o lexr.o main.o manl.o modl.o parm.o \
	  pars.o prog.o read.o repl.o save.o scan.o syml.o undo.o util.o writ.o

joy: prep $(OBJECTS)
	$(CC) -o$@ $(OBJECTS) -lm -lgc

$(OBJECTS): globals.h

prep:
	sh prim.sh .
	sh tabl.sh .
	$(MAKE) -f make.nogc pars.c

clean:
	rm -f *.o pars.c pars.h lexr.c prim.c prim.h tabl.c

.SUFFIXES: .c .o .y .l

.c.o:
	SOURCE_DATE_EPOCH=1047920271 $(CC) $(CFLAGS) -c $<

.y.c:
	bison -o$@ $<

.l.c:
	flex -o$@ $<
