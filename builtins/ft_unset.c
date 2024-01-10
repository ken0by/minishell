/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmonjas- <dmonjas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:38:16 by rofuente          #+#    #+#             */
/*   Updated: 2023/12/13 17:37:00 by dmonjas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_no_var(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
		{
			ft_egro("unset", str);
			return (1);
		}
	}
	return (0);
}

static char	**ft_malloc(t_minishell *shell, t_command *cmd)
{
	int		i;
	int		j;
	char	**aux;

	i = -1;
	j = 0;
	while (shell->env[++i])
		if (!ft_strncmp(shell->env[i], cmd->argv[1], ft_strlen(cmd->argv[1])))
			j = 1;
	if (j == 1)
		aux = malloc(sizeof(char *) * i);
	else
		return (NULL);
	if (!aux)
		return (NULL);
	return (aux);
}

void	ft_unset(t_command *cmd, t_minishell *shell)
{
	int		i;
	int		j;
	char	**aux;

	if (ft_no_var(cmd->argv[1]))
		return ;
	aux = ft_malloc(shell, cmd);
	if (!aux)
		return ;
	i = -1;
	j = 0;
	while (shell->env[++i])
	{
		if (ft_strncmp(shell->env[i], cmd->argv[1], ft_strlen(cmd->argv[1])))
		{
			aux[j] = ft_strdup(shell->env[i]);
			j++;
		}
	}
	aux[j] = NULL;
	ft_free_mtx(shell->env);
	shell->env = aux;
}
