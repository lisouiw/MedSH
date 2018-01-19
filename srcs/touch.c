#include "../twenty.h"

t_edit  *touch(t_edit *ed, t_froz *fz, t_his *hs)
{
    if (fz->buf[1] == 0 && fz->buf[2] == 0)
    {
        if (fz->buf[0] > 0 && fz->buf[0] < 27)
            ed = ctrl_touch(ed, fz, fz->buf[0], hs);
        else if (fz->buf[0] == 127)
        {
            ed = erase_ed(ed);
            fz->nb[0] = fz->nb[0] - 1;
            if (ed->rpz[0] == 1 && ed->rpz[1] == 1 && ed->rpz[2] == 3)
                fz->mode[2] = 1;
        }
        else
        {
            ed = add_ed(ed, fz->buf[0], NULL);
            fz->nb[0] = fz->nb[0] + 1;
            fz->mode[2] = 0;
        }
    }
    else
        ed = extern_touch(ed, fz, &hs);
    print_shell(ed, fz);
    return (ed);
}


t_edit  *extern_touch(t_edit *ed, t_froz *fz, t_his **hs)
{
    while (ed->rpz[2] == 0) //se mettre au nv cursor
        ed = ed->next;
    if (fz->buf[0] == 27 && fz->buf[1] == 91 && (fz->buf[2] == 68 || fz->buf[2] == 67))  // left/right
        ed = left_right(ed, fz);
    else if (fz->mode[2] == 1 && fz->buf[0] == 27 && fz->buf[1] == 91 && (fz->buf[2] == 65 ||fz->buf[2] == 66)) //historique : haut/bas
        *hs = histo(*hs, fz->buf[0]);

    //27 91 65 haut
    //27 91 66 bas
    return (ed);
}

t_his   *histo(t_his *hs, char c)
{
    if ((c == 65 || c == 66)) //historique : haut/bas
        ;
    return (hs);
}

t_edit  *left_right(t_edit *ed, t_froz *fz)
{
    if (fz->buf[2] == 68 && ed->rpz[0] == 0)  // left
    {
        ed->prev->rpz[2] = ed->rpz[2] - 1;
        ed->rpz[2] = 0;
    }
    else if (fz->buf[2] == 67 && ed->next->rpz[0] == 0) //right
    {
        ed->next->rpz[2] = ed->rpz[2] + 1;   
        ed->rpz[2] = 0;
    }
    return(ed);
}