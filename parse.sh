#
#  Generate parse.h
#
PATH=.:usr/local/wbin:$PATH
if [ $3 -nt parse.h ]
then
$*
else
echo parse.h is up-to-date
fi
