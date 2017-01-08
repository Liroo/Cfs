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

typedef struct {
  Fs  container;

  /*
  Private attributes
  */
  char const*	filePath;
  bool		isDirectory;
} FileClass;

static void	File_ctor(Object* self, va_list *ap)
{
  char  *filePath;

  filePath = va_arg(ap, char*);
  if (!filePath) { raise("File constructor called without or NULL parameter"); }

  ((FileClass *)self)->filePath = strdup(filePath);
  if (!((FileClass *)self)->filePath) { raise("Out of memory"); }

  if (access(filePath, R_OK) != 0) { return; }
  struct stat statbuf;
  if (stat(filePath, &statbuf) == -1) { raise("fatal error in FileClass constructor"); }
  ((FileClass *)self)->isDirectory = S_ISDIR(statbuf.st_mode) ? true : false;
}

static void	File_dtor(Object* self)
{
  if (!self) { raise("Destructor called without self"); }
  if (((FileClass *)self)->filePath) { free((char *)(((FileClass *)self)->filePath)); }
}

/*
  Public methods
*/

static char const* File_getFilePathStored(Object *self)
{
  FileClass *this = (FileClass *)self;

  return this->filePath;
}

static bool     File_isDirectory(Object *self)
{
  FileClass *this = (FileClass *)self;

  return this->isDirectory;
}

static bool			File_access(Object *self, int mode)
{
  FileClass *this = (FileClass *)self;

  if (access(this->filePath, mode) == 0) { return true; }
  return false;
}

static char*			File_read(Object *self, int len, int pos)
{
  FileClass *this = (FileClass *)self;

  if (this->isDirectory) { return NULL; }

  int size = this->container.getFileSize(self);

  if (pos > size || pos < 0 || len <= 0) { return NULL; }

  char *res = NULL;
  size = pos + len > size ? size - pos : len;
  res = malloc(size + 1);
  if (!res) { return NULL; }

  int fd = this->container.open(self, O_RDONLY, 0644);
  if (fd < 1) { return NULL; }
  memset(res, 0, size);
  pread(fd, res, size, pos);
  res[size] = 0;
  return res;
}

static char*			File_readFile(Object *self)
{
  FileClass *this = (FileClass *)self;

  if (this->isDirectory) { return NULL; }

  int size = this->container.getFileSize(self);

  return this->container.read(self, size, 0);
}

struct dirent*			File_readDir(Object *self)
{
  FileClass *this = (FileClass *)self;
  DIR *dirent;

  if (!this->isDirectory) { return NULL; }

  dirent = this->container.openDir(self);
  if (!dirent) { return NULL; }
  return readdir(dirent);
}

static int			File_write(Object *self, char const *toWrite, int offset)
{
  FileClass *this = (FileClass *)self;

  if (this->isDirectory || !toWrite) { return 0; }

  int size = this->container.getFileSize(self);
  if (offset < 0) { offset = size + -(-offset % size); }
  if (offset >= size) { offset = size; }

  int fd = this->container.open(self, O_WRONLY | O_CREAT, 0644);
  if (fd <= 2) { return 0; }
  int res = pwrite(fd, toWrite, strlen(toWrite), offset);
  this->container.close(self, fd);
  return res;
}

static bool			File_appendFile(Object *self, char const *toAppend)
{
  FileClass *this = (FileClass *)self;

  if (this->isDirectory || !toAppend) { return NULL; }

  return this->container.write(self, toAppend, this->container.getFileSize(self)) == 0 ? false : true;
}

static bool			File_truncate(Object *self, unsigned int len)
{
  FileClass *this = (FileClass *)self;

  if ((int)len <= 0) { return false; }

  return truncate(this->filePath, len) == 0 ? true : false;
}


static bool			File_chmod(Object *self, mode_t mode)
{
  FileClass *this = (FileClass *)self;

  return chmod(this->filePath, mode) == 0 ? true : false;
}

