#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

int main(void)
{
    int fd, n;
    struct stat buf_meta;
    char buf[256];
    mode_t mode;

    stat("unix.txt", &buf_meta);

    // data 파일이 존재하면
    if (access("data.txt", R_OK) != -1)
    {
        // 가) data.txt 파일이 일반 파일이 아니면, 에러메시지 출력 후 종료
        if ((buf_meta.st_mode & S_IFMT) != S_IFREG)
        {
            perror("This is not general file.");
            eixit(1);
        }
        // 나) GROUP/OTHER 에 읽기/쓰기 권한이 있으면,
        if ((buf_meta.st_mode & S_IRGRP) && (buf_meta.st_mode & S_IROTH) && (buf_meta.st_mode & S_IWGRP) && (buf_meta.st_mode & S_IWOTH))
        {
            // “data.txt must be protected” 와 같은 메시지 출력 후 종료
            printf("data.txt must be protected.");
            eixit(1);
        }
    }

    // 존재하지 않는다면,

    // 다) data.txt 파일 생성할 때,
    // 권한은 사용자에 대해서만 [읽기/쓰기]할 수 있도록 정하기
    mode = S_IRUSR | S_IWUSR;
    fd = open("data.txt", O_CREAT | O_WRONLY | O_TRUNC, mode);

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