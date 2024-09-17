/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:58:37 by jrichir           #+#    #+#             */
/*   Updated: 2024/03/20 14:06:02 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	ft_printf_char(char c, int c_count)
{
	ssize_t			result;

	c_count += 1;
	result = ft_printf_putchar_fd(c, 1);
	if (result == -1)
		return (result);
	else
		return (c_count);
}
