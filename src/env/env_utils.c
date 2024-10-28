/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:15:22 by lboumahd          #+#    #+#             */
/*   Updated: 2024/10/28 13:26:32 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	set_shlvl(t_env *env)
{
	char	*current;
	char	**cmd;
	char	*tmp;
	int		val;

	current = get_env_val(env, "SHLVL");
	if (!current)
		current = "0";
	val = ft_atoi(current);
	tmp = ft_itoa(val + 1);
	cmd = malloc (sizeof(char *) * 3);
	//to finish once export is coded
	free(cmd);
	free(tmp);
}

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

static void	swap_nodes(t_env *node1, t_env *node2)
{
	t_env	*swap;

	swap = node1->next;
	node1->next = node2;
	node2->next = swap;
}

// removed a break after swap_nodes() to fit in 25 lines,
// I think it was not necessary
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
				}
			}
			curr = curr->next;
		}
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
