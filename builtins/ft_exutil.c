/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exutil.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmonjas- <dmonjas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:37:25 by dmonjas-          #+#    #+#             */
/*   Updated: 2023/12/13 17:37:32 by dmonjas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_mtx(char **mtx)
{
	int	i;

	i = -1;
	while (mtx[++i])
		free(mtx[i]);
	free(mtx);
	mtx = NULL;
}

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

char	*ft_get_var(t_command *cmd)		// Al pasar la estructura va mejor q pansando como un char, pero sigue mal a veces
{
	char	*var;
	int		i;

	if (!cmd->argv[1])
		return (NULL);
	if (!ft_contain(cmd->argv[1], '='))
		var = ft_strdup(cmd->argv[1]);
	else
	{
		i = ft_find(cmd->argv[1], '=');
		var = ft_substr(&cmd->argv[1][0], 0, i);		// argv[] se corrompe aqui ns xq
	}
	if (var != NULL && var[0] == '\0')
	{
		free (var);
		var = NULL;
	}
	return (var);
}
