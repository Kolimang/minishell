/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:08:58 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/11 13:35:24 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_env(char **args, t_env *env)
{
	t_env	*temp;
	int		print;

	if (!env)
		return (merror(args[0], NULL, NULL, 12));
	if (args && args[1])
		return (merror(args[0], NULL, NULL, 13));
	print = 0;
	temp = env;
	while (temp)
	{
		if (!ft_strncmp(temp->var_name, "PATH", 5) && temp->var_val)
			print = 1;
		temp = temp->next;
	}
	if (print == 0)
		return (merror(args[0], NULL, NULL, 381));
	if (args && !args[1])
		print_env(env, 2);
	return (set_exit_status(0));
}
