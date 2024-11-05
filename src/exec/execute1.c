/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:51:12 by lboumahd          #+#    #+#             */
/*   Updated: 2024/11/05 12:44:04 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	execute_nofork(t_command *cmd, t_io_fd *io, t_env **l_env, char **g_env)
{
	int	ret_value;

	if (set_fds(cmd, io) == -1)
		return (-1);
	ret_value = exec_builtin(cmd, l_env, g_env);
	if (cmd->fd_hrdoc != -3)
		close(cmd->fd_hrdoc);
	return (ret_value);
}

// res = -1; --> Error: unknown built-in command
int	exec_builtin(t_command *cmd, t_env **l_env, char **g_env)
{
	int	res;

	if (cmd->builtin == 1)
		res = ft_echo(cmd->args);
	else if (cmd->builtin == 2)
		res = ft_cd(cmd->args, *l_env);
	else if (cmd->builtin == 3)
		res = ft_pwd(cmd->args, *l_env);
	else if (cmd->builtin == 4)
		res = ft_export(cmd->args, l_env);
	else if (cmd->builtin == 5)
		res = ft_unset(cmd->args, l_env);
	else if (cmd->builtin == 6)
		res = ft_env(cmd->args, *l_env);
	else if (cmd->builtin == 7)
	   res = ft_exit(cmd->args, *l_env, 0);
	else
		res = -1;
	return (res);
}

int	is_builtin(char *cmd)
{
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

char	**get_paths(t_env *tmp)
{
	char	**new_path;
	t_env	*l_env;

	l_env = tmp;
	new_path = NULL;
	while (l_env)
	{
		if (ft_strnstr(l_env->var_name, "PATH", 4))
		{
			new_path = ft_split(l_env->var_val, ':');
			break ;
		}
		l_env = l_env->next;
	}
	if (!new_path)
		handle_error("$PATH not found");
	return (new_path);
}

char	*get_full_path(char **full_cmd, t_env *l_env)
{
	char	*full_path;
	char	**paths;
	int		i;

	i = 0;
	paths = get_paths(l_env);
	if (!paths)
		return (NULL);
	full_cmd[0] = ft_strjoin("/", full_cmd[0]);
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], full_cmd[0]);
		if (access(full_path, F_OK | X_OK) == 0)
		{
			free_tab(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_tab(paths);
	free(full_cmd[0]);
	return (NULL);
}

void	free_tab(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

char	*find_path(char **full_cmd, char *cmd)
{
	if (access(full_cmd[0], F_OK | X_OK) == 0)
		return (full_cmd[0]);
	else
	{
		perror(cmd);
		exit(EXIT_FAILURE);
	}
	return (NULL);
}

char	*build_full_cmd(char *pathname, t_command *cmd)
{
	char	*real_full;
	char	*temp;
	int		i;

	real_full = strdup(pathname);
	i = 1;
	while (i < cmd->argc)
	{
		temp = ft_strjoin(real_full, " ");
		free(real_full);
		real_full = ft_strjoin(temp, cmd->args[i]);
		free(temp);
		i++;
	}
	return (real_full);
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

int	exec_cmd(t_command *cmd, t_env *l_env, char **g_env)
{
	char	*pathname;
	char	**full_cmd;
	char	*real_full;
	char	**full;

	full_cmd = ft_split(cmd->args[0], ' ');
	if (cmd->args[0][0] == '.' || cmd->args[0][0] == '/')
		pathname = find_path(full_cmd, cmd->args[0]);
	else
		pathname = get_full_path(full_cmd, l_env);
	if (!pathname)
	{
		ft_putstr_fd("command not found\n", 2);
		exit(127);
	}
	real_full = build_full_cmd(pathname, cmd);
	full = ft_split(real_full, ' ');
	free(real_full);
	execute_command(pathname, full, g_env);
	free_tab(full);
	free_tab(full_cmd);
	return (0);
}
