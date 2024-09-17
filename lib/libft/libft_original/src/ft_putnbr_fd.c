/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:10:46 by jrichir           #+#    #+#             */
/*   Updated: 2024/03/25 10:30:45 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	c = '0';
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		if (n != -2147483648)
			n *= -1;
		else
		{
			ft_putstr_fd("2147483648", fd);
			return ;
		}
	}
	if (n > 9)
	{
		c = (char)((n % 10) + 48);
		n /= 10;
		ft_putnbr_fd(n, fd);
	}
	else
		c = (char)n + 48;
	ft_putchar_fd(c, fd);
}
