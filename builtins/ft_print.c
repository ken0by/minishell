/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:26:57 by rofuente          #+#    #+#             */
/*   Updated: 2024/03/27 12:01:20 by rofuente         ###   ########.fr       */
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
		if (ft_contain(shell->env[i], '='))
		{
			ft_putstr_fd(shell->env[i], fd);
			ft_putstr_fd("\n", fd);
		}
	}
}

static void	ft_env_print(char *str, int fd)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
		{
			ft_putchar_fd(str[i], fd);
			ft_putstr_fd("\"", fd);
		}
		else
			ft_putchar_fd(str[i], fd);
	}
	if (ft_contain(str, '='))
		ft_putstr_fd("\"", fd);
}

void	ft_print_ordenv(char **env, int fd)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		ft_putstr_fd("declare -x ", fd);
		ft_env_print(env[i], fd);
		ft_putstr_fd("\n", fd);
	}
}
