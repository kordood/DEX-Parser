#include "dexparser.h"

void isLittleEndian(uint32_t fp);
uint32_t getHeaderSize(uint32_t fp);
void header_slice(uint32_t fp, uint32_t header_size);
void print_header();

_Bool littleEndian = TRUE;
