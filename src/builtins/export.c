/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:08:58 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/20 15:29:59 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_name(char *name)
{
	int	i;

	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (1);
	i = 1;
	while (name[i])
	{
		if (name[i] == '+' && name[i + 1] && name[i + 1] == '=')
			break ;
		if (name[i] == '=')
			break ;
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

static int	check_value(char *str, char **name, char **value, int *mode)
{
	char	*equal;
	char	*temp;
	int		len;

	equal = ft_strchr(str, '=');
	if (!equal)
	{
		*name = str;
		*value = NULL;
		return (0);
	}
	len = equal - str;
	if (str[len - 1] && str[len - 1] == '+')
	{
		*mode = 1;
		*name = ft_substr(str, 0, (size_t)len - 1);
	}
	else
		*name = ft_substr(str, 0, (size_t)len);
	*value = ft_substr(str, len + 1, ft_strlen(str) - (size_t)(len + 1));
	temp = ft_strtrim(*value, " \"\'");
	free(*value);
	*value = temp;
	return (0);
}

int	ft_export(char **args, t_env **env)
{
	char	*name;
	char	*value;
	int		i;
	int		res;
	int		mode;

	res = 0;
	mode = 0;
	value = NULL;
	if (args && !args[1])
		return (set_exit_status(print_env(*env, 1)));
	if (args && args[1])
	{
		i = 1;
		while (args[i])
		{
			res = check_name(args[i]);
			if (res)
				return (merror(args[0], NULL, args[i], 10));
			check_value(args[i], &name, &value, &mode);
			update_env(name, value, env, mode);
			i++;
		}
	}
	return (set_exit_status(res));
}
