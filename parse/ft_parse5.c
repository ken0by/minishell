/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 12:18:39 by dmonjas-          #+#    #+#             */
/*   Updated: 2024/02/28 17:47:18 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count(char *cmd, char c)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (cmd[++i])
	{
		if (cmd[i] == c)
			count++;
	}
	return (count);
}

static int	ft_inf(char *infile, char *command, t_minishell *shell)
{
	int	fd;
	int	x;

	fd = 0;
	x = ft_count(command, '<');
	if (shell->infile)
		close(shell->infile);
	if (x == 1)
	{
		fd = open(infile, O_RDONLY, 0644);
		if (fd > 0 && access(infile, R_OK) < 0)
			return (ft_err_msg("Error opening infile"), 0);
	}
	if (x == 2)
	{
		fd = open(infile, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (fd > 0 && access(infile, W_OK | R_OK) < 0)
			return (ft_err_msg("Error opening heredoc"), 0);
		shell->heredoc = 1;
		shell->here = ft_strdup(infile);
		shell->infile = ft_here(infile, fd, shell);
	}
	if (fd < 0)
		return (ft_err_msg("No such file or directory"), 0);
	return (fd);
}

static int	ft_open(char *outfile, char *command, t_minishell *shell)
{
	int	fd;
	int	x;

	fd = 0;
	x = ft_count(command, '>');
	if (shell->outfile)
		close(shell->outfile);
	if (x == 1)
	{
		fd = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (fd > 0 && access(outfile, W_OK | R_OK) < 0)
			return (ft_err_msg("Error opening outfile"), 0);
	}
	if (x == 2)
	{
		fd = open(outfile, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
		if (fd > 0 && access(outfile, W_OK | R_OK) < 0)
			return (ft_err_msg("Error opening append"), 0);
	}
	if (fd < 0)
		return (ft_err_msg("No such file or directory"), 0);
	return (fd);
}

static t_command	*ft_check_first(t_command *cmd, t_minishell *shell)
{
	if (ft_strchr(cmd->command, '<') && cmd->dollar == 0)
	{
		if (shell->inf == NULL)
			free (shell->inf);
		shell->inf = ft_strdup(cmd->next->command);
		shell->infile = ft_inf(cmd->next->command, cmd->command, shell);
		return (ft_del_node(cmd));
	}
	return (cmd);
}

t_command	*ft_inout(t_command **cmd, t_minishell *shell)
{
	t_command	*aux;

	*cmd = ft_check_first(*cmd, shell);
	aux = *cmd;
	while (aux)
	{
		if (!aux->next)
			break ;
		if (ft_strchr(aux->next->command, '<') && aux->next->dollar == 0)
		{
			if (shell->inf == NULL)
				free (shell->inf);
			shell->inf = ft_strdup(aux->next->next->command);
			shell->infile = ft_inf(aux->next->next->command, aux->next->command, shell);
			aux->next = ft_del_node(aux->next);
		}
		else if (aux->next && (ft_strchr(aux->next->command, '>') && aux->next->dollar == 0))
		{
			shell->outfile = ft_open(aux->next->next->command, aux->next->command, shell);
			aux->next = ft_out_chech(aux->next);
		}
		else
			aux = aux->next;
	}
	return(*cmd);
}
