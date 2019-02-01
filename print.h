#include "dexparser.h"

void print_all(uint32_t fp, file_layout **pChunk, string_data_item *pString_list, type_list *paramTypeList, map_list *mapList);
void print_string_item(string_data_item *pString_list, uint32_t size);
void print_type_list(string_data_item *pString_list);
void print_link(uint32_t *pItem, uint32_t size);
void print_string_ids(uint32_t *pItem, uint32_t size);
void print_type_ids(uint32_t *pItem, string_data_item *pString_list, uint32_t size);
void print_proto_ids(proto_id_item *pItem, string_data_item *pString_list, uint32_t size);
void print_proto_type(type_list *pTypeList, string_data_item *pString_list, uint32_t size);
void print_field_ids(field_id_item *pItem, string_data_item *pString_list, uint32_t size);
void print_method_ids(method_id_item *pItem, string_data_item *pString_list, uint32_t size);
void print_class_defs(class_def_item *pItem, string_data_item *pString_list, uint32_t size);
void print_access_flag(enum access_flags aces_flag);
void print_map_list(map_list *mapList);
