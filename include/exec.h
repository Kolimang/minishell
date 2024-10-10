/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:57:26 by lboumahd          #+#    #+#             */
/*   Updated: 2024/10/10 18:58:08 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
typedef struct	s_io_fd
{
	int	fd_pipe[2];
	int	std_in;
	int std_out;
	int	fd_in;
	int	fd_out;
	int fd_hrdoc;
}	t_io_fd;

typedef struct s_command
{
	int                 pid;
	char                *name;
	char                *options;
	char                **args;
	t_io_fd				*io;
	bool				is_pipe;
	struct s_command    *next;
}   t_command;
#endif