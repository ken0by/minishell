/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:24:27 by rodro             #+#    #+#             */
/*   Updated: 2024/01/24 12:41:53 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_check_in(t_minishell *shell)
{
	if (shell->infile)
		return (shell->infile);
	return (STDIN_FILENO);
}

int	ft_check_out(t_minishell *shell)
{
	if (shell->outfile)
		return (shell->outfile);
	return (STDOUT_FILENO);
}

static void	ft_order(char *cmd, t_minishell *shell, int fdin, int fdout)
{
	char	**command;

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
		ft_exec(command, shell, fdin, fdout);
	ft_free_mtx(command);
}

void	ft_ord(t_command *cmd, t_minishell *shell)
{
	t_command	*aux;
	int			fd[2];
	int			fdin;
	int			fdout;

	fdin = ft_check_in(shell);
	fdout = ft_check_out(shell);
	aux = cmd;
	while (aux)
	{
		if (pipe(fd) == -1)
			exit (1);
		if (!aux->next)
			ft_order(aux->command, shell, fdin, fdout);
		else
			ft_order(aux->command, shell, fdin, fd[1]);
		close (fd[1]);
		fdin = fd[0];
		aux = aux->next;
	}
	close(fdin);
	close(fdout);
	ft_free_cmd(&cmd);
}
