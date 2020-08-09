#include <sys/stat.h> // For stat
#include <stdio.h> // For printf()
#include <stdlib.h> // For exit()
#include <pwd.h> // For getpwuid()
#include <grp.h> // For getgrgid()
#include <time.h> // For ctime*()
#include <string.h> // For strcmp
#include <unistd.h> // For readlink

#include "arguements.h"
#include "printer.h"

// Function accepts a string and returns true of it needs to be contained in quotes, else returns false
bool quotesNeeded(char *name) {
    char *s = NULL;
    if ((s = strchr(name, ' ')) != NULL) {
        return true;
    } else if ((s = strchr(name, '!')) != NULL) {
        return true;
    } else if ((s = strchr(name, '$')) != NULL) {
        return true;
    } else if ((s = strchr(name, '\'')) != NULL) {
        return true;
    } else if ((s = strchr(name, '^')) != NULL) {
        return true;
    } else if ((s = strchr(name, '&')) != NULL) {
        return true;
    } else if ((s = strchr(name, '(')) != NULL) {
        return true;
    } else if ((s = strchr(name, ')')) != NULL) {
        return true;
    } else {
        return false;
    }
}

// Function accepts an int, and returns the number of digits in the int
static int getNumberDigits(int num) {
    int temp = num;
    int numDigits = 0;
    while (temp != 0) {
        temp = temp / 10;
        numDigits++;
    }
    return numDigits;
}

// Function accepts a dir, options and size struct, and changes the values in the sizes struct if the lstat values for dir have longer length
void getSizes(char *dir,Options *options,Sizes * sizes) {
    struct stat sb;
    if (lstat(dir, &sb) == -1) {
        perror("lstat");
    }

    if (options->i) {
        int inodeLength = 0;
        if ((inodeLength = getNumberDigits(sb.st_ino)) > sizes->inodeLength) {
            sizes->inodeLength = inodeLength;
        }
    }

    if (options->l) {
        int length = 0;

        struct passwd *pw = getpwuid(sb.st_uid);
        struct group *gr = getgrgid(sb.st_uid);

        if ((length = getNumberDigits(sb.st_nlink)) > sizes->linksLength) {
            sizes->linksLength = length;
            length = 0;
        }

        if ((length = strlen(pw->pw_name)) > sizes->userLength) {
            sizes->userLength = length;
            length = 0;
        }

        if ((length = strlen(gr->gr_name)) > sizes->groupLength) {
            sizes->groupLength = length;
            length = 0;
        }

        if ((length = getNumberDigits(sb.st_size)) > sizes->sizeLength) {
            sizes->sizeLength = length;
        }

        if (quotesNeeded(dir)) {
            sizes->extraNameSpace = true;
        }
    }
}

// Function accepts a stat object and prints out the date time in the required format
static void dateTime(struct stat sb) {
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

    // Printing the month and a space
    for (int i = 0; i < 4; ++i) {
        printf("%c", lastModified[i]);
    }

    // Printing the day of the month, with a space if it is less than needed
    if (tmp->tm_mday < 10) {
        printf(" %d", tmp->tm_mday);
    } else {
        printf("%d", tmp->tm_mday);
    }

    // Printing the rest, (i.e. year and time)
    for (int i = 6; i < strlen(lastModified); ++i) {
        printf("%c", lastModified[i]);
    }

}

static char isDir(struct stat file) {
    if (S_ISDIR(file.st_mode)) {
        return 'd';
    } else if (S_ISLNK(file.st_mode)) {
        return 'l';
    } else {
        return '-';
    }
}

static char isOwnerRead(struct stat file) {
    if (file.st_mode & S_IRUSR) {
        return 'r';
    } else {
        return '-';
    }
}

static char isOwnerWrite(struct stat file) {
    if (file.st_mode & S_IWUSR) {
        return 'w';
    } else {
        return '-';
    }
}

