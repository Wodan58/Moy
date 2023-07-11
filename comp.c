/*
    module  : comp.c
    version : 1.2
    date    : 07/11/23
*/
#include "globals.h"

/*
    BOOLEAN, CHAR, INTEGER, SET, FLOAT are lumped together allowing
    numerical compare; USR, ANON_FUNCT, STRING are lumped together allowing
    string compare; FILE can only be compared with FILE; LIST cannot be
    compared with anything.
*/
PUBLIC int Compare(pEnv env, Node first, Node second)
{
    FILE *fp1, *fp2;
    char *name1, *name2;
    double dbl, dbl1, dbl2;
    long num, num1 = 0, num2 = 0;

    switch (first.op) {
    case USR_:
        name1 = sym_at(env->symtab, first.u.ent).name;
        switch (second.op) {
        case USR_:
            name2 = sym_at(env->symtab, second.u.ent).name;
            goto cmpstr;
        case ANON_FUNCT_:
            name2 = opername(second.u.proc);
            goto cmpstr;
        case BOOLEAN_:
        case CHAR_:
        case INTEGER_:
        case SET_:
        case LIST_:
        case FLOAT_:
        case FILE_:
        default:
            return 1; /* unequal */
        case STRING_:
            name2 = second.u.str;
            goto cmpstr;
        }
        break;
    case ANON_FUNCT_:
        name1 = opername(first.u.proc);
        switch (second.op) {
        case USR_:
            name2 = sym_at(env->symtab, second.u.ent).name;
            goto cmpstr;
        case ANON_FUNCT_:
            name2 = opername(second.u.proc);
            goto cmpstr;
        case BOOLEAN_:
        case CHAR_:
        case INTEGER_:
        case SET_:
        case LIST_:
        case FLOAT_:
        case FILE_:
        default:
            return 1; /* unequal */
        case STRING_:
            name2 = second.u.str;
            goto cmpstr;
        }
        break;
    case BOOLEAN_:
        num1 = first.u.num;
        switch (second.op) {
        case BOOLEAN_:
        case CHAR_:
        case INTEGER_:
	case SET_:
            num2 = second.u.num;
            goto cmpnum;
        case FLOAT_:
            dbl1 = num1;
            dbl2 = second.u.dbl;
            goto cmpdbl;
        default:
            return 1; /* unequal */
        }
        break;
    case CHAR_:
        num1 = first.u.num;
        switch (second.op) {
        case BOOLEAN_:
        case CHAR_:
        case INTEGER_:
	case SET_:
            num2 = second.u.num;
            goto cmpnum;
        case FLOAT_:
            dbl1 = num1;
            dbl2 = second.u.dbl;
            goto cmpdbl;
        default:
            return 1; /* unequal */
        }
        break;
    case INTEGER_:
        num1 = first.u.num;
        switch (second.op) {
        case BOOLEAN_:
        case CHAR_:
        case INTEGER_:
	case SET_:
            num2 = second.u.num;
            goto cmpnum;
        case FLOAT_:
            dbl1 = num1;
            dbl2 = second.u.dbl;
            goto cmpdbl;
        default:
            return 1; /* unequal */
        }
        break;
    case SET_:
        num1 = first.u.num;
        num2 = second.u.num;
        goto cmpnum;
    case STRING_:
        name1 = first.u.str;
        switch (second.op) {
        case USR_:
            name2 = sym_at(env->symtab, second.u.ent).name;
            goto cmpstr;
        case ANON_FUNCT_:
            name2 = opername(second.u.proc);
            goto cmpstr;
        case BOOLEAN_:
        case CHAR_:
        case INTEGER_:
        case SET_:
        case LIST_:
        case FLOAT_:
        case FILE_:
        default:
            return 1; /* unequal */
        case STRING_:
            name2 = second.u.str;
            goto cmpstr;
        }
        break;
    case LIST_:
        if (second.op == SET_) {
            num1 = first.u.num;
            num2 = second.u.num;
            goto cmpnum;
        }
        return 1; /* unequal */
        break;
    case FLOAT_:
        dbl1 = first.u.dbl;
        switch (second.op) {
        case BOOLEAN_:
        case CHAR_:
        case INTEGER_:
            dbl2 = second.u.num;
            goto cmpdbl;
        case SET_:
            num1 = first.u.num;
            num2 = second.u.num;
            goto cmpnum;
        case FLOAT_:
            dbl2 = second.u.dbl;
            goto cmpdbl;
        default:
            return 1; /* unequal */
        }
        break;
    case FILE_:
        fp1 = first.u.fil;
        switch (second.op) {
        case FILE_:
            fp2 = second.u.fil;
            return fp1 - fp2 < 0 ? -1 : fp1 - fp2 > 0;
        default:
            return 1; /* unequal */
        }
    }
cmpnum:
    num = num1 - num2;
    return num < 0 ? -1 : num > 0;
cmpdbl:
    dbl = dbl1 - dbl2;
    return dbl < 0 ? -1 : dbl > 0;
cmpstr:
    num = strcmp(name1, name2);
    return num < 0 ? -1 : num > 0;
}
