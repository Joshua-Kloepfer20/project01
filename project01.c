#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


int main() {
	char * line = malloc(1000);
	int status;
	while(1) {
		char pwd[500];
		getcwd(pwd, 500);
		printf("pwd- %s", pwd);
		int f = fork();
		fgets(line, 1000, stdin);
		if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
		if (strcmp(line, "exit") == 0) return 0;
		f = fork();
		if (!f) {
			char * argv[1000];
			int i = 0;
			while (line != 0) {
				argv[i] = strsep(&line, " ");
				if (argv[i][strlen(argv[i]) - 1] == '\n') argv[i][strlen(argv[i]) - 1] = '\0';
				i++;
			}
			if (strcmp(argv[0], "cd") == 0) return 1;
			execvp(argv[0], argv);
			return 0;
		}
		else {
			waitpid(f, &status, 0);
//			if (WEXITSTATUS(status) == 1) {
				
//			}
		}
	}
	free(line);
	return 0;
}
