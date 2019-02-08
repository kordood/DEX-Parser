#include "init_item.h"

void initList_string_ids_offset(uint32_t fp, string_data_item *pString_list, file_layout **pFileLayout){		// Input listed strings to string_data_item
	uint32_t offset;
	uleb128 size;

	for(size_t i = 0; i < pHeader->string_ids_size; i++){
		offset = (**pFileLayout).pString_ids[i];
		lseek(fp, offset, SEEK_SET);
		read(fp, &size, sizeof(uleb128));
		(pString_list[i]).utf16_size = size;

		pString_list[i].data = mmap(0, sizeof(uint8_t) * (pString_list[i]).utf16_size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
		read(fp, pString_list[i].data, sizeof(uint8_t) * (pString_list[i]).utf16_size);
	}
}

void init_type_list(type_list *pTypeList, uint32_t *pType_ids, uint32_t size){
	(*pTypeList).size = size;
	(*pTypeList).list = mmap(0, sizeof(type_item) * size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);    // Allocate pType_list
	for(size_t i = 0; i < (*pTypeList).size; i++){
		(*pTypeList).list[i] = pType_ids[i];
	}
}

void init_proto_param(uint32_t fp, type_list *pTypeList, proto_id_item *pItem, uint32_t size){
	uint32_t offset;
	uint32_t tmp;
	for(size_t i = 0; i < size; i++){
		offset = pItem[i].parameters_off;
		if(offset != 0){
			lseek(fp, offset, SEEK_SET);
			read(fp, &tmp, sizeof(uint32_t));
			pTypeList[i].size = tmp;
			pTypeList[i].list = mmap(0, sizeof(type_item) * pTypeList[i].size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);    // Allocate pType_list
			for(size_t j = 0; j < pTypeList[i].size; j++){
				lseek(fp, offset + sizeof(uint32_t) + (sizeof(uint16_t) * j), SEEK_SET);    // offset + size + array index(ushort size)
				read(fp, &pTypeList[i].list[j], sizeof(uint16_t));
			}
		}
	}
}

void init_class_intrf(uint32_t fp, type_list *pTypeList, class_def_item *pItem, uint32_t size){
	uint32_t offset;
	uint32_t tmp;
	for(size_t i = 0; i < size; i++){
		offset = pItem[i].interfaces_off;
		if(offset != 0){
			lseek(fp, offset, SEEK_SET);
			read(fp, &tmp, sizeof(uint32_t));
			pTypeList[i].size = tmp;
			pTypeList[i].list = mmap(0, sizeof(type_item) * pTypeList[i].size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);    // Allocate pType_list
			for(size_t j = 0; j < pTypeList[i].size; j++){
				lseek(fp, offset + sizeof(uint32_t) + (sizeof(uint16_t) * j), SEEK_SET);    // offset + size + array index(ushort size)
				read(fp, &pTypeList[i].list[j], sizeof(uint16_t));
			}
		}
	}
}

void init_anot_dir_item(uint32_t fp, anot_dir_item *pAnotDir, class_def_item *pItem, uint32_t size){
	uint32_t offset;
	uint32_t tmp;
	for(size_t i = 0; i < size; i++){
		offset = pItem[i].annotations_off;
		if(offset != 0){
			lseek(fp, offset, SEEK_SET);
			read(fp, &pAnotDir[i], sizeof(anot_dir_item));
			pAnotDir[i].field_annotations = mmap(0, sizeof(field_anot) * pAnotDir[i].fields_size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);    // Allocate 
			pAnotDir[i].method_annotations = mmap(0, sizeof(method_anot) * pAnotDir[i].annotated_methods_size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);    // Allocate
			pAnotDir[i].parameter_annotations = mmap(0, sizeof(param_anot) * pAnotDir[i].annotated_parameters_size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);    // Allocate
			for(size_t j = 0; j < pAnotDir[i].fields_size; j++){
				lseek(fp, offset + (sizeof(uint32_t) * 4) + (sizeof(field_anot) * j), SEEK_SET);    // offset + size + array index(field_anot size)
				read(fp, &pAnotDir[i].field_annotations[j], sizeof(field_anot));
			}
			for(size_t j = 0; j < pAnotDir[i].annotated_methods_size; j++){
				lseek(fp, offset + (sizeof(uint32_t) * 4) + (sizeof(field_anot) * pAnotDir[i].fields_size) + (sizeof(method_anot) * j), SEEK_SET);    // offset + size + array index(method_anot size)
				read(fp, &pAnotDir[i].method_annotations[j], sizeof(method_anot));
			}	
			for(size_t j = 0; j < pAnotDir[i].annotated_parameters_size; j++){
				lseek(fp, offset + (sizeof(uint32_t) * 4) + (sizeof(field_anot) * pAnotDir[i].fields_size) + (sizeof(method_anot) * pAnotDir[i].annotated_methods_size) + (sizeof(param_anot) * j), SEEK_SET);    // offset + size + array index(param_anot size)
				read(fp, &pAnotDir[i].field_annotations[j], sizeof(param_anot));
			}
		}
	}
}
