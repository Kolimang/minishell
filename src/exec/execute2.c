/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:21:00 by lboumahd          #+#    #+#             */
/*   Updated: 2024/10/17 15:43:59 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	handle_error(const char *msg)
{
	perror(msg);
	return (-1); 
}

int	is_last(t_list *redirs)
{
	return (redirs && redirs->next == NULL);
}
void	execute_redir(t_command *cmd, t_io_fd *files)
{
	t_redir *redir;

	while (cmd->ls_redirs)
	{
		redir = cmd->ls_redirs->content;

		if (redir->type == INFILE)
			get_infile(cmd, redir->value, files, 0);
		else if (redir->type == HERE_DOC)
			get_infile(cmd, redir->value, files, 1);
		else if (redir->type == OUTFILE)
			get_outfile(cmd, redir->value, files, 0);
		else if (redir->type == APPEND)
			get_outfile(cmd, redir->value, files, 1);

		cmd->ls_redirs = cmd->ls_redirs->next;
	}
}

int	get_infile(t_command *cmd, char *name, t_io_fd *files, int flag)
{
	int	fd_tmp;

	if (flag == 0) // Regular infile
	{
		fd_tmp = open(name, O_RDONLY);
		if (fd_tmp == -1)
			return (handle_error("Failed to open infile"));
		files->fd_in = fd_tmp;
		if (dup2(files->fd_in, STDIN_FILENO) == -1)
			return (handle_error("Failed to duplicate infile to stdin"));
		close(fd_tmp);
	}
	else // HERE_DOC
	{
		files->fd_in = files->fd_hrdoc;
		if (dup2(files->fd_in, STDIN_FILENO) == -1)
			handle_error("Failed to duplicate heredoc to stdin");
		if (files->fd_hrdoc != -1 && is_last(cmd->ls_redirs))
		{
			close(files->fd_hrdoc);
			files->fd_hrdoc = -1;
		}
	}
	return (0);
}

void	get_outfile(t_command *cmd, char *name, t_io_fd *files, int flag)
{
	int	fd_tmp;

	if (flag == 0)//outfile
	{
		fd_tmp = open(name, O_RDONLY);
		if (dup2(files->fd_out,) == -1);
		//return error if no fork, exit if fork
	}
	else
	{
		fd_tmp = open(name, O_RDONLY);
	}
}
