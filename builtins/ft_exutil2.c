/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exutil2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodro <rodro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:44:48 by rofuente          #+#    #+#             */
/*   Updated: 2024/03/04 18:59:02 by rodro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_cpy_ct(char *str, int i)
{
	char	*ct;
	int		j;
	int		n;

	if (str[i] == '=')
		i += 1;
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
	ct = ft_cpy_ct(str, (ft_strlen(var)));
	if (ct != NULL && ct[0] == '\0')
	{
		free(ct);
		ct = NULL;
	}
	return (ct);
}

t_command	*ft_list_convert(char *cmd)
{
	t_command	*aux;
	int			i;
	int			j;

	aux = malloc(sizeof(t_command));
	if (!aux)
		return (NULL);
	aux = NULL;
	j = 0;
	i = 0;
	while (cmd[i])
	{
		j = i;
		while (cmd[i] != ' ' && cmd[i])
			i++;
		ft_lstadd_back_shell(&aux, ft_lstnew_shell(ft_substr(cmd, j, (i - j))));
		if (cmd[i] == ' ')
			i++;
	}
	return (aux);
}

static int	ft_count_en(char **env)
{
	int	i;

	if (!env || !env[0])
		return (0);
	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	ft_alfa(char **env, int fd)
{
	int		i;
	int		j;
	int		len;
	char	*aux;

	i = 0;
	len = ft_count_en(env);
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
	ft_print_ordenv(env, fd);
}
