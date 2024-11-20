/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:44:04 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/20 14:00:58 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

// char	*get_home_path(t_env *env)
// {
// 	t_env	*head;

// 	if (!env)
// 		return (NULL);
// 	head = env;
// 	while (head)
// 	{
// 		if (ft_strncmp(head->var_name, "HOME", 5) == 0)
// 			return (head->var_val);
// 		head = head->next;
// 	}
// 	return (NULL);
// }

char	*expand_tilde_path(char *unexpanded_path, t_env *env)
{
	char	*abs_path;
	char	*home_path;

	home_path = get_env_val(env, "HOME");
	if (!home_path)
		return (merror("cd", NULL, NULL, 14), NULL);
	abs_path = ft_strjoin(home_path, &unexpanded_path[1]);
	//free(unexpanded_path); // at the moment, double free with it, but I may need to reinstore later when reverting to original go() function
	return (abs_path);
}
