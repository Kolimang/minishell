/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:08:58 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/17 17:04:51 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_echo(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (args && args[1])
	{
		if (ft_strncmp(args[1], "-n", 2) == NULL)
		{
			i = 2;
			newline = 0;
		}
		while (args[i])
		{
			ft_printf("%s", args[i]);
			if (args[i + 1])
				ft_printf(" ");
			i++;
		}
	}
	if (newline == 1)
		ft_printf("\n");
	return (0);
}
