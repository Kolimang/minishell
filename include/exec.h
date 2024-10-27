/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:57:26 by lboumahd          #+#    #+#             */
/*   Updated: 2024/10/27 18:40:39 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

void	pre_exec(t_list *cmds, t_env *local_env, char **global_env);
void	exec(t_list *cmds, t_env *local_env, char **global_env);
int		get_hrdoc(t_command *cmd, t_env *local_env);
void	child_heredoc_process(t_command *cmd, t_env *local_env, int fd[2]);
int		parent_heredoc_process(t_command *cmd, pid_t pid, int pipe_fd[2]);
int		get_infile(t_command *cmd, t_io_fd *io);
int		redir_infile(t_command *cmd, t_redir *redir, t_io_fd *io);
int		redir_outfile(t_command *cmd, t_redir *redir, t_io_fd *io);
void	reset_io(t_io_fd *io);

int		get_outfile(t_command *cmd, t_io_fd *files);
//int		get_outfile(t_command *cmd, char *name, t_io_fd *files);
void	init_io_fd(t_io_fd *io);
//int		execute_redir(t_command *cmd, t_io_fd *io);
int		is_builtin(char	*cmdname); // uncommented and return type int arbitrarily set by JP
int		handle_error(const char *msg);
int		set_fds(t_command *cmd, t_io_fd *io);
int		execute_fork(t_command *cmd, t_io_fd *io, t_env *l_env, char **g_env);
int		execute_nofork(t_command *cmd, t_io_fd *io, t_env *l_env, char **g_env);
int		exec_builtin(t_command *cmd, t_env *l_env, char **g_env);

#endif
