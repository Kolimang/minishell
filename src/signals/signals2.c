/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:03:41 by jrichir           #+#    #+#             */
/*   Updated: 2024/12/02 09:37:57 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	unset_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}

void	sig_handler_hrdoc(int signum)
{
	set_exit_status(128 + signum);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	exit(EXIT_SUCCESS);
}
