/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:21:33 by jrichir           #+#    #+#             */
/*   Updated: 2023/10/25 17:04:16 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned int		i;
	char				*str;

	str = (char *)b;
	i = 0;
	while (i < len)
	{
		str[i] = (unsigned char)(c);
		i++;
	}
	return (b);
}
