/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:03:41 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/04 13:13:34 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	change_term_attr(void)
{
	struct termios	myterm;

	if (tcgetattr(STDIN_FILENO, &myterm) == -1)
	{
		perror("tcgetattr");
		return (1);
	}
	myterm.c_cc[VQUIT] = 0;
	myterm.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &myterm) == -1)
	{
		perror("tcsetattr");
		return (1);
	}
	return (0);
}

void	ft_sighandler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_signals(void)
{
	sigset_t			signal_set;
	struct sigaction	action;

	sigemptyset(&signal_set);
	sigaddset(&signal_set, SIGINT);
	sigaddset(&signal_set, SIGQUIT);
	sigaddset(&signal_set, EOF);
	ft_bzero(&action, sizeof(action));
	action.sa_handler = &ft_sighandler;
	action.sa_mask = signal_set;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
	sigaction(EOF, &action, NULL);
}
