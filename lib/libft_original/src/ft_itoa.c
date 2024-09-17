/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:26:13 by jrichir           #+#    #+#             */
/*   Updated: 2024/03/25 10:29:46 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	nblen(int n)
{
	size_t	len;

	if (n == -2147483648)
		return (10);
	else if (n < 0)
		n *= -1;
	len = 1;
	while (n > 9)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static int	power(int base, int exponent)
{
	int	power;

	if (exponent == 0)
		return (1);
	power = 1;
	while (exponent--)
	{
		power *= base;
	}
	return (power);
}

char	*ft_itoa(int n)
{
	size_t				len;
	char				*nbstr;
	unsigned int		sign;
	int					i;

	sign = n < 0;
	len = nblen(n);
	nbstr = (char *)malloc((len + sign + 1) * sizeof(char));
	if (!nbstr)
		return (NULL);
	i = 0;
	if (sign)
		nbstr[i++] = '-';
	while (len--)
	{
		nbstr[i] = (n / power(10, len)) % 10;
		if (nbstr[i] < 0)
			nbstr[i] *= -1;
		nbstr[i] += '0';
		i++;
	}
	nbstr[i] = '\0';
	return (nbstr);
}
