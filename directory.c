#include "custom_header.h"
char * dirName()
{
    char *path = (char *)malloc(1000);
    getcwd(path,1000);
    char *home = getenv("PWD");
    int x=strlen(path);
    int y=strlen(home);
    if(x==y){
        return "~";
    }
    else if(x >= y)
    {
        char *relativePath = (char *)malloc(sizeof(path)+1);
        //int lenHome = strlen(home);
        //int lenPath = strlen(path);
        relativePath[0]='~';
	int i=y;
        while(i<=x){
            relativePath[i-y+1] = path[i];
	    i++;
	}
        return relativePath;
    }
    return path;
}

