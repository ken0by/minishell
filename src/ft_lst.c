/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:25:37 by dmonjas-          #+#    #+#             */
/*   Updated: 2024/03/12 16:39:52 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_command	*ft_lst_first(char *str, char c, int *space)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	if (!new)
		return (NULL);
	new->command = ft_strdup(str);
	new->built = NULL;
	new->next = NULL;
	new->inf = 0;
	new->out = 0;
	new->space = *space;
	if (c == 39)
		new->dollar = 1;
	else if (c == 34)
		new->dollar = 2;
	else
		new->dollar = 0;
	free(str);
	return (new);
}

int	ft_lstsize_shell(t_command *lst)
{
	t_command	*aux;
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

t_command	*ft_lstlast_shell(t_command *lst)
{
	t_command	*aux;

	if (!lst)
		return (NULL);
	aux = lst;
	while (aux && aux->next)
		aux = aux->next;
	return (aux);
}

t_command	*ft_lstnew_shell(char *str)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	if (!new)
		return (NULL);
	new->command = ft_strdup(str);
	new->built = NULL;
	new->next = NULL;
	new->inf = 0;
	new->out = 0;
	if (str[0] == 39)
		new->dollar = 1;
	else
		new->dollar = 0;
	return (new);
}

void	ft_lstadd_back_shell(t_command **lst, t_command *new)
{
	t_command	*aux;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	aux = ft_lstlast_shell(*lst);
	aux->next = new;
}
