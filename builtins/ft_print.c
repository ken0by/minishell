/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmonjas- <dmonjas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:26:57 by rofuente          #+#    #+#             */
/*   Updated: 2023/12/13 17:36:58 by dmonjas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_pwd(t_minishell *shell)
{
	ft_printf("%s\n", shell->pwd);
}

void	ft_print_env(t_minishell *shell)
{
	int	i;

	i = -1;
	while (shell->env[++i])
		ft_printf("%s\n", shell->env[i]);
}
