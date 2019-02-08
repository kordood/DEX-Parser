#include "print.h"

//using typeList(string view) example: printf("%-40s\t", pString_list[(*pTypeList).list[pItem[i].return_type_idx]].data);

void print_all(uint32_t fp, file_layout **pFileLayout, string_data_item *pString_list, type_list *paramTypeList, map_list *mapList){
	print_map_list(mapList);
	print_link((**pFileLayout).pLink, pHeader->link_size);
	/* useless
	   print_string_ids((**pFileLayout).pString_data_off, pHeader->string_ids_size);
	   print_type_ids((**pFileLayout).pType_ids, pHeader->type_ids_size);
	 */
	print_string_item(pString_list, pHeader->string_ids_size);
	print_type_list(pString_list, &(**pFileLayout).typeList);
	print_proto_ids((**pFileLayout).pProto_ids, pString_list, &(**pFileLayout).typeList, pHeader->proto_ids_size);
	print_proto_param(paramTypeList, pString_list, &(**pFileLayout).typeList, pHeader->proto_ids_size);
	print_field_ids((**pFileLayout).pField_ids, pString_list, &(**pFileLayout).typeList, pHeader->field_ids_size);
	print_method_ids((**pFileLayout).pMethod_ids, pString_list, &(**pFileLayout).typeList, pHeader->method_ids_size);
	print_class_defs((**pFileLayout).pClass_defs, pString_list, &(**pFileLayout).typeList, pHeader->class_defs_size);
	print_anot_dir((**pFileLayout).pAnotDir, (**pFileLayout).pMethod_ids, pString_list, &(**pFileLayout).typeList, pHeader->class_defs_size);
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

void print_string_ids(string_id_item *pItem, uint32_t size){
	printf("\n<string_id_item>\nsize: %d\n", size);
	for(size_t i = 0; i < size; i++){
		printf("%08x ", pItem[i]);
		if(((i+1) % 4) == 0 && i > 0){
			printf("\n");
		}
	}
	printf("\n");
}

void print_type_ids(type_id_item *pItem, uint32_t size){
	printf("\n<type_id_item>\nsize: %d\n", size);
	for(size_t i = 0; i < size; i++){
		printf("%08x ", pItem[i]);
		if(((i+1) % 4) == 0 && i > 0){
			printf("\n");
		}
	}   
	printf("\n");
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

void print_type_list(string_data_item *pString_list, type_list *typeList){
	printf("\n<type list>\n");
	for(size_t i = 0; i < (*typeList).size; i++){
		printf("%d: %s\n", i, pString_list[(*typeList).list[i]].data);
	}
}

void print_proto_ids(proto_id_item *pItem, string_data_item *pString_list, type_list *typeList, uint32_t size){
	printf("\n<proto_id_item>\nsize: %d\n", size);
	printf("[shorty_idx]\t[return_type_idx]\t\t\t\t[parameters_off]\n");
	for(size_t i = 0; i < size; i++){
		printf("%-10s\t", pString_list[pItem[i].shorty_idx].data);
		//printf("%08x\t", pItem[i].return_type_idx);
		printf("%-40s\t", pString_list[(*typeList).list[pItem[i].return_type_idx]].data);
		printf("%x ", pItem[i].parameters_off);
		printf("\n");
	}
	printf("\n");
}

void print_proto_param(type_list *pTypeList, string_data_item *pString_list, type_list *typeList, uint32_t size){
	printf("\n");
	for(size_t i = 0; i < size; i++){
		if(pTypeList[i].list != '\0'){
			printf("parameter[%d]:\n", i);
			for(size_t j = 0; j < pTypeList[i].size; j++){
				printf("%s\t", pString_list[(*typeList).list[pTypeList[i].list[j]]].data);
			}
		}
		else{
			printf("parameter[%d]: NONE\n", i);
		}
		printf("\n");
	}
}

void print_anot_dir(anot_dir_item *pAnotDir, method_id_item *pMethod_ids, string_data_item *pString_list, type_list *typeList, uint32_t size){
	printf("\n<annotations_directory>\n");
	for(size_t i = 0; i < size; i++){
		if(pAnotDir[i].class_annotations_off != 0 || pAnotDir[i].fields_size != 0 || pAnotDir[i].annotated_methods_size != 0 || pAnotDir[i].annotated_parameters_size != 0){
			printf("anotDir[%d]: ", i);
			printf("%08x\t%08x\t%08x\t%08x\t", pAnotDir[i].class_annotations_off, pAnotDir[i].fields_size, pAnotDir[i].annotated_methods_size, pAnotDir[i].annotated_parameters_size);
			if(pAnotDir[i].fields_size != 0){
				print_field_anot(pAnotDir[i].field_annotations, pAnotDir[i].fields_size);
			}
			if(pAnotDir[i].annotated_methods_size != 0){
				print_method_anot(pAnotDir[i].method_annotations, pMethod_ids, pString_list, typeList, pAnotDir[i].annotated_methods_size);
			}
			if(pAnotDir[i].annotated_parameters_size != 0){
				print_param_anot(pAnotDir[i].parameter_annotations, pAnotDir[i].annotated_parameters_size);
			}
		}
		else{
			printf("anotDir[%d]: NONE", i);
		}
		printf("\n");
	}
}

void print_field_anot(field_anot *pFieldAnot, uint32_t size){
	printf("\n\t<field_annotations>\n");
	for(size_t i = 0; i < size; i++){
		printf("\t%d: %d %08x\n", i, pFieldAnot[i].field_idx, pFieldAnot[i].annotations_off);
	}
}

void print_method_anot(method_anot *pMethodAnot, method_id_item *pMethod_ids, string_data_item *pString_list, type_list *typeList, uint32_t size){
	printf("\n\t<method_annotations>\n");
	for(size_t i = 0; i < size; i++){
		printf("\t%d: %d %08x\n", i, pMethodAnot[i].method_idx, pMethodAnot[i].annotations_off);
		print_method(pMethodAnot[i].method_idx, pMethod_ids, pString_list, typeList);
	}
}

void print_param_anot(param_anot *pParamAnot, uint32_t size){
	printf("\n\t<parameter_annotations>\n");
	for(size_t i = 0; i < size; i++){
		printf("\t%d: %d %08x\n", i, pParamAnot[i].method_idx, pParamAnot[i].annotations_off);
	}
}

void print_field_ids(field_id_item *pItem, string_data_item *pString_list, type_list *typeList, uint32_t size){
	printf("\n<field_id_item>\nsize: %d\n", size);
	printf("[class_idx]\t\t\t\t\t[type_idx]\t\t\t\t\t[name_idx]\n");
	for(size_t i = 0; i < size; i++){
		printf("%-40s\t", pString_list[(*typeList).list[pItem[i].class_idx]].data);
		printf("%-40s\t", pString_list[(*typeList).list[pItem[i].type_idx]].data);
		printf("%-10s\t", pString_list[pItem[i].name_idx].data);
		printf("\n");
	}
	printf("\n");
}

void print_method_ids(method_id_item *pItem, string_data_item *pString_list, type_list *typeList, uint32_t size){
	printf("\n<method_id_item>\nsize: %d\n", size);
	printf("[class_idx]\t\t\t\t\t[proto_idx]\t[name_idx]\n");
	for(size_t i = 0; i < size; i++){
		printf("%-40s\t", pString_list[(*typeList).list[pItem[i].class_idx]].data);
		printf("%-10d\t", pItem[i].proto_idx); 
		printf("%-10s\t", pString_list[pItem[i].name_idx].data);
		printf("\n");
	}
	printf("\n");
}

void print_method(uint32_t index, method_id_item *pItem, string_data_item *pString_list, type_list *typeList){
	printf("\nmethod(%d): \n", index);
	printf("[class_idx]\t\t\t\t\t[proto_idx]\t[name_idx]\n");
		printf("%-40s\t", pString_list[(*typeList).list[pItem[index].class_idx]].data);
		printf("%-10d\t", pItem[index].proto_idx); 
		printf("%-10s\t", pString_list[pItem[index].name_idx].data);
		printf("\n");
	printf("\n");
}

void print_class_defs(class_def_item *pItem, string_data_item *pString_list, type_list *typeList, uint32_t size){
	enum access_flags aces_flag;
	printf("\n<class_def_item>\nsize: %d\n", size);
	printf("[cls_idx]\t\t\t\t\t[aces_flg]\n");
	printf("[sprcls_idx]\t\t\t\t\t[intrf_off]\t[src_file_idx]\t\t[anttn_off]\t[cls_dt_off]\t[sttc_val_off]\n");
	for(size_t i = 0; i < size; i++){
		aces_flag = pItem[i].access_flags;
		printf("%-40s\t", pString_list[(*typeList).list[pItem[i].class_idx]].data);
		print_access_flag(aces_flag);
		printf("\n%-40s\t", pString_list[(*typeList).list[pItem[i].superclass_idx]].data);
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

void print_class_intrf(type_list *pTypeList, string_data_item *pString_list, type_list *typeList, uint32_t size){
	printf("\n");
	for(size_t i = 0; i < size; i++){
		if(pTypeList[i].list != '\0'){
			printf("tmp[%d]:\n", i);
			for(size_t j = 0; j < pTypeList[i].size; j++){
				printf("%s\t", pString_list[(*typeList).list[pTypeList[i].list[j]]].data);
			}
		}
		else{
			printf("tmp[%d]: NONE\n", i);
		}
		printf("\n");
	}
}

void print_type_codes(enum type_codes typeCode){
	switch(typeCode){
		case TYPE_ANNOTATIONS_DIRECTORY_ITEM:
			printf("ANNOTATIONS_DIRECTORY_ITEM ");
			break;
		case TYPE_ENCODED_ARRAY_ITEM:
			printf("ENCODED_ARRAY_ITEM ");
			break;
		case TYPE_ANNOTATION_ITEM:
			printf("ANNOTATION_ITEM ");
			break;
		case TYPE_DEBUG_INFO_ITEM:
			printf("DEBUG_INFO_ITEM ");
			break;
		case TYPE_STRING_DATA_ITEM:
			printf("STRING_DATA_ITEM ");
			break;
		case TYPE_CODE_ITEM:
			printf("CODE_ITEM ");
			break;
		case TYPE_CLASS_DATA_ITEM:
			printf("CLASS_DATA_ITEM ");
			break;
		case TYPE_ANNOTATION_SET_ITEM:
			printf("TYPE_ANNOTATION_SET_ITEM ");
			break;
		case TYPE_ANNOTATION_SET_REF_LIST:
			printf("ANNOTATION_SET_REF_LIST ");
			break;
		case TYPE_TYPE_LIST:
			printf("TYPE_LIST ");
			break;
		case TYPE_MAP_LIST:
			printf("MAP_LIST ");
			break;
		case TYPE_METHOD_HANDLE_ITEM:
			printf("METHOD_HANDLE_ITEM ");
			break;
		case TYPE_CALL_SITE_ID_ITEM:
			printf("CALL_SITE_ID_ITEM ");
			break;
		case TYPE_CLASS_DEF_ITEM:
			printf("CLASS_DEF_ITEM ");
			break;
		case TYPE_METHOD_ID_ITEM:
			printf("METHOD_ID_ITEM ");
			break;
		case TYPE_FIELD_ID_ITEM:
			printf("FIELD_ID_ITEM ");
			break;
		case TYPE_PROTO_ID_ITEM:
			printf("PROTO_ID_ITEM ");
			break;
		case TYPE_TYPE_ID_ITEM:
			printf("TYPE_ID_ITEM ");
			break;
		case TYPE_STRING_ID_ITEM:
			printf("PSTRING_ID_ITEM ");
			break;
		case TYPE_HEADER_ITEM:
			printf("HEADER_ITEM ");
			break;
	}
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
