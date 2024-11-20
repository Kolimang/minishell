/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:08:58 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/20 13:27:39 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	go_home(char *curr_path, t_env *env)
{
	char	*home_path;
	char	*new_path;

	home_path = get_env_val(env, "HOME");
	if (!home_path || home_path[0] == '\0')
		return (merror("cd", NULL, NULL, 14));
	if (access(home_path, R_OK) != 0)
		return (merror("cd", NULL, NULL, 15));
	curr_path = getcwd(NULL, 0);
	//if (!curr_path)
	//	return (merror("cd", NULL, NULL, 16));
	if (chdir(home_path) != 0)
	{
		free(curr_path);
		return (merror("cd-bouillon", NULL, NULL, 17));
	}
	new_path = getcwd(NULL, 0);
	if (!new_path)
	{
		free(curr_path);
		return (merror("cd-cata", NULL, NULL, 16));
	}
	return (update_pwd(new_path, curr_path, env), 0);
}

static int	go_safe(t_env *env)
{
	char	*home_path;
	char	*new_path;

	home_path = get_env_val(env, "HOME");
	if (!home_path || home_path[0] == '\0')
	{
		new_path = ft_strdup("/");
		return (update_pwd(new_path, 0, env), 0);
	}
	else
	{
		go_home(0, env);
	}
	return (0);
}

static int	go_prev(char *dest_path, char *curr_path, t_env *env)
{
	t_env	*head;

	if (!env)
		return (merror("cd", NULL, NULL, 18));
	head = env;
	while (head)
	{
		if (ft_strncmp(head->var_name, "OLDPWD", 7) == 0)
		{
			dest_path = head->var_val;
			if (!dest_path || dest_path[0] == '\0')
				return (merror("cd", NULL, NULL, 18));
			if (access(dest_path, R_OK) == 0)
			{
				curr_path = getcwd(NULL, 0);
				chdir((const char *)dest_path);
				ft_printf("%s\n", dest_path);
				return (update_pwd(dest_path, curr_path, env), 0);
			}
			return (merror("cd", NULL, NULL, 15));
		}
		head = head->next;
	}
	return (merror("cd", NULL, NULL, 18));
}

static int	go(char *dest_path, char *curr_path, t_env *env, int allowedoption)
{
	char	*new_path;

	if (allowedoption && dest_path[0] == '-')
		return (merror("cd", dest_path, NULL, 19));
	else if (!dest_path || dest_path[0] == '\0' || access(dest_path, F_OK) != 0)
		return (merror("cd", dest_path, NULL, 1));
	else if (!is_directory(dest_path))
		return (merror("cd", dest_path, NULL, 11));
	else if (access(dest_path, X_OK) != 0)
		return (merror("cd", dest_path, NULL, 15));
	else
	{
		curr_path = getcwd(NULL, 0);
		if (chdir((const char *)dest_path) != 0)
			return (free(curr_path), merror("cd", NULL, NULL, 17));
		new_path = getcwd(NULL, 0);
		if (!curr_path && !new_path)
		{
			go_safe(env);
			return (merror("cd", NULL, NULL, 16));
		}
		//if (!curr_path)
		//	return (merror("cd", NULL, NULL, 16));
		if (!new_path)
			return (merror("cd", NULL, NULL, 20));
		return (update_pwd(new_path, curr_path, env), 0);
	}
}

static int	go_tilde(char *dest_path, char *curr_path, t_env *env, int allowedoption)
{
	char	*new_path;
	char	*exp_path;

	(void)allowedoption;
	exp_path = expand_tilde_path(dest_path, env);
	//ft_printf("expanded path: %s\n", exp_path);//DEBUG
	curr_path = getcwd(NULL, 0);
	if (chdir(exp_path) != 0)
		return (free(curr_path), merror("cd", NULL, NULL, 17));
	new_path = getcwd(NULL, 0);
	if (!new_path)
		return (merror("cd", NULL, NULL, 20));
	return (update_pwd(new_path, curr_path, env), 0);
}

int	ft_cd(char **args, t_env *env)
{
	char	*curr_path;
	char	*dest_path;
	int		argc;
	int		res;

	res = 0;
	dest_path = NULL;
	curr_path = NULL;
	argc = array_len(args);
	if (argc == 1 || (argc == 2 && !ft_strncmp(args[1], "--", 3))
		|| !ft_strncmp(args[1], "~", 2))
		res = go_home(curr_path, env);
	else if (!ft_strncmp(args[1], "-", 2)
		|| (!ft_strncmp(args[1], "--", 3) && !ft_strncmp(args[2], "-", 2)))
		res = go_prev(dest_path, curr_path, env);
	else if (!ft_strncmp(args[1], "--", 3))
		res = go(args[2], curr_path, env, 0);
	else if (args[1][0] == '~')
		res = go_tilde(args[1], curr_path, env, 1);
	else
		res = go(args[1], curr_path, env, 1);
	if (res > 0)
		return (set_exit_status(res));
	return (set_exit_status(0));
}
