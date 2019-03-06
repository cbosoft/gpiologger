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

void clearlog(const char * logpath){
  FILE *logf = fopen(logpath, "w");
  fprintf(logf, "%c", '\r');
  fflush(logf);
  fclose(logf);
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
    value[i] = fp ? fgetc(fp) : 0;
    if (fp == NULL)
      fprintf(stderr, "failed to open %s", gpio_path[i]);
    fclose(fp);
  }

  /* Main loop */
  while(TRUE) {

    for (i = 0; i < NGPIO; i++) {
      
      // Open GPIO file for reading, exit on error
      fp = fopen(gpio_path[i], "r");
      if (fp == NULL) {
        fprintf(stderr, "failed to open %s", gpio_path[i]);
        exit(-1);
      }

      // Read value and check if different
      ch = fgetc(fp);
      fclose(fp);
      if (value[i] != ch && ch > 0) {
        // log time of change to file
#ifdef VERBOSE
        fprintf(stderr, "%s modified: %d |= %d\n", gpio_path[i], value[i], (int)ch);
#endif
        timespec_get(&ts, TIME_UTC);
        FILE *logf = fopen(argv[i+1], "a");
        if (logf == NULL) {
          fprintf(stderr, "!! Could not open logfile '%s'! Exiting...", argv[i+1]);
          exit(-1);
        }
        fprintf(logf, "%ld.%09ld\n", ts.tv_sec, ts.tv_nsec);
        fflush(logf);
        fclose(logf);
        value[i] = ch;
      }
    }
  }
  return 0;
}
