/*
    module  : construct.c
    version : 1.17
    date    : 06/20/22
*/
#ifndef CONSTRUCT_C
#define CONSTRUCT_C

/**
construct  :  [P] [[P1] [P2] ..]  ->  R1 R2 ..
Saves state of stack and then executes [P].
Then executes each [Pi] to give Ri pushed onto saved stack.
*/
#ifdef COMPILING
void put_construct(pEnv env, Node *prog[2])
{
    Node *cur;

    fprintf(outfp, "{ /* CONSTRUCT */");
    fprintf(outfp, "Node *save[2];");
    fprintf(outfp, "save[0] = env->stk;");
    compile(env, prog[0]);
    fprintf(outfp, "save[1] = env->stk;");
    for (cur = prog[1]; cur; cur = cur->next) {
	fprintf(outfp, "env->stk = save[1];");
	compile(env, cur->u.lis);
	fprintf(outfp,"save[0] = newnode(env->stk->op, env->stk->u, save[0]);");
    }
    fprintf(outfp, "env->stk = save[0]; }");
}
#endif

PRIVATE void do_construct(pEnv env)
{
    Node *prog[2], *cur, *save[2];

    TWOPARAMS("construct");
    TWOQUOTES("construct");
    prog[1] = env->stk->u.lis;
    POP(env->stk);
    prog[0] = env->stk->u.lis;
    POP(env->stk);
    INSTANT(put_construct);
    save[0] = env->stk;		/* save old stack */
    exeterm(env, prog[0]);
    save[1] = env->stk;		/* save new stack */
    for (cur = prog[1]; cur; cur = cur->next) {
	env->stk = save[1];	/* restore new stack */
	exeterm(env, cur->u.lis);
	save[0] = newnode(env->stk->op, env->stk->u, save[0]);	/* result */
    }
    env->stk = save[0];
}
#endif
