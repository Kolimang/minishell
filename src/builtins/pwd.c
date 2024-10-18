/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:08:58 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/18 13:12:18 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// pwd does not accept arguments
int	ft_pwd(char **args, t_env *env)
{
	if (args && args[1])
		ft_putstr_fd("pwd: too many arguments", 2);
	if (!env)
		return (-1);
	while (env)
	{
		if (ft_strncmp(env->var_name, "PWD", 3) == 0)
		{
			ft_printf("%s\n", env->var_val);
			return (0);
		}
		env = env->next;
	}
	return (-1);
}
