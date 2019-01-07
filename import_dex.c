#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>

void isLittleEndian(uint32_t fp);
uint32_t getHeaderSize(uint32_t fp);

_Bool littleEndian = 1;

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
		printf("%d\n", header_size);
		lseek(fp, 0, SEEK_SET);
		uint8_t binary[header_size];
		read(fp, binary, sizeof(uint8_t)*header_size);

		for(size_t i = 0; i < header_size; i++){
			printf("%02x", binary[i]);
		}
		printf("%d\n", header_size);
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

	printf("%d\n", header_size);

	return header_size;
}
