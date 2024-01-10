/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmonjas- <dmonjas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:26:42 by dmonjas-          #+#    #+#             */
/*   Updated: 2023/01/25 15:50:54 by dmonjas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	count;
	int	valor;

	valor = 0;
	count = 1;
	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{	
		count = count * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		valor = (valor * 10) + str[i] - 48;
		i++;
	}	
	return (valor * count);
}
/*
int main(void)
{
	char str[] = "+-1234hg b345";

	printf("%d", ft_atoi(str));
	return (0);
}*/
