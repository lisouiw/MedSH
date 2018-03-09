#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/wait.h>

int   p[2];
int pid;
int r;

int main()
{
        char *ls_args[] = {"ls", NULL};
        char *grep_args[] = {"grep", "a", NULL};
        int fd;

         pid = fork();
         if (pid  != 0)
        {
            // Parent: Output is to child via pipe[1]
            // Change stdout to pipe[1]
        fd = open("mom" , O_RDONLY); 
        dup2(0, fd);
        r = execvp("echo", ls_args);
        }
        else
                kill(wait(NULL), 0);
    return r;
}