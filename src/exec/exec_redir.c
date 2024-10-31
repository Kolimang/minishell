/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:21:00 by lboumahd          #+#    #+#             */
/*   Updated: 2024/10/31 13:24:50 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int get_infile(t_command *cmd, t_io_fd *io, t_list *redirs)
{
	
    t_list *tmp = redirs;
    t_redir *redir;

    // tmp = cmd->ls_redirs;
    while (tmp)
    {    
		eprintf("LINA\n");
        redir = tmp->content;
		// printf("Redirection Type: %d : ", redir->type);
		// printf("Redirection Value: %s\n", redir->value);
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
		 eprintf("hereinfile1\n");
        if (io->fd_in > 0)
            close(io->fd_in);
        io->fd_in = open(redir->value, O_RDONLY);
        if (io->fd_in == -1)
            return handle_error("Failed to open infile");
    }
	else if (redir->type == HERE_DOC)
    {
        // Set fd_in for HERE_DOC only if it's the last node in the list
        // eprintf("heredoc\n");
		if (io->fd_in != cmd->fd_hrdoc)
            close(io->fd_in);
        io->fd_in = cmd->fd_hrdoc;
    }
    
    // if (redir->type == INFILE && is_last(curr))
    // {
    //     if (cmd->fd_hrdoc != -3)
    //     {
    //         close(cmd->fd_hrdoc);
    //         cmd->fd_hrdoc = -3;
    //     }
    // }
    return (0);
}
// Helper function to check if the current node is the last HERE_DOC in the list
// int is_last_heredoc(t_list *node)
// {
//     t_list *tmp = node->next;
//     while (tmp)
//     {
//         t_redir *redir = tmp->content;
//         if (redir->type == HERE_DOC)
//             return (0); // Found another HERE_DOC, so this is not the last
//         tmp = tmp->next;
//     }
//     return (1); // This is the last HERE_DOC
// }
// int get_infile(t_command *cmd, t_io_fd *io)
// {
//     t_list *tmp;
//     t_redir *redir;
//     int last_heredoc_found = 0;

//     tmp = cmd->ls_redirs;
//     while (tmp)
//     {    
//         redir = tmp->content;

//         // Check if we are dealing with the last HERE_DOC type redirection
//         if (redir->type == HERE_DOC && !last_heredoc_found && is_last_heredoc(tmp))
//         {
//             last_heredoc_found = 1;
//         }
//         if (redir_infile(cmd, redir, io, tmp, last_heredoc_found) == -1)
//             return (-1);
        
//         tmp = tmp->next;
//     }
//     return (0);
// }

// int redir_infile(t_command *cmd, t_redir *redir, t_io_fd *io, t_list *curr, int last_heredoc_found)
// {
//     if (redir->type == INFILE)
//     {
//         eprintf("hereinfile\n");
//         if (io->fd_in > 0)
//             close(io->fd_in);
//         io->fd_in = open(redir->value, O_RDONLY);
//         if (io->fd_in == -1)
//             return handle_error("Failed to open infile");
//     }
//     if (redir->type == HERE_DOC && last_heredoc_found)
//     {
//         eprintf("heredoc\n");
//         if (io->fd_in != cmd->fd_hrdoc)
//             close(io->fd_in);
//         io->fd_in = cmd->fd_hrdoc;
//     }
//     return (0);
// }





// int redir_infile(t_command *cmd, t_redir *redir, t_io_fd *io, t_list *curr)
// {
//     if (redir->type == INFILE)
//     {
//         if (io->fd_in > 0)
//             close(io->fd_in);  
//         io->fd_in = open(redir->value, O_RDONLY);
//         if (io->fd_in == -1)
//             return handle_error("Failed to open infile");
//     }
//     if (is_last(curr))
//     {
//         if (redir->type == HERE_DOC)
//         { 
// 			io->fd_in = cmd->fd_hrdoc;
// 		}
		
//         else if (redir->type == INFILE)
//         {
// 			if (cmd->fd_hrdoc != -3)
// 			{
// 				close(cmd->fd_hrdoc);
// 				cmd->fd_hrdoc = -3;
// 			}
//     	}
// 	}
//     return (0);
// }

int get_outfile(t_command *cmd, t_io_fd *io, t_list *redirs)
{
    t_list *tmp = redirs;
    t_redir *redir;
    
    // tmp = cmd->ls_redirs;
	while (tmp)
    {
		redir = tmp->content;
		if (redir_outfile(cmd, redir, io) == -1)
            return (-1);
		tmp = tmp->next;
    }
    return (0);
}

int redir_outfile(t_command *cmd, t_redir *redir, t_io_fd *io)
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

// int set_fds(t_command *cmd, t_io_fd *io) 
// {
//     t_redir *redir = NULL;
	
// 	if(cmd && cmd->ls_redirs)
// 		redir = cmd->ls_redirs->content;
//     if (!cmd)
//         return_error("Error: NULL command");
// 	while(cmd->ls_redirs)
// 	{	
// 		redir = cmd->ls_redirs->content;
// 		if (cmd->prevpipe || (redir && (redir->type == INFILE || redir->type == HERE_DOC))) 
// 	{
// 		if (get_infile(cmd, io) == -1)	
// 				return (-1);				
// 		if (dup2(io->fd_in, STDIN_FILENO) == -1)
// 			return (-1);	
// 		close(io->fd_in);
// 	}
// 	if (cmd->nextpipe || (redir && (redir->type == OUTFILE || redir->type == APPEND))) 
// 	{
// 		eprintf("redir\n");
// 		if (get_outfile(cmd, io) == -1)
// 			return (-1);
// 		if(dup2(io->fd_out, STDOUT_FILENO) == -1)
// 			return (-1);
// 		close(io->fd_out);
// 		if(io->pipe[1]!= -1)
// 			close(io->pipe[1]);
// 	}
// 	cmd->ls_redirs = cmd->ls_redirs->next;
// 	}
//     return 0;
// }
// int set_fds(t_command *cmd, t_io_fd *io) 
// {
//     t_redir *redir = NULL;
   
// 	t_command *og_cmd = cmd; // Store the original list position

//     if (!cmd)
//        return_error("Error: NULL command");
// // 	while(cmd->ls_redirs)
// //    {
// 	 t_list *og_ls_redirs = cmd->ls_redirs;
// 	 t_list *og_ls_redirs2 = cmd->ls_redirs;
// 	 while(og_ls_redirs2)
//     {   
//         redir = og_ls_redirs2->content;
//         if (cmd->prevpipe || (redir && (redir->type == INFILE || redir->type == HERE_DOC))) 
//         {
// 			eprintf("infile\n");
// 			if (get_infile(cmd, io, og_ls_redirs2) == -1)   
//                 return -1;                
//             if (dup2(io->fd_in, STDIN_FILENO) == -1)
//                 return -1;    
//             close(io->fd_in);
//         }
// 		og_ls_redirs2 = og_ls_redirs2->next;
// 	}
// 	while (og_ls_redirs)
// 	{
// 		eprintf("outfile\n");
// 		redir = og_ls_redirs->content;
//         if (cmd->nextpipe || (redir && (redir->type == OUTFILE || redir->type == APPEND))) 
//         {
			
//             if (get_outfile(cmd, io, og_ls_redirs) == -1)
//                 return -1;
//             if (dup2(io->fd_out, STDOUT_FILENO) == -1)
//                 return -1;
//             close(io->fd_out);
//             if (io->pipe[1] != -1)
//                 close(io->pipe[1]);
//         }
// 		og_ls_redirs = og_ls_redirs->next;
//     }
// 		// cmd->ls_redirs = cmd->ls_redirs->next;
// 	//}
//     return 0;
// }
int set_fds(t_command *cmd, t_io_fd *io) 
{
    t_redir *redir = NULL;
    int i = 0;

    if (!cmd)
        return_error("Error: NULL command");

    t_list *current_redir = cmd->ls_redirs;
    while (current_redir)
    {
        redir = current_redir->content;

        // printf("Current redir type: %d\n", redir->type);

        // Handle infile and heredoc redirection
        if ((redir && (redir->type == INFILE || redir->type == HERE_DOC))) 
        {
            // eprintf("infile\n");
            if (get_infile(cmd, io, current_redir) == -1)
                return eprintf("error0?"), -1;                
            if (/* io->fd_out > 1 &&  */dup2(io->fd_in, STDIN_FILENO) == -1)
                return eprintf("error1?"), -1;    
            close(io->fd_in);
        
		}

        // Handle outfile and append redirection
        else if ((redir && (redir->type == OUTFILE || redir->type == APPEND))) 
        {
            if (get_outfile(cmd, io, current_redir) == -1)
                return eprintf("error2?"), -1;
            if (up2(io->fd_out, STDOUT_FILENO) == -1)
                return (-1);
            close(io->fd_out);
            if (io->pipe[1] != -1)
                close(io->pipe[1]);
			 
        }
       current_redir = current_redir->next;
        i++;
    }
    write(2, "here\n", 5);
    return 0;
}


