#include "page.h"

_ptr	**getFreeChunksCollector(e_type type) {
	static _ptr	*tinyChunksCollector, 
				*smallChunksCollector, 
				*largeChunksCollector;

	if (type == TINY)
		return &tinyChunksCollector;
	else if (type == SMALL)
		return &smallChunksCollector;
	else
		return &largeChunksCollector;
}