CC=gcc

main:
	${CC} -c display.c directory.c argumentize.c commandParser.c execute_cd.c execute_ls.c execute_pwd.c lineParser.c pipe.c execCmd.c execute_echo.c input.c redirection.c execute_setenv.c execute_unsetenv.c execute_jobs.c 
	$(CC) main.c display.o directory.o argumentize.o commandParser.o execute_cd.o execute_ls.o execute_pwd.o lineParser.o pipe.o execCmd.o execute_echo.o  input.o  redirection.o execute_setenv.o execute_unsetenv.o execute_jobs.o -o thriveni

thriveni:
	  ${CC} -c display.c directory.c argumentize.c commandParser.c execute_cd.c execute_ls.c execute_pwd.c lineParser.c pipe.c  execCmd.c execute_echo.c input.c pinfo.c redirection.c execute_setenv.c execute_unsetenv.c execute_jobs.c
	  $(CC) main.c display.o directory.o argumentize.o commandParser.o execute_cd.o execute_ls.o execute_pwd.o lineParser.o pipe.o  execCmd.o execute_echo.o input.o pinfo.o redirection.o execute_setenv.o execute_unsetenv.o execute_jobs.o -o thriveni
clean:
	rm *o
	rm thriveni

