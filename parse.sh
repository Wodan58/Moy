#
#  Generate parse.h
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
$*
fi
