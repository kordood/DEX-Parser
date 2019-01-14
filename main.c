#include "dexparser.h"

int main(){
    uint32_t fp;
    uint32_t header_size;
	pChunk_item *pChunk;
	string_data_item *pString_list;
	address = mmap(0, sizeof(uint32_t *), PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);

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
		//pString_list = (uint32_t *) initList_string_ids_offset(fp, pChunk);
		initList_string_ids_offset(fp, pChunk);
		pString_list = address;
		deleteList_string_ids_offset(pString_list);
        delete_chunk(fp, pChunk);
    }

    close(fp);

    munmap(pHeader, sizeof(header_item));
    munmap(pChunk, sizeof(pChunk_item));
	munmap(address, sizeof(uint32_t *));
    return 0;
}
