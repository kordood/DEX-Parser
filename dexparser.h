#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

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

typedef struct pChunk_item{
	uint32_t *pLink;
	uint32_t *pString_ids;
	uint32_t *pMap;
//	uint32_t pMap_size;
	uint32_t *pType_ids;
	uint32_t *pProto_ids;
	uint32_t *pField_ids;
	uint32_t *pMethod_ids;
	uint32_t *pClass_defs;
	uint32_t *pData;
} pChunk_item;

typedef struct map_item{
	uint32_t size;
	uint32_t *pList;
} map_item;

typedef struct map_item_format{
	uint16_t type;
	uint16_t unused;
	uint32_t size;
	uint32_t offset;
} map_format;

void isLittleEndian(uint32_t fp);
uint32_t getHeaderSize(uint32_t fp);
void header_slice(uint32_t fp, uint32_t header_size);
void *make_chunk(uint32_t fp, void *p, uint32_t offset, uint32_t size);
void alloc_chunk(uint32_t fp, uint32_t * pItem, uint32_t offset, uint32_t size);
void init_chunk(uint32_t fp);
void print_header();

_Bool littleEndian = 1;
header_item *pHeader;
pChunk_item Chunk;
map_item map;
