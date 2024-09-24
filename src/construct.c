/*
    module  : construct.c
    version : 1.10
    date    : 09/17/24
*/
#ifndef CONSTRUCT_C
#define CONSTRUCT_C

/**
Q2  OK  2470  construct  :  DDP  [P] [[P1] [P2] ..]  ->  R1 R2 ..
Saves state of stack and then executes [P].
Then executes each [Pi] to give Ri pushed onto saved stack.
*/
void construct_(pEnv env)
{	/* [P] [[P1] [P2] ..] -> X1 X2 ..	*/
    int i, j;
    unsigned size1, size2;
    Node first, second, node;

    PARM(2, WHILE);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    code(env, unstack_);
    size2 = vec_size(env->prog);
    /*
	save the old stack; this will become the new stack
    */
    vec_copy_count(node.u.lis, env->stck, vec_size(env->stck));
    node.op = LIST_;
    prime(env, node);
    size1 = vec_size(env->prog);
    /*
	the new stack after the first program needs to be saved
    */
    code(env, id_);
    /*
	each of the programs in the construct need to be executed
    */
    for (i = 0, j = vec_size(second.u.lis); i < j; i++) {
	/*
	    the new stack is restored
	*/
	code(env, unstack_);
	/*
	    the location where the new stack was saved needs to be pushed
	*/
	push(env, size1);
	/*
	    the new stack is pushed on the data stack as a list
	*/
	code(env, spush_);
	/*
	    the location where the old stack was saved needs to be pushed
	*/
	push(env, size2);
	/*
	    the result on top of the stack is added to the old stack
	*/
	code(env, push_);
        node = vec_at(second.u.lis, i);
	prog(env, node.u.lis);
    }
    /*
	the location where the new stack is saved needs to be pushed
    */
    push(env, size1);
    /*
	the new stack is then saved at a location in the code stack
    */
    code(env, cpush_);
    /*
	this new stack first needs to be pushed as a list
    */
    code(env, stack_);
    /*
	the first program is executed
    */
    prog(env, first.u.lis);
}
#endif
