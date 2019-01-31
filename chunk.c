#include "chunk.h"

void make_chunk(uint32_t fp, pChunk_item **pChunk){
    (**pChunk).pLink = (uint32_t *)mmap(0, sizeof(uint32_t) * pHeader->link_size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    (**pChunk).pString_data_off = (uint32_t *)mmap(0, sizeof(string_id_item) * pHeader->string_ids_size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    (**pChunk).pType_ids = (uint32_t *)mmap(0, sizeof(uint32_t) * pHeader->type_ids_size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    (**pChunk).pProto_ids = (uint32_t *)mmap(0, sizeof(proto_id_item) * pHeader->proto_ids_size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    (**pChunk).pField_ids = (uint32_t *)mmap(0, sizeof(field_id_item) * pHeader->field_ids_size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    (**pChunk).pMethod_ids = (uint32_t *)mmap(0, sizeof(method_id_item) * pHeader->method_ids_size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    (**pChunk).pClass_defs = (uint32_t *)mmap(0, sizeof(class_def_item) * pHeader->class_defs_size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);

	read_chunk(fp, (**pChunk).pLink, pHeader->link_off, sizeof(uint32_t) * pHeader->link_size);
	read_chunk(fp, (**pChunk).pString_data_off, pHeader->string_ids_off, sizeof(string_id_item) * pHeader->string_ids_size);
	read_chunk(fp, (**pChunk).pType_ids, pHeader->type_ids_off, sizeof(uint32_t) * pHeader->type_ids_size);
	read_chunk(fp, (**pChunk).pProto_ids, pHeader->proto_ids_off, sizeof(proto_id_item) * pHeader->proto_ids_size);
	read_chunk(fp, (**pChunk).pField_ids, pHeader->field_ids_off, sizeof(field_id_item) * pHeader->field_ids_size);
	read_chunk(fp, (**pChunk).pMethod_ids, pHeader->method_ids_off, sizeof(method_id_item) * pHeader->method_ids_size);
	read_chunk(fp, (**pChunk).pClass_defs, pHeader->class_defs_off, sizeof(class_def_item) * pHeader->class_defs_size);
}

void read_chunk(uint32_t fp, void *pItem, uint32_t offset, uint32_t size){
    lseek(fp, offset, SEEK_SET);
    read(fp, pItem, size);
//	printf("\nsize: %d\noffset: %d\npointer: %p\n", size, offset, pItem);
}

void delete_chunk(pChunk_item **pChunk){
	munmap((**pChunk).pLink, sizeof(uint32_t) * pHeader->link_size);
	munmap((**pChunk).pString_data_off, sizeof(string_id_item) * pHeader->string_ids_size);
	munmap((**pChunk).pType_ids, sizeof(uint32_t) * pHeader->type_ids_size);
	munmap((**pChunk).pProto_ids, sizeof(proto_id_item) * pHeader->proto_ids_size);
	munmap((**pChunk).pField_ids, sizeof(field_id_item) * pHeader->field_ids_size);
	munmap((**pChunk).pMethod_ids, sizeof(method_id_item) * pHeader->method_ids_size);
	munmap((**pChunk).pClass_defs, sizeof(class_def_item) * pHeader->class_defs_size);
}

void make_map_list(uint32_t fp, map_list *mapList){
    lseek(fp, pHeader->map_off, SEEK_SET);	// map size doesn't exist in header;
    read(fp, &(*mapList).size, sizeof(uint32_t));

	(*mapList).pList = (uint32_t *)mmap(0, sizeof(map_item) * (*mapList).size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	for(size_t i = 0; i < (*mapList).size; i++){
		lseek(fp, pHeader->map_off + sizeof(uint32_t) + (sizeof(map_item) * i), SEEK_SET);
		read(fp, &(*mapList).pList[i], sizeof(map_item));
	}
}

void delete_map_list(map_list *mapList){
	munmap((*mapList).pList, sizeof(map_item) * (*mapList).size);
}
/* maybe not using
void print_chunk(uint32_t *pItem, uint32_t type_size, uint32_t size){
	printf("print size: %d\n", size);
	for(size_t i = 0; i < (size / type_size); i++){
		printf("%08x ", pItem[i]);		//	printf("%08x ", (**pChunk).pString_data_off[i]);
		if(((i+1) % 4) == 0 && i > 0){
			printf("\n");
		}
	}
	printf("\n");
}*/
