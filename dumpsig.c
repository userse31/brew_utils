#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

FILE *fp;
int file_path=0;

int main(int argc, char *argv[]){
if(argc==1){
	printf("dumpsig -o <file>\n");
	return 0;
}
for(int i=1;i<argc;i++){
	if(!strcmp(argv[i],"-o")){
		if((i+1)>argc){
			exit(0);
		}
		file_path=i+1;
	}
}
fp=fopen(argv[file_path],"r");
if(fp==NULL){
	printf("Cannot open %s\n",argv[file_path]);
	exit(0);
}
int16_t *header=malloc(sizeof(int16_t)*8);
fread(header,sizeof(int16_t),8,fp);
if(header[0]==2 && header[1]==2 && header[4]==2){
	printf("Does seem to be a sig file...\n");
}else{
	printf("May or may not be a sig file\n");
	//exit(0);
}
printf("Certificates: 0x%04x\n",header[2]);
printf("Header value 2: 0x%04x\n",header[3]);
}
