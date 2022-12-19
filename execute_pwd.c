#include"custom_header.h"

int execute_pwd()
{
    char *path = (char *)malloc(1000);
    getcwd(path,1024);
    printf("%s\n",path);
    free(path);
    return 0;
}

