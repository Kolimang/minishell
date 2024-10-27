/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:08:58 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/24 15:48:14 by jrichir          ###   ########.fr       */
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
	return (0);
}

static int	go_home(char *dest_path, char *curr_path, t_env *env)
{
	t_env	*head;

	if (!env)
		return (ft_putstr_fd("cd: HOME not set\n", 2), 1);
	head = env;
	while (head)
	{
		if (ft_strncmp(head->var_name, "HOME", 5) == 0)
		{
			dest_path = head->var_val;
			if (!dest_path || dest_path[0] == '\0')
				return (ft_putstr_fd("cd: HOME not set\n", 2), 1);
			if (access(dest_path, R_OK) == 0)
			{
				curr_path = getcwd(NULL, 0);
				chdir((const char *)dest_path);
				return (update_pwd(dest_path, curr_path, env), 0);
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

static int	go(char *dest_path, char *curr_path, t_env *env)
{
	if (!dest_path || dest_path[0] == '\0' || access(dest_path, F_OK) != 0)
		return (ft_putstr_fd("cd: No such file or directory\n", 2), 1);
	else if (access(dest_path, R_OK) != 0)
		return (ft_putstr_fd("cd: Permission denied\n", 2), 1);
	else
	{
		curr_path = getcwd(NULL, 0);
		chdir((const char *)dest_path);
		free(dest_path);
		dest_path = getcwd(NULL, 0);
	}
	return (update_pwd(dest_path, curr_path, env), 0);
}

// 0) cd sans argument, ou avec pour seul argument `--`, ou 1er argument `~`,
//    renvoie au dossier utilisateur (= Home = ~) SI la variable d'env HOME 
//    n'a pas ete unset, sinon erreur `cd: HOME not set` (return value = 1)
//
// 1) cd avec plus d'un argument : consider the first one, even if the first one
//    is `-`, `.` or `..`, or the second one if the first one is `--`
// 
// 2) `cd -beta` --> `cd: -b: invalid option` (return value = 1)
//
// 3) cd updates OLDPWD and PWD in env IF THEY ARE SET
// 
// 4) Going back to parent folder which has been destroyed while 
//    being in child folder :
//    `cd: error retrieving current directory: getcwd: cannot access parent 
//     directories: No such file or directory`
// 
// 5) chmod doesn't allow to cd in a folder named `alpha` :
//    `cd: alpha: Permission denied` (return value = 1)
//
// 6) Going to inexisting folder `cd beta`
//    `cd: beta: No such file or directory` (return value = 1)
//
// getcwd()'s output `curr_path` is malloc'ed and must be freed at some point...

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
		res = go(args[2], curr_path, env);
	else
		res = go(args[1], curr_path, env);
	if (res > 0)
		return (1);
	return (0);
}
