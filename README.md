# Replication of Linux List

This repository contains a simple replication of linux's list command ls.  This replication is not complete and only conatins a specific subset of ls's abilities.

## Sample Commands

"i" indicates the inode number should be listed
"l" indicates all file/folder information should be listed
"r" indicates all file/folders should be listed recursively

To indicate what should be printed, the structure is as follows:

./myls -<Command 1, featuring i,l, or r in any order> -<Command 2 featuring i,l, or r in any order> ... -<Command n, featuring i,l, or r in any order> <fileName 1> <fileName 2> ... <fileName n>

```
./myls -ilr .
```

```
./myls -il ..
```

```
./myls *
```