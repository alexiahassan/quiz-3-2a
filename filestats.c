#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <pwd.h>
#include <dirent.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Too few arguments\n");
        return 0;
    }


    DIR* d;
    struct dirent* dir;
    d = opendir(argv[1]);
    
    while ((dir = readdir(d)) != NULL) {
        struct stat tempFile;
        printf("File name: %s\n", dir->d_name);
        stat(dir->d_name, &tempFile);
        printf("inode number: %d\n", (int) tempFile.st_ino);
        printf("number of links: %ld\n", (long) tempFile.st_nlink);
        printf("User id of owner: %ld\n", (long) tempFile.st_uid);
        printf("Group id of owner: %ld\n", (long) tempFile.st_gid);
        printf("Size in bytes: %ld\n", (long) tempFile.st_size);

        const time_t* atime = &tempFile.st_atime;
        printf("Last access: %s", ctime(atime));

        const time_t* mtime = &tempFile.st_mtime;
        printf("Last modification: %s", ctime(mtime));

        const time_t* stime = &tempFile.st_ctime;
        printf("Last status change: %s", ctime(stime));

        printf("Number of disk blocks allocated: %ld\n", (long) tempFile.st_blocks);
        //unsigned int mode =  tempFile.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);
        printf("Access mode in octal: %lo\n", (unsigned long) tempFile.st_mode);

        printf("Access mode flags: ");
        printf( (tempFile.st_mode & S_IRUSR) ? "r" : "-");
        printf( (tempFile.st_mode & S_IWUSR) ? "w" : "-");
        printf( (tempFile.st_mode & S_IXUSR) ? "x" : "-");
        printf( (tempFile.st_mode & S_IRGRP) ? "r" : "-");
        printf( (tempFile.st_mode & S_IWGRP) ? "w" : "-");
        printf( (tempFile.st_mode & S_IXGRP) ? "x" : "-");
        printf( (tempFile.st_mode & S_IROTH) ? "r" : "-");
        printf( (tempFile.st_mode & S_IWOTH) ? "w" : "-");
        printf( (tempFile.st_mode & S_IXOTH) ? "x" : "-");
        printf("\n\n");


    }
    closedir(d);
    return 0;

}