/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 12:18:39 by dmonjas-          #+#    #+#             */
/*   Updated: 2024/01/24 12:45:23 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_built(char *cmd)
{
	if (ft_strnstr(cmd, "echo", ft_strlen(cmd))
		&& ft_strlen(cmd) > 0)
		return (ft_spr(ft_strnstr(cmd, "echo", ft_strlen(cmd))));
	else if (ft_strnstr(cmd, "cd", ft_strlen(cmd))
		&& ft_strlen(cmd) > 0)
		return (ft_spr(ft_strnstr(cmd, "cd", ft_strlen(cmd))));
	else if (ft_strnstr(cmd, "pwd", ft_strlen(cmd))
		&& ft_strlen(cmd) > 0)
		return (ft_spr(ft_strnstr(cmd, "pwd", ft_strlen(cmd))));
	else if (ft_strnstr(cmd, "export", ft_strlen(cmd))
		&& ft_strlen(cmd) > 0)
		return (ft_spr(ft_strnstr(cmd, "export", ft_strlen(cmd))));
	else if (ft_strnstr(cmd, "unset", ft_strlen(cmd))
		&& ft_strlen(cmd) > 0)
		return (ft_spr(ft_strnstr(cmd, "unset", ft_strlen(cmd))));
	else if (ft_strnstr(cmd, "env", ft_strlen(cmd))
		&& ft_strlen(cmd) > 0)
		return (ft_spr(ft_strnstr(cmd, "env", ft_strlen(cmd))));
	return ("exec");
}

static char	*ft_take_com(char *command)
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
	free (command);
	return (tmp);
}

static int	ft_open(char *outfile, int x)
{
	int	fd;

	fd = 0;
	if (x == 1)
	{
		fd = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (fd > 0 && access(outfile, W_OK | R_OK) < 0)
			ft_err_msg("Error opening outfile");
	}
	if (x == 2)
	{
		fd = open(outfile, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
		if (fd > 0 && access(outfile, W_OK | R_OK) < 0)
			ft_err_msg("Error opening append");
	}
	if (fd < 0)
		ft_err_msg("No such file or directory");
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
			aux->infile = ft_substr(aux->command,
					ft_strchr_out(aux->command, '<'),
					ft_space(aux->command, ft_strchr_out(aux->command, '<')));
			shell->infile = ft_inf(aux->infile, aux->inf, shell);
		}
		if (ft_strchr(aux->command, '>'))
		{
			aux->out = ft_count(aux->command, '>');
			aux->outfile = ft_substr(aux->command,
					ft_strchr_out(aux->command, '>'),
					ft_strlen(ft_strchr(aux->command, '>')));
			shell->outfile = ft_open(aux->outfile, aux->out);
		}
		aux->built = ft_built(aux->command);
		aux->command = ft_take_com(aux->command);
		aux = aux->next;
	}
}
