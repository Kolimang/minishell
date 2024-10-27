/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:15:22 by lboumahd          #+#    #+#             */
/*   Updated: 2024/10/27 16:39:33 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// mode 1 --> export() without arg 
//      \__ includes empty-string variables AND NULL-valued variables
// mode 2 --> env() without arg
//      \__ includes empty-string variables but not NULL-valued variables
int	print_env(t_env *env, int mode)
{
	if (!env)
		return (1);
	while (env)
	{
		if (mode == 1 && env->var_name)
		{
			ft_printf("declare -x %s", env->var_name);
			if (env->var_val)
				ft_printf("=\"%s\"\n", env->var_val);
			else
				ft_printf("\n");
		}
		else if (mode == 2 && env->var_name)
		{
			if (env->var_val)
				ft_printf("%s=%s\n", env->var_name, env->var_val);
		}
		env = env->next;
	}
	return (0);
}
