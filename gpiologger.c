/*
  Runs until stopped. Reads gpio files, logs res and time to file.
  */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "config.h"

#define TRUE 1

/* https://gist.github.com/sevko/d23646ba07c77c15fde9 */
long getMicrotime(void){
  struct timeval currentTime;
  gettimeofday(&currentTime, NULL);
  return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}

int main() {
  int i;
  char ch;
  while(TRUE) {
    printf("%ld, ", getMicrotime());
    for (i = 0; i < 3; i++) {
      FILE *fp;
      fp = fopen(gpio_path[i], "r");
      if (fp == NULL)
        perror("could not open\n");
      while((ch = fgetc(fp)) != EOF)
        if (ch != '\n')
          printf("%c", ch);
      if (i < 2)
        printf("%c", ',');
      fclose(fp);
    }
    printf("%c", '\n');
  }
  return 0;
}
