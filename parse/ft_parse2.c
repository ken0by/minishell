/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:12:11 by dmonjas-          #+#    #+#             */
/*   Updated: 2024/01/29 15:30:02 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_simple(char *str, char **line, int *space)
{
	int	i;
	int	j;
	int	k;

	i = 1;
	k = 1;
	j = 0;
	while (str[i] != 39)
		i++;
	line[0] = malloc(sizeof(char) + i);
	while (j < i - 1)
	{
		line[0][j] = str[k];
		j++;
		k++;
	}
	line[0][j] = '\0';
	if (str[i + 1] != ' ')
		*space = 1;
	return (i);
}

static int	ft_doble(char *str, char **line, int *space)
{
	int	i;
	int	j;
	int	k;

	i = 1;
	k = 1;
	j = 0;
	while (str[i] != '"')
		i++;
	line[0] = malloc(sizeof(char) + i);
	while (j < i - 1)
	{
		line[0][j] = str[k];
		j++;
		k++;
	}
	line[0][j] = '\0';
	if (str[i + 1] != ' ')
		*space = 1;
	return (i);
}

static int	ft_num(char *str, char **line, int *space)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == '|' || str[i] == '"' || str[i] == 39)
			break ;
		i++;
	}
	line[0] = malloc(sizeof(char) * i + 1);
	while (j < i)
	{
		line[0][j] = str[j];
		j++;
	}
	line[0][j] = '\0';
	if (str[i] != ' ')
		*space = 1;
	return (i - 1);
}

static int	ft_car(char *str, char **line)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (str[0] == str[1] && str[1] == str[2])
		ft_error_car();
	if (str[0] == '|' && str[1] == '|')
		ft_error_car();
	if (str[0] == str[1])
		i = 2;
	line[0] = malloc(sizeof(char) * i + 1);
	while (j < i)
	{
		line[0][j] = str[j];
		j++;
	}
	line[0][j] = '\0';
	return (i - 1);
}

t_command	*ft_take_cmd(t_command **cmd, char *line, char *cmd_line)
{
	int	i;
	int	space;

	i = -1;
	while (cmd_line[++i])
	{
		if (cmd_line[i] != ' ')
		{
			space = 0;
			if (cmd_line[i] == 39)
				i += ft_simple(&cmd_line[i], &line, &space);
			else if (cmd_line[i] == '"')
				i += ft_doble(&cmd_line[i], &line, &space);
			else if (cmd_line[i] == '<')
				i += ft_car(&cmd_line[i], &line);
			else if (cmd_line[i] == '>')
				i += ft_car(&cmd_line[i], &line);
			else if (cmd_line[i] == '|')
				i += ft_car(&cmd_line[i], &line);
			else
				i += ft_num(&cmd_line[i], &line, &space);
			if (line[0] != '\0')
			{
				ft_lstadd_back_shell(cmd,
					ft_lst_first(ft_skip_space(line), cmd_line[i], &space));
			}
			free (line);
		}
	}
	return (*cmd);
}
