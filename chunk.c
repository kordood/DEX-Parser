#include "chunk.h"

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
