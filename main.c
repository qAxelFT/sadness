#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
  FILE *fptr;
  char line[100];

  fptr = fopen("sad.txt", "a+");

  if(fptr == NULL) {
    fprintf(stderr, "%s", "Could not open file\n");
  }

  fclose(fptr); 
}
