/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_system.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:44:31 by dmonjas-          #+#    #+#             */
/*   Updated: 2024/01/22 17:34:39 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_select(t_command *cmd, t_minishell *shell, int fd)
{
	if  (!ft_strncmp(cmd->built, "echo", ft_strlen(cmd->built)))
		ft_echo(cmd->command, fd);
	else if  (!ft_strncmp(cmd->built, "cd", ft_strlen(cmd->built)))
		ft_cd(cmd->command, shell);
	else if  (!ft_strncmp(cmd->built, "pwd", ft_strlen(cmd->built)))
		ft_print_pwd(shell, fd);
	else if  (!ft_strncmp(cmd->built, "export", ft_strlen(cmd->built)))
		ft_exist(cmd->command, shell, fd);
	else if  (!ft_strncmp(cmd->built, "unset", ft_strlen(cmd->built)))
		ft_unset(cmd->command, shell);
	else if  (!ft_strncmp(cmd->built, "env", ft_strlen(cmd->built)))
		ft_print_env(shell, fd);
	else
		return (1);
	close (fd);
	return (0);
}

int	ft_cw(int fdout, pid_t pd)
{
	int	status;

	status = 0;
	close(fdout);
	waitpid(pd, &status, 0);
	return (status);
}

void	ft_exec(char **cmd, t_minishell *shell, int fdin, int fdout)
{
	char	*path;
	pid_t	pd;

	pd = fork();
	if (pd == -1)
		ft_error("fork() error");
	if (pd == 0)
	{
		path = ft_cmdpath(cmd[0], shell->env);
		if (!path)
		{
			ft_put_msg(cmd[0], "command not found\n");
			exit (127);
		}
		dup2(fdin, STDIN_FILENO);
		dup2(fdout, STDOUT_FILENO);
		close(fdin);
		if (execve(path, cmd, shell->env) == -1)
			ft_peror(cmd[0], "");
		free (path);
		close(fdout);
	}
	else
		code_error = (ft_cw(fdout, pd) >> 8) & 0xFF;
}

/* Esta funcion tiene q leer el archivo creado y sustituir los $ por su valor si existe esa variable.
Ns si hacerlo asi o sustituir la linea en el mismo archivo en vez de crear otro archivo e ir metiendolo ahi. */
/* int	ft_check_exp(int file, t_minishell *shell)
{
	char		*line;
	t_command	*tmp;
	t_command	*aux;
	int			fd;

	tmp = NULL;
	line = get_next_line(file);
	while (line)
	{
		ft_printf("%s\n", line);
		ft_lstadd_back_shell(&tmp, ft_lst_first(line, 'c'));
		free(line);
		line = get_next_line(file);
	}
	tmp = ft_sust(&tmp, shell->env);
	unlink(shell->inf);
	fd = open(shell->inf, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd > 0 && access(shell->inf, W_OK | R_OK) < 0)
		ft_err_msg("Error opening new file");
	aux = tmp;
	while (aux)
	{
		write(fd, aux->command, ft_strlen(aux->command));
		write(fd, "\n", 1);
		aux = aux->next;
	}
	ft_free_cmd(&tmp);
	return (fd);
} */

void	ft_system(t_command *cmd, t_minishell *shell, int fdin, int fdout)
{
	code_error = 0;
	if (ft_lstsize_shell(cmd) == 1)
	{
		if (!ft_strncmp(cmd->command, "exit", 4))
			ft_exit_code(shell);
		else if (!ft_strncmp(cmd->command, "minishell", ft_strlen(cmd->command)))
			ft_shell_up(shell);
		else if (shell->heredoc)
		{
			//fdin = ft_check_exp(fdin, shell);
			ft_exec(ft_split(cmd->command, ' '), shell, fdin, fdout);
			unlink(ft_split(cmd->command, ' ')[1]);
		}
		else if (ft_select(cmd, shell, fdout) == 1)
			ft_exec(ft_split(cmd->command, ' '), shell, fdin, fdout);
	}
	else if (ft_lstsize_shell(cmd) > 1)
		ft_ord(cmd, shell);
	dup2(STDIN_FILENO, STDOUT_FILENO);
}
