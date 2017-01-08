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

  file->open(file, O_CREAT, 0644);
  file->write(file, "Hello", 0);
  printf("%s\n", file->readFile(file));

  file->write(file, " World!", 5);
  printf("%s\n", file->readFile(file));

  file->write(file, "Byeee", 0);
  printf("%s\n", file->readFile(file));

  file->write(file, "Mundo", -6);
  printf("%s\n", file->readFile(file));

  file->rm(file);

  delete(file);
}
