/*
  crl -- Constant Read Logger

  Reads gpio until stopped (sigterm, sigkill... )

  Constantly reads and outputs value. 
  */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#include "defs.h"
#include "config.h"

/* https://gist.github.com/sevko/d23646ba07c77c15fde9 */
unsigned long getMicrotime(void){
  struct timeval currentTime;
  gettimeofday(&currentTime, NULL);
  return currentTime.tv_sec * (long)1e6 + currentTime.tv_usec;
}

int main() {
  struct timespec ts;
  int i;
  char ch;
  FILE *fp;

  while(TRUE) {
    timespec_get(&ts, TIME_UTC);
    printf("%ld.%09ld, ", ts.tv_sec, ts.tv_nsec);
    for (i = 0; i < 3; i++) {
      fp = fopen(gpio_path[i], "r");
      if (fp == NULL) {
        printf("failed to open %s", gpio_path[i]);
      	exit(-1);
      }
      ch = fgetc(fp);
      printf("%c", ch);
      if (i < 2) {
        printf("%c", ',');
      }
      fclose(fp);
    }
    printf("%c", '\n');
  }
  return 0;
}
