#include "custom_header.h"
char * parseCommand(char * cmd)
{
    int length = strlen(cmd);
    int i=0;
    int count=0;
    while(i<length){
        if(!(cmd[i]==' ' || cmd[i]=='\t')){
            break;
	}
	i++;
    }
    count=count+i;
    length=length-count;
    i=0;
    while(i<=length){
        cmd[i] = cmd[i+count];
	i++;
    }
    char *parsed = strdup(cmd);
    i=0;
    int j=0;
    count=0;
    while(i<=length){
        if(cmd[i]==' '|| cmd[i]=='\t')
            count=count+1;
        else
        {
            if(count)
            {
                parsed[j++]=' ';
                count=0;
            }
            parsed[j++]=cmd[i];
        }
	i++;
    }
    return parsed;
}
