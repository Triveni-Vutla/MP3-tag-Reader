// ...............PROJECT NAME: MP3 TAG READER.........................

/*NAME:V TRIVENI
DATE OF START:10/9/25
DATE OF END:16/9/25
DESCRIPTION:   In this project we are reading and editing of metadata of a audio file.
               the file should be mp3 file and version ID3v2.0. . In meta data the song 
               details are there in the form tags.using tags we are reading different type 
               of data in bynary form */

#include<stdio.h>
#include<string.h>
#include"types.h"
#include"audio.h"


int main(int argc,char *argv[])
{
    audio oper;
    
    operation_type a=check_operation(argv[1]);
    {
        if(a==view)
        {
            if(argc!=3)
            {
                printf("You must pass commands line arguments count is 3\n");
                printf("USAGE: ./a.out -v filename\n" );
                return failure;
            }
            printf(":::::::::::::::::::You are selecting View operation:::::::::::::::::::::\n");
            if(view_operation(&oper)!=success)
            {
                printf("\nAudio File display not completed\n");
                return failure;
            }
            else
            {
                printf("Audio File display successfully completed\n");
                return success;
            }  
        }
        else if(a==edit)
        {
            if(argc!=5)
            {
                printf("cla arguments must be 5\n");
                printf("Please provide arguments for editing as ./a.out -e option for edit (-t) new name  audiofilename.mp3\n");
                return failure;
            }
            printf(":::::::::::::::::::::You are Selecting Edit operation:::::::::::::::::::\n");

            if(edit_operation(&oper,argc,argv)!=success)
            {
                printf("Audio File edit not completed\n");
                return failure;
            }
            else
            {
                printf("\nAudio File  edit successfully completed\n");
                return success;
            }
     
        }
        else
        {
            printf("Invalid type of operation\n");
            printf("USAGE: use -v(for viewing) or -e(for edit)\n");
            return failure;
        }

    }
}
operation_type check_operation(char* arg)
{
    if(! (strcmp(arg,"-v")))
    return view;
    else if(!(strcmp(arg,"-e")))
    return edit;
    else
    {
        return unsupported;
    }
}