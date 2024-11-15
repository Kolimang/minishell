/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:59:16 by lboumahd          #+#    #+#             */
/*   Updated: 2024/11/05 12:13:34 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_io_fd(t_io_fd *io)
{
	io->pipe[0] = -1;
	io->pipe[1] = -1;
	io->fd_in = STDIN_FILENO;
	io->fd_out = -2;
	io->std_in = dup(STDIN_FILENO);
	io->std_out = dup(STDOUT_FILENO);
	if (io->std_in == -1 || io->std_out == -1)
	{
		perror("Failed to duplicate");
		exit(EXIT_FAILURE);
	}
}

void	reset_io(t_io_fd *io, t_command *cmd)
{
	if (dup2(io->std_in, STDIN_FILENO) == -1)
	{
		perror("Failed to reset stdin");
		exit(EXIT_FAILURE);
	}
	if (dup2(io->std_out, STDOUT_FILENO) == -1)
	{
		perror("Failed to reset stdout");
		exit(EXIT_FAILURE);
	}
	if (cmd->fd_hrdoc != -3)
	{
		close(cmd->fd_hrdoc);
		cmd->fd_hrdoc = -3;
	}
	close(io->std_in);
	close(io->std_out);
}

int	handle_error(const char *msg)
{
	g_ret_value = EXIT_FAILURE;
	write(2, "minishell: ", 12);
	perror(msg);
	return (-1);
}

void	return_error(char *arg)
{
	g_ret_value = EXIT_FAILURE;
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

int	is_last(t_list *curr)
{
	return (curr->next == NULL);
}
