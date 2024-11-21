/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 11:17:47 by lboumahd          #+#    #+#             */
/*   Updated: 2024/11/21 18:18:59 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_io_fd	*initialize_io_fd(void)
{
	t_io_fd	*io;

	io = malloc(sizeof(t_io_fd));
	if (io)
		init_io_fd(io);
	return (io);
}

int	execute_fork(t_list *cmds, t_io_fd *io, t_envs *envs)
{
	t_cmd	*cmd;
	t_list	*tmp;

	tmp = cmds;
	//init child count
	while (tmp)
	{
		cmd = tmp->content;
		create_child(tmp, io, envs, cmds);
		tmp = tmp->next;
	}
	wait_children(cmds);
	return (0);
}

void	create_child(t_list *cmds, t_io_fd *io, t_envs *envs, t_list *all)
{
	int pipes[2];

	t_cmd *cmd = cmds->content;
	if (cmds->next)
	{
		if(pipe(io->pipe) == -1)
		{
			exit(1);
		}
	}
	cmd->pid = fork();
	signal(SIGINT, sig_handler_child);
	if (cmd->pid == -1)
	{
		handle_error("fork");
		return ;
	}
	if(pipe(pipes) == -1)
		exit(1);
	if (cmd->pid == 0)
		is_child(cmd, io, all, envs);
	else
		is_parent(cmds, io);
}

void is_child(t_list *cmds, t_io_fd *io, t_list *all, t_envs *envs)
{
	t_cmd *cmd;
	if(io->fd_in != STDIN_FILENO)
	{
		dup2(io->fd_in, STDIN_FILENO);
		close(io->fd_in);
	}
	if(cmds->next)
	{
		dup2(io->pipe[1], STDOUT_FILENO);
		close(io->pipe[1]);
		close(io->pipe[0]);
	}
	set_fds(cmd, io);
	exec_cmd(cmd, io, envs, all);
}
void	wait_children(t_list *cmds)
{
	t_cmd	*cmd;
	t_list	*tmp;
	int		status;

	tmp = cmds;
	while (tmp)
	{
		cmd = tmp->content;
		waitpid(cmd->pid, &status, 0);
		if (WIFEXITED(status))
			g_ret_val = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_ret_val = 128 + WTERMSIG(status);
		tmp = tmp->next;
	}
}
