/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse8.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:24:53 by rofuente          #+#    #+#             */
/*   Updated: 2024/03/12 17:43:45 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_len(char **cmd)
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

char	*ft_swap(char *cmd, char *inf)
{
	char	**tmp;
	char	*command;
	int		i;

	i = 1;
	tmp = ft_split(cmd, ' ');
	if (open(inf, O_RDONLY, 0644) < 0)
	{
		free (tmp);
		return ("ERROR INF");
	}
	command = ft_strjoin(tmp[1], " ");
	command = ft_strjoin(command, inf);
	while (tmp[++i])
		command = ft_strjoin(command, tmp[i]);
	ft_free_mtx(tmp);
	free(cmd);
	return (command);
}

static char	*ft_spr(char **line, char *built)
{
	int		i;
	int		j;
	char	*word;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (ft_strncmp(line[i], built, ft_strlen(line[i])) == 0)
		{
			word = malloc(sizeof(char) * ft_strlen(line[i]));
			while (line[i][j])
			{
				word[j] = line[i][j];
				j++;
			}
			ft_free_mtx(line);
			return (word);
		}
		i++;
	}
	ft_free_mtx(line);
	return ("Error");
}
static char	*ft_built(char *cmd)
{
	if (ft_strnstr(cmd, "echo", ft_strlen(cmd))
		&& ft_strlen(cmd) > 0)
		return (ft_spr(ft_split(cmd, ' '), "echo"));
	else if (ft_strnstr(cmd, "cd", ft_strlen(cmd))
		&& ft_strlen(cmd) > 0)
		return (ft_spr(ft_split(cmd, ' '), "cd"));
	else if (ft_strnstr(cmd, "pwd", ft_strlen(cmd))
		&& ft_strlen(cmd) > 0)
		return (ft_spr(ft_split(cmd, ' '), "pwd"));
	else if (ft_strnstr(cmd, "export", ft_strlen(cmd))
		&& ft_strlen(cmd) > 0)
		return (ft_spr(ft_split(cmd, ' '), "export"));
	else if (ft_strnstr(cmd, "unset", ft_strlen(cmd))
		&& ft_strlen(cmd) > 0)
		return (ft_spr(ft_split(cmd, ' '), "unset"));
	else if (ft_strnstr(cmd, "env", ft_strlen(cmd))
		&& ft_strlen(cmd) > 0)
		return (ft_spr(ft_split(cmd, ' '), "env"));
	else if (ft_strnstr(cmd, "exit", ft_strlen(cmd))
		&& ft_strlen(cmd) > 0)
		return (ft_spr(ft_split(cmd, ' '), "exit"));
	else if (ft_strnstr(cmd, "./minishell", ft_strlen(cmd))
		&& ft_strlen(cmd) > 0)
		return (ft_spr(ft_split(cmd, ' '), "./minishell"));
	return ("exec");
}

void	ft_cmdtake(t_command **cmd)
{
	t_command	*aux;

	aux = *cmd;
	while (aux)
	{
		aux->built = ft_built(aux->command);
		aux = aux->next;
	}
}
