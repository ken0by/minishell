/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:44:42 by dmonjas-          #+#    #+#             */
/*   Updated: 2024/01/11 17:53:25 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*-----LIBRERIAS-----*/

# include <libft.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <limits.h>
# include <signal.h>
# include <stdbool.h>
# include <pwd.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>

/*-----COLORES-----*/

# define RED     "\x1b[31m"
# define GREEN   "\033[32m"
# define RESET   "\x1b[0m"

/*-----VARIABLE GLOBAL-----*/
int	code_error;

/*-----ESTRUCTURAS-----*/

typedef struct s_minishell
{
	int		shlvl;
	char	*cmd_line;
	int		infile;
	int		outfile;
	char	*path;
	char	*pwd;
	char	*oldpwd;
	char	*root;
	char	**env;
}	t_minishell;

typedef struct s_command
{
	char				*command;
	char				*built;
	int					dollar;	//comillas simples
	int					inf;
	int					out;
	char				*infile;
	char				*outfile;
	struct s_command	*next;
}	t_command;

typedef struct s_cmd
{
	char	**argv;
	int		builtin;
	int		exp;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_pipe
{
	char			*argv;
	int				builtin;
	int				exp;
	int				infile;
	int				heredoc;
	int				outfile;
	int				append;
	int				redir;
	struct s_pipe	*prev;
	struct s_pipe	*next;
}			t_pipe;

typedef struct s_signal
{
	struct termios	termios;
}				t_signal;

/* ---------- FUNCIONES X ARVHIVO ---------- */

/* ----- BUILTINS ----- */
/* FT_ECHO.C */
void		ft_echo(t_command *cmd);

/* FT_PRINT.C */
void		ft_print_pwd(t_minishell *shell);
void		ft_print_env(t_minishell *shell);
void		ft_print_ordenv(char **env);

/* FT_EXPORT.C */
void		ft_exist(t_command *cmd, t_minishell *shell);

/* FT_EXUTIL.C */
int			ft_check_var(char *str, char **env);
char		*ft_get_var(char *cmd);
int			ft_strcmp(char *s1, char *s2);

/* FT_EXUTIL2.C */
char		*ft_get_content(char *str, char *var);
int			ft_varct(char *str);
void		ft_alfa(char **env);

/* FT_UNSET.C */
void		ft_unset(t_command *cmd, t_minishell *shell);

/* FT_CD.C */
void		ft_cd(t_command *cmd, t_minishell *shell);

/* ----- PARSE ----- */
/* FT_PARSE.C */
void		ft_check_line(t_minishell *shell);
void		ft_shell_up(t_minishell *shell);
void		ft_shell_down(t_minishell *shell);

/* FT_PARSE2.C */
t_command	*ft_take_cmd(t_command **cmd, char *line, char *cmd_line);

/* FT_PARSE3.C */
t_command	*ft_sust(t_command **cmd, char **env);

/* FT_PARSE4.C */
char		*ft_sust_doll(char *line);

/* FT_PARSE5.C */
char		*ft_built(t_command *cmd);
t_command	*ft_inout(t_command **cmd);

/* FT_PARSE_ERROR.C */
void		ft_error_car(void);
void		ft_error_cmd(void);
void		ft_error_arguments(void);
void		ft_error_path(int i);
void		ft_error_fd(char *var, int fd);

/* ----- PIPE ----- */
/* FT_PIPE.C */
void		ft_pipe(t_pipe *pipe, t_minishell *shell);
int			ft_is_pipe(char *str);
void		ft_ord(t_pipe *pipe, t_minishell *shell);

/* FT_PIPE_UTILS.C */
int			ft_isbuilt(char *cmd);
void		ft_redir(t_pipe *pipe, t_minishell *shell);
int			ft_check_built(char *cmd);
void		ft_free_pipe(t_pipe **pipe);

/* FT_PIPE_UTILS2.C */
int			ft_file(t_pipe *pipe, int x);
int			ft_quotes(char	*cmd);

/* FT_PIPE_UTILS3.C */
int			ft_pipe_system(char **cmd, t_minishell *shell);
int			ft_pipe_built(char *str, char *str1, t_minishell *shell);
void		ft_free_cmd(t_cmd **cmd);
void		ft_del_redir(t_pipe *pipe, t_minishell *shell);

/* FT_PIPE_JOIN.C */
t_pipe		*ft_pjoin(t_pipe **cmd);
t_cmd		*ft_cmdlst_new(char *str);
void		ft_cmdlstadd_back(t_cmd **cmd, t_cmd *new);

/* FT_PLST.C */
void		ft_plstadd_back(t_pipe **lst, t_pipe *new);
t_pipe		*ft_plstnew(char *str);
t_pipe		*ft_plstlast(t_pipe *lst);
int			ft_plstsize(t_pipe *lst);
t_pipe		*ft_plst_first(char *str);

/* ----- SRC ----- */
/* FT_UTILS.C */
char		*ft_env(char **env, char *c);
char		**ft_cpy_env(char **env);
void		ft_exit_code(t_minishell *shell);

/* FT_UTILS_2.C */
int			ft_strchr_out(const char *s, int c);
int			ft_strchr_in(const char *s, int c);
void		ft_lstdel(t_pipe *pipe, t_pipe *del);

/* FT_UTILS3.C */
char		*ft_cp_nb(char *str, int j);

/* FT_ERROR.C */
void		ft_put_msg(char *var, char *s);
void		ft_error(char *str);
void		ft_per(char *var, char *s);
void		ft_free_mtx(char **mtx);
void		ft_error_perror(char *command, char *s);

/* FT_LST.C */
void		ft_lstadd_back_shell(t_command **lst, t_command *new);
t_command	*ft_lstnew_shell(char *str);
t_command	*ft_lstlast_shell(t_command *lst);
int			ft_lstsize_shell(t_command *lst);
t_command	*ft_lst_first(char *str, char c);

/* FT_SIGNAL.C */
void		ft_int(int i);
void		ft_quit(int sig);
void		ft_init_signal(void);
void		ft_signal_dis(void);

/* FT_SYSTEM.C */
void		ft_system(t_command *cmd, t_minishell *shell);
char		*ft_cmdpath(char *cmd, char **env);

/* FT_PATH.C */
char		*ft_cmdpath(char *cmd, char **env);

/* ---------- COLORES ---------- */
# define RED     "\x1b[31m"
# define GREEN   "\033[32m"
# define RESET   "\x1b[0m"

#endif
