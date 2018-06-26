#
#  Generate parse.h
#
PATH=.:usr/local/wbin:$PATH
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
