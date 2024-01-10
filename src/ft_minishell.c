/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:31:09 by dmonjas-          #+#    #+#             */
/*   Updated: 2024/01/10 14:57:36 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_init_var(t_minishell *shell, char **env)
{
	shell->cmd_line = NULL;
	shell->path = ft_env(env, "PATH=");
	shell->pwd = ft_env(env, "PWD=");
	shell->oldpwd = ft_env(env, "OLDPWD=");
	shell->root = ft_env(env, "HOME=");
	shell->env = ft_cpy_env(env);
	shell->code_error = 0;
	ft_init_signal();
}

int	main(int ac, char **av, char **env)
{
	t_minishell	shell;

	if (ac != 1 || av[1])
		ft_error_arguments();
	ft_init_var(&shell, env);
	ft_signal_dis();
	while (1)
	{
		shell.cmd_line = readline(GREEN"Minishell: "RESET);
		if (!shell.cmd_line)
			ft_error_cmd();
		if (!ft_strncmp(shell.cmd_line, "exit", 4))
			ft_exit_code(shell.cmd_line);
		shell.cmd_line[ft_strlen(shell.cmd_line)] = '\0';
		add_history(shell.cmd_line);
		ft_check_line(&shell);
		free(shell.cmd_line);
	}
	return (0);
}
