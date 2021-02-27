#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

struct TOC_Member{
uint16_t type;
uint16_t id;
uint32_t length; //maybe.
} toc_member;

FILE *fp;
FILE *extract;
struct TOC_Member *toc;

//struct TOC_Member asdf;
//asdf.type=0;
//asdf.id=0;
//asdf.length=0;

int main(int argc, char *argv[]){
int path=0;
if(argc==1){
	printf("Reads Qualcomm Brew program resource files. (.bar)\nType \"dumpbar --help\" for help.\n");
	exit(0);
}
for(int i=1;i<argc;i++){
	if(!strcmp(argv[i],"--help")){
		printf("Usage: dumpbar [options] -o <file>\n");
		exit(0);
	}
	if(!strcmp(argv[i],"-o")){
		if(i+1>argc){
			exit(0);
		}
		path=i+1;
	}
}
if(path==0){
	printf("No File Specified\n");
	exit(0);
}
fp=fopen(argv[path],"r");
if(fp==NULL){
	perror(argv[path]);
	exit(0);
}
fseek(fp,0,SEEK_END);
long file_size=(int)ftell(fp);
printf("%s: %li byte large file\n",argv[path],file_size);
rewind(fp);
int16_t *buffer=malloc(sizeof(int16_t)*4);
fread(buffer,sizeof(int16_t),4,fp);//17 1 1
int16_t header[]={17,1,1};
for(int i=0;i<3;i++){
	if(header[i]!=buffer[i]){
		printf("May or may not be a .bar file\n"); //check file header.
		exit(0);
	}
}


printf("r/fileheaderchecksout\n");
printf("%i\n",sizeof(toc_member));
printf("Number of Elements: %i\n",buffer[3]);
int total_count=buffer[3];
rewind(fp);
fseek(fp,(long)0x08,SEEK_SET);
int32_t toc_offset[]={0};
fread(toc_offset,sizeof(int32_t),1,fp);
printf("TOC_offset: 0x%08x\n",toc_offset[0]);
rewind(fp);
fseek(fp,(long)toc_offset[0],SEEK_SET);
toc=malloc(sizeof(toc_member)*total_count);
fread(toc,sizeof(toc_member),total_count,fp);
for(int i=0;i<total_count;i++){
	printf("Mod resource %i type: 0x%04x\n",i+1,toc[i].type);
	printf("Mod resource %i id: 0x%04x\n",i+1,toc[i].id);
	printf("Mod resource %i length?: 0x%08x\n",i+1,toc[i].length);
}
rewind(fp);
fseek(fp,(long)16,SEEK_SET);
uint32_t offset_table_offset[]={0,0,0};//start address,number of mod resources,end address
fread(offset_table_offset,sizeof(uint32_t),3,fp);
uint32_t offset_table_start=offset_table_offset[0];
uint32_t offset_table_len=offset_table_offset[1];
printf("Offset to table containing offsets: 0x%08x\n",offset_table_start);
printf("Number of mod resources %i\n",offset_table_len);
//printf("Length of offset table: %i\n",offset_table_offset[3]-offset_table_offset[1]);
uint32_t *offset_table=malloc(sizeof(uint32_t)*offset_table_len);
rewind(fp);
fseek(fp,(long)offset_table_start,SEEK_SET);
fread(offset_table,sizeof(uint32_t),offset_table_len,fp);
uint16_t current[1];
char *dd=malloc(sizeof(char)*512);
char *output_name=malloc(sizeof(char)*32);
for(int i=0;i<offset_table_len;i++){
	printf("Offset %i:0x%08x\n",i+1,offset_table[i]);
	fread(current,sizeof(current),1,fp);
	sprintf(output_name,"modrsc0x%04x.%i",toc[i].id,toc[i].type);
	if(i<offset_table_len-1){
		sprintf(dd,"dd if=%s of=%s bs=1 skip=%i count=%i status=progress",argv[path],output_name,offset_table[i]+2,offset_table[i+1]-(offset_table[i]+2));
	}else{
		sprintf(dd,"dd if=%s of=%s bs=1 skip=%i status=progress",argv[path],output_name,offset_table[i]+2);
	}
	printf("%s\n",dd);
	system(dd);
}
}
