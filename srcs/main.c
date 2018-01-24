#include "../twenty.h"

int         main(void)
{
    t_froz  *fz;
    t_env   *env;
    t_edit  *ed;
    t_his   *hs;

    g_nb = init_shell(&fz, &env, &ed, &hs);
    while (42)
    {
        read(0, &fz->buf, 4);
        // printf("%i %i %i\n", fz->buf[0], fz->buf[1], fz->buf[2]);
        // exit(0);
        if (fz->buf[0] == 10)
        {
            cursor_end(ed);
            env = treat_cmd(env, &ed, &hs, &fz);
            init_for_new(&hs, &fz, &ed);
        }
        else
            ed = touch(ed, &fz, &hs);
        init_data(&fz);
    }
}

void    cursor_end(t_edit *ed)
{
    int     i;
    
    tputs(tgetstr("rc", NULL), 0, ft_put);
    while (ed->rpz[1] == 0)
        ed = ed->next;
    i = ed->rpz[3];
    if (i % g_nb->tb[0] == 1)
	    ft_putstr(ft_strjoin("\033[", ft_strjoin(ft_itoa(g_nb->tb[0]), "D")));
    else
	    ft_putstr(ft_strjoin("\033[", ft_strjoin(ft_itoa(g_nb->tb[0]), "C")));
	if (i > g_nb->tb[0] && i % g_nb->tb[0] == 0)
		ft_putstr(ft_strjoin("\033[", ft_strjoin(ft_itoa((i / g_nb->tb[0]) - 1),"B")));
	else if (i > (g_nb->tb[0]))
		ft_putstr(ft_strjoin("\033[", ft_strjoin(ft_itoa((i / g_nb->tb[0])),"B")));
}