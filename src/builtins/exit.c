/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:08:58 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/27 19:06:24 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_exit(char **args, t_env *env)
{
	char	*name;
	char	*value;
	int		i;
	int		res;

	res = 0;
	if (args && !args[1])
		return (print_env(env, 1), 0);
	if (args && args[1])
	{
		i = 1;
		while (args[i])
		{
			res = check_name(args[i]);
			if (res)
				merror(args[0], args[i], "not a valid identifier", 1);
			else
			{
				check_value(args[i], &name, &value);
				update_env(name, value, &env);
			}
			i++;
		}
	}
	return (res);
}
