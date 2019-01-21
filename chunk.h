#include "dexparser.h"

void make_chunk(uint32_t fp, pChunk_item **pChunk);
void read_chunk(uint32_t fp, void *pItem, uint32_t offset, uint32_t size);
void delete_chunk(pChunk_item **pChunk);
//void print_link(uint32_t *pItem, uint32_t type_size, uint32_t size);
//void print_string_ids(uint32_t *pItem, uint32_t type_size, uint32_t size);
//void print_type_ids(uint32_t *pItem, string_data_item *pString_list, uint32_t size);
void print_chunk(uint32_t *pItem, uint32_t type_size, uint32_t size);
