/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:03:41 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/29 14:33:17 by jrichir          ###   ########.fr       */
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
	myterm.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &myterm) == -1)
	{
		perror("tcsetattr");
		return (1);
	}
	return (0);
}

void	set_signals_parent(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGINT, sig_handler_main);
}

void	set_signals_child(void)
{
	ft_printf("hohoho\n");//DEBUG - TEST
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}

void	set_signals_hrdoc(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGINT, sig_handler_hrdoc);
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
