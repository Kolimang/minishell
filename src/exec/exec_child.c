/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 11:17:47 by lboumahd          #+#    #+#             */
/*   Updated: 2024/11/26 11:27:59 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_io_fd(t_io_fd *io)
{
	io->pipes = 0;
	io->std_in = dup(STDIN_FILENO);
	io->std_out = dup(STDOUT_FILENO);
	if (io->std_in == -1 || io->std_out == -1)
	{
		perror("Failed to duplicate");
		exit(EXIT_FAILURE);
	}
}

void	close_child(int **fds, int pipes, int i)
{
	int	j;

	j = 0;
	(void)i;
	while (j < pipes)
	{
		close(fds[j][0]);
		close(fds[j][1]);
		j++;
	}
}

void	create_child(t_cmd *cmd, t_io_fd *io, t_envs *envs, t_list *cmds)
{
	if (!ft_strncmp(cmd->args[0], "./minishell", 12))
		signal(SIGINT, SIG_IGN);
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
		close_child(io->fds, io->pipes, 0);
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
