/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:03:29 by rofuente          #+#    #+#             */
/*   Updated: 2024/01/24 11:41:38 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_flag(int flag, char *nb)
{
	if (!flag && !nb)
		return (ft_printf("exit\n"), 0);
	if (!flag)
		return (ft_printf("exit\n"), ft_atoi(nb));
	else
		return (ft_printf("exit: numeric argument required\n"), 255);
}

static int	ft_code_nb(char *str)
{
	int	i;
	int	j;
	int	flag;

	i = -1;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[++i])
		if (i == 4)
			break ;
	if (i == 4 && str[i])
	{
		j = 0;
		flag = 0;
		while (str[++i])
		{
			if (str[i] >= '0' && str[i] <= '9')
				j++;
			else if (str[i] != ' ' && str[i] != '\t')
				flag = 1;
		}
		return (ft_flag(flag, ft_cp_nb(str, j)));
	}
	ft_printf("exit\n");
	return (0);
}

void	ft_exit_code(t_minishell *shell)
{
	if (shell->shlvl == 1)
		exit (ft_code_nb(shell->cmd_line));
	else
	{
		g_code_error = ft_code_nb(shell->cmd_line);
		ft_shell_down(shell);
	}
}
