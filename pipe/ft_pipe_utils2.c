/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:05:35 by rofuente          #+#    #+#             */
/*   Updated: 2024/03/06 16:07:00 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static pid_t	ft_single(char **cmd, t_minishell *shell, int fdin, int fdout)
{
	char	*path;
	pid_t	pd;

	pd = fork();
	path = NULL;
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
		ft_dupfd(fdin, fdout);
		if (execve(path, cmd, shell->env) == -1)
			ft_peror(cmd[0], "");
	}
	close(fdin);
	free (path);
	return (pd);
}

pid_t	ft_order_single(char *cmd, t_minishell *shell, int fdin, int fdout)
{
	char	**command;
	pid_t	pd;

	pd = -1;
	command = ft_split(cmd, ' ');
	if (!ft_strncmp(command[0], "echo", ft_strlen(command[0])))
		ft_echo(cmd, fdout);
	else if (!ft_strncmp(command[0], "cd", ft_strlen(command[0])))
		ft_cd(cmd, shell);
	else if (!ft_strncmp(command[0], "pwd", ft_strlen(command[0])))
		ft_print_pwd(shell, fdout);
	else if (!ft_strncmp(command[0], "export", ft_strlen(command[0])))
		ft_exist(cmd, shell, fdout);
	else if (!ft_strncmp(command[0], "unset", ft_strlen(command[0])))
		ft_unset(cmd, shell);
	else if (!ft_strncmp(command[0], "env", ft_strlen(command[0])))
		ft_print_env(shell, fdout);
	else
		pd = ft_single(command, shell, fdin, fdout);
	ft_free_mtx(command);
	if (pd != -1)
		return (pd);
	return (-1);
}

void	ft_close(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
}
