/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:59:16 by lboumahd          #+#    #+#             */
/*   Updated: 2024/10/15 18:42:51 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// are we gonna loop here or in the mian for the cmds? 

void	exec(t_command *cmds, t_env *local_env, char **global_env)
{
	t_command *tmp;

	tmp = cmds;
	while(tmp)
		{	
			init_io_fd(tmp->io);
			get_hrdoc(tmp, local_env, tmp->io);
			tmp = tmp->next;
		}
	while(cmds)
	{
		if(cmds->next == NULL && !(cmds->args[0]))
			execute_redir(cmds, cmds->io);
		if(is_builtin(cmds->args[0]))	
		{
			if(cmds->next)
				execute_fork(cmds, local_env, global_env);
			else
				execute_nofork(cmds, local_env, global_env);
		}
		else
			execute_fork(cmds, local_env, global_env);
		cmds= cmds->next;
	}
	}

//check if the cmd is built in and not alone
//check iddf the cmd is non built in  
// For each command in a pipeline to set up the appropriate input/out

// we keep both env so that we dont turn the linked list to a char, if the path exists in the local env, then we executewith the real env 
void	get_hrdoc(t_command *cmd, t_env *local_env, t_io_fd *io)
{
    int pipe_fd[2];
    pid_t pid;

	if(!cmd->is_hrdoc)
		return;
    while (cmd->redir)
    {
        if (cmd->redir->type == HERE_DOC)
        {
            if (pipe(pipe_fd) == -1)
                return (error("pipe creation failed"));

            pid = fork();
            if (pid == -1)
                return (error("fork failed"));

            if (pid == 0)
                child_heredoc_process(cmd, local_env, pipe_fd);
            else
				parent_heredoc_process(cmd, pid, pipe_fd);
		}
		cmd->redir = cmd->redir->next;
	}
}

void	child_heredoc_process(t_command *cmd, t_env *local_env, int fd[2])
{
	//how to handle signals?? 
	// Setup signal handling
	char *line;

    close(fd[0]);
    while (1) 
	{
        line = readline("> ");
        if (!line || ft_strcmp(line, cmd->redir->hr_delimiter) == 0)
		{
            free(line);
            break;
        }
        process_hrdoc(line, local_env); // to check
        write(fd[1], line, ft_strlen(line));
        write(fd[1], "\n", 1);
        free(line);
    }
    close(fd[1]);
    exit(0); 
}

int parent_heredoc_process(t_command *cmd, pid_t pid, int pipe_fd[2]) {
    int status;

    close(pipe_fd[1]);
    waitpid(pid, &status, 0);
    if (WIFEXITED(status) && WEXITSTATUS(status) == 0) 
	{
        cmd->io->fd_hrdoc = pipe_fd[0];
        return 0;
    }
	else 
	{
        close(pipe_fd[0]);
        return (-1);
    }
}
	// checks all the heredocs 
	//run readline prompt heredoc + expander  
	//recup tmp
	//
void	init_io_fd(t_io_fd *files)
{
	files->fd_pipe[0] = -1;
	files->fd_pipe[1] = -2;
	files->fd_in = 0;
	files->fd_out = -1;
	files->fd_hrdoc = -1;
	files->std_in = dup(STDIN_FILENO);
	files->std_out = dup(STDOUT_FILENO);
	if(files->std_in == -1 || files->std_out == -1)
	{
		perror("Failed to duplicate");
		//exit and ret val ???????
	}
} 