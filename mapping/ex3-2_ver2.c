// data.txt 파일 존재시 처리 루틴 변경
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
    mode_t mode;
    mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    fd = open("data.txt", O_CREAT | O_WRONLY | O_TRUNC, mode);

    if (fd == -1)
    {
        perror("Open data.txt");
        exit(1);
    }

    while (1)
    {
        write(1, ">> ", 3);    // 입력 프롬프트
        n = read(0, buf, 255); //사용자 입력
        buf[n] = '\0';
        if (n > 0) // 데이터 보내기
        {
            if (write(fd, buf, n) != n)
            {
                perror("Write error");
            }
        }
        else if (n == -1)
        {
            perror("Read error");
        }
        if (n == 1 && buf[0] == 'q') // q만 입력시 종료
        {
            write(1, "Terminate\n", 10);
            break;
        }
        write(1, buf, n); //화면에 에코 출력
    }
    close(fd);
    return 0;
}