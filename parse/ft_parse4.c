/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 10:48:52 by dmonjas-          #+#    #+#             */
/*   Updated: 2024/01/15 19:20:47 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_change_doll(char *fir_line, char *sec_line)
{
	char	*line;

	//ft_printf("code error1; %d\n", g_global.code_error);
	line = ft_strjoin_gnl(fir_line, ft_itoa(code_error));
	if (sec_line)
		line = ft_strjoin_gnl(line, sec_line);
	return (line);
}

char	*ft_sust_doll(char *line)
{
	int		i;
	int		j;
	char	*fir_line;
	char	*change;
	char	*sec_line;

	i = 0;
	fir_line = NULL;
	change = NULL;
	sec_line = NULL;
	while (line[i] != '$' && line[i])
		i++;
	fir_line = ft_substr(line, 0, i);
	j = i;
	j += 2;
	if (line[j])
		sec_line = ft_substr(line, j, ft_strlen(&line[j]));
	line = ft_change_doll(fir_line, sec_line);
	return (line);
}

static void	ft_loop(int *fd, char *line, char *end)
{
	while (line)
	{
		close(fd[0]);
		if ((ft_strncmp(line, end, ft_strlen(end)) == 0) && (ft_strlen(line) == ft_strlen(end) + 1))
			exit(EXIT_SUCCESS);
		write(1, "pipe heredoc> ", 14);
		write(fd[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
}

static void	ft_here(char *end)
{
	pid_t	pid;
	int		fd[2];
	char	*line;

	pipe(fd);
	if (fd < 0)
		ft_per_nb("pipe", STDERR_FILENO);
	pid = fork();
	if (pid < 0)
		ft_per_nb("fork", STDERR_FILENO);
	if (pid == 0)
	{
		write(1, "pipe heredoc> ", 14);
		line = get_next_line(STDIN_FILENO);
		ft_loop(fd, line, end);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		wait(NULL);
	}
}

int	ft_inf(char *infile, int x)
{
	int	fd;

	fd = 0;
	if (x == 1)
	{
		fd = open(infile, O_RDONLY, 0644);
		if (access(infile, R_OK) < 0)
			ft_err_msg("Error opening infile\n");
	}
	if (x == 2)
	{
		fd = open(infile, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (access(infile, W_OK | R_OK) < 0)
			ft_err_msg("Error opening heredoc\n");
		ft_here(infile);
	}
	if (fd < 0)
		ft_err_msg("Error opening file\n");
	return (fd);
}
