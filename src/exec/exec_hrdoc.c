/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_hrdoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:46:42 by lboumahd          #+#    #+#             */
/*   Updated: 2024/10/30 09:45:43 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	pre_exec(t_list *cmds, t_env *local_env, char **global_env)
{
	t_command	*cmd;
	t_list		*tmp_cmds;
	
	(void)global_env;
	tmp_cmds = cmds;
	while (tmp_cmds)
	{
		cmd = init_hrdoc(tmp_cmds);
		if (get_hrdoc(cmd, local_env) == -1)
			return ;
		tmp_cmds = tmp_cmds->next;
	}
}

t_command	*init_hrdoc(t_list *cmds)
{
	t_command	*cmd;
	
	cmd = cmds->content;
	if (cmd->fd_hrdoc != -3)
	{
		close(cmd->fd_hrdoc);
		cmd->fd_hrdoc = -3; 
	}
	return (cmd);
}

int get_hrdoc(t_command *cmd, t_env *local_env)
{
	int		pipe_fd[2];
	pid_t	pid;
	t_redir	*redir;
	t_list	*redir_node;

 	//pour test sans redirection check if cmd->ls_redir exists
	redir_node = cmd->ls_redirs;
	while (redir_node)
	{
		redir = redir_node->content;
		if (redir->type == HERE_DOC)
		{
			if (pipe(pipe_fd) == -1)
				return (handle_error("pipe creation failed"));
			pid = fork();
			if (pid == -1)
				return (handle_error("fork failed"));
			if (pid == 0)
				child_heredoc_process(cmd, local_env, pipe_fd, redir);  // Handle heredoc in child
			else if (parent_heredoc_process(cmd, pid, pipe_fd) == -1)
				return (-1);
		}
		redir_node = redir_node->next;
	}
	return (0);
	}

void	child_heredoc_process(t_command *cmd, t_env *local_env, int pipe_fd[2], t_redir *redir)
{
	char	*line;

	close(pipe_fd[0]);
	while (1)
	{
		line = readline("> ");
		line = process_hrdoc(line, local_env);
		if (!line)
			break ;
		if (ft_strncmp(line, redir->value, ft_strlen(redir->value) + 1) == 0)
		{
			free(line);
			break ;
		}
		if (write(pipe_fd[1], line, ft_strlen(line)) == -1 ||
			write(pipe_fd[1], "\n", 1) == -1)
		{
			perror("write error");
			free(line);
			break ;
		}
		free(line);
	}
	close(pipe_fd[1]);
	exit(EXIT_SUCCESS);
}

int	parent_heredoc_process(t_command *cmd, pid_t pid, int pipe_fd[2])
{
	int	status;

	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
	{
		cmd->fd_hrdoc = pipe_fd[0];
		return (0);
	}
	else if (WIFSIGNALED(status))
	{
		g_ret_value = WTERMSIG(status);
		close(pipe_fd[0]);
		return (-1);
	}
	close(pipe_fd[0]);
	return (-1);
}
