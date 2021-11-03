/************************************************************************
 | Project Name: 
 |    File Name: linux_fs.c
 |  Description: detailed Description
 |-----------------------------------------------------------------------
 |               A U T H O R   I D E N T I T Y
 |-----------------------------------------------------------------------
 | Initials     Name                      Company                        
 | --------     ---------------------     -------------------------------
 | MHKIM        Myoungha Kim              bitsensing Corporation
 |-----------------------------------------------------------------------
 |              R E V I S I O N   H I S T O R Y
 |-----------------------------------------------------------------------
 | Date         Ver  Author  Description                                 
 | ----------  ----  ------  --------------------------------------------
 | 2021.01.30  0.0   mhkim   Creation;
 |***********************************************************************/

#include "bts.h"
#include "os.h"
#include "cJSON.h"

#include "linux_fs.h"

extern int8_t sys_param_jsonbuff[65536 * 2];

char* ReadFile(char* filename, int* readSize)
{
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL)
        return NULL;

    int size;
    char *buffer;

    // 파일 크기 구하기
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    // 파일 크기 + NULL 공간만큼 메모리를 할당하고 0으로 초기화
    buffer = malloc(size + 1);
    memset(buffer, 0, size + 1);
    
    // 파일 내용 읽기 // which one is correct?
    //if (fread(buffer, size, 1, fp) < 1)
    if (fread(buffer, 1, size, fp) < 1)
    {
        *readSize = 0;
        free(buffer);
        fclose(fp);
        return NULL;
    }

    // 파일 크기를 넘겨줌
    *readSize = size;

    fclose(fp);    // 파일 포인터 닫기

    return buffer;
}

uint32_t WriteFile(char* filename, char* writedata, int writeSize)
{
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL)
        return NULL;

    fwrite(writedata, sizeof(char), writeSize, fp);
    fclose(fp);

    return retOK;
}