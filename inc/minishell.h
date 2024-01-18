/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:44:42 by dmonjas-          #+#    #+#             */
/*   Updated: 2024/01/18 13:09:43 by rofuente         ###   ########.fr       */
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
	int		infile;
	int		outfile;
	int		heredoc;
	char	*cmd_line;
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

typedef struct s_signal
{
	struct termios	termios;
}				t_signal;

/* ---------- FUNCIONES X ARVHIVO ---------- */

/* ----- BUILTINS ----- */
/* FT_ECHO.C */
void		ft_echo(char *cmd, int fd);

/* FT_PRINT.C */
void		ft_print_pwd(t_minishell *shell, int fd);
void		ft_print_env(t_minishell *shell, int fd);
void		ft_print_ordenv(char **env, int fd);

/* FT_EXPORT.C */
void		ft_exist(char *cmd, t_minishell *shell, int fd);

/* FT_EXUTIL.C */
int			ft_check_var(char *str, char **env);
char		*ft_get_var(char *cmd);
int			ft_strcmp(char *s1, char *s2);

/* FT_EXUTIL2.C */
char		*ft_get_content(char *str, char *var);
int			ft_varct(char *str);
void		ft_alfa(char **env, int fd);

/* FT_UNSET.C */
void		ft_unset(char *cmd, t_minishell *shell);

/* FT_CD.C */
void		ft_cd(char *cmd, t_minishell *shell);

/* ----- PARSE ----- */
/* FT_PARSE.C */
void		ft_check_line(t_command *cmd, t_minishell *shell);
void		ft_shell_up(t_minishell *shell);
void		ft_shell_down(t_minishell *shell);
char		*ft_spr(char *line);

/* FT_PARSE2.C */
t_command	*ft_take_cmd(t_command **cmd, char *line, char *cmd_line);

/* FT_PARSE3.C */
t_command	*ft_sust(t_command **cmd, char **env);

/* FT_PARSE4.C */
char		*ft_sust_doll(char *line);
int			ft_inf(char *infile, int x, t_minishell *shell);

/* FT_PARSE5.C */
char		*ft_built(t_command *cmd);
t_command	*ft_inout(t_command **cmd, t_minishell *shell);

/* FT_PARSE6.C */
void		ft_swap(t_command *cmd);
char		*ft_take_size(char *cmd);
//void		ft_exec_heredoc(char **cmd, t_minishell *shell);

/* FT_PARSE_ERROR.C */
void		ft_error_car(void);
void		ft_error_cmd(void);
void		ft_error_arguments(void);
void		ft_error_path(int i);
void		ft_error_fd(char *var, int fd);

/* ----- PIPE ----- */
/* FT_PIPE.C */
void		ft_ord(t_command *cmd, t_minishell *shell);
int			ft_check_in(t_minishell *shell);
int			ft_check_out(t_minishell *shell);

/* FT_PIPE_UTILS.C */
void		ft_free_cmd(t_command **cmd);
void		ft_peror(char *var, char *s);

/* ----- SRC ----- */
/* FT_UTILS.C */
char		*ft_env(char **env, char *c);
char		**ft_cpy_env(char **env);
char		*ft_skip_space(char *cmd);
int			ft_space(char *line, int i);

/* FT_UTILS_2.C */
int			ft_strchr_out(const char *s, int c);
int			ft_strchr_in(const char *s, int c);
char		*ft_cp_nb(char *str, int j);
void		ft_err_msg(char *s);
void		ft_per_nb(char *s, int nb);

/* FT_EXIT.C */
void		ft_exit_code(t_minishell *shell);

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
void		ft_system(t_command *cmd, t_minishell *shell, int fdin, int fdout);
void		ft_exec(char **cmd, t_minishell *shell, int fdin, int fdout);
char		*ft_cmdpath(char *cmd, char **env);
int			ft_cw(int fdout, pid_t pd);

/* FT_PATH.C */
char		*ft_cmdpath(char *cmd, char **env);

/* ---------- COLORES ---------- */
# define RED     "\x1b[31m"
# define GREEN   "\033[32m"
# define RESET   "\x1b[0m"

#endif
