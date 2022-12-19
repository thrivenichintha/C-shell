#include "custom_header.h"

char ** tokanize(char * ptr)
{
    int MAX_COMMAND = 16;
    char *tok;
    int count=0;
    char *n=NULL;
    char *str = strdup(ptr);
    char **command = malloc(MAX_COMMAND * sizeof(char *));
    char *sep = ";\n";
    command[count++] = strtok(str,sep);
    while(command[count-1]){
        command[count++] = strtok(n,sep);
    }
    command[count++] = n;
    return command;
}
