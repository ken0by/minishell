/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:58:21 by dmonjas-          #+#    #+#             */
/*   Updated: 2024/01/11 12:37:04 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* void	ft_free_list(t_command *cmd, char **command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		free(command[i]);
		i++;
	}
	while (cmd)
	{
		free (cmd->command);
		cmd = cmd->next;
	}
} */

void	ft_free_mtx(char **mtx)
{
	int	i;

	i = -1;
	while (mtx[++i])
		free(mtx[i]);
	free(mtx);
	mtx = NULL;
}

void	ft_error_perror(char *command, char *s)
{
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	perror(s);
	exit (127);
}

void	ft_put_msg(char *var, char *s)
{
	ft_putstr_fd(var, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(s, STDERR_FILENO);
	code_error = 127;
	exit (127);
}

void	ft_per(char *var, char *s)
{
	ft_putstr_fd(var, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	//exit (127);
	code_error = 127;
	perror(s);
	exit (127);
}

void	ft_error(char *str)
{
	printf("%s\n", str);
	code_error = 1;
	exit (1);
}
