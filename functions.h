#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define BUFFER_SIZE 256
#define ARRAY_SIZE 16

char * getdir();
char * shortdir();
void print_dir();
void cd_check(char** arg_array);
char * get_input();
char ** split(char* string, char* delimiters);

char** get_command(char* input, char** cmd_array);
void child_process(int forkpid2, int pipeIndex, char** arg_array);
void grandchild_process(int pipeIndex, char** arg_array);
void delete_temp(char * file);
void redirstdout(char * fileName);
void redirstdin(char * fileName);
void redir(char** arr);
int checkforpipe(char ** arr);

#endif
