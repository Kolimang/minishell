/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:10:13 by lboumahd          #+#    #+#             */
/*   Updated: 2024/11/14 16:04:31 by lboumahd         ###   ########.fr       */
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
	if (!new_node->var_name)
		return (NULL);
	if (var_val)
	{
		new_node->var_val = ft_strdup(var_val);
		if (!new_node->var_val)
			return (NULL);
	}
	else
		new_node->var_val = NULL;
	new_node->index = index;
	new_node->next = NULL;
	return (new_node);
}

int	add_env_var(t_env **env, const char *var_name, const char *var_val,
		int index)
{
	t_env	*new_node;
	t_env	*current;

	new_node = create_env_node(var_name, var_val, index);
	if (!new_node)
		return (EXIT_FAILURE);
	if (!(*env))
		*env = new_node;
	else
	{
		current = *env;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
	return (0);
}
t_env *init_env(char **original_env)
{
    t_env *env = NULL;
    t_env *current;
    char *sep;
    int index = 0;
    int i = -1;

    while (original_env[++i])
    {
        // Make a temporary copy of the current environment string
        char *temp = strdup(original_env[i]);
        if (!temp)
            return NULL; // Handle memory allocation failure

        // Find the separator in the copy
        sep = strchr(temp, '=');
        if (sep)
        {
            *sep = '\0'; // Temporarily split key and value
            current = create_env_node(temp, sep + 1, index++);
            if (!current)
            {
                free(temp);  // Free the copy before returning
                return NULL;
            }
            if (add_env_var(&env, current->var_name, current->var_val, current->index) == EXIT_FAILURE)
            {
                free(temp);
                return NULL;
            }
        }
        free(temp); // Free the copy after use
    }
    return env;
}

