/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:37:07 by dmonjas-          #+#    #+#             */
/*   Updated: 2024/02/21 16:22:15 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char *cmd, int fd)
{
	int	i;

	i = 5;
	if (!cmd[i - 1])
		ft_putstr_fd("\n", fd);
	if (cmd[i] == '-' && cmd[i + 1] == 'n')
		ft_putstr_fd(&cmd[i + 3], fd);
	else
	{
		ft_putstr_fd(&cmd[i], fd);
		ft_putstr_fd("\n", fd);
	}
}
