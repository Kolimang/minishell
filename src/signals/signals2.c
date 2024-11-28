/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:03:41 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/28 14:15:23 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	newline_hook(int sig)
{
	if (sig == SIGINT)
		write(2, "\n", 1);
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

int	*sig_status(void)
{
	static int	*triggered;

	if (!triggered)
	{
		triggered = malloc(sizeof(int));
		*triggered = 0;
	}
	return (triggered);
}
