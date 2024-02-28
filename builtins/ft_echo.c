/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:37:07 by dmonjas-          #+#    #+#             */
/*   Updated: 2024/02/28 15:29:09 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_skipn(char *cmd, int fd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '-' && cmd[i + 1] == 'n')
			i++;
		else if (cmd[i] == 'n')
			i++;
		else if (cmd[i] == ' ')
		{
			while (cmd[i] == ' ')
				i++;
			if (cmd[i] != '-')
				break ;
		}
		else
			break ;
	}
	ft_putstr_fd(&cmd[i], fd);
}

void	ft_echo(char *cmd, int fd)
{
	int	i;

	i = 5;
	if (!cmd[i - 1])
		ft_putstr_fd("\n", fd);
	if (cmd[i] == '-' && cmd[i + 1] == 'n')
		ft_skipn(&cmd[i], fd);
	else
	{
		ft_putstr_fd(&cmd[i], fd);
		ft_putstr_fd("\n", fd);
	}
}
