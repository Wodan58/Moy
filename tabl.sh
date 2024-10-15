#
#   module  : tabl.sh
#   version : 1.9
#   date    : 10/15/24
#
#   Generate tabl.c
#   The directory needs to be given as parameter.
#
echo checking tabl.c
todo=0
if [ ! -f $1/tabl.c ]
then
  echo creating tabl.c
  todo=1
else
  for i in $1/src/*.c $1/builtin.c $1/builtin.h
  do
    if [ $i -nt $1/tabl.c ]
    then
      echo updating tabl.c
      todo=1
      break
    fi
  done
fi
if [ $todo -eq 0 ]
then
  echo tabl.c is up-to-date
  exit
fi
rm -f $1/tabl.c
for i in $1/src/*.c
do
  j=`basename $i`
  j=`expr $j : '\(.*\)\.c'`
  sed -n '/\/\*\*/ {
	N
	N
	N
	N
	N
	N
	N
	N
	s/[^\n]*\n\([^ \t]*\)[ \t]*\([^ \t]*\)[ \t]*\([^ \t]*\)[ \t]*\([^ \t]*\)[ \t]*:[ \t]*\([DANUPQ]*\)[ \t]*\([^\n]*\)[ \n]*\([^*]*\)\*\/.*/\/* \3 *\/ { \1, \2, @\4@, '$j'_, @\5@, @\6@, @\7@ },/
	s/\n/\\n/g
	s/"/\\"/g
	s/@/"/g
	P
  }' <$i
done | sort >$1/tabl.c
touch $1/otab.c
