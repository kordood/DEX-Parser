#include "dexparser.h"

void make_type_list(type_list *pType_list, pChunk_item *pChunk, string_data_item *pString_list);

type_list typeList;
int main(){
	uint32_t fp;
	uint32_t header_size;

	pChunk_item *pChunk;
	map_list mapList;
	string_data_item *pString_list;
	type_list *paramTypeList;


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

		make_map_list(fp, &mapList);
		pChunk = mmap(0, sizeof(pChunk_item), PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);      // Allocate pChunk
		make_chunk(fp, &pChunk);		// Input data to each Chunk

		pString_list = mmap(0, sizeof(string_data_item) * pHeader->string_ids_size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);	// Allocate pString_list
		initList_string_ids_offset(fp, pString_list, &pChunk);		// Input data to string list

		init_type_list(&typeList, (*pChunk).pType_ids, pHeader->type_ids_size);
		paramTypeList = mmap(0, sizeof(type_list) * pHeader->type_ids_size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);	// Allocate pString_list
		init_proto_param(fp, paramTypeList, (*pChunk).pProto_ids, pHeader->proto_ids_size);

		print_all(fp, &pChunk, pString_list, paramTypeList, &mapList);	// print all items
		//print_class_defs((*pChunk).pClass_defs, pString_list, pType_list, pHeader->class_defs_size);


		/* unmapping */
		delete_proto_param(paramTypeList, pHeader->proto_ids_size);
		delete_type_list(&typeList, pHeader->type_ids_size);
		deleteList_string_ids_offset(pString_list);
		delete_chunk(&pChunk);
		delete_map_list(&mapList);

		munmap(paramTypeList, sizeof(type_list) * pHeader->type_ids_size);
		munmap(pString_list, sizeof(string_data_item) * pHeader->string_ids_size);
		munmap(pChunk, sizeof(pChunk_item));
		munmap(pHeader, sizeof(header_item));
	}

	close(fp);

	return 0;
}
