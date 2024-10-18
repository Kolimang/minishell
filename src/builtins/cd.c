/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:08:58 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/18 15:38:07 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	set_pwd(char *path, t_env *env)
{
	while (env)
	{
		if (ft_strncmp(env->var_name, "PWD", 3) == 0)
		{
			env->var_val = path;
			return (0);
		}
		env = env->next;
	}
	// on (re)crée ci-dessous la variable PWD dans env
	// avec la valeur 'path'
}

// 1) cd sans argument renvoie au dossier utilisateur (= Home = ~)
//    SI la variable d'env HOME n'a pas ete unset
// 2) cd sets PWD again in env if PWD was unset
int	ft_cd(char **args, t_env *env)
{
	char	*path;
	char 	*home_path;
	int		argc;

	argc = ft_arraylen(args);
	if (args && args[1])
		if (argc == 2)
			path = args[1];
		else if (argc == 3)
			;// substitute args[1] if present in pwd by args[2]
			// to form a new pwd and go there, if "there" is
			// an existing directory, else display
			// cd: no such file or directory: /Users/jtwoir/jGithub/minishell
			// ou alors on se casse pas la tete et on return "too many arguments"
		else if (argc > 3)
			ft_putstr_fd("cd: too many arguments\n", 2);
	if (!path && !env)
		return (-1);
	if (!path)
	{
		home_path == NULL;
		while (env)
		{
			if (ft_strncmp(env->var_name, "HOME", 4) == 0)
			{
				home_path = env->var_val;
				chdir((const char *)home_path);
				return (set_pwd(home_path, env), 0);
			}
			env = env->next;
		}
		ft_putstr_fd("cd: HOME not set\n", 2);
	}
	else if(chdir((const char *)path) == 0)
		return (set_pwd(path, env), 0);
	else
		return (-1);
}
