/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:12:11 by dmonjas-          #+#    #+#             */
/*   Updated: 2024/02/21 17:53:35 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_simple(char *str, char **line, int *space, int quote)
{
	int	i;
	int	j;
	int	k;

	i = 1;
	k = 1;
	j = 0;
	while (str[i] != quote)
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

static int	ft_closequote(char *str)
{
	int	i;
	int	j;
	int	k;

	i = 1;
	k = 1;
	if (str[0] == 39)
		j = 39;
	else
		j = 34;
	while (str[i])
	{
		if (str[i] == j)
			k++;
		i++;
	}
	if (k % 2 == 0)
		return (1);
	g_code_error = 1;
	return (0);
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
			if (cmd_line[i] == 39 || cmd_line[i] == 34)
			{
				if (!ft_closequote(&cmd_line[i]))
					return (ft_printf("Please close quotes!\n"), NULL);
				i += ft_simple(&cmd_line[i], &line, &space, cmd_line[i]);
			}
			else if (cmd_line[i] == '<'
				|| cmd_line[i] == '>' || cmd_line[i] == '|')
				i += ft_car(&cmd_line[i], &line);
			else
				i += ft_num(&cmd_line[i], &line, &space);
			ft_lstadd_back_shell(cmd,
				ft_lst_first(ft_skip_space(line), cmd_line[i], &space));
		}
	}
	return (*cmd);
}
