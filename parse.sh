#
#  Generate parse.h
#
PATH=.:usr/local/wbin:$PATH
if [ parse.y -nt parse.h ]
then
bison -doparse.c parse.y
else
echo parse.h is up-to-date
fi
