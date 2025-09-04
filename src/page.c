#include "chunks.h"

_ptr	*g_head = NULL;

e_type	getPageType(size_t size) {
	if (size <= TINY_ALLOC_SIZE) 
		return TINY;
	else if (size <= SMALL_ALLOC_SIZE)
		return SMALL;
	return LARGE;
}

size_t	getPageSize(size_t size, e_type type) {
	if (type == TINY) 
		return TINY_PAGE_SIZE;
	else if (type == SMALL)
		return SMALL_PAGE_SIZE;

	size += PAGE_META_BLOCK_SIZE + CHUNK_META_BLOCK_SIZE;
	size_t mod = size % PAGE_SIZE;
	return (size - mod + (mod ? PAGE_SIZE : 0));
}

void	*newVMPage(size_t pageSize) {
	void	*vmPage;

	vmPage = mmap(NULL, pageSize, PROT_READ | PROT_WRITE , MAP_ANON | MAP_PRIVATE, -1, 0);
	
	if (vmPage == MAP_FAILED) {
		print("ERROR: MAP FAILED\n");
		return NULL;
	}
	return vmPage;
}

_metaData	*newPage(size_t size, e_type type) {
	_page	*page;
	void	*vmPage;
	size_t	pageSize;
	_metaData	*meta;

	pageSize = getPageSize(size, type);
	vmPage = newVMPage(pageSize);
	if (!vmPage)
		return NULL;

	// init page
	page = (_page *)vmPage;
	meta = (_metaData *)((char *)vmPage + PAGE_META_BLOCK_SIZE);

	page->ptr.next = NULL;
	page->ptr.previous = NULL;
	page->chunks = meta->ptr + CHUNKS_OFFSET;
	page->size = pageSize;
	page->type = type;

	// insert in pages list 
	insertNode(&g_head, &page->ptr);

	// init big free chunk
	initChunk((void *)((char *)vmPage + PAGE_META_BLOCK_SIZE), pageSize - PAGE_META_BLOCK_SIZE, type);
	return (meta);
}

void	deletePage(_metaData *meta, e_type type) {
	_page	*page;
	_ptr	*ptr;

	ptr = meta->ptr + CHUNKS_OFFSET;
	while (ptr->previous) {
		ptr = ptr->previous;
	}

	page = (_page *)((char *)(ptr - CHUNKS_OFFSET) - PAGE_META_BLOCK_SIZE);
	
	ptr = page->chunks;
	while (ptr) {
		meta = (_metaData *)(ptr - CHUNKS_OFFSET);
		if (!meta->isFree) // to do: check it's not supposed to happen
			deleteNode(getGarbageCollector(), meta->ptr + GARBAGE_COLLECTOR_OFFSET);
		else
			deleteNode(getFreeChunksCollector(type), meta->ptr + FREE_CHUNKS_OFFSET);

		ptr = ptr->next;
	}
	
	deleteNode(&g_head, (void *)page);
	if (munmap((void *)page, page->size)) {
		print("ERROR: MUNMAP FAILED\n");
	}

}

// delete page if there's other pages from same type that has free spaces
void	cleanPages(_metaData *meta, e_type type) {
	_ptr	*freeChunksCollector = *getFreeChunksCollector(type);

	// to do: redo
	if (!freeChunksCollector 
		|| !freeChunksCollector->next)
			deleteNode(getGarbageCollector(), meta->ptr + GARBAGE_COLLECTOR_OFFSET);
	else
		deletePage(meta, type);
}