/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:31:09 by dmonjas-          #+#    #+#             */
/*   Updated: 2024/01/11 13:21:10 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_init_var(t_minishell *shell, char **env)
{
	shell->shlvl = 1;
	shell->infile = 0;
	shell->outfile = 0;
	shell->cmd_line = NULL;
	shell->path = ft_env(env, "PATH=");
	shell->pwd = ft_env(env, "PWD=");
	shell->oldpwd = ft_env(env, "OLDPWD=");
	shell->root = ft_env(env, "HOME=");
	shell->env = ft_cpy_env(env);
	code_error = 0;
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
		if (!code_error)
			shell.cmd_line = readline(GREEN"Minishell  🤯 $ "RESET);
		else
			shell.cmd_line = readline(RED"Minishell  🤯 $ "RESET);
		if (!shell.cmd_line)
			ft_error_cmd();
		shell.cmd_line[ft_strlen(shell.cmd_line)] = '\0';
		add_history(shell.cmd_line);
		ft_check_line(&shell);
		free(shell.cmd_line);
	}
	return (0);
}
