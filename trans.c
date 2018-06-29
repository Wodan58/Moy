{ "!=", "neql", do_neql },
{ "-", "minus", do_minus },
{ "*", "mul", do_mul },
{ "/", "divide", do_divide },
{ "__dump", "__dump", do___dump },
{ "__html_manual", "__html_manual", do___html_manual },
{ "__latex_manual", "__latex_manual", do___latex_manual },
{ "__manual_list", "__manual_list", do___manual_list },
{ "__memoryindex", "__memoryindex", do___memoryindex },
{ "__memorymax", "__memorymax", do___memorymax },
{ "__settracegc", "__settracegc", do___settracegc },
{ "__symtabindex", "__symtabindex", do___symtabindex },
{ "__symtabmax", "__symtabmax", do___symtabmax },
{ "_help", "_help", do__help },
{ "+", "plus", do_plus },
{ "<", "less", do_less },
{ "<=", "leql", do_leql },
{ "=", "eql", do_eql },
{ ">", "greater", do_greater },
{ ">=", "geql", do_geql },
{ "abort", "abort", do_abort },
{ "abs", "abs", do_abs },
{ "acos", "acos", do_acos },
{ "all", "all", do_all },
{ "and", "and", do_and },
{ "app1", "app1", do_app1 },
{ "app11", "app11", do_app11 },
{ "app12", "app12", do_app12 },
{ "app2", "app2", do_app2 },
{ "app3", "app3", do_app3 },
{ "app4", "app4", do_app4 },
{ "argc", "argc", do_argc },
{ "argv", "argv", do_argv },
{ "asin", "asin", do_asin },
{ "at", "at", do_at },
{ "atan", "atan", do_atan },
{ "atan2", "atan2", do_atan2 },
{ "autoput", "autoput", do_autoput },
{ "binary", "binary", do_binary },
{ "binrec", "binrec", do_binrec },
{ "body", "body", do_body },
{ "branch", "branch", do_branch },
{ "case", "case", do_case },
{ "casting", "casting", do_casting },
{ "ceil", "ceil", do_ceil },
{ "char", "char", do_char },
{ "choice", "choice", do_choice },
{ "chr", "chr", do_chr },
{ "cleave", "cleave", do_cleave },
{ "clock", "clock", do_clock },
{ "compare", "compare", do_compare },
{ "concat", "concat", do_concat },
{ "cond", "cond", do_cond },
{ "condlinrec", "condlinrec", do_condlinrec },
{ "condnestrec", "condnestrec", do_condnestrec },
{ "cons", "cons", do_cons },
{ "construct", "construct", do_construct },
{ "conts", "conts", do_conts },
{ "cos", "cos", do_cos },
{ "cosh", "cosh", do_cosh },
{ "dip", "dip", do_dip },
{ "div", "div", do_div },
{ "drop", "drop", do_drop },
{ "dup", "dup", do_dup },
{ "dupd", "dupd", do_dupd },
{ "echo", "echo", do_echo },
{ "enconcat", "enconcat", do_enconcat },
{ "equal", "equal", do_equal },
{ "exp", "exp", do_exp },
{ "false", "false", do_false },
{ "fclose", "fclose", do_fclose },
{ "feof", "feof", do_feof },
{ "ferror", "ferror", do_ferror },
{ "fflush", "fflush", do_fflush },
{ "fget", "fget", do_fget },
{ "fgetch", "fgetch", do_fgetch },
{ "fgets", "fgets", do_fgets },
{ "file", "file", do_file },
{ "filetime", "filetime", do_filetime },
{ "filter", "filter", do_filter },
{ "first", "first", do_first },
{ "float", "float", do_float },
{ "floor", "floor", do_floor },
{ "fold", "fold", do_fold },
{ "fopen", "fopen", do_fopen },
{ "format", "format", do_format },
{ "formatf", "formatf", do_formatf },
{ "fput", "fput", do_fput },
{ "fputch", "fputch", do_fputch },
{ "fputchars", "fputchars", do_fputchars },
{ "fputstring", "fputchars", do_fputchars },
{ "fread", "fread", do_fread },
{ "fremove", "fremove", do_fremove },
{ "frename", "frename", do_frename },
{ "frexp", "frexp", do_frexp },
{ "fseek", "fseek", do_fseek },
{ "ftell", "ftell", do_ftell },
{ "fwrite", "fwrite", do_fwrite },
{ "gc", "gc", do_gc },
{ "genrec", "genrec", do_genrec },
{ "get", "get", do_get },
{ "getch", "getch", do_getch },
{ "getenv", "getenv", do_getenv },
{ "gmtime", "gmtime", do_gmtime },
{ "has", "has", do_has },
{ "help", "help", do_help },
{ "helpdetail", "helpdetail", do_helpdetail },
{ "i", "i", do_i },
{ "id", "id", do_id },
{ "ifchar", "ifchar", do_ifchar },
{ "iffile", "iffile", do_iffile },
{ "iffloat", "iffloat", do_iffloat },
{ "ifinteger", "ifinteger", do_ifinteger },
{ "iflist", "iflist", do_iflist },
{ "iflogical", "iflogical", do_iflogical },
{ "ifset", "ifset", do_ifset },
{ "ifstring", "ifstring", do_ifstring },
{ "ifte", "ifte", do_ifte },
{ "in", "in", do_in },
{ "in1", "in1", do_in1 },
{ "include", "include", do_include },
{ "index", "index", do_index },
{ "infra", "infra", do_infra },
{ "integer", "integer", do_integer },
{ "intern", "intern", do_intern },
{ "ldexp", "ldexp", do_ldexp },
{ "leaf", "leaf", do_leaf },
{ "linrec", "linrec", do_linrec },
{ "list", "list", do_list },
{ "localtime", "localtime", do_localtime },
{ "log", "log", do_log },
{ "log10", "log10", do_log10 },
{ "logical", "logical", do_logical },
{ "manual", "manual", do_manual },
{ "map", "map", do_map },
{ "max", "max", do_max },
{ "maxint", "maxint", do_maxint },
{ "min", "min", do_min },
{ "mktime", "mktime", do_mktime },
{ "modf", "modf", do_modf },
{ "name", "name", do_name },
{ "neg", "neg", do_neg },
{ "not", "not", do_not },
{ "nothing", "nothing", do_nothing },
{ "null", "null", do_null },
{ "nullary", "nullary", do_nullary },
{ "of", "of", do_of },
{ "opcase", "opcase", do_opcase },
{ "or", "or", do_or },
{ "ord", "ord", do_ord },
{ "over", "over", do_over },
{ "pick", "pick", do_pick },
{ "pop", "pop", do_pop },
{ "popd", "popd", do_popd },
{ "pow", "pow", do_pow },
{ "pred", "pred", do_pred },
{ "primrec", "primrec", do_primrec },
{ "put", "put", do_put },
{ "putch", "putch", do_putch },
{ "putchars", "putchars", do_putchars },
{ "quit", "quit", do_quit },
{ "rand", "rand", do_rand },
{ "rem", "rem", do_rem },
{ "rest", "rest", do_rest },
{ "rolldown", "rolldown", do_rolldown },
{ "rolldownd", "rolldownd", do_rolldownd },
{ "rollup", "rollup", do_rollup },
{ "rollupd", "rollupd", do_rollupd },
{ "rotate", "rotate", do_rotate },
{ "rotated", "rotated", do_rotated },
{ "round", "round", do_round },
{ "sametype", "sametype", do_sametype },
{ "set", "set", do_set },
{ "setautoput", "setautoput", do_setautoput },
{ "setecho", "setecho", do_setecho },
{ "setsize", "setsize", do_setsize },
{ "setundeferror", "setundeferror", do_setundeferror },
{ "sign", "sign", do_sign },
{ "sin", "sin", do_sin },
{ "sinh", "sinh", do_sinh },
{ "size", "size", do_size },
{ "small", "small", do_small },
{ "some", "some", do_some },
{ "split", "split", do_split },
{ "sqrt", "sqrt", do_sqrt },
{ "srand", "srand", do_srand },
{ "stack", "stack", do_stack },
{ "stderr", "stderr", do_stderr },
{ "stdin", "stdin", do_stdin },
{ "stdout", "stdout", do_stdout },
{ "step", "step", do_step },
{ "strftime", "strftime", do_strftime },
{ "string", "string", do_string },
{ "strtod", "strtod", do_strtod },
{ "strtol", "strtol", do_strtol },
{ "succ", "succ", do_succ },
{ "swap", "swap", do_swap },
{ "swapd", "swapd", do_swapd },
{ "swons", "swons", do_swons },
{ "system", "system", do_system },
{ "tailrec", "tailrec", do_tailrec },
{ "take", "take", do_take },
{ "tan", "tan", do_tan },
{ "tanh", "tanh", do_tanh },
{ "ternary", "ternary", do_ternary },
{ "time", "time", do_time },
{ "times", "times", do_times },
{ "treegenrec", "treegenrec", do_treegenrec },
{ "treerec", "treerec", do_treerec },
{ "treestep", "treestep", do_treestep },
{ "true", "true", do_true },
{ "trunc", "trunc", do_trunc },
{ "unary", "unary", do_unary },
{ "unary2", "unary2", do_unary2 },
{ "unary3", "unary3", do_unary3 },
{ "unary4", "unary4", do_unary4 },
{ "uncons", "uncons", do_uncons },
{ "undeferror", "undeferror", do_undeferror },
{ "undefs", "undefs", do_undefs },
{ "unstack", "unstack", do_unstack },
{ "unswons", "unswons", do_unswons },
{ "user", "user", do_user },
{ "while", "while", do_while },
{ "x", "x", do_x },
{ "xor", "xor", do_xor },