/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exutil2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmonjas- <dmonjas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:44:48 by rofuente          #+#    #+#             */
/*   Updated: 2023/12/13 17:37:37 by dmonjas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_cpy_ct(char *str, int i)
{
	char	*ct;
	int		j;
	int		n;

	j = i;
	while (str[j])
		j++;
	ct = malloc(sizeof(char *) * (j + 1));
	if (!ct)
		return (NULL);
	j = i - 1;
	n = 0;
	while (str[++j] && str[j])
	{
		ct[n] = str[j];
		n++;
	}
	ct[n] = '\0';
	return (ct);
}

char	*ft_get_content(char *str, char *var)
{
	char	*ct;

	if (!str || !var)
		return (NULL);
	ct = ft_cpy_ct(str, (ft_strlen(var) + 1));
	if (ct != NULL && ct[0] == '\0')
	{
		free(ct);
		ct = NULL;
	}
	return (ct);
}

int	ft_varct(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '=')
			return (1);
	return (0);
}
