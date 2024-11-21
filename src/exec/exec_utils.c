/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:59:16 by lboumahd          #+#    #+#             */
/*   Updated: 2024/11/21 17:22:15 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	handle_error(const char *msg)
{
	g_ret_val = EXIT_FAILURE;
	write(2, "minishell: ", 12);
	perror(msg);
	return (-1);
}

void	reset_io(t_io_fd *io, t_cmd *cmd)
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

void	return_error(char *arg)
{
	g_ret_val = EXIT_FAILURE;
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

int	is_last(t_list *curr)
{
	return (curr->next == NULL);
}

int	has_redir_in(t_list *ls_redir)
{
	t_list	*redir;

	redir = ls_redir;
	while (redir)
	{
		if (is_redir_in(redir->content))
			return (1);
		redir = redir->next;
	}
	return (0);
}
