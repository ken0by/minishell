/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:44:57 by rofuente          #+#    #+#             */
/*   Updated: 2024/03/20 20:00:01 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_find_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	ft_putstr_fd("Path not found\n", STDERR_FILENO);
	exit (127);
	return (i);
}

static char	*ft_pat(char *c, char **env)
{
	int		i;
	char	**all_path;
	char	*slash;
	char	*path;

	i = ft_find_path(env);
	all_path = ft_split(env[i] + 5, ':');
	i = -1;
	while (all_path[++i])
	{
		slash = ft_strjoin("/", c);
		path = ft_strjoin(all_path[i], slash);
		free (slash);
		if (access(path, F_OK & R_OK) == 0)
		{
			ft_free_mtx(all_path);
			return (path);
		}
		free (path);
	}
	ft_free_mtx(all_path);
	return (NULL);
}

static int	check_command(char *command)
{
	if ((command[0] == '.' && command[1] == '/') || command[0] == '/')
	{
		if (access(command, X_OK) == 0)
			return (1);
		else
			ft_error_perror(command, "");
	}
	return (0);
}

char	*ft_cmdpath(char *cmd, char **env)
{
	char	*path;

	if (!cmd || !cmd[0])
		return (NULL);
	if (check_command(cmd) == 1)
		return (cmd);
	else
	{
		path = ft_pat(cmd, env);
		if (!path)
			return (NULL);
	}
	return (path);
}

void	ft_next_lvl(t_minishell *shell, int fdout)
{
	int	pd;

	pd = fork();
	if (pd == -1)
		ft_error("fork() error");
	if (pd == 0)
	{
		ft_shell_up(shell);
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_int);
	g_code_error = (ft_cw(fdout, pd) >> 8) & 0xFF;
}
