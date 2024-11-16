/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 11:17:47 by lboumahd          #+#    #+#             */
/*   Updated: 2024/11/16 15:29:41 by lboumahd         ###   ########.fr       */
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
	while (tmp)
	{
		cmd = tmp->content;
		if (tmp->next)
		{
			if (pipe(io->pipe) == -1)
				return (-1);
		}
		io->fd_in = create_child(cmd, io, envs, cmds);
		tmp = tmp->next;
	}
	wait_children(cmds);
	return (0);
}

// int	close_fds(t_cmd *cmd, t_io_fd *io)
// {
// 	if (cmd->prevpipe)
// 		close(io->fd_in);
// 	close(io->pipe[1]);
// 	if (cmd->fd_hrdoc != -3)
// 		close(cmd->fd_hrdoc);
// 	return (0);
// }

int	create_child(t_cmd *cmd, t_io_fd *io, t_envs *envs, t_list *cmds)
{
	cmd->pid = fork();
	signal(SIGINT, sig_handler_child);
	if (cmd->pid == -1)
	{
		handle_error("fork");
		return (-1) ;
	}
	if (cmd->pid == 0)
	{
		if (set_fds(cmd, io) == -1)
			exit(EXIT_FAILURE);	
		if (cmd->args && cmd->args[0])
			exec_cmd(cmd, io, envs, cmds);
		exit(g_ret_val);
	}
	if (cmd->prevpipe)
		close(io->fd_in);
	close(io->pipe[1]);
	if (cmd->fd_hrdoc != -3)
		close(cmd->fd_hrdoc);
	//close_fds(cmd, io);
	return(io->pipe[0]);
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
