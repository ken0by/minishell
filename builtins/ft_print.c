/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:26:57 by rofuente          #+#    #+#             */
/*   Updated: 2024/01/17 15:55:02 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_pwd(t_minishell *shell, int fd)
{
	ft_putstr_fd(shell->pwd, fd);
	ft_putstr_fd("\n", fd);
}

void	ft_print_env(t_minishell *shell, int fd)
{
	int	i;

	i = -1;
	while (shell->env[++i])
	{
		ft_putstr_fd(shell->env[i], fd);
		ft_putstr_fd("\n", fd);
	}
}

void	ft_print_ordenv(char **env, int fd)
{
	int	i;
	int	j;

	i = -1;
	while (env[++i])
	{
		ft_putstr_fd("declare -x ", fd);
		j = -1;
		while (env[i][++j])
		{
			if (env[i][j] == '=')
			{
				ft_putchar_fd(env[i][j], fd);
				ft_putstr_fd("\"", fd);
			}
			else
				ft_putchar_fd(env[i][j], fd);
		}
		ft_putstr_fd("\"\n", fd);
	}
}
