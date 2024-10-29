/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:08:58 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/29 12:49:33 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	arg_is_number(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	ft_exit(char **args, t_env *env)
{
	int	argc;

	argc = ft_arraylen(args);
	if (argc > 2)
	{
		g_ret_value = 1;
		merror(args[0], NULL, "too many arguments\n", 1);
	}
	else if (args[1] && !arg_is_number(args[1]))
	{
		g_ret_value = 255;
		merror(args[0], args[1], "numeric argument required\n", 1);
	}
	array_str_free(args, ft_arraylen(args));
	free_env(env);
	ft_printf("exit\n");
	exit(g_ret_value);
}
