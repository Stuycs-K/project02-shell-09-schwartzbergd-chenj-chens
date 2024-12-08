#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define BUFFER_SIZE 256
#define ARRAY_SIZE 16

char * getdir();
char * shortdir();
void print_dir();
char * get_input();
char ** split(char* string, char* delimiters);

void child_process(int forkpid2, int pipeIndex, char** arg_array);
void grandchild_process(int pipeIndex, char** arg_array);
void delete_temp(char * file);
void redirstdout(char * fileName);
void redirstdin(char * fileName);
void redir(char** arr);
int checkforpipe(char ** arr);
void do_cd(char** arg_array);


#endif
