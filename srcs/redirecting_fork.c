#include "../twenty.h"

void    redirection_f(t_cmd **ex, t_env **env, t_exec *s)
{
    *ex = (*ex)->next;
    if ((*ex)->type == 7)
        redirecting_in(&(*ex), &(*env), 0);
    if ((*env)->name || s)
        ;
    
}

int     redirection_file_check(char ***arr, t_cmd *ex, int nw)
{
    char    **pute;

    *arr = ft_strsplit((ex)->cmd, ' ');
    while (nw != -1 && (ex)->type == 7)
    {
        pute = ft_strsplit((ex)->cmd, ' ');
        nw = (pute[2] == NULL) ? open(pute[1], O_RDONLY) : open(pute[2], O_RDONLY);
        if ((ex)->next->type == 7)
            close(nw);
        free_tab(pute);
        ex = (ex)->next;
    }
    if (nw == -1)
    {
        free_tab(*arr);
        ft_putstr_fd("error\n", 2);
        exit(0);
    }   
    // print_tab(arr, -1);
    return (nw);
}


void    redirecting_in(t_cmd **ex, t_env **env, int nw)
{
    pid_t       pid;
    char        **arr;
    int         i = 0;

    arr = NULL;
    if ((*ex)->type == 7)
    {    
        if ((pid = fork()) == -1)
            exit(EXIT_FAILURE);
        else if (pid == 0)
        {
            nw = redirection_file_check(&arr, *ex, nw);
            i = dup(0);
            dup2(nw, (arr[2] == NULL ? 0 : ft_atoi(arr[0])));
            close(nw);
            free_tab(arr);
            arr = ft_strsplit((*ex)->prev->cmd, ' ');
            // redirecting_out();
            // dup2(open("coucou", O_CREAT | O_WRONLY | O_TRUNC, 0644), 1);
            *env = exec_fct_nf(arr, *env);
        }
        else
        {
            kill(wait(NULL), SIGKILL);
            free_tab(arr);
        }
        // dup2(i, 0);
    }
}

// void    redirecting_out(t_cmd **ex, t_env **env, int nw)
// {
//     char       **arr;
//     t_cmd       *tmp;
//     int         i = 0;
 

    // while ((*ex)->type == 7)
        // *ex = (*ex)->next;
//     while (nw != -1 && (ex)->type == 7)
//     {
//         pute = ft_strsplit((ex)->cmd, ' ');
//         nw = (pute[2] == NULL) ? open(pute[1], O_RDONLY) : open(pute[2], O_RDONLY);
//         if ((ex)->next->type == 7)
//             close(nw);
//         free_tab(pute);
//         ex = (ex)->next;
//     }
    // if ((pid = fork()) == -1)
    //     exit(EXIT_FAILURE);
    // else if (pid == 0)
    // {
    //     arr = ft_strsplit((*ex)->cmd, ' ');

    //     nw = (arr[2] == NULL) ? open(arr[1], O_CREAT | O_WRONLY | O_TRUNC, 0644) : open(arr[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    //     i = dup(1);
    //     dup2(nw, (arr[2] == NULL ? 1 : ft_atoi(arr[0])));
    //     tmp = *ex;
    //     free_tab(arr);
    //     while (tmp->prev->type != 0  && tmp->prev->type != 42)
    //         tmp = tmp->prev;
    //     if (wait(0) && tmp->prev->cmd != NULL && (arr = ft_strsplit(tmp->prev->cmd, ' ')))
    //     {
    //        *env = exec_fct_nf(arr, *env);
    //         free_tab(arr);
    //     }
    // }
    // else
    // {
    //     wait(0);
    //     close(nw);
    //     dup2(1, i);
    // }
// }