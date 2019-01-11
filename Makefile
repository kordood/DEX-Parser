CC = gcc
header = dexparser.h chunk.h import_dex.h
src = chunk.c import_dex.c
target = dex_parser

$(target) : $(src) $(header)
	$(CC) -w -o $@ $^
clean:
		rm *.o $(target)
