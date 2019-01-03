#include <stdio.h>

typedef unsigned char ubyte;
typedef unsigned int uint;
typedef unsigned long ulong;

typedef struct header_item{
ubyte magic[8];
uint checksum;
ubyte signature[20];
uint file_size;
uint header_size;
uint endian_tag;
uint linksize;
uint map_off;
uint string_ids_size;
uint string_ids_off;
uint type_ids_size;
uint type_ids_off;
uint proto_ids_size;
uint proto_ids_off;
uint field_ids_size;
uint field_ids_off;
uint method_ids_size;
uint method_ids_off;
uint class_defs_size;
uint class_defs_off;
uint data_size;
uint data_off;
} header_item;


int main(void){
header_item header_item;
printf("Successed\n");
return 0;
}
