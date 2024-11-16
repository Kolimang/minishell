/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_out.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:21:00 by lboumahd          #+#    #+#             */
/*   Updated: 2024/11/16 15:28:19 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	has_redir_out(t_list *ls_redir)
{
	t_list	*redir;

	redir = ls_redir;
	while (redir)
	{
		if (is_redir_out(redir->content))
			return (1);
		redir = redir->next;
	}
	return (0);
}

int	is_redir_out(t_redir *redir)
{
	if (redir->type == OUTFILE || redir->type == APPEND)
		return (1);
	return (0);
}

int	redir_outfile(t_cmd *cmd, t_io_fd *io)
{
	t_list	*tmp;
	t_redir	*redir;
	int		fd;

	fd = -2;
	tmp = cmd->ls_redirs;
	while (tmp)
	{
		redir = tmp->content;
		if (is_redir_out(redir))
		{
			fd = get_outfile(cmd, redir, io, fd);
			if(cmd->nextpipe) // HERE
				close(io->pipe[1]);
		}
		tmp = tmp->next;
	}
	if (fd != -2)
		return(fd);
	else
		return(io->pipe[1]);
}

int	get_outfile(t_cmd *cmd, t_redir *redir, t_io_fd *io, int fd )
{
	(void)io;
	if (fd != -2)
		close(fd);
	if (redir->type == OUTFILE)
		fd = open(redir->val, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redir->type == APPEND)
		fd= open(redir->val, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		return (handle_error(redir->val));
	if (!cmd->nextpipe)
	{
		signal(SIGINT, newline_hook);
	}
	return (fd);
}

int	set_fds(t_cmd *cmd, t_io_fd *io)
{
	if (cmd->prevpipe || has_redir_in(cmd->ls_redirs))
	{
		io->fd_in = redir_infile(cmd, io);
		if(io->fd_in == -1) 
			return (-1);
		if (dup2(io->fd_in, STDIN_FILENO) == -1)
			return (perror("dup2 failed for fd_in"), -1);
		close(io->fd_in);
	}
	if (cmd->nextpipe || has_redir_out(cmd->ls_redirs))
	{
		io->pipe[1] = redir_outfile(cmd, io);
		if (dup2(io->pipe[1], STDOUT_FILENO) == -1)
			return (perror("dup2 failed for fd_out"), -1);
		if (cmd->nextpipe)
			close(io->pipe[0]);
		close(io->pipe[1]);
	}
	return (0);
}
