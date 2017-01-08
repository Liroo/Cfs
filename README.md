# Cfs
### C Modular module that allow to use fs like from Node.js on C using Fs type

---

#### The main goal of this project is to provide a fs module like to C language.

C language already have all those method separated in multiple headers files.

Actually, this module provide a `Fs` struct pointing to a file in your file system.
You will be able to apply many method on your file using right functions members of `Fs`. 

To declare a new instance of Fs, use:
`Fs VARIABLE_NAME = new(File, PATH_TO_FILE)`

There is many examples in directory **__test__/src**

You'll be able to use methods like on this type.
There is an example:
```
 Fs  *file = new(File, "./file");
 
 file->isDirectory(file); // return true if the file is a directory
 file->appendFile(file, "Hello World !"); // write 'Hello World !' at this end of the file
```

Remember there is many fs like function in this module but not full fs methods. And there is few new methods which was not on fs usefull.

Minimal doc is provide in `Fs.h`.
