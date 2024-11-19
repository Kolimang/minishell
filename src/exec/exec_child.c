/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 11:17:47 by lboumahd          #+#    #+#             */
/*   Updated: 2024/11/19 12:30:18 by lboumahd         ###   ########.fr       */
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

// int	execute_fork(t_list *cmds, t_io_fd *io, t_envs *envs)
// {
// 	t_cmd	*cmd;
// 	t_list	*tmp;
// 	int		**fds;

// 	tmp = cmds;
// 	io->pipes = get_pipes(tmp);
// 	fds = malloc (sizeof(int *) * io->pipes);
// 	int i = 0;
// 	while (tmp)
// 	{
// 		cmd = tmp->content;
// 		if (!tmp->next)
// 			break ;
// 		if (pipe(fds[i][2]) == -1)
// 			return (-1);
// 		create_child(cmd, io, envs, cmds);
// 		tmp = tmp->next;
// 		i++;
// 	}
// 	if (tmp)
// 		create_child(cmd, io, envs, cmds);
// 	close_fds(fds, io->pipes);
// 	wait_children(cmds);
// 	return (0);
// }
int get_pipes(t_list *cmds)
{
    int count = 0;
    t_list *tmp = cmds;

    while (tmp && tmp->next)
    {
        count++;
        tmp = tmp->next;
    }
    return count;
}
void free_fds(int **fds, int pipes)
{
    for (int i = 0; i < pipes; i++)
        free(fds[i]);
    free(fds);
}
int execute_fork(t_list *cmds, t_io_fd *io, t_envs *envs)
{
    t_cmd *cmd;
    t_list *tmp;
    int **fds;

    tmp = cmds;
    io->pipes = get_pipes(tmp);
    fds = malloc(sizeof(int *) * io->pipes);
    if (!fds)
        return (perror("malloc failed for fds"), -1);
    for (int j = 0; j < io->pipes; j++)
    {
        fds[j] = malloc(sizeof(int) * 2);
        if (!fds[j])
        {
            while (--j >= 0)
                free(fds[j]);
            free(fds);
            return (perror("malloc failed for fds[j]"), -1);
        }
    }
    int i = 0;
    while (tmp && tmp->next)
    {
        cmd = tmp->content;
        if (pipe(fds[i]) == -1)
        {
            perror("pipe failed");
            close_fds(fds, i);
            free_fds(fds, io->pipes);
            return (-1);
        }
        create_child(cmd, io, envs, cmds, fds, i);
        tmp = tmp->next;
		if(tmp->next) 
			i++;
    }
    if (tmp)
    {
        cmd = tmp->content;
        create_child(cmd, io, envs, cmds, fds, i);
    }
    close_fds(fds, io->pipes);
    free_fds(fds, io->pipes);
	wait_children(cmds);
    return (0);
}

void close_fds(int **fds, int pipes)
{
   for (int j = 0; j < pipes; j++)
    {
    	close(fds[j][0]);
        close(fds[j][1]);
    }
}

void create_child(t_cmd *cmd, t_io_fd *io, t_envs *envs, t_list *cmds, int **fds, int i)
{
    cmd->pid = fork();
    if (cmd->pid == -1)
    {
        perror("fork failed");
        return;
    }
    if (cmd->pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        if (set_fds(cmd, io, fds, i) == -1)
        {
            perror("Failed to set file descriptors");
            exit(EXIT_FAILURE);
        }
		 if (!cmd->prevpipe && cmd->nextpipe)  // First command
        {
            // For cat: close read end, keep write end
            close(fds[0][0]);
        }
        else if (cmd->prevpipe && !cmd->nextpipe)  // Last command
        {
            close(fds[0][1]);
        }
        else if (cmd->prevpipe && cmd->nextpipe)  // Middle command (for longer pipes)
        {
            for (int j = 0; j < io->pipes; j++)
            {
                if (j != i - 1)
                    close(fds[j][0]);
                if (j != i)
                    close(fds[j][1]);
            }
        }
        if (cmd->args && cmd->args[0])
            exec_cmd(cmd, io, envs, cmds);
        exit(EXIT_FAILURE);
    }
}

// int close_fds(t_cmd *cmd, t_io_fd *io)
// {
//     if (!cmd->nextpipe)
//         close(io->pipe[1]);
//     if (io->pipe[0] != -1 && cmd->prevpipe)
//         close(io->pipe[0]);  
//     if (cmd->fd_hrdoc != -3)
//         close(cmd->fd_hrdoc);
//     return (0);
// }

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
