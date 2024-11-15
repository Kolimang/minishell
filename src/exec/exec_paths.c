/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:51:12 by lboumahd          #+#    #+#             */
/*   Updated: 2024/11/15 12:00:40 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
	full_cmd[0] = ft_strjoin_replace("/", full_cmd[0], 's');
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
	else if (access(full_cmd[0], F_OK) != 0)
	{
		perror(cmd);
		exit(127);
	}
	else if (access(full_cmd[0], X_OK) != 0)
	{
		perror(cmd);
		exit(126);
	}
	return (NULL);
}

char	*build_full_cmd(char *pathname, t_cmd *cmd)
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
