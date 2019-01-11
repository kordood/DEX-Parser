#include "chunk.h"

void *alloc_chunk(uint32_t fp, void *pItem, uint32_t offset, uint32_t size, _Bool unmap){
	if(unmap == TRUE){
		munmap(pItem, size);
	}
	else{
	//	printf("\nsize: %d\noffset: %d\n", size, offset);
		pItem = (uint32_t *)mmap(0, size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);		//pChunk->pString_ids = (uint32_t *) malloc(sizeof(uint32_t) * pHeader->string_ids_size);
		lseek(fp, offset, SEEK_SET);
		read(fp, pItem, size);
//		print_chunk(pItem, size);
		return pItem;
	}
}

void init_chunk(uint32_t fp, pChunk_item *pChunk){
	pChunk->pLink = (uint32_t *)alloc_chunk(fp, pChunk->pLink, pHeader->link_off, sizeof(uint32_t) * pHeader->link_size, FALSE);
	pChunk->pString_ids = (uint32_t *)alloc_chunk(fp, pChunk->pString_ids, pHeader->string_ids_off, sizeof(uint32_t) * pHeader->string_ids_size, FALSE);
	pChunk->pType_ids = (uint32_t *)alloc_chunk(fp, pChunk->pType_ids, pHeader->type_ids_off, sizeof(uint32_t) * pHeader->type_ids_size, FALSE);
	pChunk->pProto_ids = (uint32_t *)alloc_chunk(fp, pChunk->pProto_ids, pHeader->proto_ids_off, sizeof(proto_id_item) * pHeader->proto_ids_size, FALSE);
	pChunk->pField_ids = (uint32_t *)alloc_chunk(fp, pChunk->pField_ids, pHeader->field_ids_off, sizeof(field_id_item) * pHeader->field_ids_size, FALSE);
	pChunk->pMethod_ids = (uint32_t *)alloc_chunk(fp, pChunk->pMethod_ids, pHeader->method_ids_off, sizeof(method_id_item) * pHeader->method_ids_size, FALSE);
	pChunk->pClass_defs = (uint32_t *)alloc_chunk(fp, pChunk->pClass_defs, pHeader->class_defs_off, sizeof(class_def_item) * pHeader->class_defs_size, FALSE);

	lseek(fp, pHeader->map_off, SEEK_SET);
	read(fp, &map.size, sizeof(uint32_t));
	map.pList = (uint32_t *)alloc_chunk(fp, map.pList, pHeader->map_off, sizeof(map_item) * map.size, FALSE);
}

void delete_chunk(uint32_t fp, pChunk_item *pChunk){
	pChunk->pLink = (uint32_t *)alloc_chunk(fp, pChunk->pLink, pHeader->link_off, sizeof(uint32_t) * pHeader->link_size, TRUE);
	pChunk->pString_ids = (uint32_t *)alloc_chunk(fp, pChunk->pString_ids, pHeader->string_ids_off, sizeof(uint32_t) * pHeader->string_ids_size, TRUE);
	pChunk->pType_ids = (uint32_t *)alloc_chunk(fp, pChunk->pType_ids, pHeader->type_ids_off, sizeof(uint32_t) * pHeader->type_ids_size, TRUE);
	pChunk->pProto_ids = (uint32_t *)alloc_chunk(fp, pChunk->pProto_ids, pHeader->proto_ids_off, sizeof(proto_id_item) * pHeader->proto_ids_size, TRUE);
	pChunk->pField_ids = (uint32_t *)alloc_chunk(fp, pChunk->pField_ids, pHeader->field_ids_off, sizeof(field_id_item) * pHeader->field_ids_size, TRUE);
	pChunk->pMethod_ids = (uint32_t *)alloc_chunk(fp, pChunk->pMethod_ids, pHeader->method_ids_off, sizeof(method_id_item) * pHeader->method_ids_size, TRUE);
	pChunk->pClass_defs = (uint32_t *)alloc_chunk(fp, pChunk->pClass_defs, pHeader->class_defs_off, sizeof(class_def_item) * pHeader->class_defs_size, TRUE);
	map.pList = (uint32_t *)alloc_chunk(fp, map.pList, pHeader->map_off, sizeof(map_item) * map.size, TRUE);
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
