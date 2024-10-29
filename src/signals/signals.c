/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:03:41 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/29 14:04:52 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_sighandler(int signum)
{
	if (signum == SIGINT)
	{
		main(0, NULL, NULL);
	}
	else if (signum == EOF)
	{
		ft_exit(NULL, NULL); // leak of args and env
	}
	else if (signum == SIGQUIT)
	{
		
	}
}

// SIGINT  (Ctrl-C) -> Display a new prompt
// EOF     (Ctrl-D) -> Exit the shell
// SIGQUIT (Ctrl-\) -> Ignore
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
