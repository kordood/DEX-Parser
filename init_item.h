#include "dexparser.h"

void initList_string_ids_offset(uint32_t fp, string_data_item *pString_list, pChunk_item **pChunk);
void deleteList_string_ids_offset(string_data_item *pString_list);
void print_string_item(string_data_item *pString_list, uint32_t size);
void initList_type(type_list *pType_list, pChunk_item *pChunk, string_data_item *pString_list);
void print_type_list(type_list *pType_list);
