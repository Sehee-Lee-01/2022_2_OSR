#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int main(void)
{
    // 지난 시간 언급한 ex3-2 가 나중에 실행되는 경우의 문제해결하기
    while (1)
    {
        sleep(1);
        if (access("data.txt", R_OK) == -1)
            perror("access");
        else
            break;
    }

    // data 파일이 존재하면
    struct stat buf_meta;

    stat("data.txt", &buf_meta);

    int kind = buf_meta.st_mode & S_IFMT;

    // 가) data.txt 파일이 일반 파일이 아니면, 에러메시지 출력 후 종료
    if (kind != S_IFREG)
    {
        perror("This is not general file.");
        exit(1);
    }
    // 나) GROUP/OTHER 에 읽기/쓰기 권한이 있으면,
    if ((buf_meta.st_mode & S_IRGRP & S_IROTH & S_IWGRP & S_IWOTH))
    {
        // “data.txt must be protected” 와 같은 메시지 출력 후 종료
        printf("data.txt must be protected.");
        exit(1);
    }

    int fd, n;
    char buf[256];
    fd = open("data.txt", O_RDONLY);

    if (fd == -1)
    {
        perror("Open data.txt");
        exit(1);
    }

    // data.txt 가 이미 있는 경우, 기존 내용은 읽지 않기
    // ex3-3 실행 중 ex3-2가 재실행(혹은 나중에 실행)되는 경우에도
    // ex3-2로 부터 정상적으로 데이터 수신하도록 만들기
    int data_size = (int)buf_meta.st_size;
    int data_mtime = (int)buf_meta.st_mtime;
    int running = 1, deleted = 0; // flag

    if ((int)buf_meta.st_size != 0)
        lseek(fd, 0, SEEK_END);

    while (running)
    {
        // Ex3-3 은 파일을 연 후,
        // (1) 현재 파일 상태 기억: 현재 파일 변경 시간? 파일 크기?
        // (2) 상태가 변경 될 경우, 읽기 시작
        // 파일이 삭제 되었을 경우
        if (access("data.txt", R_OK) == -1)
            deleted = 1;

        while (deleted)
        {
            if (access("data.txt", R_OK) == -1)
            {
                sleep(1);
                perror("access");
            }
            else
            {
                close(fd);
                fd = open("data.txt", O_RDONLY);
                deleted = 0;
                break;
            }
        }

        stat("data.txt", &buf_meta);

        if ((int)buf_meta.st_size == 0)
        {
            lseek(fd, 0, SEEK_SET);
        }

        if ((data_size != (int)buf_meta.st_size) || (data_mtime != (int)buf_meta.st_mtime))
        {
            data_size = (int)buf_meta.st_size;
            data_mtime = (int)buf_meta.st_mtime;

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
                running = 0;
                break;
            }
        }
    }
    close(fd);
    return 0;
}
