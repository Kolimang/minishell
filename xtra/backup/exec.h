/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:57:26 by lboumahd          #+#    #+#             */
/*   Updated: 2024/11/14 15:43:07 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

//execute
void		exec(t_list *cmds, t_envs *envs);
int			execute_fork(t_list *cmds, t_io_fd *io, t_envs *envs);
void		create_child(t_command *cmd, t_io_fd *io, t_envs *envs, t_list *cmds);
int	        close_fds(t_command *cmd, t_io_fd *io);
void		wait_children(t_list *cmds);

//execute1
//int		execute_nofork(t_command *cmd, t_io_fd *io, t_env **l_env, char **g_env);
//int			execute_nofork(t_command *cmd, t_io_fd *io, t_env **l_env, t_list *cmds);
int	        execute_nofork(t_command *cmd, t_io_fd *io, t_envs *envs, t_list *cmds);
//int		exec_builtin(t_command *cmd, t_env **l_env, char **g_env, int flag);
int			exec_builtin(t_command *cmd, t_envs *envs, t_list *cmds, int flag);
int			is_builtin(char *cmd);
int			exec_cmd(t_command *cmd, t_envs *envs, t_list *cmds);
char		*find_path(char **full_cmd, char *cmd);
void		free_tab(char **paths);
char		*get_full_path(char **full_cmd, t_env *l_env);
char		**get_paths(t_env *l_env);

//exec_hrdoc
void		pre_exec(t_list *cmds, t_envs *envs);
t_command	*init_hrdoc (t_list *cmd);
int			get_hrdoc(t_command *cmd, t_env *local_env);
void		child_heredoc_process(t_command *cmd, t_env *local_env, int	pipe_fd[2], t_redir *redir);
int			parent_heredoc_process(t_command *cmd, pid_t pid, int pipe_fd[2]);

//exec_redir
int			is_redir_in(t_redir *redir);
int			redir_infile(t_command *cmd, t_io_fd *io);
int			get_infile(t_command *cmd, t_redir *redir, t_io_fd *io);
int			is_redir_out(t_redir *redir);
int			redir_outfile(t_command *cmd, t_io_fd *io);
int			get_outfile(t_command *cmd, t_redir *redir, t_io_fd *io);
int			set_fds(t_command *cmd, t_io_fd *io) ;

//exec_utils
void		init_io_fd(t_io_fd *io);
void		reset_io(t_io_fd *io, t_command *cmd);
int			handle_error(const char *msg);
int			is_last(t_list *curr);
// int			is_last(t_list *curr, t_redir *redir);
void		handle_closing(t_command *cmd, t_io_fd *io);

void		return_error(char *arg);

//debbuuuugggg
void		eprintf(const char *format, ...);
void		debug_print_fds(const char* msg, t_command *cmd, t_io_fd *io);

#endif
