/************************************************************************
 *
 * Purpose: Program to demonstrate the 'stat' function.
 *          The program will show the modification and access times
 *	    plus the size of a file.
 *
 * Author:  M J Leslie
 *
 * Date:    01-Jun-95 MJL Minor bug fixed.
 *          13-Apr-95 MJL Inital Release
 *
 * Notes:   This function is only available to Unix systems. If you
 *          are on a DOS machine, this will not compile.
 *
 * Compile: Change the #define (below) to a suitable file name on your
 *          system. The file name is not passed on the command line
 *	    as I did not want to complicate the example.
 *
 ************************************************************************/

#include <stdio.h>    /* printf			*/
#include <sys/stat.h> /* declare the 'stat' structure	*/
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include<stdlib.h>

#define FILENAME "README.md" /* PUT YOUR FILE NAME HERE	*/

/************************************************************************/

char *format_time(time_t cal_time);

void file_stat(char *filename);

/************************************************************************/

int main() { file_stat(FILENAME); }

/************************************************************************/

void file_stat(char *filename) {
  struct stat stat_p; /* 'stat_p' is a pointer to a structure
                       * of type 'stat'.  			*/

  /* Get stats for file and place them in
   * the structure.			*/
  if (-1 == lstat(filename, &stat_p)) {
    printf(" Error occoured attempting to stat %s\n", filename);
    exit(0);
  }
  /* Print a few structure members.	*/

  printf("Stats for %s \n", filename);

  printf("Modify time is %s", format_time(stat_p.st_mtime));

  /* Access time does not get updated
     if the filesystem is NFS mounted!	*/

  printf("Access time is %s", format_time(stat_p.st_atime));

  printf("File size is   %ld bytes\n", stat_p.st_size);
}

/************************************************************************/

char *format_time(time_t cal_time) {
  struct tm *time_struct;
  static char string[30];
  /* Put the calendar time into a structure
   * if type 'tm'.			*/
  time_struct = localtime(&cal_time);

  /* Build a formatted date from the
   * structure.				*/
  strftime(string, sizeof string, "%h %e %H:%M\n", time_struct);

  /* Return the date/time			*/
  return (string);
}
