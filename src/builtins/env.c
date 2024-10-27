/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:08:58 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/27 16:10:25 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_env(char **args, t_env *env)
{
	if (!env)
		return (ft_putstr_fd("env: no environment set\n", 2), 1);
	if (args && args[1])
		return (ft_putstr_fd("env: too many arguments\n", 2), 1);
	if (args && !args[1])
		print_env(env, 2);
	return (0);
}
