/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_system.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:44:31 by dmonjas-          #+#    #+#             */
/*   Updated: 2024/01/10 18:13:29 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_err(char *av)
{
	perror(av);
	exit (EXIT_FAILURE);
}

static void	ft_red(t_command *cmd, t_minishell *shell)
{
	shell->oldpwd = shell->oldpwd;
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
	code_error = 0;
	return (0);
}

static void	ft_one(t_command *cmd, t_minishell *shell)
{
	char	*path;
	char 	**command;
	int		status;
	pid_t	pd;

	status = 0;
	pd = fork();
	if (pd < 0)
		ft_error("fork() error");
	if (pd == 0)
	{
		if (ft_select(cmd, shell))
		{
			command = ft_split(cmd->command, ' ');
			path = ft_cmdpath(command[0], shell->env);
			if (!path)
				ft_put_msg(command[0], "command not found\n");
			if (cmd->infile || cmd->outfile)
				ft_red(cmd, shell);
			if (execve(path, command, shell->env) < 0)
				ft_per(command[0], "");
			//exit (0);
		}
	}
	else
		waitpid(pd, &status, 0);
	code_error = (status >> 8) & 0xFF;
}

void	ft_system(t_command *cmd, t_minishell *shell)
{
	if (ft_lstsize_shell(cmd) == 1)
	{
		ft_one(cmd, shell);
	}
	else if (ft_lstsize_shell(cmd) > 1)
		ft_printf("son dos comando");
}
