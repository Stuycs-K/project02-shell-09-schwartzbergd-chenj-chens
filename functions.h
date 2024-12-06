#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define BUFFER_SIZE 256
#define ARRAY_SIZE 16

char * getdir();
char * get_input();
char ** split(char* string, char* delimiters);

void redirstdout(char * fileName);
void redirstdin(char * fileName);
void redir(char** arr);
int checkforpipe(char ** arr);

#endif
