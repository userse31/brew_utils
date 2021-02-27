//Create key from encrypted and non-encrypted mif files

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *mif_enc;
FILE *mif_og;

unsigned char *mif1;
unsigned char *mif2;
unsigned char *key;

int main(int argc, char *argv[]){
int mif_enc_path=0;
int mif_og_path=0;
if(argc==1){
	printf("Use \"--help\" for usage details\n");
	return 0;
}
for(int i=1;i<argc;i++){
	if(!strcmp(argv[i],"--help")){
		printf("Does mif file cryptography (xor)\nmifcrypt -o1 <file1> -o2 <file2> > <output>\n");
		exit(0);
	}
	if(!strcmp(argv[i],"-o1")){
		if((i+1)>argc){
			exit(0);
		}else{
			mif_enc_path=i+1;
		}
	}
	if(!strcmp(argv[i],"-o2")){
		if((i+1)>argc){
			exit(0);
		}else{
			mif_og_path=i+1;
		}
	}
}
if(mif_enc_path==0){
	printf("No file specified\n");
	exit(0);
}
if(mif_og_path==0){
	printf("No file specified\n");
	exit(0);
}
mif_enc=fopen(argv[mif_enc_path],"r");
if(mif_enc==NULL){
printf("Cannot open %s\n",argv[mif_enc_path]);
exit(0);
}
mif_og=fopen(argv[mif_og_path],"r");
if(mif_og==NULL){
printf("Cannot open %s\n",argv[mif_og_path]);
exit(0);
}
long mif_enc_size=0;
long mif_og_size=0;
long smallest=0;
fseek(mif_enc,0,SEEK_END);
mif_enc_size=ftell(mif_enc);
//printf("%s size=%i\n",argv[mif_enc_path],mif_enc_size);
rewind(mif_enc);
fseek(mif_og,0,SEEK_END);
mif_og_size=ftell(mif_og);
//printf("%s size=%i\n",argv[mif_og_path],mif_og_size);
rewind(mif_og);
if(mif_enc_size>mif_og_size){
	smallest=mif_og_size;
}else{
smallest=mif_enc_size;
}
//printf("Smallest: %i\n",smallest);
mif1=malloc(sizeof(char)*smallest);
if(mif1==NULL){
	exit(0);
}
mif2=malloc(sizeof(char)*smallest);
if(mif2==NULL){
	exit(0);
}
key=malloc(sizeof(char)*smallest);
if(key==NULL){
	exit(0);
}
fread(mif1,sizeof(char),smallest,mif_enc);
fread(mif2,sizeof(char),smallest,mif_og);
for(long i=0;i<smallest;i++){
	key[i]=(mif1[i]^mif2[i]);
}
fwrite(key,sizeof(char),smallest,stdout);
free(mif1);
free(mif2);
free(key);
free(mif_enc);
free(mif_og);
return 0;
}
