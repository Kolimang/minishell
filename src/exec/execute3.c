/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 11:17:47 by lboumahd          #+#    #+#             */
/*   Updated: 2024/10/25 22:31:08 by lboumahd         ###   ########.fr       */
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
	if (set_fds(cmd, io)== -1)
	{	
		reset_io(cmd);
		return(-1);
	}
	//execute cmd 
	ret_value= exec_builtin(cmd, l_env, g_env);
	return(ret_value);
}
int exec_builtin(t_command *cmd, t_env *l_env, char **g_env)
{
	int res;
	//revoir les inputs pour chaque function
	//revoir si les builtin renvoie une valeur d erreur 
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
		if(!tmp->next)
			break;
		tmp = tmp->next;
	}
	if(tmp) // creating last child
		io->fd_in = create_child(cmd, io, l_env, g_env);
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
		if(set_fds(cmd, io) == -1)
		if(cmd->args)//in case we only have redirections
			execute_cmd(cmd, l_env, g_env);
		//exit_child a coder 
	}
	//parent process : 
		handle_closing(cmd, io);
		return(io->pipe[0]); //return the readend tha has the same content as stdout after execution, fd_in = read_end now ouf
	}
void	handle_closing(t_command *cmd, t_io_fd *io)
{
	if(cmd->fd_hrdoc != -3)
		close(cmd->fd_hrdoc);
	if(cmd->prevpipe > 0)//free for next fd_in assignement
		close(io->fd_in);
	close (io->pipe[1]);

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
