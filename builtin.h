/*
    module  : builtin.h
    version : 1.5
    date    : 03/18/17
*/
PRIVATE void do_id(void);
PRIVATE void do_nothing(void);	// XXX
PRIVATE void do_false(void);
PRIVATE void do_true(void);
PRIVATE void do_maxint(void);
PRIVATE void do_setsize(void);
PRIVATE void do_stack(void);
PRIVATE void do_symtabmax(void);
PRIVATE void do_symtabindex(void);
PRIVATE void do_dump(void);
PRIVATE void do_conts(void);
PRIVATE void do_autoput(void);
PRIVATE void do_undeferror(void);
PRIVATE void do_undefs(void);
PRIVATE void do_echo(void);
PRIVATE void do_clock(void);
PRIVATE void do_time(void);
PRIVATE void do_rand(void);
PRIVATE void do_memorymax(void);
PRIVATE void do_stdin(void);
PRIVATE void do_stdout(void);
PRIVATE void do_stderr(void);
PRIVATE void do_dup(void);
PRIVATE void do_swap(void);
PRIVATE void do_rollup(void);
PRIVATE void do_rolldown(void);
PRIVATE void do_rotate(void);
PRIVATE void do_popd(void);
PRIVATE void do_dupd(void);
PRIVATE void do_swapd(void);
PRIVATE void do_rollupd(void);
PRIVATE void do_rolldownd(void);
PRIVATE void do_rotated(void);
PRIVATE void do_pop(void);
PRIVATE void do_choice(void);
PRIVATE void do_or(void);
PRIVATE void do_xor(void);
PRIVATE void do_and(void);
PRIVATE void do_not(void);
PRIVATE void do_plus(void);
PRIVATE void do_minus(void);
PRIVATE void do_mul(void);
PRIVATE void do_divide(void);
PRIVATE void do_rem(void);
PRIVATE void do_div(void);
PRIVATE void do_sign(void);
PRIVATE void do_neg(void);
PRIVATE void do_ord(void);
PRIVATE void do_chr(void);
PRIVATE void do_abs(void);
PRIVATE void do_acos(void);
PRIVATE void do_asin(void);
PRIVATE void do_atan(void);
PRIVATE void do_atan2(void);
PRIVATE void do_ceil(void);
PRIVATE void do_cos(void);
PRIVATE void do_cosh(void);
PRIVATE void do_exp(void);
PRIVATE void do_floor(void);
PRIVATE void do_round(void);	// XXX
PRIVATE void do_frexp(void);
PRIVATE void do_ldexp(void);
PRIVATE void do_log(void);
PRIVATE void do_log10(void);
PRIVATE void do_modf(void);
PRIVATE void do_pow(void);
PRIVATE void do_sin(void);
PRIVATE void do_sinh(void);
PRIVATE void do_sqrt(void);
PRIVATE void do_tan(void);
PRIVATE void do_tanh(void);
PRIVATE void do_trunc(void);
PRIVATE void do_localtime(void);
PRIVATE void do_gmtime(void);
PRIVATE void do_mktime(void);
PRIVATE void do_strftime(void);
PRIVATE void do_strtol(void);
PRIVATE void do_strtod(void);
PRIVATE void do_format(void);
PRIVATE void do_formatf(void);
PRIVATE void do_srand(void);
PRIVATE void do_pred(void);
PRIVATE void do_succ(void);
PRIVATE void do_max(void);
PRIVATE void do_min(void);
PRIVATE void do_fclose(void);
PRIVATE void do_feof(void);
PRIVATE void do_ferror(void);
PRIVATE void do_fflush(void);
PRIVATE void do_fget(void);	// XXX
PRIVATE void do_fgetch(void);
PRIVATE void do_fgets(void);
PRIVATE void do_fopen(void);
PRIVATE void do_fread(void);
PRIVATE void do_fwrite(void);
PRIVATE void do_fremove(void);
PRIVATE void do_frename(void);
PRIVATE void do_filetime(void);	// XXX
PRIVATE void do_fput(void);
PRIVATE void do_fputch(void);
PRIVATE void do_fputchars(void);
PRIVATE void do_fseek(void);
PRIVATE void do_ftell(void);
PRIVATE void do_unstack(void);
PRIVATE void do_cons(void);
PRIVATE void do_swons(void);
PRIVATE void do_first(void);
PRIVATE void do_rest(void);
PRIVATE void do_compare(void);
PRIVATE void do_at(void);
PRIVATE void do_of(void);
PRIVATE void do_size(void);
PRIVATE void do_opcase(void);
PRIVATE void do_case(void);
PRIVATE void do_uncons(void);
PRIVATE void do_unswons(void);
PRIVATE void do_drop(void);
PRIVATE void do_take(void);
PRIVATE void do_concat(void);
PRIVATE void do_enconcat(void);
PRIVATE void do_name(void);
PRIVATE void do_intern(void);
PRIVATE void do_body(void);
PRIVATE void do_null(void);
PRIVATE void do_small(void);
PRIVATE void do_geql(void);
PRIVATE void do_greater(void);
PRIVATE void do_leql(void);
PRIVATE void do_less(void);
PRIVATE void do_neql(void);
PRIVATE void do_eql(void);
PRIVATE void do_equal(void);
PRIVATE void do_has(void);
PRIVATE void do_in(void);
PRIVATE void do_index(void);	// XXX
PRIVATE void do_sametype(void);	// XXX
PRIVATE void do_casting(void);	// XXX
PRIVATE void do_integer(void);
PRIVATE void do_char(void);
PRIVATE void do_logical(void);
PRIVATE void do_set(void);
PRIVATE void do_string(void);
PRIVATE void do_list(void);
PRIVATE void do_leaf(void);
PRIVATE void do_user(void);
PRIVATE void do_float(void);
PRIVATE void do_file(void);
PRIVATE void do_i(void);
PRIVATE void do_x(void);
PRIVATE void do_dip(void);
PRIVATE void do_app1(void);
PRIVATE void do_app11(void);
PRIVATE void do_app12(void);
PRIVATE void do_construct(void);
PRIVATE void do_nullary(void);
PRIVATE void do_unary(void);
PRIVATE void do_unary2(void);
PRIVATE void do_unary3(void);
PRIVATE void do_unary4(void);
PRIVATE void do_binary(void);
PRIVATE void do_ternary(void);
PRIVATE void do_cleave(void);
PRIVATE void do_branch(void);
PRIVATE void do_ifte(void);
PRIVATE void do_ifinteger(void);
PRIVATE void do_ifchar(void);
PRIVATE void do_iflogical(void);
PRIVATE void do_ifset(void);
PRIVATE void do_ifstring(void);
PRIVATE void do_iflist(void);
PRIVATE void do_iffloat(void);
PRIVATE void do_iffile(void);
PRIVATE void do_cond(void);
PRIVATE void do_while(void);
PRIVATE void do_linrec(void);
PRIVATE void do_tailrec(void);
PRIVATE void do_binrec(void);
PRIVATE void do_genrec(void);
PRIVATE void do_condnestrec(void);
PRIVATE void do_condlinrec(void);
PRIVATE void do_step(void);
PRIVATE void do_fold(void);
PRIVATE void do_map(void);
PRIVATE void do_times(void);
PRIVATE void do_infra(void);
PRIVATE void do_primrec(void);
PRIVATE void do_filter(void);
PRIVATE void do_split(void);
PRIVATE void do_some(void);
PRIVATE void do_all(void);
PRIVATE void do_treestep(void);
PRIVATE void do_treerec(void);
PRIVATE void do_treegenrec(void);
PRIVATE void do_help(void);
PRIVATE void do_help1(void);
PRIVATE void do_helpdetail(void);
PRIVATE void do_manual(void);
PRIVATE void do_html_manual(void);
PRIVATE void do_latex_manual(void);
PRIVATE void do_manual_list(void);
PRIVATE void do_settracegc(void);
PRIVATE void do_setautoput(void);
PRIVATE void do_setundeferror(void);
PRIVATE void do_setecho(void);
PRIVATE void do_gc(void);
PRIVATE void do_system(void);
PRIVATE void do_getenv(void);
PRIVATE void do_argv(void);
PRIVATE void do_argc(void);
PRIVATE void do_memoryindex(void);
PRIVATE void do_get(void);
PRIVATE void do_getch(void);	// XXX
PRIVATE void do_put(void);
PRIVATE void do_putch(void);
PRIVATE void do_putchars(void);
PRIVATE void do_include(void);
PRIVATE void do_abort(void);
PRIVATE void do_quit(void);
PRIVATE void do_stop(void);
