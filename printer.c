#include <sys/stat.h> // For stat
#include <stdio.h> // For printf()
#include <stdlib.h> // For exit()
#include <pwd.h> // For getpwuid()
#include <grp.h> // For getgrgid()
#include <time.h> // For ctime*()
#include <string.h> // For strcmp

#include "structures.h"

char isDir(struct stat file) {
    if (S_ISDIR(file.st_mode)) {
        return 'd';
    } else {
        return '-';
    }
}

char isOwnerRead(struct stat file) {
    if (file.st_mode & S_IRUSR) {
        return 'r';
    } else {
        return '-';
    }
}

char isOwnerWrite(struct stat file) {
    if (file.st_mode & S_IWUSR) {
        return 'w';
    } else {
        return '-';
    }
}

char isOwnerExecute(struct stat file) {
    if (file.st_mode & S_IXUSR ) {
        return 'x';
    } else {
        return '-';
    }
}

char isGroupRead(struct stat file) {
    if (file.st_mode & S_IRGRP) {
        return 'r';
    } else {
        return '-';
    }
}

char isGroupWrite(struct stat file) {
    if (file.st_mode &  S_IWGRP) {
        return 'w';
    } else {
        return '-';
    }
}

char isGroupExecute(struct stat file) {
    if (file.st_mode & S_IXGRP) {
        return 'x';
    } else {
        return '-';
    }
}

char isOthersRead(struct stat file) {
    if (file.st_mode & S_IROTH) {
        return 'r';
    } else {
        return '-';
    }
}

char isOthersWrite(struct stat file) {
    if (file.st_mode &  S_IWOTH) {
        return 'w';
    } else {
        return '-';
    }
}

char isOthersExecute(struct stat file) {
    if (file.st_mode & S_IXOTH) {
        return 'x';
    } else {
        return '-';
    }
}

int print(char *dir, Options *options, char *name) {

    // Removing the current directory form output
    if (strcmp(name, ".") == 0) {
        return -1;
    }

    // Removing the parent directory from output
    if (strcmp(name, "..") == 0) {
        return -1;
    }

    // Removing hidden files from output
    if (name[0]=='.') {
        return -1;
    }

    struct stat sb;
    if (lstat(dir, &sb) == -1) {
        perror("lstat");
//        exit(EXIT_FAILURE);
    }

    if (options->i) {
        printf("%7ld ", (long) sb.st_ino);
    }

    if (options->l) {
        // Getting the date/time of the last modification
        // CITATION: https://linux.die.net/man/3/strftime
        char lastModified[200];
        struct tm *tmp;
        tmp = localtime(&sb.st_mtime);
        if (tmp == NULL) {
            perror("localtime");
            exit(EXIT_FAILURE);
        }
        if (strftime(lastModified, sizeof(lastModified), "%b %d %G %H:%M", tmp) == 0) {
            fprintf(stderr, "strftime returned 0");
            exit(EXIT_FAILURE);
        }


        //CITATTION: https://stackoverflow.com/questions/7328327/how-to-get-files-owner-name-in-linux-using-c
        struct passwd *pw = getpwuid(sb.st_uid);
        struct group *gr = getgrgid(sb.st_uid);

            printf("%c%c%c%c%c%c%c%c%c%c ",
                   isDir(sb),
                   isOwnerRead(sb),
                   isOwnerWrite(sb),
                   isOwnerExecute(sb),
                   isGroupRead(sb),
                   isGroupWrite(sb),
                   isGroupExecute(sb),
                   isOthersRead(sb),
                   isOthersWrite(sb),
                   isOthersExecute(sb));
            printf("%ld ", sb.st_nlink);
            printf("%s ", pw->pw_name);
            printf("%s ", gr->gr_name);
            printf("%ld ", sb.st_size);
            printf("%s ", lastModified);


    }

    printf("%s \n", name);
}



