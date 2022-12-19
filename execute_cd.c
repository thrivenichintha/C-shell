#include"custom_header.h"

int execute_cd(char *cmd)
{
	char **argv = argumentize(cmd);
	int argc = argCount(argv);
	int p=0;
	if(argc!=2){
		if(argc!=1){
			printf("error");
			return -1;
		}
	}
	if(argc==1 || !strcmp(argv[1],"~"))
	{
		int check = chdir(getenv("PWD"));
		if(check<p)
			perror("error");
	}
	else
	{
		int check = chdir(argv[1]);
		if(check<p)
			perror("error");
	}
	return 0;
}

