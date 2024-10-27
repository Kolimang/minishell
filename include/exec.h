/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:57:26 by lboumahd          #+#    #+#             */
/*   Updated: 2024/10/27 20:04:59 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

//execute
void	exec(t_list *cmds, t_env *local_env, char **global_env);
int		execute_fork(t_list *cmds, t_io_fd *io, t_env *l_env, char **g_env);
int		create_child(t_command *cmd, t_io_fd *io, t_env *l_env, char **g_env);
void	wait_children(t_list *cmds);

//execute1
int		execute_nofork(t_command *cmd, t_io_fd *io, t_env *l_env, char **g_env);
int		exec_builtin(t_command *cmd, t_env *l_env, char **g_env);
int		is_builtin(char *cmd);
void	exec_cmd(t_command *cmd, t_env *local, char **global);
char	*check_path(char **full_cmd, char *cmd);

//exec_hrdoc
void	pre_exec(t_list *cmds, t_env *local_env, char **global_env);
void	init_hrdoc (t_command *cmd);
int		get_hrdoc(t_command *cmd, t_env *local_env);
void	child_heredoc_process(t_command *cmd, t_env *local_env, int	pipe_fd[2]);
int		parent_heredoc_process(t_command *cmd, pid_t pid, int pipe_fd[2]);

//exec_redir
int		redir_infile(t_command *cmd, t_redir *redir, t_io_fd *io, t_list *curr);
int		dup_handle(int fd, int target_fd, const char *error_msg);
int		get_infile(t_command *cmd, t_io_fd *io);
int		get_outfile(t_command *cmd, t_io_fd *io);
int		redir_outfile(t_command *cmd, t_redir *redir, t_io_fd *io);
int		set_fds(t_command *cmd, t_io_fd *io);

//exec_utils
void	init_io_fd(t_io_fd *io);
void	reset_io(t_io_fd *io, t_command *cmd);
int		handle_error(const char *msg);
int		is_last(t_list *redirs);
void	handle_closing(t_command *cmd, t_io_fd *io);

//access
char	*get_full_path(char **full_cmd, char **env);
char	**get_paths(char **env);
void	check_pid(int pid);
void	free_tab(char **paths);


void	return_error(char *arg);

#endif
