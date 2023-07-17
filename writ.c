/*
 *  module  : writ.c
 *  version : 1.5
 *  date    : 07/17/23
 */
#include "globals.h"

/*
    writefactor - print a factor in readable format to stdout.
*/
PUBLIC void writefactor(pEnv env, Node node)
{
    int i;
    char *ptr;

/*
    This cannot happen. writefactor has a small number of customers: writeterm,
    main, put, fput. They all check that the stack is not empty, so this code
    only serves as a reminder for future customers.
*/
#if 0
    if (!n)
        execerror("non-empty stack", "print");
#endif
    switch (node.op) {
    case USR_:
    case USR_PRIME_:
        printf("%s", sym_at(env->symtab, node.u.ent).name);
        if (node.op == USR_PRIME_)
            putchar('\'');
        break;
    case ANON_FUNCT_:
    case ANON_PRIME_:
        printf("%s", opername(node.u.proc));
        if (node.op == ANON_PRIME_)
            putchar('\'');
        break;
    case BOOLEAN_:
        printf("%s", node.u.num ? "true" : "false");
        break;
    case CHAR_:
        if (node.u.num >= 8 && node.u.num <= 13)
            printf("'\\%c", "btnvfr"[node.u.num - 8]);
        else
            printf("'%c", (int)node.u.num);
        break;
    case INTEGER_:
	printf("%" PRId64, node.u.num);
        break;
    case SET_:
        putchar('{');
        for (i = 0; i < SETSIZE; i++)
            if (node.u.set & ((int64_t)1 << i)) {
                printf("%d", i);
                node.u.set &= ~((int64_t)1 << i);
                if (node.u.set)
                    putchar(' ');
            }
        putchar('}');
        break;
    case STRING_:
        putchar('"');
        for (ptr = node.u.str; ptr && *ptr; ptr++) {
            if (*ptr >= 8 && *ptr <= 13)
                printf("\\%c", "btnvfr"[*ptr - 8]);
            else
                putchar(*ptr);
        }
        putchar('"');
        break;
#if 0
    case LIST_:
        putchar('[');
        writeterm(env, node.u.lis);
        putchar(']');
        break;
#endif
    case FLOAT_:
        printf("%g", node.u.dbl);
        break;
    case FILE_:
        if (!node.u.fil)
            printf("file:NULL");
        else if (node.u.fil == stdin)
            printf("file:stdin");
        else if (node.u.fil == stdout)
            printf("file:stdout");
        else if (node.u.fil == stderr)
            printf("file:stderr");
        else
            printf("file:%p", node.u.fil);
        break;
#if 0
    default:
        yyerror(env, "a factor cannot begin with this symbol");
#endif
    }
}

/*
    spacing - write a space character, except after [ or before ].
*/
PRIVATE void spacing(NodeList *stack, Node node)
{
    if (node.op == CHAR_ && node.u.num == '[') /* inspect preceding node */
        ;
    else if (vec_size(stack)) { /* inspect following node */
        node = vec_back(stack);
        if (node.op == CHAR_ && (node.u.num == '[' || node.u.num == ']'))
            ;
        else
            putchar(' ');
    }
}

/*
    writing - print from a stack, used by writeterm and writestack.
*/
PRIVATE void writing(pEnv env, NodeList *stack)
{
    int i, j;
    Node node, temp;

    while (vec_size(stack)) {
        node = vec_pop(stack);
        if (node.op != LIST_) {
            if (node.op == CHAR_ && (node.u.num == '[' || node.u.num == ']'))
                putchar((int)node.u.num);
            else 
                writefactor(env, node);
            spacing(stack, node);
        } else {
            temp.u.num = ']';
            temp.op = CHAR_;
            vec_push(stack, temp);
            for (i = 0, j = vec_size(node.u.lis); i < j; i++) {
                temp = vec_at(node.u.lis, i);
                vec_push(stack, temp);
            }            
            temp.u.num = '[';
            temp.op = CHAR_;
            vec_push(stack, temp);
        }
    }
}

/*
    writeterm - print the contents of a list in readable format to stdout.
*/
PUBLIC void writeterm(pEnv env, NodeList *list)
{
    Node node;
    NodeList *stack = 0;
    int i, j = vec_size(list);

    if (j)
        vec_init(stack);
    for (i = 0; i < j; i++) {
        node = vec_at(list, i);
        vec_push(stack, node);
    }
    writing(env, stack);
}

/*
    writestack - print the contents of the stack in readable format to stdout.
*/
#ifdef TRACING
PUBLIC void writestack(pEnv env, NodeList *list)
{
    Node node;
    NodeList *stack = 0;
    int i, j = vec_size(list);

    if (j)
        vec_init(stack);
    for (i = j - 1; i >= 0; i--) {
        node = vec_at(list, i);
        vec_push(stack, node);
    }
    writing(env, stack);
}
#endif
