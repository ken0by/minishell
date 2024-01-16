/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:37:07 by dmonjas-          #+#    #+#             */
/*   Updated: 2024/01/16 17:49:36 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char *cmd, int fd)
{
	char	**comm;
	int		i;

	i = 0;
	comm = ft_split(cmd, ' ');
	if (comm[1][0] == '-' && comm[1][1] == 'n')
	{
		i = 8;
		ft_putstr_fd(&cmd[i], fd);
	}
	else
	{
		i = 5;
		ft_putstr_fd(&cmd[i], fd);
		ft_putstr_fd("\n", fd);
	}
}
