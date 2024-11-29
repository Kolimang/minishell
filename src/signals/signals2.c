/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:03:41 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/29 14:39:29 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	unset_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}

void	newline_hook(int sig)
{
	(void)sig;
	//if (sig == SIGINT)
	//	write(2, "\n", 1);
}

void	sig_handler_hrdoc(int signum)
{
	// write (1, "\n> ", 3);
	set_exit_status(128 + signum);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	// rl_redisplay();
	exit(EXIT_FAILURE);
	// exit(EXIT_SUCCESS);
}

void	handle_hdoc_sigint(int fd, char *ln)
{
	if (g_ret_val > 128 && g_ret_val < 160)
	{
		free(ln);
		close(fd);
		// set_exit_status(1);
		//exit(EXIT_FAILURE);
		rl_redisplay();
		rl_replace_line("", 0);
		rl_on_new_line();
		exit(EXIT_FAILURE); // probleme dans la suite de l'execution si on return 1 ! Pourtant je devrai retourner 1 pour etre fidele a bash
	}
}
