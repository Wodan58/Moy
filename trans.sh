#
#  module  : trans.sh
#  version : 1.1
#  date    : 06/29/18
#
#  Generate trans.c
#
echo checking trans.c
todo=0
if [ ! -f trans.c ]
then
  echo creating trans.c
  todo=1
else
  for i in src/*.c
  do
    if [ $i -nt trans.c ]
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
