#include "../twenty.h"

int         main(void)
{
    t_froz  *fz;
    t_env   *env;
    t_edit  *ed;
    t_his   *hs;

    ls_signal();
    g_nb = init_shell(&fz, &env, &ed, &hs);
    while (42)
    {
        read(0, &fz->buf, 4);
        // printf("%i %i %i\n", fz->buf[0], fz->buf[1], fz->buf[2]);
        // exit(0);
        if (fz->buf[0] == 10)//touch enter
        {
            cursor_end(ed);                             //remettre le curseur a la fin pour les calculs
            env = treat_cmd(env, &ed, &hs, &fz);        //traiter la cmd
            init_for_new(&hs, &fz, &ed);                // init ed et mettre le prompt approprie
        }
        else if (fz->buf[0] == 3)                       //ctrl-C rendre le prompt
        {
            write(1, "\n", 1);
            init_for_new(&hs, &fz, &ed);                // init ed et mettre le prompt approprie        
        }
        else
            ed = touch(&ed, &fz, &hs);                  //add les touch -> ed
        init_data(&fz);
    }
}

void    cursor_end(t_edit *ed)               //remettre le curseur a la fin pour les calculs       
{
    int     i;
    
    tputs(tgetstr("rc", NULL), 0, ft_put);
    while (ed->rpz[1] == 0)
        ed = ed->next;
    i = ed->rpz[3];
    if (i % g_nb->tb[0] == 1)
        put_my_cur(g_nb->tb[0], 'D');
    else
        put_my_cur(g_nb->tb[0], 'C');
    if (i > g_nb->tb[0] && i % g_nb->tb[0] == 0)
        put_my_cur(((i / g_nb->tb[0]) - 1), 'B');
    else if (i > (g_nb->tb[0]))
        put_my_cur((i / g_nb->tb[0]), 'B');
    init();
        
}

void    put_my_cur(int nb, char c)
{
    char    *i;

    i = ft_itoa(nb);
    ft_putstr("\033[");
    ft_putstr(i);
    ft_putchar(c);
    free(i);
}