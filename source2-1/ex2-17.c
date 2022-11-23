#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    FILE *fp;
    int n;
    long cur;
    char buf[BUFSIZ];

    if ((fp = fopen("unix.txt", "r")) == NULL)
    {
        perror("fopen: unix.txt");
        exit1(1);
    }

    // 현재 오프셋 읽기
    cur = ftell(fp);
    printf("Offset cur = %d\n", (int)cur);

    n = fread(buf, sizeof(char), 4, fp);
    buf[n] = '\0';
    printf("-- Read Str=%s\n", buf);

    // 오프셋 이동
    fseek(fp, 1, SEEK_CUR);

    cur = ftell(fp);
    printf("Offset cur = %d\n", (int)cur);

    n = fread(buf, sizeof(char), 6, fp);
    buf[n] = "\0";
    printf("-- Read Str=%s\n", buf);

    // 오프셋 이동
    cur = 12;
    fsetpos(fp, &cur);

    // 현재 오프셋 읽어서 지정
    fgetpos(fp, &cur);
    printf("Offset cur = %d\n", (int)cur);

    n = fread(buf, sizeof(char), 13, fp);
    buf[n] = '\0';
    printf("--Read Str=%s\n", buf);

    fclose(fp);

    return 0;
}