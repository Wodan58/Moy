/*
    module  : primrec.c
    version : 1.15
    date    : 06/20/22
*/
#ifndef PRIMREC_C
#define PRIMREC_C

/**
primrec  :  X [I] [C]  ->  R
Executes I to obtain an initial value R0.
For integer X uses increasing positive integers to X, combines by C for new R.
For aggregate X uses successive members and combines by C for new R.
*/
#ifdef COMPILING
void put_primrec(pEnv env, Node *prog[2])
{
    fprintf(outfp, "{ /* PRIMREC */");
    fprintf(outfp, "int i, num = 0; Node *cur;");
    fprintf(outfp, "char *str, *volatile ptr; long set;");
    fprintf(outfp, "cur = env->stk; POP(env->stk);");
    fprintf(outfp, "switch (cur->op) {");
    fprintf(outfp, "case LIST_:");
    fprintf(outfp, "for (cur = cur->u.lis; cur; cur = cur->next, num++)");
    fprintf(outfp, "DUPLICATE(cur); break;");
    fprintf(outfp, "case STRING_:");
    fprintf(outfp, "ptr = str = cur->u.str;");
    fprintf(outfp, "for (num = strlen(str); *str; str++)");
    fprintf(outfp, "PUSH_NUM(CHAR_, *str); break;");
    fprintf(outfp, "case SET_:");
    fprintf(outfp, "set = cur->u.set;");
    fprintf(outfp, "for (num = i = 0; i < SETSIZE_; i++)");
    fprintf(outfp, "if (set & ((long)1 << i)) {");
    fprintf(outfp, "PUSH_NUM(INTEGER_, i); num++; } break;");
    fprintf(outfp, "case INTEGER_:");
    fprintf(outfp, "for (num = i = cur->u.num; i; i--)");
    fprintf(outfp, "PUSH_NUM(INTEGER_, i); break; }");
    compile(env, prog[0]);
    fprintf(outfp, "while (num--) {");
    compile(env, prog[1]);
    fprintf(outfp, "} }");
}
#endif

PRIVATE void do_primrec(pEnv env)
{
    long set;
    int i, num = 0;
    Node *prog[2], *cur;
    char *str, *volatile ptr;

    TWOPARAMS("primrec");
    TWOQUOTES("primrec");
    prog[1] = env->stk->u.lis;
    POP(env->stk);
    prog[0] = env->stk->u.lis;
    POP(env->stk);
    INSTANT(put_primrec);
    ONEPARAM("primrec");
    cur = env->stk;
    POP(env->stk);
    switch (cur->op) {
    case LIST_:
	for (cur = cur->u.lis; cur; cur = cur->next, num++)
	    DUPLICATE(cur);
	break;
    case STRING_:
	ptr = str = cur->u.str;
	for (num = strlen(str); *str; str++)
	    PUSH_NUM(CHAR_, *str);
	break;
    case SET_:
	set = cur->u.set;
	for (i = 0; i < SETSIZE_; i++)
	    if (set & ((long)1 << i)) {
		PUSH_NUM(INTEGER_, i);
		num++;
	    }
	break;
    case INTEGER_:
	for (i = num = cur->u.num; i; i--)
	    PUSH_NUM(INTEGER_, i);
	break;
    default:
	BADDATA("primrec");
	break;
    }
    exeterm(env, prog[0]);
    while (num--)
	exeterm(env, prog[1]);
}
#endif
