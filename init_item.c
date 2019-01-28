#include "init_item.h"

void initList_string_ids_offset(uint32_t fp, string_data_item *pString_list, pChunk_item **pChunk){		// Input listed strings to string_data_item
	uint32_t offset;
	uleb128 size;

	for(size_t i = 0; i < pHeader->string_ids_size; i++){
		offset = (**pChunk).pString_ids[i];
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

void initList_type(type_list *pType_list, pChunk_item *pChunk, string_data_item *pString_list){		// Input data to type_list
    for(size_t i = 0; i < pHeader->type_ids_size; i++){
        pType_list[i].size = pString_list[(*pChunk).pType_ids[i]].utf16_size;
        pType_list[i].list = mmap(0, pType_list[i].size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
        pType_list[i].list = pString_list[(*pChunk).pType_ids[i]].data;
    }
}
