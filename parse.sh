#
#  Generate parse.h
#
PATH=.:usr/local/wbin:$PATH
if [ parse.y -nt parse.h ]
then
echo Building parse.h
echo $*
$*
else
echo parse.h is up-to-date
fi
