/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse9.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodro <rodro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:50:00 by rofuente          #+#    #+#             */
/*   Updated: 2024/03/02 17:31:23 by rodro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_command	*ft_out_chech(t_command *cmd)
{
	if (ft_strchr(cmd->command, '>'))
		cmd = cmd->next;
	if (ft_strchr(cmd->command, '>'))
		cmd = cmd->next;
	if (cmd->next != NULL)
		return (cmd->next);
	return (NULL);
}

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

void	ft_unlink(char **cmd)
{
	int	i;

	if (!cmd || !cmd[0])
		return ;
	i = 0;
	while (cmd[++i])
		unlink(cmd[i]);
	ft_free_mtx(cmd);
	cmd = NULL;
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
