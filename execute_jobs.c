#include"custom_header.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>

struct ongoing_processes cur_jobs[2048];
int jobs_sz;

int cmp (const void *a, const void *b)
{
	struct ongoing_processes *aa = (struct ongoing_processes*)a;
	struct ongoing_processes *bb = (struct ongoing_processes*)b;
	return atoi(aa->p_stime) - atoi(bb->p_stime);
}

void trim (char* s, char* cmd)
{
	int it, i, j, sz = 0;
	for (i=0; s[i] != '\0'; ++i, ++sz);
	for (i=0; i<sz; ++i)
		if (!isspace(s[i]))
			break;
	for (j=sz-1; j>=0; --j)
		if (!isspace(s[j]))
			break;
	for (it=0; i<=j; ++i, ++it)
		cmd[it] = s[i];
	cmd[it] = '\0';
}

int execute_jobs (char * cmd){
	int flag=1;
	int p_sz = 512;
	jobs_sz = 0;
	DIR *dir = opendir("/proc");
	struct dirent *dst;
	struct stat st;
	char path[2048], tmp[2048];
	char* buff;
	while (dst = readdir(dir))
	{
		strcpy(path, "/proc/");
		strcat(path, dst->d_name);
		stat(path, &st);
		if (S_ISDIR(st.st_mode) && (dst->d_name[0] - '0' >= 1) && (dst->d_name[0] - '0' <= 9))
		{
			cur_jobs[jobs_sz].p_pid = dst->d_name;
			strcpy(tmp, cur_jobs[jobs_sz].p_pid);
			trim(tmp, cur_jobs[jobs_sz].p_pid);
			jobs_sz++;
		}
	}
	for (int i=0, fd, ct, j; i<jobs_sz; ++i)
	{
		strcpy(path, "/proc/");
		strcat(path, cur_jobs[i].p_pid);
		strcat(path, "/stat");
		fd = open(path, O_RDONLY);
		char s[2048];
		read(fd, s, 10000);
		j = ct = 0;
		while (ct < 21)
			if (isspace(s[j]))
			{
				++ct;
				++j;
			}
			else ++j;
		ct = 0;
		while (!isspace(s[j]))
			cur_jobs[i].p_stime[ct++] = s[j++];
		cur_jobs[i].p_stime[ct] = '\0';
		strcpy(tmp, cur_jobs[i].p_stime);
		trim(tmp, cur_jobs[i].p_stime);
		strcpy(path, "/proc/");
		strcat(path, cur_jobs[i].p_pid);
		strcat(path, "/status");
		FILE* file = fopen(path, "r");
		if (file != NULL)
		{
			size_t sz = 0;
			while (getline(&buff, &sz, file) != -1)
			{
				if (strncmp("Name", buff, 4) == 0)
					trim(buff+5, cur_jobs[i].p_name);
				else if (strncmp("State", buff, 5) == 0)
				{
					trim(buff+6, cur_jobs[i].p_status);
					break;
				}
			}
		}
		else
		{
			perror(path);
			return 0;
		}
		fclose(file);
		close(fd);
	}
	qsort(cur_jobs, jobs_sz, sizeof(jobs), cmp);
	if (flag){
		for (int i=0; i<jobs_sz; ++i){
				printf("[%d]%s%s[%s]\n", i+1, cur_jobs[i].p_status, cur_jobs[i].p_name, cur_jobs[i].p_pid);
		}
	}


	return 0;
}
