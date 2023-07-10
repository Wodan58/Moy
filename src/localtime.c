/*
    module  : localtime.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef LOCALTIME_C
#define LOCALTIME_C

#ifdef WIN32
void localtime_r(time_t *t, struct tm *tm)
{
    *tm = *localtime(t);
}
#endif

/**
OK 1700  localtime  :  DA	I  ->  T
Converts a time I into a list T representing local time:
[year month day hour minute second isdst yearday weekday].
Month is 1 = January ... 12 = December;
isdst is a Boolean flagging daylight savings/summer time;
weekday is 1 = Monday ... 7 = Sunday.
*/
void localtime_(pEnv env)
{
    static int daynums[] = { 7, 1, 2, 3, 4, 5, 6 };
    struct tm t;
    time_t timval;
    Node node, temp;

    PARM(1, UNMKTIME);
    node = vec_pop(env->stck);
    timval = node.u.num;
    localtime_r(&timval, &t);
    vec_init(temp.u.lis);
    node.u.num = daynums[t.tm_wday];
    node.op = INTEGER_;
    vec_push(temp.u.lis, node);
    node.u.num = t.tm_yday;
    vec_push(temp.u.lis, node);
    node.u.num = t.tm_isdst;
    node.op = BOOLEAN_;
    vec_push(temp.u.lis, node);
    node.u.num = t.tm_sec;
    node.op = INTEGER_;
    vec_push(temp.u.lis, node);
    node.u.num = t.tm_min;
    vec_push(temp.u.lis, node);
    node.u.num = t.tm_hour;
    vec_push(temp.u.lis, node);
    node.u.num = t.tm_mday;
    vec_push(temp.u.lis, node);
    node.u.num = t.tm_mon + 1;
    vec_push(temp.u.lis, node);
    node.u.num = t.tm_year + 1900;
    vec_push(temp.u.lis, node);
    temp.op = LIST_;
    vec_push(env->stck, temp);
}
#endif
