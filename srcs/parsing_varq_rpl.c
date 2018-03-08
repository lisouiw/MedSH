#include "../twenty.h"

int     move_to_put_varq(char *s, int i, int o)
{
    if (o == '$')
    {
        if (s[i + 1] == '$')
        {
            while (s[++i] && s[i] == '$')
                ;
            if (s[i + 1] != ' ' || s[i + 1] != '\0')
                --i;
        }
        else
            while (s[++i] && s[i] != ' ' && s[i] != '$')
                ;
    }
    else
    {
        while (s[++i] && s[i] != o)
            ;
        ++i;
    }
    return (i);
}

char    *change_w_varq(char *s, t_varq *v)
{
    int     i;
    int     in;
    char    *nw;

    i = 0;
    nw = NULL;
                
    // printf("=============================\n");    
    while (s[i])
    {
        in = i;
        if (s[i] && (s[i] != '$' && s[i] != 34 && s[i] != 39))
        {
            while (s[i] && s[i] != '$' && s[i] != 34 && s[i] != 39)
                    ++i;
            if (i - in == 0)
            {
                nw = strjoin_free(ft_strsub(s, i, 1), nw, 3);
                ++i;
            }
            else        
                nw = strjoin_free(ft_strsub(s, in, i - in), nw, 3);
                // printf("%s\n", nw);
        }
        if (s[i] && (s[i] == '$' || s[i] == 34 || s[i] == 39))
        {
            in = i;
            i = move_to_put_varq(s, i, s[i]);
            nw = strjoin_free(ft_strdup(v->cmd), nw, 3);
            if (v->next != NULL)
                v = v->next;
            // printf("%s=====%s\n", nw, &s[i]);
        }
    }
    return (nw);
}