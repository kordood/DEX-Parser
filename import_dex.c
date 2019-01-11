#include "import_dex.h"
#include <stdlib.h>


void print_chunk(uint32_t * pItem, uint32_t size);	// temporary function

int main(){
	uint32_t fp;
	uint32_t header_size;

	fp = open("classes.dex", O_RDONLY);
	if(fp == -1){
		printf("WRONG!\n");
	}
	else{
//		isLittleEndian(fp);
		header_size = getHeaderSize(fp);
		pHeader = mmap(0, sizeof(header_item), PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);		//pHeader = (header_item *) malloc(sizeof(header_item));
		pChunk = mmap(0, sizeof(pChunk_item), PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);		//pHeader = (header_item *) malloc(sizeof(header_item));

		header_slice(fp, header_size);
		init_chunk(fp);
		delete_chunk(fp);
	}

	close(fp);

	munmap(pHeader, sizeof(header_item));
	munmap(pChunk, sizeof(pChunk_item));
	return 0;
}
/*
void isLittleEndian(uint32_t fp){
	uint32_t endian;
	lseek(fp, 40, SEEK_SET);
	read(fp, &endian, sizeof(uint32_t));

	if(endian == 0x12345678){
		littleEndian = TRUE;
	}
	else if(endian == 0x78563412){
		littleEndian = FALSE;
	}
	else{
		printf("not type\n");
	}
}*/

uint32_t getHeaderSize(uint32_t fp){	// default: LittleEndian, have to make processing BigEndian
	uint32_t header_size;

	lseek(fp, 36, SEEK_SET);
	read(fp, &header_size, sizeof(uint32_t));

	printf("%d\t\t\t\t\t\t\t      header size(int)\n", header_size);

	return header_size;
}

void header_slice(uint32_t fp, uint32_t header_size){
	lseek(fp, 0, SEEK_SET);
	read(fp, pHeader, sizeof(uint8_t)*header_size);
	print_header();
}
/*
void *make_chunk(uint32_t fp,void *p, uint32_t offset, uint32_t size){
	lseek(fp, offset, SEEK_SET);
	read(fp, p, size);
	
	return p;
}

void alloc_chunk(uint32_t fp, void *pItem, uint32_t offset, uint32_t size, _Bool unmap){
	if(unmap == TRUE){
		munmap(pItem, size);
	}
	else{
		printf("\nsize: %d\noffset: %d\n", size, offset);
	pItem = (uint32_t *)mmap(0, size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);		//pChunk->pString_ids = (uint32_t *) malloc(sizeof(uint32_t) * pHeader->string_ids_size);
	pItem = (uint32_t *)make_chunk(fp, (uint32_t *)pItem, offset, size);
	//print_chunk(pItem, size);
	}
}

void init_chunk(uint32_t fp){
	alloc_chunk(fp, pChunk->pLink, pHeader->link_off, sizeof(uint32_t) * pHeader->link_size, FALSE);
	alloc_chunk(fp, pChunk->pString_ids, pHeader->string_ids_off, sizeof(uint32_t) * pHeader->string_ids_size, FALSE);
	alloc_chunk(fp, pChunk->pType_ids, pHeader->type_ids_off, sizeof(uint32_t) * pHeader->type_ids_size, FALSE);
	alloc_chunk(fp, pChunk->pProto_ids, pHeader->proto_ids_off, sizeof(proto_id_item) * pHeader->proto_ids_size, FALSE);
	alloc_chunk(fp, pChunk->pField_ids, pHeader->field_ids_off, sizeof(field_id_item) * pHeader->field_ids_size, FALSE);
	alloc_chunk(fp, pChunk->pMethod_ids, pHeader->method_ids_off, sizeof(method_id_item) * pHeader->method_ids_size, FALSE);
	alloc_chunk(fp, pChunk->pClass_defs, pHeader->class_defs_off, sizeof(class_def_item) * pHeader->class_defs_size, FALSE);

	lseek(fp, pHeader->map_off, SEEK_SET);
	read(fp, &map.size, sizeof(uint32_t));
	alloc_chunk(fp, map.pList, pHeader->map_off, sizeof(map_item) * map.size, FALSE);
}

void delete_chunk(uint32_t fp){
	alloc_chunk(fp, pChunk->pLink, pHeader->link_off, sizeof(uint32_t) * pHeader->link_size, TRUE);
	alloc_chunk(fp, pChunk->pString_ids, pHeader->string_ids_off, sizeof(uint32_t) * pHeader->string_ids_size, TRUE);
	alloc_chunk(fp, pChunk->pType_ids, pHeader->type_ids_off, sizeof(uint32_t) * pHeader->type_ids_size, TRUE);
	alloc_chunk(fp, pChunk->pProto_ids, pHeader->proto_ids_off, sizeof(proto_id_item) * pHeader->proto_ids_size, TRUE);
	alloc_chunk(fp, pChunk->pField_ids, pHeader->field_ids_off, sizeof(field_id_item) * pHeader->field_ids_size, TRUE);
	alloc_chunk(fp, pChunk->pMethod_ids, pHeader->method_ids_off, sizeof(method_id_item) * pHeader->method_ids_size, TRUE);
	alloc_chunk(fp, pChunk->pClass_defs, pHeader->class_defs_off, sizeof(class_def_item) * pHeader->class_defs_size, TRUE);
	alloc_chunk(fp, map.pList, pHeader->map_off, sizeof(map_item) * map.size, TRUE);
}

void print_chunk(uint32_t * pItem, uint32_t size){
	for(size_t i = 0; i < size; i++){
		printf("%08x ", pItem[i]);
		if(((i+1) % 4) == 0 && i > 0){
			printf("\n");
		}
	}
	printf("\n");
}
*/

