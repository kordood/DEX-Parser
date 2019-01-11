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
		pHeader = (header_item *) malloc(sizeof(header_item));
		lseek(fp, 0, SEEK_SET);
		uint8_t header[header_size];
		read(fp, header, sizeof(uint8_t)*header_size);

		header_slice(fp, header_size);

		for(size_t i = 0; i < header_size; i++){
			printf("%02x", header[i]);
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
		littleEndian = TRUE;
	}
	else if(endian == 0x78563412){
		littleEndian = FALSE;
	}
	else{
		printf("not type\n");
	}
}

uint32_t getHeaderSize(uint32_t fp){	// default: LittleEndian, have to make processing BigEndian
	uint32_t header_size;

	lseek(fp, 36, SEEK_SET);
	read(fp, &header_size, sizeof(uint32_t));

	printf("%d\n", header_size);

	return header_size;
}

void header_slice(uint32_t fp, uint32_t header_size){
	read(fp, pHeader, sizeof(uint8_t)*header_size);

	for(size_t i = 0; i < 8; i++){
		printf("%02x", pHeader->magic[i]);
	}
	printf("magic\n");
	

}
