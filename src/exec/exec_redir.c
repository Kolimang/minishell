/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:21:00 by lboumahd          #+#    #+#             */
/*   Updated: 2024/10/30 11:08:41 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	get_infile(t_command *cmd, t_io_fd *io)
{
    t_list *tmp;
    t_redir *redir;

    tmp = cmd->ls_redirs;
    while (tmp)
    {    
        redir = tmp->content;
        if (redir_infile(cmd, redir, io, tmp) == -1)
            return (-1);
        tmp = tmp->next;
    }
    return (0);
}

int	redir_infile(t_command *cmd, t_redir *redir, t_io_fd *io, t_list *curr)
{
    if (redir->type == INFILE)
    {
        if (io->fd_in > 0)
            close(io->fd_in);  
        io->fd_in = open(redir->value, O_RDONLY);
        if (io->fd_in == -1)
            return handle_error("Failed to open infile");
    }
    if (is_last(curr))
    {
        if (redir->type == HERE_DOC)
        { 
			io->fd_in = cmd->fd_hrdoc;
		}
		
        else if (redir->type == INFILE)
        {
			if (cmd->fd_hrdoc != -3)
			{
				close(cmd->fd_hrdoc);
				cmd->fd_hrdoc = -3;
			}
    	}
	}
    return (0);
}

// int	dup_handle(int fd, int target_fd, const char *error_msg)
// {
// 	if (dup2(fd, target_fd) == -1)
// 	{
// 		close(fd); // Close the fd on error
// 		return (handle_error(error_msg)); // Return error
// 	}
// 	return (0);
// }


// int get_outfile(t_command *cmd, t_io_fd *io)
// {
//     t_list *tmp;
//     t_redir *redir;
    
//     dprintf(2, "Entering get_outfile\n");
//     tmp = cmd->ls_redirs;
//     while (tmp)
//     {
//         redir = tmp->content;
//         if (redir_outfile(cmd, redir, io) == -1)
//             return (-1);
//         tmp = tmp->next;
//     }
//     return (0);
// }
int	get_outfile(t_command *cmd, t_io_fd *io)
{
    t_list *tmp;
    t_redir *redir;
    
    dprintf(2, "Entering get_outfile\n");
    tmp = cmd->ls_redirs;
    
    // Find the last OUTFILE or APPEND redirection
    t_redir *last_out_redir = NULL;
    while (tmp)
    {
        redir = tmp->content;
        if (redir->type == OUTFILE || redir->type == APPEND)
            last_out_redir = redir;
        tmp = tmp->next;
    }
    
    // Process only the last output redirection
    if (last_out_redir)
        return redir_outfile(cmd, last_out_redir, io);
        
    return (0);
}

// int redir_outfile(t_command *cmd, t_redir *redir, t_io_fd *io)
// {
//     if (io->fd_out != -2)
//         close(io->fd_out);
//     if (redir->type == OUTFILE)
// 		io->fd_out = open(redir->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	else if (redir->type == APPEND)
// 		io->fd_out = open(redir->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
// 	else if (io->pipe[1] != -1)
//         io->fd_out = io->pipe[1];
// 	else 
// 		io->fd_out = STDOUT_FILENO;
//     if (io->fd_out == -1)
//         return (handle_error("Failed to access outfile"));
// 	if (!cmd->nextpipe && io->pipe[1] != -1)
// 		close(io->pipe[1]);
//     return (0);
// }
int	redir_outfile(t_command *cmd, t_redir *redir, t_io_fd *io)
{
    dprintf(2, "Entering redir_outfile\n");
    
    // Close existing fd_out if it's not the default
    if (io->fd_out != -2 && io->fd_out != STDOUT_FILENO)
    {
        dprintf(2, "Closing existing fd_out: %d\n", io->fd_out);
        close(io->fd_out);
        io->fd_out = -2;
    }
    
    // Handle only file redirections here
    if (redir->type == OUTFILE)
    {
        dprintf(2, "Opening OUTFILE: %s\n", redir->value);
        io->fd_out = open(redir->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    }
    else if (redir->type == APPEND)
    {
        dprintf(2, "Opening APPEND: %s\n", redir->value);
        io->fd_out = open(redir->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
    }
    
    if (io->fd_out == -1)
    {
        perror("Failed to open output file");
        return (-1);
    }
    
    dprintf(2, "fd_out is now: %d\n", io->fd_out);
    return (0);
}

// int set_fds(t_command *cmd, t_io_fd *io) 
// {
//     t_redir *redir = NULL;
	
// 	if (cmd && cmd->ls_redirs)
// 		redir = cmd->ls_redirs->content;
//     if (!cmd)
//         return_error("Error: NULL command");
//     if (cmd->prevpipe || (redir && (redir->type == INFILE || redir->type == HERE_DOC))) 
// 	{
// 		if (get_infile(cmd, io) == -1)	
// 			 return (-1);
//         if (dup2(io->fd_in, STDIN_FILENO) == -1)
// 			return (-1);
//         close(io->fd_in);
// 	}
//     if (cmd->nextpipe || (redir && (redir->type == OUTFILE || redir->type == APPEND))) 
// 	{
// 		if (get_outfile(cmd, io) == -1)
//            return (-1);
// 		//eprintf("%i\n", io->fd_out);
// 		if (dup2(io->fd_out, STDOUT_FILENO) == -1)
//             return (-1);
// 	    close(io->fd_out);
// 		//eprintf("%i\n", STDOUT_FILENO);
// 		if (!cmd->nextpipe && io->pipe[1]!= -1)
// 			close(io->pipe[1]);
//     }
//     return (0);
// }
int	set_fds(t_command *cmd, t_io_fd *io)
{
    t_redir *redir = NULL;
    
    //debug_print_fds("Before set_fds", cmd, io);
    
    if (!cmd)
        return_error("Error: NULL command");  
    if (cmd && cmd->ls_redirs)
        redir = cmd->ls_redirs->content;
    if (cmd->prevpipe || (redir && (redir->type == INFILE || redir->type == HERE_DOC)))
    {
        if (get_infile(cmd, io) == -1)
            return (-1);   
        dprintf(2, "Duplicating fd_in (%d) to stdin\n", io->fd_in);
        if (dup2(io->fd_in, STDIN_FILENO) == -1)
        {
            perror("dup2 failed for stdin");
            return (-1);
        }
        close(io->fd_in);
        io->fd_in = -1;
    }
   if (redir && (redir->type == OUTFILE || redir->type == APPEND))
    {
        dprintf(2, "Processing OUTFILE redirection\n");
        
        if (get_outfile(cmd, io) == -1)
            return (-1);
            
        dprintf(2, "Got fd_out: %d\n", io->fd_out);
        
        if (dup2(io->fd_out, STDOUT_FILENO) == -1)
        {
            perror("dup2 failed for stdout");
            return (-1);
        }
        
        // Close original fd after duplication
        if (io->fd_out != STDOUT_FILENO)
        {
            close(io->fd_out);
            io->fd_out = -1;
        }
    }
    // Handle pipe output separately
    else if (cmd->nextpipe)
    {
        if (dup2(io->pipe[1], STDOUT_FILENO) == -1)
            return (-1);
        close(io->pipe[1]);
        io->pipe[1] = -1;
    }
    return (0);
}


 