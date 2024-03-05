/*
    module  : localtime.c
    version : 1.8
    date    : 03/05/24
*/
#ifndef LOCALTIME_C
#define LOCALTIME_C

/**
Q0  OK  1700  localtime  :  DA  I  ->  T
Converts a time I into a list T representing local time:
[year month day hour minute second isdst yearday weekday].
Month is 1 = January ... 12 = December;
isdst is a Boolean flagging daylight savings/summer time;
weekday is 1 = Monday ... 7 = Sunday.
*/
void localtime_(pEnv env)
{
    static int daynums[] = { 7, 1, 2, 3, 4, 5, 6 };
    struct tm *t;
    time_t timval;
    Node node, temp;

    PARM(1, UNMKTIME);
    env->stck = pvec_pop(env->stck, &node);
    timval = node.u.num;
    t = localtime(&timval);
    temp.u.lis = pvec_init();
    node.u.num = daynums[t->tm_wday];
    node.op = INTEGER_;
    temp.u.lis = pvec_add(temp.u.lis, node);
    node.u.num = t->tm_yday;
    temp.u.lis = pvec_add(temp.u.lis, node);
    node.u.num = t->tm_isdst;
    node.op = BOOLEAN_;
    temp.u.lis = pvec_add(temp.u.lis, node);
    node.u.num = t->tm_sec;
    node.op = INTEGER_;
    temp.u.lis = pvec_add(temp.u.lis, node);
    node.u.num = t->tm_min;
    temp.u.lis = pvec_add(temp.u.lis, node);
    node.u.num = t->tm_hour;
    temp.u.lis = pvec_add(temp.u.lis, node);
    node.u.num = t->tm_mday;
    temp.u.lis = pvec_add(temp.u.lis, node);
    node.u.num = t->tm_mon + 1;
    temp.u.lis = pvec_add(temp.u.lis, node);
    node.u.num = t->tm_year + 1900;
    temp.u.lis = pvec_add(temp.u.lis, node);
    temp.op = LIST_;
    env->stck = pvec_add(env->stck, temp);
}
#endif
