/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 00:53:20 by rodro             #+#    #+#             */
/*   Updated: 2024/01/10 17:06:32 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_builtin(char *argv)
{
	if (!ft_strncmp(argv, "echo", ft_strlen(argv)))
		return (1);
	if (!ft_strncmp(argv, "cd", ft_strlen(argv)))
		return (1);
	if (!ft_strncmp(argv, "export", ft_strlen(argv)))
		return (1);
	if (!ft_strncmp(argv, "unset", ft_strlen(argv)))
		return (1);
	return (0);
}

/* Da un error al ejecutar cat (cat : Bad address). Creo q es x quitar el infile,
q deberia dejarlo */
int	ft_pipe_system(char **cmd, t_minishell *shell)
{
	pid_t	pd;
	char	*path;
	int		status;

	pd = fork();
	if (pd < 0)
		ft_error("fork() error");
	if (pd == 0)
	{
		path = ft_cmdpath(cmd[0], shell->env);
		if (!path)
		{
			ft_put_msg(cmd[0], "command not found\n");
			code_error = 127;
			return (1);
		}
		else if (execve(path, cmd, shell->env) < 0)
			ft_per(cmd[0], "");
	}
	else
		waitpid(-1, &status, 0);
	code_error = 0;
	return (0);
}

int	ft_pipe_built(char *str, char *str1, t_minishell *shell)
{
	if (ft_builtin(str))
	{
		return (1);
	}
	(void)str;
	(void)str1;
	(void)shell;
	return (0);
}

void	ft_free_cmd(t_cmd **cmd)
{
	t_cmd	*aux;

	while (*cmd)
	{
		aux = (*cmd)->next;
		free (*cmd);
		*cmd = aux;
	}
	cmd = NULL;
}

void	ft_del_redir(t_pipe *pipe, t_minishell *shell)
{
	t_pipe	*aux;

	aux = pipe;
	while (aux)
	{
		if (aux->redir)
		{
			ft_lstdel(pipe, aux);
			aux = pipe;
		}
		aux = aux->next;
	}
	if (!shell->outfile)
		shell->outfile = STDOUT_FILENO;
}
