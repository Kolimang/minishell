/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 11:17:47 by lboumahd          #+#    #+#             */
/*   Updated: 2024/11/03 16:43:08 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//check EXIIIIIIT attention 
void	exec(t_list *cmds, t_env *local_env, char **global_env) 
{
	t_command	*cmd;
	t_io_fd		*io;

	t_env		*env = local_env;
	cmd = cmds->content;
	if (cmds)
	{
		io = malloc(sizeof(t_io_fd));
		if (!io)
			return_error("Failed to allocate memory for io_fd");
		init_io_fd(io);
		cmd = cmds->content;
		if (cmds->next == NULL && !(cmd->args[0]))
		{
			if (set_fds(cmd, io) == -1)
			{
				reset_io(io, cmd);
				return ;
			}
		}
		else
		{
			cmd->builtin = is_builtin(cmd->args[0]);
			if (cmd->builtin && !(cmds->next))
				execute_nofork(cmd, io, local_env, global_env);
			else
				execute_fork(cmds, io, local_env, global_env);
		}
		reset_io(io, cmd);
	}
	return ;
}

int	execute_fork(t_list *cmds, t_io_fd *io, t_env *l_env, char **g_env)
{
	t_command	*cmd;
	t_list		*tmp;

	tmp = cmds;
	while (tmp)
	{
		cmd = tmp->content;
		if (!tmp->next)
			break ;
		if (pipe(io->pipe) == -1)
			return (-1);
		create_child(cmd, io, l_env, g_env);
		tmp = tmp->next;
	}
	if (tmp)
		create_child(cmd, io, l_env, g_env);
	wait_children(cmds);
	return (0);
}

void	create_child(t_command *cmd, t_io_fd *io, t_env *l_env, char **g_env)
{
	t_redir	*redir;

	if (cmd->ls_redirs)
		redir = cmd->ls_redirs->content;
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		handle_error("fork");
		return ;
	}
	if (cmd->pid == 0)
	{
		if (set_fds(cmd, io) == -1)
			exit(EXIT_FAILURE);
		if (cmd->args)
			exec_cmd(cmd, l_env, g_env);
		exit(g_ret_value);
	}
	if (cmd->prevpipe)
		close(io->fd_in);
	if (io->pipe[0] != -1)
		close(io->pipe[1]);
	if (cmd->fd_hrdoc != -3)
		close(cmd->fd_hrdoc);
	io->fd_in = io->pipe[0];
}

void	wait_children(t_list *cmds)
{
	t_command	*cmd;
	t_list		*tmp;
	int			status;

	tmp = cmds;
	while (tmp)
	{
		cmd = tmp->content;
		waitpid(cmd->pid, &status, 0);
		if (WIFEXITED(status))
			g_ret_value = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_ret_value = 128 + WTERMSIG(status);
		tmp = tmp->next;
	}
}
