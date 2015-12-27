/* argv.c */
PRIVATE void argv_()
{
    int i;
    Node *cur = 0;

    for (i = g_argc - 1; i >= 0; i--)
	cur = newnode(STRING_, (Types) g_argv[i], cur);
    PUSH(LIST_, cur);
}
