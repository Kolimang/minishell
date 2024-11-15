/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:10:13 by lboumahd          #+#    #+#             */
/*   Updated: 2024/11/15 11:52:08 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	find_minimum(t_env *current, t_env **minimum, t_env **prev_min)
{
	t_env	*compare;
	t_env	*prev_compare;

	*minimum = current;
	*prev_min = current;
	compare = current->next;
	prev_compare = current;
	while (compare)
	{
		if (ft_strncmp((*minimum)->var_name, compare->var_name,
				ft_strlen((*minimum)->var_name) + 1) > 0)
		{
			*minimum = compare;
			*prev_min = prev_compare;
		}
		prev_compare = compare;
		compare = compare->next;
	}
}

// static void	swap_nodes(t_env *minimum, t_env *current, t_env *prev_curr,
// 						t_env *prev_min)
static void	swap_nodes(t_env *minimum, t_env *current, t_env *prev_min)
{
	t_env	*temp;

	temp = minimum->next;
	if (prev_min == current)
	{
		minimum->next = current;
	}
	else
	{
		prev_min->next = current;
		minimum->next = current->next;
	}
	current->next = temp;
}

// Update the head if `current` was the head
static void	updt_head(t_env **env, t_env *prev_curr, t_env *minimum)
{
	if (prev_curr)
	{
		prev_curr->next = minimum;
	}
	else
	{
		*env = minimum;
	}
}

t_env	*clone_env(t_env *env)
{
	t_env	*clone;
	char	**env_as_array;

	env_as_array = env_to_array(env);
	clone = init_env(env_as_array);
	free_arr(env_as_array, array_len(env_as_array));
	return (clone);
}

void	sort_env(t_env **env)
{
	t_env	*prev_curr;
	t_env	*current;
	t_env	*minimum;
	t_env	*prev_min;

	prev_curr = NULL;
	current = *env;
	while (current)
	{
		find_minimum(current, &minimum, &prev_min);
		if (minimum != current)
		{
			updt_head(env, prev_curr, minimum);
			swap_nodes(minimum, current, prev_min);
		}
		prev_curr = minimum;
		current = minimum->next;
	}
}
