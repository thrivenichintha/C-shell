#include"custom_header.h"

int execute_unsetenv(char* cmd){
	char **argv=argumentize(cmd);
	int count=argCount(argv);
	if(count!=2){
		printf("stderror");
		return -1;
	}
	int check=0;
	check=unsetenv(argv[1]);
	if(check<0){
		perror("error");
		return -1;
	}
	return 0;
}
