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

void	*initChunk(void *block, size_t size, e_type type);
_ptr	**getFreeChunksCollector(e_type type);

#endif