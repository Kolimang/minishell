/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:38:49 by lboumahd          #+#    #+#             */
/*   Updated: 2024/11/15 12:41:06 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

int	is_last_redir(t_list *ls_redir)
{
	t_list	*tmp;
	t_redir	*redir;
	int		flag;

	tmp = ls_redir;
	while (tmp)
	{
		redir = tmp->content;
		if (redir->type == HERE_DOC)
			flag = 0;
		else if (redir->type == INFILE)
			flag = 1;
		tmp = tmp->next;
	}
	return (flag);
}

int	is_redir_in(t_redir *redir)
{
	if (redir->type == INFILE || redir->type == HERE_DOC)
		return (1);
	return (0);
}

int	redir_infile(t_cmd *cmd, t_io_fd *io)
{
	t_list	*tmp;
	t_redir	*redir;
	int		has_infile;

	has_infile = 0;
	tmp = cmd->ls_redirs;
	while (tmp)
	{
		redir = tmp->content;
		if (is_redir_in(redir))
		{
			if (get_infile(cmd, redir, io) == -1)
				return (-1);
			has_infile = 1;
		}
		tmp = tmp->next;
	}
	if (!has_infile)
	{
		if (cmd->prevpipe)
			io->fd_in = io->pipe[0];
		else
			io->fd_in = STDIN_FILENO;
	}
	return (1);
}

int	get_infile(t_cmd *cmd, t_redir *redir, t_io_fd *io)
{
	if (redir->type == INFILE)
	{
		if (io->fd_in > 0)
			close(io->fd_in);
		io->fd_in = open(redir->val, O_RDONLY);
		if (io->fd_in == -1)
			return (handle_error(redir->val));
	}
	else if (redir->type == HERE_DOC)
	{
		if (io->fd_in != cmd->fd_hrdoc)
			close(io->fd_in);
		io->fd_in = cmd->fd_hrdoc;
	}
	if (redir->type == INFILE && is_last_redir(cmd->ls_redirs))
	{
		if (cmd->fd_hrdoc != -3)
		{
			close(cmd->fd_hrdoc);
			cmd->fd_hrdoc = -3;
		}
	}
	return (0);
}