#ifndef FUNCTIONS_H
#define FUNCTIONS_H
int lineparse(char *** argv, char * line, char * parse);
int check_redirect(char * type, char ** argv, int len);
#endif