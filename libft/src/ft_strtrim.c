/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmonjas- <dmonjas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:56:03 by dmonjas-          #+#    #+#             */
/*   Updated: 2023/02/01 12:58:43 by dmonjas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_start(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (set[j])
	{
		if (s1[i] == set[j])
		{
			j = 0;
			i++;
		}
		else
			j++;
	}
	return (i);
}

static int	ft_end(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i])
		i++;
	i--;
	j = 0;
	while (set[j])
	{
		if (s1[i] == set[j])
		{
			j = 0;
			i--;
		}
		else
			j++;
	}
	i++;
	return (i);
}

static char	*ft_cp(char *dst, const char *s1, int x, int y)
{
	int	i;

	if (x > y)
		dst = malloc(sizeof(char) * 1);
	else
		dst = malloc(sizeof(char) * (y - x) + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (x < y)
		dst[i++] = s1[x++];
	dst[i] = '\0';
	return (dst);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dst;
	int		x;
	int		y;

	dst = NULL;
	if (s1[0] == '\0')
	{
		dst = malloc(sizeof(char) * 1);
		if (!dst)
			return (NULL);
		dst[0] = '\0';
		return (dst);
	}
	x = ft_start(s1, set);
	y = ft_end(s1, set);
	dst = ft_cp(dst, s1, x, y);
	return (dst);
}

/*  int main()
{
    char s1[] = "hola";
    char set[] = "hola";
    
    printf("%s", ft_strtrim(s1, set));
    return (0);
} */