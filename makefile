#
#   module  : makefile
#   version : 1.1
#   date    : 09/11/23
#
.POSIX:
.SUFFIXES:
.PRECIOUS: lexr.c

CC = gcc
CFLAGS = -DNCHECK -DCOPYRIGHT -DJVERSION="\"Release 1.0\"" -O3 -Wall -Wextra -Werror -Wno-unused-parameter
OBJECTS = arty.o eval.o exec.o lexr.o main.o modl.o otab.o parm.o pars.o \
	  prog.o read.o repl.o save.o scan.o undo.o util.o writ.o xerr.o ylex.o

joy: prep $(OBJECTS)
	$(CC) -o$@ $(OBJECTS) -lm -lgc

$(OBJECTS): globals.h

prep:
	sh prim.sh .
	sh tabl.sh .
	$(MAKE) pars.c

clean:
	rm -f *.o pars.c pars.h lexr.c prim.c prim.h tabl.c

.SUFFIXES: .c .o .y .l

.c.o:
	SOURCE_DATE_EPOCH=1047920271 $(CC) -o$@ $(CFLAGS) -c $<

.y.c:
	bison -o$@ $<

.l.c:
	flex -o$@ $<
