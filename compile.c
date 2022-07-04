/*
    module  : compile.c
    version : 1.50
    date    : 06/20/22
*/
#include "globals.h"

/*
    ListLeng - return the length of a list, including lengths of sublists.
*/
static int ListLeng(Node *cur)
{
    int leng;

    for (leng = 0; cur; cur = cur->next) {
	leng++;
	if (cur->op == LIST_)
	    leng += ListLeng(cur->u.lis);
    }
    return leng;
}

/*
    StringLeng - determine the length of a string after processing escape
		 sequences. An extra character is needed for character
		 escapes and 3 extra characters are needed for a numeric escape.
*/
static int StringLeng(char *str)
{
    int i;

    for (i = 2; *str; i++, str++)
	if (strchr("\"'\\", *str) || (*str >= 8 && *str <= 13))
	    i++;
	else if (iscntrl((int)*str))
	    i += 3;
    return i;
}

/*
    StringPrint - convert escape sequences in str and store the result in ptr.
		  ", ', \, are preceded by \, as well as characters in the
		  range 8-13. All other characters are copied from str to ptr.
		  The string in ptr starts and ends with ".
		  Escapes other than the ones mentioned are prohibited by the
		  lexical analyzer.
*/
static void StringPrint(char *ptr, char *str)
{
    for (*ptr++ = '"'; *str; str++)
	if (strchr("\"'\\", *str) || (*str >= 8 && *str <= 13)) {
	    *ptr++ = '\\';
	    switch (*str) {
	    case '"':
	    case '\'':
	    case '\\':
		*ptr++ = *str;
		break;
	    case 8:
		*ptr++ = 'b';
		break;
	    case 9:
		*ptr++ = 't';
		break;
	    case 10:
		*ptr++ = 'n';
		break;
	    case 11:
		*ptr++ = 'v';
		break;
	    case 12:
		*ptr++ = 'f';
		break;
	    case 13:
		*ptr++ = 'r';
		break;
	    }
	} else if (iscntrl((int)*str)) {
	    sprintf(ptr, "\\%03o", *str);
	    ptr += 4;
	} else
	    *ptr++ = *str;
    *ptr++ = '"';
    *ptr = 0;
}

/*
    PrintString - return a copy of a string, surrounded by " and with
		  escape characters processed.
*/
static char *PrintString(char *str)
{
    int leng;
    char *ptr;

    leng = StringLeng(str);
    ptr = GC_malloc_atomic(leng + 1);
    StringPrint(ptr, str);
    return ptr;
}

/*
    PrintMember - print a line in a list data structure.
*/
static void PrintMember(pEnv env, Node *cur, int list, int *pindex, FILE *fp)
{
    char *name;
    int offset, flags, index = *pindex;

    if (!cur)
	return;
    fprintf(fp, "{");
    switch (cur->op) {
    case USR_ :
	offset = cur->u.num;
	if (dict_body(env, offset) == 0) {
	    fprintf(fp, ".u.str=\"%s\",", dict_name(env, offset));
	    fprintf(fp, ".op=USR_");
	} else {
	    flags = dict_flags(env, offset);
	    name = dict_nickname(env, offset);
	    if ((flags & (IS_BUILTIN | IS_DECLARED)) == 0) {
		flags |= IS_DECLARED;
		fprintf(declfp, "void do_%s(pEnv env);", name);
	    }
	    dict_setflags(env, offset, flags | IS_USED);
	    fprintf(fp, ".u.proc=do_%s,", name);
	    fprintf(fp, ".op=ANON_FUNCT_");
	}
	break;
    case ANON_FUNCT_ :
	fprintf(fp, ".u.proc=do_%s,", procname(cur->u.proc));
	fprintf(fp, ".op=ANON_FUNCT_");
	break;
    case BOOLEAN_ :
	fprintf(fp, ".u.num=%d,", cur->u.num != 0);
	fprintf(fp, ".op=BOOLEAN_");
	break;
    case CHAR_ :
	fprintf(fp, ".u.num=%d,", (int)cur->u.num);
	fprintf(fp, ".op=CHAR_");
	break;
    case INTEGER_ :
	fprintf(fp, ".u.num=%ld,", (long)cur->u.num);
	fprintf(fp, ".op=INTEGER_");
	break;
    case SET_ :
	fprintf(fp, ".u.num=%lu,", (unsigned long)cur->u.set);
	fprintf(fp, ".op=SET_");
	break;
    case STRING_ :
	fprintf(fp, ".u.str=%s,", PrintString(cur->u.str));
	fprintf(fp, ".op=STRING_");
	break;
    case LIST_ :
	if (cur->u.lis)
	    fprintf(fp, ".u.lis=L%d+%d,", list, index + 1);
	fprintf(fp, ".op=LIST_");
	if (cur->next)
	   fprintf(fp, ",.next=L%d+%d", list, index + 1 + ListLeng(cur->u.lis));
	fprintf(fp, "},\n");
	*pindex = index + 1;
	for (cur = cur->u.lis; cur; cur = cur->next)
	    PrintMember(env, cur, list, pindex, fp);
	return;
    case FLOAT_ :
	fprintf(fp, ".u.dbl=%g,", cur->u.dbl);
	fprintf(fp, ".op=FLOAT_");
	break;
    default:
	execerror(env, "valid datatype", "PrintMember");
	break;
    }
    if (cur->next)
	fprintf(fp, ",.next=L%d+%d", list, index + 1);
    fprintf(fp, "},\n");
    *pindex = index + 1;
}

/*
    PrintList - print a list data structure.
*/
static int PrintList(pEnv env, Node *cur, FILE *fp)
{
    static int list;
    int leng, index;

    leng = ListLeng(cur);
    fprintf(fp, "static Node L%d[%d] = {\n", ++list, leng);
    for (index = 0; cur; cur = cur->next)
	PrintMember(env, cur, list, &index, fp);
    fprintf(fp, "};\n");
    return list;
}

