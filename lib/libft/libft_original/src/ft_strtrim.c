/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:09:52 by jrichir           #+#    #+#             */
/*   Updated: 2024/03/25 10:33:04 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_string(char *s, char c)
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

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	int		i;
	int		start;
	int		end;

	if (s1 == NULL)
		return (NULL);
	else if (s1[0] == '\0' || set == NULL || set[0] == '\0')
		return (ft_strdup(s1));
	len = ft_strlen((char *)s1);
	i = 0;
	while (in_string((char *)set, s1[i]))
		i++;
	start = i;
	i = 1;
	while (in_string((char *)set, s1[len - i]))
		i++;
	end = len + 1 - i;
	return (ft_substr((char *)s1, start, end - start));
}
