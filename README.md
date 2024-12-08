[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Tfg6waJb)

# Systems Project2 - MyShell

## (funny pun here): David Schwartzberg, Jialan Chen, Stacey Chen

### Features

#### Basic Requirements
- Parses each input line, executing each line split on semicolons(no spaces in between)
- Forks and parent waits for child's execvp() to finish
- cd functionality (with or without args)
- Exits on "exit" and EOF
- Redirection of stdin, stdout, and piping works by use of a temp file

#### Extra Features
- Home directory shortened to "~" when possible
- ADD EXTRA STUFF HERE OR DELETE BEFORE FINAL 

### Unfinished Features
- something here probably

### Bugs
- NOTHING FOUND YET

### Functions
- char* getdir()
- char* get_input()
- char** split(char* string, char* delimiters)

- int chdir_wrapper(char* newdir)
- void exec_wrapper(char** arg_array)

- void redirstdout(char* fileName)
- void redirstdin(char* fileName)
- void redir(char** arr)
- int checkforpipe(char** arr)

- other functions here
