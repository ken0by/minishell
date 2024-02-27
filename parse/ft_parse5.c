/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmonjas- <dmonjas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 12:18:39 by dmonjas-          #+#    #+#             */
/*   Updated: 2024/02/27 10:54:39 by dmonjas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command	*ft_del_node(t_command *aux)
{
	t_command	*cmd;

	cmd = aux;
	if (aux->next->next)
		cmd = aux->next->next;
	else
		cmd = NULL;
	if (aux)
	{
		free (aux->next->command);
		free(aux->next);
		aux->next = NULL;
		free (aux->command);
		free(aux);
	}
	return (cmd);
}

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


t_command	*ft_inout(t_command **cmd, t_minishell *shell)
{
	t_command	*aux;

	aux = *cmd;
	while (aux)
	{
		if (ft_strchr(aux->command, '<') && aux->dollar == 0)
		{
			if (aux->next->next->command[0] == '<')
				aux = ft_del_node(aux);
			shell->inf = ft_strdup(aux->next->command);
			shell->infile = ft_inf(aux->next->command, aux->command, shell);
			*cmd = ft_del_node(aux);
			aux = *cmd;
		}
		if (aux->next && (ft_strchr(aux->next->command, '>') && aux->next->dollar == 0))
		{
			//shell->out = ft_cp_out(aux->next);
			shell->outfile = ft_open(aux->next->next->command, aux->next->command, shell);
			aux->next = NULL;
			break ;
		}
		aux = aux->next; 
	}
	return(*cmd);
}
/*
static void	ft_lstclear_shell(t_command **lst)
{
	t_command	*aux;
	t_command	*aux_next;

	aux = *lst;
	while (aux)
	{
		aux_next = aux->next;
		free(aux);
		aux = aux_next;
	}
	*lst = NULL;
}

 char	*ft_cp_out(t_command *aux)
{
	char		*out;
	t_command	*aux2;

	aux2 = aux;
	aux = aux->next;
	while (aux)
	{
		out = ft_strjoin(out, aux->command);
		aux = aux->next;
	}
	ft_lstclear_shell(&aux2);
	return (out);
} */
