echo Timing all implementations ...
echo fib
time ./fib
echo fib1
time ./fib1
echo fib3
time ./fib3
echo fib4
time ./fib5
echo gcd
time ./gcd1 24 54
time ./gcd3 24 54
time ./gcd5 24 54
echo test
time ./test1
time ./test3
time ./test5
echo jp-joytst
time ./jp-joytst1
time ./jp-joytst5
echo flatjoy
time ./flatjoy1
time ./flatjoy3			# segment fault
time ./flatjoy5
echo jp-reprodtst
time ./jp-reprodtst1
time ./jp-reprodtst3
time ./jp-reprodtst5
echo modtst
time ./modtst1			# error: two parameters needed for +
time ./modtst3
time ./modtst5			# error: two parameters needed for +
echo jp-nestrec
time ./jp-nestrec1
time ./jp-nestrec3
time ./jp-nestrec5
echo laztst
time ./laztst1
time ./laztst3
time ./laztst5
echo joytut
time ./joytut1 <joytut.inp
time ./joytut2 <joytut.inp
time ./joytut4 <joytut.inp
echo jp-church
time ./jp-church1
time ./jp-church3
time ./jp-church5
echo grmtst
time ./grmtst1
time ./grmtst3
time ./grmtst5
echo mtrtst
time ./mtrtst1
time ./mtrtst3
time ./mtrtst5
echo reptst
time ./reptst1
time ./reptst3
time ./reptst5
echo tutorial
time ./tutorial1
time ./tutorial3
time ./tutorial5
echo symtst
time ./symtst1
time ./symtst3
time ./symtst5
echo plgtst
time ./plgtst1
time ./plgtst3
time ./plgtst5
echo lsptst
time ./lsptst1 <lsptst.inp
time ./lsptst2 <lsptst.inp	# segment fault
time ./lsptst4 <lsptst.inp
