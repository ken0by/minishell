/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_system.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmonjas- <dmonjas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:44:31 by dmonjas-          #+#    #+#             */
/*   Updated: 2024/01/17 13:07:50 by dmonjas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_select(t_command *cmd, t_minishell *shell, int fd)
{
	if  (!ft_strncmp(cmd->built, "echo", ft_strlen(cmd->built)))
		ft_echo(cmd->command, fd);
	else if  (!ft_strncmp(cmd->built, "cd", ft_strlen(cmd->built)))
		ft_cd(cmd->command, shell);
	else if  (!ft_strncmp(cmd->built, "pwd", ft_strlen(cmd->built)))
		ft_print_pwd(shell, fd);
	else if  (!ft_strncmp(cmd->built, "export", ft_strlen(cmd->built)))
		ft_exist(cmd->command, shell, fd);
	else if  (!ft_strncmp(cmd->built, "unset", ft_strlen(cmd->built)))
		ft_unset(cmd->command, shell);
	else if  (!ft_strncmp(cmd->built, "env", ft_strlen(cmd->built)))
		ft_print_env(shell, fd);
	else
		return (1);
	return (0);
}

int	ft_cw(int fdout, pid_t pd, int status)
{
	close(fdout);
	waitpid(pd, &status, 0);
	return (status);
}

static void	ft_one(char **cmd, t_minishell *shell, int fdin, int fdout)
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
			ft_put_msg(cmd[0], "command not found\n");
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

void	ft_system(t_command *cmd, t_minishell *shell, int fdin, int fdout)
{
	code_error = 0;
	if (ft_lstsize_shell(cmd) == 1)
	{
		if (!ft_strncmp(cmd->command, "exit", 4))
			ft_exit_code(shell);
		else if (!ft_strncmp(cmd->command, "minishell", ft_strlen(cmd->command)))
			ft_shell_up(shell);
		else if (ft_select(cmd, shell, fdout) == 1)
			ft_one(ft_split(cmd->command, ' '), shell, fdin, fdout);
	}
	else if (ft_lstsize_shell(cmd) > 1)
		ft_ord(cmd, shell);
	dup2(STDIN_FILENO, STDOUT_FILENO);
}
