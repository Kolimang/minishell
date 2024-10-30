/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:44:04 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/29 11:20:47 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_strtrim_replace(char **str)
{
	char	*copy;

	if (!str)
		return (NULL);
	copy = *str;
	*str = ft_strtrim(*str, " ");
	free (copy);
	copy = NULL;
	if (!*str)
		return (NULL);
	return (*str);
}