// int set_fds(t_command *cmd, t_io_fd *io) 
// {
//     t_redir *redir = NULL;
//     t_list *original_ls_redirs = cmd->ls_redirs; // Store the original list position

//     if (!cmd)
//         return_error("Error: NULL command");

//     // Process infile by iterating through ls_redirs
//     if (get_infile(cmd, io) == -1)
//         return -1;
//     if (io->fd_in != -1) {
//         if (dup2(io->fd_in, STDIN_FILENO) == -1)
//             return -1;
//         close(io->fd_in);
//     }

//     // Reset ls_redirs to the beginning before processing outfile
//     if(cmd->ls_redirs)
// 		eprintf("exists\n");
// 		// = original_ls_redirs;

//     // Process outfile by iterating through ls_redirs
//     if (get_outfile(cmd, io) == -1)
//         return -1;
//     if (io->fd_out != -1) {
//         if (dup2(io->fd_out, STDOUT_FILENO) == -1)
//             return -1;
//         close(io->fd_out);
//     }

//     return 0;
// }

// int set_fds(t_command *cmd, t_io_fd *io)
// {
//     t_redir *redir = NULL;
//     if(cmd && cmd->ls_redirs)
//         redir = cmd->ls_redirs->content;
//     if (!cmd)
//         return_error("Error: NULL command");
//     while(cmd->ls_redirs)
//     {
//         redir = cmd->ls_redirs->content;
//         if (cmd->prevpipe || (redir && (redir->type == INFILE || redir->type == HERE_DOC)))
// {
//     dprintf(2, "fdhrdoc : %d\n", cmd->fd_hrdoc);
//     dprintf(2, "fd_in : %d\n", cmd->fd_hrdoc);
//     if (get_infile(cmd, io) == -1)
//         return (-1);

