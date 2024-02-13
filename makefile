#
#   module  : makefile
#   version : 1.5
#   date    : 01/18/24
#
.POSIX:
.SUFFIXES:
.PRECIOUS: pars.c lexr.c

CC = gcc
CF = -DCOPYRIGHT -O3 -Wall -Wextra -Wpedantic -Werror -Wno-unused-parameter
LF = -lm -lgc
CFLAGS = $(CF) -DCOMP="\"$(CF)\"" -DLINK="\"$(LF)\"" -DVERS="\"Release 1.0\""
HDRS = globals.h
OBJS = main.o pars.o lexr.o scan.o repl.o modl.o ylex.o util.o exec.o \
       eval.o xerr.o otab.o prog.o writ.o read.o save.o parm.o arty.o

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
	SOURCE_DATE_EPOCH=1047920271 $(CC) -o$@ $(CFLAGS) -c $<

.y.c:
	bison -o$@ $<

.l.c:
	flex -o$@ $<
