/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ecutil.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmonjas- <dmonjas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:49:51 by rofuente          #+#    #+#             */
/*   Updated: 2023/12/13 17:37:14 by dmonjas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_var(char *var)
{
	char	*aux;
	int		i;
	int		j;

	aux = malloc(sizeof(char) * ft_strlen(var) + 1);
	i = -1;
	j = 0;
	while (var[++i])
	{
		if (var[i] != '$' && var[i] != 34 && var[i] != 39)
		{
			aux[j] = var[i];
			j++;
		}
	}
	aux[j] = '=';
	aux[j + 1] = '\0';
	return (aux);
}
