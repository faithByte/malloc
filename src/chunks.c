#include "chunks.h"

void	mergeChunks(_ptr *chunk1, _ptr *chunk2, e_type type) {
	_metaData	*meta1, *meta2;

	meta1 = (_metaData *)((char *)chunk1 - CHUNKS_OFFSET);
	meta2 = (_metaData *)((char *)chunk2 - CHUNKS_OFFSET);

	meta1->size += meta2->size + CHUNK_META_BLOCK_SIZE;


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

		next->ptr[CHUNKS_OFFSET].next = chunk->next;
		next->ptr[CHUNKS_OFFSET].previous = chunk;
		chunk->next = next->ptr + CHUNKS_OFFSET;

		meta->size = size;
	} else {
		// to do: handle fragmentation
	}
}

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
	e_type		type;
	_metaData	*meta;
	_ptr		*current, *prv, *next;

	meta = (_metaData *)((char *)ptr - CHUNK_META_BLOCK_SIZE);
	type = getPageType(meta->size);
	
	if (meta->isFree)
		return;

	meta->isFree = true;

	if (type == LARGE) {
		deleteNode(getGarbageCollector(), meta->ptr + GARBAGE_COLLECTOR_OFFSET);
		deletePage(meta, type);
		return ;
	}

	current = meta->ptr + CHUNKS_OFFSET;
	next = current->next;
	prv = current->previous;

	if (next && ((_metaData *)(next - CHUNKS_OFFSET))->isFree) {
		deleteNode(getFreeChunksCollector(type), next - CHUNKS_OFFSET + FREE_CHUNKS_OFFSET);
		mergeChunks(current, next, type);
	}

	if (prv && ((_metaData *)(prv - CHUNKS_OFFSET))->isFree)
		mergeChunks(prv, current, type);
	else
		insertNode(getFreeChunksCollector(type), meta->ptr + FREE_CHUNKS_OFFSET);

	deleteNode(getGarbageCollector(), meta->ptr + GARBAGE_COLLECTOR_OFFSET);

	if (!next && !prv)
		cleanPages(meta, type);
}