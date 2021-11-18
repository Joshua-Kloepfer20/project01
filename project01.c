#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


int main() {
	char * line = malloc(1000);
	while(1) {
		fgets(line, 1000, stdin);
		int f = fork();
		if (!f) {
			char * argv[100];
			int i = 0;
			while (line != NULL) {
				argv[i] = strsep(&line, " ");
				if (argv[i][strlen(argv[i])] == '\n') argv[i][strlen(argv[i])] = '\0';
				i++;
			}
			printf("argv[0]: %s\targv[1]: %s\n", argv[0], argv[1]);
			execvp(argv[0], argv);
		}
	}
	return 0;
}
