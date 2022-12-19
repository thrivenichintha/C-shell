#include "custom_header.h"

void CtrlDHandler(int sig){
	if(sig==SIGTSTP){
		printf("exiting");
	}
	exit(1);
}

void display()
{
    struct utsname userInfo;
    uname(&userInfo);
    checkBackgroud();
    const char *sys_name = userInfo.sysname;
    const char *user_name = getenv("USER");
    char *dir=dirName();
    printf("%s@%s:%s",user_name,sys_name,dir);
    printf("%c",'>');
    CURR_FOREGROUND = -1;
    CURR_FOREGROUND_NAME = NULL;
    signal(SIGINT,CtrlCHandler);
    signal(SIGTSTP,CtrlZHandler);
    //signal(SIGTSTP,CtrlDHandler);

    char **cmd = input();
    int i;
    for(i=0;cmd[i]!=NULL;i++){
        cmd[i]=parseCommand(cmd[i]);
        pipeExec(cmd[i]);
    }
}
