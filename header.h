#include<stdio.h>
#include<string.h>
#include"enum.h"


typedef unsigned int uint;
#define MAX_FILE_SUFFIX 4                      //num size
#define MAGIC_STRING "avengers"                //MAGIC STRING

typedef struct _EncodeInfo
{
    char *src_image_fname;                     //bmp file                                                
    FILE *fptr_src_image;
    uint image_capacity;

    char *secret_fname;                         //secrete file  
    FILE *fptr_secret; 
    long size_secret_file;                      // secreate file size
    char extn_secret_file[MAX_FILE_SUFFIX];     //secrete file extn name

    char *stego_image_fname;                    //destination file of the encoding process
    FILE *fptr_stego_image;
             

}EncodeInfo;

OperationType check_operation_type(char *argv[]);                            // fun declaration for checking operation type

Status read_and_validate_encode_args(char *argv[],EncodeInfo *encInfo);     // fun declaration for checking the CLA's

Status check_capacity(EncodeInfo *encInfo);                                 // fun declaration for the checking capacity of the bmp to encode
 
Status open_files(EncodeInfo *encInfo);                                     //fun declaration for open files and storing it into the struct

Status copy_bmp_header(EncodeInfo *encInfo);                                //fun declaration for copy bmp header

Status encode_magic_string(EncodeInfo *encInfo);                            //fun declaration for encoding magic string

Status encode_byte_to_lsb(char mag_str,char * data);                        //fun declaration for encoding LSB of the each byte of the source image

Status encode_secret_file_extn_size(EncodeInfo *encInfo);                   //fun declaration for encoding secreate file extension size

Status encode_secret_file_extn(EncodeInfo *encInfo);                        //fun declaration for encoding secreate file extn

Status encode_secret_file_size(EncodeInfo *encInfo);                        //fun declaration for encoding secreate file size

Status encode_secret_file_data(EncodeInfo *encInfo);                        //fun declaration for encoding secreate file data

Status copy_remaining_img_data(EncodeInfo *encInfo);                        //fun declaration for encoding remaining data