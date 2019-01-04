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

		for(size_t i = 0; i < 10; i++){
			printf("%02x", binary[i]);
		}
	}

	close(fp);

	return 0;
}
