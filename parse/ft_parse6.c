/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:46:02 by dmonjas-          #+#    #+#             */
/*   Updated: 2024/02/27 16:57:31 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_join_line(char **cmd)
{
	char	*line;
	int		i;
	int		j;
	int		k;

	line = malloc(sizeof(char) * ft_len(cmd));
	i = -1;
	k = 0;
	while (cmd[++i])
	{
		j = -1;
		while (cmd[i][++j])
		{
			line[k] = cmd[i][j];
			k++;
		}
		if (cmd[i + 1] == NULL)
			break ;
		line[k] = ' ';
		k++;
	}
	line[k] = '\0';
	ft_free_mtx(cmd);
	return (line);
}

static char	*ft_here_exp(char *line, char **env)
{
	int		i;
	char	*aux;

	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	i = -1;
	aux = NULL;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], &line[1], ft_strlen(&line[1])))
			aux = ft_substr(env[i], (ft_strlen(&line[1]) + 1),
					(ft_strlen(env[i]) - ft_strlen(&line[1])));
		if (aux)
			break ;
	}
	free (line);
	line = ft_calloc(ft_strlen(aux) + 1, sizeof(char));
	i = -1;
	while (aux[++i])
		line[i] = aux[i];
	line[i] = '\n';
	return (free(aux), line);
}

/* Esta funcion mira si hay que sustituir cuando me pasan un variable
por el heredoc, cuando pasan comillas se cierra directamente
y no hace nada */
static char	*ft_exp(char *line, t_minishell *shell)
{
	char	**cmd;
	int		i;

	cmd = ft_split(line, ' ');
	i = 0;
	while (cmd[i])
	{
		if (cmd[i][0] != '$')
			cmd[i] = ft_find_var(cmd[i], shell->env);
		else if (ft_strnstr(cmd[i], "$?", ft_strlen(cmd[i])) != 0)
			cmd[i] = ft_sust_doll(cmd[i], shell);
		else if (ft_strnstr(cmd[i], "$", ft_strlen(cmd[i])) != 0)
			cmd[i] = ft_here_exp(cmd[i], shell->env);
		i++;
	}
	free(line);
	return (ft_join_line(cmd));
}

static void	ft_loop(int fd, char *line, char *end, t_minishell *shell)
{
	while (line)
	{
		line = ft_exp(line, shell);
		if ((ft_strncmp(line, end, ft_strlen(end)) == 0)
			&& (ft_strlen(line) == ft_strlen(end) + 1))
			exit(EXIT_SUCCESS);
		write(1, "> ", 2);
		write(fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
}

int	ft_here(char *end, int file, t_minishell *shell)
{
	pid_t	pid;
	char	*line;

	pid = fork();
	if (pid < 0)
		ft_per_nb("fork", STDERR_FILENO);
	if (pid == 0)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		ft_loop(file, line, end, shell);
		close(file);
	}
	else
		wait(NULL);
	return (file);
}
