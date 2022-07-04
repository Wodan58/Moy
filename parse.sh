#
#   module  : parse.sh
#   version : 1.4
#   date    : 06/16/22
#
#   Generate parse.h
#
echo checking parse.h
todo=0
if [ ! -f $1/parse.h ]
then
  echo creating parse.h
  todo=1
elif [ $1/parse.y -nt $1/parse.h ]
then
  echo updating parse.h
  todo=1
else
  echo parse.h is up-to-date
fi
if [ $todo -eq 1 ]
then
rm -f $1/parse.c $1/parse.h
$*
fi
