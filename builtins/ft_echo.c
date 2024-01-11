/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:37:07 by dmonjas-          #+#    #+#             */
/*   Updated: 2024/01/11 12:40:49 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_command *cmd)
{
	char	**comm;
	int		i;

	i = 0;
	comm = ft_split(cmd->command, ' ');
	if (comm[1][0] == '-' && comm[1][1] == 'n')
	{
		i = 8;
		ft_printf("%s", &cmd->command[i]);
		ft_printf("%%");
		ft_printf("\n");		//estas dos lineas no hacen falta
	}
	else
	{
		i = 5;
		ft_printf("%s", &cmd->command[i]);
		printf("\n");
	}
	exit (0);
}
