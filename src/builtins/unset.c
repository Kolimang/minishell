/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:08:58 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/27 19:18:34 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_unset(char **args, t_env *env)
{
	char	*name;
	char	*value;
	int		i;
	int		res;

	res = 0;
	if (args && !args[1])
		return (merror(args[0], NULL, "not enough arguments"));
	if (args && args[1])
	{
		i = 1;
		while (args[i])
		{
			while (env)
			{
				;//
			}
			i++;
		}
	}
	return (res);
}
