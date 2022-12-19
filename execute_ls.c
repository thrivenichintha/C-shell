#include"custom_header.h"


int execute_ls(char *cmd){
	char *path=".";
	DIR *dir;
	struct dirent *directoryPtr;
	dir = opendir(path);
	directoryPtr = readdir(dir);
	if(dir==NULL)
	{
		perror("error ");
		return -1;
	}
	int f=1;
	while(f==1){
	if(directoryPtr!=NULL){
		if(directoryPtr->d_name[0]!='.'){
			printf("%s\n",directoryPtr->d_name);
		}
		directoryPtr = readdir(dir);
	}
	else{
		break;
	}
	}
	closedir(dir);
	return 0;
}

