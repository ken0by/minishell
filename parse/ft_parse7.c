/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse7.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:24:53 by rofuente          #+#    #+#             */
/*   Updated: 2024/01/23 18:36:21 by rofuente         ###   ########.fr       */
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

static void	*ft_join_line(char **cmd)
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
	}
	line[k] = '\0';
	ft_free_mtx(cmd);
	return (line);
}

/* Esta funcion mira si hay que sustituir cuando me pasan un variable por el heredoc, pero no devuelve la variable ns xq */

char	*ft_exp(char *line, char **env)
{
	char	**cmd;
	int		i;

	cmd = ft_split(line, ' ');
	i = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == 39)
			i++;
		else if (ft_strnstr(cmd[i], "$?", ft_strlen(cmd[i])) != 0)
			cmd[i] = ft_sust_doll(cmd[i]);
		else if (ft_strnstr(cmd[i], "$", ft_strlen(cmd[i])) != 0)
			cmd[i] = ft_param(cmd[i], env);
		else
			i++;
	}
	return (ft_join_line(cmd));
}

