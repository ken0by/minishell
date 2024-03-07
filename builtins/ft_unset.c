/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodro <rodro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:38:16 by rofuente          #+#    #+#             */
/*   Updated: 2024/03/07 16:14:26 by rodro            ###   ########.fr       */
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

static int	ft_if_var(char **tmp, char *env)
{
	int	k;
	int	i;

	k = 0;
	i = 0;
	while (tmp[++k])
	{
		if (ft_strncmp(env, tmp[k], ft_strlen(tmp[k])))
			i++;
	}
	if (i == (k - 1))
		return (1);
	return (0);
}

static char	**ft_malloc(t_minishell *shell, char **var)
{
	int		i;
	int		j;
	char	**aux;

	i = -1;
	j = 0;
	while (shell->env[++i])
	{
		if (ft_if_var(var, shell->env[i]))
			j++;
	}
	if (j)
		aux = malloc(sizeof(char *) * (j + 1));
	else
		return (NULL);
	if (!aux)
		return (NULL);
	return (aux);
}

static char	**ft_delete_vars(char **tmp, t_minishell *shell)
{
	int		i;
	int		j;
	char	**aux;

	aux = ft_malloc(shell, tmp);
	if (!aux)
		return (NULL);
	i = -1;
	j = 0;
	while (shell->env[++i])
	{
		if (ft_if_var(tmp, shell->env[i]))
		{
			aux[j] = ft_strdup(shell->env[i]);
			j++;
		}
	}
	aux[j] = NULL;
	return (aux);
}

void	ft_unset(char *cmd, t_minishell *shell)
{
	char	**aux;
	char	**tmp;

	tmp = ft_split(cmd, ' ');
	if (ft_no_var(tmp[1]))
		return ;
	aux = ft_delete_vars(tmp, shell);
	if (!aux)
		return ;
	ft_free_mtx(shell->env);
	free(tmp);
	shell->env = aux;
}
