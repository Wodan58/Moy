#
#  Generate runtime.c and builtin.h
#
echo checking runtime.c and builtin.h
ls -1Q src/*.c | sed 's/^/#include /' >prims.tmp
if [ ! -f runtime.c ]
then
echo creating runtime.c and builtin.h
>runtime.c
fi
diff prims.tmp runtime.c
if [ $? -eq 0 ]
then
echo runtime.c and builtin.h are up-to-date
rm prims.tmp
else
echo updating runtime.c and builtin.h
mv prims.tmp runtime.c
sed 's/.*\//void do_/;s/\..*/(void);/' <runtime.c >builtin.h
fi
