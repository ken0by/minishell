/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmonjas- <dmonjas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 08:24:23 by dmonjas-          #+#    #+#             */
/*   Updated: 2024/02/27 10:31:03 by dmonjas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_strchr_in(const char *s, int c)
{
	int	i;
	int	j;

	j = ft_strlen(s);
	i = 0;
	if (!s)
		return (0);
	while (i <= j)
	{
		if (s[i] == (char)c)
		{
			i--;
			while (s[i] == ' ')
				i--;
			i++;
			return (i);
		}
		i++;
	}
	return (0);
}

int	ft_strchr_out(const char *s, int c)
{
	int	i;
	int	j;

	j = ft_strlen(s);
	i = 0;
	if (!s)
		return (0);
	while (i <= j)
	{
		if (s[i] == (char)c)
		{
			if (s[i + 1] == (char)c)
				i++;
			i++;
			while (s[i] == ' ')
				i++;
			return (i);
		}
		i++;
	}
	return (0);
}

char	*ft_cp_nb(char *str, int j)
{
	int		i;
	char	*nb;

	nb = malloc(sizeof(char) * j);
	i = 4;
	j = 0;
	while (str[++i])
	{
		nb[j] = str[i];
		j++;
	}
	return (nb);
}

void	ft_err_msg(char *s)
{
	ft_printf("%s\n", s);
	g_code_error = 1;
}

void	ft_per_nb(char *s, int nb)
{
	perror(s);
	g_code_error = nb;
}
/*  static void	ft_pintar(t_command *cmd)
{
	t_command	*aux;
	int	i;

	i = 0;
	aux = cmd;
	while (aux)	
	{
		ft_printf("ccommand: %s\n", aux->command);
		//ft_printf("infile: %s\n", aux->infile);
		//ft_printf("outfile: %s\n", aux->outfile);
		aux = aux->next;
	}
} */
