/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:21:00 by lboumahd          #+#    #+#             */
/*   Updated: 2024/10/28 17:52:16 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int get_infile(t_command *cmd, t_io_fd *io)
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

int redir_infile(t_command *cmd, t_redir *redir, t_io_fd *io, t_list *curr)
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

int	dup_handle(int fd, int target_fd, const char *error_msg)
{
	if (dup2(fd, target_fd) == -1)
	{
		close(fd); // Close the fd on error
		return (handle_error(error_msg)); // Return error
	}
	return (0);
}

int	get_outfile(t_command *cmd, t_io_fd *io)
{
	t_list	*tmp;
	t_redir	*redir;

	tmp = cmd->ls_redirs;
	while (tmp)
	{	
		redir = tmp->content;
		if (redir_outfile(cmd, redir, io) == -1)
			return (-1);
		tmp = tmp->next;
 	}
	return (0);
}

// int	redir_outfile(t_command *cmd, t_redir *redir, t_io_fd *io)
// {
// 	if (redir->type == OUTFILE) // Regular infile
// 	{ 
// 		io->fd_out = open(redir->value,O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 		if (io->fd_out == -1)
// 			return (handle_error("Failed to access outfile"));
// 	}
// 	else if (redir->type == APPEND)
// 	{
// 		io->fd_out = open(redir->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
// 		if (io->fd_out == -1)
// 			return (handle_error("Failed to access outfile"));
// 	}
// 	else
// 		io->fd_out = io->pipe[1];
// 	return (0);
// }
int redir_outfile(t_command *cmd, t_redir *redir, t_io_fd *io)
{
    if (io->fd_out != -2)
        close(io->fd_out);
    if (redir->type == OUTFILE)
		   io->fd_out = open(redir->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redir->type == APPEND)
		io->fd_out = open(redir->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (io->pipe[1] != -1)
        io->fd_out = io->pipe[1];
	else 
		io->fd_out = STDOUT_FILENO;
    if (io->fd_out == -1)
        return (handle_error("Failed to access outfile"));
	if(!cmd->nextpipe && io->pipe[1] != -1)
		close(io->pipe[1]);
    return (0);
}


int set_fds(t_command *cmd, t_io_fd *io) 
{
    t_redir *redir = NULL;
	
	if(cmd && cmd->ls_redirs)
		redir = cmd->ls_redirs->content;
    if (!cmd)
        return_error("Error: NULL command");
    if (cmd->prevpipe || (redir && (redir->type == INFILE || redir->type == HERE_DOC))) 
	{
        if (get_infile(cmd, io) == -1)	
			 return (-1);
        if (dup2(io->fd_in, STDIN_FILENO) == -1)
			return (-1);
        close(io->fd_in);
	}
    if (cmd->nextpipe || (redir && (redir->type == OUTFILE || redir->type == APPEND))) 
	{
		if (get_outfile(cmd, io) == -1)
           return (-1);
		if(dup2(io->fd_out, STDOUT_FILENO) == -1)
            return (-1);
	    close(io->fd_out);
		if(!cmd->nextpipe && io->pipe[1]!= -1)
			close(io->pipe[1]);
    }
    return 0;
}



/////////////Functions get_input and get_output to debugg /////////////////////

// void print_redirection(const char *descriptor, int original_fd, int new_fd, const char *file_name) {
//     printf("%s redirection: original FD %d -> new FD %d (file: %s)\n", descriptor, original_fd, new_fd, file_name);
// }
// int get_infile(t_command *cmd, char *name, t_io_fd *files, int flag) {
//     int fd_tmp;
// 	 (void)cmd;
//     if (flag == 0) // Regular infile
//     {
//         fd_tmp = open(name, O_RDONLY);
//         if (fd_tmp == -1)
//             return (handle_error("Failed to open infile"));
//         files->fd_in = fd_tmp;
//         print_redirection("stdin", STDIN_FILENO, files->fd_in, name);  // Print FD redirection
//         if (dup2(files->fd_in, STDIN_FILENO) == -1)
//         {
//             close(fd_tmp);
//             return (handle_error("Failed to duplicate infile to stdin"));
//         }
//     }
//     else // HERE_DOC
//     {
//         files->fd_in = files->fd_hrdoc;
//         print_redirection("stdin", STDIN_FILENO, files->fd_in, name);  // Print FD redirection
//         if (dup2(files->fd_in, STDIN_FILENO) == -1)
//             handle_error("Failed to duplicate heredoc to stdin");
//         // if (files->fd_hrdoc != -1 && is_last(cmd->ls_redirs))
//         //     close(files->fd_hrdoc);
//     }
//     return (0);
// }


 