/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:57:26 by lboumahd          #+#    #+#             */
/*   Updated: 2024/10/18 13:08:17 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

void	pre_exec(t_list *cmds, t_env *local_env, char **global_env);
void	exec(t_list *cmds, t_env *local_env, char **global_env);
void	get_hrdoc(t_command *cmd, t_env *local_env, t_io_fd *io);

// Non existant yet
void	init_io_fd(t_io_fd *io);
int execute_redir(t_command *cmd, t_io_fd *io);
// is_builtin(char	*cmdname);
// execute_fork(t_command *cmd, t_env *local_env, char **global_env);
// execute_nofork(t_command *cmd, t_env *local_env, char **global_env);

void	child_heredoc_process(t_command *cmd, t_env *local_env, int fd[2]);
int	parent_heredoc_process(t_command *cmd, pid_t pid, int pipe_fd[2]);
void	reset_io(t_command *cmd);
int	get_outfile(t_command *cmd, char *name, t_io_fd *files, int flag);
int	get_infile(t_command *cmd, char *name, t_io_fd *files, int flag);

#endif
