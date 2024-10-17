/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:57:26 by lboumahd          #+#    #+#             */
/*   Updated: 2024/10/17 12:38:21 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

void	pre_exec(t_list *cmds, t_env *local_env, char **global_env);
void	exec(t_list *cmds, t_env *local_env, char **global_env);
void	get_hrdoc(t_command *cmd, t_env *local_env, t_io_fd *io);

// Non existant yet
void	init_io_fd(t_io_fd *io);
execute_redir(t_command *cmd, t_io_fd *io);
is_builtin(char *cmdname);
execute_fork(t_command *cmd, t_env *local_env, char **global_env);
execute_nofork(t_command *cmd, t_env *local_env, char **global_env);

#endif
