#include "../twenty.h"

//LEKS AU NIVEAU DU STUCT HEREDOC

void    free_ex(t_cmd **ex)
{
    if (*ex != NULL)
        free(*ex);
    return;
}

void    free_all_ex(t_cmd **ex)
{
    t_cmd   *tmp;

    while ((*ex)->next != NULL)
        *ex = (*ex)->next;
    while ((*ex)->prev != NULL)
    {
        tmp = (*ex)->prev;
        free((*ex)->cmd);
        free(*ex);
        *ex = tmp;
    
    }
    free((*ex)->cmd);
    free(*ex);
}

void    free_init_fz(t_froz *fz)
{
    fz->mode[0] = 0;
    fz->mode[1] = 0;
    fz->mode[2] = 1;
    if (fz->mode[3] == 0)
    {
        free(fz->cmd);
        fz->cmd = NULL;
        while (fz->here->prev != NULL)
            fz->here = fz->here->prev;
        while (fz->here->next != NULL)
        {
            if (fz->here->delim)
                free(fz->here->delim);
            if (fz->here->doc)
                free(fz->here->doc);
            fz->here = fz->here->next;
            free(fz->here->prev);
            fz->here->prev = NULL;
        }
        fz->here->ok[0] = 0;
        fz->here->doc = NULL;
        fz->here->delim = NULL;
    }
}

void    free_for_exit(void)
{
    while (hs->prev != NULL)
        hs = hs->prev;
    while (hs->next != NULL)
    {
        free(hs->cmd);
        hs = hs->next;
        free(hs->prev);
    }
    free(hs);
    
    if (fz->cmd)
        free(fz->cmd);
    if (fz->paste)
        free(fz->paste);
    while (fz->here->prev != NULL)
        fz->here = fz->here->prev;
    while (fz->here->next != NULL)
    {
        if (fz->here->delim)
            free(fz->here->delim);
        if (fz->here->doc)
            free(fz->here->doc);
        fz->here = fz->here->next;
        free(fz->here->prev);
        fz->here->prev = NULL;
    }
    free(fz->here);
    free(fz);
	exit(-1);
    // free_init_fz(fz);
}