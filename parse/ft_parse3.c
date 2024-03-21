/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmonjas- <dmonjas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 12:31:43 by dmonjas-          #+#    #+#             */
/*   Updated: 2024/03/21 11:34:23 by dmonjas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_dollar(char *change, char *env)
{
	int		i;
	int		j;
	char	*line;

	i = ft_size_param(change) + 1;
	j = ft_strlen(env) - ft_size_param(change) - 1;
	line = ft_substr(env, i, j);
	i = 0;
	j = 0;
	while (change[i])
	{
		if (change[i] == '/')
			j++;
		i++;
	}
	while (j > 0)
	{
		line = ft_strjoin_gnl(line, "/");
		j--;
	}
	free(change);
	return (line);
}

static int	ft_pos(char *line, char **env)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], line, ft_size_param(line)))
		{
			while (env[i][j] != '=')
				j++;
			str = ft_substr(env[i], 0, j);
			if (!ft_strncmp(env[i], line, ft_strlen(str)))
				return (free (str), i);
			else
				return (free (str), -1);
		}
		i++;
	}
	return (-1);
}

static char	*ft_change(char *fir_line, char *sec_line, char *change, char **env)
{
	int		pos;
	char	*line;

	line = NULL;
	pos = ft_pos(change, env);
	if (pos != -1)
	{
		change = ft_dollar(change, env[pos]);
		line = ft_strjoin_gnl(fir_line, change);
		if (sec_line)
			line = ft_strjoin_gnl(line, sec_line);
	}
	else
	{
		line = ft_strdup(fir_line);
		if (sec_line)
			line = ft_strjoin_gnl(line, sec_line);
	}
	free(change);
	if (pos == -1 && fir_line)
		free(fir_line);
	if (sec_line)
		free(sec_line);
	return (line);
}

char	*ft_param(char *line, char **env)
{
	int		i;
	int		j;
	char	*fir_line;
	char	*change;
	char	*sec_line;

	i = 0;
	fir_line = NULL;
	change = NULL;
	sec_line = NULL;
	while (line[i] != '$' && line[i])
		i++;
	fir_line = ft_substr(line, 0, i);
	i++;
	j = i;
	while (line[j] && line[j] != ' ' && line[j] != 39 && line[j] != '$')
		j++;
	change = ft_substr(line, i, (j - i));
	if (line[j])
		sec_line = ft_substr(line, j, ft_strlen(&line[j]));
	free(line);
	line = ft_change(fir_line, sec_line, change, env);
	return (line);
}

void	ft_sust(t_command **cmd, t_minishell *shell)
{
	t_command	*aux;

	aux = *cmd;
	while (aux)
	{
		if (aux->dollar == 1)
			aux = aux->next;
		else
			aux = ft_select_sust(cmd, aux, shell);
	}
}
