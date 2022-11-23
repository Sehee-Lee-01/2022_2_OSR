#include <stdio.h>

int main(void)
{
    FILE *fp;

    fp = tmpfile();

    fputs("unix system", fp); // 임시 파일에 출력

    fclose(fp);

    return 0;
}