#include "chunks.h"

void	*initChunk(void *block, size_t size, e_type type) {
	_metaData	*meta;

	meta = (_metaData *)block;
	memset(meta, 0, sizeof(_metaData));
	meta->size = size - CHUNK_META_BLOCK_SIZE;
	meta->isFree = true;

	insertNode(getFreeChunksCollector(type), meta->ptr + FREE_CHUNKS_OFFSET);
	return ((void *)((char *)block + CHUNK_META_BLOCK_SIZE));
}