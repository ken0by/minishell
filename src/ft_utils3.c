/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:11:48 by rofuente          #+#    #+#             */
/*   Updated: 2024/01/15 18:54:14 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_cp_nb(char *str, int j)
{
	int		i;
	char	*nb;

	nb = malloc(sizeof(char) * j);
	i = 4;
	j = 0;
	while (str[++i])
	{
		nb[j] = str[i];
		j++;
	}
	return (nb);
}

void	ft_err_msg(char *s)
{
	ft_printf("%s\n", s);
	code_error = 1;
}

void	ft_per_nb(char *s, int nb)
{
	perror(s);
	code_error = nb;
}
