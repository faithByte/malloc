#include "chunks.h"

_ptr	*g_head = NULL;

void	*newVMPage(size_t pageSize) {
	void	*vmPage;

	vmPage = mmap(NULL, pageSize, PROT_READ | PROT_WRITE , MAP_ANON | MAP_PRIVATE, -1, 0);
	
	if (vmPage == MAP_FAILED) {
		print("ERROR: MAP FAILED\n");
		return NULL;
	}
	return vmPage;
}

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

_metaData	*newPage(size_t size, e_type type) {
	_page	*page;
	void	*vmPage;
	size_t	pageSize;

	pageSize = getPageSize(size, type);
	vmPage = newVMPage(pageSize);
	if (!vmPage)
		return NULL;

	// init page
	page = (_page *)vmPage;
	page->ptr.next = NULL;
	page->ptr.previous = NULL;
	page->chunks = NULL;
	page->size = pageSize;
	page->type = type;
	// insert in pages list 
	insertNode(&g_head, &page->ptr);

	// init big free chunk
	initChunk((void *)((char *)vmPage + PAGE_META_BLOCK_SIZE), pageSize - PAGE_META_BLOCK_SIZE, type);
	return ((_metaData *)((char *)vmPage + PAGE_META_BLOCK_SIZE));
}

void	deletePage(void *ptr) {
	// _page	*page;

	// page = (_page *)(char *)ptr - CHUNK_META_BLOCK_SIZE - PAGE_META_BLOCK_SIZE;
	// deleteNode(&g_head, (void *)page);
	// munmap((void *)page, page->size);
}
