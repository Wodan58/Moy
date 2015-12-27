/* manual.c */
PRIVATE void manual_list_()
{
    int i = -1;
    Node *tmp, *cur = 0;

    while (optable[++i].name);
    while (--i) {
	tmp = newnode(STRING_, (Types) optable[i].messg2, 0);
	tmp = newnode(STRING_, (Types) optable[i].messg1, tmp);
	tmp = newnode(STRING_, (Types) optable[i].name, tmp);
	cur = newnode(LIST_, (Types) tmp, cur);
    }
    PUSH(LIST_, cur);
}
