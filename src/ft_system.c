/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_system.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:44:31 by dmonjas-          #+#    #+#             */
/*   Updated: 2024/03/27 14:30:27 by rofuente         ###   ########.fr       */
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

void	ft_exec(char **cmd, t_minishell *shell, int fdin, int fdout)
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
	else
		g_code_error = (ft_cw(fdout, pd) >> 8) & 0xFF;
	if (path)
		free (path);
	ft_free_mtx(cmd);
	close(fdout);
}

static void	ft_single_cmd(t_command *cmd,
	t_minishell *shell, int fdin, int fdout)
{
	if (!ft_strncmp(cmd->built, "exit", ft_strlen(cmd->built)))
		ft_exit_code(cmd, shell);
	else if (!ft_strncmp(cmd->built, "./minishell",
			ft_strlen(cmd->built)))
		ft_next_lvl(shell, fdout);
	else if (shell->heredoc)
	{
		if (!ft_strncmp(cmd->built, "echo", ft_strlen(cmd->built)))
			ft_putstr_fd("\n", fdout);
		else
			ft_exec(ft_take_one(ft_split(cmd->command, ' ')),
				shell, fdin, fdout);
		ft_unlink(ft_split(cmd->command, ' '));
		shell->heredoc = 0;
	}
	else if (ft_select(cmd, shell, fdout) == 1)
		ft_exec(ft_check_quotes(cmd), shell, fdin, fdout);
}

void	ft_system(t_command *cmd, t_minishell *shell, int fdin, int fdout)
{
	g_code_error = 0;
	if (ft_lstsize_shell(cmd) == 1)
		ft_single_cmd(cmd, shell, fdin, fdout);
	else if (ft_lstsize_shell(cmd) > 1)
		ft_ord(cmd, shell, ft_check_in(shell), ft_check_out(shell));
	shell->outfile = -1;
	shell->infile = -1;
	dup2(STDIN_FILENO, STDOUT_FILENO);
}
