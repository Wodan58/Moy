#
#   module  : makefile
#   version : 1.4
#   date    : 10/12/23
#
.POSIX:
.SUFFIXES:
.PRECIOUS: pars.c lexr.c

CC = gcc
CF = -DCOPYRIGHT -O3 -Wall -Wextra -Wpedantic -Werror -Wno-unused-parameter
LF = -lm -lgc
CFLAGS = $(CF) -DCOMP="\"$(CF)\"" -DLINK="\"$(LF)\"" -DVERS="\"Release 1.0\""
OBJECTS = main.o pars.o lexr.o scan.o repl.o modl.o ylex.o util.o exec.o \
	  eval.o xerr.o otab.o prog.o writ.o read.o save.o parm.o arty.o

joy: prep $(OBJECTS)
	$(CC) -o$@ $(OBJECTS) $(LF)

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
