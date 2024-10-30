/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:03:41 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/29 17:06:49 by jrichir          ###   ########.fr       */
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
		ft_printf("\n");
		// terminate child processes
		main(0, NULL, NULL);
	}
	else if (signum == SIGQUIT)
	{
		;// ignore
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
	action.sa_handler = &ft_sighandler;
	action.sa_mask = signal_set;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
	sigaction(EOF, &action, NULL);
}
