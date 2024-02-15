/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:05:35 by rodro             #+#    #+#             */
/*   Updated: 2024/02/15 15:43:19 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_peror(char *var, char *s)
{
	ft_putstr_fd(var, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	perror(s);
	g_code_error = 127;
	exit (1);
}

void	ft_free_cmd(t_command **cmd)
{
	t_command	*aux;

	while (*cmd)
	{
		aux = (*cmd)->next;
		free(cmd[0]->command);
		free(cmd[0]->built);
		free(cmd[0]->infile);
		free(cmd[0]->outfile);
		free (*cmd);
		*cmd = aux;
	}
	cmd = NULL;
}

int	ft_check_in(t_minishell *shell)
{
	if (shell->infile)
		return (shell->infile);
	return (0);
}

int	ft_check_out(t_minishell *shell)
{
	if (shell->outfile)
		return (shell->outfile);
	return (1);
}

int	ft_lst_size(t_command *lst)
{
	t_command	*aux;
	int			i;

	aux = lst;
	i = 0;
	while (aux)
	{
		i++;
		aux = aux->next;
	}
	return (i);
}
