/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:53:28 by jrichir           #+#    #+#             */
/*   Updated: 2024/09/17 16:28:46 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*result;
	int		i;

	if (!s)
		return (NULL);
	if ((char)c == '\0')
	{
		return (((char *)s) + (ft_strlen(s) * sizeof(char)));
	}
	else
	{
		i = 0;
		while (s[i] != '\0')
		{
			if (s[i] == (char)c)
			{
				result = (char *)&s[i];
				return (result);
			}
			i++;
		}
		return (NULL);
	}
}
