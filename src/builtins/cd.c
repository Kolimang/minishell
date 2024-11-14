/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:08:58 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/14 18:13:22 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	update_pwd(char *dest_path, char *curr_path, t_env *env)
{
	t_env	*head;

	if (!env)
		return (1);
	head = env;
	while (head)
	{
		if (ft_strncmp(head->var_name, "PWD", 4) == 0)
		{
			if (head->var_val)
				free(head->var_val);
			head->var_val = ft_strdup(dest_path);
		}
		if (ft_strncmp(head->var_name, "OLDPWD", 7) == 0)
		{
			if (head->var_val)
				free(head->var_val);
			head->var_val = ft_strdup(curr_path);
		}
		head = head->next;
	}
	free(curr_path);
	return (0);
}

static int	go_home(char *dest_path, char *curr_path, t_env *env)
{
	t_env	*head;
    char    *home_path;
    char    *new_path;

	if (!env)
		return (ft_putstr_fd("cd: HOME not set\n", 2), 1);
	head = env;
	while (head)
	{
		if (ft_strncmp(head->var_name, "HOME", 5) == 0)
		{
            home_path = head->var_val;
			if (!home_path || home_path[0] == '\0')
				return (ft_putstr_fd("cd: HOME not set\n", 2), 1);
			if (access(home_path, R_OK) == 0)
			{
				curr_path = getcwd(NULL, 0);
                if (!curr_path)
                    return (ft_putstr_fd("cd: error retrieving current directory\n", 2), 1);
                
                if (chdir(home_path) != 0)
                {
                    free(curr_path);
                    return (ft_putstr_fd("cd: cannot change directory\n", 2), 1);
                }

                new_path = getcwd(NULL, 0);
                if (!new_path)
                {
                    free(curr_path);
                    return (ft_putstr_fd("cd: error retrieving current directory\n", 2), 1);
                }

				return (update_pwd(new_path, curr_path, env), 0);
			}
			return (ft_putstr_fd("cd: Permission denied\n", 2), 1);
		}
		head = head->next;
	}
	return (ft_putstr_fd("cd: HOME not set\n", 2), 1);
}
static int	go_prev(char *dest_path, char *curr_path, t_env *env)
{
	t_env	*head;

	if (!env)
		return (ft_putstr_fd("cd: OLDPWD not set\n", 2), 1);
	head = env;
	while (head)
	{
		if (ft_strncmp(head->var_name, "OLDPWD", 7) == 0)
		{
			dest_path = head->var_val;
			if (!dest_path || dest_path[0] == '\0')
				return (ft_putstr_fd("cd: OLDPWD not set\n", 2), 1);
			if (access(dest_path, R_OK) == 0)
			{
				curr_path = getcwd(NULL, 0);
				chdir((const char *)dest_path);
				ft_printf("%s\n", dest_path);
				return (update_pwd(dest_path, curr_path, env), 0);
			}
			return (ft_putstr_fd("cd: Permission denied\n", 2), 1);
		}
		head = head->next;
	}
	return (ft_putstr_fd("cd: OLDPWD not set\n", 2), 1);
}

static int	go(char *dest_path, char *curr_path, t_env *env, int allowedoption)
{
    char *new_path;

    if (allowedoption && dest_path[0] == '-')
        return (merror("cd", dest_path, "no option supported for cd", 1));
    else if (!is_directory(dest_path))
        return (merror("cd", dest_path, NULL, 11));
    else if (!dest_path || dest_path[0] == '\0' || access(dest_path, F_OK) != 0)
        return (merror("cd", dest_path, NULL, 1));
    else if (access(dest_path, X_OK) != 0)
        return (merror("cd", dest_path, "Permission denied", 1));
    else
    {
        curr_path = getcwd(NULL, 0);
        if (!curr_path)
            return (merror("cd", NULL, "Error retrieving current directory", 1));
        if (chdir((const char *)dest_path) != 0)
            return (free(curr_path), ft_putstr_fd("cd: cannot change directory\n", 2), 1);
        free(curr_path);
        new_path = getcwd(NULL, 0);
        if (!new_path)
            return (merror("cd", NULL, "Error retrieving new directory", 1));
        return (update_pwd(new_path, curr_path, env), 0);
    }
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
	argc = ft_arraylen(args);
	if (argc == 1 || (argc == 2 && !ft_strncmp(args[1], "--", 3))
		|| !ft_strncmp(args[1], "~", 2))
	{
		res = go_home(dest_path, curr_path, env);
	}
	else if (!ft_strncmp(args[1], "-", 2)
		|| (!ft_strncmp(args[1], "--", 3) && !ft_strncmp(args[2], "-", 2)))
		res = go_prev(dest_path, curr_path, env);
	else if (!ft_strncmp(args[1], "--", 3))
		res = go(args[2], curr_path, env, 0);
	else
		res = go(args[1], curr_path, env, 1);
	if (res > 0)
		return (set_exit_status(res));
	return (set_exit_status(0));
}
