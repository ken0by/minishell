/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmonjas- <dmonjas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 08:38:14 by dmonjas-          #+#    #+#             */
/*   Updated: 2023/01/23 17:12:26 by dmonjas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	i;

	i = 0;
	if (!s)
	{
		return (0);
	}
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(&s[start]))
		len = ft_strlen(&s[start]);
	dst = malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (0);
	while (i < len && s[start])
			dst[i++] = s[start++];
	dst[i] = '\0';
	return (dst);
}

/* int main()
{
	printf("%s", ft_substr("hola", 9870, 0));
	return (0);
} */