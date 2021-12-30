#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "heads.h"

//any-qualcomm-brew-file
//figure out what type of file a brew file is.
//Remember, brew is a utf-16 based operating system!

FILE *fp;
char *header;
char strip_contents=0;
char *command;

int main(int argc, char *argv[]){
if(argc<3){
	printf("Usage:brew_file [options] <file>\n-s: strip contents\n-n: nothing\n");
	exit(0);
}
command=malloc(sizeof(char)*512);
if(command==NULL){
	printf("Cannot malloc!\n");
	exit(0);
}
if(!strcmp(argv[1],"-s")){
	printf("Stripping Contents\n");
	strip_contents=1;
}
fp=fopen(argv[1],"r");
if(fp==NULL){
	printf("Cannot open %s\n",argv[1]);
	exit(0);
}
//png images
header=malloc(sizeof(char)*IMAGE_SIZE);
fread(header,sizeof(char),IMAGE_SIZE,fp);
if(!strcmp(header,IMAGE_HEADER)){
	printf("PNG Image\n");
	if(strip_contents){
		sprintf(command,"dd if=./%s of=./%s.png bs=1 skip=%i status=none",argv[2],argv[2],IMAGE_SKIP);
		system(command);
	}
	exit(0);
}
//file format for mif and bar files.
free(header);
int16_t mif_header[]=MIF_HEADER;
header=malloc(sizeof(int16_t)*MIF_SIZE);
fread(header,sizeof(int16_t),MIF_SIZE,fp);
int checks_out=1;
for(int i=0;i<3;i++){
	if(header[i]!=mif_header[i]){
		checks_out=0;
	}
}
if(checks_out){
	printf("A Brew MIF or BAR file.\n");
	exit(0);
}
printf("Unknown or not a Brew file\n");
}
