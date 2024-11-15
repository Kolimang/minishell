/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:15:22 by lboumahd          #+#    #+#             */
/*   Updated: 2024/11/15 12:31:13 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	print_env_sorted(t_env *env)
{
	t_env	*clone;
	t_env	*sorted;

	clone = clone_env(env);
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

// mode 1 --> export() without arg : includes null-valued variables
// mode 2 --> env() without arg : does NOT include null-valued variables
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
