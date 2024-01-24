/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse8.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:24:53 by rofuente          #+#    #+#             */
/*   Updated: 2024/01/24 18:31:03 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*ft_join_all(char *first, char *var, char *second, int k)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = malloc(sizeof(char) * (ft_strlen(first)
				+ ft_strlen(var) + ft_strlen(second) + k));
	if (!tmp)
		return (NULL);
	i = -1;
	j = 0;
	while (first[++i])
		tmp[j++] = first[i];
	if (!var)
		return (tmp[j] = '\n', tmp[j + 1] = '\0', tmp);
	i = -1;
	while (var[++i])
		tmp[j++] = var[i];
	i = -1;
	while (second[++i])
		tmp[j++] = second[i];
	tmp[j] = '\0';
	free(first);
	free(var);
	free(second);
	return (tmp);
}

static char	*ft_second(char *line, int i)
{
	char	*second;
	int		j;
	int		k;

	i++;
	while (ft_isalpha(line[i]))
		i++;
	k = i - 1;
	if (!line[i])
		return (NULL);
	while (line[i])
		i++;
	second = malloc(sizeof(char) * (i - k) + 1);
	if (!second)
		return (NULL);
	j = 0;
	while (line[++k])
		second[j++] = line[k];
	second[j] = '\0';
	return (second);
}

static char	*ft_var(char *line, char **env, int k)
{
	int		i;
	int		j;
	char	*var;

	while (line[++k])
		if (!ft_isalpha(line[k]))
			break ;
	var = malloc(sizeof(char) * k + 1);
	if (!var)
		return (NULL);
	i = 0;
	j = 0;
	while (line[++i])
	{
		if (!ft_isalpha(line[i]))
			break ;
		var[j++] = line[i];
	}
	var[j] = '\0';
	i = -1;
	while (env[++i])
		if (!ft_strncmp(env[i], var, ft_strlen(var)))
			return (ft_substr(env[i], ft_strlen(var) + 1,
					(ft_strlen(env[i]) - ft_strlen(var))));
	return (NULL);
}

static char	*ft_first(char *line, int i)
{
	char	*first;

	first = malloc(sizeof(char) * i + 1);
	if (!first)
		return (NULL);
	i = -1;
	while (line[++i])
	{
		if (line[i] == '$')
			break ;
		first[i] = line[i];
	}
	first[i] = '\0';
	return (first);
}

char	*ft_find_var(char *line, char **env)
{
	int		i;
	char	*first;
	char	*var;
	char	*second;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
			break ;
		i++;
	}
	if (!line[i])
		return (line);
	first = ft_first(line, i);
	if (!first)
		return (NULL);
	var = ft_var(&line[i], env, 0);
	if (!var)
		return (free(line), ft_join_all(first, NULL, NULL, 2));
	second = ft_second(line, i);
	return (free(line), ft_join_all(first, var, second, 1));
}
