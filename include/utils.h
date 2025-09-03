#ifndef	UTILS_H
# define UTILS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>

typedef struct ptr
{
	struct ptr *next;
	struct ptr *previous;	
} _ptr;

void	printList(_ptr **list, short offset);
void	insertNode(_ptr **list, _ptr *node);
void	deleteNode(_ptr **list, _ptr *node);

void	print(char *str);

#endif