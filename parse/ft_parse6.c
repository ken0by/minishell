/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:50:00 by rofuente          #+#    #+#             */
/*   Updated: 2024/01/23 17:25:09 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


static char	*ft_sjoin(char *s1, char *s2)
{
	char	*r;
	int		x;
	int		y;

	r = malloc(sizeof(char) * (ft_strlen((char *)s1)
				+ ft_strlen((char *)s2)) + 2);
	if (!r)
		return (NULL);
	x = 0;
	y = 0;
	while (s1[y])
		r[x++] = s1[y++];
	r[x] = ' ';
	x++;
	y = 0;
	while (s2[y])
		r[x++] = s2[y++];
	r[x] = '\0';
	return (r);
}

void	ft_swap(t_command *cmd)
{
	char	**tmp;
	char	*aux;
	char	*aux2;

	tmp = ft_split(cmd->command, ' ');
	if (open(tmp[0], O_RDONLY, 0644) < 0)
	{
		free (tmp);
		return ;
	}
	aux = tmp[0];
	aux2 = tmp[1];
	tmp[0] = aux2;
	tmp[1] = aux;
	free (cmd->command);
	cmd->command = ft_sjoin(tmp[0], tmp[1]);
}

char	*ft_take_size(char *cmd)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	j = 0;
	while (cmd[++i])
	{
		if (cmd[i] == '>')
			break ;
		if (cmd[i] == '<')
		{
			i++;
			while (cmd[i] == ' ')
				i++;
			i--;
		}
		else
			j++;
	}
	tmp = ft_calloc((j + 1), sizeof(char));
	return (tmp);
}
