/*
    module  : quit.c
    version : 1.1
    date    : 04/23/16
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "globals1.h"

PUBLIC void abort_(void)
{
    exit(1);
}

PUBLIC void quit_(void)
{
    exit(0);
}
