#
#   module  : tabl.sh
#   version : 1.2
#   date    : 07/17/23
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
  for i in $1/src/*.c
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
	s/[^\n]*\n\([^ \t]*\)[ \t]*\([^ \t]*\)[ \t]*\([^ \t]*\)[ \t]*:[ \t]*\([DANUP]*\)[ \t]*\([^\n]*\)[ \n]*\([^*]*\)\*\/.*/\/* \2 *\/ { \1, @\3@, '$j'_, @\4@, @\5@, @\6@ },/
	s/\n/\\n/g
	s/"/\\"/g
	s/@/"/g
	P
  }' <$i
done | sort >$1/tabl.c
touch $1/eval.c
