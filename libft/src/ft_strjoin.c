/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmonjas- <dmonjas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:24:33 by dmonjas-          #+#    #+#             */
/*   Updated: 2023/06/12 12:41:13 by dmonjas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	a;

	a = (ft_strlen(s1) + ft_strlen(s2)) + 1;
	dst = malloc(sizeof(char) * a);
	if (dst == 0)
		return (0);
	ft_strlcpy(dst, s1, (ft_strlen(s1) + 1));
	ft_strlcat(dst, s2, a);
	return (dst);
}

/* int main()
{
 	//char *s1 = "my favorite animal is";
 	//char s2[] = " ";
 	//char *s3 = "the nyancat";
 	//char *res = ft_strjoin(s1, s2);
	//char *res = ft_strjoin(ft_strjoin(s1, s2), s3);
	//printf("%s", res);

	char a[] = "";
	char b[] = "";

	printf("%s", ft_strjoin(a, b)); 
	return (0);
}
 */
