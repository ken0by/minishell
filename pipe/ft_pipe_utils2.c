/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 21:04:32 by rodro             #+#    #+#             */
/*   Updated: 2024/01/10 17:00:16 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
		ft_error_fd("pipe", STDERR_FILENO);
	pid = fork();
	if (pid < 0)
		ft_error_fd("fork", STDERR_FILENO);
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

static int	ft_heredoc(t_pipe *pipe, int x)
{
	int	fd;

	fd = 0;
	if (x == 2)
	{
		fd = open(pipe->argv, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (access(pipe->argv, W_OK | R_OK) < 0)
			ft_error("Error opening heredoc\n");
		ft_here(pipe->next->argv);
	}
	else if (x == 3)
	{
		fd = open(pipe->argv, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
		if (access(pipe->argv, W_OK | R_OK) < 0)
			ft_error("Error opening append\n");
	}
	return (fd);
}

int	ft_file(t_pipe *pipe, int x)
{
	int	fd;

	fd = 0;
	if (x == 0)
	{
		fd = open(pipe->argv, O_RDONLY, 0644);
		if (access(pipe->argv, R_OK) < 0)
			ft_error("Error opening infile\n");
	}
	else if (x == 1)
	{
		fd = open(pipe->argv, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (access(pipe->argv, W_OK | R_OK) < 0)
			ft_error("Error opening outfile\n");
	}
	else
		fd = ft_heredoc(pipe, x);
	if (fd < 0)
		ft_error("Error opening file\n");
	return (fd);
}

int	ft_quotes(char	*cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == 39 || cmd[i] == 34)
			return (1);
	}
	return (0);
}
