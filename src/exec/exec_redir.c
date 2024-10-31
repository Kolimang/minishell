/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:21:00 by lboumahd          #+#    #+#             */
/*   Updated: 2024/10/31 15:10:19 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_last_redir(t_list *ls_redir)
{
	t_list *tmp;
	t_redir *redir;
	int flag;

	tmp = ls_redir;
	while(tmp)
	{
		redir = tmp->content;
		if(redir->type == HERE_DOC)
			flag = 0;
		else if(redir->type == INFILE)
			flag = 1;
		tmp = tmp->next;
	}
	return(flag);
}
int	is_redir_in(t_redir *redir)
{
	if(redir->type == INFILE || redir->type == HERE_DOC)
		return(1);
	return(0);
}
int redir_infile(t_command *cmd, t_io_fd *io)
{
	t_list *tmp;
	t_redir *redir;

	tmp = cmd->ls_redirs;
	while(tmp)
	{
		redir = tmp->content;
		if(is_redir_in(redir))
			if(get_infile(cmd, redir, io) == -1)
				return(-1);
		tmp = tmp->next;
	}
	return(1);
}

int get_infile(t_command *cmd, t_redir *redir, t_io_fd *io)
{
    if (redir->type == INFILE)
    {
        if (io->fd_in > 0)
            close(io->fd_in);
        io->fd_in = open(redir->value, O_RDONLY);
        if (io->fd_in == -1)
            return handle_error("Failed to open infile");
    }
	else if (redir->type == HERE_DOC)
    {
		// if (io->fd_in != cmd->fd_hrdoc)
        //     close(io->fd_in);
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

int	is_redir_out(t_redir *redir)
{
	if(redir->type == OUTFILE || redir->type == APPEND)
		return(1);
	return(0);
}
int redir_outfile(t_command *cmd, t_io_fd *io)
{
	t_list *tmp;
	t_redir *redir;

	tmp = cmd->ls_redirs;
	while(tmp)
	{
		redir = tmp->content;
		if(is_redir_out(redir))
			if(get_outfile(cmd, redir, io) == -1)
				return(-1);
		tmp = tmp->next;
	}
	return(1);
}

int get_outfile(t_command *cmd, t_redir *redir, t_io_fd *io)
{
    if (io->fd_out != -2)
        close(io->fd_out);
    if (redir->type == OUTFILE)
	{
		eprintf("hereoutfile\n");
		io->fd_out = open(redir->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		
	}
	else if (redir->type == APPEND)
		io->fd_out = open(redir->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (io->pipe[1] != -1)
        io->fd_out = io->pipe[1];
	else {
		//eprintf("type = %d; pipe[1] = %d\n", redir->type, io->pipe[1]);
		io->fd_out = STDOUT_FILENO;
	}
    if (io->fd_out == -1)
        return (handle_error("Failed to access outfile"));
	if(!cmd->nextpipe && io->pipe[1] != -1)
		close(io->pipe[1]);
    return (0);
}

int	set_fds(t_command *cmd, t_io_fd *io) 
{
    t_redir *redir = NULL;
    int i = 0;

	
    if (!cmd)
        return_error("Error: NULL command");
	//number of inputs
	//number of outputs?
        // printf("Current redir type: %d\n", redir->type);
        if (cmd->prevpipe || redir_infile(cmd, io)) 
        {
			if (dup2(io->fd_in, STDIN_FILENO) == -1)
    			return eprintf("error1?"), -1;    
			close(io->fd_in);
		}
        // Handle outfile and append redirection
		eprintf("break\n");
        if (cmd->nextpipe || redir_outfile(cmd, io)) 
        {
            if (dup2(io->fd_out, STDOUT_FILENO) == -1)
                return (-1);
            close(io->fd_out);
            if (io->pipe[1] != -1)
                close(io->pipe[1]);
			 
        }
    return 0;
}