void print_header(){
	uint8_t *tmp = "";
	for(size_t i = 0; i < 8; i++){
		printf("%02x", pHeader->magic[i]);
	}
	printf("\t\t\t\t\t      magic\n");

	printf("%08x %-52s checksum\n", pHeader->checksum, tmp);

	for(size_t i = 0; i < 20; i++){
		printf("%02x", pHeader->signature[i]);
	}
	printf("\t\t      signature\n");
	
	printf("%08x %-52s file_size\n", pHeader->file_size, tmp);

	printf("%08x %-52s header_size\n", pHeader->header_size, tmp);

	printf("%08x %-52s endian_tag\n", pHeader->endian_tag, tmp);

	printf("%08x %-52s link_size\n", pHeader->link_size, tmp);

	printf("%08x %-52s link_off\n", pHeader->link_off, tmp);

	printf("%08x %-52s map_off\n", pHeader->map_off, tmp);

	printf("%08x %-52s string_ids_size\n", pHeader->string_ids_size, tmp);

	printf("%08x %-52s string_ids_off\n", pHeader->string_ids_off, tmp);

	printf("%08x %-52s type_ids_size\n", pHeader->type_ids_size, tmp);

	printf("%08x %-52s type_ids_off\n", pHeader->type_ids_off, tmp);

	printf("%08x %-52s proto_ids_size\n", pHeader->proto_ids_size, tmp);

	printf("%08x %-52s proto_ids_off\n", pHeader->proto_ids_off, tmp);

	printf("%08x %-52s field_ids_size\n", pHeader->field_ids_size, tmp);

	printf("%08x %-52s field_ids_off\n", pHeader->field_ids_off, tmp);

	printf("%08x %-52s method_ids_size\n", pHeader->method_ids_size, tmp);

	printf("%08x %-52s method_ids_off\n", pHeader->method_ids_off, tmp);

	printf("%08x %-52s class_defs_size\n", pHeader->class_defs_size, tmp);

	printf("%08x %-52s class_defs_off\n", pHeader->class_defs_off, tmp);

	printf("%08x %-52s data_size\n", pHeader->data_size, tmp);

	printf("%08x %-52s data_off\n", pHeader->data_off, tmp);
}

