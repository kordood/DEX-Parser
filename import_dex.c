#include "import_dex.h"

void isLittleEndian(uint32_t fp){
	uint32_t endian;
	lseek(fp, 40, SEEK_SET);
	read(fp, &endian, sizeof(uint32_t));

	if(endian == ENDIAN_CONSTANT){
		littleEndian = TRUE;
		printf("little endian\n");
	}
	else if(endian == REVERSE_ENDIAN_CONSTANT){
		littleEndian = FALSE;
		printf("big endian\n");
	}
	else{
		printf("not type\n");
	}
}

uint32_t getHeaderSize(uint32_t fp){	// default: LittleEndian, have to make processing BigEndian
	uint32_t header_size;

	lseek(fp, 36, SEEK_SET);
	read(fp, &header_size, sizeof(uint32_t));

//	printf("%d\t\t\t\t\t\t\t      header size(int)\n", header_size);

	return header_size;
}

void header_slice(uint32_t fp, uint32_t header_size){
	lseek(fp, 0, SEEK_SET);
	read(fp, (*pFileLayout).pHeader, sizeof(uint8_t)*header_size);
//	print_header();
}

void print_header(){
	printf("\n<Header>\n");
	uint8_t *tmp = "";
	for(size_t i = 0; i < 8; i++){
		printf("%02x", (*(*pFileLayout).pHeader).magic[i]);
	}
	printf("\t\t\t\t\t      magic\n");

	printf("%08x %-52s checksum\n", (*(*pFileLayout).pHeader).checksum, tmp);

	for(size_t i = 0; i < 20; i++){
		printf("%02x", (*(*pFileLayout).pHeader).signature[i]);
	}
	printf("\t\t      signature\n");

	printf("%08x %-52s file_size\n", (*(*pFileLayout).pHeader).file_size, tmp);

	printf("%08x %-52s header_size\n", (*(*pFileLayout).pHeader).header_size, tmp);

	printf("%08x %-52s endian_tag\n", (*(*pFileLayout).pHeader).endian_tag, tmp);

	printf("%08x %-52s link_size\n", (*(*pFileLayout).pHeader).link_size, tmp);

	printf("%08x %-52s link_off\n", (*(*pFileLayout).pHeader).link_off, tmp);

	printf("%08x %-52s map_off\n", (*(*pFileLayout).pHeader).map_off, tmp);

	printf("%08x %-52s string_ids_size\n", (*(*pFileLayout).pHeader).string_ids_size, tmp);

	printf("%08x %-52s string_ids_off\n", (*(*pFileLayout).pHeader).string_ids_off, tmp);

	printf("%08x %-52s type_ids_size\n", (*(*pFileLayout).pHeader).type_ids_size, tmp);

	printf("%08x %-52s type_ids_off\n", (*(*pFileLayout).pHeader).type_ids_off, tmp);

	printf("%08x %-52s proto_ids_size\n", (*(*pFileLayout).pHeader).proto_ids_size, tmp);

	printf("%08x %-52s proto_ids_off\n", (*(*pFileLayout).pHeader).proto_ids_off, tmp);

	printf("%08x %-52s field_ids_size\n", (*(*pFileLayout).pHeader).field_ids_size, tmp);

	printf("%08x %-52s field_ids_off\n", (*(*pFileLayout).pHeader).field_ids_off, tmp);

	printf("%08x %-52s method_ids_size\n", (*(*pFileLayout).pHeader).method_ids_size, tmp);

	printf("%08x %-52s method_ids_off\n", (*(*pFileLayout).pHeader).method_ids_off, tmp);

	printf("%08x %-52s class_defs_size\n", (*(*pFileLayout).pHeader).class_defs_size, tmp);

	printf("%08x %-52s class_defs_off\n", (*(*pFileLayout).pHeader).class_defs_off, tmp);

	printf("%08x %-52s data_size\n", (*(*pFileLayout).pHeader).data_size, tmp);

	printf("%08x %-52s data_off\n", (*(*pFileLayout).pHeader).data_off, tmp);
}
