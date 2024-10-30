/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:03:41 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/30 17:07:47 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// SIGINT  (Ctrl-C) -> Display a new prompt
// EOF     (Ctrl-D) -> Exit the shell
// SIGQUIT (Ctrl-\) -> Ignore
void	ft_sighandler(int signum)
{
	if (signum == SIGINT)
	{
		// https://en.wikipedia.org/wiki/ANSI_escape_code
		// A B C D (up, down, forward, back)
		//ft_printf("\r\033[10C");
		//ft_printf("\033[2C\033[2D");
		//ft_printf("\b\b");
		//ft_printf("   ");
		//ft_printf("\033[2K");
		//ft_printf("\033[0;32mminishell$\033[0m ");
		//execve("/bin/stty", &"-echoctl", NULL); // Does not work
		printf("\n"); // Move to a new line
		rl_on_new_line(); // Regenerate the prompt on a newline
		rl_replace_line("", 0); // function not found in readline lib!
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
	{
		ft_printf("\r");// ignore
		//rl_redisplay();
	}
}

// SIGINT  (Ctrl-C) -> Display a new prompt
// SIGQUIT (Ctrl-\) -> Ignore
// EOF     (Ctrl-D) -> Exit the shell, if done at the beginning of the line (not a signal per se)
void	init_signals(void)
{
	sigset_t			signal_set;
	struct sigaction	action;

	sigemptyset(&signal_set);
	sigaddset(&signal_set, SIGINT);
	sigaddset(&signal_set, SIGQUIT);
	sigaddset(&signal_set, EOF);
	ft_bzero(&action, sizeof(action));
	//action.sa_RESTART;
	//action = {{0}};
	action.sa_handler = &ft_sighandler;
	action.sa_mask = signal_set;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
	sigaction(EOF, &action, NULL);
}
