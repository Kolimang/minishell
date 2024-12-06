/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:10:13 by lboumahd          #+#    #+#             */
/*   Updated: 2024/12/06 23:40:12 by jrichir          ###   ########.fr       */
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

t_env	*init_env(char **original_env)
{
	t_env	*env;
	t_env	*c;
	char	*sep;
	int		index;
	int		i;

	env = NULL;
	index = 0;
	i = -1;
	while (original_env[++i])
	{
		sep = ft_strchr(original_env[i], '=');
		if (sep)
		{
			*sep = '\0';
			c = create_env_node(original_env[i], sep + 1, index++);
			if (!c)
				return (NULL);
			*sep = '=';
			if (add_env_var(&env, c->var_name, c->var_val, c->index) == 1)
				return (NULL);
			free_env(&c);
		}
	}
	return (env);
}

int	set_new_env(char *name, char *value, t_env **env)
{
	t_env	*head;

	head = malloc(sizeof(t_env));
	if (!head)
		return (-1);
	*env = head;
	head->next = NULL;
	head->index = 0;
	head->var_name = ft_strdup(name);
	if (!head->var_name)
		return (-1);
	if (value)
	{
		head->var_val = ft_strdup(value);
		if (!head->var_val)
			return (-1);
	}
	if (add_env_var(env, "PWD", getcwd(NULL, 0), 0) != 0
		|| add_env_var(env, "OLDPWD", "", 0) != 0
		|| add_env_var(env, "PATH", "/bin", 0) != 0)
		return (-1);
	return (0);
}

int	check_env(t_env **env)
{
	set_shlvl(env);
	if (env && !get_env_val((*env), "PWD"))
		if (add_env_var(env, "PWD", getcwd(NULL, 0), 0) != 0)
			return (1);
	if (env && !get_env_val((*env), "OLDPWD"))
		if (add_env_var(env, "OLDPWD", "", 0) != 0)
			return (1);
	if (env && !get_env_val((*env), "PATH"))
		if (add_env_var(env, "PATH", "/bin:/usr/bin:/usr/local/bin", 0) != 0)
			return (1);
	return (0);
}
