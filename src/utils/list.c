#include "chunks.h"


void	printPages() {
	_ptr	*ptr = g_head;
	_page	*page;
	size_t	i = 0;

	if (!ptr)
		return;

	print("==>PAGES=========================\n");
	while (ptr) {
		page = (_page *)(ptr);
		// print(page->data);
		if (page->type == LARGE)
			print("LARGE\n");
		else if (page->type == SMALL)
			print("SMALL\n");
		else
			print("TINY\n");
		ptr = ptr->next;
		i++;
	}
	printf("size: =========================\n");
	printNumber((size_t)i, DEC_BASE);
	print("\n");
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
		print("size :");
		printNumber((size_t)node->size, DEC_BASE);
		print("\n");
		if (node->isFree)
			print("FREE\n");
		else
			print("USED\n");

		ptr = ptr->next;
	}
	print("=======================================\n");
	
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

void	mergeChunks(_ptr *chunk1, _ptr *chunk2, e_type type) {
	_metaData	*meta1, *meta2;

	meta1 = (_metaData *)((char *)chunk1 - CHUNKS_OFFSET);
	meta2 = (_metaData *)((char *)chunk2 - CHUNKS_OFFSET);

	meta1->size += meta2->size + CHUNK_META_BLOCK_SIZE;

	deleteNode(getFreeChunksCollector(type), meta2->ptr + FREE_CHUNKS_OFFSET);

	if (chunk2->next)
		chunk2->next->previous = chunk1;
	chunk1->next = chunk2->next;


	// to do: handle fragmentation
}


void	splitChunk(_ptr *chunk, size_t size, e_type type) {
	_metaData	*meta, *next;

	meta = (_metaData *)((char *)chunk - CHUNKS_OFFSET);
	if (meta->size > (CHUNK_META_BLOCK_SIZE + size)) {
		next = (_metaData *)((char *)meta + CHUNK_META_BLOCK_SIZE + size);
		memset(next->ptr, 0, sizeof(_ptr) * 3);
		next->size = meta->size - size - CHUNK_META_BLOCK_SIZE;
		next->isFree = true;
		insertNode(getFreeChunksCollector(type), next->ptr + FREE_CHUNKS_OFFSET);

		meta->size = size;
	} else {
		// to do: handle fragmentation
	}
}