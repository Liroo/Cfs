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
  printf("%d\n", dir->appendFile(dir, ""));
  printf("%d\n", file->appendFile(file, "Hello World !"));
  printf("%d\n", file->appendFile(file, "\nBonjour :)"));
  printf("%s\n", file->readFile(file));
  dir->rm(dir);
  file->rm(file);

  delete(file);
  delete(dir);
}
