#include "chunks.h"


void	printPages() {
	_ptr	*ptr = g_head;
	_page	*page;
	size_t	i = 0;

	if (!ptr)
		return;

	printf("==>PAGES=========================\n");
	while (ptr) {
		page = (_page *)(ptr);
		// print(page->data);
		if (page->type == LARGE)
			printf("LARGE\n");
		else if (page->type == SMALL)
			printf("SMALL\n");
		else
			printf("TINY\n");
		ptr = ptr->next;
		i++;
	}
	printf("size: %ld\n=========================\n", i);
	
}

void	printList(_ptr **listHead, short offset) {
	_ptr	*ptr;
	_metaData	*node;

	if (!listHead || !*listHead)
		return;
	ptr = *listHead;
	while (ptr) {
		node = (_metaData *)(ptr - offset);
		// print(node->data);
		printf("size :%ld\n", node->size);
		if (node->isFree)
			printf("FREE\n");
		else
			printf("USED\n");

		ptr = ptr->next;
	}
	printf("=======================================\n");
	
}

void	insertNode(_ptr **listHead, _ptr *node) {
	if (!listHead || !node)
		return;

	if (*listHead)
		(*listHead)->previous = node;
	node->next = *listHead;
	node->previous = NULL;
	*listHead = node;
}

void	deleteNode(_ptr **listHead, _ptr *node) {
	_ptr	*next, *prv;

	if (!listHead || !*listHead || !node)
		return;

	next = node->next;
	prv = node->previous;

	if (!prv) {
		(*listHead) = node->next;
	} else
		prv->next = node->next;

	if (next)
		next->previous = prv;
}