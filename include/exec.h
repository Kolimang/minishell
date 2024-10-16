/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:57:26 by lboumahd          #+#    #+#             */
/*   Updated: 2024/10/16 16:20:32 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
typedef struct	s_io_fd
{
	int	fd_pipe[2];
	int	std_in;//backup des stdio
	int std_out;//backup des stdio
	int	fd_in;//current fd in
	int	fd_out;//current fd out 
	int fd_hrdoc;//fd_tmp pour HRDOC
}	t_io_fd;

typedef enum e_tkn_type
{
	INFILE = 0,
	HERE_DOC,
	OUTFILE,
	APPEND,	
}t_tkn_type;

typedef struct s_list
{
	t_tkn_type		type;
	char			*name;
	char			*hr_delimiter;
	struct s_list	*next;
	
}t_list;
typedef struct s_command
{
	int                 pid;//???
	int					idx; //??
	char                *name;
	char                **args;//onlyy args
	t_redi				*redir;
	t_io_fd				*io;
	bool				is_pipe;
	bool 				is_hrdoc;
	struct s_command    *next;
}   t_command;
#endif