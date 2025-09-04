#include "malloc.h"
_ptr	**getChunksCollector(_ptr *chunk);

int	main() {
	// char *str;

	// printf("%ld\n", PAGE_SIZE);
	// printf("%ld\n", TINY_PAGE_SIZE - CHUNK_META_BLOCK_SIZE - PAGE_META_BLOCK_SIZE);
	// // printPages();
	// str = (char *)newPage(1, TINY);

	// memset(str, '-', TINY_PAGE_SIZE + 2);
	void	*ptr = malloc(SMALL_ALLOC_SIZE + 1);
	void	*ptr1 = malloc(10);

	free(ptr);
	void	*ptr2 = malloc(20);

	// _metaData *meta = (_metaData *)((char *)ptr - CHUNK_META_BLOCK_SIZE);
	// print("++> ");
	// printNumber((size_t)ptr, HEXA_BASE);
	// print("\n");

	// print("\n--> ");
	// printNumber((size_t)meta->ptr + FREE_CHUNKS_OFFSET, HEXA_BASE);
	// print("\n");

	ptr = realloc(ptr, 10);
	// void	*ptr3 = malloc(2);
	// write(1, str, TINY_PAGE_SIZE + 2);
	// printPages();
	// newPage(SMALL_ALLOC_SIZE, SMALL);
	// // // printPages();
	// // newPage(SMALL_PAGE_SIZE + 55, LARGE);
	// // // printPages();
	// newPage(2, TINY);
	// // printPages();
	// // while (1)
	// // {
	// // 	;
	// // }
	// splitChunk((_ptr *)((char *)ptr - CHUNK_META_BLOCK_SIZE + CHUNKS_OFFSET), 1000, TINY);
	// splitChunk((_ptr *)((char *)ptr - CHUNK_META_BLOCK_SIZE + CHUNKS_OFFSET), 100, TINY);
	// // splitChunk((_ptr *)((char *)ptr - CHUNK_META_BLOCK_SIZE + CHUNKS_OFFSET), 10, TINY);

	// _ptr	*tmp = *getFreeChunksCollector(TINY);
	
	// while (tmp->next)
	// {
	// 	tmp = tmp->next;
	// }
	
	// tmp -= FREE_CHUNKS_OFFSET;

	// splitChunk(tmp + CHUNKS_OFFSET, 10, TINY);
	// tmp = *getFreeChunksCollector(TINY);
	// tmp = tmp->next;
	// tmp -= FREE_CHUNKS_OFFSET;
	// splitChunk(tmp + CHUNKS_OFFSET, 10, TINY);

	// printList(getFreeChunksCollector(TINY), FREE_CHUNKS_OFFSET);

	// _ptr *t;

	// tmp = *getFreeChunksCollector(TINY);
	
	// while (tmp->next)
	// {
	// 	t = tmp;
	// 	tmp = tmp->next;
	// }
	
	// t -= FREE_CHUNKS_OFFSET;
	// tmp -= FREE_CHUNKS_OFFSET;

	// mergeChunks(t + CHUNKS_OFFSET, tmp + CHUNKS_OFFSET, TINY);

	// tmp = *getFreeChunksCollector(TINY);
	// t = tmp->next;

	// tmp -= FREE_CHUNKS_OFFSET;
	// t -= FREE_CHUNKS_OFFSET;
	// mergeChunks(t + CHUNKS_OFFSET, tmp + CHUNKS_OFFSET, TINY);

	// tmp = *getFreeChunksCollector(TINY);
	// t = tmp->next;

	// tmp -= FREE_CHUNKS_OFFSET;
	// t -= FREE_CHUNKS_OFFSET;
	// mergeChunks(t + CHUNKS_OFFSET, tmp + CHUNKS_OFFSET, TINY);

	// tmp = *getFreeChunksCollector(TINY);
	// t = tmp->next;

	// tmp -= FREE_CHUNKS_OFFSET;
	// t -= FREE_CHUNKS_OFFSET;
	// mergeChunks(t + CHUNKS_OFFSET, tmp + CHUNKS_OFFSET, TINY);



	// // mergeChunks(*getFreeChunksCollector(TINY) - FREE_CHUNKS_OFFSET + CHUNKS_OFFSET, tmp + CHUNKS_OFFSET, TINY);
	// // mergeChunks((*getFreeChunksCollector(TINY))->next  - FREE_CHUNKS_OFFSET + CHUNKS_OFFSET, (*getFreeChunksCollector(TINY))->next->next  - FREE_CHUNKS_OFFSET + CHUNKS_OFFSET, TINY);

	// // deleteNode(getFreeChunksCollector(TINY), (*getFreeChunksCollector(TINY))->next);
	// printList(getGarbageCollector(), GARBAGE_COLLECTOR_OFFSET);
	// printList(getFreeChunksCollector(TINY), FREE_CHUNKS_OFFSET);
	// _ptr *list = *getChunksCollector(meta->ptr + CHUNKS_OFFSET);

	// while (list)
	// {
	// 	meta = (_metaData *)(list - CHUNKS_OFFSET);
	// 	printf("size: %ld\n", meta->size);
	// 	if (meta->isFree)
	// 		print("FREE\n");
	// 	else
	// 		print("USED\n");
	// 	list = list->next;
	// }
	

	// printList(getChunksCollector(meta->ptr + CHUNKS_OFFSET), FREE_CHUNKS_OFFSET);
	// printList(getGarbageCollector(), GARBAGE_COLLECTOR_OFFSET);
	// printList(getFreeChunksCollector(SMALL), FREE_CHUNKS_OFFSET);
	// printList(getFreeChunksCollector(LARGE), FREE_CHUNKS_OFFSET);
	
	return 0;
}