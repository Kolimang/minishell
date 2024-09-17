/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:21:06 by jrichir           #+#    #+#             */
/*   Updated: 2024/03/25 10:32:56 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;

	if ((char)c == '\0')
	{
		return ((char *)(s + ft_strlen(s)));
	}
	else
	{
		i = (int)ft_strlen(s) - 1;
		while (i >= 0)
		{
			if (s[i] == (char)c)
			{
				return ((char *)&s[i]);
			}
			i--;
		}
		return (NULL);
	}
}
