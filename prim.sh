#
#   module  : prim.sh
#   version : 1.4
#   date    : 10/02/23
#
#   Generate prim.c and prim.h
#   The directory needs to be given as parameter.
#
echo checking prim.c and prim.h
todo=0
ls -1Q $1/src/*.c | sed 's/^/#include /' >prim.tmp
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
  rm -f $1/prim.c $1/prim.h
  mv prim.tmp $1/prim.c
  sed 's/.*\//void /;s/\..*/_(pEnv env);/' <$1/prim.c >$1/prim.h
  if [ -f $1/otab.c ]
  then
    touch $1/otab.c
  fi
fi
