/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:26:57 by rofuente          #+#    #+#             */
/*   Updated: 2024/01/11 16:19:24 by rofuente         ###   ########.fr       */
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
	int	j;

	i = -1;
	while (env[++i])
	{
		printf("declare -x ");
		j = -1;
		while (env[i][++j])
		{
			if (env[i][j] == '=')
			{
				printf("%c", env[i][j]);
				printf("\"");
			}
			else
				printf("%c", env[i][j]);
		}
		printf("\"\n");
	}
}
