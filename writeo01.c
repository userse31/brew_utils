#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

FILE *fp;
FILE *fp_write;
char *buffer;//1024
char *id;//64
int _id;
char *string;//1024
int str_len;
int str_len_total;
int str_count_total;
char *tmp;//1
int _done;
int32_t *header;//[number of strings,combined string length], 2

int parse_line(){
int semicolon=0;
for(int i=0;i<64;i++){
	if(buffer[i]==';'){
		semicolon=i+1;
		break;
	}
	id[i]=buffer[i];
}
_id=atoi(id);
int str_ptr=0;
for(int i=semicolon;i<1024;i++){
	if(buffer[i]==0){
		str_len=str_ptr+1;
		return 0;
	}
	string[str_ptr]=buffer[i];
	str_ptr++;
}
}

int clear_buffers(){
for(int i=0;i<1024;i++){
	buffer[i]=0;
}
for(int i=0;i<64;i++){
	id[i]=0;
}
for(int i=0;i<1024;i++){
	string[i]=0;
}
}

int next_line(){
int tmp2;
for(int i=0;i<1024;i++){
	tmp2=fread(tmp,sizeof(char),1,fp);
	if(tmp2==0){
		_done=1;
		return 0;
	}
	if(tmp[0]==0){
		return 0;
	}
	buffer[i]=tmp[0];
}
}

int main(int argc, char *argv[]){
_done=0;
str_len_total=0;
str_count_total=0;
if(argc<3){
	printf("./writeo01 <in> <out>\n");
	return 0;
}
fp=fopen(argv[1],"r");
fp_write=fopen(argv[2],"w+");
if(fp==NULL || fp_write==NULL){
	printf("%s or %s not opened\n",argv[1],argv[2]);
	return 0;
}
buffer=malloc(sizeof(char)*1024);
id=malloc(sizeof(char)*64);
string=malloc(sizeof(char)*1024);
tmp=malloc(sizeof(char)*1);
header=malloc(sizeof(int32_t)*2);
if(buffer==NULL || id==NULL || string==NULL || tmp==NULL || header==NULL){
	printf("NULL Pointer\n");
	exit(0);
}
//create header
header[0]=0;//Number of Strings
header[1]=0;//Total string length;
fwrite(header,sizeof(int32_t),2,fp_write);
while(_done==0){
next_line();
parse_line();
if(id[0]==0){
	printf("Done\n");
	goto _update_header;
}
str_count_total++;
str_len_total+=str_len;
printf("id:%i\n",_id);
printf("string:%s\n",string);
printf("string length:%i\n",str_len);
header[0]=(int32_t)_id;//string id
header[1]=(int32_t)str_len;//String length
fwrite(header,sizeof(int32_t),2,fp_write);//header for string
fwrite(string,sizeof(char),str_len,fp_write);//string itself
clear_buffers();
}
_update_header:
printf("String Count: %i\n",str_count_total);
printf("String Length Total: %i\n",str_len_total);
header[0]=str_count_total;
header[1]=str_len_total;
rewind(fp_write);
fwrite(header,sizeof(int32_t),2,fp_write);//write correct header.
}
