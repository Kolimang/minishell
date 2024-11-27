/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:44:04 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/27 14:29:07 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	switch_bool(int *val)
{
	if (*val == 0)
		*val = 1;
	else
		*val = 0;
}

int	is_directory(char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

int	char_in_set(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	array_len(char **array)
{
	int	i;

	if (!array)
		return (-1);
	i = 0;
	while (array[i])
		i++;
	return (i);
}

char	*expand_tilde_path(char *unexpanded_path, t_env *env)
{
	char	*abs_path;
	char	*home_path;

	home_path = get_env_val(env, "HOME");
	if (!home_path)
		return (merror("cd", NULL, NULL, 14), NULL);
	abs_path = ft_strjoin(home_path, &unexpanded_path[1]);
	return (abs_path);
}
