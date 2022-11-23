#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    FILE *fp;
    int fd, n;
    char str[BUFSIZ];

    fp = fopen("unix.txt", "r"); // 고수준 파일입출력 함수로 파일 오픈
    if (fp = NULL)
    {
        perror("fopen");
        exit(1);
    }

    fd = fileno(fp); // 파일 기술자 리턴
    printf("fd: %d\n", fd);

    n = read(fd, str, BUFSIZ); // 저수준 파일읽기 함수로 읽기
    str[n] = '\0';
    printf("Read: %s\n", str);

    close(fd);

    return 0;
}