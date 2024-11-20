/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 11:17:47 by lboumahd          #+#    #+#             */
/*   Updated: 2024/11/20 13:27:19 by lboumahd         ###   ########.fr       */
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
int **allocate_pipes(int pipe_count)
{
    int **fds;
	int	j;

    fds = malloc(sizeof(int *) * pipe_count);
    if (!fds)
    {
        perror("malloc failed for fds");
        return (NULL);
    }
   j = 0;
   while(j < pipe_count)
    {
        fds[j] = malloc(sizeof(int) * 2);
        if (!fds[j])
        {
            while (--j >= 0)
                free(fds[j]);
            free(fds);
            perror("malloc failed for fds[j]");
            return (NULL);
        }
		j++;
    }
    return (fds);
}

// int execute_fork(t_list *cmds, t_io_fd *io, t_envs *envs)
// {
//     t_cmd *cmd;
//     t_list *tmp;
//     int **fds;

//     tmp = cmds;
//     io->pipes = get_pipes(tmp);
//   	if (io->pipes > 0)
//     {
//         fds = allocate_pipes(io->pipes);
//         if (!fds)
//             return (-1);
//     }
//     else
//         fds = NULL;
//     int i = 0;
//     while (tmp && tmp->next)
//     {
//         cmd = tmp->content;
//         if (pipe(fds[i]) == -1)
//         {
//             perror("pipe failed");
//             close_fds(fds, i);
//             free_fds(fds, io->pipes);
//             return (-1);
//         }
//         create_child(cmd, io, envs, cmds, fds, i);
//         tmp = tmp->next;
// 		if(tmp->next) 
// 			i++;
//     }
//     if (tmp)
//     {
//         cmd = tmp->content;
//         create_child(cmd, io, envs, cmds, fds, i);
//     }
//     close_fds(fds, io->pipes);
//     free_fds(fds, io->pipes);
// 	wait_children(cmds);
//     return (0);
// }
int **prepare_pipes(int pipe_count)
{
    int **fds;

    if (pipe_count <= 0)
        return (NULL);
    fds = allocate_pipes(pipe_count);
    if (!fds)
        perror("Failed to allocate pipes");
    return (fds);
}
int process_command(t_list **tmp, t_envs *envs, t_list *cmds, t_io_fd *io)
{
    t_cmd *cmd;

    cmd = (*tmp)->content;
    cmd->i = get_command_index(cmds, *tmp); // Assign the correct index to cmd->i
    if (pipe(io->fds[cmd->i]) == -1) // Use io->fds
    {
        perror("pipe failed");
        return (-1);
    }
    create_child(cmd, io, envs, cmds); // Pass io instead of fds
    *tmp = (*tmp)->next; // Move to the next command in the list
    return (0);
}

int free_all(int **fds, int pipes)
{
    if (fds)
    {
        close_fds(fds, pipes);
        free_fds(fds, pipes);
    }
    return (-1);
}
int execute_fork(t_list *cmds, t_io_fd *io, t_envs *envs)
{
    t_list *tmp;

    tmp = cmds;
    io->pipes = get_pipes(tmp);
    io->fds = prepare_pipes(io->pipes); // Prepare fds directly in io->fds
    if (!io->fds && io->pipes > 0)
        return (-1);

    while (tmp && tmp->next)
    {
        if (process_command(&tmp, envs, cmds, io) == -1) // Pass io with fds
            return (free_all(io->fds, io->pipes));
    }
    if (tmp)
        create_child(tmp->content, io, envs, cmds); // Pass io with fds
    close_fds(io->fds, io->pipes);
    free_fds(io->fds, io->pipes);
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

void	close_child(int **fds, int pipes, int i)
{
	int j;
	
	j = 0;
	while(j < pipes)
	{
		if (j != i - 1)
        	close(fds[j][0]);
        if (j != i)
            close(fds[j][1]);
		j++;
	}
}
void create_child(t_cmd *cmd, t_io_fd *io, t_envs *envs, t_list *cmds)
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
        if (set_fds(cmd, io, io->fds, i) == -1)
        {
            perror("Failed to set file descriptors");
            exit(EXIT_FAILURE);
        }
		if (!cmd->prevpipe && cmd->nextpipe)
            close(io->fds[0][0]);
      	else if (cmd->prevpipe && cmd->nextpipe)
            close_child(io->fds, io->pipes, cmd->i);
		else if (cmd->prevpipe && cmd->nextpipe==0 && cmd->i != 0)
		{	
			close(io->fds[cmd->i][0]);
			close(io->fds[cmd->i][1]);
		}
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
