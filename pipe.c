#include "custom_header.h"

const int MAX_PIPE = 16;

char ** parsePipe(char* cmd)
{
	char *sep = "|";
        int count = 0;
	char *str = strdup(cmd);
	char **pipelets = malloc(MAX_PIPE * sizeof(char *));

	pipelets[count++] = strtok(str,"|");
	while(pipelets[count-1]){
		pipelets[count++] = strtok(NULL,"|");
	}
	pipelets[count++] = NULL;
	return pipelets;
}

int pipeExec(char *cmd)
{
	int n=strlen(cmd);
	int p=0;
	for(int i=0;i<n;i++){
		if(cmd[i]=='|'){
			p=1;
			break;
		}
	}
	if(p==0){
		return execCmd(cmd);
	}
	int original_stdout = dup(1);
        int original_stdin = dup(0);
        int fildes[2];


	char **pipelets = parsePipe(cmd);
	int pipe_num = argCount(pipelets);
	int k=0;
	while(k<pipe_num){
		pipelets[k]=parseCommand(pipelets[k]);
		k++;
	}
	//Cross pipe joining var
	int fd = dup(0);

	int i=0;
	int c=-1;
	while(i<pipe_num)
	{
		 if(dup2(fd,0)==c){
                        perror("dup2 fail");
                }
                close(fd);

		if(i==pipe_num-1)
		{
			if(dup2(original_stdout,1)==c){
				perror("dup2 fail");
			}
			close(original_stdout);
		}
		else
		{
			pipe(fildes);
			fd=fildes[0];
			if(dup2(fildes[1],1)==c)
				perror("dup2 fail");
			close(fildes[1]);
		}

		int flag = execCmd(pipelets[i]);
		if(flag){
			break;
		}
		i++;
	}

	//Restore the original I\O field
	dup2(original_stdout,1);
	dup2(original_stdin,0);
	close(original_stdout);
	close(original_stdin);
	if(i!=pipe_num)
	{
		printf("Command %d not executed properly\n",i+1);
		return -1;
	}
	return 0;
}
