#include"header.h"
#include"decode.h"

int main(int argc,char* argv[])                                // Used for accessing CLA 
{

    if(argc >= 2)
{
    EncodeInfo encInfo;                                         // sturct variable declaration
    
    OperationType ret;                                          // declaring variable for enum datatype
    
    ret = check_operation_type(argv);                           // fun call for checking operation type
    
    if(ret == e_encode)
    
    {
        Status opt;                                             // declaring variable for enum datatype
        
        opt = read_and_validate_encode_args(argv,&encInfo);     // fun call for checking the CLA's
    
        if(opt == e_success)
        {
            // printf("Secreate file exist\n");
            Status o_file;
            o_file = open_files(&encInfo);
            {
                
                if(o_file == e_success)
                    {
                        Status cap_file;                      
                        cap_file = check_capacity(&encInfo);                 // fun call for checking capacity in the source file
            
                        if(cap_file == e_success)
                        {
                            if( ((strlen(MAGIC_STRING) + encInfo.size_secret_file + strlen(encInfo.extn_secret_file) + 4 )*8) <= encInfo.image_capacity)
                            {
                                    printf("✅✅ successfully the size is higher in the bmp file ✅✅\n\n");
                                    Status bmp_header_encoding;
                                    bmp_header_encoding  =  copy_bmp_header(&encInfo);
                                    if(bmp_header_encoding == e_success)
                                    {

                                            printf(" Header of the RGB data is Encoded successfully \n\n");
                                            Status mag_str_en;
                                            mag_str_en = encode_magic_string(&encInfo);                                                      

                                            if(mag_str_en == e_success)
                                            {
                                                    printf(" Magic string is successfully encoded \n\n");

                                                    Status extn_size;
                                                    extn_size = encode_secret_file_extn_size(&encInfo);

                                                    if(extn_size == e_success)
                                                    {
                                                        Status extn_name;
                                                        extn_name = encode_secret_file_extn(&encInfo);

                                                        if(extn_name == e_success)
                                                        {
                                                            printf(" Extension size and name is successfully encoded \n\n");
                                                            Status sec_size;
                                                            sec_size = encode_secret_file_size(&encInfo);
                                                            if(sec_size == e_success)
                                                            {
                                                                printf(" Secret file size is successfully encoded \n\n");
                                                                Status sec_data;
                                                                sec_data = encode_secret_file_data(&encInfo);

                                                                if(sec_data == e_success)
                                                                {
                                                                    printf("**  Secret data is Encoded successfully  **\n\n");
                                                                    Status rem_data;
                                                                    rem_data = copy_remaining_img_data(&encInfo);

                                                                    if(rem_data == e_success)
                                                                    {
                                                                        printf(" Encoding process is completed \n\n");
                                                                    }
                                                                }
                                                            }
                                                            
                                                            
                                                        }
                                                    }
                        
                                            }
                                    }
                            }

                        }
                        
                    }
            }

        }
    
        else if(opt == e_failure)
        {
            printf("File not exist");
        }
        
    }
    else
    {

        DecInfo decInfo;


        Status re_and_val_bmp;
        re_and_val_bmp = validate(argv,&decInfo);
        
        if(re_and_val_bmp == e_success)
        {

        printf("Given CLA have an bmp file\n");
        Status re_nd_val;
        re_nd_val = storing_file(argv,&decInfo);
        
        if(re_nd_val == e_success)
        {
            printf("%s is the Destination file name\n",decInfo.dest_fname);
            Status open_files_de;
            open_files_de = open_files_dec(&decInfo);

            if(open_files_de == e_success)
            {
                printf("Found Data in the BMP file\n%s is the Source file for the Decoding\n",decInfo.source_fname);
                Status dec_header;
                dec_header= decode_mag_str(&decInfo);

                if(dec_header == e_success)
                {
                    printf("The magic string is %s\n",decInfo.magic_string);
                    if(strcmp(decInfo.magic_string,"avengers")==0)
                    {

                        printf("\n\t  Magic String is MATCHED \n\n*********PROCEEDING TO DECODING**********\n\n");
                        Status dec_ex_size;
                        dec_ex_size = dec_extn_size(&decInfo);                                                                 //fun call for decoding the size of the extension 

                        if(dec_ex_size == e_success)
                        {

                            Status ex_dec;
                            ex_dec = extn_decode(&decInfo);

                            if(ex_dec == e_success)
                            {

                                Status con_name;                                                         //concatenating the file extension and file name
                                con_name = concat(&decInfo);

                                if(con_name == e_success)
                                {
                                    Status sec_size;
                                    sec_size = decode_sec_size(&decInfo);                                 //fun call for the decodingthe secreate file size                       

                                    if(sec_size == e_success)
                                    {
                                        Status sec_data;
                                        sec_data = dec_secret_file_data(&decInfo);

                                        if(sec_data == e_success)
                                        {
                                            printf("\n---Decoding Successfully completed---\n\n");
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

        }

    }
    else
    {
        printf("\nEnter the Valid BMP file\n\n");
    }
}
}
}
