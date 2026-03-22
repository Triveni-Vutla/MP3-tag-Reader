#include<stdio.h>
#include"types.h"
#include<string.h>
#include"audio.h"
char *tag[6] = {"TIT2","TPE1","TALB","TYER","TCON","COMM"};
int sum;
status view_operation(audio* oper)
{
    oper->fptr_audio=fopen("new.mp3","r");
    if(oper->fptr_audio==NULL)
    {
        printf("file not opened successfully\n");
        perror("fopen");
        return failure;
    }
    if(check_id3(oper->fptr_audio)!=success)
    {
        printf("This is not mp3 audio  file\n");
        return failure;
    }
    printf("The file is mp3 file\n");
    fseek(oper->fptr_audio,10,SEEK_SET);
    //............TITLE TAG ....................
    printf("\n............TITLE TAG.......................\n");
    if(tag_success(oper)!=success)
    {
        printf("tag is not success\n");
        return failure;
    }
    //.............ALBUM TAG........................\\

    printf("\n............ARTIST TAG.......................\n");
     if(tag_success(oper)!=success)
    {
        printf("tag is not success\n");
        return failure;
    }
    // ............ TAG3.......................

     printf("\n............ALBUM TAG.......................\n");
      if(tag_success(oper)!=success)
    {
        printf("tag is not success\n");
        return failure;
    }
     //............YEAR TAG .......................
     printf("\n............YEAR TAG .......................\n");
    if(tag_success(oper)!=success)
    {
        printf("tag is not success\n");
        return failure;
    }
      //............ TAG .......................
     printf("\n............GENRE TAG .......................\n");
    if(tag_success(oper)!=success)
    {
        printf("tag is not success\n");
        return failure;
    }
      //............COMMENT TAG .......................
     printf("\n............COMMENT TAG .......................\n");
    if(tag_success(oper)!=success)
    {
        printf("tag is not success\n");
        return failure;
    }
    printf("\n");
    return success;
}
status tag_success(audio * oper)
{
    if(read_tags(oper->fptr_audio,oper)!=success)
    {
        printf("Tag reading not successful\n");
        return failure;
    }
    if(read_size(oper->fptr_audio)!=success)
    {
        printf("Converting bes to les is not done\n");
        return failure;
    }
    fseek(oper->fptr_audio,3,SEEK_CUR);
    if(write_content(oper->fptr_audio)!=success)
    {
        printf("writing content is not successful\n");
        return failure;
    }   
    return success;
}
status check_id3(FILE * fp)
{
    char arr[3];
    if(fread(arr,3,1,fp)!=1)
    {
        printf("reading is not successfl\n");
        return failure;
    }
    if(!(strcmp(arr,"ID3")))
    {
        return success;
    }
}
status read_tags(FILE*fp,audio *oper)
{
    char arr[4];
    if(fread(arr,4,1,fp)!=1)
    {
        printf("Reading 4 bytes not successful\n");
        return failure;
    }
    if(compare_tags(arr,tag)!=success)
    {
        printf("Comparing tags is not successful\n");
        return failure;
    }
    return success;
}
status compare_tags(char *data ,char **tag)
{
    for(int i=0;i<6;i++)
    {
        if(!(strcmp(data,tag[i])))
        {
            printf("Tag is %s\n",data);
            return success;
        }   
    }
    printf("Tag is not available\n");
    return failure;
}
status read_size(FILE *fp)
{
    char arr[4];
    if(fread(arr,4,1,fp)!=1)
    {
        printf("reading 4 bytes not successful\n");
        return failure;
    }
    int len=strlen(arr);
    for(int i=0;i<len/2;i++)
    {
        int temp=arr[i];
        arr[i]=arr[len-1];
        arr[len-1]=temp;
    }
    sum=0;
    for(int i=0;i<4;i++)
    {
        sum+=arr[i];
    }
    printf("Tag content size is %d \n",sum);
    return success;
}
status write_content(FILE *fp)
{
    char content[sum-1];
        size_t a=fread(content,1,sum-1,fp);
        if(a==0)
    {
        printf("reading content is not successful\n");
        return failure;
    }
    content[sum-1]='\0';
    for (size_t i = 0; i < a; i++) {
        if (content[i] == '\0') content[i] = ' ';
    }
    printf("----Tag Content is-----\n");
    printf("%s\n",content);
    return success;
}