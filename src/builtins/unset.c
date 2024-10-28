/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:08:58 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/28 17:55:27 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	unset_head(t_env **env)
{
	t_env	*temp;

	temp = *env;
	if ((*env)->next)
		*env = (*env)->next;
	free(temp->var_name);
	temp->var_name = NULL;
	free(temp->var_val);
	temp->var_val = NULL;
	free(temp);
	temp = NULL;
	return (0);
}

static int	unset_node(t_env *node, t_env *prev)
{
	prev->next = node->next;
	free(node->var_name);
	node->var_name = NULL;
	free(node->var_val);
	node->var_val = NULL;
	free(node);
	node = NULL;
	return (0);
}

static int	handle_unset(t_env **env, char *var_name)
{
	t_env	*prev;
	t_env	*curr;

	curr = *env;
	if (!ft_strncmp(curr->var_name, var_name, ft_strlen(var_name) + 1))
	{
		unset_head(env);
		return (0);
	}
	prev = *env;
	curr = curr->next;
	while (curr)
	{
		if (!ft_strncmp(curr->var_name, var_name, ft_strlen(var_name) + 1))
		{
			unset_node(curr, prev);
			return (0);
		}
		curr = curr->next;
		prev = prev->next;
	}
	return (0);
}

int	ft_unset(char **args, t_env **env)
{
	int	i;

	if (args && !args[1])
		return (merror(args[0], NULL, "not enough arguments", 1));
	if (args && args[1])
	{
		i = 1;
		while (args[i])
		{
			handle_unset(env, args[i]);
			i++;
		}
	}
	return (0);
}
