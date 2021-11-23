#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

int lineparse(char *** argv, char * line) {
	*argv = malloc(1000);
	int i = 0;
	while (line != 0) {
		(*argv)[i] = strsep(&line, " ");
		if ((*argv)[i][strlen((*argv)[i]) - 1] == '\n') (*argv)[i][strlen((*argv)[i]) - 1] = '\0';
		i++;
	}
	return i;
}

int check_redirect(char * type, char ** argv, int len) {
	int i;
	for (i = 0; i < len; i++) {
		if (strcmp(argv[i], ">") == 0) {
			*type = '>';
			break;
		}
		else if (strcmp(argv[i], "<") == 0) {
			*type = '<';
			break;
		}
	}
	if (i == len - 1) return 0;
	return i;
}

int main() {
	char * line = malloc(1000);
	int status;
	while(1) {
		char pwd[500];
		getcwd(pwd, 500);
		printf("pwd- %s\t", pwd);
		fgets(line, 1000, stdin);
		char ** argv;
		int argc = lineparse(&argv, line);
		char type;
		if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
		if (strcmp(line, "exit") == 0) return 0;
		else if (strcmp(argv[0], "cd") == 0) chdir(argv[1]);
		int f = fork();
		if (!f) {
			if (int i = check_redirect(&type, argv, argc)) {
                        	if (type == '<') {
                                	int stdin_new = open(argv[i+1], O_CREAT | O_TRUNC);
                                	dup2(stdin_new, 0);
                        	}
                	}
			return execvp(argv[0], argv);
		}
		else {
			waitpid(f, &status, 0);
			free(argv);
		}
	}
	free(line);
	return 0;
}
