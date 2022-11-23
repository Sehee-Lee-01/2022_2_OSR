#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    FILE *fp;
    int fd;
    char str[BUFSIZ];

    // 저수준 파일 입출력 함수로 파일 오픈
    fd = open("unix.txt", O_RDONLY);
    if (fd = -1)
    {
        perror("open");
        exit(1);
    }

    // 파일 포인터 생성
    fp = fdopen(fd, "r");

    fgets(str, BUFSIZ, fp);
    printf("Read: %s\n", str); // 고수준 파일 읽기 함수로 읽기

    fclose(fp);

    return 0;
}