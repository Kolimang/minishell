/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:15:22 by lboumahd          #+#    #+#             */
/*   Updated: 2024/10/09 14:52:04 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_shlvl(t_env *env)
{
	char	*current;
	char	**cmd;
	char	*tmp;
	int		val;

	current = get_env_val(env, "SHLVL");
	if(!current)
		current = "0";
	
	val = ft_atoi(current);
	tmp = ft_itoa(val + 1);
	cmd = malloc (sizeof(char *) * 3);
	//to finishe once export is coded 
	free(cmd);
	free(tmp);
}

t_env	*create_env_node(const char *var_name, const char *var_val, int index)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->var_name = ft_strdup(var_name);
	new_node->var_val = ft_strdup(var_val);
	new_node->index = index;
	new_node->next = NULL;
	return (new_node);
}

void	free_env(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		temp = env;
		env = env->next;
		free(temp->var_name);
		free(temp->var_val);
		free(temp);
	}
}
