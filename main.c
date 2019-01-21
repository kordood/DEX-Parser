#include "dexparser.h"

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
        header_slice(fp, header_size);
		print_header();


        pChunk = mmap(0, sizeof(pChunk_item), PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);      //pHeader = (header_item *) malloc(sizeof(header_item));
        make_chunk(fp, &pChunk);


    	pString_list = mmap(0, sizeof(string_data_item) * pHeader->string_ids_size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
		initList_string_ids_offset(fp, pString_list, &pChunk);

		delete_chunk(&pChunk);
//		deleteList_string_ids_offset(pString_list);
    }

    close(fp);

    munmap(pHeader, sizeof(header_item));
    munmap(pChunk, sizeof(pChunk_item));
    return 0;
}
