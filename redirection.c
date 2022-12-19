#include"custom_header.h"

void truncateCmd(char* cmd, int c){
	char** argv=argumentize(cmd);
        int count=argCount(argv);
	int i=0;
	int n=0;
	int len=strlen(cmd);
	for(i=0;i<c;i++){
		n=n+strlen(argv[i]);
		n=n+1;
	}
	int m = strlen(argv[c])+strlen(argv[c+1])+1;
	i=n;
	while(i<len-m){
		cmd[i-1]=cmd[i+m];
		i++;
	}
	cmd[i]='\0';

}
char* checkInputRedirection(char* command){
	char** argv=argumentize(command);
	int i=0;
	int count=argCount(argv);
	while(i<count){
		if(!strcmp(argv[i],"<")){
			break;
		}
		i++;
	}
	if(i!=count){
		truncateCmd(command,i);
		return argv[i+1];
	}
	return NULL;
}

char* checkOutputRedirection(char* command){
	char** argv=argumentize(command);
        int count=argCount(argv);
        int i=0;
        while(i<count){
                if(!strcmp(argv[i],">")){
                        break;
                }
		i++;
        }
        if(i!=count){
                truncateCmd(command,i);
                return argv[i+1];
        }
        return NULL;
}

char* checkAppendRedirection(char* command){
	char** argv=argumentize(command);
        int count=argCount(argv);
        int i=0;
        while(i<count){
                if(!strcmp(argv[i],">>")){
                        break;
                }
                i++;
        }
        if(i!=count){
                truncateCmd(command,i);
                return argv[i+1];
        }
        return NULL;
}

