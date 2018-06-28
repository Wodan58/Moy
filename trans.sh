#
#  Generate trans.c
#
if [ ! -f trans.c ]
then
echo creating trans.c
else
todo=0
for i in src/*.c
do
if [ $i -nt trans.c ]
then
todo=1
break
fi
done
if [ $todo -eq 0 ]
then
echo trans.c is up-to-date
exit
fi
echo updating trans.c
fi
for i in src/*.c
do
file=`basename $i`
name=`expr $file : '\(.*\)\.c'`
sed -n '/\/\*\*/ {
	N
	s/.*\n\(^[^ ]*\).*/{ "\1", "'$name'", do_'$name' },/
	P
}' <$i
done | sort >trans.c
