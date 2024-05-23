#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CLEAR_COLOR "\x1B[0m"
#define GREEN "\x1B[32m"
#define RED "\x1B[31m"

void complete(FILE *fptr, FILE *fptrw, int index, const char* TODO_PATH) {
  char target[100];
  char line[255];

  int count = 0;

  while(fgets(line, 255, fptr)) {
    if(index < 1) {
      fprintf(stderr, "%s", "Index bellow 1");
      remove("tmp.txt");

      exit(-1);
    }
    if(count == index - 1) { 
      snprintf(target, sizeof(target), "%.3s", line);
      if(!strcmp(target, "[ ]")) {
        char* title = line + 4;

        fprintf(fptrw, "[*] %s", title);
          
      } else {
        fprintf(stderr, "%s", "That task is already complete!");
        remove("tmp.txt");
        exit(-1);
      }
    } else {
      fputs(line, fptrw);
    }

    count++;
  }
  remove(TODO_PATH);
  rename("tmp.txt", TODO_PATH);
}

void list(FILE *fptr) {
  char target[100];
  char line[255]; 
  while(fgets(line, 255, fptr)) {
    char* title = line + 4;

    snprintf(target, sizeof(target), "%.3s", line);

    if(!strcmp(target, "[*]")) {
      printf("%s %s%s",GREEN , title, CLEAR_COLOR);
    } else {
      printf("%s %s%s",RED , title, CLEAR_COLOR);
    }
  }
}
int main(int argc, char** argv) {
  
  const char* TODO_PATH = getenv("TODO_PATH");

  if(argc != 3 && !strcmp("add", argv[1])) {
    fprintf(stderr, "%s", "Problem parsing arguments");
    exit(-1);

  } else if(argc != 3 && !strcmp("complete", argv[1])) {
    fprintf(stderr, "%s", "Problem parsing arguments");
    exit(-1);

  } else if(argc != 2 && !(strcmp("list", argv[1]))) {
    fprintf(stderr, "%s", "Problem parsing arguments");
    exit(-1);

  }

  FILE *fptr;
  FILE *fptrw;

  char* command = argv[1];
    
  fptr = fopen(TODO_PATH, "a+");
  fptrw = fopen("tmp.txt", "w+");

  if(fptr == NULL || fptrw == NULL) {
    fprintf(stderr, "%s", "Could not open file\n");
    exit(-1);
  }
  
  if(!strcmp("add", command)) {
    char* text = argv[2];

    fprintf(fptr, "[ ] %s\n", text);

  } else if(!strcmp("complete", command)) {
    int numLine = atoi(argv[2]);

    complete(fptr, fptrw, numLine, TODO_PATH);
  } else if(!strcmp("list", command)) {
    list(fptr);
  }

  fclose(fptr);
  fclose(fptrw);

  remove("tmp.txt");
  return 0;
}
