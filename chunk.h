#include "dexparser.h"
void *make_chunk(uint32_t fp, void *p, uint32_t offset, uint32_t size);
void alloc_chunk(uint32_t fp, void *pItem, uint32_t offset, uint32_t size, _Bool unmap);
void init_chunk(uint32_t fp);
void delete_chunk(uint32_t fp);

