#include <minishell.h>

int	get_command_index(t_list *cmds, t_list *current)
{
	int	index;

	index = 0;
	while (cmds)
	{
		if (cmds == current)
			return (index);
		index++;
		cmds = cmds->next;
	}
	return (-1);
}

int	process_command(t_list **tmp, t_envs *envs, t_list *cmds, t_io_fd *io)
{
	t_cmd	*cmd;

	cmd = (*tmp)->content;
	cmd->i = 0;
	cmd->i = get_command_index(cmds, *tmp);
	if (pipe(io->fds[cmd->i]) == -1)
		return (perror("pipe failed"), -1);
	create_child(cmd, io, envs, cmds);
	*tmp = (*tmp)->next;
	return (0);
}

int	free_all(int **fds, int pipes)
{
	if (fds)
	{
		close_fds(fds, pipes);
		free_fds(fds, pipes);
	}
	return (-1);
}

int	execute_fork(t_list *cmds, t_io_fd *io, t_envs *envs)
{
	t_list	*tmp;

	tmp = cmds;
	io->pipes = get_pipes(tmp);
	io->fds = prepare_pipes(io->pipes);
	if (!io->fds && io->pipes > 0)
		return (-1);
	while (tmp && tmp->next)
	{
		if (process_command(&tmp, envs, cmds, io) == -1)
			return (free_all(io->fds, io->pipes));
	}
	if (tmp)
		create_child(tmp->content, io, envs, cmds);
	close_fds(io->fds, io->pipes);
	free_fds(io->fds, io->pipes);
	wait_children(cmds);
	return (0);
}

void	close_fds(int **fds, int pipes)
{
	int	j;

	j = 0;
	while (j < pipes)
	{
		close(fds[j][0]);
		close(fds[j][1]);
		j++;
	}
}
