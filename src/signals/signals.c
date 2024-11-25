/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:03:41 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/25 16:58:53 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	change_term_attr(void)
{
	/*
	struct termios	myterm;

	if (tcgetattr(STDIN_FILENO, &myterm) == -1)
	{
		perror("tcgetattr");
		return (1);
	}
	myterm.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &myterm) == -1)
	{
		perror("tcsetattr");
		return (1);
	}
	*/
	return (0);
}

int	*sig_status(void)
{
	static int	*triggered;

	if (!triggered)
	{
		triggered = (int *)malloc(sizeof(int));
		*triggered = 0;
	}
	return (triggered);
}

void	sig_handler_child(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		signal(SIGINT, sig_handler_child);
	}
}

void	sig_handler_main(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_handler_hrdoc(int signum)
{
	int	*triggered;

	triggered = sig_status();
	if (signum == SIGINT)
	{
		*triggered = 1;
		signal(SIGINT, sig_handler_hrdoc);
	}
}
