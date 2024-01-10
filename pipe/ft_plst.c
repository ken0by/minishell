/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:14:28 by rofuente          #+#    #+#             */
/*   Updated: 2024/01/10 17:26:53 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_pipe	*ft_plst_first(char *str)
{
	t_pipe	*new;

	new = malloc(sizeof(t_pipe));
	if (!new)
		return (NULL);
	new->argv = ft_strdup(str);
	new->builtin = 0;
	new->infile = 0;
	new->outfile = 0;
	new->heredoc = 0;
	new->append = 0;
	new->redir = 0;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

int	ft_plstsize(t_pipe *lst)
{
	t_pipe	*aux;
	int			i;

	aux = lst;
	i = 0;
	while (aux)
	{
		aux = aux->next;
		i++;
	}
	return (i);
}


t_pipe	*ft_plstlast(t_pipe *lst)
{
	t_pipe	*aux;

	if (!lst)
		return (NULL);
	aux = lst;
	while (aux && aux->next)
		aux = aux->next;
	return (aux);
}

t_pipe	*ft_plstnew(char *str)
{
	t_pipe	*new;

	new = malloc(sizeof(t_pipe));
	if (!new)
		return (NULL);
	new->argv = ft_strdup(str);
	new->builtin = 0;
	new->infile = 0;
	new->outfile = 0;
	new->heredoc = 0;
	new->append = 0;
	new->redir = 0;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	ft_plstadd_back(t_pipe **lst, t_pipe *new)
{
	t_pipe	*aux;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	aux = ft_plstlast(*lst);
	aux->next = new;
}
