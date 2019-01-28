#include "print_ids.h"

void print_all(pChunk_item **pChunk, string_data_item *pString_list, type_list *pType_list){
	print_string_item(pString_list, pHeader->string_ids_size);
	print_type_list(pType_list);
	print_link((**pChunk).pLink, pHeader->link_size);
	print_string_ids((**pChunk).pString_ids, pHeader->string_ids_size);
	print_type_ids((**pChunk).pType_ids, pString_list, pHeader->type_ids_size);
	print_proto_ids((**pChunk).pProto_ids, pString_list, pType_list, pHeader->proto_ids_size);
	print_field_ids((**pChunk).pField_ids, pString_list, pType_list, pHeader->field_ids_size);
}

void print_string_item(string_data_item *pString_list, uint32_t size){
    printf("\n<string item>\n");
    for(size_t i = 0; i < size; i++){
        printf("%d: ", i);
        for(size_t j = 0; j < pString_list[i].utf16_size; j++){
            printf("%c", pString_list[i].data[j]);
        }
        printf("\n");
    }
}

void print_type_list(type_list *pType_list){
    printf("\n<type list>\n");
    for(size_t i = 0; i < pHeader->type_ids_size; i++){
        printf("%d: %s\n", i, pType_list[i].list);
    }
}

void print_link(uint32_t *pItem, uint32_t size){
	printf("\n<print link>\nsize: %d\n", size);
	for(size_t i = 0; i < size; i++){
		printf("%08x ", pItem[i]);      //  printf("%08x ", (**pChunk).pLink[i]);
		if(((i+1) % 4) == 0 && i > 0){
			printf("\n");
		}
	}
	printf("\n");
}

void print_string_ids(uint32_t *pItem, uint32_t size){
	printf("\n<print string_ids>\nsize: %d\n", size);
	for(size_t i = 0; i < size; i++){
		printf("%08x ", pItem[i]);      //  printf("%08x ", (**pChunk).pString_ids[i]);
		if(((i+1) % 4) == 0 && i > 0){
			printf("\n");
		}
	}
	printf("\n");
}

void print_type_ids(uint32_t *pItem, string_data_item *pString_list, uint32_t size){
	printf("\n<print type_ids>\nsize: %d\n", size);
	for(size_t i = 0; i < size; i++){
		printf("%s\n", pString_list[pItem[i]].data);
	}   
}

void print_proto_ids(proto_id_item *pItem, string_data_item *pString_list, type_list *pType_list, uint32_t size){
	printf("\n<print proto_ids>\nsize: %d\n", size);
	printf("[shorty_idx]\t[return_type_idx]\t\t\t\t[parameters_off]\n");
	for(size_t i = 0; i < size; i++){
		printf("%-10s\t", pString_list[pItem[i].shorty_idx].data);      //  printf("%08x ", (**pChunk).pLink[i]);
		printf("%-40s\t", pType_list[pItem[i].return_type_idx].list);      //  printf("%08x ", (**pChunk).pLink[i]);
		printf("%x ", pItem[i].parameters_off);      //  printf("%08x ", (**pChunk).pLink[i]);
			printf("\n");
	}
	printf("\n");
}

void print_field_ids(field_id_item *pItem, string_data_item *pString_list, type_list *pType_list, uint32_t size){
	printf("\n<print field_ids>\nsize: %d\n", size);
	printf("[class_idx]\t\t\t\t\t[type_idx]\t\t\t\t\t[name_idx]\n");
	for(size_t i = 0; i < size; i++){
		printf("%-40s\t", pType_list[pItem[i].class_idx].list);      //  printf("%08x ", (**pChunk).pLink[i]);
		printf("%-40s\t", pType_list[pItem[i].type_idx].list);      //  printf("%08x ", (**pChunk).pLink[i]);
		printf("%-10s\t", pString_list[pItem[i].name_idx].data);      //  printf("%08x ", (**pChunk).pLink[i]);
			printf("\n");
	}
	printf("\n");
}
