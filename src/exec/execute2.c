/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:21:00 by lboumahd          #+#    #+#             */
/*   Updated: 2024/10/21 10:03:33 by jrichir          ###   ########.fr       */
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
int	execute_redir(t_command *cmd, t_io_fd *files)
{
	t_redir *redir;
	int		ret;

	ret = 0;
	while (cmd->ls_redirs)
	{
		redir = cmd->ls_redirs->content;
		if (redir->type == INFILE)
			ret = get_infile(cmd, redir->value, files, 0);
		else if (redir->type == HERE_DOC)
			ret = get_infile(cmd, redir->value, files, 1);
		else if (redir->type == OUTFILE)
			ret = get_outfile(cmd, redir->value, files, 0);
		else if (redir->type == APPEND)
			ret = get_outfile(cmd, redir->value, files, 1);
		if (ret == -1)
			return (ret);
		cmd->ls_redirs = cmd->ls_redirs->next;
	}
	return (0);
}

int	get_infile(t_command *cmd, char *name, t_io_fd *files, int flag)
{
	int	fd_tmp;

	if (flag == 0) // Regular infile
	{
		fd_tmp = open(name, O_RDONLY);
		if (fd_tmp == -1)
			return(handle_error("Failed to open infile"));
		files->fd_in = fd_tmp;
		if (dup2(files->fd_in, STDIN_FILENO) == -1)
			return(handle_error("Failed to duplicate infile to stdin"));
		if(close(fd_tmp) == -1)
			return(-1); // not sure, to check
	}
	else // HERE_DOC
	{
		files->fd_in = files->fd_hrdoc;
		if (dup2(files->fd_in, STDIN_FILENO) == -1)
			handle_error("Failed to duplicate heredoc to stdin");
		if(close(files->fd_hrdoc))
			return (-1); //not sure, to check
			//make sure to reset here-doc at the end
	}
	return(0);
}

int	dup_handle(int fd, int target_fd, const char *error_msg)
{
	 if (dup2(fd, target_fd) == -1)
	{
		close(fd);  // Close the fd on error
		return (handle_error(error_msg));  // Return error
	}
	return (0);
}

int	get_outfile(t_command *cmd, char *name, t_io_fd *files, int flag)
{
	int	fd_tmp;

	(void)cmd;
	if (flag == 0) // Regular outfile
	{
		fd_tmp = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd_tmp == -1)
			return(handle_error("Failed to redirect outfile"));
		files->fd_out = fd_tmp;
		return(dup_handle(files->fd_out, STDOUT_FILENO,
			"Failed to duplicate outfile to stdout"));
	}
	else // append
	{
		fd_tmp = open(name, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd_tmp == -1)
			return (handle_error("Failed to append outfile"));
		files->fd_out = fd_tmp;
		return (dup_handle(files->fd_out, STDOUT_FILENO,
			"Failed to duplicate outfile to stdout"));
	}
	if (close(fd_tmp) == -1)
		return (-1); 
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

// int get_outfile(t_command *cmd, char *name, t_io_fd *files, int flag) {
//     int fd_tmp;
//     (void)cmd; // To be removed
//     if (flag == 0) // Regular outfile
//     {
//         fd_tmp = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
//         if (fd_tmp == -1)
//             return (handle_error("Failed to redirect outfile"));
//         files->fd_out = fd_tmp;
//         print_redirection("stdout", STDOUT_FILENO, files->fd_out, name);  // Print FD redirection
//         return (dup_handle(files->fd_out, STDOUT_FILENO, "Failed to duplicate outfile to stdout"));
//     }
//     else // append
//     {
//         fd_tmp = open(name, O_CREAT | O_WRONLY | O_APPEND, 0644);
//         if (fd_tmp == -1)
//             return (handle_error("Failed to append outfile"));
//         files->fd_out = fd_tmp;
//         print_redirection("stdout", STDOUT_FILENO, files->fd_out, name);  // Print FD redirection
//         return (dup_handle(files->fd_out, STDOUT_FILENO, "Failed to duplicate outfile to stdout"));
//     }
// }
