#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include "functions.h"

int main() {
	char ** args = malloc(1000);
	int status;
	int total_arg = 0;
	int curr_arg = 0;
	while(1) {
		char * line = malloc(1000);
		if (curr_arg >= total_arg - 1) {
			free(args);
			curr_arg = 0;
			total_arg = 0;
			char pwd[500];
			getcwd(pwd, 500);
			printf("pwd- %s  ", pwd);
			fgets(line, 1000, stdin);
			if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
			if (strcmp(line, "exit") == 0) {
				return 0;
			}
			total_arg = lineparse(&args, line, ";");
		}
		else {
			curr_arg++;
		}
		char ** argv;
		int argc = lineparse(&argv, args[curr_arg], " ");
		char type;
		int dupin;
		int dupout;
		if (strcmp(argv[0], "cd") == 0) chdir(argv[1]);
		int i;
                if (i = check_redirect(&type, argv, argc)) {
                	if (type == '<') {
                        	int stdin_new = open(argv[i+1], O_RDONLY);
                                dupin = dup(0);
				dup2(stdin_new, 0);
                        }
                        else if (type == '>') {
                        	int stdout_new = open(argv[i+1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
                        	dupout = dup(1);
				dup2(stdout_new, 1);
                        }
                        int a;
                        for (a = i; a < argc; a++) {
                                argv[a] = NULL;
                        }
                }
		int f = fork();
		if (!f) {
			return execvp(argv[0], argv);
		}
		else {
			waitpid(f, &status, 0);
			if (i && type == '>') {
				dup2(dupout, 1);
			}
			else if (i && type == '<') {
				dup2(dupin, 0);
			}
			free(argv);
		}
	}
	return 0;
}
