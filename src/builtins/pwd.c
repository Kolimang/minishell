/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:08:58 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/14 13:51:29 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// int	ft_pwd(char **args, t_env *env)
// {
// 	char	*path;
// 	t_env	*head;

// 	if (args && args[1])
// 		return (merror(args[0], NULL, "too many arguments", 1));
// 	if (!env)
// 		return (set_exit_status(1));
// 	head = env;
// 	while (head)
// 	{
// 		if (ft_strncmp(head->var_name, "PWD", 4) == 0)
// 		{
// 			ft_printf("%s\n", head->var_val);
// 			return (set_exit_status(0));
// 		}
// 		head = head->next;
// 	}
// 	path = getcwd(NULL, 0);
// 	if (path)
// 	{
// 		ft_printf("%s\n", path);
// 		free(path);
// 	}
// 	return (set_exit_status(0));
// }
// suggestion

// int	ft_pwd(char **args, t_env *env)
// {
// 	char	*path;
// 	t_env	*head;

// 	if (args && args[1])
// 		return (merror(args[0], NULL, NULL, 13)); // too many arguments
// 	...
int	ft_pwd(char **args, t_env *env)
{
	char	*path;
	t_env	*head;

	if (!env)
		return (set_exit_status(1));
	head = env;
	while (head)
	{
		if (ft_strncmp(head->var_name, "PWD", 4) == 0)
		{
			ft_printf("%s\n", head->var_val);
			return (set_exit_status(0));
		}
		head = head->next;
	}
	path = getcwd(NULL, 0);
	if (path)
	{
		ft_printf("%s\n", path);
		free(path);
	}
	return (set_exit_status(0));
}
