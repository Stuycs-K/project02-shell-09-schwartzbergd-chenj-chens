[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Tfg6waJb)

# Systems Project2 - MyShell

## Sally Sells CShells by the Seashore: David Schwartzberg, Jialan Chen, Stacey Chen

### Features

#### Basic Requirements
- Parses each input line, executing each line split on semicolons(no spaces in between)
- Forks and parent waits for child's execvp() to finish
- cd functionality (with or without args)
- Exits on "exit" and EOF
- Redirection of stdin, stdout, and piping works by use of a temp file

#### Extra Features
- Home directory shortened to "~" when possible

### Bugs
- No known bugs

### Other Notes
- When cwd is "before" home, the cwd will not shorten to ~.
- Do not include any trailing spaces for commands as they might fail.
- Semicolons must be exactly in between commands with no spaces (e.g. "echo hello;ls")

### Functions

#### input/output
- char* getdir();
- char* get_short_cwd();
- void print_dir(char* cwd);
- char* get_input();
- char** split(char* string, char* delimiters);

#### execvp() and fork() wrappers
- void child_process(int forkpid2, int pipeIndex, char** arg_array);
- void grandchild_process(int pipeIndex, char** arg_array);

#### redirection
- void redir(char** arr);
- void redirstdin(char* fileName);
- void redirstdout(char* fileName);
- int checkforpipe(char** arr);
- void delete_temp(char* file);

#### miscellaneous
- void do_cd(char** arg_array);