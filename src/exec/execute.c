/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 11:17:47 by lboumahd          #+#    #+#             */
/*   Updated: 2024/10/27 19:37:39 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//check EXIIIIIIT attention 

void	exec(t_list *cmds, t_env *local_env, char **global_env)
{
	t_command	*cmd;
	t_io_fd		*io;

	if (cmds)
	{
		init_io_fd(io);
		cmd = cmds->content;
		if (cmds->next == NULL && !(cmd->args[0]))
		{
			if (set_fds(cmd, io)== -1)
			{
				reset_io(io, cmd);
				return ;
			}
		}
		else
		{
			cmd->builtin = is_builtin(cmd->args[0]);
			if (cmd->builtin && !(cmds->next))
				execute_nofork(cmd, io, local_env, global_env);
			else
				execute_fork(cmds, io, local_env, global_env);
		}
		reset_io(io, cmd);//not sure if fdhroc to close
	}
	return ;
}

int	execute_fork(t_list *cmds, t_io_fd *io, t_env *l_env, char **g_env)
{
	t_command *cmd;
	t_list *tmp;

	tmp = cmds;

	while(tmp)
	{
		cmd = tmp->content;
		if (pipe(io->pipe) == -1)
			return (-1);
		//save the fd[0]
		io->fd_in = create_child(cmd, io, l_env, g_env); // return smh fd_in updated with read end of pipe
		//gets the fd[0]
			//check redirections
		//if (cmd->builtin = EXIT)
			//mini_exxit : dont exit lol ;
		if (!tmp->next)
			break;
		tmp = tmp->next;
	}
	if (tmp) // creating last child
		io->fd_in = create_child(cmd, io, l_env, g_env);
	wait_children(tmp->content); 	//recupere le code d'erreur final
	return (0);
}

int	create_child(t_command *cmd, t_io_fd *io, t_env *l_env, char **g_env)
{
	t_redir	*redir;
	int	ret;

	redir = cmd->ls_redirs->content;
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (handle_error("fork"));
	if (cmd->pid == 0) //in child
	{
		if (set_fds(cmd, io) == -1)
		if (cmd->args)//in case we only have redirections
			exec_cmd(cmd, l_env, g_env);
		//exit_child a coder 
	}
	//parent process : 
		handle_closing(cmd, io);
		return (io->pipe[0]); //return the readend tha has the same content as stdout after execution, fd_in = read_end now ouf
	}

void	wait_children(t_list *cmds)
{
    t_command *cmd;
	t_list *tmp;	
	int status;

    while (tmp)
    {
        cmd = tmp->content;
		waitpid(cmd->pid, &status, 0);
        
        if (WIFEXITED(status))
            // Normal termination
            ret_value = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            // Terminated by signal
            ret_value = 128 + WTERMSIG(status);
        tmp = tmp->next;
    }
}
