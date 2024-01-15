/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_system.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:44:31 by dmonjas-          #+#    #+#             */
/*   Updated: 2024/01/15 17:47:50 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_err(char *av)
{
	perror(av);
	exit (EXIT_FAILURE);
}

static void	ft_red(t_command *cmd)
{
	cmd->inf = open(cmd->infile, O_RDONLY);
	if (cmd->inf < 0)
		ft_err(cmd->infile);
	cmd->out = open(cmd->outfile, O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (cmd->out < 0)
		ft_err(cmd->outfile);

}

static int	ft_select(t_command *cmd, t_minishell *shell)
{
	if  (ft_strnstr(cmd->built, "echo", ft_strlen(cmd->built)))
		ft_echo(cmd);
	else if  (ft_strnstr(cmd->built, "cd", ft_strlen(cmd->built)))
		ft_cd(cmd, shell);
	else if  (ft_strnstr(cmd->built, "pwd", ft_strlen(cmd->built)))
		ft_print_pwd(shell);
	else if  (ft_strnstr(cmd->built, "export", ft_strlen(cmd->built)))
		ft_exist(cmd, shell);
	else if  (ft_strnstr(cmd->built, "unset", ft_strlen(cmd->built)))
		ft_unset(cmd, shell);
	else if  (ft_strnstr(cmd->built, "env", ft_strlen(cmd->built)))
		ft_print_env(shell);
	else
		return (1);
	return (0);
}

static void	ft_one(t_command *cmd, t_minishell *shell)
{
	char	*path;
	char 	**command;
	int		status;
	pid_t	pd;

	status = 0;
	pd = fork();		//los builtins tinen que ir fuera del fork pq el cd no funciona si hay un exit al final
	if (pd < 0)
		ft_error("fork() error");
	if (pd == 0)
	{
		command = ft_split(cmd->command, ' ');
		path = ft_cmdpath(command[0], shell->env);
		if (!path)
			ft_put_msg(command[0], "command not found\n");
		if (cmd->infile || cmd->outfile)
			ft_red(cmd);
		if (execve(path, command, shell->env) < 0)
			ft_per(command[0], "");
		//exit (0);
	}
	else
		waitpid(pd, &status, 0);
	code_error = (status >> 8) & 0xFF;
}

void	ft_system(t_command *cmd, t_minishell *shell)
{
	code_error = 0;
	if (ft_lstsize_shell(cmd) == 1)
	{
		if (!ft_strncmp(cmd->command, "exit", 4))
			ft_exit_code(shell);
		else if (!ft_strncmp(cmd->command, "minishell", ft_strlen(cmd->command)))
			ft_shell_up(shell);
		else if (ft_select(cmd, shell) == 1)
			ft_one(cmd, shell);
	}
	else if (ft_lstsize_shell(cmd) > 1)
		ft_ord(cmd, shell);
}
