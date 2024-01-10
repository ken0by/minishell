/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmonjas- <dmonjas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:44:00 by dmonjas-          #+#    #+#             */
/*   Updated: 2023/11/08 08:24:03 by dmonjas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free(char **dst, int i)
{
	while (i-- > 0)
		free (dst[i]);
	free(dst);
}

static int	ft_num(const char *s, char c)
{
	int	i;
	int	count;
	int	j;

	i = 0;
	j = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && j == 0)
		{
			j = 1;
			count++;
		}
		else if (s[i] == c)
			j = 0;
		i++;
	}
	return (count);
}

static char	*ft_word(const char *s, char c)
{
	int		len;
	int		i;
	char	*word;

	len = 0;
	while (s[len] && s[len] != c)
	{
		len++;
	}
	word = malloc(sizeof(char) * len + 1);
	if (word == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static char	**ft_end(char **dst, const char *s, char c, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] != c && j == 0)
		{
			j = 1;
			dst[k] = ft_word(&s[i], c);
			if (!dst[k])
			{
				ft_free(dst, k);
				return (NULL);
			}
			k++;
		}
		else if (s[i] == c)
			j = 0;
		i++;
	}
	dst[k] = NULL;
	return (dst);
}

char	**ft_split(char const *s, char c)
{
	char	**dst;
	int		i;

	i = 0;
	dst = malloc(sizeof(char *) * (ft_num(s, c) + 1));
	if (!dst || !s)
		return (NULL);
	dst = ft_end(dst, s, c, i);
	return (dst);
}

/* int main()
{
	const char s[] = "lorem ipsum dolor";
	char c = ' ';
	char **dst;
	int	i;

	dst = ft_split(s, ' ');
	i = 0;	
	while (dst[i])
	{
		printf("%s\n", dst[i]);
		i++;
	} 
	printf("%s\n", dst[i]);
	printf("%s\n", dst[i+1]);
	printf("%s\n", dst[i+2]);
	return (0);
} */
