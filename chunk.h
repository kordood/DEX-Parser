#include "dexparser.h"

void make_chunk(uint32_t fp, file_layout **pFileLayout);
void read_chunk(uint32_t fp, void *pItem, uint32_t offset, uint32_t size);
void delete_chunk(file_layout **pFileLayout);
void make_map_list(uint32_t fp, map_list *mapList);
void delete_map_list(map_list *mapList);
//void print_chunk(uint32_t *pItem, uint32_t type_size, uint32_t size);
