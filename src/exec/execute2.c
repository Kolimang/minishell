/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:21:00 by lboumahd          #+#    #+#             */
/*   Updated: 2024/10/17 13:12:35 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execute_redir(t_command *cmd, t_io_fd *files)
{
	t_redir	*redir;

	while (cmd->ls_redirs)
	{
		redir = cmd->ls_redirs->content;
		if (redir->type == INFILE || redir->type == HERE_DOC)
			get_infile();
		if (redir->type == OUTFILE || redir->type == APPEND)
			;// ...
		cmd->ls_redirs = cmd->ls_redirs->next;
	}
}
