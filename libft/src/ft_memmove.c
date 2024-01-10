/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmonjas- <dmonjas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:32:02 by dmonjas-          #+#    #+#             */
/*   Updated: 2023/01/25 15:33:15 by dmonjas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*str2;
	char	*str1;

	str1 = (char *)dst;
	str2 = (char *)src;
	if (!str1 && !str2)
		return (0);
	if (src < dst)
	{
		while (len > 0)
		{
			len--;
			str1[len] = str2[len];
		}
	}
	i = 0;
	while (i < len)
	{
		str1[i] = str2[i];
		i++;
	}
	return (dst);
}
