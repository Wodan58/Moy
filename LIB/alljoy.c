d_rem d_look d_differ d_union d_add d_null d_new r_bs_delete1 
r_bs_insert1 r_bs_member r_bs_differ r_bs_union bs_delete bs_insert 
bs_member bs_differ bs_union bs_new t_rem t_front t_null t_add t_reset 
t_new q_rem q_front q_addl q_add q_null q_new st_pull st_pop st_top 
st_null st_push st_new fatal2 MTRLIB m-print mm-2bin-m mm-mul-m 
mm-add-m mm-bin-m ms-cbin-m ms-bin-m sm-bin-m m-transpose-m mm-horcat-m 
mm-vercat-m mm-samedimensions mm-conformable m-dimensions vv-bin-m 
v-e-diag-m v-zdiag-m v-1col-m v-1row-m vv-2bin-s vv-bin-v 
vv-comformable vs-cbin-v vs-bin-v v-invert-v v-negate-v sv-bin-v 
n-e-vector vv-samesize TUTLIB toc-do-sec0-loop toc-repeat-sections 
toc-do-section toc-ask-for-section toc-do-section0 toc-one-heading 
toc-all-headings toc-of-tutorial put-stats ini-stats expecting-from 
expecting get-quote get-list get-integer praise pausing pause LAZLIB 
Squares Ones Powers-of-2 Odds Evens Positives Naturals Filter Map 
From-by From-to-by From-to From Take Size N-th Drop Third Second Cons 
Uncons Rest First Null LSPLIB lisp EXIT l-prompt y RECFOLDR tern l2 l1 
FOLDR2 FOLDL bin ini lis lib0 FOLDR LIST NULL ATOM EQ CONS CDR CAR 
apply DEFUN DEF eval IF CLOSURE LAMBDA GRMLIB prs-count 
prs-list-residues prs-string-residues prs-test parse prs-trace 
gen-accumulate gen-putchars-sp-step gen-putchars-step gen-put-step 
gen-put gen-trace-default epsilon generate gen-trace | $ ? SYMLIB 
j2f-reverse j2f-forwards Min2Inf Min2Tre Min2Rev Min2Pol Min2Cam 
Inf2Tre Inf2Rev Inf2Pol Inf2Cam Cam2Inf Cam2Tre Cam2Rev Cam2Pol Rev2Tre 
Rev2Inf Rev2Cam Rev2Pol Pol2Tre Pol2Inf Pol2Cam Pol2Rev bin3ops bin2ops 
bin1ops binops QUOTE unops NUMLIB cube-root use-newton newton deriv 
quadratic-formula qroots tandeg cosdeg sindeg radians e pi celsius 
fahrenheit gcd fib fact prime odd even negative positive SEQLIB 
treesample treemap treestrip treefilter treereverse treeflatten 
treeshunt orlistfilter orlist cartproduct transpose delete insert-old 
insert merge1 merge mk_qsort qsort1 qsort1-1 qsort permlist insertlist 
powerlist2 powerlist1 subseqlist frontlist frontlist1 scalarproduct 
product restlist flatten reversestring reverselist reverse putlist 
AGGLIB variance average sum interleave2list interleave2 foldr2 mapr2 
fold2 stepr2 mapr pairstep from-to-string from-to-set from-to-list 
from-to zip unswons2 swons2 uncons2 cons2 null2 thirdd secondd restd 
firstd unswonsd unconsd swonsd consd nulld set2string foldr elements 
string2set shunt fifth fourth third second unpair pairlist pairstring 
pairset unitlist unitstring unitset INILIB all-libload special-libload 
basic-libload libload verbose forever repeat nullary2 i2 call dip3 dip2 
dipd sequand negate disjoin conjoin show-todaynow now today 
localtime-strings months weekdays swoncat numerical boolean sequor 
to-lower to-upper falsity truth newstack pop2 dup2 ask putstrings bell 
space putln newline USRLIB standard-setting find-in unix edit escape 
editor dir terminal control-eof vms 
/*
 * generated Sun Oct 23 14:14:47 2016
 */
#include "runtime.h"


int joy_main() {
stk = &memory[MEMORYMAX];
writestack();
time_(); srand_();writestack();
writestack();
return 0; }

