/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_hrdoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:46:42 by lboumahd          #+#    #+#             */
/*   Updated: 2024/10/27 20:24:44 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pre_exec(t_list *cmds, t_env *local_env, char **global_env)
{
	t_command	*cmd;
	t_list		*tmp_cmds;

	(void)global_env; 
	tmp_cmds = cmds;  
	while (tmp_cmds)
	{
		cmd = tmp_cmds->content;
		cmd->fd_hrdoc = -3;
		if (get_hrdoc(cmd, local_env) == -1)
			return ;//return or exit??? 
		tmp_cmds = tmp_cmds->next; 
	}
	//restore files if heredoc isnt working ??
}

void	init_hrdoc (t_command *cmd)
{
	if (cmd->fd_hrdoc != -3)
		{
			close(cmd->fd_hrdoc);
			cmd->fd_hrdoc = -3;
		}
}

int	get_hrdoc(t_command *cmd, t_env *local_env)
{
	int		pipe_fd[2];
	pid_t	pid;
	t_redir	*redir;

	//set_signals??
	while (cmd->ls_redirs)
	{
		init_hrdoc(cmd);
		redir = cmd->ls_redirs->content;
		if (redir->type == HERE_DOC)
		{
			if (pipe(pipe_fd) == -1)
				return (handle_error("pipe creation failed"));
			pid = fork();
			if (pid == -1)
				return (handle_error("fork failed"));
			if (pid == 0)
				child_heredoc_process(cmd, local_env, pipe_fd);
			else
				if (parent_heredoc_process(cmd, pid, pipe_fd) == -1)
					return (-1);
		}
		cmd->ls_redirs = cmd->ls_redirs->next;
	}
	return (0);
}

void	child_heredoc_process(t_command *cmd, t_env *local_env, int	pipe_fd[2])
{
	
	char	*line;
	t_redir	*redir;

	//set_signals_hrdoc
	close(pipe_fd[0]);
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
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	close(pipe_fd[1]);
	exit(0);
}

int	parent_heredoc_process(t_command *cmd, pid_t pid, int pipe_fd[2])
{
	int	status;

	//handle signals + g_ret_value 
	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
	{
		cmd->fd_hrdoc = pipe_fd[0];
		return (0);
	}
	else
	{
		close(pipe_fd[0]);
		return (-1);
	}
}
