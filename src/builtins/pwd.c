/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:08:58 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/20 13:01:28 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	update_pwd(char *dest_path, char *curr_path, t_env *env)
{
	t_env	*head;
	char	*home;

	if (!env)
		return (1);
	home = get_env_val(env, "HOME");
	head = env;
	while (head)
	{
		if (ft_strncmp(head->var_name, "PWD", 4) == 0)
		{
			if (head->var_val)
				free(head->var_val);
			if (dest_path)
				head->var_val = ft_strdup(dest_path);
			else if (home)
				head->var_val = ft_strdup(get_env_val(env, "HOME"));
			else
				head->var_val = ft_strdup("/");
		}
		if (ft_strncmp(head->var_name, "OLDPWD", 7) == 0)
		{
			if (head->var_val)
				free(head->var_val);
			if (curr_path)
				head->var_val = ft_strdup(curr_path);
			else if (home)
				head->var_val = ft_strdup(get_env_val(env, "HOME"));
			else
				head->var_val = ft_strdup("/");
		}
		head = head->next;
	}
	free(curr_path);
	return (0);
}

int	ft_pwd(char **args, t_env *env)
{
	char	*path;
	t_env	*head;

	if (!env)
		return (set_exit_status(1));
	(void)args;
	head = env;
	while (head)
	{
		if (ft_strncmp(head->var_name, "PWD", 4) == 0)
		{
			ft_printf("%s\n", head->var_val);
			return (set_exit_status(0));
		}
		head = head->next;
	}
	path = getcwd(NULL, 0);
	if (path)
	{
		ft_printf("%s\n", path);
		free(path);
	}
	return (set_exit_status(0));
}
