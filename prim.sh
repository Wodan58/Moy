#
#   module  : prim.sh
#   version : 1.7
#   date    : 08/31/24
#
#   Generate prim.c and prim.h
#   The directory needs to be given as parameter.
#
echo checking prim.c and prim.h
todo=0
ls $1/src/*.c | sed 's/^/#include "/;s/$/"/' >prim.tmp
if [ ! -f $1/prim.c -o ! -f $1/prim.h ]
then
  echo creating prim.c and prim.h
  todo=1
else
  diff $1/prim.c prim.tmp
  if [ $? -eq 0 ]
  then
    echo prim.c and prim.h are up-to-date
    rm prim.tmp
  else
    echo updating prim.c and prim.h
    todo=1
  fi
fi
if [ $todo -eq 1 ]
then
  rm -f $1/prim.c $1/prim.h $1/tabl.c
  mv prim.tmp $1/prim.c
  sed 's/.*\//void /;s/\..*/_(pEnv env);/' <$1/prim.c >$1/prim.h
fi
