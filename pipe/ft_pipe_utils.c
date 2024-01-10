/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:05:35 by rodro             #+#    #+#             */
/*   Updated: 2024/01/10 17:30:14 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_redir(t_pipe *pipe, t_minishell *shell)
{
	if (pipe->argv[0] == '>' && pipe->argv[1] == '>')
		shell->outfile = ft_file(pipe->next, 3);
	else if (pipe->argv[0] == '<' && pipe->argv[1] == '<')
		shell->infile = ft_file(pipe->next, 2);
	else if (pipe->argv[0] == '>')
		 shell->outfile = ft_file(pipe->next, 1);
	else if (pipe->argv[0] == '<')
		shell->infile = ft_file(pipe->next, 0);
	pipe->redir = 1;
}

int	ft_isbuilt(char *cmd)
{
	if  (!ft_strncmp(cmd, "echo", ft_strlen(cmd))
		&& ft_strlen(cmd) > 0)
		return (1);
	if  (!ft_strncmp(cmd, "cd", ft_strlen(cmd))
		&& ft_strlen(cmd) > 0)
		return (1);
	if  (!ft_strncmp(cmd, "pwd", ft_strlen(cmd))
		&& ft_strlen(cmd) > 0)
		return (1);
	if  (!ft_strncmp(cmd, "export", ft_strlen(cmd))
		&& ft_strlen(cmd) > 0)
		return (1);
	if  (!ft_strncmp(cmd, "unset", ft_strlen(cmd))
		&& ft_strlen(cmd) > 0)
		return (1);
	if  (!ft_strncmp(cmd, "env", ft_strlen(cmd))
		&& ft_strlen(cmd) > 0)
		return (1);
	return (0);
}

int	ft_check_built(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)))
		return (1);
	if  (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
		return (1);
	if  (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
		return (1);
	if  (!ft_strncmp(cmd, "export ", ft_strlen(cmd)))
		return (1);
	if  (!ft_strncmp(cmd, "unset ", ft_strlen(cmd)))
		return (1);
	if  (!ft_strncmp(cmd, "env", ft_strlen(cmd)))
		return (1);
	return (0);
}

void	ft_free_pipe(t_pipe **pipe)
{
	t_pipe	*aux;

	while (*pipe)
	{
		aux = (*pipe)->next;
		free(*pipe);
		*pipe = aux;
	}
	pipe = NULL;
}
