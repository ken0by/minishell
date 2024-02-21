/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 12:31:50 by dmonjas-          #+#    #+#             */
/*   Updated: 2024/02/21 19:02:46 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_signal_dis(void)
{
	int			rc;
	t_signal	signal;

	rc = tcgetattr(0, &signal.termios);
	if (rc != 0)
	{
		perror("tcgetattr");
		exit (1);
	}
	signal.termios.c_lflag &= ~ECHOCTL;
	rc = tcsetattr(0, 0, &signal.termios);
	if (rc != 0)
	{
		perror("tcsetattr");
		exit(0);
	}
}

void	ft_intnl(int i)
{
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", '\0');
	(void)i;
}

void	ft_int(int i)
{
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", '\0');
	rl_redisplay();
	(void)i;
}

void	ft_quit(int sig)
{
	ft_putstr_fd("^\\Quit: ", STDERR_FILENO);
	ft_putnbr_fd(sig, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	ft_init_signal(void)
{
	rl_event_hook = 0;
	signal(SIGINT, ft_int);
	signal(SIGQUIT, SIG_IGN);
}
