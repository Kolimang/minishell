/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_hrdoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:46:42 by lboumahd          #+#    #+#             */
/*   Updated: 2024/11/15 14:13:44 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <minishell.h>

void	pre_exec(t_list *cmds, t_envs *envs)
{
	t_cmd	*cmd;
	t_list	*tmp_cmds;

	tmp_cmds = cmds;
	while (tmp_cmds)
	{
		cmd = init_hrdoc(tmp_cmds);
		if (get_hrdoc(cmd, *(envs->l_env)) == -1)
			return ;
		tmp_cmds = tmp_cmds->next;
	}
}

t_cmd	*init_hrdoc(t_list *cmds)
{
	t_cmd	*cmd;

	cmd = cmds->content;
	if (cmd->fd_hrdoc != -3)
	{
		close(cmd->fd_hrdoc);
		cmd->fd_hrdoc = -3;
	}
	return (cmd);
}

int	get_hrdoc(t_cmd *cmd, t_env *l_env)
{
	int		pipe_fd[2];
	pid_t	pid;
	t_redir	*redir;
	t_list	*redir_node;

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
				child_hd(l_env, pipe_fd, redir);
			else if (parent_heredoc_process(cmd, pid, pipe_fd) == -1)
				return (-1);
		}
		redir_node = redir_node->next;
	}
	return (0);
}

void	child_hd(t_env *l_env, int pipe_fd[2], t_redir *r)
{
	char	*ln;

	close(pipe_fd[0]);
	signal(SIGINT, sig_handler_hrdoc);
	while (1)
	{
		ln = readline("> ");
		ln = process_hrdoc(ln, l_env);
		if (!ln)
			break ;
		if (!ft_strncmp(ln, r->val, ft_strlen(r->val) + 1) || *(sig_status()))
		{
			free(ln);
			break ;
		}
		if (write(pipe_fd[1], ln, ft_strlen(ln)) == -1
			|| write(pipe_fd[1], "\n", 1) == -1)
		{
			free(ln);
			break ;
		}
		free(ln);
	}
	close(pipe_fd[1]);
	exit(EXIT_SUCCESS);
}

int	parent_heredoc_process(t_cmd *cmd, pid_t pid, int pipe_fd[2])
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
		g_ret_val = WTERMSIG(status);
		close(pipe_fd[0]);
		return (-1);
	}
	close(pipe_fd[0]);
	return (-1);
}
