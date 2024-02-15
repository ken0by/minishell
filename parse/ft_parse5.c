/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodro <rodro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 12:18:39 by dmonjas-          #+#    #+#             */
/*   Updated: 2024/02/15 12:49:24 by rodro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_built(char *cmd)
{
	if (ft_strnstr(cmd, "echo", ft_strlen(cmd))
		&& ft_strlen(cmd) > 0)
		return (ft_spr(ft_split(cmd, ' '), "echo"));
	else if (ft_strnstr(cmd, "cd", ft_strlen(cmd))
		&& ft_strlen(cmd) > 0)
		return (ft_spr(ft_split(cmd, ' '), "cd"));
	else if (ft_strnstr(cmd, "pwd", ft_strlen(cmd))
		&& ft_strlen(cmd) > 0)
		return (ft_spr(ft_split(cmd, ' '), "pwd"));
	else if (ft_strnstr(cmd, "export", ft_strlen(cmd))
		&& ft_strlen(cmd) > 0)
		return (ft_spr(ft_split(cmd, ' '), "export"));
	else if (ft_strnstr(cmd, "unset", ft_strlen(cmd))
		&& ft_strlen(cmd) > 0)
		return (ft_spr(ft_split(cmd, ' '), "unset"));
	else if (ft_strnstr(cmd, "env", ft_strlen(cmd))
		&& ft_strlen(cmd) > 0)
		return (ft_spr(ft_split(cmd, ' '), "env"));
	return ("exec");
}

char	*ft_take_com(char *command)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = ft_take_size(command);
	i = -1;
	j = 0;
	while (command[++i])
	{
		if (command[i] == '>')
			break ;
		if (command[i] == '<')
		{
			i++;
			while (command[i] == ' ' && command[i + 1] == ' ')
				i++;
		}
		else
		{
			tmp[j] = command[i];
			j++;
		}
	}
	tmp[j] = '\0';
	return (free (command), tmp);
}

static int	ft_open(char *outfile, int x, t_minishell *shell)
{
	int	fd;

	fd = 0;
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

void	ft_inout(t_command **cmd, t_minishell *shell)
{
	t_command	*aux;

	aux = *cmd;
	while (aux)
	{
		if (ft_strchr(aux->command, '<'))
		{
			aux->inf = ft_count(aux->command, '<');
			shell->infile = ft_inf(aux->next->command, aux->inf, shell);
		}
		if (ft_strchr(aux->command, '>'))
		{
			aux->out = ft_count(aux->command, '>');
			shell->outfile = ft_open(aux->next->command, aux->out, shell);
		}
		aux = aux->next;
	}
}
