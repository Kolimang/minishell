/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:15:22 by lboumahd          #+#    #+#             */
/*   Updated: 2024/11/22 05:59:07 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_env(t_env **envdp)
{
	t_env	*temp;
	t_env	*env;

	env = *envdp;
	while (env)
	{
		temp = env;
		env = env->next;
		free(temp->var_name);
		temp->var_name = NULL;
		free(temp->var_val);
		temp->var_val = NULL;
		free(temp);
		temp = NULL;
	}
	//free(envdp);//DEBUG
}

int	cleanup_envs(t_envs *envs, int exit_code)
{
	free_env(envs->l_env);
	free(envs->l_env);//DEBUG
	free(envs);
	return (exit_code);
}
