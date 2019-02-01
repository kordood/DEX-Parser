#include "dexparser.h"

void make_type_list(type_list *pType_list, file_layout *pFileLayout, string_data_item *pString_list);

type_list typeList;
int main(){
	uint32_t fp;
	uint32_t header_size;

	file_layout *pFileLayout;
//	map_list mapList;
	string_data_item *pString_list;
	type_list *proto_param;


	fp = open("classes.dex", O_RDONLY);
	if(fp == -1){
		printf("WRONG!\n");
	}
	else{
		isLittleEndian(fp);
		header_size = getHeaderSize(fp);
		pFileLayout = mmap(0, sizeof(file_layout), PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);     //(*pFileLayout).pHeader = (header_item *) malloc(sizeof(header_item));
		pHeader = mmap(0, sizeof(header_item), PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);     //(*pFileLayout).pHeader = (header_item *) malloc(sizeof(header_item));
		header_slice(fp, header_size);		// Input data to header
		print_header();

		make_map_list(fp, &(*pFileLayout).mapList);

		//pFileLayout = mmap(0, sizeof(pFileLayout_item), PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);      // Allocate pFileLayout
		make_chunk(fp, &pFileLayout);		// Input data to each Chunk

		pString_list = mmap(0, sizeof(string_data_item) * pHeader->string_ids_size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);	// Allocate pString_lis
		initList_string_ids_offset(fp, pString_list, &pFileLayout);		// Input data to string list

		init_type_list(&typeList, (*pFileLayout).pType_ids, pHeader->type_ids_size);
		proto_param = mmap(0, sizeof(type_list) * pHeader->type_ids_size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);	// Allocate pString_list
		init_proto_param(fp, proto_param, (*pFileLayout).pProto_ids, pHeader->proto_ids_size);

		print_all(fp, &pFileLayout, pString_list, proto_param, &(*pFileLayout).mapList);	// print all items
		//print_class_defs((*pFileLayout).pClass_defs, pString_list, pType_list, (*pFileLayout).pHeader->class_defs_size);


		// unmapping 
		delete_proto_param(proto_param, pHeader->proto_ids_size);
		delete_type_list(&typeList, pHeader->type_ids_size);
		deleteList_string_ids_offset(pString_list);
		delete_chunk(&pFileLayout);
		delete_map_list(&(*pFileLayout).mapList);

		munmap(proto_param, sizeof(type_list) * pHeader->type_ids_size);
		munmap(pString_list, sizeof(string_data_item) * pHeader->string_ids_size);
		munmap(pFileLayout, sizeof(file_layout));
		munmap(pHeader, sizeof(header_item));
	}

	close(fp);

	return 0;
}
