/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 08:24:23 by dmonjas-          #+#    #+#             */
/*   Updated: 2024/01/10 17:10:06 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_strchr_in(const char *s, int c)
{
	int	i;
	int	j;

	j = ft_strlen(s);
	i = 0;
	if (!s)
		return (0);
	while (i <= j)
	{
		if (s[i] == (char)c)
		{
			i--;
			while (s[i] == ' ')
				i--;
			i++;
			return (i);
		}
		i++;
	}
	return (0);
}

int	ft_strchr_out(const char *s, int c)
{
	int	i;
	int	j;

	j = ft_strlen(s);
	i = 0;
	if (!s)
		return (0);
	while (i <= j)
	{
		if (s[i] == (char)c)
		{
			i++;
			while (s[i] == ' ')
				i++;
			return (i);
		}
		i++;
	}
	return (0);
}

void	ft_lstdel(t_pipe *pipe, t_pipe *del)
{
	t_pipe	*aux;
	t_pipe	*aux1;

	aux = pipe;
	while (aux)
	{
		if (aux->next->argv == del->argv)
		{
			aux1 = aux->next;
			aux->next = aux1->next;
			free(aux1->argv);
		}
		aux = aux->next;
	}
}
