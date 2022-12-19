#include "custom_header.h"


const int MAX_COMMAND = 16;

int argCount(char ** args)
{
    int count=0;
    while(args[count++]);
    count--;
    return count;
}

char ** argumentize(char * cmd)
{
	char *sep = " ";
	int count=0;

    char *str = strdup(cmd);
    char **args = malloc(MAX_COMMAND * sizeof(char *));
    args[count++] = strtok(str,sep);
    while(args[count-1]){
        args[count++] = strtok(NULL,sep);
    }
    args[count++] = NULL;
    return args;
}

