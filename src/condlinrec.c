/*
    module  : condlinrec.c
    version : 1.19
    date    : 06/20/22
*/
#ifndef CONDLINREC_C
#define CONDLINREC_C

/**
condlinrec  :  [ [C1] [C2] .. [D] ]  ->  ...
Each [Ci] is of the form [[B] [T]] or [[B] [R1] [R2]].
Tries each B. If that yields true and there is just a [T], executes T and exit.
If there are [R1] and [R2], executes R1, recurses, executes R2.
Subsequent case are ignored. If no B yields true, then [D] is used.
It is then of the form [[T]] or [[R1] [R2]]. For the former, executes T.
For the latter executes R1, recurses, executes R2.
*/
#ifdef COMPILING
void put_condnestrec(pEnv env, Node *root)
{
    static int ident;
    FILE *oldfp;
    Node *cur, *list, *node;

    fprintf(declfp, "void condnestrec_%d(pEnv env);", ++ident);
    fprintf(outfp, "condnestrec_%d(env);", ident);
    oldfp = outfp;
    outfp = nextfile();
    fprintf(outfp, "void condnestrec_%d(pEnv env) {", ident);
    fprintf(outfp, "Node *save; int num;");
    for (cur = root; cur->next; cur = cur->next) {
	fprintf(outfp, "save = env->stk;");
	list = cur->u.lis->u.lis;
	compile(env, list);
	fprintf(outfp, "num = env->stk->u.num; env->stk = save; if (num) {");
	node = cur->u.lis->next;
	compile(env, node->u.lis);
	while ((node = node->next) != 0) {
	    fprintf(outfp, "condnestrec_%d(env);", ident);
	    compile(env, node->u.lis);
	}
	fprintf(outfp, "return; }");
    }
    cur = cur->u.lis;
    compile(env, cur->u.lis);
    while ((cur = cur->next) != 0) {
	fprintf(outfp, "condnestrec_%d(env);", ident);
	compile(env, cur->u.lis);
    }
    fprintf(outfp, "}");
    closefile(outfp);
    outfp = oldfp;
}
#endif

PRIVATE void condnestrec(pEnv env, Node *root)
{
    int num = 0;
    Node *cur, *save;

    for (cur = root; cur->next; cur = cur->next) {
	save = env->stk;
	exeterm(env, cur->u.lis->u.lis);
	num = env->stk->u.num;
	env->stk = save;
	if (num)
	    break;
    }
    cur = num ? cur->u.lis->next : cur->u.lis;
    exeterm(env, cur->u.lis);
    while ((cur = cur->next) != 0) {
	condnestrec(env, root);
	exeterm(env, cur->u.lis);
    }
}

PRIVATE void do_condlinrec(pEnv env)
{
    Node *prog;

    ONEPARAM("condlinrec");
    LIST("condlinrec");
    prog = env->stk->u.lis;
    CHECKEMPTYLIST(prog, "condlinrec");
    POP(env->stk);
    INSTANT(put_condnestrec);
    condnestrec(env, prog);
}
#endif
