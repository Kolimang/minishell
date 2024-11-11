/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:15:22 by lboumahd          #+#    #+#             */
/*   Updated: 2024/10/28 17:27:34 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// static int	print_value(t_env *node)
// {
// 	char	*val;
// 	int		last;

// 	val = node->var_val;
// 	if (val)
// 	{
// 		last = (int)(ft_strlen(val) - 1);
// 		ft_printf("=");
// 		if (val[0] != '\"')
// 			ft_printf("\"");
// 		ft_printf("%s", val);
// 		if (val[last] != '\"')
// 			ft_printf("\"");
// 		ft_printf("\n");
// 	}
// }

int	print_env_sorted(t_env *env)
{
	t_env	*clone;
	t_env	*sorted;

	clone  = clone_env(env);
	sort_env(&clone);
	while (clone && clone->var_name)
	{
		ft_printf("declare -x %s", clone->var_name);
		if (clone->var_val)
			ft_printf("=\"%s\"\n", clone->var_val);
		else
			ft_printf("\n");
		clone = clone->next;
	}
	free_env(&clone);
	return (0);
}

int	print_env_unsorted(t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (temp->var_name && temp->var_val)
			ft_printf("%s=%s\n", temp->var_name, temp->var_val);
		temp = temp->next;
	}
	return (0);
}

// mode 1 --> export() without arg 
//      \__ includes empty-string variables AND NULL-valued variables
// mode 2 --> env() without arg
//      \__ includes empty-string variables but not NULL-valued variables
int	print_env(t_env *env, int mode)
{
	if (!env)
		return (1);
	if (mode == 1)
	{
		print_env_sorted(env);
	}
	else if (mode == 2)
	{
		print_env_unsorted(env);
	}
	return (0);
}
