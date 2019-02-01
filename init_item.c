#include "init_item.h"

void initList_string_ids_offset(uint32_t fp, string_data_item *pString_list, pChunk_item **pChunk){		// Input listed strings to string_data_item
	uint32_t offset;
	uleb128 size;

	for(size_t i = 0; i < (*pFileLayout).pHeader->string_ids_size; i++){
		offset = (**pChunk).pString_data_off[i];
		lseek(fp, offset, SEEK_SET);
		read(fp, &size, sizeof(uleb128));
		(pString_list[i]).utf16_size = size;

		pString_list[i].data = mmap(0, sizeof(uint8_t) * (pString_list[i]).utf16_size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
		read(fp, pString_list[i].data, sizeof(uint8_t) * (pString_list[i]).utf16_size);
	}
}

void init_type_list(type_list *pTypeList, uint32_t *pType_ids, uint32_t size){
        (*pTypeList).size = size;
        (*pTypeList).list = mmap(0, sizeof(type_item) * size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);    // Allocate pType_list
        for(size_t i = 0; i < (*pTypeList).size; i++){
            (*pTypeList).list[i] = pType_ids[i];
        }
}

void init_proto_param(uint32_t fp, type_list *pTypeList, proto_id_item *pItem, uint32_t size){
    uint32_t offset;
    uint32_t tmp;
    for(size_t i = 0; i < size; i++){
        offset = pItem[i].parameters_off;
        if(offset != 0){
            lseek(fp, offset, SEEK_SET);
            read(fp, &tmp, sizeof(uint32_t));
            pTypeList[i].size = tmp;
            pTypeList[i].list = mmap(0, sizeof(type_item) * pTypeList[i].size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);    // Allocate pType_list
            for(size_t j = 0; j < pTypeList[i].size; j++){
                lseek(fp, offset + sizeof(uint32_t) + (sizeof(uint16_t) * j), SEEK_SET);    // offset + size + array index(ushort size)
                read(fp, &pTypeList[i].list[j], sizeof(uint16_t));
            }
        }
    }
}
