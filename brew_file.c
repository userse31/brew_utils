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
char DO_EXTRACT=0;

void extract_mime_contents(char *src, char *dest, unsigned int skip_len){
	if(DO_EXTRACT){
		printf("Extracting to %s...\n",dest);
		snprintf(command,sizeof(char)*512,"dd if=%s of=%s bs=1 skip=%i status=none",src,dest,skip_len);
		system(command);
	}
}

int main(int argc, char *argv[]){
if(argc<2){
	printf("Usage:brew_file <file> [options]\n-x <file name>: extract\n");
	exit(0);
}
command=malloc(sizeof(char)*512);
if(command==NULL){
	printf("Cannot malloc!\n");
	exit(0);
}
if(argc>=4){
	printf("%s\n",argv[2]);
	if(!strcmp("-x",argv[2])){
		printf("Yes\n");
		DO_EXTRACT=1;
	}
}

fp=fopen(argv[1],"r");
if(fp==NULL){
	printf("Cannot open %s\n",argv[1]);
	exit(0);
}

//Is it a MIF or a BAR file?
header=malloc(sizeof(char)*MIF_SIZE);
fread(header,sizeof(char),MIF_SIZE,fp);//Read the first 6 bytes of the file.
if(header[0]==0x11&&header[1]==0&&header[2]==0x01&&header[3]==0&&header[4]==0x01&&header[5]==0){
	printf("A BREW MIF or BAR file.\n");
	exit(0);
}

//Get MIME Media Type.
if(header!=NULL){
	free(header);
}
header=malloc(sizeof(char)*64);
rewind(fp);
fread(header,sizeof(char),64,fp);//Get the first 64 bytes.
char *MIME_TYPE=malloc(sizeof(char)*64);
strncpy(MIME_TYPE,header,sizeof(char)*64);
printf("MIME Type: %s\n",MIME_TYPE);
if(!strcmp("image/bci",MIME_TYPE)){
	printf("BCI image file.\n");
	if(DO_EXTRACT){
		extract_mime_contents(argv[1],argv[3],10);
	}
	exit(0);
}
if(!strcmp("image/bmp",MIME_TYPE)){
	printf("Bitmap image file.\n");
	if(DO_EXTRACT){
		extract_mime_contents(argv[1],argv[3],10);
	}
	exit(0);
}

//If all fails:
printf("Unknown, or not a BREW file.\n");
}
/*
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
}*/
