/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:05:35 by rodro             #+#    #+#             */
/*   Updated: 2024/01/10 14:59:55 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_redir(t_pipe *pipe, t_minishell *shell)
{
	if (pipe->argv[0] == '>' && pipe->argv[1] == '>')
		shell->outfile = ft_file(pipe->next, 3, shell);
	else if (pipe->argv[0] == '<' && pipe->argv[1] == '<')
		shell->infile = ft_file(pipe->next, 2, shell);
	else if (pipe->argv[0] == '>')
		 shell->outfile = ft_file(pipe->next, 1, shell);
	else if (pipe->argv[0] == '<')
		shell->infile = ft_file(pipe->next, 0, shell);
	pipe->redir = 1;
}

void	ft_check_exp(t_pipe *pipe, t_minishell *shell)
{
	//int	i;

	if (pipe->argv[0] == '$' && pipe->argv[1] == '?')
		ft_exp_code(pipe, shell);
	if (pipe->argv[0] == '$' && pipe->argv[1] != '?')
		pipe->argv = ft_exp(pipe->argv, shell);
	/* i = ft_quotes(pipe->argv);
	if ((i != 2 && pipe->argv[0] == '$' && pipe->argv[1] == '?')
		|| !ft_strncmp(pipe->argv, "'$?'", 4)
		|| (pipe->argv[0] == '"' && pipe->argv[1] == '$'))
		pipe->exp = 2;
	else if ((i == 3 && pipe->argv[0] == '$') || (i != 2 && pipe->argv[0] == '$')
		|| !ft_strncmp(pipe->argv, "'$", 2))
		pipe->exp = 1; */
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
