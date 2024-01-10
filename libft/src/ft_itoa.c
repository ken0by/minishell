/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmonjas- <dmonjas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:32:25 by dmonjas-          #+#    #+#             */
/*   Updated: 2023/01/25 15:46:41 by dmonjas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(long int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		n = n / 10;
		len ++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char		*dst;
	int			len;
	long int	a;

	a = n;
	len = ft_len(n);
	dst = malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	dst[len--] = '\0';
	if (a == 0)
		dst[0] = '0';
	if (a < 0)
	{
		dst[0] = '-';
		a = a * -1;
	}
	while (a > 0)
	{
		dst[len--] = a % 10 + '0';
		a = a / 10;
	}
	return (dst);
}

/*  int main()
{
	int a;

	a = -2147483648LL;
	printf("%s", ft_itoa(a));

	return (0);
} */