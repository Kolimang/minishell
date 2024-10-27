/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 18:12:18 by lboumahd          #+#    #+#             */
/*   Updated: 2024/10/27 19:37:39 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	check_pid(int pid)
{
	if (pid == -1)
	return_error("Fork Error");
	else
		return ;
}

char **get_paths(char **env)
{
	char **new_path;
	int i;

	i = 0;
	while (ft_strnstr(env[i], "PATH=", 5) == 0)
		i++;
	if (!env[i])
		return_error("$PATH not found");
	new_path = ft_split(env[i] + 5, ':');
	return (new_path);
}
char *get_full_path(char **full_cmd, char **env)
{
    char *full_path;
    char **paths;
    int i;

    i = 0;
    paths = get_paths(env);
    while (paths[i++])
    {
		full_cmd[0] = ft_strjoin("/", full_cmd[0]); 
        full_path = ft_strjoin(paths[i], full_cmd[0]);
		
        if (access(full_path, F_OK | X_OK) == 0)
        {
            free_tab(paths);
			return (full_path);
        }
        free(full_path);
    }
    free_tab(paths);
    free_tab(full_cmd);
    return_error("Path not found");
    return NULL;
}

void	free_tab(char **paths)
{
	int	i;
	
	i = 0;
	while(paths[i])
	{
		free(paths[i]);
		i++;	
	}
	free(paths);
}