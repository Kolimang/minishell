/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:00:15 by lboumahd          #+#    #+#             */
/*   Updated: 2024/11/22 14:22:23 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	get_command_index(t_list *tmp, t_list *current)
{
	int		index;
	t_list	*cmds;

	cmds = tmp;
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

void	set_index(t_list *cmds)
{
	t_list	*tmp;
	t_cmd	*cmd;

	tmp = cmds;
	while (tmp)
	{
		cmd = tmp->content;
		cmd->i = get_command_index(cmds, tmp);
		tmp = tmp->next;
	}
}

int	process_command(t_list **tmp, t_envs *envs, t_list *cmds, t_io_fd *io)
{
	t_cmd	*cmd;

	cmd = (*tmp)->content;
	create_child(cmd, io, envs, cmds);
	*tmp = (*tmp)->next;
	return (0);
}

int	execute_fork(t_list *cmds, t_io_fd *io, t_envs *envs)
{
	t_list	*tmp;
	int		j;

	tmp = cmds;
	io->pipes = get_pipes(tmp);
	io->fds = prepare_pipes(io->pipes);
	if (!io->fds && io->pipes > 0)
		return (-1);
	set_index(tmp);
	j = -1;
	while (++j < io->pipes)
	{
		if (pipe(io->fds[j]) == -1)
			return (perror("pipe failed"), -1);
	}
	while (tmp && tmp->next)
	{
		if (process_command(&tmp, envs, cmds, io) == -1)
			return (free_all(io->fds, io->pipes));
	}
	if (tmp)
		create_child(tmp->content, io, envs, cmds);
	close_fds(io->fds, io->pipes);
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
	free_fds(fds, pipes);
}
