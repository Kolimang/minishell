/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:40:10 by jrichir           #+#    #+#             */
/*   Updated: 2023/11/20 12:50:58 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_handle_args(char c, va_list args, int c_count)
{
	if (c == '%')
		c_count = ft_printf_char('%', c_count);
	else if (c == 'c')
		c_count = ft_printf_char(va_arg(args, int), c_count);
	else if (c == 's')
		c_count = ft_printf_str(va_arg(args, char *), c_count);
	else if (c == 'd' || c == 'i')
		c_count = ft_printf_int(va_arg(args, int), c_count);
	else if (c == 'p')
		c_count = ft_printf_ptr(va_arg(args, unsigned long), c_count);
	else if (c == 'x' || c == 'X')
		c_count = ft_printf_hex(va_arg(args, unsigned int), c, c_count);
	else if (c == 'u')
		c_count = ft_printf_u(va_arg(args, unsigned int), c_count);
	return (c_count);
}

int	ft_printf(const char *str, ...)
{
	int				c_count;
	va_list			args;

	if (!str)
		return (-1);
	va_start(args, str);
	c_count = 0;
	while (*str)
	{
		if (*str != '%')
			c_count = ft_printf_char(*str, c_count);
		else
		{
			str++;
			c_count = ft_handle_args((char)*str, args, c_count);
		}
		if (c_count == -1)
			return (-1);
		str++;
	}
	va_end(args);
	return (c_count);
}
