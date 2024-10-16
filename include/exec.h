/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:57:26 by lboumahd          #+#    #+#             */
/*   Updated: 2024/10/16 15:55:07 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

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

void	pre_exec(t_list *cmds, t_env *local_env, char **global_env);
void	exec(t_list *cmds, t_env *local_env, char **global_env);
void	get_hrdoc(t_command *cmd, t_env *local_env, t_io_fd *io);

// Non existant yet
init_io_fd(t_io_fd *io);
execute_redir(t_list *cmds, t_io_fd *io);
is_builtin(char	*cmdname);
execute_fork(t_list *cmds, t_env *local_env, char **global_env);
execute_nofork(t_list *cmds, t_env *local_env, char **global_env);

#endif
