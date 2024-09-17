/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:58:37 by jrichir           #+#    #+#             */
/*   Updated: 2023/11/20 12:11:20 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	ft_printf_int(int nb, int c_count)
{
	ssize_t			result;

	c_count += ft_nbrlen_base(nb, 10) + (nb < 0);
	result = ft_putnbr_base(nb, "0123456789");
	if (result == -1)
		return (result);
	else
		return (c_count);
}
