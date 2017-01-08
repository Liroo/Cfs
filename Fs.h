
/*
  File declaration
 */

#ifndef FS_H
# define FS_H

# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <dirent.h>
# include "Object.h"

/*
 */
typedef struct s_Fs
{
  /*
    To create an Object FS *, use `new(File, [fileName]);`
   */

  /*
    Private attributes
   */
  Class		base;

  /*
    Public method
   */

  /*
    getter of FilePath attribute
   */
  char const*			(*getFilepathStored)(Object *self);
  /*
    getter of isDirectory
    true if path pointed by filePath is a directory
   */
  bool      (*isDirectory)(Object *self);
  /*
    access(2)
   */
  bool			(*access)(Object *self, int mode);
  /*
    read(2), pread(2)
   */
  char*			(*read)(Object *self, int length, int position);
  /*
    return file content
   */
  char*			(*readFile)(Object *self);
  /*
    readdir(2)
   */
  struct dirent*	(*readDir)(Object *self);
  /*
    write(2), pwrite(2)
   */
  int			(*write)(Object *self, char const *toWrite, int offset);
  /*
    write str at the end of the file
   */
  bool			(*appendFile)(Object *self, char const *toAppend);
  /*
    truncate(2)
   */
  bool			(*truncate)(Object *self, unsigned int len);

  /*
    chmod(2)
   */
  bool			(*chmod)(Object *self, mode_t mode);
  /*
    chown(2)
   */
  bool			(*chown)(Object *self, uid_t owner, gid_t group);
  /*
    link(2)
   */
  bool			(*link)(Object *self, char const *newPath);
  /*
    stat(2)
   */
  bool			(*stat)(Object *self, struct stat *buf);
  /*
    lstat(2)
   */
  bool			(*lstat)(Object *self, struct stat *buf);
  /*
    realpath(2)
   */
  char*			(*realPath)(Object *self);
  /*
    get file content size
   */
  size_t    (*getFileSize)(Object *self);

  /*
    open(2)
   */
  int			(*open)(Object *self, int oflag, mode_t );
  /*
    fopen(2)
   */
  FILE*			(*fopen)(Object *self, char const *mode);
  /*
    close(2)
   */
  bool			(*close)(Object *self, int fd);
  /*
    fclose(2)
   */
  bool			(*fclose)(Object *self, FILE *filePtr);
  /*
    opendir(2)
   */
  DIR*			(*openDir)(Object *self);

  /*
    mkdir(2)
   */
  bool			(*mkdir)(Object *self, mode_t mode);
  /*
    remove(2), unlink(2), rmdir(2)
   */
  bool			(*rm)(Object *self);
  /*
    rename the filePath
   */
  bool			(*rename)(Object *self, char const *newName);
}		Fs;

extern Class* File;

#endif /* !FS_H_ */
