/*
    module  : compare.h
    version : 1.1
    date    : 06/20/22
*/
#ifndef COMPARE_H
#define COMPARE_H

int Compare(pEnv env, Node *first, Node *second)
{
    FILE *fp1, *fp2;
    int type1, type2;
    char *name1, *name2;
    double dbl, dbl1, dbl2;
    int64_t num, num1, num2;

    type1 = first->op;
    type2 = second->op;
    switch (type1) {
#ifdef COMPILING
    case USR_:
	name1 = dict_nickname(env, first->u.num);
        switch (type2) {
        case USR_:
	    name2 = dict_nickname(env, second->u.num);
            goto cmpstr;
        case ANON_FUNCT_:
            name2 = nickname(second->u.proc);
            goto cmpstr;
        case STRING_:
            name2 = second->u.str;
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
        }
        break;
#endif
    case ANON_FUNCT_:
	name1 = nickname(first->u.proc);
        switch (type2) {
#ifdef COMPILING
        case USR_:
	    name2 = dict_nickname(env, second->u.num);
            goto cmpstr;
#endif
        case ANON_FUNCT_:
            name2 = nickname(second->u.proc);
            goto cmpstr;
#ifndef COMPILING
	case USR_:
#endif
        case STRING_:
            name2 = second->u.str;
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
        }
        break;
    case BOOLEAN_:
        num1 = first->u.num;
        switch (type2) {
        case BOOLEAN_:
        case CHAR_:
        case INTEGER_:
            num2 = second->u.num;
            goto cmpnum;
        case FLOAT_:
            dbl1 = num1;
            dbl2 = second->u.dbl;
            goto cmpdbl;
        default:
            return 1; /* unequal */
        }
        break;
    case CHAR_:
        num1 = first->u.num;
        switch (type2) {
        case BOOLEAN_:
        case CHAR_:
        case INTEGER_:
            num2 = second->u.num;
            goto cmpnum;
        case FLOAT_:
            dbl1 = num1;
            dbl2 = second->u.dbl;
            goto cmpdbl;
        default:
            return 1; /* unequal */
        }
        break;
    case INTEGER_:
        num1 = first->u.num;
        switch (type2) {
        case BOOLEAN_:
        case CHAR_:
        case INTEGER_:
            num2 = second->u.num;
            goto cmpnum;
        case FLOAT_:
            dbl1 = num1;
            dbl2 = second->u.dbl;
            goto cmpdbl;
        default:
            return 1; /* unequal */
        }
        break;
    case SET_:
        num1 = first->u.set;
        switch (type2) {
        case SET_:
            num2 = second->u.set;
            goto cmpnum;
        default:
            return 1; /* unequal */
        }
        break;
#ifndef COMPILING
    case USR_:
#endif
    case STRING_:
        name1 = first->u.str;
        switch (type2) {
#ifdef COMPILING
        case USR_:
	    name2 = dict_nickname(env, second->u.num);
            goto cmpstr;
#endif
        case ANON_FUNCT_:
            name2 = nickname(second->u.proc);
            goto cmpstr;
#ifndef COMPILING
	case USR_:
#endif
        case STRING_:
            name2 = second->u.str;
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
        }
        break;
    case FLOAT_:
        dbl1 = first->u.dbl;
        switch (type2) {
        case BOOLEAN_:
        case CHAR_:
        case INTEGER_:
            dbl2 = second->u.num;
            goto cmpdbl;
        case FLOAT_:
            dbl2 = second->u.dbl;
            goto cmpdbl;
        default:
            return 1; /* unequal */
        }
        break;
    case FILE_:
        fp1 = first->u.fil;
        switch (type2) {
        case FILE_:
            fp2 = second->u.fil;
            return fp1 - fp2 < 0 ? -1 : fp1 - fp2 > 0;
        default:
            return 1; /* unequal */
        }
        break;
    default:
        return 1; /* unequal */
    }
cmpdbl:
    dbl = dbl1 - dbl2;
    return dbl < 0 ? -1 : dbl > 0;
cmpstr:
    num = strcmp(name1, name2);
    return num < 0 ? -1 : num > 0;
cmpnum:
    num = num1 - num2;
    return num < 0 ? -1 : num > 0;
}
#endif
