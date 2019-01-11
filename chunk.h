#include "dexparser.h"
void *alloc_chunk(uint32_t fp, void *pItem, uint32_t offset, uint32_t size, _Bool unmap);
void init_chunk(uint32_t fp, pChunk_item *pChunk);
void delete_chunk(uint32_t fp, pChunk_item *pChunk);

