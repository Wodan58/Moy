#
#   module  : parse.sh
#   version : 1.3
#   date    : 04/28/21
#
#   Generate parse.h
#
echo checking parse.h
todo=0
if [ ! -f parse.h ]
then
  echo creating parse.h
  todo=1
elif [ parse.y -nt parse.h ]
then
  echo updating parse.h
  todo=1
else
  echo parse.h is up-to-date
fi
if [ $todo -eq 1 ]
then
rm -f parse.c parse.h
$*
fi
