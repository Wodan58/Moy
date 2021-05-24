#
#   module  : table.sh
#   version : 1.3
#   date    : 04/28/21
#
#   Generate table.c
#
echo checking table.c
todo=0
if [ ! -f table.c ]
then
  echo creating table.c
  todo=1
else
  for i in src/*.c gui/*.c
  do
    if [ $i -nt table.c ]
    then
      echo updating table.c
      todo=1
      break
    fi
  done
fi
if [ $todo -eq 0 ]
then
  echo table.c is up-to-date
  exit
fi
rm -f table.c
for i in src/*.c gui/*.c
do
  sed -n '/\/\*\*/ {
	N
	N
	N
	N
	N
	N
	N
	N
	s/[^\n]*\n\([^ ]*\)[ ]*:[ ]*\([^\n]*\)[ \n]*\([^*]*\)\*\/.*/{ @\1@, @\2@, @\3@ },/
	s/\n/\\n/g
	s/"/\\"/g
	s/@/"/g
	P
  }' <$i
done | sort >table.c
