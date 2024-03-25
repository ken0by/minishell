/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmonjas- <dmonjas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:57:47 by dmonjas-          #+#    #+#             */
/*   Updated: 2024/03/25 15:40:09 by dmonjas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_er_out(char *str, int i)
{
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	g_code_error = i;
}

void	ft_g_code(char *str)
{
	if (str[0] == str[1] && str[1] == str[2])
	{
		g_code_error = 258;
		ft_printf("syntax error near unexpected token `%c'\n", str[0]);
	}
	if (str[0] == '|' && str[1] == '|')
	{
		g_code_error = 258;
		ft_printf("syntax error near unexpected token `%c'\n", str[0]);
	}
}

int	ft_size_param(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '/')
			return (i);
		i++;
	}
	return (i);
}

t_command	*ft_so_long(t_command *aux, t_minishell *shell)
{
	if (shell->inf == NULL)
		free (shell->inf);
	shell->inf = ft_strdup(aux->next->next->command);
	shell->infile = ft_inf(aux->next->next->command, aux->next->command, shell);
	return (ft_del_node(aux->next));
}
