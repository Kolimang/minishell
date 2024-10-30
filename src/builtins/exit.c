/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:08:58 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/30 11:04:44 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	arg_is_number(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **args, t_env *env, int eof)
{
	int	argc;

	if (eof)
		ft_printf("\033[A\033[11C");
	ft_printf("exit\n");
	argc = ft_arraylen(args);
	if (args && args[1] && !arg_is_number(args[1]))
	{
		g_ret_value = 255;
		merror(args[0], args[1], "numeric argument required", 1);
	}
	else if (argc > 2)
	{
		g_ret_value = 1;
		merror(args[0], NULL, "too many arguments", 1);
	}
	array_str_free(args, ft_arraylen(args));
	free_env(env);
	// free command(s) ?
	exit(g_ret_value);
}
