/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:15:22 by lboumahd          #+#    #+#             */
/*   Updated: 2024/10/28 17:12:24 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	swap_nodes(t_env *node1, t_env *node2)
{
	t_env	*swap;

	swap = node1->next;
	node1->next = node2;
	node2->next = swap;
}

static int	replace_head(t_env **env, t_env *new)
{
	t_env	*temp;

	temp = *env;
	new->next = temp;
	*env = new;
	return (0);
}

static int	insert_inside(t_env **env, t_env *new)
{
	t_env *curr;

	curr = *env;
	while (curr)
	{
		if (ft_strncmp(new->var_name, curr->var_name,
				ft_strlen(new->var_name)) > 0)
		{
			if (!curr->next || ft_strncmp(new->var_name,
					curr->next->var_name, ft_strlen(new->var_name)) < 0)
			{
				swap_nodes(curr, new);
				return (0);
			}
		}
		curr = curr->next;
	}
	return (0);
}

static void	insert_in_env(t_env **env, const char *var_name,
		const char *var_val, int index)
{
	t_env	*new;
	t_env	*curr;

	new = create_env_node(var_name, var_val, index);
	if (!new)
		return ;
	if (!(*env))
		*env = new;
	else
	{
		if (ft_strncmp(new->var_name, (*env)->var_name,
				ft_strlen(new->var_name)) < 0)
			replace_head(env, new);
		else
			insert_inside(env, new);
	}
}

int	update_env(char *name, char *value, t_env **env)
{
	t_env	*head;

	if (!*env)
		return (1);
	head = *env;
	while (head)
	{
		if (value && !ft_strncmp(head->var_name, name, ft_strlen(name) + 1))
		{
			if (head->var_val)
				free(head->var_val);
			head->var_val = ft_strdup(value);
			return (0);
		}
		head = head->next;
	}
	insert_in_env(env, name, value, 1);
	return (0);
}
