/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:23:20 by jrichir           #+#    #+#             */
/*   Updated: 2024/03/20 11:34:45 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	init_dst_len;
	unsigned int	init_src_len;
	unsigned int	i;

	if (!dst || !src)
		return (0);
	init_dst_len = ft_strlen(dst);
	init_src_len = ft_strlen(src);
	dst += (ft_strlen(dst) * sizeof(char));
	if (dstsize > 0)
	{
		i = 0;
		while (*src && (init_dst_len + i + 1) < dstsize)
		{
			*dst++ = *src++;
			i++;
		}
		*dst = '\0';
		if (init_dst_len < dstsize)
			return (init_dst_len + init_src_len);
		else
			return (dstsize + init_src_len);
	}
	return (init_src_len);
}
