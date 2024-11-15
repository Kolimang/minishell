/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:44:04 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/13 16:09:17 by jrichir          ###   ########.fr       */
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

// f = first string  is autoreferential, meaning we do s1 = ft_strjoin(s1, s2)
// s = second string is autoreferential, meaning we do s2 = ft_strjoin(s1, s2)
char	*ft_strjoin_replace(char *s1, char *s2, char autoref_string)
{
	char	*temp;

	if (autoref_string == 'f')
	{
		temp = s1;
		s1 = ft_strjoin(s1, s2);
		free(temp);
		return (s1);
	}
	else if (autoref_string == 's')
	{
		temp = s2;
		s2 = ft_strjoin(s1, s2);
		free(temp);
		return (s2);
	}
	return (NULL);
}

int	set_exit_status(int exitcode)
{
	g_ret_value = exitcode;
	return (exitcode);
}
