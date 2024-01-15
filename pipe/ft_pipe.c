/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:24:27 by rodro             #+#    #+#             */
/*   Updated: 2024/01/15 19:24:01 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* Esta funcion ve si es built-in o un ejecutable. Hay q ver como hacer q tenga un archivo outfile temporal
xa cada comando, xq xa el primero seria outfile, pero xa el siguiente infile y asi sucesivamente hasta el ultimo
q si hay outfile lo envia ahi y sino a la salida estandart (q eso ya esta solo falta el tmp) */
static void	ft_order(t_command *cmd, t_minishell *shell)
{
	t_command	*aux;
	int			i;

	dup2(shell->infile, STDOUT_FILENO);
	close (shell->infile);
	aux = cmd;
	while (aux->next)
	{
		if (ft_strncmp(aux->built, "exec", ft_strlen(aux->built)))
		{
			i = -1;
			while (aux->command[++i])
			{
				write(shell->outfile, &aux->command[i], ft_strlen(&aux->command[i]));
				write(shell->outfile, " ", 1);
			}
		}
		else
		{
			i = -1;
			while (aux->command[++i])
			{
				write(shell->outfile, &aux->command[i], ft_strlen(&aux->command[i]));
				write(shell->outfile, " ", 1);
			}
			if (ft_pipe_system(&aux->command, shell))
				break ;
		}
		write(shell->outfile, "\n", 1);
		aux = aux->next;
	}
	dup2(shell->outfile, STDOUT_FILENO);
	close (shell->outfile);
	//ejecutar ultimo comando aqui
	dup2(STDIN_FILENO, STDOUT_FILENO);
	ft_free_cmd(&cmd);
}

void	ft_ord(t_command *cmd, t_minishell *shell)
{
	t_command	*aux;

	aux = cmd;
	while (aux)
	{
		if (aux->inf)
			shell->infile = aux->inf;
		if (aux->out)
			shell->outfile = aux->out;
		aux = aux->next;
	}
	ft_order(cmd, shell);
}
