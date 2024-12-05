#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define BUFFER_SIZE 256
#define ARRAY_SIZE 16

int err();
void redirstdout(char * fileName);
void redirstdin(char * fileName);
void redir(char** arr);
char* get_input();
char** split(char* string, char* delimiters);
void piper();

#endif
