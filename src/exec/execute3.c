/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 11:17:47 by lboumahd          #+#    #+#             */
/*   Updated: 2024/10/24 12:37:40 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//check EXIIIIIIT attention 
	int	is_builtin(char *cmd)
{
	//check EXIIIIIIT attention 
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		return (2);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (3);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return (4);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return (5);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		return (6);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		return (7);
	return (0);
}

int	execute_nofork(t_command *cmd, t_io_fd *io, t_env *l_env, char **g_env)
{
	//void or int ?? what about g_ret_val??
	int ret_value;
	//check redirection
	if (execute_redir(cmd, io)== -1)
	{	
		reset_io(cmd);
		return(-1);
	}
	//execute cmd 
	ret_value = exec_builtin(cmd, l_env, g_env);
	return(ret_value);
}
int exec_builtin(t_command *cmd, t_env *l_env, char **g_env)
{
	int res;
	//revoir les inputs pour chaque function
    if (cmd->builtin == 1)
        res = ft_echo(cmd->args);
    else if (cmd->builtin == 2)
        res = ft_cd(cmd->args, l_env, g_env);
    else if (cmd->builtin == 3)
        res = ft_pwd(cmd->args, l_env, g_env);
    else if (cmd->builtin == 4)
        res = ft_export(cmd->args, l_env, g_env);
    else if (cmd->builtin == 5)
        res = ft_unset(cmd->args, l_env, g_env);
    else if (cmd->builtin == 6)
        res = ft_env(cmd->args, l_env, g_env);
    else if (cmd->builtin == 7)
        res = ft_exit(cmd->args, l_env, g_env);
    else
        res = -1;  // Error: unknown built-in command
    return res;
}

int	execute_fork(t_command *cmd, t_io_fd *io, t_env *l_env, char **g_env)
{
	t_command *cmd;
	t_list *tmp;
	int	fd_pipe[2];

	while(tmp)
	{
		cmd = tmp->content;
		if(pipe(io->pipe) == -1)
			return(-1);
		//save the fd[0]
		io->fd_in = create_child(cmd, io, l_env, g_env); // return smh fd_in updated with read end of pipe
		//gets the fd[0]
			//check redirections
		//if(cmd->builtin = EXIT)
			//mini_exxit : dont exit lol ;
		//if theres redirection put it, otherwhise keep stdin 1st cmd / stdout last cmd
		//make sure that fd_pipe[0]readend of the pipe
		//after executing we close the fd_in of the cmd
		//fd_in become fd_pipe[0] that is the read end of pipe, where the pipe reads
		if(!tmp->next)
			break;
		tmp = tmp->next;
	}
	if(tmp) // creating last child
		io->fd_in = create_child(cmd, l_env, g_env);
		//what to do with fd_in??? c deja gere ici ou gere dans le set fd? 
	wait_children(tmp->content); 	//recupere le code d'erreur final
	return(0);
}

int	create_child(t_command *cmd, t_io_fd *io, t_env *l_env, char **g_env)
{
	t_redir	*redir;
	int	ret;
	redir = cmd->ls_redirs->content;
	cmd->pid = fork();
	if(cmd->pid == -1)
		return(handle_error("fork"));
	if (cmd->pid == 0) //in child
	{
		if (cmd->prevpipe > 0)
		{
			get_infile(cmd, io);
			//close(io->pipe[1]);
		}
		if(cmd->args)
			execute_cmd(cmd, l_env, g_env);
		//exit error val??
		return(io->pipe[0]); //return the readend tha has the same content as stdout after execution, fd_in = read_end now ouf
	}
}

void wait_children(t_list *cmds)
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
            g_ret_value = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            // Terminated by signal
            g_ret_value = 128 + WTERMSIG(status);
        tmp = tmp->next;
    }
}

void	set_fds(t_command *cmd, t_io_fd *io)
{
	/*when you use dup2 to redirect STDOUT_FILENO to pipe_fd[1],
	any output sent to standard output will be directed into 
	the write end of the pipe (pipe_fd[1])
	*/
	//fd_in is already here pipe_fd[0]
	//fd_in first call is STDIN
	if(cmd->prevpipe > 0)
	{
		if(dup2(io->fd_in, STDIN_FILENO) == -1)
				return ???;
		if(close(io->fd_in))
			return ???;//close fd_in
	}
	if(cmd->nextpipe > 0)
	{
		if(dup2(fd_pipe[1], ))//close unused fds ?
		//set fd_pipe[1] as the fd_out
	}
}

void	close_fds(t_command *cmd, t_io_fd *io)
{
	t_command *tmp;
	t_redir	*redir;
	int flag1;
	int flag2;
	
	flag1 = 0;
	flag2 = 0;
	tmp = cmd;
	while (tmp->ls_redirs && io->pipe && !(flag2 == 1 && flag1 == 1))
	{
		redir = tmp->ls_redirs;
		if(flag1 == 0 && (redir->type == INFILE || redir->type == HERE_DOC))
		{
			close(io->pipe[0]);
			flag1 = 1;
		}
		else if (flag2 == 0)
		{	
			close(io->pipe[1]);
			flag2 = 1;
		}
		tmp->ls_redirs = tmp->ls_redirs->next;
	}
}
/*
if(has infile redirection)
	get_infile as stdinfileno
	close read pipe
else
	get fd_in as stdinfileno
if(has outfile redirection)
	get outfile as stdfileout
	close write pipe 
else 
	get fd_pipe[0] as stdfileout
*/
