void Intersection(List *la, List *lb, List &lc) {
	LinkNode *pa = la->getHead();
	LinkNode *pb = lb->getHead();
	LinkNode *pc = lc.getHead();
	LinkNode *temp;
	while (pa->link!=NULL)
	{
		pb = lb->getHead();
		while (pb->link!=NULL)
		{
			if (pa->link->data==pb->link->data)
			{
				temp = pb->link;
				pb->link = temp->link;
				pc->link = temp;
				temp->link = NULL;
				pc = pc->link;
			}
			else
			{
				pb = pb->link;
			}
		}
		pa = pa->link;
	}
}
