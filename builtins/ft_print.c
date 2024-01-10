/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:26:57 by rofuente          #+#    #+#             */
/*   Updated: 2024/01/10 18:24:35 by rofuente         ###   ########.fr       */
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

void	ft_print_ordenv(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
}
