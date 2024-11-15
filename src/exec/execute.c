/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 11:17:47 by lboumahd          #+#    #+#             */
/*   Updated: 2024/11/15 11:19:40 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	handle_single_command(t_command *cmd, t_io_fd *io)
{
	if (set_fds(cmd, io) == -1)
	{
		reset_io(io, cmd);
		// free io ?
		return (-1);
	}
	return (0);
}

void	exec(t_list *cmds, t_envs *envs)
{
	t_command	*cmd;
	t_io_fd		*io;

	if (!cmds)
		return ;
	io = initialize_io_fd();
	if (!io)
		return_error("Failed to allocate memory for io_fd");
	cmd = cmds->content;
	if (cmds->next == NULL && !(cmd->args[0]))
	{
		if (handle_single_command(cmd, io) == -1)
			return ;
	}
	else
	{
		cmd->builtin = is_builtin(cmd->args[0]);
		if (cmd->builtin && !(cmds->next))
			execute_nofork(cmd, io, envs, cmds);
		else
			execute_fork(cmds, io, envs);
	}
	reset_io(io, cmd);
	free(io);
}

int	execute_command(char *pathname, char **full, char **g_env)
{
	if (execve(pathname, full, g_env) == -1)
	{
		perror("Execution failure");
		free_tab(full);
		free(pathname);
		exit(127);
	}
	return (0);
}

int	exec_cmd(t_command *cmd, t_io_fd *io, t_envs *envs, t_list *cmds)
{
	char	*pathname;
	char	**full_cmd;
	char	*real_full;
	char	**full;

	cmd->builtin = is_builtin(cmd->args[0]);
	if (cmd->builtin)
		pre_exec_builtin(cmd, io, envs, cmds);	
	else
	{
		full_cmd = ft_split(cmd->args[0], ' ');
		if (cmd->args[0][0] == '.' || cmd->args[0][0] == '/')
			pathname = find_path(full_cmd, cmd->args[0]);
		else
			pathname = get_full_path(full_cmd, *(envs->l_env));
		if (!pathname)
			exit(merror(cmd->args[0], NULL, NULL, 127));
		real_full = build_full_cmd(pathname, cmd);
		full = ft_split(real_full, ' ');
		free(real_full);
		execute_command(pathname, full,envs->g_env);
		free_tab(full);
		free_tab(full_cmd);
	}
	return (0);
}
