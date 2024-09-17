/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:50:11 by jrichir           #+#    #+#             */
/*   Updated: 2024/03/20 14:01:42 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
	{
		return (0);
	}
	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_gnl_strjoin(char **s1, char **s2, int free_param)
{
	size_t	len;
	char	*joined;
	int		i;
	int		j;

	if ((!s1 && !s2) || (!*s1 && !*s2))
		return (NULL);
	len = ft_strlen(*s1) + ft_strlen(*s2) + 1;
	joined = (char *)malloc(len * sizeof(char));
	if (!joined)
		return (del(s1), del(s2), NULL);
	i = -1;
	while (*s1 && (*s1)[++i])
		joined[i] = (*s1)[i];
	if (i == -1)
		i = 0;
	j = -1;
	while (*s2 && (*s2)[++j])
		joined[i++] = (*s2)[j];
	joined[i] = '\0';
	if (free_param % 2 == 0)
		del(s1);
	if (free_param % 3 == 0)
		del(s2);
	return (joined);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;

	if (!dst || !src)
		return (0);
	if (dstsize > 0)
	{
		i = 0;
		while (src[i] && (i + 1) < dstsize)
		{
			dst[i] = (char)src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

char	*ft_gnl_strdup(char **s)
{
	int		len;
	char	*dup;

	if (!s || !*s)
		return (NULL);
	len = ft_strlen(*s);
	dup = malloc((len + 1) * sizeof(char));
	if (!dup)
	{
		return (del(s), NULL);
	}
	ft_strlcpy(dup, *s, len + 1);
	return (dup);
}

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
		while (s && s[i] != '\0')
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
