#include "list.h"

_ptr	*g_head = NULL;

void	print(char *str) {
	if (!str)
		return;

	write(1, str, strlen(str));
}

void	printList(_ptr **listHead, short offset) {
	_ptr	*ptr;
	_node	*node;

	if (!listHead || !*listHead)
		return;
	ptr = *listHead;
	while (ptr) {
		node = (_node *)(ptr - offset);
		print(node->data);
		ptr = ptr->next;
	}
	
}

void	insertNode(_ptr **listHead, _ptr *node) {
	if (!listHead || !node)
		return;

	if (*listHead)
		(*listHead)->previous = node;
	node->next = *listHead;
	*listHead = node;
	node->previous = NULL;
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