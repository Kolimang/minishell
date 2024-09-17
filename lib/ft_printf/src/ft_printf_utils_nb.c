/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_nb.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:17:53 by jrichir           #+#    #+#             */
/*   Updated: 2024/03/20 13:56:42 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_valid_base(char *base)
{
	int		i;
	int		j;

	if (!base || ft_printf_strlen(base) < 2)
		return (0);
	i = -1;
	while (base[++i])
	{
		if (base[i] < 32 || base[i] == '+' || base[i] == '-' || base[i] > 126)
			return (0);
		j = i + 1;
		while (base[j] != '\0')
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
	}
	return (1);
}

ssize_t	ft_putunsnbr_base(unsigned long int ulnbr, char *base)
{
	char	unit;
	int		system;
	ssize_t	result;

	if (!base || ft_valid_base(base) == 0)
		return (-1);
	system = (int)ft_printf_strlen(base);
	if (system == -1)
		return (-1);
	unit = base[ulnbr % (unsigned)system];
	if (ulnbr >= (unsigned)system)
	{
		ulnbr /= (unsigned)system;
		result = ft_putunsnbr_base(ulnbr, base);
		if (result == -1)
			return (-1);
	}
	return (write(1, &unit, 1));
}

ssize_t	ft_putnbr_base(long long int nbr, char *base)
{
	char	unit;
	int		system;
	ssize_t	result;

	if (!base || ft_valid_base(base) == 0)
		return (-1);
	system = (int)ft_printf_strlen(base);
	if (system == -1)
		return (-1);
	if (nbr < 0)
	{
		nbr *= -1;
		result = write(1, "-", 1);
		if (result == -1)
			return (-1);
	}
	unit = base[nbr % system];
	if (nbr >= system)
	{
		nbr /= system;
		result = ft_putnbr_base(nbr, base);
		if (result == -1)
			return (-1);
	}
	return (write(1, &unit, 1));
}

int	ft_unsnbrlen_base(unsigned long int nb, int radix)
{
	int	len;

	len = 1;
	while (nb >= (unsigned int)radix)
	{
		nb /= (unsigned int)radix;
		len++;
	}
	return (len);
}

int	ft_nbrlen_base(long long int nb, int radix)
{
	int	len;

	if (nb < 0)
		nb *= (-1);
	len = 1;
	while (nb >= radix)
	{
		nb /= radix;
		len++;
	}
	return (len);
}
