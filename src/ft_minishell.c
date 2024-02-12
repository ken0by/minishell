/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodro <rodro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:31:09 by dmonjas-          #+#    #+#             */
/*   Updated: 2024/02/12 12:41:07 by rodro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_cpy_no_env(t_minishell *shell)
{
	shell->env = (char **)malloc(sizeof(char *) * (3));
	shell->env[0] = ft_strjoin("PWD=", getcwd(shell->pwd, 100));
	shell->env[1] = ft_strdup("SHLVL=1");
	shell->env[2] = ft_strdup("_=");
}

static void	ft_init_var(t_minishell *shell, char **env)
{
	shell->shlvl = 1;
	shell->infile = 0;
	shell->outfile = 0;
	shell->heredoc = 0;
	shell->cmd_line = NULL;
	if (!env[0])
	{
		ft_cpy_no_env(shell);
		shell->pwd = ft_env(shell->env, "PWD=");
	}
	else
	{
		shell->env = ft_cpy_env(env);
		shell->path = ft_env(env, "PATH=");
		shell->pwd = ft_env(env, "PWD=");
		shell->oldpwd = ft_env(env, "OLDPWD=");
		shell->root = ft_env(env, "HOME=");
	}
	g_code_error = 0;
	ft_init_signal();
}

/* void leaks()
{
	atexit (leaks);
	system("leaks -q minishell");
} */

int	main(int ac, char **av, char **env)
{
	t_minishell	shell;
	t_command	*cmd;

	if (ac != 1 || av[1])
		ft_error_arguments();
	ft_init_var(&shell, env);
	ft_signal_dis();
	cmd = NULL;
	while (1)
	{
		if (!g_code_error)
			shell.cmd_line = readline(GREEN"Minishell  🤯 $ "RESET);
		else
			shell.cmd_line = readline(RED"Minishell  🤯 $ "RESET);
		if (!shell.cmd_line)
			ft_error_cmd();
		g_code_error = 0;
		shell.cmd_line[ft_strlen(shell.cmd_line)] = '\0';
		add_history(shell.cmd_line);
		ft_check_line(cmd, &shell);
		free(shell.cmd_line);
		ft_free_cmd(&cmd);
	}
	return (0);
}
