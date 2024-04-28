#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
  const char* TODO_PATH = getenv("TODO_PATH");

  if(argc != 3) {
    fprintf(stderr, "%s", "Not enough arguments");
    exit(-1);
  }

  FILE *fptr;
  FILE *fptrw;

  int count = 0;
  char line[255];
  char* command = argv[1];

  char target[100];
  
  
  fptr = fopen(TODO_PATH, "a+");
  fptrw = fopen("tmp.txt", "w+");

  if(fptr == NULL || fptrw == NULL) {
    fprintf(stderr, "%s", "Could not open file\n");
    exit(-1);
  }
  
  if(!strcmp("add", command)) {
    char* text = argv[2];

    fprintf(fptr, "[ ] %s\n", text);

    remove("tmp.txt");
  } else if(!strcmp("complete", command)) {
    int numLine = atoi(argv[2]);

    while(fgets(line, 255, fptr)) {
      if(count == numLine) { 
        snprintf(target, sizeof target, "%.3s", line);
        if(!strcmp(target, "[ ]")) {
          char* title = line + 4;

          fprintf(fptrw, "[*] %s", title);
          
        } else {
          fprintf(stderr, "%s", "That task is already complete!");
          return -1;
        }
      } else {
        fputs(line, fptrw);
      }

      count++;
    }
    remove(TODO_PATH);
    rename("tmp.txt", TODO_PATH);
  }

  fclose(fptr);
  fclose(fptrw);

  return 0;
}
