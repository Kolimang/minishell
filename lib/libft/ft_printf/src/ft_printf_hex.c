/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:28:36 by jrichir           #+#    #+#             */
/*   Updated: 2023/11/20 12:09:42 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	ft_printf_hex(unsigned int hex, char letter_case, int c_count)
{
	ssize_t	result;

	c_count += ft_nbrlen_base((unsigned int)hex, 16);
	if (letter_case == 'x')
	{
		result = ft_putnbr_base((unsigned int)hex, "0123456789abcdef");
	}
	else
	{
		result = ft_putnbr_base((unsigned int)hex, "0123456789ABCDEF");
	}
	if (result == -1)
		return (-1);
	else
		return (c_count);
}
