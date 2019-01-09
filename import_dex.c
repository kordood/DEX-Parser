#include "dexparser.h"
#include <stdlib.h>

int main(){
	uint32_t fp;
	uint32_t header_size;

	fp = open("classes.dex", O_RDONLY);
	if(fp == -1){
		printf("WRONG!\n");
	}
	else{
		isLittleEndian(fp);
		header_size = getHeaderSize(fp);
		pHeader = mmap(0, sizeof(header_item), PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);		//pHeader = (header_item *) malloc(sizeof(header_item));
		pChunk = (pChunk_item *) malloc(sizeof(pChunk_item));

		header_slice(fp, header_size);
		pChunk->pString_ids = (uint32_t *)mmap(0, sizeof(uint32_t) * pHeader->string_ids_size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);		//pChunk->pString_ids = (uint32_t *) malloc(sizeof(uint32_t) * pHeader->string_ids_size);
		printf("size and offset is %d\n%d\n", pHeader->string_ids_size, pHeader->string_ids_off);
		pChunk->pString_ids = (uint32_t *)make_chunk(fp, (uint32_t *)pChunk->pString_ids, pHeader->string_ids_off, sizeof(uint32_t) * pHeader->string_ids_size);
		for(size_t i = 0; i < pHeader->string_ids_size; i++){
			printf("%08x ", pChunk->pString_ids[i]);
			if(((i+1) % 4) == 0 && i > 0){
				printf("\n");
			}
		}
	}

	close(fp);

	return 0;
}

void isLittleEndian(uint32_t fp){
	uint32_t endian;
	lseek(fp, 40, SEEK_SET);
	read(fp, &endian, sizeof(uint32_t));

	if(endian == 0x12345678){
		littleEndian = 1;
	}
	else if(endian == 0x78563412){
		littleEndian = 0;
	}
	else{
		printf("not type\n");
	}
}

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

void *make_chunk(uint32_t fp,void *p, uint32_t offset, uint32_t size){
	lseek(fp, offset, SEEK_SET);
	read(fp, p, size);
	
	return p;
}

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
