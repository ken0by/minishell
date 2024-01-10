/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmonjas- <dmonjas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:39:49 by dmonjas-          #+#    #+#             */
/*   Updated: 2023/01/23 10:52:48 by dmonjas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*str;
	char	caracter;

	i = 0;
	caracter = (char)c;
	str = (char *)s;
	while (i < n)
	{
		if (str[i] == caracter)
		{
			return (&str[i]);
		}
		i++;
	}
	return (0);
}
/*
int main()
{
	void	*src;

	src = "hola mundo";
	printf("%c", ft_memchr(src, 'o', 10));
	return (0);
}*/
