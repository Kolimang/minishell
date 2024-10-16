/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:21:00 by lboumahd          #+#    #+#             */
/*   Updated: 2024/10/16 16:30:57 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_redir(t_command *cmd, t_io_fd *files)
{
	while(cmd->redir)
	{
		if(cmd->redir->type == INFILE || cmd->redir->type == HERE_DOC)
			get_infile();
		if(cmd->redir->type == OUTFILE || cmd->redir->type == APPEND)

		;
		cmd->redir = cmd->redir->next;
	}
}

