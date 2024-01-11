/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:12:21 by rofuente          #+#    #+#             */
/*   Updated: 2024/01/11 13:36:52 by rofuente         ###   ########.fr       */
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
void	ft_exist(t_command *cmd, t_minishell *shell)
{
	char	*var;
	char	*ct;
	char	**command;

	command = ft_split(cmd->command, ' ');
	if (!command[1] || !ft_varct(command[1]))		//hay q ver si hay q guardar solo una letra cuando la pasan sin =
	{
		ft_alfa(shell->env);
		return ;
	}
	var = ft_get_var(command[1]);		// esto no hace falta al hacer el split el command[1] es la variable
	ct = ft_get_content(command[1], var);
	// var = ft_split(cmd->argv[1], '=');		// Da error a veces con el contenido
	if (!ft_check_var(var, shell->env))
		ft_export(shell, var, ct);		// crear la nueva variable y la añade a env
	else
		ft_change(shell, command[1], var);		// cambia el contenido de una variable x el nuevo dado
}
