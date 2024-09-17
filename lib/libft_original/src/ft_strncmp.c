/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:04:34 by jrichir           #+#    #+#             */
/*   Updated: 2024/03/25 10:32:40 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// keep pointer protection in this one
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	if (!s1 && !s2 && n == 0)
		return (0);
	i = -1;
	while ((*s1 || *s2) && (++i < n))
	{
		if (*s1 && *s2 && *s1 != *s2)
			return ((int)((unsigned char)*s1 - (unsigned char)*s2));
		else if (*s1 == *s2 && i == n - 1)
			return (0);
		else if (!s2 || *s2 == '\0')
		{
			return ((unsigned char)*s1);
		}
		else if (!s1 || *s1 == '\0')
			return (-1 * (unsigned char)*s2);
		s1++;
		s2++;
	}
	return (0);
}
