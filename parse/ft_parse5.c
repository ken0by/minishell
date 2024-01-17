/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 12:18:39 by dmonjas-          #+#    #+#             */
/*   Updated: 2024/01/16 17:25:20 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_built(t_command *cmd)
{
	if  (ft_strnstr(cmd->command, "echo", ft_strlen(cmd->command))
		&& ft_strlen(cmd->command) > 0)
		return (ft_spr(ft_strnstr(cmd->command, "echo", ft_strlen(cmd->command))));
	else if  (ft_strnstr(cmd->command, "cd", ft_strlen(cmd->command))
		&& ft_strlen(cmd->command) > 0)
		return (ft_spr(ft_strnstr(cmd->command, "cd", ft_strlen(cmd->command))));
	else if  (ft_strnstr(cmd->command, "pwd", ft_strlen(cmd->command))
		&& ft_strlen(cmd->command) > 0)
		return (ft_spr(ft_strnstr(cmd->command, "pwd", ft_strlen(cmd->command))));
	else if  (ft_strnstr(cmd->command, "export", ft_strlen(cmd->command))
		&& ft_strlen(cmd->command) > 0)
		return (ft_spr(ft_strnstr(cmd->command, "export", ft_strlen(cmd->command))));
	else if  (ft_strnstr(cmd->command, "unset", ft_strlen(cmd->command))
		&& ft_strlen(cmd->command) > 0)
		return (ft_spr(ft_strnstr(cmd->command, "unset", ft_strlen(cmd->command))));
	else if  (ft_strnstr(cmd->command, "env", ft_strlen(cmd->command))
		&& ft_strlen(cmd->command) > 0)
		return (ft_spr(ft_strnstr(cmd->command, "env", ft_strlen(cmd->command))));
	return ("exec");
}
static char	*ft_take_com(char *command, int size_inf, int size_out)
{
	if (size_inf != 0)
		size_inf += 1;
	if (size_out == -1)
		size_out = ft_strlen(command);
	while (command[size_inf] == ' ' || command[size_inf] == '<')
		size_inf++;
	while (command[size_out] == ' ' || command[size_out] == '>')
		size_out--;
	command = ft_substr(command, size_inf, (size_out - size_inf) + 1);
	return (command);
}

static int	ft_open(char *outfile, int x)
{
	int	fd;

	fd = 0;
	if (x == 1)
	{
		fd = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (access(outfile, W_OK | R_OK) < 0)
			ft_err_msg("Error opening outfile\n");
	}
	if (x == 2)
	{
		fd = open(outfile, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
		if (access(outfile, W_OK | R_OK) < 0)
			ft_err_msg("Error opening append\n");
	}
	if (fd < 0)
		ft_err_msg("Error opening file\n");
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

t_command	*ft_inout(t_command **cmd, t_minishell *shell)
{
	t_command	*aux;

	aux = *cmd;
	while (aux)
	{
		if (ft_strchr(aux->command, '<'))
		{
			aux->inf = ft_count(aux->command, '<');
			aux->infile = ft_substr(aux->command, ft_strchr_out(aux->command,'<'),
				ft_strlen(ft_strchr(aux->command, '<')));
			shell->infile = ft_inf(aux->infile, aux->inf);
		}
		if (ft_strchr(aux->command, '>'))
		{
			aux->out = ft_count(aux->command, '>');
			aux->outfile = ft_substr(aux->command, ft_strchr_out(aux->command,'>'),
				ft_strlen(ft_strchr(aux->command, '>')));
			shell->outfile = ft_open(aux->outfile, aux->out);
		}
		aux->built = ft_built(aux);
		aux->command = ft_take_com(aux->command, ft_strchr_in(aux->command, '<'),
			ft_strchr_out(aux->command,'>') - 1);
		aux = aux->next;
	}
	return (*cmd);
}
