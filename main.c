#include "dexparser.h"

void make_type_list(type_list *pType_list, pChunk_item *pChunk, string_data_item *pString_list);

int main(){
	uint32_t fp;
	uint32_t header_size;

	pChunk_item *pChunk;
	string_data_item *pString_list;
	type_list *pType_list;


	fp = open("classes.dex", O_RDONLY);
	if(fp == -1){
		printf("WRONG!\n");
	}
	else{
		isLittleEndian(fp);
		header_size = getHeaderSize(fp);
		pHeader = mmap(0, sizeof(header_item), PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);     //pHeader = (header_item *) malloc(sizeof(header_item));
		header_slice(fp, header_size);		// Input data to header
		print_header();

		pChunk = mmap(0, sizeof(pChunk_item), PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);      // Allocate pChunk
		make_chunk(fp, &pChunk);		// Input data to each Chunk

		pString_list = mmap(0, sizeof(string_data_item) * pHeader->string_ids_size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);	// Allocate pString_list
		initList_string_ids_offset(fp, pString_list, &pChunk);		// Input data to string list

		pType_list = mmap(0, sizeof(type_list) * pHeader->type_ids_size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);	// Allocate pType_list
		initList_type(pType_list, pChunk, pString_list);	// Input data to type list

		print_all(&pChunk, pString_list, pType_list);	// print all items
		//print_class_defs((*pChunk).pClass_defs, pString_list, pType_list, pHeader->class_defs_size);

		delete_chunk(&pChunk);
		deleteList_string_ids_offset(pString_list);

		munmap(pString_list, sizeof(string_data_item) * pHeader->string_ids_size);
		munmap(pType_list, sizeof(type_list) * pHeader->type_ids_size);
		munmap(pChunk, sizeof(pChunk_item));
		munmap(pHeader, sizeof(header_item));
	}

	close(fp);

	return 0;
}
