 ![](Wynn.PNG)
======================

Introduction
============

This is a discussion of Joy and an overview of the Moy implementation.
There is an update about the Compiler at the end of this text.

Execution model of Joy
======================

This is how a Joy program gets executed:

1)  First, the program is read from file into memory.

2)  Then, the program is compiled to internal format.

3)  After that, the internal format is executed.

4)  Execution proceeds by stepping through the internal format, factor
    after factor, executing one factor at a time.

This description concerns itself mostly with Joy as an interpreted
language. Now, when compiling Joy, only step 3) remains during the
execution phase. The result, of course, will be the same as when Joy
is interpreted.

Joy compared to other Concatenative languages
=============================================

Joy has conditions that, after reading the condition code, restore the stack
to what it was before the condition started. All other concatenative languages
discard this behaviour, because of performance considerations. Moy follows Joy,
and not the majority.

Valid Joy programs
==================

    2 +

is a program that expects a number on top of the stack, adds 2 to that number
and replaces the number with the result of the addition. It is a valid program.

If this program is executed on an empty stack, it will issue a runtime error.
That error does not make the program invalid. It means that one of the
assumptions about the start condition is violated.

What this means is that all sequences of factors are valid programs. It also
means that runtime errors can occur.

More abstract: if P is a valid program and Q is a valid program, then so is
P Q. In the example, both `2` and `+` are valid programs and so is `2 +`.

Runtime errors are not generated when compiling this code. The compiled code
can look like: `push(2); do_add();`. It is then left till runtime to generate
an error, or not.

Interface to C, implementation agnostic
=======================================

One way to interface between a program written in C and a procedure written
in Joy is to have the C program call the Joy procedure with *argc* and *argv*
initialized with input parameters and one output parameter: a file-pointer
received from tmpfile(). This file-pointer is then used in the Joy procedure
to write data to. For that purpose a new builtin was introduced: *casting*,
because *argv* is a table of strings, not file-pointers and the runtime type
checker rejects the use of a string as file-pointer
(or should reject such use).

Interface to C, implementation aware
====================================

Another way to interface with C is to have the C functions \#include
"runtime.h". The C functions are now aware of the way that the stack is
implemented in Joy and can PUSH input parameters on the stack before calling
the Joy procedure and also read output from the stack after the Joy procedure
returns.

In addition to that, it is possible to have definitions like A == A ... that
cause the compiler to generate a declaration void do\_A(void); and no
definition of do\_A. This definition has to be supplied by the programmer
during the link phase. This is an example of Joy calling a C function.

Additions in Moy
================

Some builtins have been added in addition to *casting*. The tutorial from
42minjoy can be replayed with the addition of *nothing*, *index*, and
*sametype*. For reasons of symmetry *fget* and *getch* have been added, next
to the existing *fput* and *putch*. An arithmetic operator was added, *round*,
because there is also *floor* and *ceil*. Lastly, *filetime* was added, because
it is needed in an implementation of the `make` program. It is not part of
standard C, so that is a good reason why it is not part of joy1. Later on,
*over* and *pick* have been added, allowing conditions whithout save/restore
of the stack, because the programmer already has taken care of that.

Compiling in Moy
================

Moy allows Joy sources to be compiled. The output is C source (to stdout) that
can be compiled and linked with a Joy library of builtins. As a consequence of
the split between compile time behaviour and runtime behaviour two directives
have been borrowed from 42minjoy. This is %PUT that prints a diagnostic message
at compile time to stderr and %INCLUDE that includes source files at compile
time. Later on, %LISTING has been added as well. This overlaps the
functionality of *setecho*, but was easy to add and at this moment *setecho*
is not doing anything.

Changes in Moy
==============

Not all of the builtins of Joy are supported in Moy. Echo of input to output
is not supported. It is used in Joy to build listings of input alongside the
result of interpreting that input. And error messages can be as short as
"syntax error". To mention one example: when trying to redefine a builtin,
Moy will react with "syntax error" without even mentioning in what line the
error should be located. Because of these changes, Moy is not a full
replacement of joy1.

Compiler internals
==================

The compiler writes out the code that otherwise the interpreter would execute,
in case the program is interpreted instead of compiled. This summarizes the
task of the compiler. In practice a little more is going on. The compiler can
also evaluate the program before writing it out. Writing out becomes necessary
when seeing builtins that can only be executed at runtime or when a function is
called recursively or when there are not enough parameters on the compile-time
stack available to allow executing a builtin. The Moy implementation has two
compile options: -l and -c. The latter more thoroughly compiles the code and is
used when benchmarking. This is currently down to one: only -c. The other
project, Coy, uses the equivalent of -c, except when compiling `joytut` or
`lsptst`. The reason why the -c approach fails sometimes is that the
application keeps some kind of state at the bottom of the stack and the
compiler has the habit of printing and clearing the stack.

