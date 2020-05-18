#
#  module  : prims.sh
#  version : 1.3
#  date    : 03/28/20
#
#  Generate builtin.c and builtin.h
#
echo checking builtin.c and builtin.h
todo=0
ls -1Q src/*.c | sed 's/^/#include /' >prims.tmp
if [ ! -f builtin.c ]
then
  echo creating builtin.c and builtin.h
  todo=1
else
  diff prims.tmp builtin.c
  if [ $? -eq 0 ]
  then
    echo builtin.c and builtin.h are up-to-date
    rm prims.tmp
  else
    echo updating builtin.c and builtin.h
    todo=1
  fi
fi
if [ $todo -eq 1 ]
then
  rm -f builtin.c builtin.h
  mv prims.tmp builtin.c
  sed 's/.*\//void do_/;s/\..*/(void);/' <builtin.c >builtin.h
fi