/*
    printnode - print the instruction that pushes an item on the stack.
*/
void printnode(pEnv env, Node *node)
{
    Node *cur;
    char *name;
    int index, flags;

    switch (node->op) {
    case USR_ :
	index = node->u.num;
	if ((cur = dict_body(env, index)) == 0) {
	    name = dict_name(env, index);
	    fprintf(outfp, "PUSH_PTR(USR_, \"%s\");", name);
	} else {
	    flags = dict_flags(env, index);
	    name = dict_nickname(env, index);
	    if ((flags & (IS_BUILTIN | IS_DECLARED)) == 0) {
		flags |= IS_DECLARED;
		fprintf(declfp, "void do_%s(pEnv env);", name);
	    }
	    dict_setflags(env, index, flags | IS_USED);
	    fprintf(outfp, "PUSH_PTR(ANON_FUNCT_, do_%s);", name);
	}
	break;
    case ANON_FUNCT_ :
	fprintf(outfp, "PUSH_PTR(ANON_FUNCT_, do_%s,", procname(node->u.proc));
	break;
    case BOOLEAN_:
	fprintf(outfp, "PUSH_NUM(BOOLEAN_, %d);", node->u.num != 0);
	break;
    case CHAR_:
	fprintf(outfp, "PUSH_NUM(CHAR_, %d);", (int)node->u.num);
	break;
    case INTEGER_:
	fprintf(outfp, "PUSH_NUM(INTEGER_, %ld);", (long)node->u.num);
	break;
    case SET_:
	fprintf(outfp, "PUSH_NUM(SET_, %lu);", (unsigned long)node->u.set);
	break;
    case STRING_:
	name = PrintString(node->u.str);
	fprintf(outfp, "PUSH_PTR(STRING_, %s);", name);
	break;
    case LIST_:
	if (!node->u.lis)
	    fprintf(outfp, "PUSH_PTR(LIST_, 0);");
	else
	    fprintf(outfp, "PUSH_PTR(LIST_, L%d);",
		    PrintList(env, node->u.lis, outfp));
	break;
    case FLOAT_:
	fprintf(outfp, "PUSH_DBL(%g);", node->u.dbl);
	break;
    default:
	execerror(env, "valid datatype", "printnode");
	break;
    }
}

/*
    printstack - print instructions that recreate the stack at runtime.
*/
void printstack(pEnv env)
{
    for (env->stk = reverse(env->stk); env->stk; env->stk = env->stk->next)
	printnode(env, env->stk);
}

/*
    compile - print and clear the stack, execute a sequence of instructions
	      and print and clear the stack again.
*/
void compile(pEnv env, Node *node)
{
    printstack(env);
    exeterm(env, node);
    printstack(env);
}

/*
    declare - ensure that builtins become part of the compiled program.
*/
static void declare(pEnv env, FILE *fp)
{
    char *name;
    int i, j, leng, flags;

    leng = dict_size(env);
    for (i = 0; i < leng; i++) {
	flags = dict_flags(env, i);
	if ((flags & IS_ORIGINAL) == 0)
	    continue;
	if ((flags & IS_BUILTIN) == 0 || (flags & IS_USED) == 0) {
	    name = dict_nickname(env, i);
	    if (!strcmp(name, "quit"))
		continue;
	    fprintf(fp, "#define ");
	    for (j = 0; name[j]; j++)
		fputc(toupper(name[j]), fp);
	    fprintf(fp, "_X\n");
	    fprintf(fp, "#define ");
	    for (j = 0; name[j]; j++)
		fputc(toupper(name[j]), fp);
	    fprintf(fp, "_C\n");
	}
    }
}

/*
    finalise - output the final part of the compiled program.
*/
static void finalise(pEnv env)
{
    Node *body;
    char *name;
    int i, leng, flags, changed;

    fprintf(outfp, "\n/* finish */\nreturn 0; }");
    do {
	changed = 0;
	for (leng = dict_size(env), i = 0; i < leng; i++) {
	    flags = dict_flags(env, i);
	    if ((flags & IS_BUILTIN) || (flags & IS_USED) == 0)
		continue;
	    if ((body = dict_body(env, i)) == 0)
		continue;
	    if ((flags & IS_PRINTED) == 0) {
		dict_setflags(env, i, flags | IS_PRINTED);
		name = dict_nickname(env, i);
		if (body->op == USR_)
		    if (!strcmp(name, dict_nickname(env, body->u.num)))
			continue;
		changed = 1;
		fprintf(outfp, "void do_%s(pEnv env) {", name);
		compile(env, body);
		fprintf(outfp, "}");
	    }
	}
    } while (changed);
    printout(declfp);
    closeout();
    fprintf(declfp, "\ntable_t table[] = {");
    iterate_dict_and_write_struct(env, declfp);
    fprintf(declfp, "{ 0, \"\" } };\n");
    declare(env, declfp);
    fprintf(declfp, "#include \"interp.c\"\n");
}

/*
    initialise - initialise the output of the compiled program; also inialise
		 everything that is not available in compiled programs.
*/
void initialise(pEnv env)
{
    static int init;
    time_t t;

    if (init)
	return;
    init = 1;
    init_dict(env);
    if (!compiling)
	return;
    my_atexit(finalise);
    t = time(0);
    fprintf(declfp = stdout, "/*\n * generated %s */\n", ctime(&t));
    fprintf(declfp, "#define RUNTIME\n");
    fprintf(declfp, "#include \"runtime.h\"\n");
    initout();
    outfp = nextfile();
    fprintf(outfp, "int yyparse(pEnv env) {");
}
