/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:28:37 by dmonjas-          #+#    #+#             */
/*   Updated: 2024/01/11 12:30:26 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static void ft_p_list(t_command *cmd)
{
	int i = 1;

	while (cmd)
	{
		ft_printf("Lista numero: %d\n", i);
		ft_printf("%s\n", cmd->command);
		if (cmd->infile != NULL)
			ft_printf("infile: %s\n", cmd->infile);
		if (cmd->outfile != NULL)
			ft_printf("outfile: %s\n", cmd->outfile);
		ft_printf("%s\n", cmd->built);
		ft_printf("comillas simples: %d\n", cmd->dollar);
		cmd = cmd->next;
		i++;
	}
} */

static void	ft_shell_up(t_minishell *shell)
{
	int		i;
	int		j;
	int		k;
	char	*aux;

	shell->shlvl += 1;
	i = -1;
	aux = ft_itoa(shell->shlvl);
	while (shell->env[++i])
	{
		if (!ft_strncmp(shell->env[i], "SHLVL", 5))
		{
			j = -1;
			while (shell->env[i][++j])
				if (shell->env[i][j] == '=')
					break ;
			k = 0;
			while (shell->env[i][++j])
			{
				shell->env[i][j] = aux[k];
				k++;
			}
			break ;
		}
	}
}

void	ft_shell_down(t_minishell *shell)
{
	int		i;
	int		j;
	int		k;
	char	*aux;

	shell->shlvl -= 1;
	i = -1;
	aux = ft_itoa(shell->shlvl);
	while (shell->env[++i])
	{
		if (!ft_strncmp(shell->env[i], "SHLVL", 5))
		{
			j = -1;
			while (shell->env[i][++j])
				if (shell->env[i][j] == '=')
					break ;
			k = 0;
			while (shell->env[i][++j])
			{
				shell->env[i][j] = aux[k];
				k++;
			}
			break ;
		}
	}
}

static t_command	*ft_join(t_command **cmd)
{
	t_command	**pipe;
	t_command	*aux;
	char		*line;

	pipe = malloc(sizeof(t_command));
	*pipe = 0;
	line = NULL;
	aux = *cmd;
	while (aux)
	{
		if (ft_strlen(aux->command) == 1 && aux->command[0] == '|')
		{
			ft_lstadd_back_shell(pipe, ft_lstnew_shell(line));
			free(line);
			line = NULL;
			aux = aux->next;
		}
		line = ft_strjoin_gnl(line, aux->command);
		if (aux->next && aux->next->command[0] != '|')
			line = ft_strjoin_gnl(line, " ");
		aux = aux->next;
	}
	ft_lstadd_back_shell(pipe, ft_lstnew_shell(line));
	free(line);
	return (*pipe);
}

void	ft_check_line(t_minishell *shell)
{
	t_command	*cmd;
	char		*line;
	char		*cmd_line;

	if (!ft_strncmp(shell->cmd_line, "exit", 4))
		ft_exit_code(shell);
	else if (!ft_strncmp(shell->cmd_line, "minishell", ft_strlen(shell->cmd_line)))
		ft_shell_up(shell);
	else
	{
		line = NULL;
		cmd_line = shell->cmd_line;
		if (cmd_line[0] == '\0')
			return ;
		signal(SIGQUIT, ft_quit);
		cmd = ft_take_cmd(&cmd, line, cmd_line);
		cmd = ft_sust(&cmd, shell->env);
		cmd = ft_join(&cmd);
		cmd = ft_inout(&cmd);
		///ft_p_list(cmd);
		ft_system(cmd, shell);
	}
}
