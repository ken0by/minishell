/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmonjas- <dmonjas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:24:27 by rodro             #+#    #+#             */
/*   Updated: 2024/03/27 11:35:58 by dmonjas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_cw2(pid_t *pd)
{
	int	status;
	int	i;

	status = 0;
	i = -1;
	while (pd[++i])
		waitpid(pd[i], &status, 0);
	free(pd);
	return (status);
}

pid_t	ft_exec2(char **cmd, t_minishell *shell, int fdin, int *fdout)
{
	char	*path;
	pid_t	pd;

	pd = fork();
	path = NULL;
	if (pd == -1)
		ft_error("fork() error");
	if (pd == 0)
	{
		close(fdout[0]);
		path = ft_cmdpath(cmd[0], shell->env);
		if (!path)
		{
			ft_put_msg(cmd[0], "command not found\n");
			exit (127);
		}
		ft_dupfd(fdin, fdout[1]);
		if (execve(path, cmd, shell->env) == -1)
			ft_peror(cmd[0], "");
	}
	if (path)
		free (path);
	close(fdin);
	return (pd);
}

static pid_t	ft_order(char *cmd, t_minishell *shell, int fdin, int *fd)
{
	char	**command;
	pid_t	pd;

	pd = -1;
	command = ft_split(cmd, ' ');
	if (!ft_strncmp(command[0], "echo", ft_strlen(command[0])))
		ft_echo(cmd, fd[1]);
	else if (!ft_strncmp(command[0], "cd", ft_strlen(command[0])))
		return (ft_free_mtx(command), -1);
	else if (!ft_strncmp(command[0], "pwd", ft_strlen(command[0])))
		ft_print_pwd(shell, fd[1]);
	else if (!ft_strncmp(command[0], "export", ft_strlen(command[0])))
		return (ft_free_mtx(command), -1);
	else if (!ft_strncmp(command[0], "unset", ft_strlen(command[0])))
		return (ft_free_mtx(command), -1);
	else if (!ft_strncmp(command[0], "exit", ft_strlen(command[0])))
		return (ft_free_mtx(command), -1);
	else if (!ft_strncmp(command[0], "env", ft_strlen(command[0])))
		ft_print_env(shell, fd[1]);
	else
		pd = ft_exec2(command, shell, fdin, fd);
	ft_free_mtx(command);
	if (pd != -1)
		return (pd);
	return (-1);
}

static t_command	*ft_check_heredoc(t_command *cmd, t_minishell *shell)
{
	t_command	*aux;
	char		**tmp;

	if (!shell->here)
		return (cmd);
	aux = cmd;
	tmp = NULL;
	while (aux)
	{
		if (ft_strnstr(aux->command, shell->here, ft_strlen(aux->command)))
		{
			shell->del = ft_split(aux->command, ' ');
			tmp = ft_take_one(ft_split(aux->command, ' '));
			free(aux->command);
			aux->command = ft_strjoin_gnl(tmp[0], " ");
			aux->command = ft_strjoin_gnl(aux->command, tmp[1]);
			free(tmp[1]);
			free(tmp);
		}
		aux = aux->next;
	}
	return (cmd);
}

void	ft_ord(t_command *cmd, t_minishell *shell, int fdin, int fdout)
{
	t_command	*aux;
	int			fd[2];
	pid_t		*pd;
	int			i;

	pd = ft_calloc((ft_lst_size(cmd) + 1), sizeof(pid_t));
	aux = ft_check_heredoc(cmd, shell);
	i = 0;
	fdin = -1;
	while (aux)
	{
		if (pipe(fd) == -1)
			exit (1);
		if (!aux->next)
			pd[i] = ft_order_single(aux->command, shell, fdin, fdout);
		else
			pd[i] = ft_order(aux->command, shell, fdin, fd);
		i++;
		close (fd[1]);
		fdin = fd[0];
		aux = aux->next;
	}
	g_code_error = (ft_cw2(pd) >> 8) & 0xFF;
	ft_close(fdin, fdout);
	ft_unlink(shell->del);
}
