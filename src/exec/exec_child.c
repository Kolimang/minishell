/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 11:17:47 by lboumahd          #+#    #+#             */
/*   Updated: 2024/11/20 17:23:07 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_io_fd	*initialize_io_fd(void)
{
	t_io_fd	*io;

	io = malloc(sizeof(t_io_fd));
	if (!io)
		return (NULL);
	init_io_fd(io);
	return (io);
}

int	get_pipes(t_list *cmds)
{
	int		count;
	t_list	*tmp;

	count = 0;
	tmp = cmds;
	while (tmp && tmp->next)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

void	free_fds(int **fds, int pipes)
{
    int	i;

	i = 0;
	while (i < pipes)
    {
		free(fds[i]);
		i++;
	}
	free(fds);
}

int	**allocate_pipes(int pipe_count)
{
	int	**fds;
	int	j;

	fds = malloc(sizeof(int *) * pipe_count);
	if (!fds)
		return (perror("malloc failed for fds"), NULL);
	j = 0;
	while (j < pipe_count)
	{
		fds[j] = malloc(sizeof(int) * 2);
		if (!fds[j])
		{
			while (--j >= 0)
				free(fds[j]);
			return (free(fds), perror("malloc failed for fds[j]"), NULL);
		}
		j++;
	}
	return (fds);
}

int	**prepare_pipes(int pipe_count)
{
	if (pipe_count <= 0)
		return (NULL);
	return (allocate_pipes(pipe_count));
}

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
	io->pipes = 0;
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

void	close_child(int **fds, int pipes, int i)
{
	int	j;

	j = 0;
	while (j < pipes)
	{
		if (j != i - 1)
			close(fds[j][0]);
		if (j != i)
			close(fds[j][1]);
		j++;
	}
}

void	create_child(t_cmd *cmd, t_io_fd *io, t_envs *envs, t_list *cmds)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (perror("fork failed"));
	if (cmd->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (set_fds(cmd, io) == -1)
		{
			perror("Failed to set file descriptors");
			exit(EXIT_FAILURE);
		}
		if (!cmd->prevpipe && cmd->nextpipe)
			close(io->fds[0][0]);
		else if (cmd->prevpipe && cmd->nextpipe)
			close_child(io->fds, io->pipes, cmd->i);
		else if (cmd->prevpipe && !cmd->nextpipe)
			close(io->fds[cmd->i][1]);
		if (cmd->args && cmd->args[0])
			exec_cmd(cmd, io, envs, cmds);
		exit(EXIT_FAILURE);
	}
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
