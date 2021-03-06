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
  file->appendFile(file, "J'aime beaucoup l'objet\n");
  printf("%s\n", file->read(file, -5, 10) ? "" : "Null");
  printf("%s\n", file->read(file, 0, 5) ? "" : "Null");
  printf("%s\n", file->read(file, 0, 100) ? "" : "Null");
  printf("%s\n", file->read(file, 100, 0));
  printf("%s\n", file->read(file, 5, 5));
  file->rm(file);

  delete(file);
}
