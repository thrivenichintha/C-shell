#include"custom_header.h"

int execute_setenv(char* cmd){
	int check=0;
	char** argv=argumentize(cmd);
	int count=argCount(argv);
	if(count==3){
		check=setenv(argv[1],argv[2],1);
	}
	else if( count!=2 && count!=3){
		printf("stderror");
		return -1;
	}
	else{
		check=setenv(argv[1],"",1);
	}
	if(check<0){
		perror("error");
		return -1;
	}
	return 0;
}

	
