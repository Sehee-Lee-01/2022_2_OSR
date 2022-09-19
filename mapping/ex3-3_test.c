#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int main(void)
{
    int fd, n;
    char buf[256];
    mode_t mode; // 정의
    mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    fd = open("data.txt", O_CREAT | O_RDONLY, mode);
    if (fd == -1)
    {
        perror("Open data.txt");
        exit(1);
    }
    while (1)
    {
        n = read(fd, buf, 255); // 데이터 수신
        buf[n] = '\0';
        if (n == -1)
        {
            perror("Read error");
        }
        else if (n == 0)
            continue;           //읽은 내용이 없다면 대기
        write(1, "Recv>> ", 7); // 화면에 출력
        write(1, buf, n);
        if (n == 1 && buf[0] == 'q') // q입력으로 종료
        {
            write(1, "Terminate\n", 10);
            break;
        }
    }
    close(fd);
    return 0;
}
