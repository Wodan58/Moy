/*
    module  : gmtime.c
    version : 1.9
    date    : 09/17/24
*/
#ifndef GMTIME_C
#define GMTIME_C

/**
Q0  OK  1710  gmtime  :  DA  I  ->  T
Converts a time I into a list T representing universal time:
[year month day hour minute second isdst yearday weekday].
Month is 1 = January ... 12 = December;
isdst is false; weekday is 1 = Monday ... 7 = Sunday.
*/
void gmtime_(pEnv env)
{
    static int daynums[] = { 7, 1, 2, 3, 4, 5, 6 };
    struct tm *t;
    time_t timval;
    Node node, temp;

    PARM(1, UNMKTIME);
    node = vec_pop(env->stck);
    timval = node.u.num;
    t = gmtime(&timval);
    vec_init(temp.u.lis);
    node.u.num = daynums[t->tm_wday];
    node.op = INTEGER_;
    vec_push(temp.u.lis, node);
    node.u.num = t->tm_yday;
    vec_push(temp.u.lis, node);
    node.u.num = t->tm_isdst;
    node.op = BOOLEAN_;
    vec_push(temp.u.lis, node);
    node.u.num = t->tm_sec;
    node.op = INTEGER_;
    vec_push(temp.u.lis, node);
    node.u.num = t->tm_min;
    vec_push(temp.u.lis, node);
    node.u.num = t->tm_hour;
    vec_push(temp.u.lis, node);
    node.u.num = t->tm_mday;
    vec_push(temp.u.lis, node);
    node.u.num = t->tm_mon + 1;
    vec_push(temp.u.lis, node);
    node.u.num = t->tm_year + 1900;
    vec_push(temp.u.lis, node);
    temp.op = LIST_;
    vec_push(env->stck, temp);
}
#endif
