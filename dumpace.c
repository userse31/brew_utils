#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <strings.h>

FILE *fp;

int main(int argc, char *argv[]){
	printf("Not implemented.\n");
	exit(0);
	if(argc<2){
		printf("dumpace <Ace.bin>\nDumps information from the SPH-M330 \"Ace.dat\" file.\n");
		exit(0);
	}
	fp=fopen(argv[1],"r");
	if(fp==NULL){
		perror(argv[1]);
		exit(0);
	}
}
