/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_out.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:21:00 by lboumahd          #+#    #+#             */
/*   Updated: 2024/11/22 14:16:15 by lboumahd         ###   ########.fr       */
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
		}
		tmp = tmp->next;
	}
	if (!has_outfile)
	{
		if (cmd->nextpipe)
			cmd->fd_out = io->fds[cmd->i][1];
		else
			cmd->fd_out = STDOUT_FILENO;
	}
	return (1);
}

int	get_outfile(t_cmd *cmd, t_redir *redir, t_io_fd *io)
{
	(void)io;
	if (cmd->fd_out != STDOUT_FILENO)
		close(cmd->fd_out);
	if (redir->type == OUTFILE)
		cmd->fd_out = open(redir->val, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redir->type == APPEND)
		cmd->fd_out = open(redir->val, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (cmd->fd_out == -1)
		return (handle_error(redir->val));
	if (cmd->nextpipe)
		signal(SIGINT, newline_hook);
	return (0);
}

int	set_fds(t_cmd *cmd, t_io_fd *io)
{
	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
	if (redir_infile(cmd, io) == -1)
		return (-1);
	if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
	{
		perror("dup2 failed for fd_in");
		return (-1);
	}
	if (cmd->fd_in != STDIN_FILENO)
		close(cmd->fd_in);
	if (redir_outfile(cmd, io) == -1)
		return (-1);
	if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
	{
		perror("dup2 failed for fd_out");
		return (-1);
	}
	if (cmd->fd_out != STDOUT_FILENO)
		close(cmd->fd_out);
	return (0);
}
