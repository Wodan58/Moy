#
#   module  : makefile
#   version : 1.11
#   date    : 09/19/24
#
.POSIX:
.SUFFIXES:

CC = gcc # -pg
CF = -DBYTECODE -O3 -Wall -Wextra -Wpedantic -Werror -Wno-unused-parameter
LF = -lm -lgc
CFLAGS = $(CF) -DCOMP="\"$(CF)\"" -DLINK="\"$(LF)\"" -DVERS="\"Release 1.0\""
HDRS = globals.h
OBJS = main.o pars.o lexr.o arty.o eval.o exec.o module.o otab.o parm.o prog.o \
       read.o repl.o save.o scan.o util.o writ.o error.o ylex.o print.o \
       byte.o code.o comp.o dumpbyte.o optimize.o

joy:	prep $(OBJS)
	$(CC) -o$@ $(OBJS) $(LF)

$(OBJECTS): $(HDRS)

prep:
	sh prim.sh .
	sh tabl.sh .
	$(MAKE) pars.c

clean:
	rm -f $(OBJS) pars.c pars.h lexr.c prim.c prim.h tabl.c

.SUFFIXES: .c .o .y .l

.c.o:
	$(CC) -o$@ $(CFLAGS) -c $<

.y.c:
	bison -o$@ $<

.l.c:
	flex -o$@ $<
