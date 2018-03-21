#include "../twenty.h"

t_cmd   *parse_redirec(t_cmd *ex, char *s)
{
    char    *tmp1;
    char    *tmp2;
    t_cmd   *tmp;

    // printf("===========REDIRECTION==========\n");
    // print_ex_up(ex);
    
    if (ex->prev->cmd != NULL && ex->prev != NULL && isnumber(ex->prev->cmd) && s[ex->start -1] != ' ')
    {
        tmp = ex->prev;
        tmp1 = ft_strjoin(" ", ex->cmd);
        tmp2 = ft_strjoin(ex->prev->cmd, tmp1);
        free(ex->cmd);
        ex->cmd = tmp2;
        ex->prev->prev->next = ex;
        ex->prev = ex->prev->prev;
        free(tmp1);
        free(tmp->cmd);
        free(tmp);
    }
    if (ex->next != NULL && ex->next->type != 42 && ex->next->type == 0)
    {
        tmp1 = ft_strjoin(" " , ex->next->cmd);
        tmp2 = ft_strjoin(ex->cmd, tmp1);
        free(tmp1);
        free(ex->cmd);
        ex->cmd = tmp2;
    }
    // print_ex(ex);
    return (ex);
}

t_cmd   *parse_ampersand(t_cmd *ex)
{
    if (ft_strcmp(ex->cmd, "&&") == 0)
        ex->type = 4;
    else
        ex->type = -1;    
    return (ex);
}

t_cmd   *parse_great_than(t_cmd *ex, char *s)
{
    if (ft_strcmp(ex->cmd, ">") == 0)
    {
        ex->type = 8;
        ex = parse_redirec(ex, s);
    }
    else if (ft_strcmp(ex->cmd, ">>") == 0)
    {
        ex->type = 9; 
        ex = parse_redirec(ex, s);
    }
    else if (ft_strcmp(ex->cmd, ">&") == 0 )
    {
        ex->type = 10;        
        ex = parse_redirec(ex, s);
    }
    else
        ex->type = -1;    
    return (ex);
}

t_cmd   *parse_less_than(t_cmd *ex, char *s)
{
    if (ft_strcmp(ex->cmd, "<") == 0)
    {
        ex->type = 7;
        ex = parse_redirec(ex, s);
    }
    else if (ft_strcmp(ex->cmd, "<<") == 0)
    {
        ex->type = 6;        
        ex = parse_redirec(ex, s);
    }
    else if (ft_strcmp(ex->cmd, "<&") == 0 )
    {
        ex->type = 11;        
        ex = parse_redirec(ex, s);
    }
    else
        ex->type = -1;    
    return (ex);
}

t_cmd   *parse_pipe_or(t_cmd *ex)
{
    if (ft_strcmp(ex->cmd, "|") == 0) // prompt
        ex->type = 3;
    else if (ft_strcmp(ex->cmd, "||") == 0) // prompt
        ex->type = 5;
    else
        ex->type = -1;
    return (ex);
}