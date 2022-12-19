#include<dirent.h>
#include<sys/stat.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<stdio.h>
#include<sys/utsname.h>
#include<fcntl.h>
#include<signal.h>

//Functions in argumentize.c
char ** argumentize(char * cmd);
int argCount(char ** args);

//functions in builtin_ls.c
char * formatDate(char *str,time_t val);

//functions in commandParser.c
char * parseCommand(char * cmd);

//fuctions in display.c
char * dirName();
void display();

int findCmdNo(char *cmd);
int execute_ls(char *cmd);
int execute_pwd();
int execute_cd(char *cmd);
int execute_echo(char *cmd);
int execute_pinfo(char *cmd);
int launch_cmd(char *cmd);
int checkBackgroud();
int execCmd(char *cmd);

//functions in input.c
char **input();

//fuctions in lineParser.c
char ** tokanize(char * ptr);

//functions in pinfo.c
int exec_pinfo(int pid);

//functions in pipe.c
int pipeExec(char *cmd);

void CtrlCHandler(int sig_num);
void CtrlZHandler(int sig_num);

//functions in redirection.c

char *checkInputRedirection(char *cmd);
char *checkOutputRedirection(char *cmd);
char *checkAppendRedirection(char *cmd);
void trunacateCmd(char* cmd,int c);

int execute_setenv(char* cmd);
int execute_unsetenv(char* cmd);

struct ongoing_processes {
	char* p_pid;
	char p_name[1024];
	char p_stime[128];
	char p_status[128];
}jobs;
extern struct ongoing_processes cur_jobs[2048];
int execute_jobs(char* cmd);
int execute_kjob(char* cmd);

// variables
pid_t CURR_FOREGROUND;
char * CURR_FOREGROUND_NAME;
