/*
    module  : filetime.c
    version : 1.14
    date    : 09/17/24
*/
#ifndef FILETIME_C
#define FILETIME_C

#include <sys/stat.h>

/**
Q0  OK  3160  filetime  :  DA  F  ->  T
[FOREIGN] T is the modification time of file F.
*/
void filetime_(pEnv env)
{
    FILE *fp;
    Node node;
    struct stat *buf;	/* struct stat is big */
    time_t mtime = 0;	/* modification time */

    PARM(1, STRTOD);
    node = vec_pop(env->stck);
    if ((fp = fopen(node.u.str, "r")) != 0) {
	buf = GC_malloc(sizeof(struct stat));
	if (fstat(fileno(fp), buf) >= 0)
	    mtime = buf->st_mtime;
	fclose(fp);
    }
    node.u.num = mtime;
    node.op = INTEGER_;
    vec_push(env->stck, node);
}
#endif
