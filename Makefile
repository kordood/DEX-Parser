CC = gcc
header = dexparser.h chunk.h import_dex.h init_item.h print_ids.h
src = chunk.c import_dex.c init_item.c print_ids.c main.c
target = dex_parser

$(target) : $(src) $(header)
	$(CC) -g -w -o $@ $^
clean:
		rm *.o $(target)