static char isOwnerExecute(struct stat file) {
    if (file.st_mode & S_IXUSR ) {
        return 'x';
    } else {
        return '-';
    }
}

static char isGroupRead(struct stat file) {
    if (file.st_mode & S_IRGRP) {
        return 'r';
    } else {
        return '-';
    }
}

static char isGroupWrite(struct stat file) {
    if (file.st_mode &  S_IWGRP) {
        return 'w';
    } else {
        return '-';
    }
}

static char isGroupExecute(struct stat file) {
    if (file.st_mode & S_IXGRP) {
        return 'x';
    } else {
        return '-';
    }
}

static char isOthersRead(struct stat file) {
    if (file.st_mode & S_IROTH) {
        return 'r';
    } else {
        return '-';
    }
}

static char isOthersWrite(struct stat file) {
    if (file.st_mode &  S_IWOTH) {
        return 'w';
    } else {
        return '-';
    }
}

static char isOthersExecute(struct stat file) {
    if (file.st_mode & S_IXOTH) {
        return 'x';
    } else {
        return '-';
    }
}

int print(char *dir, Options *options, char *name, Sizes *sizes) {
    struct stat sb;
    if (lstat(dir, &sb) == -1) {
        perror("lstat");
        return -1;
//        exit(EXIT_FAILURE);
    }

    if (options->i) {
        if (sizes->inodeLength != -1) {
            printf("%*ld ", sizes->inodeLength,(long) sb.st_ino);
        } else {
            printf("%ld ", (long) sb.st_ino);
        }
    }

    if (options->l) {

        //CITATTION: https://stackoverflow.com/questions/7328327/how-to-get-files-owner-name-in-linux-using-c
        struct passwd *pw = getpwuid(sb.st_uid);
        struct group *gr = getgrgid(sb.st_gid);

        // Printing all the various permissions
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

        // Printing the number of links
        if (sizes->linksLength != -1) {
            printf("%*ld ", sizes->linksLength,sb.st_nlink);
        } else {
            printf("%ld ", sb.st_nlink);
        }

        // Printing the username
        if (sizes->userLength != -1) {
            printf("%*s ", sizes->userLength,pw->pw_name);
        } else {
            printf("%s ", pw->pw_name);
        }

        // Printing the group name
        if (sizes->groupLength != -1) {
            printf("%*s ",sizes->groupLength, gr->gr_name);
        } else {
            printf("%s ", gr->gr_name);
        }

        // Printing the file size
        if (sizes->sizeLength != -1) {
            printf("%*ld ", sizes->sizeLength,sb.st_size);
        } else {
            printf("%ld ", sb.st_size);
        }

        // Printing the date
        // The if statements here are to account for any extra spaces needed between the date and the file name.  This is done to reflect
        // the exact spacing of ls
        if (quotesNeeded(dir) && sizes->extraNameSpace) {
            dateTime(sb);
            printf(" ");
        } else if (sizes->extraNameSpace) {
            dateTime(sb);
            printf("  ");
        } else {
            dateTime(sb);
            printf(" ");
        }



    }

    // Printing the file name
    // Checking if the file is a soft link
    if (S_ISLNK(sb.st_mode) && options->l) {
        char buf[1024];
        int len;
        if ((len = readlink(dir, buf, sizeof(buf)-1)) != -1) {
            buf[len] = '\0';
        }
        if (quotesNeeded(name) && quotesNeeded(buf)) {
            printf("\'%s\' -> \'%s\'\n", name, buf);
        } else if (quotesNeeded(name)) {
            printf("\'%s\' -> %s\n", name, buf);
        } else if (quotesNeeded(buf)){
            printf("%s -> \'%s\'\n", name, buf);
        } else {
            printf("%s -> %s\n", name, buf);
        }

    } else {
        if (quotesNeeded(name)) {
            printf("\'%s\' \n", name);
        } else {
            printf("%s \n", name);
        }

    }

}



