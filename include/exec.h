/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:57:26 by lboumahd          #+#    #+#             */
/*   Updated: 2024/11/16 15:27:23 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

//execute
void	exec(t_list *cmds, t_envs *envs);
int		execute_command(char *pathname, char **full, char **g_env);
int		exec_cmd(t_cmd *cmd, t_io_fd *io, t_envs *envs, t_list *cmds);
int		handle_single_command(t_cmd *cmd, t_io_fd *io);

//exec_child
int		execute_fork(t_list *cmds, t_io_fd *io, t_envs *envs);
int	create_child(t_cmd *cmd, t_io_fd *io, t_envs *envs, t_list *cmds);
int		close_fds(t_cmd *cmd, t_io_fd *io);
void	wait_children(t_list *cmds);
t_io_fd	*initialize_io_fd(void);

//exec_paths
char	*find_path(char **full_cmd, char *cmd);
void	free_tab(char **paths);
char	*get_full_path(char **full_cmd, t_env *l_env);
char	**get_paths(t_env *l_env);
char	*build_full_cmd(char *pathname, t_cmd *cmd);

//exec_builtins
int		execute_nofork(t_cmd *cmd, t_io_fd *io, t_envs *envs, t_list *cmds);
int		pre_exec_builtin(t_cmd *cmd, t_io_fd *io, t_envs *envs, t_list *cmds);
int		exec_builtin(t_cmd *cmd, t_io_fd *io, t_envs *envs, t_list *cmds);
int		is_builtin(char *cmd);

//exec_hrdoc
void	pre_exec(t_list *cmds, t_envs *envs);
t_cmd	*init_hrdoc(t_list *cmd);
int		get_hrdoc(t_cmd *cmd, t_env *l_env);
void	child_hd(t_env *l_env, int pipe_fd[2], t_redir *redir);
int		parent_heredoc_process(t_cmd *cmd, pid_t pid, int pipe_fd[2]);

//exec_redir
int		is_redir_in(t_redir *redir);
int		redir_infile(t_cmd *cmd, t_io_fd *io);
int		get_infile(t_cmd *cmd, t_redir *redir, t_io_fd *io, int fd);
int		is_redir_out(t_redir *redir);
int		redir_outfile(t_cmd *cmd, t_io_fd *io);
int		get_outfile(t_cmd *cmd, t_redir *redir, t_io_fd *io, int fd);
int		set_fds(t_cmd *cmd, t_io_fd *io);
int		has_redir_in(t_list *ls_redir);

//exec_utils
void	init_io_fd(t_io_fd *io);
void	reset_io(t_io_fd *io, t_cmd *cmd);
int		handle_error(const char *msg);
int		is_last(t_list *curr);
void	handle_closing(t_cmd *cmd, t_io_fd *io);

void	return_error(char *arg);

//debbuuuugggg
void	eprintf(const char *format, ...);
void	debug_print_fds(const char *msg, t_cmd *cmd, t_io_fd *io);

#endif
