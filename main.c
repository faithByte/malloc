#include "chunks.h"

int	main() {
	// char *str;

	// printf("%ld\n", PAGE_SIZE);
	// printf("%ld\n", TINY_PAGE_SIZE - CHUNK_META_BLOCK_SIZE - PAGE_META_BLOCK_SIZE);
	// // printPages();
	// str = (char *)newPage(1, TINY);

	// memset(str, '-', TINY_PAGE_SIZE + 2);

	// write(1, str, TINY_PAGE_SIZE + 2);
	// // printPages();
	newPage(SMALL_ALLOC_SIZE, SMALL);
	// // printPages();
	// newPage(SMALL_PAGE_SIZE + 55, LARGE);
	// // printPages();
	newPage(2, TINY);
	// printPages();
	// while (1)
	// {
	// 	;
	// }
	printList(getFreeChunksCollector(TINY), FREE_CHUNKS_OFFSET);
	printList(getFreeChunksCollector(SMALL), FREE_CHUNKS_OFFSET);
	printList(getFreeChunksCollector(LARGE), FREE_CHUNKS_OFFSET);
	
	return 0;
}