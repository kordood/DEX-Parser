#include "delete_item.h"

void deleteList_string_ids_offset(string_data_item *pString_list){      // Unalloc string list
    for(size_t i = 0; i < pHeader->string_ids_size; i++){
        munmap(pString_list[i].data, pString_list[i].utf16_size);
    }   
}

void delete_type_list(type_list *pTypeList, uint32_t size){
    munmap((*pTypeList).list, sizeof(type_item) * size);
}

void delete_proto_param(type_list *pTypeList, uint32_t size){
    for(size_t i = 0; i < size; i++){
        munmap(pTypeList[i].list, sizeof(type_item) * pTypeList[i].size);
    }
}
