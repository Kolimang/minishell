// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   execute.c                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/10/10 18:59:16 by lboumahd          #+#    #+#             */
// /*   Updated: 2024/10/17 17:38:55 by lboumahd         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include <minishell.h>

// are we gonna loop here or in the main for the cmds? 

void	pre_exec(t_list *cmds, t_env *local_env, char **global_env)
{
	t_command	*cmd;

	//a gerer le ctrl+D pour auitter que le heredoc
	(void)global_env; // temp, to allow project compilation
	while (cmds)
	{
		cmd = cmds->content;
		init_io_fd(cmd->io);
		get_hrdoc(cmd, local_env, cmd->io);
		cmds = cmds->next;
	}
	//restore files if heredoc isnt working !!!
}

void	exec(t_list *cmds, t_env *local_env, char **global_env)
{
	t_command	*cmd;

	(void)local_env; // Temp, only there to allow compilation
	(void)global_env; // Temp, only there to allow compilation
	while (cmds)
	{
		cmd = cmds->content;
		if (cmds->next == NULL && !(cmd->args[0]))
			if (execute_redir(cmd, cmd->io)== -1)
				return ; //?????
			//check ret value if -1 donc problem
		if (is_builtin(cmd->args[0]))	
		{
			if (cmds->next)
				;//execute_fork(cmd, local_env, global_env);
			else
				;//execute_nofork(cmd, local_env, global_env);
		}
		else
			execute_fork(cmd, local_env, global_env);
		reset_io(cmd);
		cmds = cmds->next;
	}
}

// Created to allow compilation
int	is_builtin(char *cmdname)
{
	(void)cmdname; // Temp, only there to allow compilation
	return (1);
}

//check if the cmd is built in and not alone
//check if the cmd is non built in  
// For each command in a pipeline to set up the appropriate input/out

// We keep both env so that we dont turn the linked list to a char, if the path 
// exists in the local env, then we execute with the real env.
void	get_hrdoc(t_command *cmd, t_env *local_env, t_io_fd *io)
{
	int		pipe_fd[2];
	pid_t	pid;
	t_redir	*redir;

	//a gerer le ctrl+D pour quitter que le heredoc
	(void)io; // Temp, only there to allow compilation
	if (!cmd->is_hrdoc)
		return ;
	while (cmd->ls_redirs)
	{
		redir = cmd->ls_redirs->content;
		if (redir->type == HERE_DOC)
		{
			if (pipe(pipe_fd) == -1)
				return (perror("pipe creation failed"));
			pid = fork();
			if (pid == -1)
				return (perror("fork failed"));
			if (pid == 0)
				child_heredoc_process(cmd, local_env, pipe_fd);
			else
				parent_heredoc_process(cmd, pid, pipe_fd);
		}
		cmd->ls_redirs = cmd->ls_redirs->next;
		reset_io(cmd);
	}
}

void	child_heredoc_process(t_command *cmd, t_env *local_env, int fd[2])
{
	// how to handle signals?
	// Setup signal handling
	//a gerer le ctrl+D pour auitter que le heredoc
	char	*line;
	t_redir	*redir;

	close(fd[0]);
	redir = cmd->ls_redirs->content;
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, redir->value, ft_strlen(line)) == 0)
		{
			free(line);
			break ;
		}
		process_hrdoc(line, local_env);// to check
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	exit(0);
}

int	parent_heredoc_process(t_command *cmd, pid_t pid, int pipe_fd[2])
{
	int	status;

	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
	{
		cmd->io->fd_hrdoc = pipe_fd[0];
		return (0);
	}
	else
	{
		close(pipe_fd[0]);
		return (-1);
	}
}

void	init_io_fd(t_io_fd *files)
{
	files->fd_pipe[0] = -1;
	files->fd_pipe[1] = -2;
	files->fd_in = 0;
	files->fd_out = -1;
	files->fd_hrdoc = -1;
	files->std_in = dup(STDIN_FILENO);
	files->std_out = dup(STDOUT_FILENO);
	if (files->std_in == -1 || files->std_out == -1)
	{
		perror("Failed to duplicate");
		exit(1);// Exit with error code 1
	}
}

void	reset_io(t_command *cmd)
{
	t_io_fd *io;

	io = cmd->io;
	if (dup2(io->std_in, STDIN_FILENO) == -1)
	{
		perror("Failed to reset stdin");
		exit(1);
	}
	if (dup2(io->std_out, STDOUT_FILENO) == -1)
	{
		perror("Failed to reset stdout");
		exit(1);
	}
	close(io->std_in);
	close(io->std_out);
}