Benchmarking
============

When compiling, the user expects that the resulting program will run faster
than the interpreted program. That is indeed the case, when using the -c
compile option, but the main slowdown is caused by the way that the stack is
organized. Any improvement there will benefit compiled programs as well as the
interpreter.

Customizing
===========

In joy1 there is only one location where the program can be configured, in
globals.h. In Moy the configuration used to be scattered over several .h and
.c files. An important decision is whether 32 bits or 64 bits will be used as
the width of the value field. That decision can be made in joy.h. The size of
the static part of the stack can be set in node.h. The length of symbol names
and the size of the symbol table can be set in symbol.h; the line length of
input files can also be set in symbol.h; there are limits in history.c,
listing.c, outfile.c, lexer.l, help.c, node.c, scan.c, and symbol.c

Type systems
============

Moy uses the same type system as Joy. Joy only does runtime typing. Moy does
the same typing at compile time and if the types are ok and the builtin to be
executed is not recursive, the builtin is executed at compile time. It is a bit
more complicated than that, because some builtins are generic w.r.t. type and
thus need to be compiled more than once. The types are kept save in history.c
and restored from there in between the multiple executions that are needed on
behalf of the multiple types. In addition to that, there is also the arity
count in arity.c that is used to decide whether conditions need to save and
restore the stack with CONDITION and RELEASE statements.

Adding a new builtin
====================

Adding a new builtin, for example *over*, required a change of 10 files:

-   parse.y - DO\_OVER, a new token type
-   builtin.h - do\_over(), a function declaration
-   lexer.l - over, a new word as builtin
-   optable.c - "over", an explanation of the functionality
-   CMakeLists.txt - over.c must be added to the build process
-   over.c - definition, a file that contains the definition of *over*
-   interp.c - DO\_OVER in the interpreter switch
-   aritysym.c - DO\_OVER in table of arities
-   print.c - "DO\_OVER" in opername
-   runtime.c - \#include over.c

There is now only one location where a builtin needs to be written - as a
C source file in the src-directory with an explanatory comment, starting
with /\*\* followed by a minimum of 8 lines. The blame is on condlinrec
that needs 8 lines of explanation. The build system takes care of the rest.

Roadmap
=======

There is no roadmap for future developments. The language is best used in a
real application and missing parts can be added if and when the need arises.
Maybe a multi-tasking version? Maybe multi-precision numbers? It all depends
on the application whether these additions are needed. The other project, Coy,
has been setup for better performance.

Compile options
===============

There is currently only one way to compile Joy sources: -c.
It has the habit of not making the program run faster.

Decommissioning of lexer.l
==========================

There is now a lexical analyzer in C, rather than (f)lex-generated.
The reason for that are the following considerations:

- The build system complains in the test-directory that lexer.c does not exist,
  and because lexer.l was not found, it does not know how to build lexer.c

- A handwritten lexical analyzer is easier to convert to Joy, in case the
  compiler needs to be written in its own language.

Compiler update
===============

The compiler has been updated. Joy has three kinds of words: literals,
operators, and combinators. Literals are pushed on the stack. Operators can be
executed if they can find the right number of parameters on the stack, of the
right kind. Combinators take quotations as parameters. There are two ways to
compile: in the first approach operators and combinators are compiled to a
C function that implements those operators and combinators, like: do_oper();
and do_comb(); After printing the stack. That is, before a call to do_oper() or
do_comb() is inserted, instructions are printed that recreate at runtime the
stack that existed at compile time. This approach should always work and is
used when compiling the Lisp interpreter. The other way to compile is to execute
an operator, just like it is executed when interpreting. If an operator can't
execute, because of missing or wrong parameters, the first approach is used.
No attempt is made to execute a combinator at compile time. If the correct
number of quotations is present, an instantiated version of the combinator is
printed into the code stream, with the code of the quotations inlined. This
allows the combinator to use the real processor instead of exeterm to evaluate
the quotations. That is faster, as is expected from a compiled program. If the
correct number of quotations is not present, then again the first approach is
used. The first approach is available with option -l; the second approach is
available with option -c. Because the output of the compiler is sent to stdout,
any compile time messages and listings are sent to stderr.

The lexical analyser is back. The problem with the build system was solved and
creating a listing, even in the presence of multi-line comments, is possible.

history.c and arity.c are no longer used - Moy follows Joy, as it costs little
time to save/restore the stack when the stack is implemented as a linked list.
