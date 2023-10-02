/*
    module  : decode.h
    version : 1.5
    date    : 10/02/23
*/
#ifndef DECODE_H
#define DECODE_H

PUBLIC void decode(Node node, struct tm *t)
{
    int i;
    Node temp;

    memset(t, 0, sizeof(struct tm));
    for (i = pvec_cnt(node.u.lis) - 1; i >= 0; i--) {
	temp = pvec_nth(node.u.lis, i);
	switch (i) {
	case 8: t->tm_year  = temp.u.num - 1900; break;
	case 7: t->tm_mon   = temp.u.num - 1; break;
	case 6: t->tm_mday  = temp.u.num; break;
	case 5: t->tm_hour  = temp.u.num; break;
	case 4: t->tm_min   = temp.u.num; break;
	case 3: t->tm_sec   = temp.u.num; break;
	case 2: t->tm_isdst = temp.u.num; break;
	case 1: t->tm_yday  = temp.u.num; break;
	case 0: t->tm_wday  = temp.u.num % 7; break;
	}
    }
}
#endif
