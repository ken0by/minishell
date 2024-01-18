/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:05:35 by rodro             #+#    #+#             */
/*   Updated: 2024/01/18 12:49:06 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_peror(char *var, char *s)
{
	ft_putstr_fd(var, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	perror(s);
	code_error = 127;
	exit (1);
}

void	ft_free_cmd(t_command **cmd)
{
	t_command	*aux;

	while (*cmd)
	{
		aux = (*cmd)->next;
		free (*cmd);
		*cmd = aux;
	}
	cmd = NULL;
}
