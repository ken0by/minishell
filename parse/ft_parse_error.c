/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 09:50:47 by dmonjas-          #+#    #+#             */
/*   Updated: 2024/01/10 14:48:35 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_car(void)
{
	ft_printf("Error in <, >, |\n");
	exit (0);
}

void	ft_error_cmd(void)
{
	ft_printf("Error readline\n");
	exit (0);
}

void	ft_error_arguments(void)
{
	ft_printf("This program doesn't take arguments\n");
	exit (0);
}

void	ft_error_path(int i)
{
	if (i == 1)
		ft_printf("Error: can't find path\n");
	if (i == 2)
		ft_printf("Error: can't find pwd\n");
	if (i == 3)
		ft_printf("Error: can't find oldpwd\n");
	exit (0);
}
