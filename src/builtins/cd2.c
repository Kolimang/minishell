/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:08:58 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/20 16:32:25 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	go_home(char *curr_path, t_env *env)
{
	char	*home_path;
	char	*new_path;

	home_path = get_env_val(env, "HOME");
	if (!home_path || home_path[0] == '\0')
		return (merror("cd", NULL, NULL, 14));
	if (access(home_path, R_OK) != 0)
		return (merror("cd", NULL, NULL, 15));
	curr_path = getcwd(NULL, 0);
	if (chdir(home_path) != 0)
	{
		free(curr_path);
		return (merror("cd", NULL, NULL, 17));
	}
	new_path = getcwd(NULL, 0);
	if (!new_path)
	{
		free(curr_path);
		return (merror("cd", NULL, NULL, 16));
	}
	return (update_pwd(new_path, curr_path, env), 0);
}
