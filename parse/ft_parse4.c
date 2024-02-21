/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 10:48:52 by dmonjas-          #+#    #+#             */
/*   Updated: 2024/02/21 19:04:42 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_change_doll(char *fir_line, char *sec_line, t_minishell *shell)
{
	char	*line;

	line = ft_strjoin_gnl(fir_line, ft_itoa(shell->last_error));
	if (sec_line)
		line = ft_strjoin_gnl(line, sec_line);
	return (line);
}

char	*ft_sust_doll(char *line, t_minishell *shell)
{
	int		i;
	int		j;
	char	*fir_line;
	char	*sec_line;

	i = 0;
	fir_line = NULL;
	sec_line = NULL;
	while (line[i] != '$' && line[i])
		i++;
	fir_line = ft_substr(line, 0, i);
	j = i;
	j += 2;
	if (line[j])
		sec_line = ft_substr(line, j, ft_strlen(&line[j]));
	line = ft_change_doll(fir_line, sec_line, shell);
	return (line);
}

static void	ft_loop(int fd, char *line, char *end, t_minishell *shell)
{
	while (line)
	{
		line = ft_exp(line, shell);
		if ((ft_strncmp(line, end, ft_strlen(end)) == 0)
			&& (ft_strlen(line) == ft_strlen(end) + 1))
			exit(EXIT_SUCCESS);
		write(1, "> ", 2);
		write(fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
}

static int	ft_here(char *end, int file, t_minishell *shell)
{
	pid_t	pid;
	char	*line;

	pid = fork();
	if (pid < 0)
		ft_per_nb("fork", STDERR_FILENO);
	if (pid == 0)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		ft_loop(file, line, end, shell);
		close(file);
	}
	else
		wait(NULL);
	return (file);
}

int	ft_inf(char *infile, int x, t_minishell *shell)
{
	int	fd;

	fd = 0;
	if (shell->infile)
		close(shell->infile);
	if (x == 1)
	{
		fd = open(infile, O_RDONLY, 0644);
		if (fd > 0 && access(infile, R_OK) < 0)
			return (ft_err_msg("Error opening infile"), 0);
	}
	if (x == 2)
	{
		fd = open(infile, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (fd > 0 && access(infile, W_OK | R_OK) < 0)
			return (ft_err_msg("Error opening heredoc"), 0);
		shell->heredoc = 1;
		shell->infile = ft_here(infile, fd, shell);
	}
	if (fd < 0)
		return (ft_err_msg("No such file or directory"), 0);
	return (fd);
}
