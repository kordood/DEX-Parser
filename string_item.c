#include "string_item.h"

void initList_string_ids_offset(uint32_t fp, string_data_item *pString_list, pChunk_item **pChunk){
	uint32_t offset;
	uleb128 size;
	
	for(size_t i = 0; i < pHeader->string_ids_size; i++){
		offset = (**pChunk).pString_ids[i];
		//printf("\noffset: %d\n", offset);
		lseek(fp, offset, SEEK_SET);
		//printf("utf: %p\n", &(pString_list[i]).utf16_size);
		read(fp, &size, sizeof(uleb128));
		(pString_list[i]).utf16_size = size;

		pString_list[i].data = mmap(0, sizeof(uint8_t) * (pString_list[i]).utf16_size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
		//printf("%d: %p\n", i, (pString_list[i]).data);
		read(fp, pString_list[i].data, sizeof(uint8_t) * (pString_list[i]).utf16_size);
			printf("%d: ", i);
		for(size_t j = 0; j < pString_list[i].utf16_size; j++){
			printf("%c", pString_list[i].data[j]);
		}
			printf("\n");
	}
}


/*
void initList_string_ids_offset(uint32_t fp, pChunk_item *pChunk){
	string_data_item *pString_list;
	uint32_t offset;
    pString_list = mmap(0, sizeof(string_data_item) * pHeader->string_ids_size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0); 
    for(size_t i = 0; i < pHeader->string_ids_size; i++){
        offset = pChunk->pString_ids[i];
        pString_list[i].string_data_off = offset;
        lseek(fp, offset, SEEK_SET);
        read(fp, &pString_list[i].utf16_size, sizeof(uleb128));
        pString_list[i].data = alloc_string_data(pString_list[i].data, pString_list[i].utf16_size, FALSE);
	printf("%d %p\n", i, pString_list[i].data);
    }   
		printf("%s\n", *(pString_list[10].data));
	address = (uint32_t *) pString_list;
}
*/
void deleteList_string_ids_offset(string_data_item *pString_list){
    for(size_t i = 0; i < pHeader->string_ids_size; i++){
        pString_list[i].data = alloc_string_data(pString_list[i].data, pString_list[i].utf16_size, TRUE);
		//printf("%d %x\n", i, pString_list[i].data);
    }   
}

void *alloc_string_data(uint8_t *addr, uleb128 size, _Bool unmap){
    if(unmap == 1){ 
        munmap(addr, sizeof(uint8_t) * size); 
    }   
    else{
    addr = mmap(0, sizeof(uint8_t) * size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0); 
    }   
}

