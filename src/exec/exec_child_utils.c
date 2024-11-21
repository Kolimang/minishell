/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:00:05 by lboumahd          #+#    #+#             */
/*   Updated: 2024/11/21 17:00:09 by lboumahd         ###   ########.fr       */
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
