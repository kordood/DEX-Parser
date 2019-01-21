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
		//      isLittleEndian(fp);
		header_size = getHeaderSize(fp);
		pHeader = mmap(0, sizeof(header_item), PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);     //pHeader = (header_item *) malloc(sizeof(header_item));
		header_slice(fp, header_size);
		print_header();

		pChunk = mmap(0, sizeof(pChunk_item), PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);      //pHeader = (header_item *) malloc(sizeof(header_item));
		make_chunk(fp, &pChunk);

		pString_list = mmap(0, sizeof(string_data_item) * pHeader->string_ids_size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
		initList_string_ids_offset(fp, pString_list, &pChunk);

		pType_list = mmap(0, sizeof(type_list) * pHeader->type_ids_size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
		//	print_all_ids(&pChunk, pString_list);
		//	print_proto_ids((*pChunk).pProto_ids, pString_list, pHeader->proto_ids_size);
		initList_type(pType_list, pChunk, pString_list);
		//print_type_list(pType_list);

		print_proto_ids((*pChunk).pProto_ids, pString_list, pType_list, pHeader->proto_ids_size);

		delete_chunk(&pChunk);
		deleteList_string_ids_offset(pString_list);
	}

	close(fp);

	munmap(pHeader, sizeof(header_item));
	munmap(pChunk, sizeof(pChunk_item));
	return 0;
}
