/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmonjas- <dmonjas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 12:18:39 by dmonjas-          #+#    #+#             */
/*   Updated: 2024/01/09 14:17:55 by dmonjas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_built(t_command *cmd)
{
	if  (ft_strnstr(cmd->command, "echo", ft_strlen(cmd->command))
		&& ft_strlen(cmd->command) > 0)
		return ("echo");
	else if  (ft_strnstr(cmd->command, "cd", ft_strlen(cmd->command))
		&& ft_strlen(cmd->command) > 0)
		return ("cd");
	else if  (ft_strnstr(cmd->command, "pwd", ft_strlen(cmd->command))
		&& ft_strlen(cmd->command) > 0)
		return ("pwd");
	else if  (ft_strnstr(cmd->command, "export", ft_strlen(cmd->command))
		&& ft_strlen(cmd->command) > 0)
		return ("export");
	else if  (ft_strnstr(cmd->command, "unset", ft_strlen(cmd->command))
		&& ft_strlen(cmd->command) > 0)
		return ("unset");
	else if  (ft_strnstr(cmd->command, "env", ft_strlen(cmd->command))
		&& ft_strlen(cmd->command) > 0)
		return ("env");
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

t_command	*ft_inout(t_command **cmd)
{
	t_command	*aux;
	int			size_inf;
	int			size_out;

	aux = *cmd;
	
	while (aux)
	{
		size_inf = 0;
		size_out = ft_strlen(aux->command);
		if (ft_strchr(aux->command, '<'))
		{
			size_inf = ft_strchr_in(aux->command, '<');
			aux->infile = ft_substr(aux->command, 0, size_inf);
		}
		if (ft_strchr(aux->command, '>'))
		{
			size_out = ft_strlen(ft_strchr(aux->command, '>'));
			aux->outfile = ft_substr(aux->command, ft_strchr_out(aux->command,'>'), size_out);
		}
		aux->built = ft_built(aux);
		aux->command = ft_take_com(aux->command, size_inf, ft_strchr_out(aux->command,'>') - 1);
		aux = aux->next;
	}
	return (*cmd);
}
