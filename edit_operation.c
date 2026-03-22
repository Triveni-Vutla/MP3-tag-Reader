#include<stdio.h>
#include"types.h"
#include<string.h>
#include<stdlib.h>
#include"audio.h"

char *ta[6] = {"-t","-a","-A","-y","-g","-c"};
status edit_operation(audio*oper,int argc,char ** argv)
{
    char *tag[6] = {"TIT2","TPE1","TALB","TYER","TCON","COMM"};
    int falg=0;
    for(int i=0;i<6;i++)
    {
        if(!(strcmp(argv[2],ta[i])))
        {
            falg=1;
        }
    }
    if(falg!=1)
    {
        printf("give proper tag in between -t/-g/-y/-a/-c/-A\n");
        printf("-t for title\n-a for artist\n-A for Album\n-y for year\n-g for genre information\n-c for comment\n");
        return failure;
    }
    oper->fptr_audio=fopen("new.mp3","r");
    if( oper->fptr_audio==NULL)
    {
        perror("fopen\n");
        return failure;
    }
    oper->fp_temp=fopen("temp.mp3","w");
    if( oper->fp_temp==NULL)
    {
        perror("fopen\n");
        return failure;
    }
    if (!oper->fptr_audio || !oper->fp_temp) 
    {
    printf("Invalid file pointers!\n");
    return -1;
    }
    char buffer[10];
    if(fread(buffer,10,1,oper->fptr_audio)!=1)
    {
        printf("Reading not successful\n");
        return failure;
    }
    if(fwrite(buffer,10,1,oper->fp_temp)!=1)
    {
        printf("writing not successful\n");
        return failure;
    }
    for(int i=0;i<6;i++)
    {
        if(!(strcmp(ta[i],argv[2])))
        {
            char ch[4];
            if(fread(ch,4,1,oper->fptr_audio)!=1)
            {
                printf("Reading not successful\n");
                return failure;
            }
            if((memcmp(tag[i],ch,4)))
            {
                printf("Not correct tag\n");
                return failure;
            }
            else
            {
               if(fwrite(ch,4,1,oper->fp_temp)!=1)
               {
                   printf("writing not successful\n");
                   return failure;
               }
               unsigned int new_len =strlen(argv[3])+1;
               char temp[4];
               if(fread(temp,4 ,1,oper->fptr_audio)!=1)
               {
                  printf("failed to read temp\n");
                  return failure;
               }
               int len=0;
               if(con_big_lit(temp,&len)!=success)
               {
                  printf("Convert big to little endian not success\n");
                  return failure;
               }
               char byte[4];
               if(con_lit_big(new_len,byte)!=success)
               {
                  printf("Not converted to big endian\n");
                  return failure;
               }
               if(fwrite(byte,4,1,oper->fp_temp)!=1)
               {
                  printf("writing not successful\n");
                  return failure;
               }
               char flag[2];
               if(fread(flag,2,1,oper->fptr_audio)!=1)
               {
                  printf("reading not successful\n");
                   return failure;
               }
               if(fwrite(flag,2,1,oper->fp_temp)!=1)
               {
                  printf("writing not successful\n");
                  return failure;
               }
               fputc(0x00,oper->fp_temp);
               if(fwrite(argv[3],strlen(argv[3]),1,oper->fp_temp)!=1)
               {
                  printf("Writing is not successful\n");
                  return failure;
               }
               fseek(oper->fptr_audio,len,SEEK_CUR);
            }
        }
        else
        {
            char ch[4];
            if(fread(ch,4,1,oper->fptr_audio)!=1)
            {
               printf("Reading not successful\n");
               return failure;
            }
            if(fwrite(ch,4,1,oper->fp_temp)!=1)
            {
                   printf("writing not successful\n");
                   return failure;
            }
            char temp[4];
            if(fread(temp,4,1,oper->fptr_audio)!=1)
            {
                printf("REading not successful\n");
                return failure;
            }
            if(fwrite(temp,4,1,oper->fp_temp)!=1)
            {
                printf("Writing not successful\n");
                return failure;
            }
            int len=0;
            if(con_big_lit(temp,&len)!=success)
            {
                  printf("Convert big to little endian not success\n");
                  return failure;
            }
            char fla[2];
            fread(fla,2,1,oper->fptr_audio);
            fwrite(fla,2,1,oper->fp_temp);
           char * remind =malloc(len);
           if(remind==NULL)
           {
            printf("memory not allocated\n");
            return failure;
           }
             if(fread(remind,len,1,oper->fptr_audio)!=1)
            {
                printf(" tri reading not successful\n");
                return failure;
            }
            if(fwrite(remind,len,1,oper->fp_temp)!=1)
            {
                printf("writing not successful\n");
                return failure;
            }
            free(remind);
            remind=NULL;
        }
    }
   if (!oper->fptr_audio || !oper->fp_temp) 
   {
    printf("Invalid file pointers!\n");
    return -1;
   }
    char buff[4096];
    size_t bytesRead, bytesWritten;

    while ((bytesRead = fread(buff, 1, 4096, oper->fptr_audio)) > 0) 
    {
        bytesWritten = fwrite(buff, 1, bytesRead, oper->fp_temp);
        if (bytesWritten != bytesRead)
         {
            perror("Write error");
            return -1;
        }
    }
     fclose(oper->fptr_audio);
     fclose(oper->fp_temp);

    if (rename("temp.mp3", "new.mp3") == 0) 
    {
        oper->fptr_audio = fopen("new.mp3", "r"); 
    } 
    else 
    {
    perror("Rename failed");
    }

    return success;
}
status con_lit_big(unsigned int a,char *byte)
{
    byte[0]= (a >>24) & 0xFF;
    byte[1]= (a >>16) & 0xFF;
    byte[2]= (a >>8) & 0xFF;
    byte[3]= (a) & 0xFF;
    return success;
}
status con_big_lit(unsigned char * arr,int *sum)
{
*sum = ((unsigned)arr[0] << 24) | ((unsigned)arr[1] << 16) | ((unsigned)arr[2] << 8) | ((unsigned)arr[3]);
return success;
}

