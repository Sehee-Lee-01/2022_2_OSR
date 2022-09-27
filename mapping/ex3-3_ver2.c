// (1) data.txt 파일 존재시 처리 루틴 변경
// (2) ex3-3 이 ex3-2 보다 먼저 실행한 경우의 문제 해결하기
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
int main(void)
{
    DIR *check = NULL;
    struct dirent *entry = NULL;
    int exist = -1;
    int fd, n;
    char buf[256];

    check = opendir(".");
    while (exist != 1) // 존재 확인할 때까지
    {
        sleep(1);
        entry = readdir(check);
        while (entry)
        {
            if (entry->d_name == "data.txt")
            {
                exist = 1;
                break;
            }
        }
    }

    fd = open("data.txt", O_RDONLY);
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
