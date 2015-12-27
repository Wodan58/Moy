/* undefs.c */
PRIVATE void undefs_(void)
{
    Node *n = 0;
    Entry *i = symtabindex;

    while (--i != symtab)
	if (i->name[0] && i->name[0] != '_' && !i->u.body)
	    n = newnode(STRING_, (Types) i->name, n);
    PUSH(LIST_, n);
}
