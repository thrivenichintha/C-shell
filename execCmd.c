#include "custom_header.h"

const char *Commands[]={"pwd","cd","echo","q","ls","pinfo","fg","bg","setenv","unsetenv","jobs","kjob","overkill"};

int processPointer=0;

struct Process
{
	int  pid;
	char cmd[1024];
	int status; 
};

struct Process backgroundProcess[1024];

int findCmdNo(char *cmd)
{
	int i,n;
	n=strlen(cmd);
	int count=0;
	i=0;
	while(i<n){
		if(cmd[i]==' '){
			break;
		}
		i++;
	}
	count=i;
	char *command = (char *)malloc(sizeof(char)*count+2);
	i=0;
	while(i<count){
		command[i]=cmd[i];
		i++;
	}
	command[i]='\0';
	int totalCommand = sizeof(Commands)/sizeof(char*);
	i=0;
	while(i<totalCommand){
		if(!strcmp(command,Commands[i]))
		{
			free(command);
			return i;
		}
		i++;
	}
	free(command);
	return -1;
}


int execute_fg(char *cmd)
{
	char **argv = argumentize(cmd);
	int argc = argCount(argv);
	int i,count=0;
	i=0;
	if(argc!=2)
	{
		printf("error\n");
		return -1;
	}
	int pindex = atoi(argv[1]);
	for(i=0;i<processPointer;i++){
		if(backgroundProcess[i].pid)
			count++;
		int y=pindex;
		if(count==y)
		{
			int status;
			pid_t wpid = waitpid(backgroundProcess[i].pid,&status,WUNTRACED|WCONTINUED);
			int c=0;
			int check = kill(backgroundProcess[i].pid,SIGCONT);
			if(!check){
				backgroundProcess[i].pid=c;
			}
			return check;
		}
	}
	if(i==processPointer)
	{
		printf("error\n");
		return -1;
	}
	return 0;
}

int execute_bg(char *cmd)
{
	char **argv = argumentize(cmd);
	int argc = argCount(argv);
	int pindex = atoi(argv[1]);
	int i,count=0;
	i=0;

	if(argc!=2)
	{
		printf("error\n");
		return -1;
	}
	while(i<processPointer){
		if(backgroundProcess[i].pid)
			count++;
		int y=pindex;

		if(count==y)
		{
			backgroundProcess[i].status = 1;
			int check = kill(backgroundProcess[i].pid,SIGCONT);
			return check;
		}
		i++;
	}
	if(i==processPointer)
	{
		printf("error\n");
		return -1;
	}
	return 0;
}

void CtrlCHandler(int sig_num)
{
	if(CURR_FOREGROUND==-1)
		return;
	kill(CURR_FOREGROUND,SIGINT);
	fflush(stdout);
}
void CtrlZHandler(int sig_num)
{

	if(CURR_FOREGROUND==-1)
		return;
	kill(CURR_FOREGROUND,SIGTSTP);
	int stat=0;
	strcpy(backgroundProcess[processPointer].cmd,CURR_FOREGROUND_NAME);
	backgroundProcess[processPointer].status = stat;
	backgroundProcess[processPointer].pid = CURR_FOREGROUND;
	processPointer++;
	printf("[+] %s [%d]\n",CURR_FOREGROUND_NAME,CURR_FOREGROUND);
	fflush(stdout);
}

