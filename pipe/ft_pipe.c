/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:24:27 by rodro             #+#    #+#             */
/*   Updated: 2024/01/10 17:30:29 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_is_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY, 0644);
	if (fd == -1)
		return (0);
	close (fd);
	return (1);
}

/* Esta funcion ve si es built-in o un ejecutable. Hay q ver como hacer q tenga un archivo outfile temporal
xa cada comando, xq xa el primero seria outfile, pero xa el siguiente infile y asi sucesivamente hasta el ultimo
q si hay outfile lo envia ahi y sino a la salida estandart (q eso ya esta solo falta el tmp) */
static void	ft_order(t_cmd *cmd, t_minishell *shell)
{
	t_cmd	*aux;
	int		i;

	dup2(shell->infile, STDOUT_FILENO);
	close (shell->infile);
	aux = cmd;
	while (aux)
	{
		if (ft_check_built(aux->argv[0]))
		{
			i = -1;
			while (aux->argv[++i])
			{
				write(shell->outfile, aux->argv[i], ft_strlen(aux->argv[i]));
				write(shell->outfile, " ", 1);
			}
		}
		else
		{
			i = -1;
			while (aux->argv[++i])
			{
				write(shell->outfile, aux->argv[i], ft_strlen(aux->argv[i]));
				write(shell->outfile, " ", 1);
			}
			if (ft_pipe_system(aux->argv, shell))
				break ;
		}
		write(shell->outfile, "\n", 1);
		aux = aux->next;
	}
	dup2(shell->outfile, STDOUT_FILENO);
	close (shell->outfile);
	dup2(STDIN_FILENO, STDOUT_FILENO);
	ft_free_cmd(&cmd);
}

t_cmd	*ft_psplit(t_pipe *pipe)
{
	t_cmd	*cmd;
	t_pipe	*aux;

	aux = pipe;
	while (aux)
	{
		ft_cmdlstadd_back(&cmd, ft_cmdlst_new(aux->argv));
		aux = aux->next;
	}
	ft_free_pipe(&pipe);
	return (cmd);
}

int	ft_is_pipe(char *str)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	while (str[++i])
		if (str[i] == '|')
			flag++;
	return (flag);
}

void	ft_ord(t_pipe *pipe, t_minishell *shell)
{
	t_pipe	*aux;

	aux = pipe;
	while (aux)
	{
		if (aux->argv[0] != '|')
		{
			if (ft_isbuilt(aux->argv))
				aux->builtin = 1;
			else if (ft_is_file(aux->argv))
				shell->infile = ft_file(aux, 0);
			else if (aux->argv[0] == '>' || aux->argv[0] == '<')
			{
				ft_redir(aux, shell);
				aux = aux->next;
			}
		}
		aux = aux->next;
	}
	ft_del_redir(pipe, shell);
	pipe = ft_pjoin(&pipe);
	ft_order(ft_psplit(pipe), shell);
}
