#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define BUFFER_SIZE 256
#define ARRAY_SIZE 16

char* getdir();
char* get_short_cwd();
void print_dir(char* cwd);

char* get_input();
char** split(char* string, char* delimiters);

void child_process(int forkpid2, int pipeIndex, char** arg_array);
void grandchild_process(int pipeIndex, char** arg_array);

void redir(char** arr);
void redirstdin(char* fileName);
void redirstdout(char* fileName);
int checkforpipe(char** arr);
void delete_temp(char* file);

void do_cd(char** arg_array);

#endif
