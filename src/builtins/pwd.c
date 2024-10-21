/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:08:58 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/21 13:29:30 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_pwd(char **args, t_env *env)
{
	char	*path;

	if (args && args[1])
		return (ft_putstr_fd("pwd: too many arguments\n", 2), 1);
	if (env)
	{
		while (env)
		{
			if (ft_strncmp(env->var_name, "PWD", 3) == 0)
			{
				ft_printf("%s\n", env->var_val);
				return (0);
			}
			env = env->next;
		}
	}
	path = getcwd(NULL, 0);
	if (path)
	{
		ft_printf("%s\n", path);
		free(path);
	}
	else
		return (perror(path), 1);
	return (0);
}
