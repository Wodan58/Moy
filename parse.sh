#
#  Generate parse.h
#
echo checking parse.h
if [ ! -f parse.h ]
then
echo creating parse.h
$*
elif [ parse.y -nt parse.h ]
then
echo updating parse.h
$*
else
echo parse.h is up-to-date
fi
