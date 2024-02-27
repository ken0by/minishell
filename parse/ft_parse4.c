/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmonjas- <dmonjas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 10:48:52 by dmonjas-          #+#    #+#             */
/*   Updated: 2024/02/27 10:38:13 by dmonjas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_change_doll(char *fir_line, char *sec_line, t_minishell *shell)
{
	char	*line;

	line = ft_strjoin_gnl(fir_line, ft_itoa(shell->last_error));
	if (sec_line)
		line = ft_strjoin_gnl(line, sec_line);
	return (line);
}

char	*ft_sust_doll(char *line, t_minishell *shell)
{
	int		i;
	int		j;
	char	*fir_line;
	char	*sec_line;

	i = 0;
	fir_line = NULL;
	sec_line = NULL;
	while (line[i] != '$' && line[i])
		i++;
	fir_line = ft_substr(line, 0, i);
	j = i;
	j += 2;
	if (line[j])
		sec_line = ft_substr(line, j, ft_strlen(&line[j]));
	line = ft_change_doll(fir_line, sec_line, shell);
	return (line);
}
