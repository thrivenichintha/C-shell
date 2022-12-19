#include "custom_header.h"

int execute_echo(char *cmd)
{
	char **argv = argumentize(cmd);
	int argc = argCount(argv);
	int i=1;
	while(i<argc){
		printf("%s ",argv[i]);
		i++;
	}
	printf("\n");
	return 0;
}
