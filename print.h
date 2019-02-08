#include "dexparser.h"

void print_all(uint32_t fp, file_layout **pFileLayout, string_data_item *pString_list, type_list *paramTypeList, map_list *mapList);
void print_string_item(string_data_item *pString_list, uint32_t size);
void print_type_list(string_data_item *pString_list, type_list *typeList);
void print_link(uint32_t *pItem, uint32_t size);
void print_string_ids(uint32_t *pItem, uint32_t size);
void print_type_ids(uint32_t *pItem, uint32_t size);
void print_proto_ids(proto_id_item *pItem, string_data_item *pString_list, type_list *typeList, uint32_t size);
void print_proto_type(type_list *pTypeList, string_data_item *pString_list,type_list *typeList, uint32_t size);
void print_field_ids(field_id_item *pItem, string_data_item *pString_list, type_list *typeList, uint32_t size);
void print_method_ids(method_id_item *pItem, string_data_item *pString_list, type_list *typeList, uint32_t size);
void print_method(uint32_t index, method_id_item *pItem, string_data_item *pString_list, type_list *typeList);
void print_class_defs(class_def_item *pItem, string_data_item *pString_list, type_list *typeList, uint32_t size);
void print_anot_dir(anot_dir_item *pAnotDir, method_id_item *pMethod_ids, string_data_item *pString_list, type_list *typeList, uint32_t size);
void print_field_anot(field_anot *pFieldAnot, uint32_t size);
void print_method_anot(method_anot *pMethodAnot, method_id_item *pMethod_ids, string_data_item *pString_list, type_list *typeList, uint32_t size);
void print_param_anot(param_anot *pParamAnot, uint32_t size);
void print_access_flag(enum access_flags aces_flag);
void print_map_list(map_list *mapList);
