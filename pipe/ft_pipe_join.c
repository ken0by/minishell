/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_join.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:36:32 by rofuente          #+#    #+#             */
/*   Updated: 2024/01/10 14:59:57 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*ft_strlcat_gnl(char *dst, char *s1, char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s1 && s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		dst[i + j] = s2[j];
		j++;
	}
	dst[i + j] = '\0';
	return (dst);
}

static char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*dst;
	size_t	a;

	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	a = ((ft_strlen(s1) + ft_strlen(s2)) + 1);
	dst = malloc(sizeof(char) * a);
	if (!dst)
		return (NULL);
	dst = ft_strlcat_gnl(dst, s1, s2);
	free(s1);
	return (dst);
}

t_pipe	*ft_join(t_pipe **cmd)
{
	t_pipe	**pipe;
	t_pipe	*aux;
	char		*line;

	pipe = malloc(sizeof(t_pipe));
	*pipe = 0;
	line = NULL;
	aux = *cmd;
	while (aux)
	{
		if (ft_strlen(aux->argv) == 1 && aux->argv[0] == '|')
		{
			ft_plstadd_back(pipe, ft_plst_new(line));
			free(line);
			line = NULL;
			aux = aux->next;
		}
		line = ft_strjoin_gnl(line, aux->argv);
		if (aux->next && aux->next->argv[0] != '|')
			line = ft_strjoin_gnl(line, " ");
		aux = aux->next;
	}
	ft_plstadd_back(pipe, ft_plst_new(line));
	free(line);
	return (*pipe);
}

t_cmd	*ft_cmdlst_new(char *str)
{
	t_cmd	*new;

	new = malloc(sizeof(t_command));
	if (!new)
		return (NULL);
	new->argv = ft_split(str, ' ');
	new->builtin = 0;
	new->exp = 0;
	new->next = NULL;
	return (new);
}

void	ft_cmdlstadd_back(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*aux;

	if (!*cmd)
	{
		*cmd = new;
		return ;
	}
	aux = (*cmd);
	while (aux && aux->next)
		aux = aux->next;
	aux->next = new;
}
