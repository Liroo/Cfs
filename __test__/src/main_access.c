/*
  main.c test for class File !
 */

#include <limits.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "Object.h"
#include "new.h"
#include "raise.h"
#include "Fs.h"

int	main()
{
  Fs  *file = new(File, "./file");
  Fs  *dir = new(File, "./dir");

  dir->mkdir(dir, DEFFILEMODE);
  file->open(file, O_CREAT, 0644);
  printf("%c\n", dir->access(dir, W_OK) ? '1' : '0');
  printf("%c\n", dir->access(dir, X_OK) ? '1' : '0');
  printf("%c\n", file->access(file, R_OK) ? '1' : '0');
  file->rm(file);
  printf("%c\n", file->access(file, R_OK) ? '1' : '0');
  dir->rm(dir);

  delete(file);
  delete(dir);
}
