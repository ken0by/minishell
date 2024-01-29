/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse7.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:24:53 by rofuente          #+#    #+#             */
/*   Updated: 2024/01/29 12:44:34 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_len(char **cmd)
{
	int		i;
	int		j;
	int		k;

	i = -1;
	k = 0;
	while (cmd[++i])
	{
		j = -1;
		while (cmd[i][++j])
			k++;
		k++;
	}
	return (k + 1);
}

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
char	*ft_exp(char *line, char **env)
{
	char	**cmd;
	int		i;

	cmd = ft_split(line, ' ');
	i = 0;
	while (cmd[i])
	{
		if (cmd[i][0] != '$')
			cmd[i] = ft_find_var(cmd[i], env);
		else if (ft_strnstr(cmd[i], "$?", ft_strlen(cmd[i])) != 0)
			cmd[i] = ft_sust_doll(cmd[i]);
		else if (ft_strnstr(cmd[i], "$", ft_strlen(cmd[i])) != 0)
			cmd[i] = ft_here_exp(cmd[i], env);
		i++;
	}
	free(line);
	return (ft_join_line(cmd));
}
