#include "chunks.h"

void	initChunk(void *block, size_t size, e_type type) {
	_metaData	*meta;

	meta = (_metaData *)block;
	memset(meta->ptr, 0, sizeof(meta->ptr));
	meta->size = size - CHUNK_META_BLOCK_SIZE;
	meta->isFree = true;
	insertNode(getFreeChunksCollector(type), meta->ptr + FREE_CHUNKS_OFFSET);
}

bool	isAllocated(void *toFind) {
	_metaData *meta;
	_ptr	*ptr = *getGarbageCollector();

	while (ptr) {
		void *tmp = ((_ptr *)((char *)(ptr - GARBAGE_COLLECTOR_OFFSET) + CHUNK_META_BLOCK_SIZE));

		if (tmp == toFind)
			return true;
		ptr = ptr->next;
	}
	return false;
}

void	*allocChunk(size_t size) {
	e_type	type = getPageType(size);
	_metaData	*meta;

	if (type == LARGE)
		meta = newPage(size, type);
	else {
		meta = MALLOC_ALGO(size, type);
		if (!meta)
			meta = newPage(size, type);
	}

	if (!meta) 
		return NULL;
	
	splitChunk(meta->ptr + CHUNKS_OFFSET, size, type);
	meta->isFree = false;
	deleteNode(getFreeChunksCollector(type), meta->ptr + FREE_CHUNKS_OFFSET);
	insertNode(getGarbageCollector(), meta->ptr + GARBAGE_COLLECTOR_OFFSET);

	return ((void *)((char *)meta + CHUNK_META_BLOCK_SIZE));
}

void	freeChunk(void *ptr) {
	_metaData	*meta, *prv, *next;

	// PROTECTED ON FREE
	meta = (_metaData *)((char *)ptr - CHUNK_META_BLOCK_SIZE);


}