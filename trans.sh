#
#   module  : trans.sh
#   version : 1.4
#   date    : 06/16/22
#
#   Generate trans.c
#
echo checking trans.c
todo=0
if [ ! -f $1/trans.c ]
then
  echo creating trans.c
  todo=1
else
  for i in $1/src/*.c
  do
    if [ $i -nt $1/trans.c ]
    then
      echo updating trans.c
      todo=1
      break
    fi
  done
fi
if [ $todo -eq 0 ]
then
  echo trans.c is up-to-date
  exit
fi
rm -f $1/trans.c
for i in $1/src/*.c
do
  file=`basename $i`
  name=`expr $file : '\(.*\)\.c'`
  sed -n '/\/\*\*/ {
	N
	s/.*\n\(^[^ ]*\).*/{ "\1", "'$name'", do_'$name' },/
	P
  }' <$i
done | sort >$1/trans.c
touch $1/dict.c
