/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:08:58 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/21 17:25:06 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	update_env(char *dest_path, char *curr_path, t_env *env)
{
	if (!env)
		return (1);
	while (env)
	{
		if (ft_strncmp(env->var_name, "PWD", 4) == 0)
		{
			env->var_val = dest_path;
		}
		if (ft_strncmp(env->var_name, "OLDPWD", 7) == 0)
		{
			env->var_val = curr_path;
		}
		env = env->next;
	}
	return (0);
}

// 1) cd sans argument renvoie au dossier utilisateur (= Home = ~)
//    SI la variable d'env HOME n'a pas ete unset, sinon erreur
// 	  `cd: HOME not set` (return value = 1)
// 2) cd updates OLDPWD and PWD in env if they are set
// 
// 3) Going back to parent folder which has been destroyed while 
//    being in child folder :
//    cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
// 
// getcwd()'s output `curr_path` is malloc'ed and must be freed at some point...
int	ft_cd(char **args, t_env *env)
{
	char	*curr_path;
	char	*dest_path;
	int		argc;

	dest_path = NULL;
	argc = ft_arraylen(args);
	if (argc > 2)
		return (ft_putstr_fd("cd: too many arguments\n", 2), 1);
	else if (argc == 2)
	{
		curr_path = getcwd(NULL, 0);
		dest_path = args[1];
		if (ft_strncmp(dest_path, "-", 2) == 0)
		{
			;// case `cd -`, relying on the OLDPWD variable
			// /!\ `cd -` prints the path where it goes !
		}
		else if (ft_strncmp(dest_path, "--", 3))
		{
			;// case `cd --`, equivalent to cd without argument, relying on the HOME variable
		}
		if (chdir((const char *)dest_path) == 0)
			return (update_env(dest_path, curr_path, env), 0);
		else
			;//... error handling, check dest_path existence/accessibility
	}
	else if (!dest_path && !env)
		return (ft_putstr_fd("cd: HOME not set\n", 2), 1);
	else if (!dest_path)
	{
		dest_path = NULL;
		while (env)
		{
			if (ft_strncmp(env->var_name, "HOME", 5) == 0)
			{
				dest_path = env->var_val;
				curr_path = getcwd(NULL, 0);
				if (dest_path)
					chdir((const char *)dest_path);
				return (update_env(dest_path, curr_path, env), 0);
			}
			env = env->next;
		}
		return (ft_putstr_fd("cd: HOME not set\n", 2), 1);
	}
	return (1);
}
