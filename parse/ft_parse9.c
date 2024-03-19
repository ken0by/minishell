/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse9.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:50:00 by rofuente          #+#    #+#             */
/*   Updated: 2024/03/19 19:36:09 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_command	*ft_del_node(t_command *aux)
{
	t_command	*cmd;

	cmd = aux;
	if (aux->next)
		cmd = aux->next;
	else
		cmd = NULL;
	if (aux)
	{
		free(aux->command);
		free(aux);
	}
	return (cmd);
}

t_command	*ft_out_chech(t_command *cmd)
{
	if (ft_strchr(cmd->command, '>'))
		cmd = ft_del_node(cmd);
	if (ft_strchr(cmd->command, '>'))
		cmd = ft_del_node(cmd);
	if (cmd->next != NULL)
		return (ft_del_node(cmd));
	return (ft_del_node(cmd));
}

void	ft_unlink(char **cmd)
{
	int	i;

	if (!cmd || !cmd[0])
		return ;
	i = -1;
	while (cmd[++i])
		unlink(cmd[i]);
}

char	**ft_take_one(char **cmd)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	while (cmd[i])
		i++;
	i--;
	tmp = malloc(sizeof(char *) * 3);
	tmp[0] = malloc(sizeof(char) * (ft_strlen(cmd[0]) + 1));
	tmp[1] = malloc(sizeof(char) * (ft_strlen(cmd[i]) + 1));
	j = -1;
	while (cmd[0][++j])
		tmp[0][j] = cmd[0][j];
	tmp[0][j] = '\0';
	j = -1;
	while (cmd[i][++j])
		tmp[1][j] = cmd[i][j];
	tmp[1][j] = '\0';
	tmp[2] = NULL;
	ft_free_mtx(cmd);
	return (tmp);
}

int	ft_checker(t_command *cmd)
{
	if(cmd->command[0] == '<' && cmd->command[1] == '<' && cmd->next->command[0] == '|')
		return (ft_printf("syntax error near unexpected token `|'\n"),
		g_code_error = 258, 1);
	else if(cmd->command[0] == '<' && cmd->next->command[0] == '|')
		return (ft_printf("syntax error near unexpected token `newline'\n"),
		g_code_error = 258, 1);
	if (ft_strchr(cmd->command, '<')
		&& ft_strchr(cmd->next->command, '|')
		&& ft_strchr(cmd->next->next->command, '>'))
		return (ft_printf("syntax error near unexpected token `|'\n"),
			g_code_error = 258, 1);
	else if (ft_strchr(cmd->command, '>')
		&& ft_strchr(cmd->next->command, '|')
		&& ft_strchr(cmd->next->next->command, '<'))
		return (ft_printf("syntax error near unexpected token `<'\n"),
			g_code_error = 258, 1);
	return (0);
}
