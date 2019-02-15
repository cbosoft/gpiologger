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

int main() {
  struct timespec ts;
  int i;
  char ch;
  FILE *fp;
  
  if (argc < (NGPIO+1)) {
    puts("expects arguments: log path for each gpio.");
    exit(-1);
  }

  /* Initialise values */
  char value[NGPIO];
  for (i = 0; i < NGPIO; i++) value[i] = '0';

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
      if (value[i] != ch) {
        // log time of change to file
        printf("%s modified\n", gpio_path[i]);
        timespec_get(&ts, TIME_UTC);
        fprintf(logf[i], "%ld.%09ld\n", ts.tv_sec[i], ts.tv_nsec[i]);
        fflush(logf[i]);
        value[i] = ch;
      }
    }
  }

  /* Tidy up */
  closelogs(logf);
  return 0;
}
