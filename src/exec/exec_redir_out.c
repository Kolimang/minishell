/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_out.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:21:00 by lboumahd          #+#    #+#             */
/*   Updated: 2024/11/18 14:05:20 by lboumahd         ###   ########.fr       */
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

int	redir_outfile(t_cmd *cmd, t_io_fd *io, int **fd, int i)
{
	t_list	*tmp;
	t_redir	*redir;
	int		has_outfile;

	has_outfile = 0;
	tmp = cmd->ls_redirs;
	
	while (tmp)
	{
		redir = tmp->content;
		if (is_redir_out(redir))
		{
			if (get_outfile(cmd, redir, io) == -1)
				return (-1);
			has_outfile = 1;
			close(fd[i][1]);
		}
		tmp = tmp->next;
	}
	if (!has_outfile)
	{
		if (cmd->nextpipe && !cmd->prevpipe)
			io->fd_out = fd[i][1];
		else
			io->fd_out = STDOUT_FILENO;
	}
	return (1);
}

int	get_outfile(t_cmd *cmd, t_redir *redir, t_io_fd *io)
{
	if (io->fd_out != -2)
		close(io->fd_out);
	if (redir->type == OUTFILE)
		io->fd_out = open(redir->val, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redir->type == APPEND)
		io->fd_out = open(redir->val, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (io->fd_out == -1)
		return (handle_error(redir->val));
	if (cmd->nextpipe)
	{
		signal(SIGINT, newline_hook);
	}
	return (0);
}


int set_fds(t_cmd *cmd, t_io_fd *io, int **fd, int i)
{
    if (cmd->prevpipe || has_redir_in(cmd->ls_redirs))
    {
        if (redir_infile(cmd, io, fd, i) == -1) 
            return -1;
        if (dup2(io->fd_in, STDIN_FILENO) == -1)
        {
            perror("dup2 failed for fd_in");
            return -1;
        }
		// close(io->fd_in);
    }
    if (cmd->nextpipe || has_redir_out(cmd->ls_redirs))
    {
        if (redir_outfile(cmd, io, fd, i) == -1) 
            return -1;
        if (dup2(io->fd_out, STDOUT_FILENO) == -1)
        {
            perror("dup2 failed for fd_out");
            return -1;
        }
		// if(!cmd->nextpipe)
        // 	close(io->fd_out);
    }
    return 0;
}

