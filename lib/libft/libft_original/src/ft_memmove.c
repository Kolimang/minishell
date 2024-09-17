/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:34:42 by jrichir           #+#    #+#             */
/*   Updated: 2024/03/25 10:30:27 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*cdst;
	char	*csrc;

	if (!dst && !src)
		return (NULL);
	cdst = (char *)dst;
	csrc = (char *)src;
	if (dst <= src)
	{
		while (len--)
		{
			*cdst++ = *csrc++;
		}
	}
	else if (dst > src)
	{
		cdst += len - 1;
		csrc += len - 1;
		while (len--)
		{
			*cdst-- = *csrc--;
		}
	}
	return (dst);
}
