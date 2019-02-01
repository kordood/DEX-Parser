#include "print.h"

//using typeList(string view) example: printf("%-40s\t", pString_list[(*pTypeList).list[pItem[i].return_type_idx]].data);

void print_all(uint32_t fp, pChunk_item **pChunk, string_data_item *pString_list, type_list *paramTypeList, map_list *mapList){
	print_string_item(pString_list, (*pFileLayout).pHeader->string_ids_size);
	print_type_list(pString_list);
	print_link((**pChunk).pLink, (*pFileLayout).pHeader->link_size);
	/* useless
	   print_string_ids((**pChunk).pString_data_off, (*pFileLayout).pHeader->string_ids_size);
	   print_type_ids((**pChunk).pType_ids, pString_list, (*pFileLayout).pHeader->type_ids_size);
	 */
	print_proto_ids((**pChunk).pProto_ids, pString_list, (*pFileLayout).pHeader->proto_ids_size);
	print_proto_param(paramTypeList, pString_list, (*pFileLayout).pHeader->proto_ids_size);
	print_field_ids((**pChunk).pField_ids, pString_list, (*pFileLayout).pHeader->field_ids_size);
	print_method_ids((**pChunk).pMethod_ids, pString_list, (*pFileLayout).pHeader->method_ids_size);
	print_class_defs((**pChunk).pClass_defs, pString_list, (*pFileLayout).pHeader->class_defs_size);
	print_map_list(mapList);
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

void print_type_list(string_data_item *pString_list){
	printf("\n<type list>\n");
	for(size_t i = 0; i < typeList.size; i++){
		printf("%d: %s\n", i, pString_list[typeList.list[i]].data);
	}
}

void print_link(uint32_t *pItem, uint32_t size){
	printf("\n<link>\nsize: %d\n", size);
	for(size_t i = 0; i < size; i++){
		printf("%08x ", pItem[i]);
		if(((i+1) % 4) == 0 && i > 0){
			printf("\n");
		}
	}
	printf("\n");
}

void print_string_ids(uint32_t *pItem, uint32_t size){
	printf("\n<string_id_item>\nsize: %d\n", size);
	for(size_t i = 0; i < size; i++){
		printf("%08x ", pItem[i]);
		if(((i+1) % 4) == 0 && i > 0){
			printf("\n");
		}
	}
	printf("\n");
}

void print_type_ids(uint32_t *pItem, string_data_item *pString_list, uint32_t size){
	printf("\n<type_id_item>\nsize: %d\n", size);
	for(size_t i = 0; i < size; i++){
		printf("%s\n", pString_list[pItem[i]].data);
	}   
}

void print_proto_ids(proto_id_item *pItem, string_data_item *pString_list, uint32_t size){
	printf("\n<proto_id_item>\nsize: %d\n", size);
	printf("[shorty_idx]\t[return_type_idx]\t\t\t\t[parameters_off]\n");
	for(size_t i = 0; i < size; i++){
		printf("%-10s\t", pString_list[pItem[i].shorty_idx].data);
		//printf("%08x\t", pItem[i].return_type_idx);
		printf("%-40s\t", pString_list[typeList.list[pItem[i].return_type_idx]].data);
		printf("%x ", pItem[i].parameters_off);
		printf("\n");
	}
	printf("\n");
}

void print_proto_param(type_list *pTypeList, string_data_item *pString_list, uint32_t size){
	printf("\n");
	for(size_t i = 0; i < size; i++){
		if(pTypeList[i].list != '\0'){
			printf("tmp[%d]:\n", i);
			for(size_t j = 0; j < pTypeList[i].size; j++){
				printf("%s\t", pString_list[typeList.list[pTypeList[i].list[j]]].data);
			}
		}
		else{
			printf("tmp[%d]: NONE\n", i);
		}
		printf("\n");
	}
}

void print_field_ids(field_id_item *pItem, string_data_item *pString_list, uint32_t size){
	printf("\n<field_id_item>\nsize: %d\n", size);
	printf("[class_idx]\t\t\t\t\t[type_idx]\t\t\t\t\t[name_idx]\n");
	for(size_t i = 0; i < size; i++){
		printf("%-40s\t", pString_list[typeList.list[pItem[i].class_idx]].data);
		printf("%-40s\t", pString_list[typeList.list[pItem[i].type_idx]].data);
		printf("%-10s\t", pString_list[pItem[i].name_idx].data);
		printf("\n");
	}
	printf("\n");
}

void print_method_ids(method_id_item *pItem, string_data_item *pString_list, uint32_t size){
	printf("\n<method_id_item>\nsize: %d\n", size);
	printf("[class_idx]\t\t\t\t\t[proto_idx]\t[name_idx]\n");
	for(size_t i = 0; i < size; i++){
		printf("%-40s\t", pString_list[typeList.list[pItem[i].class_idx]].data);
		printf("%-10d\t", pItem[i].proto_idx); 
		printf("%-10s\t", pString_list[pItem[i].name_idx].data);
		printf("\n");
	}
	printf("\n");
}

void print_class_defs(class_def_item *pItem, string_data_item *pString_list, uint32_t size){
	enum access_flags aces_flag;
	printf("\n<class_def_item>\nsize: %d\n", size);
	printf("[cls_idx]\t\t\t\t\t[aces_flg]\n");
	printf("[sprcls_idx]\t\t\t\t\t[intrf_off]\t[src_file_idx]\t\t[anttn_off]\t[cls_dt_off]\t[sttc_val_off]\n");
	for(size_t i = 0; i < size; i++){
		aces_flag = pItem[i].access_flags;
		printf("%-40s\t", pString_list[typeList.list[pItem[i].class_idx]].data);
		print_access_flag(aces_flag);
		printf("\n%-40s\t", pString_list[typeList.list[pItem[i].superclass_idx]].data);
		printf("%d\t\t", pItem[i].interfaces_off);      // index to type_list
		if(pItem[i].source_file_idx == NO_INDEX){
			printf("NO_INDEX%-10s\t", "");
		}
		else{
			printf("%-20s\t", pString_list[pItem[i].source_file_idx].data);      // 
		}
		printf("%d\t\t", pItem[i].annotations_off);      // index to 
		printf("%d\t\t", pItem[i].class_data_off);      // index to 
		printf("%d\t", pItem[i].static_values_off);      // index to 
		printf("\n\n");
	}
	printf("\n");
}

void print_access_flag(enum access_flags aces_flag){
	if(aces_flag / ACC_DECLARED_SYNCHRONIZED == 1){
		aces_flag %= ACC_DECLARED_SYNCHRONIZED;
		printf("DECLARED_SYNCHRONIZED ");
	}
	if(aces_flag / ACC_CONSTRUCTOR == 1){
		aces_flag %= ACC_CONSTRUCTOR;
		printf("CONSTRUCTOR ");
	}
	if(aces_flag / unused == 1){
		aces_flag %= unused;
	}
	if(aces_flag / ACC_ENUM == 1){
		aces_flag %= ACC_ENUM;
		printf("ENUM ");
	}
	if(aces_flag / ACC_ANNOTATION == 1){
		aces_flag %= ACC_ANNOTATION;
		printf("ANNOTATION ");
	}
	if(aces_flag / ACC_SYNTHETIC == 1){
		aces_flag %= ACC_SYNTHETIC;
		printf("SYNTHETIC ");
	}
	if(aces_flag / ACC_STRICT == 1){
		aces_flag %= ACC_STRICT;
		printf("STRICT ");
	}
	if(aces_flag / ACC_ABSTRACT == 1){
		aces_flag %= ACC_ABSTRACT;
		printf("ABSTRACT ");
	}
	if(aces_flag / ACC_INTERFACE == 1){
		aces_flag %= ACC_INTERFACE;
		printf("INTERFACE ");
	}
	if(aces_flag / ACC_NATIVE == 1){
		aces_flag %= ACC_NATIVE;
		printf("NATIVE ");
	}
	if(aces_flag / ACC_VARARGS == 1){
		aces_flag %= ACC_VARARGS;
		printf("VARARGS ");
	}
	if(aces_flag / ACC_TRANSIENT == 1){
		aces_flag %= ACC_TRANSIENT;
		printf("TRANSIENT ");
	}
	if(aces_flag / ACC_BRIDGE == 1){
		aces_flag %= ACC_BRIDGE;
		printf("BRIDGE ");
	}
	if(aces_flag / ACC_VOLATILE == 1){
		aces_flag %= ACC_VOLATILE;
		printf("VOLATILE ");
	}
	if(aces_flag / ACC_SYNCHRONIZED == 1){
		aces_flag %= ACC_SYNCHRONIZED;
		printf("SYNCHRONIZED ");
	}
	if(aces_flag / ACC_FINAL == 1){
		aces_flag %= ACC_FINAL;
		printf("FINAL ");
	}
	if(aces_flag / ACC_STATIC == 1){
		aces_flag %= ACC_STATIC;
		printf("STATIC ");
	}
	if(aces_flag / ACC_PROTECTED == 1){
		aces_flag %= ACC_PROTECTED;
		printf("PROTECTED ");
	}
	if(aces_flag / ACC_PRIVATE == 1){
		aces_flag %=ACC_PRIVATE ;
		printf("PRIVATE ");
	}
	if(aces_flag / ACC_PUBLIC == 1){
		aces_flag %= ACC_PUBLIC;
		printf("PUBLIC ");
	}
}

void print_map_list(map_list *mapList){
	printf("\n<map list>\n");
	printf("[type]\t[unused]\t[size]\t\t[offset]\n");
	for(size_t i = 0; i < (*mapList).size; i++){
		printf("%04x\t", ((*mapList).pList[i]).type);
		printf("%04x\t\t", ((*mapList).pList[i]).unused);
		printf("%08x\t", ((*mapList).pList[i]).size);
		printf("%08x\n", ((*mapList).pList[i]).offset);
	}
}
