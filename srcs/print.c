#include "../twenty.h"

void    print_here(t_froz *fz)
{
    printf("======PRINT_HEREDOC===========\n");
    while(fz->here->prev != NULL)
        fz->here = fz->here->prev;
    while(fz->here->next != NULL)
    {
        printf("[%s][%s]\n", fz->here->doc,fz->here->delim);
        fz->here = fz->here->next;
    }
    printf("[%s][%s]\n", fz->here->doc,fz->here->delim);
}