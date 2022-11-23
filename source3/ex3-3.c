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

    fd = open("data.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Open data.txt");
        exit(1);
    }
    while (1)
    {
        n = read(fd, buf, 255);
        buf[n] = '\0';
        if (n == -1)
        {
            perror("Read error");
        }
        else if (n == 0)
            continue;
        write(1, "Recv>> ", 7);
        write(1, buf, n);
        if (n == 1 && buf[0] == 'q')
        {
            write(1, "Terminate\n", 10);
            break;
        }
    }
}