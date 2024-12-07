/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 18:08:39 by jrichir           #+#    #+#             */
/*   Updated: 2024/12/07 18:09:29 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_env(t_env **env)
{
	set_shlvl(env);
	if (env && !get_env_val((*env), "PWD"))
		if (add_env_var(env, "PWD", getcwd(NULL, 0), 0) != 0)
			return (1);
	if (env && !get_env_val((*env), "OLDPWD"))
		if (add_env_var(env, "OLDPWD", NULL, 0) != 0)
			return (1);
	if (env && !get_env_val((*env), "PATH"))
		if (add_env_var(env, "PATH", "/bin:/usr/bin:/usr/local/bin", 0) != 0)
			return (1);
	return (0);
}

char	*get_env_node(t_env *env, const char *var_name)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (ft_strncmp(temp->var_name, var_name, ft_strlen(var_name) + 1) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}
