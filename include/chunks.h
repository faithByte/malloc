#ifndef	CHUNKS_H
# define CHUNKS_H

# include "page.h"


# define CHUNKS_OFFSET				0
# define FREE_CHUNKS_OFFSET			1
# define GARBAGE_COLLECTOR_OFFSET	2

typedef struct metaData {
	_ptr	ptr[3];
	size_t	size;
	bool	isFree;
} _metaData;

# define CHUNK_META_BLOCK_SIZE	sizeof(_metaData)

_ptr	**getFreeChunksCollector(e_type type);
_ptr	**getGarbageCollector(void);

void	initChunk(void *block, size_t size, e_type type);
bool	isAllocated(void *toFind);
void	*allocChunk(size_t size);
void	freeChunk(void *ptr);

void	splitChunk(_ptr *chunk, size_t size, e_type type);
void	mergeChunks(_ptr *chunk1, _ptr *chunk2, e_type type);

_metaData	*getFirstEmptyBlock(size_t size, e_type type);
_metaData	*getNextEmptyBlock(size_t size, e_type type);
_metaData	*getBestEmptyBlock(size_t size, e_type type);
_metaData	*getWorstEmptyBlock(size_t size, e_type type);
# define MALLOC_ALGO(size, type) getFirstEmptyBlock(size, type)

#endif