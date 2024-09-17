/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:30:26 by jrichir           #+#    #+#             */
/*   Updated: 2024/03/20 14:05:33 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	ft_printf_ptr(unsigned long ptr, int c_count)
{
	ssize_t	result;

	c_count += ft_unsnbrlen_base(ptr, 16) + 2;
	result = ft_printf_putstr_fd("0x", 1);
	if (result == -1)
		return (-1);
	result = ft_putunsnbr_base(ptr, "0123456789abcdef");
	if (result == -1)
		return (-1);
	else
		return (c_count);
}
