/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:53:28 by jrichir           #+#    #+#             */
/*   Updated: 2024/03/19 15:28:21 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	if (!haystack || !needle)
		return (NULL);
	if ((char)(needle[0]) == '\0')
		return ((char *)haystack);
	i = 0;
	j = 0;
	while (needle[j] && haystack[i] && i < len)
	{
		if (haystack[i] == needle[j])
		{
			while (needle[j] && needle[j] == haystack[i + j] && i + j < len)
			{
				j++;
			}
			if ((char)needle[j] == '\0')
				return ((char *)&haystack[i]);
			j = 0;
		}
		i++;
	}
	return (NULL);
}
