/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:08:58 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/27 15:39:10 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	update_data(char *path, t_env *head, t_env *env)
{
	char	*home;

	if (!env)
		return (1);
	home = get_env_val(env, "HOME");
	if (head->var_val)
		free(head->var_val);
	if (path)
	{
		head->var_val = ft_strdup(path);
		free (path);
	}
	else if (home)
		head->var_val = ft_strdup(get_env_val(env, "HOME"));
	else
		head->var_val = ft_strdup("/");
	return (0);
}

int	update_pwd(char *dest_path, char *curr_path, t_env *env)
{
	t_env	*head;

	if (!env)
		return (1);
	head = env;
	while (head)
	{
		if (ft_strncmp(head->var_name, "PWD", 4) == 0)
			update_data(dest_path, head, env);
		if (ft_strncmp(head->var_name, "OLDPWD", 7) == 0)
			update_data(curr_path, head, env);
		head = head->next;
	}
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
