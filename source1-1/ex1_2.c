// library
#include </usr/include/errno.h>
#include <stdlib.h>
#include <stdio.h>

extern int errno;

int main(void)
{
    FILE *fp;
    // 실패하면 NULL을 리턴, 함수의 리턴값이 int면 -1 리턴
    // 공통: errno에 오류 코드 저장
    if ((fp = fopen("unix.txt", "r")) == NULL)
    {
        printf("errno=%d\n", errno);
        exit(1);
    }
    fclose(fp);

    return 0;
}