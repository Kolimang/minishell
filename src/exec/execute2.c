/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:21:00 by lboumahd          #+#    #+#             */
/*   Updated: 2024/10/24 18:21:28 by lboumahd         ###   ########.fr       */
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

int	redir_infile(t_command *cmd, t_redir *redir, t_io_fd *io)
{
	if(io->fd_tmp != -2)
		close(io->fd_tmp);
	if (redir->type == INFILE) // Regular infile
	{
		io->fd_tmp = open(redir->value, O_RDONLY);
		if (io->fd_tmp == -1)
			return (handle_error("Failed to open infile"));
		io->fd_in = io->fd_tmp;
	}
	//heredoc case not completed : closing
	else if (redir->type == HERE_DOC && is_last(cmd->ls_redirs))
		io->fd_in = cmd->fd_hrdoc;
	else if (redir->type == HERE_DOC)
		close(cmd->fd_hrdoc);
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

int	get_infile(t_command *cmd, t_io_fd *io)
{
	t_list *tmp;
	t_redir *redir;

	tmp = cmd->ls_redirs;
	while (tmp)
	{	
		redir = tmp->content;
		if(redir_infile(cmd, redir, io) == -1)
			return(-1);
		tmp = tmp->next;
 	}
	return (0);
}


int	redir_outfile(t_command *cmd, t_redir *redir, t_io_fd *io)
{
	if(io->fd_tmp != -2)
		close(io->fd_tmp);
	if (redir->type == OUTFILE) // Regular infile
	{
		io->fd_tmp = open(redir->value,O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (io->fd_tmp == -1)
			return (handle_error("Failed to access outfile"));
		io->pipe[1] = io->fd_tmp;
	}
	else if (redir->type == APPEND)
	{
		io->fd_tmp = open(redir->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if(io->fd_tmp = -1)
			return (handle_error("Failed to access outfile"));
		io->pipe[1] = io->fd_tmp;
	}
}

 
int	set_fds(t_command *cmd, t_io_fd *io)
{
	t_redir	*redir;
	int	ret;

	redir = cmd->ls_redirs->content;
	if(cmd->prevpipe || redir->type == INFILE || redir->type == HERE_DOC)
	{
		if(get_infile(cmd, cmd->ls_redirs, io) == -1);
			return(-1);
		if(dup2(io->fd_in, STDIN_FILENO) == -1)
			return(-1);
		if(close(io->fd_in) == -1)
			error();//set error ? a voir 
	}
	//anything from stdout drop it into write end of pipe
	if(cmd->nextpipe || redir->type == OUTFILE || redir->type == APPEND)
	{
		if(get_outfile(cmd, cmd->ls_redirs, io) == -1);
			return(-1);
		if(dup2(io->pipe[1], STDOUT_FILENO) == -1)
			return(-1);
		close(io->pipe[1]);
	}
	if(cmd->nextpipe)
		close(io->pipe[0]);
	return(0);
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
