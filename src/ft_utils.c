/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:59:53 by dmonjas-          #+#    #+#             */
/*   Updated: 2024/01/16 18:04:26 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_skip_space(char *cmd, int i)
{
	while (cmd[i] == ' ')
		i++;
	return (i);
}

static char	*ft_copy_path(char *str, int i)
{
	char	*tmp;

	if (i == 4)
		tmp = ft_substr(str, i, ft_strlen(str) - i);
	if (i == 5)
		tmp = ft_substr(str, i, ft_strlen(str) - i);
	if (i == 7)
		tmp = ft_substr(str, i, ft_strlen(str) - i);
	return (tmp);
}

char	*ft_env(char **env, char *c)
{
	int		i;
	int		size;
	char	*str;

	size = ft_strlen(c);
	i = -1;
	str = NULL;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], c, size))
			str = ft_copy_path(env[i], size);
		if (str)
			break ;
	}
	if (!str)
		ft_error_path(1);
	return (str);
}

char	**ft_cpy_env(char **env)
{
	char	**tmp;
	int		i;
	int		j;

	i = 0;
	while (env[i])
		i++;
	tmp = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (env[++i])
		tmp[i] = malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
	i = -1;
	while (env[++i])
	{
		j = -1;
		while (env[i][++j])
			tmp[i][j] = env[i][j];
		tmp[i][j] = '\0';
	}
	tmp[i] = NULL;
	return (tmp);
}
