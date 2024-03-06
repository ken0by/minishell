/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:03:29 by rofuente          #+#    #+#             */
/*   Updated: 2024/03/06 15:56:26 by rofuente         ###   ########.fr       */
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

	i = 0;
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

static void	ft_free_exit(t_command **cmd, t_minishell **shell)
{
	ft_free_cmd(cmd);
	free((*shell)->cmd_line);
	if ((*shell)->path)
		free((*shell)->path);
	if ((*shell)->pwd)
		free((*shell)->pwd);
	if ((*shell)->oldpwd)
		free((*shell)->oldpwd);
	if ((*shell)->root)
		free((*shell)->root);
	if ((*shell)->env && (*shell)->env[0])
		ft_free_mtx((*shell)->env);
	if ((*shell)->inf)
		free((*shell)->inf);
	if ((*shell)->here)
		free((*shell)->here);
	if ((*shell)->del && (*shell)->del[0])
		ft_free_mtx((*shell)->del);
	*shell = NULL;
}

void	ft_exit_code(t_command *cmd, t_minishell *shell)
{
	char	**tmp;

	tmp = ft_split(cmd->command, ' ');
	if (shell->shlvl == 1)
	{
		if (tmp[1])
			exit (ft_code_nb(shell->cmd_line));
		else
		{
			ft_printf("exit\n");
			exit (0);
		}
	}
	else
	{
		g_code_error = ft_code_nb(shell->cmd_line);
		ft_shell_down(shell);
	}
}
