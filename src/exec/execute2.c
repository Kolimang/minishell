/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:21:00 by lboumahd          #+#    #+#             */
/*   Updated: 2024/10/24 13:09:09 by lboumahd         ###   ########.fr       */
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
	t_command *tmp;
	t_redir	*redir;
	int		ret;

	tmp = cmd;
	ret = 0;
	while (tmp->ls_redirs)
	{
		redir = cmd->ls_redirs->content;
		if (redir->type == INFILE || redir->type == HERE_DOC)
			ret = redir_infile(tmp, redir->value, files, redir->type);
		else if (redir->type == OUTFILE || redir->type == APPEND )
			ret = redir_outfile(tmp, redir->value, files, redir->type);
		if (ret == -1)
			return (ret);
		tmp->ls_redirs = tmp->ls_redirs->next;
	}
	return (0);
}

int	redir_infile(t_command *cmd, char *name, t_io_fd *files, int flag)
{
	int	fd_tmp;

	if (flag == INFILE) // Regular infile
	{
		fd_tmp = open(name, O_RDONLY);
		if (fd_tmp == -1)
			return (handle_error("Failed to open infile"));
		files->fd_in = fd_tmp;
		if (dup2(files->fd_in, STDIN_FILENO) == -1)
			return (handle_error("Failed to duplicate infile to stdin"));
		if (close(fd_tmp) == -1)
			return (-1); // not sure, to check
	}
	else if (flag == HERE_DOC) // HERE_DOC
	{
		//not sure of the fd_hrdoc closing 
		files->fd_in = cmd->fd_hrdoc;
		if (dup2(files->fd_in, STDIN_FILENO) == -1)
			handle_error("Failed to duplicate heredoc to stdin");
		if (close(cmd->fd_hrdoc))
			return (-1); //not sure, to check
			//make sure to reset here-doc at the end
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

int	redir_outfile(t_command *cmd, char *name, t_io_fd *files, int flag)
{
	int	fd_tmp;

	(void)cmd;
	if (flag == OUTFILE) // Regular outfile
	{
		fd_tmp = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd_tmp == -1)
			return (handle_error("Failed to redirect outfile"));
		files->fd_out = fd_tmp;
		return (dup_handle(files->fd_out, STDOUT_FILENO,
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



void	get_infile(t_command *cmd, t_io_fd *io)
 {
	t_list *tmp;
	t_redir *redir;

	tmp = cmd->ls_redirs;
	if(tmp)
	{
		while (tmp)
		{	
			redir = tmp->content;
			redir_infile(cmd, redir->value, io, redir->type);
			tmp = tmp->next;
 		}
		return
	else
		if (dup2(io->fd_in, STDIN_FILENO) == -1)
			return (handle_error("Failed to duplicate infile to stdin"));
	
 }