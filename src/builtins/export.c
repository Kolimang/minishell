/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:08:58 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/24 12:51:56 by jrichir          ###   ########.fr       */
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

static int	update_env(char *name, char *value, t_env **env)
{
	t_env	*head;

	if (!*env)
		return (1);
	head = *env;
	while (head)
	{
		if (ft_strncmp(head->var_name, name, ft_strlen(name) + 1) == 0)
			if (value)
			{
				if (head->var_val)
					free(head->var_val);
				head->var_val = value;
				return (0);
			}
		head = head->next;
	}
	add_env_var(env, name, value, 1);
	return (0);
}

int	ft_env(char **args, t_env *env)
{
	if (!env)
		return (ft_putstr_fd("env: no environment set\n", 2), 1);
	if (args && args[1])
		return (ft_putstr_fd("env: too many arguments\n", 2), 1);
	if (args && !args[1])
		print_env(env, 2);
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

int	merror(char *cmd, char *arg, char *msg, int value)
{
	if (cmd)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
	}
	if (arg)
	{
		write(2, "`", 1);
		write(2, arg, ft_strlen(arg));
		write(2, "': ", 3);
	}
	if (msg)
	{
		write(2, msg, ft_strlen(msg));
	}
	write(2, "\n", 1);
	return (value);
}
