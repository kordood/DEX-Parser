#include "dexparser.h"

void print_all(pChunk_item **pChunk, string_data_item *pString_list, type_list *pType_list);
void print_string_item(string_data_item *pString_list, uint32_t size);
void print_type_list(type_list *pType_list);
void print_link(uint32_t *pItem, uint32_t size);
void print_string_ids(uint32_t *pItem, uint32_t size);
void print_type_ids(uint32_t *pItem, string_data_item *pString_list, uint32_t size);
void print_proto_ids(proto_id_item *pItem, string_data_item *pString_list, type_list *pType_list, uint32_t size);
void print_field_ids(field_id_item *pItem, string_data_item *pString_list, type_list *pType_list, uint32_t size);
void print_method_ids(method_id_item *pItem, string_data_item *pString_list, type_list *pType_list, uint32_t size);
void print_class_defs(class_def_item *pItem, string_data_item *pString_list, type_list *pType_list, uint32_t size);
void print_access_flag(enum access_flags aces_flag);
