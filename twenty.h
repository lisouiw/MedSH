#ifndef TWENTY_H
# define TWENTY_H

# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <sys/ioctl.h>

///GLOBALE

struct termios		term;

typedef struct		s_num
{
	int				tb[3];
}					t_num;
t_num	*g_nb;

t_num	*g_nb;


///

typedef struct      s_froz
{
    int             mode[3];
    //mode 0        copier
    //mode 1        couper
    //mode 2        mode historique  
    char            buf[3]; // buffer pour lire le char tape
    char            *paste; // la chaine a coller
    char            *cmd; // keep cmd car imcomplete
    int             nb[1]; // last position
}                   t_froz;

typedef struct		s_env
{
	char			*name;
	char			*ctn;
	struct s_env	*next;
}					t_env;

typedef struct      s_edit
{
    int             rpz[5];
    // 0: debut list
    // 1: fin list
    // 2: cursor position
    // 3: 
    // 4: 
    char            c[1];
    struct  s_edit  *next;
    struct  s_edit  *prev;
}                   t_edit;

typedef struct      s_his
{
    char            *cmd;
    // struct  t_edit  *ed;
    struct  s_his   *next;
    struct  s_his   *prev;
}                   t_his;    

// main
t_num   *init_shell(t_froz **fz, t_env **env, t_edit **ed, t_his **hs);
t_froz      *init_fz(t_froz *fz);
void    init_data(t_froz **fz);
void    cursor_end(t_froz *fz);
void    init_for_new(t_his **hs, t_froz **fz);
void    free_ed(t_edit **ed);


// term
int		init(void);
int		set_up_term(void);

//env
void	free_elem(t_env *tmp);
void	b_export(char *cut, t_env **env);
void	b_unset(char **cut, t_env **env, int i);
t_env	*add_env(char *environ, t_env *env, size_t one, size_t all);
t_env	*give_env(t_env *env);

//ed
void    modif_edit(t_edit **ed, t_edit **nw);
t_edit  *add_ed(t_edit *ed, char c, t_edit *nw);
t_edit  *init_edit(t_edit *init);
t_edit  *erase_ed(t_edit *ed);

//touch
t_edit  *touch(t_edit *ed, t_froz **fz, t_his **hs);
t_edit  *extern_touch(t_edit *ed, t_froz **fz, t_his **hs);
t_edit  *left_right(t_edit *ed, t_froz *fz);
// t_his   *histo(t_his *hs, char c);
int     the_same(t_edit *ed, t_his *hs);
t_his   *histo(t_his *hs, char c, t_edit **ed, t_froz **fz);

//print_shell
int		ft_put(int c);
void	my_tputs(t_edit *ed);
void	put_cursor(t_edit *ed);
void	save_init(t_froz *fz);
void    print_shell(t_edit *ed, t_froz *fz);

// treatmt
t_env   *treat_cmd(t_env *env, t_edit **cmd, t_his **hs, t_froz *fz);
t_env   *launchcmd(t_his **cmd, t_env *env);
// t_his   *add_his(t_edit *cmd, t_his *hs, t_his *nw, t_froz *fz);
t_env	*exec_giv(char *line, t_env *env, char **cut, int *i);
int     add_his(t_edit *cmd, t_his **hs, t_his *nw, t_froz *fz);


//t 
void	free_list(t_env **env);
char	*t_strjoin(char *f, char *s, char *t);
void	free_tab(char **array);
int		free_for_exit(char *line, char **cut, t_env *env);

//
int		give_path(t_env *env, char **cut, int i, char **tab_env);
char	**list_to_tab(t_env *env, char **tab_env);
void	b_other(char **cut, t_env *env);
void	print_tab(char **ta, int i);

//ctrl 
void    ctrl_de_test(t_edit *ed, t_froz *fz, char c, t_his *hs);
t_edit  *ctrl_touch(t_edit *ed, t_froz *fz, char c, t_his *hs);
t_edit  *move_word(t_edit *ed, char c);
t_edit  *up_down(t_edit *ed, char c);
t_edit  *home_end(t_edit *ed, char c);

//tools
int     if_only(char *s, char c);




#endif
