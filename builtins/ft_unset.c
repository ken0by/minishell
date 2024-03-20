/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:38:16 by rofuente          #+#    #+#             */
/*   Updated: 2024/03/20 17:27:18 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_no_var(char *str)
{
	int	i;

	if (!str || !str[0])
		return (1);
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

static int	ft_check_cpy(char *tmp, char *env)
{
	if (ft_strlen(tmp) == 1 && ft_strlen(env) == 1)
	{
		if (ft_strncmp(env, tmp, ft_strlen(tmp)))
			return (1);
	}
	else if (!ft_contain(env, '='))
	{
		if (ft_strncmp(env, tmp, ft_strlen(env) + 1))
			return (1);
	}
	else if (ft_strncmp(env, tmp, ft_strlen(env)))
		return (1);
	return (0);
}

static char	**ft_new_env(char *tmp, char **env, char **aux)
{
	int	i;
	int	j;

	j = 0;
	i = -1;
	while (env[++i])
	{
		if (ft_check_cpy(tmp, env[i]))
		{
			aux[j] = ft_strdup(env[i]);
			j++;
		}
	}
	aux[j] = NULL;
	return (aux);
}

void	ft_unset(char *cmd, t_minishell *shell)
{
	int		i;
	char	**aux;
	char	**tmp;

	tmp = ft_split(cmd, ' ');
	i = 0;
	while (tmp[++i])
	{
		if (ft_no_var(tmp[i]))
			return (ft_free_mtx(tmp));
		aux = ft_malloc(shell, tmp[i]);
		if (!aux)
			return ;
		aux = ft_new_env(tmp[i], shell->env, aux);
		ft_free_mtx(shell->env);
		shell->env = ft_cpy_env(aux);
		ft_free_mtx(aux);
		aux = NULL;
	}
	ft_free_mtx(tmp);
}
