#include "dexparser.h"
/*
string_data_item *initList_string_ids_offset(uint32_t fp, pChunk_item *pChunk);
void *alloc_string_data(uint8_t *addr, uleb128 size, _Bool unmap);
void deleteList_string_ids_offset(string_data_item *pString_list);
*/
int main(){
    uint32_t fp;
    uint32_t header_size;
	pChunk_item *pChunk;
	string_data_item *pString_list;

    fp = open("classes.dex", O_RDONLY);
    if(fp == -1){
        printf("WRONG!\n");
    }
    else{
//      isLittleEndian(fp);
        header_size = getHeaderSize(fp);
        pHeader = mmap(0, sizeof(header_item), PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);     //pHeader = (header_item *) malloc(sizeof(header_item));
        pChunk = mmap(0, sizeof(pChunk_item), PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);      //pHeader = (header_item *) malloc(sizeof(header_item));

        header_slice(fp, header_size);
        init_chunk(fp, pChunk);
		pString_list = initList_string_ids_offset(fp, pChunk);
		deleteList_string_ids_offset(pString_list);
        delete_chunk(fp, pChunk);
    }

    close(fp);

    munmap(pHeader, sizeof(header_item));
    munmap(pChunk, sizeof(pChunk_item));
    return 0;
}
/*
string_data_item *initList_string_ids_offset(uint32_t fp, pChunk_item *pChunk){
	string_data_item *pString_list;
	uint32_t offset;
	pString_list = mmap(0, sizeof(string_data_item), PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	for(size_t i = 0; i < pHeader->string_ids_size; i++){
		offset = pChunk->pString_ids[i];
		pString_list[i].string_data_off = offset;
		lseek(fp, offset, SEEK_SET);
		read(fp, &pString_list[i].utf16_size, sizeof(uleb128));
		pString_list[i].data = alloc_string_data(pString_list[i].data, pString_list[i].utf16_size, FALSE);
	}
	return pString_list;
}

void deleteList_string_ids_offset(string_data_item *pString_list){
	for(size_t i = 0; i < pHeader->string_ids_size; i++){
		pString_list[i].data = alloc_string_data(pString_list[i].data, pString_list[i].utf16_size, TRUE);
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
*/
