/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:12:21 by rofuente          #+#    #+#             */
/*   Updated: 2024/01/18 12:42:17 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_env_cpy(char **env, char **new)
{
	int	i;

	if (!env)
		return ;
	i = -1;
	while (env[++i])
		new[i] = ft_strdup(env[i]);
	new[i] = NULL;
	new[i + 1] = NULL;
}

/* Coge el nuevo tamaño para env */
static void	ft_new_env(t_minishell *shell)
{
	int		i;
	char	**aux;

	i = 0;
	while (shell->env[i])
		i++;
	aux = malloc(sizeof(char *) * (i + 2));
	if (!aux)
		return ;
	ft_env_cpy(shell->env, aux);
	ft_free_mtx(shell->env);
	shell->env = aux;
}

/* Esta funcion crea una nueva variable */
static void	ft_export(t_minishell *shell, char *var, char *ct)
{
	int		i;
	char	*str;
	char	*new;

	i = 0;
	new = NULL;
	ft_new_env(shell);
	while (shell->env[i])
		i++;
	str = ft_strjoin(var, "=");
	if (!ct)
		new = ft_strdup(str);
	else
		new = ft_strjoin(str, ct);
	shell->env[i] = ft_strdup(new);
	if (str)
		free (str);
	if (new)
		free (new);
	i++;
	shell->env[i] = NULL;
}

static void	ft_change(t_minishell *shell, char *str, char *var)
{
	int		i;
	char	*aux;

	i = -1;
	while (shell->env[++i])
	{
		if (!ft_strncmp(shell->env[i], var, ft_strlen(var)))
		{
			shell->env[i] = NULL;
			aux = ft_strdup(str);
			shell->env[i] = aux;
			break ;
		}
	}
}

/* Esta funcion comprueba si la variable existe, si existe cambia su contenido y sino la crea */
/* Ns si hay q gestionar si te pasan una variable sin = */
void	ft_exist(char *cmd, t_minishell *shell, int fd)
{
	char	*var;
	char	*ct;
	char	**command;

	command = ft_split(cmd, ' ');
	if (!command[1])
	{
		ft_alfa(shell->env, fd);
		return ;
	}
	var = ft_get_var(command[1]);
	ct = ft_get_content(command[1], var);
	if (!ft_check_var(var, shell->env))
		ft_export(shell, var, ct);
	else
		ft_change(shell, command[1], var);
}
