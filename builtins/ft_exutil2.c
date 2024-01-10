/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exutil2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:44:48 by rofuente          #+#    #+#             */
/*   Updated: 2024/01/10 18:24:31 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_cpy_ct(char *str, int i)
{
	char	*ct;
	int		j;
	int		n;

	j = i;
	while (str[j])
		j++;
	ct = malloc(sizeof(char *) * (j + 1));
	if (!ct)
		return (NULL);
	j = i - 1;
	n = 0;
	while (str[++j] && str[j])
	{
		ct[n] = str[j];
		n++;
	}
	ct[n] = '\0';
	return (ct);
}

char	*ft_get_content(char *str, char *var)
{
	char	*ct;

	if (!str || !var)
		return (NULL);
	ct = ft_cpy_ct(str, (ft_strlen(var) + 1));
	if (ct != NULL && ct[0] == '\0')
	{
		free(ct);
		ct = NULL;
	}
	return (ct);
}

int	ft_varct(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '=')
			return (1);
	return (0);
}

static int	ft_count(char **env)
{
	int	i;

	if (!env || !env[0])
		return (0);
	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	ft_alfa(char **env)
{
	int		i;
	int		j;
	int		len;
	char	*aux;

	i = 0;
	len = ft_count(env);
	while (i < len)
	{
		j = -1;
		while (++j < (len - i - 1))
		{
			aux = env[j];
			if (ft_strcmp(env[j], env[j + 1]) > 0)
			{
				aux = env[j];
				env[j] = env[j + 1];
				env[j + 1] = aux;
			}
		}
		i++;
	}
	ft_print_ordenv(env);
}
