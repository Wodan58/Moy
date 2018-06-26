#
#  Generate table.c
#
PATH=.:usr/local/wbin:$PATH
todo=0
for i in src/*.c
do
if [ $i -nt table.c ]
then
todo=1
break
fi
done
if [ $todo -eq 0 ]
then
echo table.c is up-to-date
exit
fi
for i in src/*.c
do
sed -n '/\/\*\*/ {
	N
	N
	N
	N
	N
	N
	N
	N
	s/[^\n]*\n\([^ ]*\)[ ]*:[ ]*\([^\n]*\)[ \n]*\([^*]*\)\*\/.*/{ @\1@, @\2@, @\3@ },/
	s/\n/\\n/g
	s/"/\\"/g
	s/@/"/g
	P
}' <$i
done | sort >table.c
