#include "list.h"

_node	*newNode(char *str){
	if (!str)
		return NULL;

	size_t size = strlen(str);
	_node *node = malloc(sizeof(_node));

	node->data = malloc(size + 1);
	memcpy(node->data, str, size);
	node->data[size] = 0;

	return node;
}

_ptr	**getCollectors(short type);

int	main() {
	char *str[5] = {"hello\n", "world\n", "test\n", "hhhh\n", "imane\n"};
	_node	**nodes;
	short	offset = 0;

	nodes = malloc(sizeof(_node *) * 5);

	printList(getCollectors(offset), offset);
	for (int i = 0; i < 5; i++) {
		nodes[i] = newNode(str[i]);
		insertNode(getCollectors(offset), nodes[i]->pointers + offset);
	}
	printList(getCollectors(offset), offset);
	for (int i = 0; i < 3; i++)
		deleteNode(getCollectors(offset), nodes[i]->pointers + offset);
	printf("====\n");
	printList(getCollectors(offset), offset);
	printf("====\n");

	printList(getCollectors(1), offset);
	printf("====\n");

	for (int i = 0; i < 5; i++) {
		free(nodes[i]->data);
		free(nodes[i]);
	}
	free(nodes);
	return 0;
}