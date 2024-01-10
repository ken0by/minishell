/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:02:03 by dmonjas-          #+#    #+#             */
/*   Updated: 2023/01/20 16:08:56 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	k;

	k = ft_strlen(src);
	i = 0;
	while (dst[i] && i < dstsize)
		i++;
	j = 0;
	while (src[j] && (i + j + 1) < dstsize)
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i < dstsize)
		dst[i + j] = '\0';
	return (i + k);
}

/* int main()
{
	char	s1[] = "hola";
	char	*s2 = " mundo";
	size_t	a;

	a = (ft_strlen(s1) + ft_strlen(s2)) + 1;
	printf("%lu", ft_strlcat(s1, s2, a));
	return (0);
} */
