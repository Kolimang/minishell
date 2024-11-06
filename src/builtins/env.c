/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:08:58 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/06 11:06:24 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_env(char **args, t_env *env)
{
	if (!env)
		return (merror(args[0], NULL, "no environment set", 1));
	if (args && args[1])
		return (merror(args[0], NULL, "too many arguments", 1));
	if (args && !args[1])
		print_env(env, 2);
	return (set_exit_status(0));
}
