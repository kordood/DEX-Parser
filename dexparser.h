#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#define TRUE 1
#define FALSE 0
#define HEADER_FRONT 11
#define NO_INDEX 0xffffffff
#define ENDIAN_CONSTANT 0x12345678
#define REVERSE_ENDIAN_CONSTANT 0x78563412

enum access_flags{
	ACC_PUBLIC = 0x1,
	ACC_PRIVATE = 0x2,
	ACC_PROTECTED = 0x4,
	ACC_STATIC = 0x8,
	ACC_FINAL = 0x10,
	ACC_SYNCHRONIZED = 0x20,
	ACC_VOLATILE = 0x40,
	ACC_BRIDGE = 0x40,
	ACC_TRANSIENT = 0x80,
	ACC_VARARGS = 0x80,
	ACC_NATIVE = 0x100,
	ACC_INTERFACE = 0x200,
	ACC_ABSTRACT = 0x400,
	ACC_STRICT = 0x800,
	ACC_SYNTHETIC = 0x1000,
	ACC_ANNOTATION = 0x2000,
	ACC_ENUM = 0x4000,
	unused = 0x8000,
	ACC_CONSTRUCTOR = 0x10000,
	ACC_DECLARED_SYNCHRONIZED = 0x20000,
};

typedef uint8_t uleb128;

typedef struct header_item{
	uint8_t magic[8];
	uint32_t checksum;
	uint8_t signature[20];
	uint32_t file_size;
	uint32_t header_size;
	uint32_t endian_tag;
	uint32_t link_size;
	uint32_t link_off;
	uint32_t map_off;
	uint32_t string_ids_size;
	uint32_t string_ids_off;
	uint32_t type_ids_size;
	uint32_t type_ids_off;
	uint32_t proto_ids_size;
	uint32_t proto_ids_off;
	uint32_t field_ids_size;
	uint32_t field_ids_off;
	uint32_t method_ids_size;
	uint32_t method_ids_off;
	uint32_t class_defs_size;
	uint32_t class_defs_off;
	uint32_t data_size;
	uint32_t data_off;
} header_item;

typedef struct map_item{
	uint16_t type;
	uint16_t unused;
	uint32_t size;
	uint32_t offset;
} map_item;

typedef struct map_list{
	uint32_t size;
	map_item *pList;
} map_list;

typedef struct proto_id_item{
	uint32_t shorty_idx;
	uint32_t return_type_idx;
	uint32_t parameters_off;
} proto_id_item;

typedef struct field_id_item{
	uint16_t class_idx;
	uint16_t type_idx;
	uint32_t name_idx;
} field_id_item;

typedef struct method_id_item{
	uint16_t class_idx;
	uint16_t proto_idx;
	uint32_t name_idx;
} method_id_item;

typedef struct class_def_item{
	uint32_t class_idx;
	uint32_t access_flags;
	uint32_t superclass_idx;
	uint32_t interfaces_off;
	uint32_t source_file_idx;
	uint32_t annotations_off;
	uint32_t class_data_off;
	uint32_t static_values_off;
} class_def_item;

typedef uint32_t string_id_item;

typedef struct pChunk_item{
	uint32_t *pLink;
	string_id_item *pString_data_off;
	uint32_t *pMap;
	uint32_t *pType_ids;
	proto_id_item *pProto_ids;
	field_id_item *pField_ids;
	method_id_item *pMethod_ids;
	class_def_item *pClass_defs;
	uint32_t *pData;
} pChunk_item;

typedef struct method_handle_item{
	uint16_t method_handle_type;
	uint16_t unused;
	uint16_t field_or_method_id;
	uint16_t unused_2;
} method_handle_item;

typedef struct string_data_item{
//	uint32_t string_data_off;
	uleb128 utf16_size;
	uint8_t *data;
}	string_data_item;

typedef uint16_t type_item;

typedef struct type_list{
	uint32_t size;
	type_item *list;
} type_list;

// need to learn about uleb128
typedef struct encoded_field{
	uleb128 field_idx_diff;
	uleb128 access_flags;
} encoded_field;

typedef struct encoded_method{
	uleb128 method_idx_diff;
	uleb128 access_flags;
	uleb128 code_off;
} encoded_method;

typedef struct class_data_item{
	uleb128 static_fields_size;
	uleb128 instance_fields_size;
	uleb128 direct_methods_size;
	uleb128 virtual_methods_size;
	encoded_field *static_fields;
	encoded_field *instance_fields;
	encoded_method *direct_methods;
	encoded_method *virtual_methods;
} class_data_item;

typedef struct encoded_value{
	uint8_t value_type;
	uint8_t *value;
} encoded_value;

typedef struct annotation_element{
	uleb128 name_idx;
	encoded_value value;
} annotation_element;

typedef struct file_layout{
	header_item header;
	string_id_item *string_ids;
	//type_id_item *type_ids;
	proto_id_item *proto_ids;
	field_id_item *field_ids;
	method_id_item *method_ids;
	class_def_item *class_defs;
	method_handle_item *method_handles;
	uint8_t *data;
	uint8_t *link_data;
} file_layout;

header_item *pHeader;
map_list map;
