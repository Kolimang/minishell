/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:10:13 by lboumahd          #+#    #+#             */
/*   Updated: 2024/10/27 16:15:07 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_env	*create_env_node(const char *var_name, const char *var_val, int index)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->var_name = ft_strdup(var_name);
	if (var_val)
		new_node->var_val = ft_strdup(var_val);
	else
		new_node->var_val = NULL;
	new_node->index = index;
	new_node->next = NULL;
	return (new_node);
}

void	add_env_var(t_env **env, const char *var_name, const char *var_val,
		int index)
{
	t_env	*new_node;
	t_env	*current;

	new_node = create_env_node(var_name, var_val, index);
	if (!new_node)
		return ;
	if (!(*env))
		*env = new_node;
	else
	{
		current = *env;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}

t_env	*init_env(char **original_env)
{
	t_env	*env;
	t_env	*current;
	char	*sep;
	int		index;
	int		i;

	env = NULL;
	current = NULL;
	index = 0;
	i = 0;
	while (original_env[i])
	{
		sep = ft_strchr(original_env[i], '=');
		if (sep)
		{
			*sep = '\0';
			current = create_env_node(original_env[i], sep + 1, index++);
			*sep = '=';
			add_env_var(&env, current->var_name, current->var_val,
				current->index);
		}
		i++;
	}
	sort_env(&env);
	return (env);
}