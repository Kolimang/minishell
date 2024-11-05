/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:15:22 by lboumahd          #+#    #+#             */
/*   Updated: 2024/11/05 12:05:11 by lboumahd         ###   ########.fr       */
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
	//ft_export
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
