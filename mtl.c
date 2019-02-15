/*
  Runs until stopped. Reads gpio files, logs res and time to file.
  */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "defs.h"
#include "config.h"

void closelogs(FILE **logfs) {
  int i;
  for (i = 0; i < NGPIO; i++) {
    fclose(logfs[i]);
  }
}


int main(int argc, char *argv[]) {

  setbuf(stdout, NULL);
  int i;
  time_t mtimes[NGPIO];
  time_t mtimes_ns[NGPIO];
  struct stat attr;

  if (argc < (NGPIO+1)) {
    puts("expects arguments: log path for each gpio.");
    exit(-1);
  }
  
  /* Initialise mtime array */

  for (i = 0; i < NGPIO; i++) {
    if (stat(gpio_path[i], &attr) != 0) {
      printf("failed to open %s", gpio_path[i]);
      exit(-1);
    }
    else {
      mtimes[i] = attr.st_mtim.tv_sec;
      mtimes_ns[i] = attr.st_mtim.tv_nsec;
    }
  }

  /* Open log files */
  FILE *logf[NGPIO];
  for (i = 0; i < 3; i++) {
    printf("opening log %s\n", argv[i+1]);
    logf[i] = fopen(argv[i+1], "w");
    if (logf[i] == NULL) {
      printf("failed to open logf %s", argv[i+1]);
      exit(-1);
    }
  }


  while(TRUE) {
    // printf("%ld.%09ld %ld.%09ld %ld.%09ld \n", mtimes[0], mtimes_ns[0], mtimes[1], mtimes_ns[1], mtimes[2], mtimes_ns[2]);
    for (i = 0; i < NGPIO; i++) {
      if (stat(gpio_path[i], &attr) != 0) {
        printf("failed to read %s", gpio_path[i]);
        closelogs(logf);
        exit(-1);
      }

      if (attr.st_mtim.tv_sec != mtimes[i] || attr.st_mtim.tv_nsec != mtimes_ns[i]) {
        mtimes[i] = attr.st_mtim.tv_sec;
        mtimes_ns[i] = attr.st_mtim.tv_nsec;
        printf("%s modified\n", gpio_path[i]);
        fprintf(logf[i], "%ld.%09ld\n", mtimes[i], mtimes_ns[i]);
        fflush(logf[i]);
      }
    }
  }

  /* Tidy up */
  closelogs(logf);

  return 0;
}
