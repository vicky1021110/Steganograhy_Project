#include"header.h"

OperationType check_operation_type(char *argv[])
{

    if(strcmp(argv[1],"-e")==0)                                //checking user going to encode
    return e_encode;

    else if(strcmp(argv[1],"-d")==0)                           //checking user going to decode
    return e_decode;
    
    else
    {
        printf("\n❌❌ Enter valid operation Type ❌❌\n");
        return e_unsupported;
    }

}

Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo)                    // fun definition for checking the argv[2] and argv[3]
{

    if(argv[2] == NULL )
    return e_failure;
    
    char* ext;
    ext = strrchr(argv[2],'.');                                                            // extracting the address of dot in argv[2] 

    if(ext != NULL)
    {
    
        if(strcmp(ext,".bmp")==0)                                                          // comparing the address of dot in argv[2] and with dot
        {
        encInfo -> src_image_fname = argv[2];                                              // saving the .bmp file into the 
        }
    
    }

    if(argv[3] == NULL)
    return e_failure;

    else
    {
    encInfo -> secret_fname = argv[3];                                                     // checking secreate file extension type and storing it         
    char* sec_ext=strrchr(argv[3],'.');
    
    if(sec_ext != NULL)
    {
        strcpy(encInfo -> extn_secret_file,sec_ext);
    }
    
    }

    return e_success;
    
}

Status open_files(EncodeInfo *encInfo)
{
    encInfo -> fptr_src_image = fopen(encInfo -> src_image_fname,"r");       //opening the file to read

    encInfo -> fptr_secret = fopen(encInfo -> secret_fname,"r");             //opening the secret file to read

    encInfo -> fptr_stego_image = fopen("destination_encode.bmp","w");       //opening and creating the encoded destination bmp file
    
    if(encInfo->fptr_src_image == NULL)
    
    {
        printf("\n ⚠️⚠️ Unable to access source image file ⚠️⚠️\n\n");
        return e_failure;
    }

    if(encInfo -> fptr_secret == NULL)
    
    {
        printf("\n ⚠️⚠️ Unable to open secret image file ⚠️⚠️\n\n");
        return e_failure;
    }

    return e_success;

}


Status check_capacity(EncodeInfo *encInfo)
{

    fseek(encInfo -> fptr_src_image,0,SEEK_END);                                     //checking capacity of the bmp file            
    uint size = ftell(encInfo -> fptr_src_image);
    rewind(encInfo -> fptr_src_image);

    if(size == 0)
    return e_failure;

    else
    {
    encInfo -> image_capacity = size-54;                                             //substracting first 54 bytes from header of the bmp file
    }

    fseek(encInfo -> fptr_secret,0,SEEK_END);                                        //checking chapacity of the secret file       
    uint size_of_secretdata = ftell(encInfo -> fptr_secret);
    rewind(encInfo -> fptr_secret);

    if(size_of_secretdata == 0)
    return e_failure;

    else
    {
    encInfo -> size_secret_file = size_of_secretdata;        
    }

    return e_success;
}

Status copy_bmp_header(EncodeInfo *encInfo)                      // copying the  header of the RGB data 54byte
{
    for(int i=0 ;i < 54 ; i++)
    {
        char ch;

        fread(&ch,1,1,encInfo -> fptr_src_image);                 // taking the one by one byte from the source file / BMP file 

        fwrite(&ch,1,1,encInfo -> fptr_stego_image);
    }
    return e_success;
}

Status encode_magic_string(EncodeInfo *encInfo)                   // encoding of the magic string
{
    char* mag_str = MAGIC_STRING;

    char image_data[8];

    for(int i=0;i<strlen(mag_str);i++)
    {
        fread(image_data,8,1,encInfo -> fptr_src_image);          // taking 8 bytes from the RGB data and storing it to buffer
    
        encode_byte_to_lsb(mag_str[i],image_data);                 // calling fun for encode the mag string by byte by byte

        fwrite(image_data,8,1,encInfo -> fptr_stego_image);

    }

     return e_success;

}

Status encode_byte_to_lsb(char mag_str,char * data)
{
    for(int i=0 ;i<8 ;i++)
    {
            data[i] = (data[i] & 0xFE) | ((mag_str>>i)&1);
    }
    return e_success;
}

Status encode_secret_file_extn_size(EncodeInfo *encInfo)              // encoding the size of the extension of secret file                        
{
    int size = strlen(encInfo -> extn_secret_file);
    
    // printf("size of the file extension %d\n\n",size);

    char data1[32];                                                   //this is the buffer for every iteration for taking 32 bytes from the source file because the integer is 4 bytes for that we want 32 bytes of the data from the source file

    fread(data1,32,1,encInfo -> fptr_src_image);

    for(int i= 0 ;i< 32 ;i++)
    {
        data1[i] = (data1[i] & 0xFE) | ((size>>i)&1 );                 //encoding the 32 bytes of number to the source file's LSB of the each byte
    }

    fwrite(data1,32,1,encInfo -> fptr_stego_image);

    return e_success;
}

Status encode_secret_file_extn(EncodeInfo *encInfo)
{
    char data[8];                                                   //this is the buffer for every iteration for taking 8 bytes from the source file

    char* extn_name = encInfo -> extn_secret_file;                  //save the name into the extn_name

    for(int i=0;i< strlen(extn_name);i++)
    {
        fread(data,8,1,encInfo -> fptr_src_image);                  //reading or taking 1 byte or 1 character from the secreate file

        encode_byte_to_lsb(extn_name[i],data);                      // sending the two parameters extn_name[i] => each character by character

        fwrite(data,8,1,encInfo -> fptr_stego_image);
    }

    return e_success;
}

Status encode_secret_file_size(EncodeInfo *encInfo)
{
    int size = encInfo -> size_secret_file;

    char data1[32];                                                   //this is the buffer for every iteration for taking 32 bytes from the source file because the integer is 4 bytes for that we want 32 bytes of the data from the source file

    fread(data1,32,1,encInfo -> fptr_src_image);

    for(int i=0;i<32;i++)
    {
        data1[i] = (data1[i] & 0xFE) | ((size>>i) &1 );
    }

    fwrite(data1,32,1,encInfo -> fptr_stego_image);

    return e_success;
}

Status encode_secret_file_data(EncodeInfo *encInfo)
{
    char data[8];                                                         //this is the buffer for every iteration for taking 8 bytes from the source file

    char ch;

    for(int i = 0;i < encInfo -> size_secret_file ; i++)
    {
        fread(&ch,1,1,encInfo -> fptr_secret);                                     //taking 1 byte or 1 character from the secreate file

        fread(data,8,1,encInfo -> fptr_src_image);                                 //taking 8 byte from the source file to encode the 1 byte from the secret file

        encode_byte_to_lsb(ch,data);                                               //call for encoding

        fwrite(data,8,1,encInfo -> fptr_stego_image);                              //writing it into the dest file
    }

    return e_success;
}

Status copy_remaining_img_data(EncodeInfo *encInfo)
{
    char ch;

    while(fread(&ch,1,1,encInfo -> fptr_src_image) > 0 )                              //encoding the remaining data into the dest file by byte by byte
    {  
        fwrite(&ch,1,1,encInfo -> fptr_stego_image);
    }
    return e_success;
}