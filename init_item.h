#include "dexparser.h"

void initList_string_ids_offset(uint32_t fp, string_data_item *pString_list, file_layout **pFileLayout);
void init_type_list(type_list *pTypeList, uint32_t *pType_ids, uint32_t size);
void init_proto_param(uint32_t fp, type_list *pTypeList, proto_id_item *pItem, uint32_t size);
void init_class_intrf(uint32_t fp, type_list *pTypeList, class_def_item *pItem, uint32_t size);
void init_anot_dir_item(uint32_t fp, anot_dir_item *pAnotDir, class_def_item *pItem, uint32_t size);
