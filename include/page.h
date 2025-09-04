#ifndef	PAGE_H
# define PAGE_H

# include "utils.h"
# include <sys/mman.h>

# define PAGE_SIZE			(size_t)(getpagesize())

# define TINY_ALLOC_SIZE	128
# define SMALL_ALLOC_SIZE	1024

# define TINY_PAGE_SIZE		PAGE_SIZE
# define SMALL_PAGE_SIZE	PAGE_SIZE * 2

extern _ptr	*g_head;
typedef struct metaData _metaData;

typedef enum type {
	TINY,
	SMALL,
	LARGE
} e_type;

typedef struct page {
	_ptr	ptr;
	_ptr	*chunks;
	size_t	size;
	e_type	type;
} _page;

# define PAGE_META_BLOCK_SIZE	sizeof(_page)


void		*newVMPage(size_t size);
void		deletePage(_metaData *meta, e_type type);
void		cleanPages(_metaData *meta, e_type type);
_metaData	*newPage(size_t size, e_type type);

void	printPages();
e_type	getPageType(size_t size);

#endif
