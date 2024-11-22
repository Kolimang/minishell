/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:38:49 by lboumahd          #+#    #+#             */
/*   Updated: 2024/11/22 13:04:22 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

void	set_infile(t_cmd *cmd, t_io_fd *io)
{
	if (cmd->prevpipe)
		cmd->fd_in = io->fds[cmd->i - 1][0];
	else
		cmd->fd_in = STDIN_FILENO;
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
		set_infile(cmd, io);
	return (1);
}

int	get_infile(t_cmd *cmd, t_redir *redir, t_io_fd *io)
{
	(void)io;
	if (redir->type == INFILE)
	{
		if (cmd->fd_in > 0)
			close(cmd->fd_in);
		cmd->fd_in = open(redir->val, O_RDONLY);
		if (cmd->fd_in == -1)
			return (handle_error(redir->val));
	}
	else if (redir->type == HERE_DOC)
	{
		if (cmd->fd_in != cmd->fd_hrdoc)
			close(cmd->fd_in);
		cmd->fd_in = cmd->fd_hrdoc;
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
