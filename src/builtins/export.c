/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:08:58 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/22 16:22:16 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_name(char *name)
{
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (1);
	return (0);
}

static int	check_value(char *str, char **name, char **value)
{
	char	*equal;
	int		len;

	equal = ft_strchr(str, '=');
	if (equal)
	{
		len = equal - str;
		*name = ft_substr(str, 0, (size_t)len);
		*value = ft_substr(str, len, ft_strlen(str) - (size_t)len);
	}
	else
		*name = str;
		*value = NULL;
}

static int	update_env(char *name, char *value, t_env **env)
{
	if (!*env)
		return (1);
	while (*env)
	{
		if (ft_strncmp((*env)->var_name, name, ft_strlen(name)) == 0)
			if (value)
			{
				if ((*env)->var_val)
					free((*env)->var_val);
				(*env)->var_val = value;
				return (0);
			}
		env = (*env)->next;
	}
	add_env_var(env, name, value, 1);
	return (0);
}

int	ft_export(char **args, t_env *env)
{
	char	*name;
	char	*value;
	int		i;
	int		res;

	res = 0;
	i = 1;
	if (args && args[1])
	{
		while (args[i])
		{
			res = check_name(args[i]);
			if (res)
				return (ft_putstr_fd("export: `%s': not a valid identifier\n", 2), 1);
			check_value(args[i], &name, &value);
			update_env(name, value, &env);
			// To be tested and checked for missing steps/checks
			i++;
		}
	}
	return (0);
}
