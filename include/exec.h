/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:57:26 by lboumahd          #+#    #+#             */
/*   Updated: 2024/10/16 14:16:47 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef struct	s_io_fd
{
	int	fd_pipe[2];
	int	std_in;//backup des stdio
	int	std_out;//backup des stdio
	int	fd_in;//current fd in
	int	fd_out;//current fd out 
	int	fd_hrdoc;//fd_tmp pour HRDOC
}	t_io_fd;

// typedef enum e_tok_type
// {
// 	INFILE = 0,
// 	HERE_DOC,
// 	OUTFILE,
// 	APPEND,	
// }	t_tok_type;

// typedef struct s_list
// {
// 	t_tok_type		type;
// 	char			*name;
// 	char			*hd_delimiter;
// 	struct s_list	*next;
	
// }	t_list;

// typedef struct s_command
// {
// 	int                 pid;//???
// 	int					idx; //??
// 	char                *name;
// 	char                **args;//onlyy args
// 	t_list				*redir;
// 	t_io_fd				*io;
// 	bool				is_pipe;
// 	bool 				is_hrdoc;
// 	struct s_command    *next;
// }	t_command;

#endif