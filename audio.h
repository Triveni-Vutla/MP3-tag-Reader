#ifndef AUDIO_H
#define AUDIO_H
#include "types.h"
#include<stdio.h>

typedef struct ope
{
    FILE *fptr_audio;
    FILE *fp_temp;
}audio;
operation_type check_operation(char * argv);
status view_operation(audio * oper);
status edit_operation(audio *oper,int argc,char **argv);
status check_id3(FILE * fp);
status compare_tags(char *data ,char **tag);
status read_tags(FILE*fp,audio *oper);
status read_size(FILE *fp);
status write_content(FILE *fp);
status tag_success(audio * oper);
status con_lit_big(unsigned int a,char *byte);
status con_big_lit(unsigned char * arr,int *sum);




#endif
