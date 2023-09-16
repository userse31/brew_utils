#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

FILE *fp;
FILE *fp_palette;
FILE *fp_bmp;
unsigned char *header_buffer;
unsigned char *palette_buffer;
unsigned char *bmp_metadata_buffer;
unsigned char *zlib_bmp_buffer;
unsigned short file_size=0;
unsigned short zlib_bmp_offset=0;
unsigned short image_width=0;
unsigned short image_height=0;

int main(int argc, char *argv[]){
	if(argc<4){
		printf("dumpbci <file> <color palette> <bmp data>\n");
		exit(0);
	}
	fp=fopen(argv[1],"r");
	if(fp==NULL){
		printf("Cannot open %s\n",argv[1]);
		exit(0);
	}
	header_buffer=malloc(sizeof(char)*32);
	fread(header_buffer,sizeof(char),32,fp);

	//Check magic number (BCI)
	if(header_buffer[0]==0x42&&header_buffer[1]==0x43&&header_buffer[2]==0x49&&header_buffer[3]==0){
		printf("It's a BCI file!\n");
	}else{
		printf("This is not a BCI file.\n");
	}

	//File size
	file_size=header_buffer[4]|(header_buffer[5]<<8);
	printf("File size: %i\n",file_size);

	//zlib bitmap data offset
	zlib_bmp_offset=header_buffer[8]|(header_buffer[9]<<8);
	printf("Zlib bmp data offset: %i\n",zlib_bmp_offset);

	//Something 0.
	printf("Something 0: %i\n",header_buffer[12]|(header_buffer[13]<<8));

	//Width and height.
	image_width=header_buffer[14]|(header_buffer[15]<<8);
	image_height=header_buffer[16]|(header_buffer[17]<<8);
	printf("Dimensions: %ix%i\n",image_width,image_height);

	//Something 1.
	printf("Something 1: %i\n",header_buffer[18]|(header_buffer[19]<<8));
	//Something 2.
	printf("Something 2: %i\n",header_buffer[20]|(header_buffer[21]<<8));
	//Something 3.
	printf("Something 3: %i\n",header_buffer[22]|(header_buffer[23]<<8));
	//Something 4.
	printf("Something 4: %i\n",header_buffer[26]|(header_buffer[27]<<8));
	//Something 5.
	printf("Something 5: %i\n",header_buffer[28]|(header_buffer[29]<<8));
	//Something 6.
	printf("Something 6: %i\n",header_buffer[30]|(header_buffer[31]<<8));

	//Get length of color palette.
	int palette_len=zlib_bmp_offset-32;
	//Read the palette.
	palette_buffer=malloc(sizeof(char)*palette_len);
	fread(palette_buffer,sizeof(char),palette_len,fp);

	//Get length of compressed bitmap area.
	int zlib_len=(file_size-zlib_bmp_offset)-12;
	//Read the 12 byte metadata.
	bmp_metadata_buffer=malloc(sizeof(char)*12);
	fread(bmp_metadata_buffer,sizeof(char),12,fp);
	printf("ZLIB bitmap metadata:\n");
	printf("Something 0: %i\n",bmp_metadata_buffer[0]|(bmp_metadata_buffer[1]>>8));
	printf("Width: %i\n",bmp_metadata_buffer[4]|(bmp_metadata_buffer[5]>>8));
	printf("Height: %i\n",bmp_metadata_buffer[6]|(bmp_metadata_buffer[7]>>8));
	printf("Something 1: %i\n",bmp_metadata_buffer[8]|(bmp_metadata_buffer[9]>>8));
	printf("Something 2: %i\n",bmp_metadata_buffer[10]|(bmp_metadata_buffer[11]>>8));


	//Read the compressed bitmap data.
	zlib_bmp_buffer=malloc(sizeof(char)*zlib_len);
	fread(zlib_bmp_buffer,sizeof(char),zlib_len,fp);

	//Write both
	fp_palette=fopen(argv[2],"w");
	fp_bmp=fopen(argv[3],"w");
	if(fp_palette==NULL){
		printf("Error creating %s\n",argv[2]);
		exit(0);
	}
	if(fp_bmp==NULL){
		printf("Error creating %s\n",argv[3]);
		exit(0);
	}
	fwrite(palette_buffer,sizeof(char),palette_len,fp_palette);

	fwrite(zlib_bmp_buffer,sizeof(char),zlib_len,fp_bmp);
	fclose(fp);
	fclose(fp_palette);
	fclose(fp_bmp);
	exit(0);
}
