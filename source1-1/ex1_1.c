// sys call
#include </usr/include/errno.h>
#include <unistd.h>
#include <stdio.h>

extern int errno;

int main(void)
{
    // 성공하면 0, 실패하면 -1 리턴
    // 공통: errno에 오류 코드 저장
    if (access("unit.txt", F_OK) == -1)
    {
        printf("errno=%d\n", errno);
    }
    return 0;
}