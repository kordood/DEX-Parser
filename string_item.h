#include "dexparser.h"

void initList_string_ids_offset(uint32_t fp, string_data_item *pString_list, pChunk_item **pChunk);
void *alloc_string_data(uint8_t *addr, uleb128 size, _Bool unmap);
void deleteList_string_ids_offset(string_data_item *pString_list);

