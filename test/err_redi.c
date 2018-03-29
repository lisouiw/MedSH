#include "../twenty.h"

void  loop_pipe(char ***cmd)           
{
  int   p[2];
  pid_t pid;
  int   fd_in = 0;

  while (*cmd != NULL)
    {
      pipe(p);
      if ((pid = fork()) == -1)
        {
          exit(EXIT_FAILURE);
        }
      else if (pid == 0)
        {
          printf("fd = %i && p[0] = %i && p[1] = %i\n", fd_in, p[0], p[1]);
          if (strcmp(*cmd[0], "rm") == 0)
          {
            dup2(1, 2);
            close(1);
          }
        dup2(fd_in, 0); //change the input according to the old one 
          if (*(cmd + 1) != NULL)
            dup2(p[1], 1);
          close(p[0]);
          execvp((*cmd)[0], *cmd);
          exit(EXIT_FAILURE);
        }
      else
        {
             if (strcmp(*cmd[0], "rm") == 0)
          {
            dup2(1, 2);
            close(1);
          }
          wait(NULL);
          close(p[1]);
          fd_in = p[0]; //save the input for the next command
          printf("fd = %i && p[0] = %i && p[1] = %i\n=========================\n", fd_in, p[0], p[1]);
          cmd++;
        }
    }
}

int main()
{
  char *ls[] = {"ls","-l",  NULL};
  char *grep[] = {"grep", "a", NULL};
  char *wc[] = {"wc", NULL};
  char *rm[] = {"rm", "dfugfjj", NULL};
  char *cat[] = {"/bin/cat", "-e" , NULL};
  char **cmd[] = {rm,cat, NULL};
  extern char		**environ;

  
  loop_pipe(cmd);
  return (0);
}