static bool			File_chown(Object *self, uid_t owner, gid_t group)
{
  FileClass *this = (FileClass *)self;

  return chown(this->filePath, owner, group) == 0 ? true : false;
}

static bool			File_link(Object *self, char const *newPath)
{
  FileClass *this = (FileClass *)self;

  return link(this->filePath, newPath) == 0 ? true : false;
}

static bool			File_stat(Object *self, struct stat *buf)
{
  FileClass *this = (FileClass *)self;

  return stat(this->filePath, buf) == 0 ? true : false;
}

static bool			File_lstat(Object *self, struct stat *buf)
{
  FileClass *this = (FileClass *)self;

  return lstat(this->filePath, buf) == 0 ? true : false;
}

static char*			File_realPath(Object *self)
{
  FileClass *this = (FileClass *)self;

  return realpath(this->filePath, NULL);
}

static size_t   File_getFileSize(Object *self)
{
  FileClass *this = (FileClass *)self;

  if (this->isDirectory) { return 0; }
  FILE *filePtr = this->container.fopen(self, "r");
  if (!filePtr) { return 0; }

  int size = 0;
  fseek(filePtr, 0, SEEK_END);
  size = ftell(filePtr);
  this->container.fclose(self, filePtr);
  return size;
}

static int			File_open(Object *self, int oflag, mode_t mode)
{
  FileClass *this = (FileClass *)self;

  if (this->isDirectory) { return -1; }
  return mode == UINT_MAX ? open(this->filePath, oflag) :
    open(this->filePath, oflag, mode);
}

static FILE*			File_fopen(Object *self, char const *mode)
{
  FileClass *this = (FileClass *)self;

  if (this->isDirectory) { return NULL; }
  return fopen(this->filePath, mode);
}

static bool			File_close(Object *self, int fd)
{
  (void)self;

  if (fd <= 2) { return true; }
  return (close(fd) == 0) ? true : false;
}

static bool			File_fclose(Object *self, FILE *filePtr)
{
  (void)self;

  if (!filePtr) { return true; }
  return (fclose(filePtr) == 0) ? true : false;
}

static DIR*			File_openDir(Object *self)
{
  FileClass *this = (FileClass *)self;

  if (!this->isDirectory) { return NULL; }
  return opendir(this->filePath);
}


static bool			File_mkdir(Object *self, mode_t mode)
{
  FileClass *this = (FileClass *)self;

  if (this->isDirectory) { return true; }
  int res = mkdir(this->filePath, mode);
  if (res == 0) { this->isDirectory = true; }
  return res == 0 ? true : false;
}

static bool			File_rm(Object *self)
{
  FileClass *this = (FileClass *)self;

  int res = remove(this->filePath);
  if (res == 0) { this->isDirectory = false; }
  return res == 0 ? true : false;
}

static bool			File_rename(Object *self, char const *newName)
{
  FileClass *this = (FileClass *)self;

  int res = rename(this->filePath, newName);
  if (res == 0) { this->filePath = strdup(newName); }
  if (!this->filePath) { raise("Out of memory"); }
  return res == 0 ? true : false;
}

static FileClass	_description = {
  {
    {
      sizeof(FileClass), "Fs",
      &File_ctor,
      &File_dtor
    },
    &File_getFilePathStored,
    &File_isDirectory,
    &File_access,
    &File_read,
    &File_readFile,
    &File_readDir,
    &File_write,
    &File_appendFile,
    &File_truncate,

    &File_chmod,
    &File_chown,
    &File_link,
    &File_stat,
    &File_lstat,
    &File_realPath,
    &File_getFileSize,
    &File_open,
    &File_fopen,
    &File_close,
    &File_fclose,
    &File_openDir,

    &File_mkdir,
    &File_rm,
    &File_rename,
  },
  NULL, false
};

Class*	File = (Class*) &_description;
