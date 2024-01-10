/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_gnl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmonjas- <dmonjas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:43:42 by dmonjas-          #+#    #+#             */
/*   Updated: 2023/11/21 13:33:33 by dmonjas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*dst;
	size_t	a;

	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	a = ((ft_strlen(s1) + ft_strlen(s2)) + 1);
	dst = malloc(sizeof(char) * a);
	if (!dst)
		return (NULL);
	dst = ft_strlcat_gnl(dst, s1, s2);
	free(s1);
	return (dst);
}
