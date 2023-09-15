/*
    module  : gmtime.c
    version : 1.6
    date    : 09/15/23
*/
#ifndef GMTIME_C
#define GMTIME_C

/**
OK 1710  gmtime  :  DA	I  ->  T
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
    node = lst_pop(env->stck);
    timval = node.u.num;
    t = gmtime(&timval);
    lst_init(temp.u.lis);
    node.u.num = daynums[t->tm_wday];
    node.op = INTEGER_;
    lst_push(temp.u.lis, node);
    node.u.num = t->tm_yday;
    lst_push(temp.u.lis, node);
    node.u.num = t->tm_isdst;
    node.op = BOOLEAN_;
    lst_push(temp.u.lis, node);
    node.u.num = t->tm_sec;
    node.op = INTEGER_;
    lst_push(temp.u.lis, node);
    node.u.num = t->tm_min;
    lst_push(temp.u.lis, node);
    node.u.num = t->tm_hour;
    lst_push(temp.u.lis, node);
    node.u.num = t->tm_mday;
    lst_push(temp.u.lis, node);
    node.u.num = t->tm_mon + 1;
    lst_push(temp.u.lis, node);
    node.u.num = t->tm_year + 1900;
    lst_push(temp.u.lis, node);
    temp.op = LIST_;
    lst_push(env->stck, temp);
}
#endif