int execute_overkill()
{
	int i=0;
	int count=0;
	while(i<processPointer){
		if(backgroundProcess[i].pid){
			kill(backgroundProcess[i].pid,9);
		}
		i++;
	}
	return 1;
}
int launch_cmd(char *cmd)
{
	int status=0;
    char **argv = argumentize(cmd);
    int argc = argCount(argv);
    pid_t pid;
    pid_t wpid;
    int background = 0;
    if(!strcmp(argv[argc-1],"&")){
        background = 1;
    }
    pid = fork();

    if(!pid)
    {
	    if(background){
            argv[argc - 1] = NULL;
        }
        int check = execvp(argv[0],argv);
        if(check<0)
        {
            perror("error");

            _exit(1);
        }
    }
    else if(pid<0)
    {
            perror("error");
	    _exit(1);
    }
    else if(!background)
    {
        CURR_FOREGROUND = pid;
        CURR_FOREGROUND_NAME = argv[0];
            wpid = waitpid(pid,&status,WUNTRACED);
            if(wpid<0)
            {
                perror("error");
            }
        
    }
    else
    {
        kill(pid,SIGCONT);
        backgroundProcess[processPointer].pid = pid;
        backgroundProcess[processPointer].status = 1;
        strcpy(backgroundProcess[processPointer].cmd,argv[0]);
        processPointer++;
        printf("[+] %s [%d]\n",argv[0],pid);
    }
    return status;
}
int execute_kjob(char *cmd)
{
	char **argv = argumentize(cmd);
	int argc = argCount(argv);
	int count=0;
	int i;
	if(argc!=3)
	{
		fprintf(stderr,"%s\n","Enter as kjob <process index> <signal number>\n");
		return -1;
	}
	int sig = atoi(argv[2]);
	int pid = atoi(argv[1]);
	int check=0;
	i=0;
	while(i<processPointer)
	{
		if(backgroundProcess[i].pid){
			count=count+1;
		}
		if(count==pid)
		{
			int check = kill(backgroundProcess[i].pid,sig);
			return check;
		}
		i++;
	}
	if(i==processPointer)
	{
		fprintf(stderr,"%s\n","Not valid process index use jobs for index\n");
		return -1;
	}
	return 0;
}
int checkBackgroud()
{
	int wpid,status;
	for(int i=0;i<processPointer;i++)
	{
		if(backgroundProcess[i].pid!=0)
		{
			wpid = waitpid(backgroundProcess[i].pid,&status,WNOHANG);
			if(backgroundProcess[i].pid==wpid)
			{
				printf(" %s with pid %d exited with status %d\n",backgroundProcess[i].cmd,wpid,WIFEXITED(status));
				backgroundProcess[i].pid=0;
			}
		}
	}
	return 0;
}
int execCmd(char *cmd)
{
	int original_stdin = dup(0);
	int original_stdout = dup(1);
	int c=-1;
	int z=0;
	int o=1;

	char *file = checkInputRedirection(cmd);
	if(file)
	{
		int fd;
		fd = open(file, O_RDONLY);

		if(fd == c) {
			perror("Failed to open file");
		}
		close(0);
		if(dup2(fd, 0) != z)  
			perror("dup2 fail");
		close(fd);
	}
	file = checkAppendRedirection(cmd);
	if(file)
	{
		int fd;
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);

		if(fd == c) {
			perror("Failed to open file");
		}
		close(1);
		if(dup2(fd, 1) != o)  
			perror("dup2 fail");
		close(fd);
	}
	file = checkOutputRedirection(cmd);
	if(file)
	{
		int fd;
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);

		if(fd == c) {
			perror("Failed to open file");
		}
		close(1);
		if(dup2(fd, 1) != o) 
			perror("dup2 fail");
		close(fd);
	}
	

	int commandNumber = findCmdNo(cmd);

	int status=0;

	if(commandNumber==0){
		status = execute_pwd();

	}
	if(commandNumber==1){
		status = execute_cd(cmd);

	}
	if(commandNumber==2){
		status = execute_echo(cmd);
	}
	if(commandNumber==3){
		_exit(0);

	}
	if(commandNumber==4){

		status = execute_ls(cmd);

	}
	if(commandNumber==5){
		//status = execute_pinfo(cmd);

	}
	if(commandNumber==6){
		status = execute_fg(cmd);

	}
	if(commandNumber==7){
		status = execute_bg(cmd);

	}
	if(commandNumber==8){
		status = execute_setenv(cmd);

	}
	if(commandNumber==9){
		status=execute_unsetenv(cmd);

	}
	if(commandNumber==10){
		status=execute_jobs(cmd);

	}
	if(commandNumber==11){
		status=execute_kjob(cmd);

	}
	if(commandNumber==12){
		status=execute_overkill(cmd);
	}
	if(commandNumber==-1)
	{
		status = launch_cmd(cmd);
	}
	dup2(original_stdout,1);
	dup2(original_stdin,0);
	close(original_stdout);
	close(original_stdin);
	checkBackgroud();
	return status;
}
