/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:50:00 by rofuente          #+#    #+#             */
/*   Updated: 2024/01/18 13:09:35 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


static char	*ft_sjoin(char *s1, char *s2)
{
	char	*r;
	int		x;
	int		y;

	r = malloc(sizeof(char) * (ft_strlen((char *)s1)
				+ ft_strlen((char *)s2)) + 2);
	if (!r)
		return (NULL);
	x = 0;
	y = 0;
	while (s1[y])
		r[x++] = s1[y++];
	r[x] = ' ';
	x++;
	y = 0;
	while (s2[y])
		r[x++] = s2[y++];
	r[x] = '\0';
	return (r);
}

void	ft_swap(t_command *cmd)
{
	char	**tmp;
	char	*aux;
	char	*aux2;

	tmp = ft_split(cmd->command, ' ');
	if (open(tmp[0], O_RDONLY, 0644) < 0)
	{
		free (tmp);
		return ;
	}
	aux = tmp[0];
	aux2 = tmp[1];
	tmp[0] = aux2;
	tmp[1] = aux;
	free (cmd->command);
	cmd->command = ft_sjoin(tmp[0], tmp[1]);
}

char	*ft_take_size(char *cmd)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	j = 0;
	while (cmd[++i])
	{
		if (cmd[i] == '>')
			break ;
		if (cmd[i] == '<')
		{
			i++;
			while (cmd[i] == ' ')
				i++;
			i--;
		}
		else
			j++;
	}
	tmp = ft_calloc((j + 1), sizeof(char));
	return (tmp);
}

/* void	ft_exec_heredoc(char **cmd, t_minishell *shell)
{
	pid_t	pid;
	int		fd[2];

	pipe(fd);
	if (fd < 0)
		ft_perror("pipe", STDERR_FILENO);
	pid = fork();
	if (pid < 0)
		ft_perror("fork", STDERR_FILENO);
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		ft_command(cmd, shell->env);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, 0, 0);
	}
	close(fd[0]);
	close(fd[1]);
} */
