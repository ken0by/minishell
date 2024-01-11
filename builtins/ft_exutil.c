/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exutil.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:37:25 by dmonjas-          #+#    #+#             */
/*   Updated: 2024/01/11 13:34:49 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* Esta funcion comprueba q si la variable existe */
int	ft_check_var(char *str, char **env)
{
	int		i;
	char	*aux;

	aux = ft_strjoin(str, "=");
	i = -1;
	while (env[++i])
		if (!ft_strncmp(env[i], aux, ft_strlen(aux)))
			return (1);
	return (0);
}

static int	ft_contain(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (c == '\0')
		return (0);
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return (1);
	return (0);
}

static int	ft_find(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char	*ft_get_var(char *cmd)		// Al pasar la estructura va mejor q pansando como un char, pero sigue mal a veces
{
	char	*var;
	int		i;

	if (!cmd)
		return (NULL);
	if (!ft_contain(cmd, '='))
		var = ft_strdup(cmd);
	else
	{
		i = ft_find(cmd, '=');
		var = ft_substr(cmd, 0, i);		// command[] se corrompe aqui ns xq
	}
	if (var != NULL && var[0] == '\0')
	{
		free (var);
		var = NULL;
	}
	return (var);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] && s2[j])
	{
		if (s1[i] != s2[j])
			return (s1[i] - s2[j]);
		i++;
		j++;
	}
	return (s1[i] - s2[j]);
}
