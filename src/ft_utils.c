/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:59:53 by dmonjas-          #+#    #+#             */
/*   Updated: 2024/01/11 18:11:00 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_flag(int flag, char *nb)
{
	if (!flag)
	{
		ft_printf("exit\n");
		return (ft_atoi(nb));
	}
	else
	{
		ft_printf("exit: numeric argument required\n");
		return (255);
	}
}

static int	ft_code_nb(char *str)
{
	int	i;
	int	j;
	int	flag;

	i = -1;
	while (str[++i])
		if (i == 4)
			break ;
	if (i == 4 && str[i])
	{
		j = 0;
		flag = 0;
		while (str[++i])
		{
			if (str[i] >= '0' && str[i] <= '9')
				j++;
			else
				flag = 1;
		}
		return (ft_flag(flag, ft_cp_nb(str, j)));
	}
	return (0);
}

void	ft_exit_code(t_minishell *shell)
{
	if (shell->shlvl == 1)
		exit (ft_code_nb(shell->cmd_line));
	else
	{
		code_error = ft_code_nb(shell->cmd_line);
		ft_shell_down(shell);
	}
}

static char	*ft_copy_path(char *str, int i)
{
	char	*tmp;

	if (i == 4)
		tmp = ft_substr(str, i, ft_strlen(str) - i);
	if (i == 5)
		tmp = ft_substr(str, i, ft_strlen(str) - i);
	if (i == 7)
		tmp = ft_substr(str, i, ft_strlen(str) - i);
	return (tmp);
}

char	*ft_env(char **env, char *c)
{
	int		i;
	int		size;
	char	*str;

	size = ft_strlen(c);
	i = -1;
	str = NULL;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], c, size))
			str = ft_copy_path(env[i], size);
		if (str)
			break ;
	}
	if (!str)
		ft_error_path(1);
	return (str);
}

char	**ft_cpy_env(char **env)
{
	char	**tmp;
	int		i;
	int		j;

	i = 0;
	while (env[i])
		i++;
	tmp = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (env[++i])
		tmp[i] = malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
	i = -1;
	while (env[++i])
	{
		j = -1;
		while (env[i][++j])
			tmp[i][j] = env[i][j];
		tmp[i][j] = '\0';
	}
	tmp[i] = NULL;
	return (tmp);
}
