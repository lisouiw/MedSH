#include "../twenty.h"

int     error_syntax(t_froz *fz)
{
    if (fz->mode[3] == -1 || fz->mode[3] == -2  || (fz->mode[3] <= -6 && fz->mode[3] >= -11))
        ft_putendl_fd("sh: parse error near `\\n'", 2);
    else if (fz->mode[3] == -20)
        ft_putendl_fd("sh: parse error near `&'", 2);
    else if (fz->mode[3] == -3)
        ft_putendl_fd("sh: parse error near `|'", 2);
    else if (fz->mode[3] == -4)
        ft_putendl_fd("sh: parse error near `&&'", 2);
    else if (fz->mode[3] == -5)
        ft_putendl_fd("sh: parse error near `||'", 2);
    else if (fz->mode[3] == -13)
        ft_putendl_fd("sh: parse error near `;'", 2);
    else
        printf("ERROR %i\n", fz->mode[3]);
    fz->mode[3] = 0;
    return (0);
}