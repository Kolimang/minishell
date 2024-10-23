/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:10:13 by lboumahd          #+#    #+#             */
/*   Updated: 2024/10/23 15:03:34 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_env_val(t_env *env, const char *var_name)
{
	while (env)
	{
		if (ft_strncmp(env->var_name, var_name, ft_strlen(var_name) + 1) == 0)
			return (env->var_val);
		env = env->next;
	}
	return (NULL);
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
	return (env);
}

// mode 1 --> export() without arg 
//      \__ sorted list
//      \__ includes empty-string variables AND NULL-valued variables
// mode 2 --> env() without arg
//      \__ not sorted list
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
