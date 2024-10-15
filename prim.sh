#
#   module  : prim.sh
#   version : 1.8
#   date    : 10/11/24
#
#   Generate builtin.c and builtin.h
#   The directory needs to be given as parameter.
#
echo checking builtin.c and builtin.h
todo=0
ls $1/src/*.c | sed 's/^/#include "/;s/$/"/' >builtin.tmp
if [ ! -f $1/builtin.c -o ! -f $1/builtin.h ]
then
  echo creating builtin.c and builtin.h
  todo=1
else
  diff $1/builtin.c builtin.tmp
  if [ $? -eq 0 ]
  then
    echo builtin.c and builtin.h are up-to-date
    rm -f builtin.tmp
  else
    echo updating builtin.c and builtin.h
    todo=1
  fi
fi
if [ $todo -eq 1 ]
then
  rm -f $1/builtin.c $1/builtin.h $1/tabl.c
  mv builtin.tmp $1/builtin.c
  sed 's/.*\//void /;s/\..*/_(pEnv env);/' <$1/builtin.c >$1/builtin.h
fi
