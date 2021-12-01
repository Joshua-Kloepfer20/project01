#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int lineparse(char *** argv, char * line, char * parse) {
	*argv = malloc(1000);
	int i = 0;
	char * linecpy = line;
	while (line != 0) {
		(*argv)[i] = strsep(&line, parse);
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
	if (i == len) return 0;
	return i;
}