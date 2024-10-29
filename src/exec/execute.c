/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 11:17:47 by lboumahd          #+#    #+#             */
/*   Updated: 2024/10/29 15:37:07 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//check EXIIIIIIT attention 

void exec(t_list *cmds, t_env *local_env, char **global_env) {
    t_command *cmd;
    t_io_fd *io;

	cmd = cmds->content;
    if (cmds) {
        io = malloc(sizeof(t_io_fd));
        if (!io)
            return_error("Failed to allocate memory for io_fd");
        init_io_fd(io);

        cmd = cmds->content;
        if (cmds->next == NULL && !(cmd->args[0])) {
            if (set_fds(cmd, io) == -1) {
                reset_io(io, cmd);
                return;
            }
        } else {
            cmd->builtin = is_builtin(cmd->args[0]);
            if (cmd->builtin && !(cmds->next))
			    execute_nofork(cmd, io, local_env, global_env);
			else 
                execute_fork(cmds, io, local_env, global_env);
        }
        reset_io(io, cmd);  // Reset std_in and std_out after execution
    }
    return;
}

int	execute_fork(t_list *cmds, t_io_fd *io, t_env *l_env, char **g_env)
{
	t_command *cmd;
	t_list *tmp;

	tmp = cmds;

	while(tmp)
	{
		cmd = tmp->content;
		if (!tmp->next)
			break;	
		if (pipe(io->pipe) == -1)
			return (-1);
		io->fd_in = create_child(cmd, io, l_env, g_env); // return smh fd_in updated with read end of pipe
		tmp = tmp->next;
	}
	if (tmp) // creating last child
		io->fd_in = create_child(cmd, io, l_env, g_env);
		// set_fds(cmd, io);
	wait_children(cmds);
	if(cmd->prevpipe)
		close(io->fd_in);
    if(io->pipe[0] != -1)
		close(io->pipe[1]);
   	if (cmd->fd_hrdoc != -3)
		close(cmd->fd_hrdoc);
	close(io->fd_out); 	//recupere le code d'erreur final
	return (0);
}

int create_child(t_command *cmd, t_io_fd *io, t_env *l_env, char **g_env)
{
	t_redir *redir;
	if(cmd->ls_redirs)
		redir = cmd->ls_redirs->content;
    cmd->pid = fork();
    if (cmd->pid == -1)
        return (handle_error("fork"));
    if (cmd->pid == 0)  // Child process
    {
        if (set_fds(cmd, io) == -1)
			 exit(EXIT_FAILURE);
		if (cmd->args)
            exec_cmd(cmd, l_env, g_env);
        exit(1);
    }
    // Return the read end of the pipe for the next command
    if(cmd->prevpipe)
		return (io->pipe[0]);
	else
		return(-1);
}

void	wait_children(t_list *cmds)
{
    t_command *cmd;
	t_list *tmp;	
	int status;

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



