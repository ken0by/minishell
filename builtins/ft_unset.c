/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:38:16 by rofuente          #+#    #+#             */
/*   Updated: 2024/01/25 16:03:46 by rofuente         ###   ########.fr       */
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
			ft_putstr_fd("unset", STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putstr_fd("`", STDERR_FILENO);
			ft_putstr_fd(str, STDERR_FILENO);
			ft_putstr_fd("'", STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putstr_fd("not a valid identifier", STDERR_FILENO);
			ft_putstr_fd("\n", STDERR_FILENO);
			return (1);
		}
	}
	return (0);
}

static char	**ft_malloc(t_minishell *shell, char *var)
{
	int		i;
	int		j;
	char	**aux;

	i = -1;
	j = 0;
	while (shell->env[++i])
		if (!ft_strncmp(shell->env[i], var, ft_strlen(var)))
			j = 1;
	if (j == 1)
		aux = malloc(sizeof(char *) * i);
	else
		return (NULL);
	if (!aux)
		return (NULL);
	return (aux);
}

void	ft_unset(char *cmd, t_minishell *shell)
{
	int		i;
	int		j;
	char	**aux;
	char	**tmp;

	tmp = ft_split(cmd, ' ');
	if (ft_no_var(tmp[1]))
		return ;
	aux = ft_malloc(shell, tmp[1]);
	if (!aux)
		return ;
	i = -1;
	j = 0;
	while (shell->env[++i])
	{
		if (ft_strncmp(shell->env[i], tmp[1], ft_strlen(tmp[1])))
		{
			aux[j] = ft_strdup(shell->env[i]);
			j++;
		}
	}
	aux[j] = NULL;
	ft_free_mtx(shell->env);
	free(tmp);
	shell->env = aux;
}
