#ifndef	LIST_H
# define LIST_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <sys/mman.h>

typedef struct ptr
{
	struct ptr *next;
	struct ptr *previous;	
} _ptr;

extern _ptr	*g_head;

typedef struct node {
	_ptr	pointers[3];
	char	*data;
} _node;

void	printList(_ptr **list, short offset);
void	insertNode(_ptr **list, _ptr *node);
void	deleteNode(_ptr **list, _ptr *node);

#endif