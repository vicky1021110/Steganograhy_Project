#include"decode.h"

Status validate(char* argv[],DecInfo* decInfo)                               //validating the bmp file 
{
    if(argv[2] != NULL)
    {
    char* str;
    str = strrchr(argv[2],'.');

    if(str != NULL)
    {
        if(strcmp(str,".bmp")==0)
        strcpy(decInfo -> source_fname,argv[2]);
        return e_success;
    }
    else
    {
        return e_failure;
    }
    }
    else
    {
        return e_failure;
    }

}


Status storing_file(char* argv[],DecInfo* decInfo)
{

    if(argv[3] == NULL)
    {
    strcpy(decInfo -> dest_fname,"destination_decode");
    
    return e_success;
    }

    else
    {
    char* str;
    
    str = strrchr(argv[3],'.');
    
    if(str != NULL)
    {
    *str = '\0';
    
    strcpy(decInfo -> dest_fname,argv[3]);
    
    return e_success;
    }

    else
    {
    
        strcpy(decInfo -> dest_fname,argv[3]);
        return e_success;
    
    }
}

}


Status open_files_dec(DecInfo* decInfo)
{
    decInfo -> fptr_dest_file = fopen(decInfo -> source_fname,"r");

    if(decInfo -> fptr_dest_file != NULL)
    {
        // printf("%s\n",decInfo -> source_fname);
        return e_success;
    }

    else
    {
        return e_failure;
    }
}

Status decode_mag_str(DecInfo* decInfo)
{
    fseek(decInfo -> fptr_dest_file,54,SEEK_SET);
    char buffer[8];
    for(int i=0;i<8;i++)
    {
        fread(buffer,8,1,decInfo -> fptr_dest_file);                                    //reading 8 bytes from the source file

        decInfo -> magic_string[i] = decode_byte_from_lsb(buffer);

    }

    decInfo->magic_string[8] = '\0';

    return e_success;
}

char decode_byte_from_lsb(char* buffer)
{
    char ch = 0;

    for(int i=0 ; i < 8 ;i++)
    {
        ch = ch | ((buffer[i] & 1) << i) ;
    }

    return ch;
}

Status dec_extn_size(DecInfo* decInfo)
{
    char buffer[32];

    uint ext_size = 0;

    fread(buffer,32,1,decInfo -> fptr_dest_file);

    for(int i=0 ; i<32 ; i++)
    {
        ext_size |= ((buffer[i] & 1) << i) ;
    }

    decInfo -> extn_size = ext_size;

    return e_success;
}

Status extn_decode(DecInfo* decInfo)
{
    char buffer[8];

    decInfo -> extn = malloc(decInfo -> extn_size+1);

    if(decInfo -> extn == NULL)
    {
        printf("memory not allocated for Decoding extension ");
        return e_failure;
    }

    for(int i=0;i<decInfo -> extn_size;i++)
    {

        fread(buffer,8,1,decInfo -> fptr_dest_file);

        decInfo -> extn[i] =  decode_byte_from_lsb(buffer);
    }

    decInfo -> extn[decInfo -> extn_size] = '\0';

    return e_success;
}

Status concat(DecInfo* decInfo)
{
    strcat(decInfo -> dest_fname,decInfo -> extn);

    printf("The Final destination file name ----- %s\n",decInfo -> dest_fname);

    return e_success;
}

Status decode_sec_size(DecInfo* decInfo)                       //fun definition for the decodingthe secreate file size
{
    char buffer[32];

    // printf("%ld\n", ftell(decInfo->fptr_dest_file));

    decInfo -> sec_size = 0;

    fread(buffer,32,1,decInfo -> fptr_dest_file);

    for(int i=0 ; i < 32 ;i++)
    {
        decInfo -> sec_size |= ((buffer[i] & 1) << i);
    }

    // printf("%d\n",decInfo -> sec_size);

    return e_success;

}

Status dec_secret_file_data(DecInfo* decInfo)
{

    decInfo -> fptr_final_file = fopen(decInfo -> dest_fname,"w");

    if(decInfo -> fptr_final_file  ==  NULL)
    printf("Open failed");

    for(int i=0 ; i < decInfo -> sec_size ; i++)
    {
        char buffer[8];

        char ch;

        fread(buffer,8,1,decInfo -> fptr_dest_file);

        ch = decode_byte_from_lsb(buffer);

        fwrite(&ch,1,1,decInfo -> fptr_final_file);

    }

    return e_success;

}