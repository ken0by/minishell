/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 08:24:23 by dmonjas-          #+#    #+#             */
/*   Updated: 2024/01/15 19:22:15 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_strchr_in(const char *s, int c)
{
	int	i;
	int	j;

	j = ft_strlen(s);
	i = 0;
	if (!s)
		return (0);
	while (i <= j)
	{
		if (s[i] == (char)c)
		{
			i--;
			while (s[i] == ' ')
				i--;
			i++;
			return (i);
		}
		i++;
	}
	return (0);
}

int	ft_strchr_out(const char *s, int c)
{
	int	i;
	int	j;

	j = ft_strlen(s);
	i = 0;
	if (!s)
		return (0);
	while (i <= j)
	{
		if (s[i] == (char)c)
		{
			if (s[i + 1] == (char)c)
				i++;
			i++;
			while (s[i] == ' ')
				i++;
			return (i);
		}
		i++;
	}
	return (0);
}
