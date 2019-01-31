#include "dexparser.h"

void make_type_list(type_list *pType_list, pChunk_item *pChunk, string_data_item *pString_list);

type_list typeList;
int main(){
	uint32_t fp;
	uint32_t header_size;

	pChunk_item *pChunk;
	map_list mapList;
	string_data_item *pString_list;


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

		init_type_list_for(&typeList, (*pChunk).pType_ids, pHeader->type_ids_size);
		//print_proto_ids((*pChunk).pProto_ids, pString_list, &typeList, pHeader->proto_ids_size);


		print_proto_type(fp, (*pChunk).pProto_ids, pHeader->proto_ids_size, pString_list);
		print_all(fp, &pChunk, pString_list, &mapList);	// print all items
		//print_class_defs((*pChunk).pClass_defs, pString_list, pType_list, pHeader->class_defs_size);
/*
		uint32_t tmp;
		lseek(fp, ((*pChunk).pProto_ids[5]).parameters_off, SEEK_SET);
		read(fp, tmp, sizeof(uint32_t));
		printf("tmp: %08x\n", tmp);
*/
		delete_chunk(&pChunk);
		delete_map_list(&mapList);
		deleteList_string_ids_offset(pString_list);

		munmap(pString_list, sizeof(string_data_item) * pHeader->string_ids_size);
		munmap(pChunk, sizeof(pChunk_item));
		munmap(pHeader, sizeof(header_item));
	}

	close(fp);

	return 0;
}
