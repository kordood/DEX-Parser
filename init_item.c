#include "init_item.h"

void initList_string_ids_offset(uint32_t fp, string_data_item *pString_list, pChunk_item **pChunk){		// Input listed strings to string_data_item
	uint32_t offset;
	uleb128 size;

	for(size_t i = 0; i < pHeader->string_ids_size; i++){
		offset = (**pChunk).pString_data_off[i];
		lseek(fp, offset, SEEK_SET);
		read(fp, &size, sizeof(uleb128));
		(pString_list[i]).utf16_size = size;

		pString_list[i].data = mmap(0, sizeof(uint8_t) * (pString_list[i]).utf16_size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
		read(fp, pString_list[i].data, sizeof(uint8_t) * (pString_list[i]).utf16_size);
	}
}

void deleteList_string_ids_offset(string_data_item *pString_list){		// Unalloc string list
	for(size_t i = 0; i < pHeader->string_ids_size; i++){
		munmap(pString_list[i].data, pString_list[i].utf16_size);
	}   
}

void init_type_list_for(type_list *pTypeList, uint32_t *pType_ids, uint32_t size){
        (*pTypeList).size = size;
        (*pTypeList).list = mmap(0, sizeof(type_item) * size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);    // Allocate pType_list
        for(size_t i = 0; i < (*pTypeList).size; i++){
            (*pTypeList).list[i] = pType_ids[i];
        }
}
