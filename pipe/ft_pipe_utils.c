/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:05:35 by rodro             #+#    #+#             */
/*   Updated: 2024/01/16 19:37:54 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_peror(char *var, char *s)
{
	ft_putstr_fd(var, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	perror(s);
	code_error = 127;
	exit (1);
}

void	ft_exec(char **cmd, t_minishell *shell, int fdin, int fdout)
{
	char	*path;
	int		status;
	pid_t	pd;

	status = 0;
	pd = fork();
	if (pd == -1)
		ft_error("fork() error");
	if (pd == 0)
	{
		path = ft_cmdpath(cmd[0], shell->env);
		if (!path)
		{
			ft_put_msg(cmd[0], "command not found\n");
			exit (127);
		}
		close(fdin);
		dup2(fdout, STDOUT_FILENO);
		if (execve(path, cmd, shell->env) == -1)
			ft_peror(cmd[0], "");
		close(fdout);
	}
	else
		status = ft_cw(fdout, pd, status);
	code_error = (status >> 8) & 0xFF;
}

void	ft_free_cmd(t_command **cmd)
{
	t_command	*aux;

	while (*cmd)
	{
		aux = (*cmd)->next;
		free (*cmd);
		*cmd = aux;
	}
	cmd = NULL;
}
