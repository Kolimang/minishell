/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 18:12:18 by lboumahd          #+#    #+#             */
/*   Updated: 2024/10/30 10:06:51 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdarg.h>
#include <stdio.h>

void	eprintf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
}
void	debug_print_fds(const char* msg, t_command *cmd, t_io_fd *io) {
    dprintf(2, "\n=== %s ===\n", msg);
    dprintf(2, "stdin_fd: %d\n", fcntl(STDIN_FILENO, F_GETFD));
    dprintf(2, "stdout_fd: %d\n", fcntl(STDOUT_FILENO, F_GETFD));
	if (io)
	{dprintf(2, "io->fd_in: %d\n", io->fd_in);
	dprintf(2, "io->fd_out: %d\n", io->fd_out);
	dprintf(2, "io->pipe[0]: %d\n", io->pipe[0]);
	dprintf(2, "io->pipe[1]: %d\n", io->pipe[1]);
	}
    dprintf(2, "cmd->nextpipe: %d\n", cmd->nextpipe);
    dprintf(2, "cmd->prevpipe: %d\n", cmd->prevpipe);
	 dprintf(2, "stdoutfileno: %d\n", STDOUT_FILENO);
	  dprintf(2, "stdinfileno: %d\n", STDIN_FILENO);
}