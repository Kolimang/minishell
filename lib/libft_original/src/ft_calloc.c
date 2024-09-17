/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:07:57 by jrichir           #+#    #+#             */
/*   Updated: 2024/03/25 10:29:30 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	alloc;

	alloc = count * size;
	if (count != 0 && size != 0)
	{
		if (alloc / count != size || alloc % count != 0)
		{
			return (NULL);
		}
	}
	ptr = (void *)malloc(count * size);
	if (!ptr)
	{
		return (NULL);
	}
	ft_bzero(ptr, alloc);
	return (ptr);
}