//     // Debug fd_in status
//     dprintf(2, "----fd_in status BEFORE read----\n");
//     off_t pos = lseek(io->fd_in, 0, SEEK_CUR);
//     dprintf(2, "Current position: %lld\n", pos);

//     // Test fd_in content with read limit
//     if (redir && redir->type == HERE_DOC) 
//     {
//         char buffer1[4096];
//         ssize_t bytes_read;
//         int read_count = 0;
//         const int MAX_READS = 1;  // Limit number of reads to prevent infinite loop
                
//         dprintf(2, "----Testing fd_in content----\n");
//         while ((bytes_read = read(io->fd_in, buffer1, sizeof(buffer1) - 1)) > 0 
//                && read_count < MAX_READS) 
//         {
//             buffer1[bytes_read] = '\0';
//             dprintf(2, "Bytes read: %zd\n", bytes_read);
//             dprintf(2, "Content: %s\n", buffer1);
//             read_count++;
//         }
        
//         if (bytes_read == -1)
//             dprintf(2, "Read error: %s\n", strerror(errno));
        
//         // Reset position
//        lseek(io->fd_in, 0, SEEK_SET);
//     }

//     if (dup2(io->fd_in, STDIN_FILENO) == -1)
//         return (-1);
    
//     close(io->fd_in);
// }
//         if (cmd->nextpipe || (redir && (redir->type == OUTFILE || redir->type == APPEND)))
//         {
//             if (get_outfile(cmd, io) == -1)
//                 return (-1);
//             if(dup2(io->fd_out, STDOUT_FILENO) == -1)
//                 return (-1);
//             close(io->fd_out);
//             if(io->pipe[1]!= -1)
//                 close(io->pipe[1]);
//         }
//         cmd->ls_redirs = cmd->ls_redirs->next;
//     }
//     return 0;
// }

 