/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:04:29 by jrichir           #+#    #+#             */
/*   Updated: 2024/03/19 15:18:49 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t				len;
	unsigned int		i;
	char				*mod_str;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	mod_str = (char *)malloc((len + 1) * sizeof(char));
	if (!mod_str)
	{
		return (NULL);
	}
	i = 0;
	while ((char)s[i])
	{
		mod_str[i] = f(i, s[i]);
		i++;
	}
	mod_str[i] = '\0';
	return (mod_str);
}
