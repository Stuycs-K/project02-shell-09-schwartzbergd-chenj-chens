int func(int num) {
  return num;
}

// splits commands by semicolon; returns char * []; takes in a char array
char** scSplit(char* line, char ** arg){
  char * x[256];
  char * curr = arr;
  char * token;
  int i = 0;
  while (token = strsep(&curr, ";")){
    strcpy(x[i], token);
    i++;
  }
  return x;
}
