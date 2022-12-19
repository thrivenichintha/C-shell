#include "custom_header.h"
char ** input()
{
    char buffer[1024];
    char *b = buffer;
    size_t bufsize = 1024;
    int n = getline(&b,&bufsize,stdin);
    return tokanize(buffer);
}
