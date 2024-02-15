/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodro <rodro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:24:27 by rodro             #+#    #+#             */
/*   Updated: 2024/02/15 13:12:30 by rodro            ###   ########.fr       */
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
	return (status);
}

static void	ft_dupfd2(int fdin, int fdout)
{
	if (fdin > 0)
		dup2(fdin, STDIN_FILENO);
	if (fdout > 1)
		dup2(fdout, STDOUT_FILENO);
	close(fdin);
}

pid_t	ft_exec2(char **cmd, t_minishell *shell, int fdin, int fdout)
{
	char	*path;
	pid_t	pd;

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
		ft_dupfd2(fdin, fdout);
		if (execve(path, cmd, shell->env) == -1)
			ft_peror(cmd[0], "");
		free (path);
		ft_free_mtx(cmd);
		close(fdout);
	}
	else
		close(fdout);
	return (pd);
}

static pid_t	ft_order(char *cmd, t_minishell *shell, int fdin, int fdout)
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
		pd = ft_exec2(command, shell, fdin, fdout);
	ft_free_mtx(command);
	if (pd != -1)
		return (pd);
	return (-1);
}

void	ft_ord(t_command *cmd, t_minishell *shell, int fdin, int fdout)
{
	t_command	*aux;
	int			fd[2];
	pid_t		*pd;
	int			i;

	pd = malloc(sizeof(pid_t) * ft_lst_size(cmd) + 1);	//cambiar el malloc por un calloc a ver si el error de heap-buffer-overflow desaparace
	aux = cmd;
	i = 0;
	while (aux)
	{
		if (pipe(fd) == -1)
			exit (1);
		if (!aux->next)
			pd[i] = ft_order(aux->command, shell, fdin, fdout);
		else
			pd[i] = ft_order(aux->command, shell, fdin, fd[1]);
		i++;
		close (fd[1]);
		fdin = fd[0];
		aux = aux->next;
	}
	ft_printf("%d\n", i);
	ft_printf("%d\n", ft_lst_size(cmd) + 1);
	pd[i] = '\0';
	g_code_error = (ft_cw2(pd) >> 8) & 0xFF;
	close(fdin);
	close(fdout);
}
