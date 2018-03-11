// myls.c ..MAXFNAME. my very own "ls" implementation

#include <stdlib.h>
#include <stdio.h>
#include <bsd/string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAXDIRNAME 100
#define MAXFNAME   200
#define MAXNAME    20

char *rwxmode(mode_t, char *);
char *username(uid_t, char *);
char *groupname(gid_t, char *);

int main(int argc, char *argv[])
{
   // string buffers for various names
   char dirname[MAXDIRNAME];
    char uname[MAXNAME+1]; // UNCOMMENT this line
    char gname[MAXNAME+1]; // UNCOMMENT this line
    char mode[MAXNAME+1]; // UNCOMMENT this line

   // collect the directory name, with "." as default
   if (argc < 2)
      strlcpy(dirname, ".", MAXDIRNAME);
   else
      strlcpy(dirname, argv[1], MAXDIRNAME);

   // check that the name really is a directory
   struct stat info;
   if (stat(dirname, &info) < 0)
      { perror(argv[0]); exit(EXIT_FAILURE); }
   if ((info.st_mode & S_IFMT) != S_IFDIR)
      { fprintf(stderr, "%s: Not a directory\n",argv[0]); exit(EXIT_FAILURE); }

   // open the directory to start reading
    DIR *df;
	df = opendir(dirname);  //open the directory
   // ... TODO ...

   // read directory entries
    struct dirent *entry;
    struct stat sp;// ... TODO ...
    char fp[MAXFNAME];

	while((entry=readdir(df)) != NULL){
	snprintf(fp, MAXFNAME, "%s/%s", dirname, entry->d_name);
		lstat(fp,&sp);
        char type[1] = {0};
        if(entry->d_name[0]=='.')continue;    
        switch (sp.st_mode & S_IFMT){
            case S_IFDIR: type[0] = 'd';                        break;
            case S_IFREG: type[0] = '-';                        break;
            case S_IFLNK: type[0] = 'l';                        break;      
            default: type[0] = '?';                             break;
        }
		printf("%c%s   %-8.8s %-8.8s %8lld %s\n",type[0],rwxmode(sp.st_mode, mode),username(sp.st_uid,uname),groupname(sp.st_gid, gname), (long long)sp.st_size, entry->d_name);
	}
   // finish up
    closedir(df);opendir
   return EXIT_SUCCESS;
}

// convert octal mode to -rwxrwxrwx string
char *rwxmode(mode_t mode, char *str)
{
    str[0] = mode & S_IRUSR ? 'r' : '-';
    str[1] = mode & S_IWUSR ? 'w' : '-';
    str[2] = mode & S_IXUSR ? 'x' : '-';
    str[3] = mode & S_IRGRP ? 'r' : '-';
    str[4] = mode & S_IWGRP ? 'w' : '-';
    str[5] = mode & S_IXGRP ? 'x' : '-';
    str[6] = mode & S_IROTH ? 'r' : '-';
    str[7] = mode & S_IWOTH ? 'w' : '-';
    str[8] = mode & S_IXOTH ? 'x' : '-';
    str[9] = ' ';
    str[10] = '\0';
    return str;
}

// convert user id to user name
char *username(uid_t uid, char *name)
{
   struct passwd *uinfo = getpwuid(uid);
   if (uinfo == NULL)
      snprintf(name, MAXNAME, "%d?", (int)uid);
   else
      snprintf(name, MAXNAME, "%s", uinfo->pw_name);
   return name;
}

// convert group id to group name
char *groupname(gid_t gid, char *name)
{
   struct group *ginfo = getgrgid(gid);
   if (ginfo == NULL)
      snprintf(name, MAXNAME, "%d?", (int)gid);
   else
      snprintf(name, MAXNAME, "%s", ginfo->gr_name);
   return name;
}
