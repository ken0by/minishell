/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_system.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:44:31 by dmonjas-          #+#    #+#             */
/*   Updated: 2024/02/27 15:41:18 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_select(t_command *cmd, t_minishell *shell, int fd)
{
	if (!ft_strncmp(cmd->built, "echo", ft_strlen(cmd->built)))
		ft_echo(cmd->command, fd);
	else if (!ft_strncmp(cmd->built, "cd", ft_strlen(cmd->built)))
		ft_cd(cmd->command, shell);
	else if (!ft_strncmp(cmd->built, "pwd", ft_strlen(cmd->built)))
		ft_print_pwd(shell, fd);
	else if (!ft_strncmp(cmd->built, "export", ft_strlen(cmd->built)))
		ft_exist(cmd->command, shell, fd);
	else if (!ft_strncmp(cmd->built, "unset", ft_strlen(cmd->built)))
		ft_unset(cmd->command, shell);
	else if (!ft_strncmp(cmd->built, "env", ft_strlen(cmd->built)))
		ft_print_env(shell, fd);
	else
		return (1);
	close (fd);
	return (0);
}

int	ft_cw(int fdout, pid_t pd)
{
	int	status;

	status = 0;
	close(fdout);
	waitpid(pd, &status, 0);
	return (status);
}

void	ft_dupfd(int fdin, int fdout)
{
	if (fdin > 0 || fdin != -1)
	{
		dup2(fdin, STDIN_FILENO);
		close(fdin);
	}
	if (fdout > 1)
		dup2(fdout, STDOUT_FILENO);
}

void	ft_exec(char **cmd, t_minishell *shell, int fdin, int fdout)
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
		ft_dupfd(fdin, fdout);
		if (execve(path, cmd, shell->env) == -1)
			ft_peror(cmd[0], "");
		free (path);
		ft_free_mtx(cmd);
		close(fdout);
	}
	else
		g_code_error = (ft_cw(fdout, pd) >> 8) & 0xFF;
}

void	ft_system(t_command *cmd, t_minishell *shell, int fdin, int fdout)
{
	g_code_error = 0;
	if (ft_lstsize_shell(cmd) == 1)
	{
		if (!ft_strncmp(cmd->command, "exit", 4))
			ft_exit_code(cmd, shell);
		else if (!ft_strncmp(cmd->command, "minishell",
				ft_strlen(cmd->command)))
			ft_shell_up(shell);
		else if (shell->heredoc)
		{
			if (!ft_strncmp(cmd->built, "echo", ft_strlen(cmd->built)))
				ft_putstr_fd("\n", fdout);
			else
				ft_exec(ft_split(cmd->command, ' '), shell, fdin, fdout);
			unlink(ft_split(cmd->command, ' ')[1]);
			shell->heredoc = 0;
		}
		else if (ft_select(cmd, shell, fdout) == 1)
			ft_exec(ft_split(cmd->command, ' '), shell, fdin, fdout);
	}
	else if (ft_lstsize_shell(cmd) > 1)
		ft_ord(cmd, shell, ft_check_in(shell), ft_check_out(shell));
	shell->outfile = STDOUT_FILENO;
	shell->infile = STDIN_FILENO;
	dup2(STDIN_FILENO, STDOUT_FILENO);
}
