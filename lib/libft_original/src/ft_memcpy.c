/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:21:33 by jrichir           #+#    #+#             */
/*   Updated: 2023/10/25 17:04:58 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// keep pointer protection in this one ?
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned int		i;
	char				*cdst;
	char				*csrc;

	if (!dst && !src)
	{
		return (0);
	}
	cdst = (char *)dst;
	csrc = (char *)src;
	i = 0;
	while (i < n)
	{
		cdst[i] = csrc[i];
		i++;
	}
	return (dst);
}
