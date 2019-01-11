CC = gcc
header = dexparser.h chunk.h import_dex.h string_item.h
src = chunk.c import_dex.c string_item.c main.c
target = dex_parser

$(target) : $(src) $(header)
	$(CC) -w -o $@ $^
clean:
		rm *.o $(target)
