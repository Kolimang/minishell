/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:08:58 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/27 18:22:57 by jrichir          ###   ########.fr       */
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
		*value = ft_substr(str, len + 1, ft_strlen(str) - (size_t)(len + 1));
	}
	else
	{
		*name = str;
		*value = NULL;
	}
	return (0);
}

int	ft_export(char **args, t_env *env)
{
	char	*name;
	char	*value;
	int		i;
	int		res;

	res = 0;
	if (args && !args[1])
		return (print_env(env, 1), 0);
	if (args && args[1])
	{
		i = 1;
		while (args[i])
		{
			res = check_name(args[i]);
			if (res)
				merror(args[0], args[i], "not a valid identifier", 1);
			else
			{
				check_value(args[i], &name, &value);
				update_env(name, value, &env);
			}
			i++;
		}
	}
	return (res);
}
