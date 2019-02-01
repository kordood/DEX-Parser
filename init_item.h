#include "dexparser.h"

void initList_string_ids_offset(uint32_t fp, string_data_item *pString_list, file_layout **pFileLayout);
void deleteList_string_ids_offset(string_data_item *pString_list);
void init_type_list(type_list *pTypeList, uint32_t *pType_ids, uint32_t size);
void delete_type_list(type_list *pTypeList, uint32_t size);
void init_proto_param(uint32_t fp, type_list *pTypeList, proto_id_item *pItem, uint32_t size);
void delete_proto_param(type_list *pTypeList, uint32_t size);
