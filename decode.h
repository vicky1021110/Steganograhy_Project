#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"enum.h"

typedef struct _decoding
{ 
char dest_fname[50];       //destination file for the decoding
char magic_string[9];      //decoded magicstring
uint extn_size;
char* extn;
uint sec_size;
FILE* fptr_final_file;     //final destination file of the decoding

char source_fname[50];     //bmp file name
FILE* fptr_dest_file;      //file pointer to the bmp file
}DecInfo;

Status validate(char* argv[],DecInfo* decInfo);                                        //validating the argv[2]

Status storing_file(char* argv[],DecInfo* decInfo);                   //validating the argv[3]

Status open_files_dec(DecInfo* decInfo);

Status decode_mag_str(DecInfo* decInfo);

char decode_byte_from_lsb(char* buffer);

Status dec_extn_size(DecInfo* decInfo);                           //fun declaration for decoding the size of the extension 

Status extn_decode(DecInfo* decInfo);                              //fun declaration for decoding extension 

Status concat(DecInfo* decInfo);                                  //fun declaration for the concatenation

Status decode_sec_size(DecInfo* decInfo);                       //fun decalartion for the decoding the secreate file size

Status dec_secret_file_data(DecInfo* decInfo);                    //fun declaration for the decoding the secret fila data's

