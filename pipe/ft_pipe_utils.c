/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:05:35 by rodro             #+#    #+#             */
/*   Updated: 2024/03/19 16:58:50 by rofuente         ###   ########.fr       */
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

	while (*cmd != NULL)
	{
		aux = (*cmd)->next;
		free(cmd[0]->command);
		if (cmd[0]->built
			&& !ft_strnstr(cmd[0]->built, "exec", ft_strlen(cmd[0]->built))
			&& !ft_strnstr(cmd[0]->built, "Error", ft_strlen(cmd[0]->built)))
			free(cmd[0]->built);
		free(cmd[0]);
		*cmd = aux;
	}
	free(*cmd);
	*cmd = NULL;
}

int	ft_check_in(t_minishell *shell)
{
	if (shell->infile > 0)
		return (shell->infile);
	return (0);
}

int	ft_check_out(t_minishell *shell)
{
	if (shell->outfile > 1)
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
