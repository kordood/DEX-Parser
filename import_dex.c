#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
	int fp;

	fp = open("./exp", O_RDONLY);
	if(fp == -1){
		printf("WRONG!\n");
	}
	else{
	char binary[10];

	read(fp, binary, sizeof(char)*10);

	printf("%02x", binary);
	}

	close(fp);

	return 0;
}
