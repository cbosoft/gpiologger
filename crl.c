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

void closelogs(FILE **logfs) {
  int i;
  for (i = 0; i < NGPIO; i++) {
    fclose(logfs[i]);
  }
}

int main(int argc, char *argv[]) {
  struct timespec ts;
  int i;
  char ch;
  FILE *fp;
  
  if (argc < (NGPIO+1)) {
    puts("expects arguments: log path for each gpio.");
    exit(-1);
  }

  /* Initialise values */
  int value[NGPIO];
  for (i = 0; i < NGPIO; i++) {
    fp = fopen(gpio_path[i], "r");
    value[i] = fgetc(fp);
    if (fp == NULL)
      printf("failed to open %s", gpio_path[i]);
    fclose(fp);
  }

  /* Open log files */
  FILE *logf[NGPIO];
  for (i = 0; i < 3; i++) {
    printf("opening log %s\n", argv[i+1]);
    logf[i] = fopen(argv[i+1], "w");
    if (logf[i] == NULL) {
      printf("failed to open logf %s\n", argv[i+1]);
      exit(-1);
    }
  }

  /* Main loop */
  while(TRUE) {

    for (i = 0; i < NGPIO; i++) {
      
      // Open GPIO file for reading, exit on error
      fp = fopen(gpio_path[i], "r");
      if (fp == NULL) {
        printf("failed to open %s", gpio_path[i]);
      	closelogs(logf);
      }

      // Read value and check if different
      ch = fgetc(fp);
      fclose(fp);
      if (value[i] != ch && ch > 0) {
        // log time of change to file
        printf("%s modified\n", gpio_path[i]);
        timespec_get(&ts, TIME_UTC);
        fprintf(logf[i], "%ld.%09ld\n", ts.tv_sec, ts.tv_nsec);
        fflush(logf[i]);
        fflush(stdout);
        value[i] = ch;
      }
    }
  }

  /* Tidy up */
  closelogs(logf);
  return 0;
}
