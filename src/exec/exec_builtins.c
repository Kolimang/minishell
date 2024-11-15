/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:51:12 by lboumahd          #+#    #+#             */
/*   Updated: 2024/11/15 11:24:35 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	execute_nofork(t_command *cmd, t_io_fd *io, t_envs *envs, t_list *cmds)
{
	int	ret_value;

	if (set_fds(cmd, io) == -1)
		return (-1);
	ret_value = exec_builtin(cmd, io, envs, cmds);
	if (cmd->fd_hrdoc != -3)
		close(cmd->fd_hrdoc);
	return (ret_value);
}

int	exec_builtin(t_command *cmd, t_io_fd *io, t_envs *envs, t_list *cmds)
{
	int	res;

	if (cmd->builtin == 1)
		res = ft_echo(cmd->args);
	else if (cmd->builtin == 2)
		res = ft_cd(cmd->args, *envs->l_env);
	else if (cmd->builtin == 3)
		res = ft_pwd(cmd->args, *envs->l_env);
	else if (cmd->builtin == 4)
		res = ft_export(cmd->args, envs->l_env);
	else if (cmd->builtin == 5)
		res = ft_unset(cmd->args, envs->l_env);
	else if (cmd->builtin == 6)
		res = ft_env(cmd->args, *envs->l_env);
	else if (cmd->builtin == 7)
		res = ft_exit(cmds, envs, 0, io);
	else
		res = -1;
	return (res);
}

int	is_builtin(char *cmd)
{
	if (cmd == NULL)
		return (0);
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

int	pre_exec_builtin(t_command *cmd, t_io_fd *io, t_envs *envs, t_list *cmds)
{
	g_ret_value = exec_builtin(cmd, io, envs, cmds);
	return (0);
}
