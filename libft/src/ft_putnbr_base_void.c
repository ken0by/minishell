/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmonjas- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 12:56:40 by dmonjas-          #+#    #+#             */
/*   Updated: 2023/03/27 15:16:04 by dmonjas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	ft_write(unsigned long long number, char *base, int i, int *r)
{
	if (number > 0)
	{
		(*r)++;
		ft_write(number / i, base, i, r);
		write(1, &base[number % i], 1);
	}
}

int	ft_putnbr_base_void(unsigned long long number, char *base)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		i++;
	}
	if (number == 0)
	{
		write (1, &base[number % i], 1);
		return (1);
	}
	ft_write(number, base, i, &r);
	return (r);
}
